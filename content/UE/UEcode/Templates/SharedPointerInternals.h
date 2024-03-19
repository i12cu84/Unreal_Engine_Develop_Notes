// C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\Core\Public\Templates

// 版权 Epic Games, Inc. 所有权利保留。

#pragma once

// HEADER_UNIT_SKIP - 通过 SharedPointer.h 包含

#include "CoreTypes.h"
#include "HAL/UnrealMemory.h"
#include "Misc/AssertionMacros.h"
#include "Templates/RemoveReference.h"
#include "Templates/SharedPointerFwd.h"
#include "Templates/TypeCompatibleBytes.h"
#include <atomic>
#include <type_traits>

/** 默认行为。 */
#define THREAD_SANITISE_UNSAFEPTR 0

#if THREAD_SANITISE_UNSAFEPTR
#define TSAN_SAFE_UNSAFEPTR
#else
#define TSAN_SAFE_UNSAFEPTR TSAN_SAFE
#endif

/**
 * SharedPointerInternals 包含了共享和弱指针的内部工作原理。你最好不要直接使用这个命名空间内的任何东西。
 */
namespace SharedPointerInternals
{
	// 前向声明
	template <ESPMode Mode>
	class FWeakReferencer;

	/** 在类型转换中用作模板参数的虚拟结构 */
	struct FStaticCastTag
	{
	};
	struct FConstCastTag
	{
	};

	// 注意：以下内容是对标准 shared_ptr 行为的 Unreal 扩展
	struct FNullTag
	{
	};

	template <ESPMode Mode>
	class TReferenceControllerBase
	{
		using RefCountType = std::conditional_t<Mode == ESPMode::ThreadSafe, std::atomic<int32>, int32>;

	public:
		FORCEINLINE explicit TReferenceControllerBase() = default;

		// 对该对象的共享引用数量。当这个计数达到零时，关联的对象将被销毁（即使仍有弱引用也不例外！），但引用控制器不会被销毁。
		//
		// 这个从1开始，因为我们通过 TSharedPtr 的构造来创建引用控制器，这是第一个引用。没有必要从0开始然后递增它。
		RefCountType SharedReferenceCount{ 1 };

		// 对该对象的弱引用数量。如果有任何共享引用，那也算作一个弱引用。当这个计数达到零时，引用控制器将被销毁。
		//
		// 这个从1开始，因为它代表我们同时初始化 SharedReferenceCount 的共享引用。
		RefCountType WeakReferenceCount{ 1 };

		/** 销毁与这个引用计数器关联的对象。 */
		virtual void DestroyObject() = 0;

		virtual ~TReferenceControllerBase()
		{
		}

		/** 返回共享引用计数 */
		FORCEINLINE int32 GetSharedReferenceCount() const
		{
			if constexpr (Mode == ESPMode::ThreadSafe)
			{
				// 一个 '活动' 的共享引用计数本质上是不可稳定的，因此尝试围绕它的读取强制内存顺序是没有好处的。
				//
				// 这相当于 https://en.cppreference.com/w/cpp/memory/shared_ptr/use_count

				// 这个引用计数可能被多个线程访问
				return SharedReferenceCount.load(std::memory_order_relaxed);
			}
			else
			{
				return SharedReferenceCount;
			}
		}

		/** 检查是否恰好有一个引用留在对象上。 */
		FORCEINLINE bool IsUnique() const
		{
			if constexpr (Mode == ESPMode::ThreadSafe)
			{
				// 这相当于 C++ 参考手册中的 shared_ptr::unique，
				// 然而我们不将其弃用，而是使用一个获取操作，这应该
				// 符合我们的使用场景。

				// 这个引用计数可能被多个线程访问
				return SharedReferenceCount.load(std::memory_order_acquire) == 1;
			}
			else
			{
				// 在非线程安全的模式下，直接比较引用计数
				return SharedReferenceCount == 1;
			}
		}

		/** 向此计数器添加一个共享引用 */
		FORCEINLINE void AddSharedReference()
		{
			if constexpr (Mode == ESPMode::ThreadSafe)
			{
				// 以松散的顺序增加引用计数始终是安全的，因为没有任何其他操作会响应这个增加，所以不存在需要排序的情况。

#if defined(_MSC_VER) && (defined(_M_X64) || defined(_M_IX86))
				// 在这里我们使用普通的 SC 增加，因为它是通过 _InterlockedIncrement (锁增) 实现的。
				// 在 MSVC 下，松散的 fetch_add 生成的代码实际上要差得多（锁 xadd）。
				++SharedReferenceCount;
#else
				SharedReferenceCount.fetch_add(1, std::memory_order_relaxed);
#endif
			}
			else
			{
				++SharedReferenceCount;
			}
		}

		/**
		 * 仅当已经有至少一个引用时，才向此计数器添加一个共享引用
		 *
		 * @return  成功添加共享引用返回 true
		 */
		bool ConditionallyAddSharedReference()
		{
			if constexpr (Mode == ESPMode::ThreadSafe)
			{
				// 参见 AddSharedReference，这里同样使用 std::memory_order_relaxed 是因为同样的原因。

				// 窥视当前的共享引用计数。记住，这个值可能被多个线程更新。
				int32 OriginalCount = SharedReferenceCount.load(std::memory_order_relaxed);

				for (;;)
				{
					if (OriginalCount == 0)
					{
						// 如果指针已经过期，绝不要添加共享引用
						return false;
					}

					// 尝试增加引用计数。
					//
					// 我们需要确保我们永远不会复活一个已经过期的计数器，所以如果实际的值与我们预期的（因为另一个线程触摸了它）不符，那么我们将再次尝试。
					// 注意，实际上只有在不寻常的情况下才会需要循环。
					//
					// 我们在这里使用弱读取，因为我们需要循环，这是推荐的做法：
					//
					// https://en.cppreference.com/w/cpp/atomic/atomic/compare_exchange
					//
					// > 当 compare-and-exchange 在循环中时，弱版本将会在某些平台上提供更好的性能。
					// > 当一个弱 compare-and-exchange 需要循环而强的一个不需要时，强的一个更可取
					if (SharedReferenceCount.compare_exchange_weak(OriginalCount, OriginalCount + 1, std::memory_order_relaxed))
					{
						return true;
					}
				}
			}
			else
			{
				if (SharedReferenceCount == 0)
				{
					// 如果指针已经过期，绝不要添加共享引用
					return false;
				}

				++SharedReferenceCount;
				return true;
			}
		}
		/** 释放对 this 计数器的共享引用 */
		FORCEINLINE void ReleaseSharedReference()
		{
			if constexpr (Mode == ESPMode::ThreadSafe)
			{
				// 使用 std::memory_order_acq_rel，以确保如果我们最终执行了析构函数，那么析构函数的副作用不会在我们确定共享引用计数实际上是零之前可见。

				int32 OldSharedCount = SharedReferenceCount.fetch_sub(1, std::memory_order_acq_rel);
				checkSlow(OldSharedCount > 0); // 确保引用计数在减一后仍然大于零
				if (OldSharedCount == 1)
				{
					// 最后一个共享引用被释放了！销毁引用的对象。
					DestroyObject();

					// 没有更多的共享引用，因此减少一个弱引用计数。当弱引用计数达到零时，此对象将被删除。
					ReleaseWeakReference();
				}
			}
			else
			{
				checkSlow(SharedReferenceCount > 0); // 确保共享引用计数大于零

				if (--SharedReferenceCount == 0)
				{
					// 最后一个共享引用被释放了！销毁引用的对象。
					DestroyObject();

					// 没有更多的共享引用，因此减少一个弱引用计数。当弱引用计数达到零时，此对象将被删除。
					ReleaseWeakReference();
				}
			}
		}

		/** 向此计数器添加一个弱引用 */
		FORCEINLINE void AddWeakReference()
		{
			if constexpr (Mode == ESPMode::ThreadSafe)
			{
				// 参见 AddSharedReference，这里同样使用 std::memory_order_relaxed 是因为同样的原因。

#if defined(_MSC_VER) && (defined(_M_X64) || defined(_M_IX86))
				// 在这里我们使用普通的 SC 增加，因为它是通过 _InterlockedIncrement (锁增) 实现的。
				// 在 MSVC 下，松散的 fetch_add 生成的代码实际上要差得多（锁 xadd）。
				++WeakReferenceCount;
#else
				WeakReferenceCount.fetch_add(1, std::memory_order_relaxed);
#endif
			}
			else
			{
				++WeakReferenceCount;
			}
		}

		/** 释放对 this 计数器的弱引用 */
		void ReleaseWeakReference()
		{
			if constexpr (Mode == ESPMode::ThreadSafe)
			{
				// 参见 ReleaseSharedReference，这里同样使用 std::memory_order_acq_rel 是因为同样的原因。

				int32 OldWeakCount = WeakReferenceCount.fetch_sub(1, std::memory_order_acq_rel);
				checkSlow(OldWeakCount > 0); // 确保弱引用计数在减一后仍然大于零
				if (OldWeakCount == 1)
				{
					// 当运行 clang 的静态分析器时，禁用此操作。向它传递无法推理的共享指针和引用，会在 TSharedPtr/TSharedRef 析构函数中产生关于使用后释放的虚假阳性。
#if !defined(__clang_analyzer__)
					// 没有更多的引用指向这个引用计数。销毁它！
					delete this;
#endif
				}
			}
			else
			{
				checkSlow(WeakReferenceCount > 0); // 确保弱引用计数大于零

				if (--WeakReferenceCount == 0)
				{
					// 没有更多的引用指向这个引用计数。销毁它！
#if !defined(__clang_analyzer__)
					delete this;
#endif
				}
			}
		}

		// 不可复制
		TReferenceControllerBase(const TReferenceControllerBase&) = delete;
		TReferenceControllerBase& operator=(const TReferenceControllerBase&) = delete;
	};

	// 一个帮助类，用于有效地存储自定义删除器，并打算被派生类使用。如果自定义删除器是一个空类，
	// TDeleterHolder 利用空基优化（https://en.cppreference.com/w/cpp/language/ebo）从它派生。否则，
	// 它将自定义删除器作为成员存储，以允许使用函数指针作为自定义删除器（函数指针不能
	// 作为基类）
	template <typename DeleterType, bool bIsZeroSize = std::is_empty_v<DeleterType>>
	struct TDeleterHolder : private DeleterType
	{
		explicit TDeleterHolder(DeleterType&& Arg)
			: DeleterType(MoveTemp(Arg))
		{
		}

		template <typename ObjectType>
		void InvokeDeleter(ObjectType* Object)
		{
			Invoke(*static_cast<DeleterType*>(this), Object);
		}
	};

	template <typename DeleterType>
	struct TDeleterHolder<DeleterType, false>
	{
		explicit TDeleterHolder(DeleterType&& Arg)
			: Deleter(MoveTemp(Arg))
		{
		}

		template <typename ObjectType>
		void InvokeDeleter(ObjectType* Object)
		{
			Invoke(Deleter, Object);
		}

	private:
		DeleterType Deleter;
	};

	template <typename ObjectType, typename DeleterType, ESPMode Mode>
	class TReferenceControllerWithDeleter : private TDeleterHolder<DeleterType>, public TReferenceControllerBase<Mode>
	{
	public:
		explicit TReferenceControllerWithDeleter(ObjectType* InObject, DeleterType&& Deleter)
			: TDeleterHolder<DeleterType>(MoveTemp(Deleter)), Object(InObject)
		{
		}

		virtual void DestroyObject() override
		{
			this->InvokeDeleter(Object);
		}

		// 不可复制
		TReferenceControllerWithDeleter(const TReferenceControllerWithDeleter&) = delete;
		TReferenceControllerWithDeleter& operator=(const TReferenceControllerWithDeleter&) = delete;

	private:
		/** 与此引用计数器关联的对象。  */
		ObjectType* Object;
	};
	template <typename ObjectType, ESPMode Mode>
	class TIntrusiveReferenceController : public TReferenceControllerBase<Mode>
	{
	public:
		template <typename... ArgTypes>
		explicit TIntrusiveReferenceController(ArgTypes &&...Args)
		{
			// 如果尝试用非公共构造函数调用 MakeShared 时失败，
			// 不要将 SharedPointerInternals::TIntrusiveReferenceController 设为朋友。
			//
			// 相反，推荐使用以下模式：
			//
			//     class FMyType
			//     {
			//     private:
			//         struct FPrivateToken { explicit FPrivateToken() = default; };
			//
			//     public:
			//         // 此构造函数的访问级别与私有构造函数等效，
			//         // 因为只有 FMyType 的朋友才能访问 FPrivateToken，
			//         // 但 MakeShared 可以合法地调用它，因为它是公共的。
			//         explicit FMyType(FPrivateToken, int32 Int, float Real, const TCHAR* String);
			//     };
			//
			//     // 如果调用者没有访问 FMyType::FPrivateToken 的权限，则不会编译
			//     TSharedPtr<FMyType> Val = MakeShared<FMyType>(FMyType::FPrivateToken{}, 5, 3.14f, TEXT("Banana"));
			//
			new ((void*)&ObjectStorage) ObjectType(Forward<ArgTypes>(Args)...);
		}

		ObjectType* GetObjectPtr() const
		{
			return (ObjectType*)&ObjectStorage;
		}

		virtual void DestroyObject() override
		{
			DestructItem((ObjectType*)&ObjectStorage);
		}

		// 不可复制
		TIntrusiveReferenceController(const TIntrusiveReferenceController&) = delete;
		TIntrusiveReferenceController& operator=(const TIntrusiveReferenceController&) = delete;

	private:
		/** 与此引用计数器关联的对象。  */
		mutable TTypeCompatibleBytes<ObjectType> ObjectStorage;
	};

	/** 通过标准 delete 操作符删除一个对象 */
	template <typename Type>
	struct DefaultDeleter
	{
		FORCEINLINE void operator()(Type* Object) const
		{
			delete Object;
		}
	};
	/** 创建一个调用 delete 的引用控制器 */
	template <ESPMode Mode, typename ObjectType>
	inline TReferenceControllerBase<Mode>* NewDefaultReferenceController(ObjectType* Object)
	{
		return new TReferenceControllerWithDeleter<ObjectType, DefaultDeleter<ObjectType>, Mode>(Object, DefaultDeleter<ObjectType>());
	}

	/** 创建一个带有指定删除器的自定义引用控制器 */
	template <ESPMode Mode, typename ObjectType, typename DeleterType>
	inline TReferenceControllerBase<Mode>* NewCustomReferenceController(ObjectType* Object, DeleterType&& Deleter)
	{
		return new TReferenceControllerWithDeleter<ObjectType, typename TRemoveReference<DeleterType>::Type, Mode>(Object, Forward<DeleterType>(Deleter));
	}

	/** 创建一个侵入式引用控制器 */
	template <ESPMode Mode, typename ObjectType, typename... ArgTypes>
	inline TIntrusiveReferenceController<ObjectType, Mode>* NewIntrusiveReferenceController(ArgTypes &&...Args)
	{
		return new TIntrusiveReferenceController<ObjectType, Mode>(Forward<ArgTypes>(Args)...);
	}

	/** 用于隐式地将原始指针转换为共享/弱指针的代理结构 */
	// 注意：以下内容是 Unreal 对标准 shared_ptr 行为的扩展
	template <class ObjectType>
	struct TRawPtrProxy
	{
		/** 对象指针 */
		ObjectType* Object;

		/** 从 nullptr 隐式构造 */
		FORCEINLINE TRawPtrProxy(TYPE_OF_NULLPTR)
			: Object(nullptr)
		{
		}

		/** 从一个对象显式构造 */
		explicit FORCEINLINE TRawPtrProxy(ObjectType* InObject)
			: Object(InObject)
		{
		}
	};

	/** 用于隐式地将原始指针转换为共享/弱指针，并带有自定义删除器的代理结构 */
	// 注意：以下内容是 Unreal 对标准 shared_ptr 行为的扩展
	template <class ObjectType, typename DeleterType>
	struct TRawPtrProxyWithDeleter
	{
		/** 对象指针 */
		ObjectType* Object;

		/** 删除器对象 */
		DeleterType Deleter;

		/** 从一个对象和自定义删除器隐式构造 */
		FORCEINLINE TRawPtrProxyWithDeleter(ObjectType* InObject, const DeleterType& InDeleter)
			: Object(InObject), Deleter(InObject, InDeleter)
		{
		}

		/** 从一个对象和自定义删除器隐式构造 */
		FORCEINLINE TRawPtrProxyWithDeleter(ObjectType* InObject, DeleterType&& InDeleter)
			: Object(InObject), Deleter(MoveTemp(InDeleter))
		{
		}
	};

	/**
	 * FSharedReferencer 是一个包装了引用控制器指针的类，它被 TSharedRef 或 TSharedPtr 使用，以跟踪引用的对象的生存周期
	 */
	template <ESPMode Mode>
	class FSharedReferencer
	{
	public:
		/** 构造一个空的共享引用器对象 */
		FORCEINLINE FSharedReferencer()
			: ReferenceController(nullptr)
		{
		}

		/** 构造函数，用于对指定对象计数单个引用 */
		inline explicit FSharedReferencer(TReferenceControllerBase<Mode>* InReferenceController)
			: ReferenceController(InReferenceController)
		{
		}

		/** 复制构造函数，创建对现有对象的新的引用 */
		FORCEINLINE FSharedReferencer(FSharedReferencer const& InSharedReference)
			: ReferenceController(InSharedReference.ReferenceController)
		{
			// 如果传入的引用关联了对象，那么就增加共享引用计数
			if (ReferenceController != nullptr)
			{
				ReferenceController->AddSharedReference();
			}
		}

		/** 移动构造函数，不创建新的引用 */
		FORCEINLINE FSharedReferencer(FSharedReferencer&& InSharedReference)
			: ReferenceController(InSharedReference.ReferenceController)
		{
			InSharedReference.ReferenceController = nullptr;
		}

		/** 从一个弱引用器对象创建共享引用器对象。如果对象已经有至少一个其他共享引用器，这将只导致一个有效的对象引用 */
		FSharedReferencer(FWeakReferencer<Mode> const& InWeakReference)
			: ReferenceController(InWeakReference.ReferenceController)
		{
			// 如果传入的引用关联了对象，那么就增加共享引用计数
			if (ReferenceController != nullptr)
			{
				// 尝试将弱引用提升为共享引用。为了使这工作，这个弱引用计数关联的对象必须已经有至少一个共享引用。我们不会复活一个已经过期的指针！
				if (!ReferenceController->ConditionallyAddSharedReference())
				{
					ReferenceController = nullptr;
				}
			}
		}

		/** 从一个弱引用器对象创建共享引用器对象。如果对象已经有至少一个其他共享引用器，这将只导致一个有效的对象引用 */
		FSharedReferencer(FWeakReferencer<Mode>&& InWeakReference)
			: ReferenceController(InWeakReference.ReferenceController)
		{
			// 如果传入的引用关联了对象，那么就增加共享引用计数
			if (ReferenceController != nullptr)
			{
				// 尝试将弱引用提升为共享引用。为了使这工作，这个弱引用计数关联的对象必须已经有至少一个共享引用。我们不会复活一个已经过期的指针！
				if (!ReferenceController->ConditionallyAddSharedReference())
				{
					ReferenceController = nullptr;
				}

				// 告诉引用计数对象，我们不再用这个弱指针引用对象
				InWeakReference.ReferenceController->ReleaseWeakReference();
				InWeakReference.ReferenceController = nullptr;
			}
		}

		/** 析构函数。 */
		FORCEINLINE ~FSharedReferencer()
		{
			if (ReferenceController != nullptr)
			{
				// 告诉引用计数对象，我们不再用这个共享指针引用对象
				ReferenceController->ReleaseSharedReference();
			}
		}

		/** 赋值运算符，向赋值的对象添加一个引用。如果这个计数器之前引用了一个对象，那么那个引用将被释放。 */
		inline FSharedReferencer& operator=(FSharedReferencer const& InSharedReference)
		{
			// 确保我们不会被重新赋值给自己！
			auto NewReferenceController = InSharedReference.ReferenceController;
			if (NewReferenceController != ReferenceController)
			{
				// 首先，向新对象添加共享引用
				if (NewReferenceController != nullptr)
				{
					NewReferenceController->AddSharedReference();
				}

				// 释放对旧对象的共享引用
				if (ReferenceController != nullptr)
				{
					ReferenceController->ReleaseSharedReference();
				}

				// 接管赋值的引用计数器
				ReferenceController = NewReferenceController;
			}

			return *this;
		}

		/** 移动赋值运算符，向赋值的对象添加没有引用。如果这个计数器之前引用了一个对象，那么那个引用将被释放。 */
		inline FSharedReferencer& operator=(FSharedReferencer&& InSharedReference)
		{
			// 确保我们不会被重新赋值给自己！
			auto NewReferenceController = InSharedReference.ReferenceController;
			auto OldReferenceController = ReferenceController;
			if (NewReferenceController != OldReferenceController)
			{
				// 接管赋值的引用计数器
				InSharedReference.ReferenceController = nullptr;
				ReferenceController = NewReferenceController;

				// 释放对旧对象的共享引用
				if (OldReferenceController != nullptr)
				{
					OldReferenceController->ReleaseSharedReference();
				}
			}

			return *this;
		}

		/**
		 * 检查此共享计数器是否包含有效引用
		 *
		 * @return 如果引用有效返回真
		 */
		FORCEINLINE const bool IsValid() const
		{
			// 如果引用控制器不为空，则引用有效
			return ReferenceController != nullptr;
		}

		/**
		 * 返回对此对象的共享引用数量（包括此引用）
		 *
		 * @return 对象的共享引用数量（包括此引用）
		 */
		FORCEINLINE const int32 GetSharedReferenceCount() const
		{
			// 如果引用控制器不为空，则返回引用数量，否则返回0
			return ReferenceController != nullptr ? ReferenceController->GetSharedReferenceCount() : 0;
		}

		/**
		 * 如果这是对此对象的唯一共享引用，则返回真。注意可能还有未解决的弱引用。
		 *
		 * @return 如果对象的唯一共享引用是此引用，则返回真
		 */
		FORCEINLINE const bool IsUnique() const
		{
			// 如果引用控制器不为空并且引用控制器表明引用唯一，则返回真
			return ReferenceController != nullptr && ReferenceController->IsUnique();
		}

	private:
		// 允许FWeakReferencer访问ReferenceController
		template <ESPMode OtherMode>
		friend class FWeakReferencer;

	private:
		/** 指向共享引用/指针所引用对象的引用控制器的指针 */
		TReferenceControllerBase<Mode>* ReferenceController;
	};

	/**
	 * FWeakReferencer是一个包装器，用于通过TWeakPtr跟踪引用对象生命周期的引用控制器的指针。
	 */
	template <ESPMode Mode>
	class FWeakReferencer
	{
	public:
		/** 默认构造函数，初始化为空计数器 */
		FORCEINLINE FWeakReferencer()
			: ReferenceController(nullptr)
		{
		}

		/** 从另一个弱引用计数器构造弱引用计数器对象 */
		FORCEINLINE FWeakReferencer(FWeakReferencer const& InWeakRefCountPointer)
			: ReferenceController(InWeakRefCountPointer.ReferenceController)
		{
			// 如果弱引用计数器有有效的控制器，则向其添加弱引用
			if (ReferenceController != nullptr)
			{
				ReferenceController->AddWeakReference();
			}
		}

		/** 从右值弱引用计数器构造弱引用计数器对象 */
		FORCEINLINE FWeakReferencer(FWeakReferencer&& InWeakRefCountPointer)
			: ReferenceController(InWeakRefCountPointer.ReferenceController)
		{
			// 重置输入的弱引用计数器的控制器指针
			InWeakRefCountPointer.ReferenceController = nullptr;
		}

		/** 从共享引用计数器对象构造弱引用计数器对象 */
		FORCEINLINE FWeakReferencer(FSharedReferencer<Mode> const& InSharedRefCountPointer)
			: ReferenceController(InSharedRefCountPointer.ReferenceController)
		{
			// 如果共享引用计数器有有效的控制器，则向其添加弱引用
			if (ReferenceController != nullptr)
			{
				ReferenceController->AddWeakReference();
			}
		}

		/** 析构函数。 */
		FORCEINLINE ~FWeakReferencer()
		{
			if (ReferenceController != nullptr)
			{
				// 通知引用计数器对象，我们不再使用此弱指针引用对象
				ReferenceController->ReleaseWeakReference();
			}
		}

		/** 从弱引用计数器对象赋值。如果此前计数器引用了某个对象，该引用将被释放。 */
		FORCEINLINE FWeakReferencer& operator=(FWeakReferencer const& InWeakReference)
		{
			AssignReferenceController(InWeakReference.ReferenceController);

			return *this;
		}

		/** 从右值弱引用计数器对象赋值。如果此前计数器引用了某个对象，该引用将被释放。 */
		FORCEINLINE FWeakReferencer& operator=(FWeakReferencer&& InWeakReference)
		{
			auto OldReferenceController = ReferenceController;
			ReferenceController = InWeakReference.ReferenceController;
			InWeakReference.ReferenceController = nullptr;
			if (OldReferenceController != nullptr)
			{
				OldReferenceController->ReleaseWeakReference();
			}

			return *this;
		}

		/** 从共享引用计数器赋值。如果此前计数器引用了某个对象，该引用将被释放。 */
		FORCEINLINE FWeakReferencer& operator=(FSharedReferencer<Mode> const& InSharedReference)
		{
			AssignReferenceController(InSharedReference.ReferenceController);

			return *this;
		}

		/**
		 * 检查此弱引用计数器是否包含有效引用
		 *
		 * @return 如果引用有效返回真
		 */
		FORCEINLINE const bool IsValid() const
		{
			// 如果引用控制器不为空且共享引用计数大于0，则引用有效
			return ReferenceController != nullptr && ReferenceController->GetSharedReferenceCount() > 0;
		}

	private:
		/** 为此计数器对象分配新的引用控制器，首先添加对新对象的弱引用，然后释放对旧对象的引用。 */
		inline void AssignReferenceController(TReferenceControllerBase<Mode>* NewReferenceController)
		{
			// 只有当新的引用控制器与当前的不同时才继续
			if (NewReferenceController != ReferenceController)
			{
				// 首先，添加对新对象的弱引用
				if (NewReferenceController != nullptr)
				{
					NewReferenceController->AddWeakReference();
				}

				// 释放对旧对象的弱引用
				if (ReferenceController != nullptr)
				{
					ReferenceController->ReleaseWeakReference();
				}

				// 假设对分配的引用计数器的所有权
				ReferenceController = NewReferenceController;
			}
		}

	private:
		/** 允许FSharedReferencer访问ReferenceController。 */
		template <ESPMode OtherMode>
		friend class FSharedReferencer;

	private:
		/** 指向TWeakPtr所引用对象的引用控制器的指针。 */
		TReferenceControllerBase<Mode>* ReferenceController;
	};

	/**
	 * 模板辅助函数（常量），用于从对象实例创建共享指针。
	 */
	template <class SharedPtrType, class ObjectType, class OtherType, ESPMode Mode>
	FORCEINLINE void EnableSharedFromThis(TSharedPtr<SharedPtrType, Mode> const* InSharedPtr, ObjectType const* InObject, TSharedFromThis<OtherType, Mode> const* InShareable)
	{
		if (InShareable != nullptr)
		{
			// 更新内部弱引用
			InShareable->UpdateWeakReferenceInternal(InSharedPtr, const_cast<ObjectType*>(InObject));
		}
	}

	/**
	 * 模板辅助函数，用于从对象实例创建共享指针。
	 */
	template <class SharedPtrType, class ObjectType, class OtherType, ESPMode Mode>
	FORCEINLINE void EnableSharedFromThis(TSharedPtr<SharedPtrType, Mode>* InSharedPtr, ObjectType const* InObject, TSharedFromThis<OtherType, Mode> const* InShareable)
	{
		if (InShareable != nullptr)
		{
			// 更新内部弱引用
			InShareable->UpdateWeakReferenceInternal(InSharedPtr, const_cast<ObjectType*>(InObject));
		}
	}

	/**
	 * 模板辅助函数（常量），用于从对象实例创建共享引用。
	 */
	template <class SharedRefType, class ObjectType, class OtherType, ESPMode Mode>
	FORCEINLINE void EnableSharedFromThis(TSharedRef<SharedRefType, Mode> const* InSharedRef, ObjectType const* InObject, TSharedFromThis<OtherType, Mode> const* InShareable)
	{
		if (InShareable != nullptr)
		{
			// 更新内部弱引用
			InShareable->UpdateWeakReferenceInternal(InSharedRef, const_cast<ObjectType*>(InObject));
		}
	}

	/**
	 * 模板辅助函数，用于从对象实例创建共享引用。
	 */
	template <class SharedRefType, class ObjectType, class OtherType, ESPMode Mode>
	FORCEINLINE void EnableSharedFromThis(TSharedRef<SharedRefType, Mode>* InSharedRef, ObjectType const* InObject, TSharedFromThis<OtherType, Mode> const* InShareable)
	{
		if (InShareable != nullptr)
		{
			// 更新内部弱引用
			InShareable->UpdateWeakReferenceInternal(InSharedRef, const_cast<ObjectType*>(InObject));
		}
	}

	/**
	 * 模板辅助捕获所有函数，以上辅助函数的助手。
	 */
	FORCEINLINE void EnableSharedFromThis(...) {}

}

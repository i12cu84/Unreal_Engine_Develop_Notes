// C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\Core\Public\Windows\WindowsPlatformCompilerSetup.h

// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#if !PLATFORM_WINDOWS
#error PLATFORM_WINDOWS not defined
#endif

//
// 为了保证最小版本检查的未来，所以每次升级时我们都会提升它。
//
#if defined(_MSC_VER) && _MSC_VER > 1939
#pragma message("Detected compiler newer than Visual Studio 2022, please update min version checking in WindowsPlatformCompilerSetup.h")
#endif

//
// 我们至少需要Visual Studio 2019才能编译
//
static_assert(_MSC_VER >= 1929, "Visual Studio 2019 v16.11 or greater is required to build Unreal Engine.");

//
// 手动启用所有警告为错误，除非显式跳过。
// 我们稍后明确禁用的警告仍然包含在其中。
//

#pragma warning(error : 4001 4002 4003 4006 4007 4008 4010 4013 4015 4018 4019 4020 4022 4023 4024 4025 4026 4027 4028 4029 4030 4031 4032 4033 4034 4035 4036 4038 4041 4042 4045 4047 4048 4049 4051 4052 4053 4054 4055 4056 4057 4060 4064 4065 4066 4067 4068 4069 4073 4074 4075 4076 4077 4079 4080 4081 4083 4085 4086 4087 4088 4089 4090 4091 4092 4094 4096 4097 4098 4099)
#pragma warning(error : 4100 4101 4102 4103 4109 4112 4113 4114 4115 4116 4117 4119 4120 4121 4122 4123 4124 4125 4127 4129 4130 4131 4132 4133 4137 4138 4141 4142 4143 4144 4145 4146 4150 4152 4153 4154 4155 4156 4157 4158 4159 4160 4161 4162 4163 4164 4166 4167 4168 4172 4174 4175 4176 4177 4178 4179 4180 4181 4182 4183 4185 4186 4187 4188 4189 4190 4191 4192 4193 4194 4195 4196 4197 4199)
#pragma warning(error : 4200 4201 4202 4203 4204 4205 4206 4207 4208 4210 4211 4212 4213 4214 4215 4216 4218 4220 4221 4223 4224 4226 4227 4228 4229 4230 4232 4233 4234 4235 4237 4238 4239 4240 4243 4245 4250 4251 4255 4256 4258 4263 4264 4267 4268 4269 4272 4273 4274 4275 4276 4277 4278 4279 4280 4281 4282 4283 4285 4286 4287 4288 4289 4290 4291 4293 4295 4297 4298 4299)
#pragma warning(error : 4301 4302 4303 4306 4308 4309 4310 4313 4314 4315 4316 4318 4319 4321 4322 4323 4324 4325 4326 4327 4328 4329 4330 4333 4334 4335 4336 4337 4338 4340 4343 4344 4346 4348 4352 4353 4355 4356 4357 4358 4359 4362 4364 4366 4367 4368 4369 4374 4375 4376 4377 4378 4379 4380 4381 4382 4383 4384 4387 4389 4390 4391 4392 4393 4394 4395 4396 4397 4398 4399)
#pragma warning(error : 4400 4401 4402 4403 4404 4405 4406 4407 4408 4409 4410 4411 4413 4414 4415 4416 4417 4418 4419 4420 4423 4424 4425 4426 4427 4429 4430 4431 4434 4436 4438 4439 4440 4441 4442 4443 4445 4446 4447 4448 4449 4450 4451 4452 4453 4454 4455 4460 4461 4462 4464 4465 4466 4467 4468 4469 4470 4473 4474 4475 4476 4477 4478 4480 4482 4483 4484 4485 4486 4487 4488 4489 4490 4491 4492 4493 4494 4495 4496 4497 4498 4499)
#pragma warning(error : 4502 4503 4505 4506 4508 4509 4511 4512 4513 4514 4515 4516 4517 4518 4519 4521 4522 4523 4526 4530 4531 4532 4533 4534 4535 4536 4537 4538 4540 4541 4542 4543 4544 4545 4546 4550 4551 4552 4553 4554 4556 4557 4558 4559 4561 4562 4564 4565 4566 4568 4569 4570 4572 4573 4575 4576 4578 4580 4581 4584 4585 4586 4587 4588 4589 4591 4593 4594 4595 4596 4597 4598)
#pragma warning(error : 4600 4602 4603 4604 4606 4609 4610 4611 4612 4613 4615 4616 4618 4620 4621 4622 4623 4624 4625 4626 4627 4628 4629 4630 4631 4632 4633 4634 4635 4636 4637 4638 4639 4640 4641 4642 4644 4645 4646 4648 4649 4650 4652 4653 4654 4655 4656 4657 4658 4659 4661 4662 4667 4669 4670 4671 4672 4673 4674 4676 4677 4678 4679 4680 4681 4682 4683 4684 4685 4686 4687 4688 4689 4690 4691 4693 4694 4695 4696 4698)
#pragma warning(error : 4700 4702 4703 4706 4709 4710 4711 4714 4715 4716 4717 4718 4719 4720 4721 4722 4723 4724 4725 4726 4727 4728 4729 4731 4732 4733 4734 4739 4740 4741 4742 4743 4744 4745 4747 4749 4750 4751 4752 4753 4754 4755 4756 4757 4761 4764 4771 4772 4775 4776 4777 4778 4786 4788 4789 4792 4793 4794 4798 4799)
#pragma warning(error : 4800 4801 4803 4804 4805 4806 4807 4808 4809 4810 4811 4812 4813 4815 4816 4817 4821 4822 4823 4827 4829 4834 4835 4839 4840 4841 4842 4843 4844 4845 4846 4847 4848 4849 4867 4869 4872 4880 4881 4882 4883)
#pragma warning(error : 4900 4905 4906 4910 4912 4913 4916 4917 4918 4920 4921 4925 4926 4927 4928 4929 4930 4931 4932 4934 4935 4936 4937 4938 4939 4944 4945 4946 4947 4948 4949 4950 4951 4952 4953 4954 4955 4956 4957 4958 4959 4960 4961 4963 4964 4965 4966 4970 4971 4972 4973 4974 4981 4985 4989 4990 4991 4992 4995 4997 4998 4999)
#pragma warning(error : 5038)

//
// 跳过警告，在下面不会禁用。大多数默认是禁用的。可能需要检查一下，重新启用一些并修复代码。
// 注意:我们不会在这些警告上使用#pragma warning(disable:####)，因为default启用默认为禁用的警告。
//

// 4005 - ` identifier `:宏重新定义https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4005
// 4061 -枚举` enumeration `开关中的枚举器` identifier `不是由case标签显式处理https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4061
// 4062 -枚举“枚举”开关中的枚举“标识符”没有被处理https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4062

// 4165 - ` HRESULT `被转换为` bool `;你确定这是你想要的吗?https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4165

// 4242 - ` identifier `:从` type1 `到` type2 `的转换，可能丢失数据https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4242
// 4254 - ` operator `:从` type1 `转换为` type2 `，可能丢失数据https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4254
// 4265 - ` class `:类有虚函数，但析构函数不是虚函数https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-3-c4265
// 4266 - ` function `:基类` type `中的虚成员函数不可重写;功能隐藏https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4266
// 4296 - ` operator `:表达式总是false https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4296

// 4305 - ` identifier `:从` type1 `截断为` type2 ` https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4305
// 4307 - ":整数常量溢出https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4307
// 4311 - ` variable `:指针从` type `截断到` type ` https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4311
// 4312 - 'operation':将'type1'转换为更大的'type2' https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4312
// 4339 - 'type':在CLR元数据中检测到未定义类型的使用-使用此类型可能导致运行时异常https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4339
// 4342 -行为改变:在之前的版本中调用了` function `，但调用了成员运算符https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4342
// 4345 -行为改变:用form()的初始化方法构造的POD类型对象将被default-initialized http://msdn.microsoft.com/en-us/library/wewb47ee.aspx
// 4350 -行为改变:调用'member1'而不是'member2' https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4350
// 4365 - ` action `:从` type_1 `到` type_2 `的转换，有符号/无符号不匹配https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4365
// 4370 -由于更好的打包，类的布局与以前版本的编译器不同https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4200-through-c4399
// 4371 -类的布局可能与以前版本的编译器不同，因为成员的包装更好https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/c4371
// 4373 - ` function `:虚函数覆盖` base_function `，以前版本的编译器不会覆盖参数仅与const/volatile限定符不同的情况https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-3-c4373
// 4388 - '==':有符号/无符号不匹配https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4200-through-c4399
// 4412 - 'function':函数签名包含类型'type';c++对象在纯代码和混合代码或本地代码之间传递是不安全的https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4412
// 4435 - 'class1':/ vd2下的对象布局将因虚拟基地'class2' https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4435而改变
// 4437 - dynamic_cast从虚拟基础'class1'转换为'class2'在某些情况下可能会失败https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4437
// 4444 - ` identifier `:在这里没有实现顶层的` __unaligned ` https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4400-through-c4599

// 注意:阴影变量声明警告。这些最终应该被修复并重新启用。
//  4456 - ` identifier `的声明隐藏了之前的本地声明https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4456
//  4457 -声明` identifier `隐藏函数参数https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4457
//  4458 -声明` identifier `隐藏类成员https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4458
//  4459 -声明` identifier `隐藏全局声明https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4459

// 4463 -溢出;为位字段赋值，该位字段只能保存low_value到high_value的值https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4463
// 4471 -无作用域枚举的前向声明必须有基础类型(假定为int) https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4471
// 4472 - ` identifier `是一个原生枚举:添加一个访问标识符(private/public)来声明一个` WinRT|managed `枚举https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4400-through-c4599
// 4481 -使用了非标准扩展:覆盖说明符'keyword' https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4481

// 4510 - ` class `:无法生成默认构造函数https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4510
// 4547 - 'operator':逗号前面的运算符无效;期望操作员有副作用https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4547
// 4548 -逗号前面的表达式无效;有副作用的预期表达https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4548
// 4549 - 'operator':逗号前面的运算符无效;你想用` operator `吗?https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4549
// 4555 -表达式没有作用;有副作用的预期表达https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4555
// 4571 - Informational: catch(…)语义自Visual c++ 7.1以来发生了变化;不再捕获结构化异常(SEH) https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4571
// 4574 - ` Identifier `被定义为` 0 `:你是想使用` #if Identifier `吗?https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4400-through-c4599
// 4577 - ` noexcept `在不指定异常处理模式的情况下使用;不保证在异常情况下终止。请指定/ ehsc https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4400-through-c4599

// 4608 - 'union_member'已经被初始化列表中的另一个工会成员'union_member'初始化了https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-3-c4608
// 4619 - #pragma warning:没有警告数字'number' https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-3-c4619
// 4643 - c++标准不允许在命名空间std中正向声明` identifier `。https://docs.microsoft.com/en-us/cpp/cpp-conformance-improvements-2017
// 4647 -行为改变:__is_pod(type)在以前的版本中有不同的值https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4600-through-c4799
// 4651 -“定义”指定为预编译头，但不用于当前编译https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4651
// 4668 - ` symbol `没有被定义为预处理器宏，取而代之的是` 0 `来表示` directives ` https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4668
// 4692 - 'function':非私有成员的签名包含程序集私有本机类型'native_type' https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4692

// 4701 -使用了可能未初始化的局部变量'name' https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4701
// 4730 - 'main':混合使用_m64和浮点表达式可能导致错误代码https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4730
// 4738 -存储32位浮点数会导致内存占用，可能会损失性能https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-3-c4738
// 4767 -节名'%s'大于8个字符，并且会被链接器截断https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4600-through-c4799
// 4770 -部分验证的enum 'name'用作索引https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4600-through-c4799
// 4774 - 'string':参数数字中期望的格式字符串不是字符串字面量https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4600-through-c4799

// 4819 -文件包含了一个无法在当前代码页(数字)中表示的字符。以Unicode格式保存文件，防止数据丢失。https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4819
// 4820 - 'bytes'在构造'member_name'之后添加的字节数https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4820
// 4826 -从'type1'到'type2'的转换是符号扩展的。这可能会导致意外的运行时行为。https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4800-through-c4999
// 4828 -文件包含一个从offset开始的字符…这在当前的源字符集(codepage…)中是非法的。https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4800-through-c4999
// 4837 -检测到trigraph: '??字符'被'字符' https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4800-through-c4999
// 4868 - file(line_number) `编译器可能不会强制在大括号初始化列表中执行从左到右的求值顺序https://msdn.microsoft.com/en-us/library/mt656772.aspx

// 4962 - 'function':禁用基于配置文件的优化，因为优化导致配置文件数据不一致https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-c4962
// 4986 - 'function':异常规范与之前的声明不匹配https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-c4986
// 4987 -使用了非标准扩展:'throw(…)' https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4800-through-c4999
// 4988 - ` variable `:声明在类/函数作用域之外的变量https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4800-through-c4999
// 4996 -编译器遇到了一个废弃的声明。https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-3-c4996

// 5045 -编译器将插入Spectre缓解内存负载，如果/Qspectre开关指定https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/c5045

//
// 禁用警告
//

#pragma warning(disable : 4063) // case 'val'不是enum 'E'的switch的有效值

// @todo HoloLens:禁用，因为DbgHelp.h中有一些匿名typedefs(在Visual Studio 2015中不允许)。也许我们应该把标题包起来。
#pragma warning(disable : 4091) // 'keyword':当没有声明变量时，'type'左边的` keyword `会被忽略https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4091

// 禁用不需要的vc++四级警告。
#pragma warning(disable : 4100) // 'identifier':未引用的形式参数https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4100
#pragma warning(disable : 4121) // 'symbol':成员的对齐对包装敏感https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4121
#pragma warning(disable : 4127) // 条件表达式是常量https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4127
#pragma warning(disable : 4180) // 限定符应用于函数类型没有意义;忽略了 										 https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4180
#pragma warning(disable : 4189) // ` identifier `:局部变量被初始化但没有被引用https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4000-through-c4199

#pragma warning(disable : 4200) // 结构末尾为零长度的数组项，vc专用扩展https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-levels-2-and-4-c4200
#pragma warning(disable : 4201) // 使用的非标准扩展:nameless struct/union https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4201
#pragma warning(disable : 4217) // 'operator':成员模板函数不能用于复制赋值或复制构造//没有文档
#pragma warning(disable : 4245) // 'initializing':从'type'到'type'的转换，有符号/无符号不匹配https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4245
#pragma warning(disable : 4251) // ` type `需要dll接口才能被` type `客户端使用https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4251
#pragma warning(disable : 4267) // 'var':从'size_t'转换为'type'，可能丢失数据https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-3-c4267
#pragma warning(disable : 4275) // 非dll接口classkey 'identifier'用作dll接口classkey 'identifier'的基础https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275
#pragma warning(disable : 4291) // typedef-name " used as synonym for class-name " https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4291

#pragma warning(disable : 4307) // ":整型常量溢出https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4307
#pragma warning(disable : 4315) // 'classname': '这个成员'member'的指针可能没有像构造函数预期的那样对齐'alignment' https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4200-through-c4399
#pragma warning(disable : 4316) // ` identifier `:分配在堆上的对象可能没有对齐` alignment ` https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4200-through-c4399
#pragma warning(disable : 4324) // 结构体由于__declspec(align())被填充https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4324
#pragma warning(disable : 4347) // 行为改变:调用了`函数模板`而不是`函数https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4200-through-c4399
#pragma warning(disable : 4351) // 新的行为:数组'array'的元素将被默认初始化https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4200-through-c4399
#pragma warning(disable : 4355) // 在基础初始化列表中使用https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-c4355
#pragma warning(disable : 4366) // 一元运算符` operator `的结果可能是非对齐的https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4366
#pragma warning(disable : 4373) // '%$S':虚函数覆盖'%$pS'，以前版本的编译器不会覆盖当参数仅由const/volatile限定符不同https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-3-c4373
#pragma warning(disable : 4389) // 有符号/无符号不匹配https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-c4355

#pragma warning(disable : 4464) // 相对包含路径包含'..'																 https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/c4464
#pragma warning(disable : 4482) // 非标准扩展used: enum 'enumeration'用于限定名https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4400-through-c4599

#pragma warning(disable : 4505) // 'function':未引用的本地函数已被删除https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4505
#pragma warning(disable : 4511) // 'class':无法生成复制构造函数https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-3-c4511
#pragma warning(disable : 4512) // 'class':无法生成赋值运算符https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4512
#pragma warning(disable : 4514) // 'function':未引用的内联函数已被删除https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4514

#pragma warning(disable : 4592) // ` function `: ` constexpr `调用求值失败;函数将在运行时被调用https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4400-through-c4599
#pragma warning(disable : 4599) // 'flag path':命令行参数number number与预编译头不匹配https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4400-through-c4599

#pragma warning(disable : 4605) // '/Dmacro'在当前命令行中指定，但在构建预编译头文件时未指定https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4600-through-c4799
#pragma warning(disable : 4623) // ` derived class `:默认构造函数被隐式定义为deleted，因为基类的默认构造函数不可访问或被删除https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4623
#pragma warning(disable : 4625) // 'derived class':复制构造函数被隐式定义为deleted，因为基类复制构造函数不可访问或被删除https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4625
#pragma warning(disable : 4626) // ` derived class `:赋值运算符被隐式定义为deleted，因为基类赋值运算符不可访问或被删除https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4626
#pragma warning(disable : 4640) // 'instance':本地静态对象的构造不是线程安全的https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-3-c4640
#pragma warning(disable : 4699) // 创建预编译头//没有文档

#pragma warning(disable : 4702) // 不可访问的代码https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4702
#pragma warning(disable : 4710) // 'function':函数未内联https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4710
#pragma warning(disable : 4711) // 自动内联的函数https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4711
#pragma warning(disable : 4714) // 函数` function `标记为__forceinline而不是内联https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4714
#pragma warning(disable : 4748) // /GS无法保护参数和局部变量免受局部缓冲区溢出的影响，因为在function中禁用了优化//没有文档
#pragma warning(disable : 4768) // 忽略链接规范之前的__declspec属性https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4600-through-c4799
// 注意:如果没有内联，_mm_cvtpu8_ps将错误地生成它
#pragma warning(disable : 4799) // 警告:函数'ident'没有EMMS指令https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4799

// 注意:https://answers.unrealengine.com/questions/701635/warning-c4828.html
#pragma warning(disable : 4828) // 文件中包含一个从offset开始的字符…这在当前的源字符集(codepage…)中是非法的。//没有文档
#pragma warning(disable : 4868) // ` file(line_number) `编译器可能不会强制在花括号初始化列表中执行从左到右的求值顺序https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-c4868

// 注意:ocid.h破坏了这一点
#pragma warning(disable : 4917) // 'declarator': GUID只能与类、接口或命名空间相关联https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4917

//
// 我们可以启用的所有/Wall警告
// @todo: https://docs.microsoft.com/en-us/cpp/preprocessor/compiler-warnings-that-are-off-by-default
// 注意:目前这只是覆盖上面的错误版本，删除这些将导致它们成为错误!
//

#pragma warning(disable : 4191) // ` operator/operation `:从` type_of_expression `到` type_required `的不安全转换https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4000-through-c4199

#pragma warning(disable : 4255) // 'function':没有给出函数原型:将'()'转换为'(void)' https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4255
#pragma warning(disable : 4263) // 'function':成员函数不覆盖任何基类虚成员函数https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4263
#pragma warning(disable : 4264) // ` virtual_function `:基类` class `中的虚成员函数没有可用的重载;功能隐藏https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4264
#pragma warning(3 : 4265)       // 'class':类有虚函数，但析构函数不是虚函数https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-3-c4265
#pragma warning(disable : 4287) // ` operator `:无符号/负常量不匹配https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4264
#pragma warning(disable : 4289) // 非标准扩展used: 'var':在for循环中声明的循环控制变量在for循环作用域之外使用https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4289

// #pragma warning(disable: 4339) // 'type':在CLR元数据中检测到使用未定义类型——使用此类型可能导致运行时异常
#pragma warning(disable : 4345) // 行为改变:使用form()的初始化方法构造的POD对象将被default-initialized

#pragma warning(disable : 4514) // 移除未引用的内联/局部函数
#pragma warning(disable : 4529) // 'member_name':创建成员指针需要显式使用address-of操作符('&')和限定名
#pragma warning(disable : 4536) // 'type name': type-name超过元数据的'limit'字符限制https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4536
#pragma warning(disable : 4545) // 逗号前的表达式求值为缺少参数列表的函数https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4545
#pragma warning(disable : 4546) // 函数调用前逗号缺少参数列表https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4546
#pragma warning(disable : 4557) // ` __assume `包含effect ` effect ` https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-3-c4557
#pragma warning(disable : 4577) // ` noexcept `没有指定异常处理模式;不保证在异常情况下终止。指定/ EHsc

#pragma warning(disable : 4628) // 使用-Ze时不支持有向图字符序列` digraph `没有被解释为` char `的替代标记https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4289
#pragma warning(disable : 4682) // 'parameter':没有指定方向参数属性，默认为[in] https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4682
#pragma warning(disable : 4686) // 'user-defined type':行为可能发生的变化，UDT返回调用约定的变化https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-3-c4686

#pragma warning(disable : 4710) // 'function': function not inline /给定函数被选择用于内联扩展，但编译器没有执行内联。
#pragma warning(disable : 4746) // 对` <expression> `的volatile访问受/volatile限制https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-c4746?view=msvc-170
#pragma warning(disable : 4786) // 'identifier':在调试信息中，identifier被截断为'number'字符//没有文档
#pragma warning(disable : 4793) // 'function':函数被编译为本地代码:'reason' https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-and-3-c4793

#pragma warning(disable : 4905) // 宽字符串字面量转换为'LPSTR' https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4905
#pragma warning(disable : 4906) // 将字符串字面量转换为'LPWSTR' https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4906
#pragma warning(disable : 4928) // 非法复制初始化;已经隐式地应用了多个用户定义转换https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4928
#pragma warning(disable : 4931) // 我们假设类型库是为数字位指针构建的https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4931
#pragma warning(disable : 4946) // 在相关类之间使用reinterpret_cast: 'class1'和'class2' https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4946
#pragma warning(disable : 5038) // 数据成员'A::y'将在数据成员'A::x' https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/c5038之后初始化
#pragma warning(disable : 4984) // 'if constexpr'是c++ 17语言扩展

// #pragma warning(disable:4996)//弃用:通过命令行控制

// 可以不时打开和关闭的有趣元素
// #pragma warning(disable: 4266) // ": base中的虚成员函数没有可用的覆盖";函数被隐藏
// #pragma warning(disable: 4296) // ` operator `:表达式总是true / false
// #pragma warning(disable: 4820) // 'bytes'在成员'member'之后添加字节填充
// 混合使用MMX和SSE的内部函数也会导致这个警告，即使操作正确
// #pragma warning(disable: 4730) //混合_m64和浮点表达式可能导致错误代码

// 确保字符是签名过的
#ifdef _CHAR_UNSIGNED
#error "Bad vc++ option: Characters must be signed" //lint !e309 suppress，因为lint程序没有定义这个参数
#endif
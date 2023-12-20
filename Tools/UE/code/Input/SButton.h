// C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\Slate\Public\Widgets\Input\SButton.h

// Slate的按钮是可点击的部件，可以包含任意部件作为其Content()。
class SLATE_API SButton:public SBorder
{
	SLATE_DECLARE_WIDGET(SButton, SBorder)

#if WITH_ACCESSIBILITY
	// 允许无障碍按钮"点击"此按钮
	friend class FSlateAccessibleButton;
#endif
public:
	SLATE_BEGIN_ARGS(SButton)
		: _Content(), _ButtonStyle(&FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("Button")), _TextStyle(&FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("ButtonText")), _HAlign(HAlign_Fill), _VAlign(VAlign_Fill), _ContentPadding(FMargin(4.0, 2.0)), _Text(), _ClickMethod(EButtonClickMethod::DownAndUp), _TouchMethod(EButtonTouchMethod::DownAndUp), _PressMethod(EButtonPressMethod::DownAndUp), _DesiredSizeScale(FVector2D(1, 1)), _ContentScale(FVector2D(1, 1)), _ButtonColorAndOpacity(FLinearColor::White), _ForegroundColor(FSlateColor::UseStyle()), _IsFocusable(true)
		{
		}
		// 按钮内容的位置(可选)
		SLATE_DEFAULT_SLOT(FArguments, Content)

		// 按钮的视觉样式
		SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle)

		// 按钮的文本样式
		SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextStyle)

		// 水平对齐
		SLATE_ARGUMENT(EHorizontalAlignment, HAlign)

		// 垂直对齐
		SLATE_ARGUMENT(vertical alignment, VAlign)

		// 按钮边框与内容之间的间距。
		SLATE_ATTRIBUTE(FMargin, ContentPadding)

		// 如果没有指定自定义内容，则该按钮显示的文本
		SLATE_ATTRIBUTE(FText, Text)

		// 当按钮被点击时调用
		SLATE_EVENT(FOnClicked, OnClicked)

		// 按下按钮时调用
		SLATE_EVENT(FSimpleDelegate, OnPressed)

		// 在按钮释放时调用
		SLATE_EVENT(FSimpleDelegate, OnReleased)

		// 在浮于按钮上方时调用
		SLATE_EVENT(FSimpleDelegate, OnHovered)

		// 在离开按钮上方时调用
		SLATE_EVENT(FSimpleDelegate, OnUnhovered)

		// 设置判断按钮是否被点击的规则。这是一个高级设置，通常应该保留为默认设置。
		SLATE_ARGUMENT(EButtonClickMethod:Type, ClickMethod)

		// 触摸事件如何点击按钮?
		SLATE_ARGUMENT(EButtonTouchMethod:Type, TouchMethod)

		// 如何用键盘/控制器按钮事件点击按钮?
		SLATE_ARGUMENT(EButtonPressMethod:Type, PressMethod)

		//
		SLATE_ATTRIBUTE(FVector2D, DesiredSizeScale)

		//
		SLATE_ATTRIBUTE(FVector2D, ContentScale)

		//
		SLATE_ATTRIBUTE(FSlateColor, ButtonColorAndOpacity)

		//
		SLATE_ATTRIBUTE(FSlateColor, ForegroundColor)

		// 有时一个按钮应该只能被鼠标点击，而不能被键盘聚焦。
		SLATE_ARGUMENT(bool IsFocusable)

		// 按下按钮时播放的声音
		PressedSoundOverride SLATE_ARGUMENT(TOptional<FSlateSound>)

		// 按钮悬停时播放的声音
		HoveredSoundOverride SLATE_ARGUMENT(TOptional<FSlateSound>)

		// 我们应该使用哪种文本整形方法?(未设置为使用GetDefaultTextShapingMethod返回的默认值)
		TextShapingMethod SLATE_ARGUMENT(TOptional<ETextShapingMethod>)

		// 我们应该使用哪个文本流方向?(未设置为使用GetDefaultTextFlowDirection返回的默认值)
		TextFlowDirection SLATE_ARGUMENT(TOptional<ETextFlowDirection>)

	SLATE_END_ARGS()

protected: SButton();

public:
	// 返回一个表示按钮边框的图像
	UE_DEPRECATED(5.0, "GetBorder is deprecated. Use SetBorderImage or GetBorderImage")
		virtual const FSlateBrush* GetBorder() const
	{
		return GetBorderImage();
	}

	// @返回这个部件设置的前景色;如果widget没有设置前景色，则取消设置选项
	virtual FSlateColor GetForegroundColor() const final
	{
		return Super::GetForegroundColor();
	}

	// @返回当前部件或其任何祖先部件被禁用时设置的前景色;如果小部件没有设置前景色，取消设置选项
	virtual FSlateColor GetDisabledForegroundColor() const final;

	// 如果当前有人按下该按钮，返回true
	// 按下时返回true，否则返回false
	//@note IsPressed曾经是虚拟的。如果需要覆盖默认行为，可以使用setappearance来指定属性。
	bool IsPressed() const
	{
		return bIsPressed || AppearPressedAttribute.Get();
	}

	// 构建这个widget
	// param inargs此部件的声明数据
	void Construct(const FArguments& InArgs);

	// 参见ContentPadding属性
	SetContentPadding(TAttribute<FMargin> InContentPadding);

	// 参见HoveredSound属性
	SetHoveredSound(可选<FSlateSound> InHoveredSound);

	// 参见PressedSound属性
	void SetPressedSound(选项<FSlateSound> InPressedSound);

	// 查看OnClicked事件
	void SetOnClicked(FOnClicked InOnClicked);

	// 设置悬停事件
	void setonhover(FSimpleDelegate inonhover);

	// 设置未悬停事件
	void setonunhover(FSimpleDelegate inonunhover);

	// 参见ButtonStyle属性
	SetButtonStyle(const FButtonStyle* ButtonStyle);

	void SetClickMethod(EButtonClickMethod::Type InClickMethod);
	void SetTouchMethod(EButtonTouchMethod::Type InTouchMethod);
	void SetPressMethod(EButtonPressMethod::Type InPressMethod);

#if !UE_BUILD_SHIPPING
	void SimulateClick();
#endif // !UE_BUILD_SHIPPING

public:
	//~ SWidget overrides
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	virtual bool SupportsKeyboardFocus() const override;
	virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;
	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;
	virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;
	virtual bool IsInteractable() const override;
#if WITH_ACCESSIBILITY
	virtual TSharedRef<FSlateAccessibleWidget> CreateAccessibleWidget() override;
#endif
private:
	virtual FVector2D ComputeDesiredSize(float) const override;
	//~ SWidget

protected:
	// 按下按钮
	virtual void Press();

	// 释放按钮
	virtual void Release();

	// 执行"OnClicked"委托，并获取回复
	FReply ExecuteOnClick();

	// @return组合了用户指定的外边距和按钮内部的外边距。
	FMargin GetCombinedPadding();

	// @return True，如果要显示禁用的特效
	GetShowDisabledEffect();

	// 将其他输入单击方法转换为常规单击方法的实用函数
	GetClickMethodFromInputType(const FPointerEvent& MouseEvent) const;

	// 实用函数，用于确定传入的鼠标事件是用于精确点击还是点击
	const FPointerEvent& MouseEvent;

	// 播放按下的声音
	void PlayPressedSound() const;

	// 播放悬停的声音
	void PlayHoverSound() const;

	// 设置该按钮是否可以聚焦
	void SetIsFocusable(bool bInIsFocusable)
	{
		bIsFocusable = bInIsFocusable;
	}

	void ExecuteHoverStateChanged(bool bPlaySound);

protected:
	// @返回BorderForegroundColor属性。
	TSlateAttributeRef<FSlateColor> GetBorderForegroundColorAttribute() const { return TSlateAttributeRef<FSlateColor>(SharedThis(this)， BorderForegroundColorAttribute); }

	// @返回ContentPadding属性。
	TSlateAttributeRef<FMargin> GetContentPaddingAttribute() const { return TSlateAttributeRef<FMargin>(SharedThis(this)， ContentPaddingAttribute); }

	// 设置显示的外观
	void SetAppearPressed(TAttribute<bool> InValue)
	{
		AppearPressedAttribute.Assign(*this, MoveTemp(InValue));
	}

	// @return appearance属性。
	TSlateAttributeRef<bool> GetAppearPressedAttribute() const { return TSlateAttributeRef<bool>(SharedThis(this), AppearPressedAttribute); }

private:
	void UpdatePressStateChanged();

	void UpdatePadding();
	void UpdateShowDisabledEffect();
	void UpdateBorderImage();
	void UpdateForegroundColor();
	void UpdateDisabledForegroundColor();

protected:
#if WITH_EDITORONLY_DATA
	UE_DEPRECATED(5.0, "直接访问ContentPadding现在已弃用。使用setter或getter。")
		TSlateDeprecatedTAttribute<FMargin> ContentPadding;
	// 刷出代表按钮的资源
	UE_DEPRECATED(5.0, “NormalImage现在已弃用。使用ButtonStyle。")
		const FSlateBrush * NormalImage;
	//当按钮悬停时，画笔资源代表按钮
	UE_DEPRECATED(5.0, “HoverImage现在已弃用。使用ButtonStyle。")
		const FSlateBrush * HoverImage;
	//当按钮被按下时，画笔资源表示按钮
	UE_DEPRECATED(5.0, " pre - sediment现在已被弃用。使用ButtonStyle。")
		const FSlateBrush* 预沉积;
	//当按钮被禁用时，刷出代表按钮的资源
	UE_DEPRECATED(5.0, "DisabledImage现在已弃用。使用ButtonStyle。")
		const FSlateBrush* disableimage;
	//填充按钮边框
	UE_DEPRECATED(5.0, "BorderPadding现在已弃用。使用ButtonStyle。")
		FMargin BorderPadding;
	//填充当按钮被按下时的边框
	UE_DEPRECATED(5.0, "PressedBorderPadding现在已弃用。使用ButtonStyle。")
		FMargin PressedBorderPadding;
#endif

private:

	//按下按钮在屏幕空间中的位置
	FVector2D PressedScreenSpacePosition;

	//按钮的样式资源
	const FButtonStyle* Style;

	//当按钮被点击时执行的委托
	FOnClicked onclick;

	//当按钮被按下时执行的委托
	FSimpleDelegate OnPressed;

	//当按钮释放时执行的委托
	FSimpleDelegate OnReleased;

	//当按钮悬停时执行的委托
	FSimpleDelegate OnHovered;

	//当按钮退出悬停状态时执行的委托
	FSimpleDelegate OnUnhovered;

	//当按钮悬停时播放的声音
	FSlateSound HoveredSound;

	//按下按钮时播放的声音
	FSlateSound PressedSound;

	//设置单击是在mouse down、mouse up还是同时需要mouse down和mouse up
	TEnumAsByte<EButtonClickMethod:Type>ClickMethod;

	//如何通过触摸事件点击按钮?
	TEnumAsByte<EButtonTouchMethod:Type>TouchMethod;

	//如何通过键盘/控制器按钮事件来点击按钮?
	TEnumAsByte<EButtonPressMethod:Type>PressMethod;

	//这个按钮可以聚焦吗?
	uint8 bIsFocusable:1;

	//如果这个按钮当前处于按下状态，返回True
	uint8 bIsPressed:1;

private:
	//可选的前景颜色，将被此部件的所有内容继承
	TSlateAttribute<FSlateColor>BorderForegroundColorAttribute;
	//用户指定的Padding;它将与按钮的内部填充相结合。
	TSlateAttribute<FMargin>ContentPaddingAttribute;
	//可选的前景颜色，将被此部件的所有内容继承
	TSlateAttribute<bool>AppearPressedAttribute;
};

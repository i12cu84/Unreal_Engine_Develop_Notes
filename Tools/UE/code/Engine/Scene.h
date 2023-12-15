// C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\Engine\Classes\Engine\Scene.h

//
struct FColorGradePerRangeSettings{};

//
struct FColorGradingSettings{};

//
struct FFilmStockSettings{};

//
struct FGaussianSumBloomSettings{};

//
struct FConvolutionBloomSettings{};

//
struct FLensBloomSettings{};

//
struct FLensImperfectionSettings{};

//
struct FLensSettings{};

//
struct FCameraExposureSettings{};

//
struct FWeightedBlendable{};

//
struct FWeightedBlendables{};

//
struct FPostProcessSettingsDebugInfo{};

/**能够使用struct PostProcessSettings。*/
// 每个属性由一个布尔值组成，用于启用它(默认为关闭)，
// 变量声明和默认值
// 注释应该包含含义和可用范围
struct FPostProcessSettings
{
};

#if WITH_EDITORONLY_DATA
//
template<>
struct TStructOpsTypeTraits<FPostProcessSettings>
	: public TStructOpsTypeTraitsBase2<FPostProcessSettings>
{
};
#endif

//
class UScene : public UObject{};
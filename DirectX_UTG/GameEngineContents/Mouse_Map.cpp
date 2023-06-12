#include "PrecompileHeader.h"
#include "Mouse_Map.h"

#include "HBSCSpriteRenderer.h"

Mouse_Map::Mouse_Map() 
{
}

Mouse_Map::~Mouse_Map() 
{
}

void Mouse_Map::BrightnessControl(std::shared_ptr<class HBSCSpriteRenderer> _Object, float _saturation, float _brightness, float _contrast)
{
	float4 OriginColor = _Object->ColorOptionValue.MulColor;
	float4 ControlColor = float4::Zero;

	ControlColor.r = OriginColor.r;
	ControlColor.g = _saturation;
	ControlColor.b = _brightness;
	ControlColor.a = _contrast;

	_Object->HBSCColorValue.HBSCColor = ControlColor;
}

void Mouse_Map::Start()
{
	if (nullptr == GameEngineTexture::Find("Mouse_BackGround_Phase_1.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("3_Werner_Werman");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_BackGround_Phase_1.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_House_BackGround.png").GetFullPath());
	}

	if (nullptr == WallBGRenderPtr)
	{
		WallBGRenderPtr = CreateComponent<HBSCSpriteRenderer>();
		WallBGRenderPtr->SetScaleToTexture("Mouse_BackGround_Phase_1.png");
		//WallBGRenderPtr->GetTransform()->AddLocalPosition({ 0, -10 });
	}

	if (nullptr == HouseBGRenderPtr)
	{
		HouseBGRenderPtr = CreateComponent<HBSCSpriteRenderer>();
		HouseBGRenderPtr->SetTexture("Mouse_House_BackGround.png");
		HouseBGRenderPtr->GetTransform()->SetLocalScale({ 1400, 719 });
		HouseBGRenderPtr->GetTransform()->AddLocalPosition({ 0, 100, 10 });
	}

	BrightnessControl(WallBGRenderPtr, 0.6f, 0.6f, 0.6f);
	BrightnessControl(HouseBGRenderPtr, 0.6f, 0.6f, 0.6f);
}

void Mouse_Map::Update(float _DeltaTime)
{

}
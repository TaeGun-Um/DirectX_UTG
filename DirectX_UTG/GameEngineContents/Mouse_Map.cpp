#include "PrecompileHeader.h"
#include "Mouse_Map.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Mouse_Map::Mouse_Map() 
{
}

Mouse_Map::~Mouse_Map() 
{
}

void Mouse_Map::HBSCControl(std::shared_ptr<class GameEngineSpriteRenderer> _Object, float _saturation, float _brightness, float _contrast)
{
	float4 OriginColor = _Object->ColorOptionValue.MulColor;
	float4 ControlColor = float4::Zero;

	ControlColor.r = OriginColor.r;
	ControlColor.g = _saturation;
	ControlColor.b = _brightness;
	ControlColor.a = _contrast;

	_Object->ColorOptionValue.HBSCColor = ControlColor;
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
		WallBGRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		WallBGRenderPtr->SetScaleToTexture("Mouse_BackGround_Phase_1.png");
		//WallBGRenderPtr->GetTransform()->AddLocalPosition({ 0, -10 });
	}

	if (nullptr == HouseBGRenderPtr)
	{
		HouseBGRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		HouseBGRenderPtr->SetTexture("Mouse_House_BackGround.png");
		HouseBGRenderPtr->GetTransform()->SetLocalScale({ 1400, 719 });
		HouseBGRenderPtr->GetTransform()->AddLocalPosition({ 0, 100, 10 });
	}

	HBSCControl(WallBGRenderPtr, 0.47f, 0.59f, 0.5f);
	HBSCControl(HouseBGRenderPtr, 0.47f, 0.59f, 0.5f);
}

void Mouse_Map::Update(float _DeltaTime)
{

}
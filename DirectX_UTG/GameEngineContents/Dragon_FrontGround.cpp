#include "PrecompileHeader.h"
#include "Dragon_FrontGround.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Dragon_FrontGround::Dragon_FrontGround() 
{
}

Dragon_FrontGround::~Dragon_FrontGround() 
{
}

void Dragon_FrontGround::HBSCControl(std::shared_ptr<class GameEngineSpriteRenderer> _Object, float _saturation, float _brightness, float _contrast)
{
	float4 OriginColor = _Object->ColorOptionValue.MulColor;
	float4 ControlColor = float4::Zero;

	ControlColor.r = OriginColor.r;
	ControlColor.g = _saturation;
	ControlColor.b = _brightness;
	ControlColor.a = _contrast;

	_Object->ColorOptionValue.HBSCColor = ControlColor;
}

void Dragon_FrontGround::Start()
{
	if (nullptr == GameEngineTexture::Find("Dragon_Foreground_Clouds_001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("FrontClouds");
		NewDir.Move("FrontWhite");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Dragon_Foreground_Clouds_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Dragon_Foreground_Clouds_002.png").GetFullPath());
	}

	if (nullptr == FrontCloudRenderPtr_One)
	{
		FrontCloudRenderPtr_One = CreateComponent<GameEngineSpriteRenderer>();
		FrontCloudRenderPtr_One->SetScaleToTexture("Dragon_Foreground_Clouds_002.png");
		FrontCloudRenderPtr_One->GetTransform()->SetLocalPosition({ 0, -270 });
	}

	if (nullptr == FrontCloudRenderPtr_Two)
	{
		FrontCloudRenderPtr_Two = CreateComponent<GameEngineSpriteRenderer>();
		FrontCloudRenderPtr_Two->SetScaleToTexture("Dragon_Foreground_Clouds_002.png");
		FrontCloudRenderPtr_Two->GetTransform()->SetLocalPosition({ 0, -270 });
	}

	if (nullptr == CloudRenderPtr_One)
	{
		CloudRenderPtr_One = CreateComponent<GameEngineSpriteRenderer>();
		CloudRenderPtr_One->SetScaleToTexture("Dragon_Foreground_Clouds_001.png");
		CloudRenderPtr_One->GetTransform()->SetLocalPosition({ 0, -320 });
	}

	if (nullptr == CloudRenderPtr_Two)
	{
		CloudRenderPtr_Two = CreateComponent<GameEngineSpriteRenderer>();
		CloudRenderPtr_Two->SetScaleToTexture("Dragon_Foreground_Clouds_001.png");
		CloudRenderPtr_Two->GetTransform()->SetLocalPosition({ 0, -320 });
	}

	{
		Low_FrontCloudScale = FrontCloudRenderPtr_One->GetTransform()->GetLocalScale();
		Low_FrontCloudStartPosition_One = FrontCloudRenderPtr_One->GetTransform()->GetLocalPosition();
		Low_FrontCloudLerpPosition_One = Low_FrontCloudStartPosition_One - float4{ Low_FrontCloudScale.x, 0 };

		FrontCloudRenderPtr_Two->GetTransform()->SetLocalPosition({ Low_FrontCloudScale.x, -270 });
		Low_FrontCloudStartPosition_Two = FrontCloudRenderPtr_Two->GetTransform()->GetLocalPosition();
		Low_FrontCloudLerpPosition_Two = Low_FrontCloudStartPosition_Two - float4{ Low_FrontCloudScale.x, 0 };
	}

	{
		FrontCloudScale = CloudRenderPtr_One->GetTransform()->GetLocalScale();
		FrontCloudStartPosition_One = CloudRenderPtr_One->GetTransform()->GetLocalPosition();
		FrontCloudLerpPosition_One = FrontCloudStartPosition_One - float4{ FrontCloudScale.x, 0 };

		FrontCloudRenderPtr_Two->GetTransform()->SetLocalPosition({ FrontCloudScale.x, -320 });
		FrontCloudStartPosition_Two = FrontCloudRenderPtr_Two->GetTransform()->GetLocalPosition();
		FrontCloudLerpPosition_Two = FrontCloudStartPosition_Two - float4{ FrontCloudScale.x, 0 };
	}
}

void Dragon_FrontGround::Update(float _DeltaTime)
{
	FrontCloudLerp(_DeltaTime);
	CloudLerp(_DeltaTime);
}

void Dragon_FrontGround::FrontCloudLerp(float _DeltaTime)
{
	Low_FrontCloudLerpTime += _DeltaTime;

	float4 CurPos_One = FrontCloudRenderPtr_One->GetTransform()->GetLocalPosition();
	float4 CurPos_Two = FrontCloudRenderPtr_Two->GetTransform()->GetLocalPosition();

	float4 NewPos_One = float4::LerpClamp(Low_FrontCloudStartPosition_One, Low_FrontCloudLerpPosition_One, Low_FrontCloudLerpTime / 25);
	float4 NewPos_Two = float4::LerpClamp(Low_FrontCloudStartPosition_Two, Low_FrontCloudLerpPosition_Two, Low_FrontCloudLerpTime / 25);

	FrontCloudRenderPtr_One->GetTransform()->SetLocalPosition(NewPos_One);
	FrontCloudRenderPtr_Two->GetTransform()->SetLocalPosition(NewPos_Two);

	if (CurPos_One.x <= Low_FrontCloudLerpPosition_One.x)
	{
		FrontCloudRenderPtr_One->GetTransform()->SetLocalPosition(Low_FrontCloudStartPosition_One);
		FrontCloudRenderPtr_Two->GetTransform()->SetLocalPosition(Low_FrontCloudStartPosition_Two);
		Low_FrontCloudLerpTime = 0.0f;
	}
}

void Dragon_FrontGround::CloudLerp(float _DeltaTime)
{
	FrontCloudLerpTime += _DeltaTime;

	float4 CurPos_One = CloudRenderPtr_One->GetTransform()->GetLocalPosition();
	float4 CurPos_Two = CloudRenderPtr_Two->GetTransform()->GetLocalPosition();

	float4 NewPos_One = float4::LerpClamp(FrontCloudStartPosition_One, FrontCloudLerpPosition_One, FrontCloudLerpTime / 10);
	float4 NewPos_Two = float4::LerpClamp(FrontCloudStartPosition_Two, FrontCloudLerpPosition_Two, FrontCloudLerpTime / 10);

	CloudRenderPtr_One->GetTransform()->SetLocalPosition(NewPos_One);
	CloudRenderPtr_Two->GetTransform()->SetLocalPosition(NewPos_Two);

	if (CurPos_One.x <= FrontCloudLerpPosition_One.x)
	{
		CloudRenderPtr_One->GetTransform()->SetLocalPosition(FrontCloudStartPosition_One);
		CloudRenderPtr_Two->GetTransform()->SetLocalPosition(FrontCloudStartPosition_Two);
		FrontCloudLerpTime = 0.0f;
	}
}
#include "PrecompileHeader.h"
#include "Dragon_BackGround.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Dragon_BackGround* Dragon_BackGround::BackGroundPtr = nullptr;

Dragon_BackGround::Dragon_BackGround() 
{
}

Dragon_BackGround::~Dragon_BackGround() 
{
}

void Dragon_BackGround::HBSCControl(std::shared_ptr<class GameEngineSpriteRenderer> _Object, float _saturation, float _brightness, float _contrast)
{
	float4 OriginColor = _Object->ColorOptionValue.MulColor;
	float4 ControlColor = float4::Zero;

	ControlColor.r = OriginColor.r;
	ControlColor.g = _saturation;
	ControlColor.b = _brightness;
	ControlColor.a = _contrast;

	_Object->ColorOptionValue.HBSCColor = ControlColor;
}

void Dragon_BackGround::Start()
{
	BackGroundPtr = this;

	if (nullptr == GameEngineTexture::Find("Dragon_Background_Sky_Normal.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Background");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Dragon_Background_Sky_Normal.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Dragon_Background_Clouds1.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("BackClouds");
		NewDir.Move("Cloud_White");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Dragon_Background_Clouds1.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Dragon_Background_Clouds2.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Dragon_Background_Clouds3.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Dragon_Background_Clouds4.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Dragon_Background_Clouds5.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Dragon_Foreground_Clouds_003.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("FrontClouds");
		NewDir.Move("FrontWhite");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Dragon_Foreground_Clouds_003.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Tower_Light"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Tower");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Tower_Light").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Dragon_Ph2_Dash"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_Ph2_Dash").GetFullPath());
	}

	if (nullptr == BackGroundRenderPtr_One)
	{
		BackGroundRenderPtr_One = CreateComponent<GameEngineSpriteRenderer>();
		BackGroundRenderPtr_One->SetScaleToTexture("Dragon_Background_Sky_Normal.png");
	}

	if (nullptr == BackGroundRenderPtr_Two)
	{
		BackGroundRenderPtr_Two = CreateComponent<GameEngineSpriteRenderer>();
		BackGroundRenderPtr_Two->SetScaleToTexture("Dragon_Background_Sky_Normal.png");
	}

	if (nullptr == Middle_BackCloudRenderPtr_One)
	{
		Middle_BackCloudRenderPtr_One = CreateComponent<GameEngineSpriteRenderer>();
		Middle_BackCloudRenderPtr_One->SetScaleToTexture("Dragon_Background_Clouds5.png");
		Middle_BackCloudRenderPtr_One->GetTransform()->SetLocalPosition({ 0, 170 });
	}

	if (nullptr == Middle_BackCloudRenderPtr_Two)
	{
		Middle_BackCloudRenderPtr_Two = CreateComponent<GameEngineSpriteRenderer>();
		Middle_BackCloudRenderPtr_Two->SetScaleToTexture("Dragon_Background_Clouds5.png");
		Middle_BackCloudRenderPtr_Two->GetTransform()->SetLocalPosition({ 0, 170 });
	}

	if (nullptr == Middle_Two_BackCloudRenderPtr_One)
	{
		Middle_Two_BackCloudRenderPtr_One = CreateComponent<GameEngineSpriteRenderer>();
		Middle_Two_BackCloudRenderPtr_One->SetScaleToTexture("Dragon_Background_Clouds4.png");
		Middle_Two_BackCloudRenderPtr_One->GetTransform()->SetLocalPosition({ 0, -70 });
	}

	if (nullptr == Middle_Two_BackCloudRenderPtr_Two)
	{
		Middle_Two_BackCloudRenderPtr_Two = CreateComponent<GameEngineSpriteRenderer>();
		Middle_Two_BackCloudRenderPtr_Two->SetScaleToTexture("Dragon_Background_Clouds4.png");
		Middle_Two_BackCloudRenderPtr_Two->GetTransform()->SetLocalPosition({ 0, -70 });
	}

	if (nullptr == Low_BackCloudRenderPtr_One)
	{
		Low_BackCloudRenderPtr_One = CreateComponent<GameEngineSpriteRenderer>();
		Low_BackCloudRenderPtr_One->SetScaleToTexture("Dragon_Background_Clouds1.png");
		Low_BackCloudRenderPtr_One->GetTransform()->SetLocalPosition({0, -250 });
	}

	if (nullptr == Low_BackCloudRenderPtr_Two)
	{
		Low_BackCloudRenderPtr_Two = CreateComponent<GameEngineSpriteRenderer>();
		Low_BackCloudRenderPtr_Two->SetScaleToTexture("Dragon_Background_Clouds1.png");
		Low_BackCloudRenderPtr_Two->GetTransform()->SetLocalPosition({ 0, -250 });
	}

	if (nullptr == DragonDashRenderPtr)
	{
		DragonDashRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		DragonDashRenderPtr->CreateAnimation({ .AnimationName = "Dragon_Ph2_Dash", .SpriteName = "Dragon_Ph2_Dash", .FrameInter = 0.04f, .Loop = true, .ScaleToTexture = true });

		DragonDashRenderPtr->GetTransform()->SetLocalPosition({ 900, 0 });

		DragonDashRenderPtr->ChangeAnimation("Dragon_Ph2_Dash");
		DragonDashRenderPtr->Off();
	}

	if (nullptr == TowerRenderPtr)
	{
		TowerRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		TowerRenderPtr->CreateAnimation({ .AnimationName = "Tower_Light", .SpriteName = "Tower_Light", .FrameInter = 0.1f, .Loop = true, .ScaleToTexture = true });
		TowerRenderPtr->ChangeAnimation("Tower_Light");
	}

	if (nullptr == Low_FrontCloudRenderPtr_One)
	{
		Low_FrontCloudRenderPtr_One = CreateComponent<GameEngineSpriteRenderer>();
		Low_FrontCloudRenderPtr_One->SetScaleToTexture("Dragon_Foreground_Clouds_003.png");
		Low_FrontCloudRenderPtr_One->GetTransform()->SetLocalPosition({ 0, -290 });
	}

	if (nullptr == Low_FrontCloudRenderPtr_Two)
	{
		Low_FrontCloudRenderPtr_Two = CreateComponent<GameEngineSpriteRenderer>();
		Low_FrontCloudRenderPtr_Two->SetScaleToTexture("Dragon_Foreground_Clouds_003.png");
		Low_FrontCloudRenderPtr_Two->GetTransform()->SetLocalPosition({ 0, -290 });
	}

	{
		BackGroundScale = BackGroundRenderPtr_One->GetTransform()->GetLocalScale();
		StartPosition_One = BackGroundRenderPtr_One->GetTransform()->GetLocalPosition();
		LerpPosition_One = StartPosition_One + float4{ BackGroundScale.x, 0 };

		BackGroundRenderPtr_Two->GetTransform()->SetLocalPosition({ -BackGroundScale.x + 3, 0 });
		StartPosition_Two = BackGroundRenderPtr_Two->GetTransform()->GetLocalPosition();
		LerpPosition_Two = StartPosition_Two + float4{ BackGroundScale.x, 0 };
	}

	{
		Middle_CloudScale = Middle_BackCloudRenderPtr_One->GetTransform()->GetLocalScale();
		Middle_CloudStartPosition_One = Middle_BackCloudRenderPtr_One->GetTransform()->GetLocalPosition();
		Middle_CloudLerpPosition_One = Middle_CloudStartPosition_One + float4{ Middle_CloudScale.x, 0 };

		Middle_BackCloudRenderPtr_Two->GetTransform()->SetLocalPosition({ -Middle_CloudScale.x, 170 });
		Middle_CloudStartPosition_Two = Middle_BackCloudRenderPtr_Two->GetTransform()->GetLocalPosition();
		Middle_CloudLerpPosition_Two = Middle_CloudStartPosition_Two + float4{ Middle_CloudScale.x, 0 };
	}

	{
		Middle_Two_CloudScale = Middle_Two_BackCloudRenderPtr_One->GetTransform()->GetLocalScale();
		Middle_Two_CloudStartPosition_One = Middle_Two_BackCloudRenderPtr_One->GetTransform()->GetLocalPosition();
		Middle_Two_CloudLerpPosition_One = Middle_Two_CloudStartPosition_One + float4{ Middle_Two_CloudScale.x, 0 };

		Middle_Two_BackCloudRenderPtr_Two->GetTransform()->SetLocalPosition({ -Middle_Two_CloudScale.x, -70 });
		Middle_Two_CloudStartPosition_Two = Middle_Two_BackCloudRenderPtr_Two->GetTransform()->GetLocalPosition();
		Middle_Two_CloudLerpPosition_Two = Middle_Two_CloudStartPosition_Two + float4{ Middle_Two_CloudScale.x, 0 };
	}

	{
		Low_CloudScale = Low_BackCloudRenderPtr_One->GetTransform()->GetLocalScale();
		Low_CloudStartPosition_One = Low_BackCloudRenderPtr_One->GetTransform()->GetLocalPosition();
		Low_CloudLerpPosition_One = Low_CloudStartPosition_One + float4{ Low_CloudScale.x, 0 };

		Low_BackCloudRenderPtr_Two->GetTransform()->SetLocalPosition({ -Low_CloudScale.x, -250 });
		Low_CloudStartPosition_Two = Low_BackCloudRenderPtr_Two->GetTransform()->GetLocalPosition();
		Low_CloudLerpPosition_Two = Low_CloudStartPosition_Two + float4{ Low_CloudScale.x, 0 };
	}

	{
		Low_FrontCloudScale = Low_FrontCloudRenderPtr_One->GetTransform()->GetLocalScale();
		Low_FrontCloudStartPosition_One = Low_FrontCloudRenderPtr_One->GetTransform()->GetLocalPosition();
		Low_FrontCloudLerpPosition_One = Low_FrontCloudStartPosition_One - float4{ Low_FrontCloudScale.x, 0 };

		Low_FrontCloudRenderPtr_Two->GetTransform()->SetLocalPosition({ Low_FrontCloudScale.x, -290 });
		Low_FrontCloudStartPosition_Two = Low_FrontCloudRenderPtr_Two->GetTransform()->GetLocalPosition();
		Low_FrontCloudLerpPosition_Two = Low_FrontCloudStartPosition_Two - float4{ Low_FrontCloudScale.x, 0 };
	}
}

void Dragon_BackGround::Update(float _DeltaTime)
{
	BackGroundLerp(_DeltaTime);
	MiddleCloudLerp(_DeltaTime);
	Middle_Two_CloudLerp(_DeltaTime);
	LowCloudLerp(_DeltaTime);
	LowFrontCloudLerp(_DeltaTime);
	DragonDash(_DeltaTime);
}

void Dragon_BackGround::DragonDash(float _DeltaTime)
{
	if (false == IsDragonDash)
	{
		return;
	}

	if (false == IsDashSound)
	{
		IsDashSound = true;
		EffectPlayer = GameEngineSound::Play("dragon_tail_attack.wav");
	}

	float4 CurPos = DragonDashRenderPtr->GetTransform()->GetLocalPosition();

	if (-1200.0f >= CurPos.x)
	{
		IsDragonDash = false;
		IsDragonDashEnd = true;
		DragonDashRenderPtr->Off();
	}

	float MoveDis = 1000.0f * _DeltaTime;

	DragonDashRenderPtr->GetTransform()->AddLocalPosition({ -MoveDis , 0 });
}

void Dragon_BackGround::BackGroundLerp(float _DeltaTime)
{
	BackGroudLerpTime += _DeltaTime;

	float4 CurPos_One = BackGroundRenderPtr_One->GetTransform()->GetLocalPosition();
	float4 CurPos_Two = BackGroundRenderPtr_Two->GetTransform()->GetLocalPosition();

	float4 NewPos_One = float4::LerpClamp(StartPosition_One, LerpPosition_One, BackGroudLerpTime / 25);
	float4 NewPos_Two = float4::LerpClamp(StartPosition_Two, LerpPosition_Two, BackGroudLerpTime / 25);

	BackGroundRenderPtr_One->GetTransform()->SetLocalPosition(NewPos_One);
	BackGroundRenderPtr_Two->GetTransform()->SetLocalPosition(NewPos_Two);

	if (CurPos_One.x >= LerpPosition_One.x)
	{
		BackGroundRenderPtr_One->GetTransform()->SetLocalPosition(StartPosition_One);
		BackGroundRenderPtr_Two->GetTransform()->SetLocalPosition(StartPosition_Two);
		BackGroudLerpTime = 0.0f;
	}
}

void Dragon_BackGround::MiddleCloudLerp(float _DeltaTime)
{
	Middle_CloudLerpTime += _DeltaTime;

	float4 CurPos_One = Middle_BackCloudRenderPtr_One->GetTransform()->GetLocalPosition();
	float4 CurPos_Two = Middle_BackCloudRenderPtr_Two->GetTransform()->GetLocalPosition();

	float4 NewPos_One = float4::LerpClamp(Middle_CloudStartPosition_One, Middle_CloudLerpPosition_One, Middle_CloudLerpTime / 35);
	float4 NewPos_Two = float4::LerpClamp(Middle_CloudStartPosition_Two, Middle_CloudLerpPosition_Two, Middle_CloudLerpTime / 35);

	Middle_BackCloudRenderPtr_One->GetTransform()->SetLocalPosition(NewPos_One);
	Middle_BackCloudRenderPtr_Two->GetTransform()->SetLocalPosition(NewPos_Two);

	if (CurPos_One.x >= Middle_CloudLerpPosition_One.x)
	{
		Middle_BackCloudRenderPtr_One->GetTransform()->SetLocalPosition(Middle_CloudStartPosition_One);
		Middle_BackCloudRenderPtr_Two->GetTransform()->SetLocalPosition(Middle_CloudStartPosition_Two);
		Middle_CloudLerpTime = 0.0f;
	}
}

void Dragon_BackGround::Middle_Two_CloudLerp(float _DeltaTime)
{
	Middle_Two_CloudLerpTime += _DeltaTime;

	float4 CurPos_One = Middle_Two_BackCloudRenderPtr_One->GetTransform()->GetLocalPosition();
	float4 CurPos_Two = Middle_Two_BackCloudRenderPtr_Two->GetTransform()->GetLocalPosition();

	float4 NewPos_One = float4::LerpClamp(Middle_Two_CloudStartPosition_One, Middle_Two_CloudLerpPosition_One, Middle_Two_CloudLerpTime / 40);
	float4 NewPos_Two = float4::LerpClamp(Middle_Two_CloudStartPosition_Two, Middle_Two_CloudLerpPosition_Two, Middle_Two_CloudLerpTime / 40);

	Middle_Two_BackCloudRenderPtr_One->GetTransform()->SetLocalPosition(NewPos_One);
	Middle_Two_BackCloudRenderPtr_Two->GetTransform()->SetLocalPosition(NewPos_Two);

	if (CurPos_One.x >= Middle_Two_CloudLerpPosition_One.x)
	{
		Middle_Two_BackCloudRenderPtr_One->GetTransform()->SetLocalPosition(Middle_Two_CloudStartPosition_One);
		Middle_Two_BackCloudRenderPtr_Two->GetTransform()->SetLocalPosition(Middle_Two_CloudStartPosition_Two);
		Middle_Two_CloudLerpTime = 0.0f;
	}
}

void Dragon_BackGround::LowCloudLerp(float _DeltaTime)
{
	Low_CloudLerpTime += _DeltaTime;

	float4 CurPos_One = Low_BackCloudRenderPtr_One->GetTransform()->GetLocalPosition();
	float4 CurPos_Two = Low_BackCloudRenderPtr_Two->GetTransform()->GetLocalPosition();

	float4 NewPos_One = float4::LerpClamp(Low_CloudStartPosition_One, Low_CloudLerpPosition_One, Low_CloudLerpTime / 45);
	float4 NewPos_Two = float4::LerpClamp(Low_CloudStartPosition_Two, Low_CloudLerpPosition_Two, Low_CloudLerpTime / 45);

	Low_BackCloudRenderPtr_One->GetTransform()->SetLocalPosition(NewPos_One);
	Low_BackCloudRenderPtr_Two->GetTransform()->SetLocalPosition(NewPos_Two);

	if (CurPos_One.x >= Low_CloudLerpPosition_One.x)
	{
		Low_BackCloudRenderPtr_One->GetTransform()->SetLocalPosition(Low_CloudStartPosition_One);
		Low_BackCloudRenderPtr_Two->GetTransform()->SetLocalPosition(Low_CloudStartPosition_Two);
		Low_CloudLerpTime = 0.0f;
	}
}

void Dragon_BackGround::LowFrontCloudLerp(float _DeltaTime)
{
	Low_FrontCloudLerpTime += _DeltaTime;

	float4 CurPos_One = Low_FrontCloudRenderPtr_One->GetTransform()->GetLocalPosition();
	float4 CurPos_Two = Low_FrontCloudRenderPtr_Two->GetTransform()->GetLocalPosition();

	float4 NewPos_One = float4::LerpClamp(Low_FrontCloudStartPosition_One, Low_FrontCloudLerpPosition_One, Low_FrontCloudLerpTime / 45);
	float4 NewPos_Two = float4::LerpClamp(Low_FrontCloudStartPosition_Two, Low_FrontCloudLerpPosition_Two, Low_FrontCloudLerpTime / 45);

	Low_FrontCloudRenderPtr_One->GetTransform()->SetLocalPosition(NewPos_One);
	Low_FrontCloudRenderPtr_Two->GetTransform()->SetLocalPosition(NewPos_Two);

	if (CurPos_One.x <= Low_FrontCloudLerpPosition_One.x)
	{
		Low_FrontCloudRenderPtr_One->GetTransform()->SetLocalPosition(Low_FrontCloudStartPosition_One);
		Low_FrontCloudRenderPtr_Two->GetTransform()->SetLocalPosition(Low_FrontCloudStartPosition_Two);
		Low_FrontCloudLerpTime = 0.0f;
	}
}
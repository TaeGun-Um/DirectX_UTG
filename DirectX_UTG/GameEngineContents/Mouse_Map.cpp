#include "PrecompileHeader.h"
#include "Mouse_Map.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Mouse_BackObject.h"

Mouse_Map* Mouse_Map::MouseMapPtr = nullptr;

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

void Mouse_Map::PlatformSound()
{
	EffectPlayer = GameEngineSound::Play("mouse_phase2_background_shelf_drop.wav");
}

void Mouse_Map::Start()
{
	MouseMapPtr = this;
	
	if (nullptr == GameEngineTexture::Find("Mouse_BackGround_Phase_1.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("3_Werner_Werman");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_BackGround_Phase_1.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_BackGround_Phase_2.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_House_BackGround.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_BackGround_Phase_3B.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Phase2_Platform"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("3_Werner_Werman");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase2_Platform").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase3_WallBrake").GetFullPath());
	}

	if (nullptr == WallBGRenderPtr)
	{
		WallBGRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		WallBGRenderPtr->SetScaleToTexture("Mouse_BackGround_Phase_1.png");
	}

	if (nullptr == Phase2PlatformRenderPtr)
	{
		Phase2PlatformRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		Phase2PlatformRenderPtr->CreateAnimation({ .AnimationName = "Phase2_Platform", .SpriteName = "Phase2_Platform", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		Phase2PlatformRenderPtr->CreateAnimation({ .AnimationName = "Phase3_WallBrake", .SpriteName = "Phase3_WallBrake", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
		Phase2PlatformRenderPtr->ChangeAnimation("Phase2_Platform");
		Phase2PlatformRenderPtr->GetTransform()->SetLocalPosition({ -2, 80 });
		Phase2PlatformRenderPtr->Off();

		Phase2PlatformRenderPtr->SetAnimationStartEvent("Phase2_Platform", 0, std::bind(&Mouse_Map::PlatformSound, this));
	}

	if (nullptr == HouseBGRenderPtr)
	{
		HouseBGRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		HouseBGRenderPtr->SetTexture("Mouse_House_BackGround.png");
		HouseBGRenderPtr->GetTransform()->SetLocalScale({ 1400, 719 });
		HouseBGRenderPtr->GetTransform()->AddLocalPosition({ 0, 100, 10 });
	}

	if (nullptr == PlatformCollisionPtr)
	{
		PlatformCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Platform));
		PlatformCollisionPtr->GetTransform()->SetLocalScale({ 1000, 50, 1 });
		PlatformCollisionPtr->GetTransform()->SetLocalPosition({ 0, -10, -10 });
		PlatformCollisionPtr->Off();
	}

	if (nullptr == PlatformCollisionRenderPtr)
	{
		PlatformCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		PlatformCollisionRenderPtr->GetTransform()->SetLocalScale(PlatformCollisionPtr->GetTransform()->GetLocalScale());
		PlatformCollisionRenderPtr->GetTransform()->SetLocalPosition(PlatformCollisionPtr->GetTransform()->GetLocalPosition());
		PlatformCollisionRenderPtr->SetTexture("GreenBox.png");
		PlatformCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.5f;
		PlatformCollisionRenderPtr->Off();
	}

	HBSCControl(WallBGRenderPtr, 0.47f, 0.59f, 0.5f);
	HBSCControl(HouseBGRenderPtr, 0.47f, 0.59f, 0.5f);
	HBSCControl(Phase2PlatformRenderPtr, 0.47f, 0.52f, 0.5f);
}

void Mouse_Map::Update(float _DeltaTime)
{
	if (true == IsPhase3)
	{
		IsPhase3 = false;
		Phase2PlatformRenderPtr->ChangeAnimation("Phase3_WallBrake");
		Phase2PlatformRenderPtr->GetTransform()->SetLocalPosition({ 0, 30, -10 });
		Phase2PlatformRenderPtr->SetAnimationStartEvent("Phase3_WallBrake", 11, std::bind(&Mouse_Map::Phase3Setting, this));
		Mouse_BackObject::MouseBackObjectPtr->Off();
	}

	if (true == IsPhase2)
	{
		IsPhase2 = false;
		WallBGRenderPtr->SetScaleToTexture("Mouse_BackGround_Phase_2.png");
		Phase2PlatformRenderPtr->On();
	}

	if (true == Phase2PlatformRenderPtr->IsAnimationEnd() && true == IsEnd)
	{
		Phase2PlatformRenderPtr->Off();
	}
	if (11 == Phase2PlatformRenderPtr->GetCurrentFrame() && true == IsEnd)
	{
		Phase2PlatformRenderPtr->GetTransform()->SetLocalPosition({ 0, 30, -50 });
	}

	if (true == Phase2PlatformRenderPtr->IsUpdate() && false == IsEnd)
	{
		if (true == Phase2PlatformRenderPtr->IsAnimationEnd())
		{
			PlatformCollisionPtr->On();
		}
	
		if (true == IsDebugRender)
		{
			PlatformCollisionRenderPtr->On();
		}
		else
		{
			PlatformCollisionRenderPtr->Off();
		}
	}
}

void Mouse_Map::Phase3Setting()
{
	WallBGRenderPtr->SetScaleToTexture("Mouse_BackGround_Phase_3B.png");
	PlatformCollisionPtr->Off();
	PlatformCollisionRenderPtr->Off();
	IsEnd = true;
}

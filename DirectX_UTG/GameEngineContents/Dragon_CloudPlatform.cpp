#include "PrecompileHeader.h"
#include "Dragon_CloudPlatform.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"

Dragon_CloudPlatform::Dragon_CloudPlatform() 
{
}

Dragon_CloudPlatform::~Dragon_CloudPlatform() 
{
}

void Dragon_CloudPlatform::Start()
{
	if (nullptr == GameEngineSprite::Find("Cloud_Platform_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Cloud_Platform");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cloud_Platform_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Standing_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Standing_Outro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Standing_Idle").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Standing_Top_001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Cloud_Platform");
		NewDir.Move("Standing_Top");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Standing_Top_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Standing_Top_002.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Standing_Top_003.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Standing_Top_004.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Standing_Top_005.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Standing_Top_006.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Standing_Top_007.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Standing_Top_Idle_001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Cloud_Platform");
		NewDir.Move("Standing_Top_Idle");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Standing_Top_Idle_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Standing_Top_Idle_002.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Standing_Top_Idle_003.png").GetFullPath());
	}

	if (nullptr == CloudRenderPtr)
	{
		CloudRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		CloudRenderPtr->CreateAnimation({ .AnimationName = "Cloud_Platform_Idle", .SpriteName = "Cloud_Platform_Idle", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		CloudRenderPtr->CreateAnimation({ .AnimationName = "Standing_Intro", .SpriteName = "Standing_Intro", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		CloudRenderPtr->CreateAnimation({ .AnimationName = "Standing_Outro", .SpriteName = "Standing_Outro", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		CloudRenderPtr->CreateAnimation({ .AnimationName = "Standing_Idle", .SpriteName = "Standing_Idle", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		CloudRenderPtr->ChangeAnimation("Cloud_Platform_Idle");
	}

	if (nullptr == CloudUpRenderPtr)
	{
		CloudUpRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		CloudUpRenderPtr->SetScaleToTexture("Standing_Top_001.png");
		CloudUpRenderPtr->Off();
	}

	if (nullptr == PlatformCollisionPtr)
	{
		PlatformCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Platform));
		PlatformCollisionPtr->GetTransform()->SetLocalScale({ 200, 35, -2 });
	}

	if (nullptr == PlatformCollisionRenderPtr)
	{
		PlatformCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		PlatformCollisionRenderPtr->GetTransform()->SetLocalScale(PlatformCollisionPtr->GetTransform()->GetLocalScale());
		PlatformCollisionRenderPtr->GetTransform()->SetLocalPosition(PlatformCollisionPtr->GetTransform()->GetLocalPosition());
		PlatformCollisionRenderPtr->SetTexture("GreenBox.png");
		PlatformCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.6f;
		//PlatformCollisionRenderPtr->Off();
	}

	MoveSpeed = 50.0f;
}

void Dragon_CloudPlatform::Update(float _DeltaTime)
{
	MoveDis = MoveSpeed * _DeltaTime;

	GetTransform()->AddLocalPosition({ -MoveDis , 0 });

	CollisionCheck();
	UpdateState(_DeltaTime);

	float4 CurPos = GetTransform()->GetWorldPosition();

	if (CurPos.x <= 0.0f)
	{
		GetTransform()->SetWorldPosition(ActorInitPosition);
	}
}

void Dragon_CloudPlatform::CollisionCheck()
{
	/////////////// Platform
	//if (nullptr != PlatformCollisionPtr->Collision(static_cast<int>(CollisionOrder::PlayerFrontSensor), ColType::AABBBOX2D, ColType::AABBBOX2D))
	//{
	//	Player::MainPlayer->PlayerBlockDisturbance(MoveDis);
	//}

	if (nullptr != PlatformCollisionPtr->Collision(static_cast<int>(CollisionOrder::PlayerBottomSensor), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		if (true == Player::MainPlayer->GetPlatformCheckAble())
		{
			Player::MainPlayer->PlayerMoveDisturbance(-MoveDis);
		}

		IsStanding = true;
	}
}

void Dragon_CloudPlatform::ChangeState(CloudState _StateValue)
{
	CloudState NextState = _StateValue;
	CloudState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case CloudState::Idle:
		IdleStart();
		break;
	case CloudState::Plat_Intro:
		Plat_IntroStart();
		break;
	case CloudState::Plat:
		PlatStart();
		break;
	case CloudState::Plat_Outro:
		Plat_OutroStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case CloudState::Idle:
		IdleEnd();
		break;
	case CloudState::Plat_Intro:
		Plat_IntroEnd();
		break;
	case CloudState::Plat:
		PlatEnd();
		break;
	case CloudState::Plat_Outro:
		Plat_OutroEnd();
		break;
	default:
		break;
	}
}

void Dragon_CloudPlatform::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case CloudState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	case CloudState::Plat_Intro:
		Plat_IntroUpdate(_DeltaTime);
		break;
	case CloudState::Plat:
		PlatUpdate(_DeltaTime);
		break;
	case CloudState::Plat_Outro:
		Plat_OutroUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Dragon_CloudPlatform::IdleStart()
{
	CloudUpRenderPtr->Off();
}
void Dragon_CloudPlatform::IdleUpdate(float _DeltaTime)
{
	if (true == IsStanding)
	{
		ChangeState(CloudState::Plat_Intro);
		return;
	}
}
void Dragon_CloudPlatform::IdleEnd()
{

}

void Dragon_CloudPlatform::Plat_IntroStart()
{
	CloudRenderPtr->ChangeAnimation("Standing_Intro");
	CloudUpRenderPtr->On();
}
void Dragon_CloudPlatform::Plat_IntroUpdate(float _DeltaTime)
{
	PlatIntroUpRenderSetting();

	if (false == IsStanding)
	{
		ChangeState(CloudState::Plat_Outro);
		return;
	}

	if (true == CloudRenderPtr->IsAnimationEnd())
	{
		ChangeState(CloudState::Plat);
		return;
	}
}
void Dragon_CloudPlatform::Plat_IntroEnd()
{
}

void Dragon_CloudPlatform::PlatStart()
{
	CloudRenderPtr->ChangeAnimation("Standing_Idle");
}
void Dragon_CloudPlatform::PlatUpdate(float _DeltaTime)
{
	PlatUpRenderSetting();

	if (false == IsStanding)
	{
		ChangeState(CloudState::Plat_Outro);
		return;
	}
}
void Dragon_CloudPlatform::PlatEnd()
{

}

void Dragon_CloudPlatform::Plat_OutroStart()
{
	CloudRenderPtr->ChangeAnimation("Standing_Outro");
}
void Dragon_CloudPlatform::Plat_OutroUpdate(float _DeltaTime)
{
	PlatOutroUpRenderSetting();

	if (true == CloudRenderPtr->IsAnimationEnd())
	{
		ChangeState(CloudState::Idle);
		return;
	}
}
void Dragon_CloudPlatform::Plat_OutroEnd()
{
	CloudUpRenderPtr->Off();
}

void Dragon_CloudPlatform::PlatIntroUpRenderSetting()
{
	if (6 == CloudRenderPtr->GetCurrentFrame())
	{
		CloudUpRenderPtr->SetScaleToTexture("Standing_Top_007.png");
	}
	else if (5 == CloudRenderPtr->GetCurrentFrame())
	{
		CloudUpRenderPtr->SetScaleToTexture("Standing_Top_006.png");
	}
	else if (4 == CloudRenderPtr->GetCurrentFrame())
	{
		CloudUpRenderPtr->SetScaleToTexture("Standing_Top_005.png");
	}
	else if (3 == CloudRenderPtr->GetCurrentFrame())
	{
		CloudUpRenderPtr->SetScaleToTexture("Standing_Top_004.png");
	}
	else if (2 == CloudRenderPtr->GetCurrentFrame())
	{
		CloudUpRenderPtr->SetScaleToTexture("Standing_Top_003.png");
	}
	else if (1 == CloudRenderPtr->GetCurrentFrame())
	{
		CloudUpRenderPtr->SetScaleToTexture("Standing_Top_002.png");
	}
	else if (0 == CloudRenderPtr->GetCurrentFrame())
	{
		CloudUpRenderPtr->SetScaleToTexture("Standing_Top_001.png");
	}
}

void Dragon_CloudPlatform::PlatUpRenderSetting()
{
	if (2 == CloudRenderPtr->GetCurrentFrame())
	{
		CloudUpRenderPtr->SetScaleToTexture("Standing_Top_Idle_003.png");
	}
	else if (1 == CloudRenderPtr->GetCurrentFrame())
	{
		CloudUpRenderPtr->SetScaleToTexture("Standing_Top_Idle_002.png");
	}
	else if (0 == CloudRenderPtr->GetCurrentFrame())
	{
		CloudUpRenderPtr->SetScaleToTexture("Standing_Top_Idle_001.png");
	}
}

void Dragon_CloudPlatform::PlatOutroUpRenderSetting()
{
	if (6 == CloudRenderPtr->GetCurrentFrame())
	{
		CloudUpRenderPtr->SetScaleToTexture("Standing_Top_001.png");
	}
	else if (5 == CloudRenderPtr->GetCurrentFrame())
	{
		CloudUpRenderPtr->SetScaleToTexture("Standing_Top_002.png");
	}
	else if (4 == CloudRenderPtr->GetCurrentFrame())
	{
		CloudUpRenderPtr->SetScaleToTexture("Standing_Top_003.png");
	}
	else if (3 == CloudRenderPtr->GetCurrentFrame())
	{
		CloudUpRenderPtr->SetScaleToTexture("Standing_Top_004.png");
	}
	else if (2 == CloudRenderPtr->GetCurrentFrame())
	{
		CloudUpRenderPtr->SetScaleToTexture("Standing_Top_005.png");
	}
	else if (1 == CloudRenderPtr->GetCurrentFrame())
	{
		CloudUpRenderPtr->SetScaleToTexture("Standing_Top_006.png");
	}
	else if (0 == CloudRenderPtr->GetCurrentFrame())
	{
		CloudUpRenderPtr->SetScaleToTexture("Standing_Top_007.png");
	}
}
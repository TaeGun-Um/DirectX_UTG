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

	if (nullptr == CloudRenderPtr)
	{
		CloudRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		CloudRenderPtr->CreateAnimation({ .AnimationName = "Cloud_Platform_Idle", .SpriteName = "Cloud_Platform_Idle", .FrameInter = 0.09f, .Loop = true, .ScaleToTexture = true });
		CloudRenderPtr->CreateAnimation({ .AnimationName = "Standing_Intro", .SpriteName = "Standing_Intro", .FrameInter = 0.02f, .Loop = false, .ScaleToTexture = true });
		CloudRenderPtr->CreateAnimation({ .AnimationName = "Standing_Outro", .SpriteName = "Standing_Outro", .FrameInter = 0.02f, .Loop = false, .ScaleToTexture = true });
		CloudRenderPtr->CreateAnimation({ .AnimationName = "Standing_Idle", .SpriteName = "Standing_Idle", .FrameInter = 0.09f, .Loop = true, .ScaleToTexture = true });
		CloudRenderPtr->ChangeAnimation("Cloud_Platform_Idle");
	}

	if (nullptr == PlatformCollisionPtr)
	{
		PlatformCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Platform));
		PlatformCollisionPtr->GetTransform()->SetLocalPosition({ 0, -10 });
		PlatformCollisionPtr->GetTransform()->SetLocalScale({ 200, 35, -2 });
	}

	if (nullptr == PlatformCollisionRenderPtr)
	{
		PlatformCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		PlatformCollisionRenderPtr->GetTransform()->SetLocalScale(PlatformCollisionPtr->GetTransform()->GetLocalScale());
		PlatformCollisionRenderPtr->GetTransform()->SetLocalPosition(PlatformCollisionPtr->GetTransform()->GetLocalPosition());
		PlatformCollisionRenderPtr->SetTexture("GreenBox.png");
		PlatformCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.6f;
		PlatformCollisionRenderPtr->Off();
	}

	ChangeState(CloudState::Idle);
	MoveSpeed = 70.0f;
}

void Dragon_CloudPlatform::Update(float _DeltaTime)
{
	CollisionCheck();
	UpdateState(_DeltaTime);

	if (false == IsMove)
	{
		return;
	}

	MoveDis = MoveSpeed * _DeltaTime;
	GetTransform()->AddLocalPosition({ -MoveDis , 0 });

	float4 CurPos = GetTransform()->GetWorldPosition();

	if (CurPos.x <= -100.0f)
	{
		GetTransform()->SetWorldPosition({ 1370.0f , ActorInitPosition.y, ActorInitPosition.z });
	}
}

void Dragon_CloudPlatform::CollisionCheck()
{
	if (true == Player::MainPlayer->GetPlatformCheckAble())
	{
		if (nullptr != PlatformCollisionPtr->Collision(static_cast<int>(CollisionOrder::PlayerBottomSensor), ColType::AABBBOX2D, ColType::AABBBOX2D)
			&& false == Player::MainPlayer->GetIsBottomJump())
		{
			IsStanding = true;
			Player::MainPlayer->PlayerMoveDisturbance(-MoveDis);
		}
	}
	else
	{
		IsStanding = false;
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
	CloudRenderPtr->ChangeAnimation("Cloud_Platform_Idle");
}
void Dragon_CloudPlatform::IdleUpdate(float _DeltaTime)
{
	if (true == IsStanding)
	{
		ChangeState(CloudState::Plat_Intro);
		return;
	}

	if (true == IsInit)
	{
		ChangeState(CloudState::Plat);
		return;
	}
}
void Dragon_CloudPlatform::IdleEnd()
{

}

void Dragon_CloudPlatform::Plat_IntroStart()
{
	CloudRenderPtr->ChangeAnimation("Standing_Intro");
}
void Dragon_CloudPlatform::Plat_IntroUpdate(float _DeltaTime)
{
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
	if (false == IsMove)
	{
		return;
	}

	if (false == IsStanding)
	{
		ChangeState(CloudState::Plat_Outro);
		return;
	}
}
void Dragon_CloudPlatform::PlatEnd()
{
	IsInit = false;
}

void Dragon_CloudPlatform::Plat_OutroStart()
{
	CloudRenderPtr->ChangeAnimation("Standing_Outro");
}
void Dragon_CloudPlatform::Plat_OutroUpdate(float _DeltaTime)
{
	if (true == CloudRenderPtr->IsAnimationEnd())
	{
		ChangeState(CloudState::Idle);
		return;
	}
}
void Dragon_CloudPlatform::Plat_OutroEnd()
{

}

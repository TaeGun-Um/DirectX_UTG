#include "PrecompileHeader.h"
#include "SpringObject.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"
#include "MouseLevel.h"
#include "You_Died.h"

SpringObject::SpringObject() 
{
}

SpringObject::~SpringObject() 
{
}

void SpringObject::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "Spring_Intro", .SpriteName = "Spring_Intro", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Spring_Land", .SpriteName = "Spring_Land", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Spring_Idle_Loop", .SpriteName = "Spring_Idle_Loop", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Spring_Launch", .SpriteName = "Spring_Launch", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Spring_Death", .SpriteName = "Spring_Death", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("Spring_Intro");
		ChangeState(SpringState::Intro);
	}

	if (nullptr == ParryCollisionPtr)
	{
		ParryCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::ParrySpot));
		ParryCollisionPtr->SetColType(ColType::SPHERE2D);
		ParryCollisionPtr->GetTransform()->SetLocalScale({ 70, 80, 1 });
		ParryCollisionPtr->GetTransform()->SetLocalPosition({ 0, -60 });
		ParryCollisionPtr->Off();
	}

	if (nullptr == BreakCollisionPtr)
	{
		BreakCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::ParrySpot));
		BreakCollisionPtr->SetColType(ColType::SPHERE2D);
		BreakCollisionPtr->GetTransform()->SetLocalScale({ 70, 80, 1 });
		BreakCollisionPtr->GetTransform()->SetLocalPosition({ 0, -60 });
		BreakCollisionPtr->Off();
	}

	if (nullptr == ParryCollisionRenderPtr)
	{
		ParryCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ParryCollisionRenderPtr->SetTexture("GreenLine.png");
		ParryCollisionRenderPtr->GetTransform()->SetLocalScale(ParryCollisionPtr->GetTransform()->GetLocalScale());
		ParryCollisionRenderPtr->GetTransform()->SetLocalPosition(ParryCollisionPtr->GetTransform()->GetLocalPosition());
		ParryCollisionRenderPtr->Off();
	}
}

void SpringObject::Update(float _DeltaTime)
{
	if (true == MouseLevel::MouseLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	MoveDirection(_DeltaTime);
	PixelCheck(_DeltaTime);
	CollisionCheck();
	UpdateState(_DeltaTime);
}

void SpringObject::MoveDirection(float _DeltaTime)
{
	if (true == IsLand)
	{
		return;
	}

	if (false == IsJump)
	{
		IsJump = true;
		MoveDirect.y += JumpPower;
	}

	if (true == IsJump && MoveDirect.y >= -800.0f)
	{
		MoveDirect.y -= 1200.0f * _DeltaTime;
	}

	float MoveDist = MoveSpeed * _DeltaTime;

	GetTransform()->AddLocalPosition({ -MoveDist, 0 });

	GetTransform()->AddLocalPosition(MoveDirect * _DeltaTime);
}

void SpringObject::CollisionCheck()
{
	if (nullptr != ParryCollisionPtr->Collision(static_cast<int>(CollisionOrder::PlayerParry), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		Player::MainPlayer->SetSpringOn();
		ParryCollisionPtr->Off();
		IsLaunch = true;
	}

	if (nullptr != BreakCollisionPtr->Collision(static_cast<int>(CollisionOrder::Monster), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		IsDeath = true;
	}
}

void SpringObject::PixelCheck(float _DeltaTime)
{
	if (true == IsLand)
	{
		return;
	}

	float4 ProjectilePos = GetTransform()->GetWorldPosition();
	float4 LandPos = ProjectilePos + float4{ 0, -140 };

	GameEnginePixelColor LandPixel = PixelCollisionCheck.PixelCheck(LandPos);

	if (true == PixelCollisionCheck.IsBlack(LandPixel))
	{
		EffectPlayer = GameEngineSound::Play("mouse_can_springboard_land_01.wav");
		MoveDirect = float4::Zero;
		IsLand = true;
	}
}

void SpringObject::ChangeState(SpringState _StateValue)
{
	SpringState NextState = _StateValue;
	SpringState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case SpringState::Intro:
		IntroStart();
		break;
	case SpringState::Land:
		LandStart();
		break;
	case SpringState::Idle_Loop:
		Idle_LoopStart();
		break;
	case SpringState::Launch:
		LaunchStart();
		break;
	case SpringState::Death:
		DeathStart();
		break;
	default:
		break;
	}

	switch (NextState)
	{
	case SpringState::Intro:
		IntroEnd();
		break;
	case SpringState::Land:
		LandEnd();
		break;
	case SpringState::Idle_Loop:
		Idle_LoopEnd();
		break;
	case SpringState::Launch:
		LaunchEnd();
		break;
	case SpringState::Death:
		DeathEnd();
		break;
	default:
		break;
	}
}

void SpringObject::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case SpringState::Intro:
		IntroUpdate(_DeltaTime);
		break;
	case SpringState::Land:
		LandUpdate(_DeltaTime);
		break;
	case SpringState::Idle_Loop:
		Idle_LoopUpdate(_DeltaTime);
		break;
	case SpringState::Launch:
		LaunchUpdate(_DeltaTime);
		break;
	case SpringState::Death:
		DeathUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void SpringObject::IntroStart()
{
	RenderPtr->ChangeAnimation("Spring_Intro");
}
void SpringObject::IntroUpdate(float _DeltaTime)
{
	if (true == IsLand)
	{
		ChangeState(SpringState::Land);
		return;
	}
}
void SpringObject::IntroEnd()
{

}

void SpringObject::LandStart()
{
	RenderPtr->ChangeAnimation("Spring_Land");
}
void SpringObject::LandUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ParryCollisionPtr->On();
		BreakCollisionPtr->On();
		ChangeState(SpringState::Idle_Loop);
		return;
	}
}
void SpringObject::LandEnd()
{

}

void SpringObject::Idle_LoopStart()
{
	RenderPtr->ChangeAnimation("Spring_Idle_Loop");
}
void SpringObject::Idle_LoopUpdate(float _DeltaTime)
{
	if (true == IsDeath)
	{
		ChangeState(SpringState::Death);
		return;
	}

	if (true == IsLaunch)
	{
		ChangeState(SpringState::Launch);
		return;
	}
}
void SpringObject::Idle_LoopEnd()
{

}

void SpringObject::LaunchStart()
{
	RenderPtr->ChangeAnimation("Spring_Launch");
}
void SpringObject::LaunchUpdate(float _DeltaTime)
{
	if (true == IsDeath)
	{
		ChangeState(SpringState::Death);
		return;
	}

	if (true == RenderPtr->IsAnimationEnd())
	{
		IsLaunch = false;
		ParryCollisionPtr->On();
		ChangeState(SpringState::Idle_Loop);
		return;
	}
}
void SpringObject::LaunchEnd()
{

}

void SpringObject::DeathStart()
{
	ParryCollisionPtr->Off();
	ParryCollisionRenderPtr->Off();

	RenderPtr->ChangeAnimation("Spring_Death");
}
void SpringObject::DeathUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		Death();
	}
}
void SpringObject::DeathEnd()
{

}
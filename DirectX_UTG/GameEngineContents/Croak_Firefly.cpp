#include "PrecompileHeader.h"
#include "Croak_Firefly.h"

#include <cmath>

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"
#include "Peashooter.h"
#include "Spread.h"

#include "FrogLevel.h"
#include "You_Died.h"

Croak_Firefly::Croak_Firefly() 
{
}

Croak_Firefly::~Croak_Firefly() 
{
}

void Croak_Firefly::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Firefly_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Left", .SpriteName = "Firefly_Left", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Up", .SpriteName = "Firefly_Up", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Down", .SpriteName = "Firefly_Down", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Death", .SpriteName = "Firefly_Death", .FrameInter = 0.03f, .Loop = false, .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("Left");
	}

	if (nullptr == ProjectileCollisionPtr)
	{
		ProjectileCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Monster));
		ProjectileCollisionPtr->SetColType(ColType::SPHERE2D);
		ProjectileCollisionPtr->GetTransform()->SetLocalScale({ 80, 80, 1 });
		ProjectileCollisionPtr->GetTransform()->SetLocalPosition({ 5, -25 });
	}

	if (nullptr == ProjectileCollisionRenderPtr)
	{
		ProjectileCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ProjectileCollisionRenderPtr->SetTexture("GreenLine.png");
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalScale(ProjectileCollisionPtr->GetTransform()->GetLocalScale());
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalPosition(ProjectileCollisionPtr->GetTransform()->GetLocalPosition());
		ProjectileCollisionRenderPtr->Off();
	}
}

void Croak_Firefly::Update(float _DeltaTime)
{
	if (true == FrogLevel::FrogLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	if (true == IsSpawn)
	{
		SpawnMove(_DeltaTime);
	}

	CollisionCheck();
	UpdateState(_DeltaTime);
}

void Croak_Firefly::SpawnMove(float _DeltaTime)
{
	if (true == IsDeath)
	{
		return;
	}

	CurPosition = GetTransform()->GetLocalPosition();
	float4 Movedir = float4::Zero;

	Movedir = (SpawnPosition - CurPosition);

	MoveDistance = Movedir * 4.0f * _DeltaTime;

	GetTransform()->AddWorldPosition(MoveDistance);

	if ((SpawnPosition.x + 15) >= CurPosition.x)
	{
		IsSpawn = false;
		ChangeState(FlyState::Idle);
	}
}

void Croak_Firefly::CollisionCheck()
{
	if (nullptr != ProjectileCollisionPtr->Collision(static_cast<int>(CollisionOrder::Peashooter), ColType::AABBBOX2D, ColType::SPHERE2D) && false == IsDeath)
	{
		GameEngineActor* Projectile = ProjectileCollisionPtr->Collision(static_cast<int>(CollisionOrder::Peashooter), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();

		ProjectileCollisionRenderPtr->Death();
		ProjectileCollisionPtr->Death();

		dynamic_cast<Peashooter*>(Projectile)->SetPeashooterDeath();
		dynamic_cast<Peashooter*>(Projectile)->SetHitture();

		IsDeath = true;
	}

	if (nullptr != ProjectileCollisionPtr->Collision(static_cast<int>(CollisionOrder::Spread), ColType::AABBBOX2D, ColType::SPHERE2D) && false == IsDeath)
	{
		GameEngineActor* Projectile = ProjectileCollisionPtr->Collision(static_cast<int>(CollisionOrder::Spread), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		
		ProjectileCollisionRenderPtr->Death();
		ProjectileCollisionPtr->Death();
		
		dynamic_cast<Spread*>(Projectile)->SetSpreadDeath();
		dynamic_cast<Spread*>(Projectile)->SetHitture();

		IsDeath = true;
	}
}

void Croak_Firefly::ChangeState(FlyState _StateValue)
{
	FlyState NextState = _StateValue;
	FlyState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case FlyState::Idle:
		IdleStart();
		break;
	case FlyState::Move:
		MoveStart();
		break;
	case FlyState::Death:
		DeathStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case FlyState::Idle:
		IdleEnd();
		break;
	case FlyState::Move:
		MoveEnd();
		break;
	case FlyState::Death:
		DeathEnd();
		break;
	default:
		break;
	}
}

void Croak_Firefly::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case FlyState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	case FlyState::Move:
		MoveUpdate(_DeltaTime);
		break;
	case FlyState::Death:
		DeathUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Croak_Firefly::IdleStart()
{
	RenderPtr->ChangeAnimation("Idle");
}
void Croak_Firefly::IdleUpdate(float _DeltaTime)
{
	if (true == IsDeath)
	{
		ChangeState(FlyState::Death);
		return;
	}

	if (true == IsSpawn)
	{
		return;
	}

	IdleDelayTime += _DeltaTime;

	if (1.0f <= IdleDelayTime)
	{
		ChangeState(FlyState::Move);
		return;
	}
}
void Croak_Firefly::IdleEnd()
{
	IdleDelayTime = 0.0f;
}

void Croak_Firefly::MoveStart()
{
	CurPosition = GetTransform()->GetLocalPosition();
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
	float4 YUpPos = { 0, 50 };
	float4 Direct = PlayerPos + YUpPos - CurPosition;

	DirectNormal = Direct.NormalizeReturn();

	int RandC = GameEngineRandom::MainRandom.RandomInt(0, 3);
	++RandMoveCount;

	if (0 == RandC && RandMoveCount <= MaxRandMoveCount)
	{
		DirectNormal.RotaitonYDeg(180.0f);
	}

	TrackingPosition = (CurPosition + (DirectNormal * 200));

	if (0.0f >= TrackingPosition.x)
	{
		TrackingPosition.x = 30.0f;
	}
	else if (1280.0f <= TrackingPosition.x)
	{
		TrackingPosition.x = 1250.0f;
	}

	RenderPtr->ChangeAnimation("Left");

	if (0 == RandC)
	{
		if (Direct.x < 0)
		{
			GetTransform()->SetLocalNegativeScaleX();
		}
		else if (Direct.x >= 0)
		{
			GetTransform()->SetLocalPositiveScaleX();
		}
	}
	else
	{
		if (Direct.x < 0)
		{
			GetTransform()->SetLocalPositiveScaleX();
		}
		else if (Direct.x >= 0)
		{
			GetTransform()->SetLocalNegativeScaleX();
		}
	}
}
void Croak_Firefly::MoveUpdate(float _DeltaTime)
{
	if (true == IsDeath)
	{
		ChangeState(FlyState::Death);
		return;
	}

	CurPosition = GetTransform()->GetLocalPosition();
	float4 Movedir = float4::Zero;

	Movedir = (TrackingPosition - CurPosition);

	MoveDistance = Movedir * 4.0f * _DeltaTime;

	GetTransform()->AddWorldPosition(MoveDistance);

	if (TrackingPosition.y + 5 >= CurPosition.y)
	{
		ChangeState(FlyState::Idle);
		return;
	}
}
void Croak_Firefly::MoveEnd()
{

}

void Croak_Firefly::DeathStart()
{
	RenderPtr->ChangeAnimation("Death");
}
void Croak_Firefly::DeathUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		Death();
	}
}
void Croak_Firefly::DeathEnd()
{

}
#include "PrecompileHeader.h"
#include "Peashooter.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"

Peashooter::Peashooter() 
{
}

Peashooter::~Peashooter() 
{
}

void Peashooter::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ "Loop", "Peashooter_Loop.png", 0, 7, 0.07f, true, false });
		RenderPtr->CreateAnimation({ "Death", "Peashooter_Death.png", 0, 6, 0.05f, true, false });

		RenderPtr->GetTransform()->SetLocalScale(float4{ 350, 350 });
		RenderPtr->ChangeAnimation("Loop");
	}

	if (nullptr == ProjectileCollisionPtr)
	{
		ProjectileCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Peashooter));
		ProjectileCollisionPtr->GetTransform()->SetLocalScale({ 20, 20, 1 });
		ProjectileCollisionPtr->GetTransform()->SetLocalPosition({ 25, 0 });
	}

	if (nullptr == ProjectileCollisionRenderPtr)
	{
		ProjectileCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ProjectileCollisionRenderPtr->SetTexture("RedBox.png");
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalScale(ProjectileCollisionPtr->GetTransform()->GetLocalScale());
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalPosition(ProjectileCollisionPtr->GetTransform()->GetLocalPosition());
	}
}
void Peashooter::Update(float _DeltaTime)
{
	MoveDirection(_DeltaTime);
	HitCheck();
	PixelCheck();
	DeathCheck();
}

void Peashooter::MoveDirection(float _DeltaTime)
{
	if (true == IsDeath || true == Check)
	{
		return;
	}

	float MoveDist = MoveSpeed * _DeltaTime;

	float4 MoveDist4 = float4::Zero;
	float4 Correction = float4::Zero;

	Correction = GetTransform()->GetWorldRightVector().NormalizeReturn();
	GetTransform()->AddLocalPosition(Correction * MoveSpeed * _DeltaTime);
}

void Peashooter::HitCheck()
{
	if (true == IsHit)
	{
		IsHit = false;
		Player::MainPlayer->AddPlayerEXGauge_Peashooter();
	}
}

void Peashooter::PixelCheck()
{
	float4 ProjectilePosition = GetTransform()->GetLocalPosition();

	GameEnginePixelColor ColMapPixel = PixelCollisionCheck.PixelCheck(ProjectilePosition);

	if (true == PixelCollisionCheck.IsBlack(ColMapPixel))
	{
		if (false == Check)
		{
			SetPeashooterDeath();
		}
	}
}

void Peashooter::DeathCheck()
{
	if (1.0f <= GetLiveTime())
	{
		if (false == Check)
		{
			SetPeashooterDeath();
		}
	}

	if (true == RenderPtr->FindAnimation("Death")->IsEnd())
	{
		IsDeath = true;
	}

	if (true == IsDeath)
	{
		Death();
	}
}

void Peashooter::SetPeashooterDeath()
{
	Check = true;

	ProjectileCollisionRenderPtr->Death();
	ProjectileCollisionPtr->Death();

	RenderPtr->ChangeAnimation("Death", false);
	RenderPtr->GetTransform()->SetLocalPosition(float4{ 20, 0 });
	RenderPtr->GetTransform()->SetLocalScale(float4{ 270, 270 });
}
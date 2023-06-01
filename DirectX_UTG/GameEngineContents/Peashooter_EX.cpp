#include "PrecompileHeader.h"
#include "Peashooter_EX.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Peashooter_EX::Peashooter_EX() 
{
}

Peashooter_EX::~Peashooter_EX() 
{
}

void Peashooter_EX::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ "Loop", "Peashooter_EX_Loop.png", 0, 7, 0.06f, true, false });
		RenderPtr->CreateAnimation({ "Death", "Peashooter_EX_Death.png", 0, 8, 0.06f, false, false });

		RenderPtr->GetTransform()->SetLocalScale(float4{ 750, 750 });
		RenderPtr->ChangeAnimation("Loop");
	}

	if (nullptr == ProjectileCollisionPtr)
	{
		ProjectileCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::PeashooterEX));
		ProjectileCollisionPtr->GetTransform()->SetLocalScale({ 70, 70, 1 });
		ProjectileCollisionPtr->GetTransform()->SetLocalPosition({ 100, 0 });
	}

	if (nullptr == ProjectileCollisionRenderPtr)
	{
		ProjectileCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ProjectileCollisionRenderPtr->SetTexture("RedLine.png");
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalScale(ProjectileCollisionPtr->GetTransform()->GetLocalScale());
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalPosition(ProjectileCollisionPtr->GetTransform()->GetLocalPosition());
	}
}

void Peashooter_EX::Update(float _DeltaTime)
{
	MoveDirection(_DeltaTime);
	DeathCheck();
}

void Peashooter_EX::MoveDirection(float _DeltaTime)
{
	if (0 == Stack)
	{
		IsHit = false;
		StopTime = 0.0f;
		SetPeashooter_EXDeath();
		return;
	}

	if (true == IsDeath || true == Check)
	{
		return;
	}

	if (true == IsHit)
	{
		StopTime += _DeltaTime;

		ProjectileCollisionPtr->Off();

		if (StopTime <= 0.2f)
		{
			return;
		}
	}

	if (StopTime >= 0.27f)
	{
		IsHit = false;
		StopTime = 0.0f;
		ProjectileCollisionPtr->On();
	}

	float MoveDist = MoveSpeed * _DeltaTime;

	float4 MoveDist4 = float4::Zero;
	float4 Correction = float4::Zero;

	Correction = GetTransform()->GetWorldRightVector().NormalizeReturn();
	GetTransform()->AddLocalPosition(Correction * MoveSpeed * _DeltaTime);
}

void Peashooter_EX::DeathCheck()
{
	if (3.0f <= GetLiveTime())
	{
		if (false == Check)
		{
			Check = true;
			RenderPtr->ChangeAnimation("Death", false);
			RenderPtr->GetTransform()->SetLocalPosition({ 60, 0 });
		}
	}

	if (true == Check && true == RenderPtr->IsAnimationEnd())
	{
		IsDeath = true;
		Death();
	}
}

void Peashooter_EX::SetPeashooter_EXDeath()
{
	Check = true;

	ProjectileCollisionRenderPtr->Death();
	ProjectileCollisionPtr->Death();

	RenderPtr->ChangeAnimation("Death", false);
	RenderPtr->GetTransform()->SetLocalPosition({60, 0});
}
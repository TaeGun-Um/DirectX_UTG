#include "PrecompileHeader.h"
#include "Spread.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"

Spread::Spread() 
{
}

Spread::~Spread() 
{
}

void Spread::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ "Loop", "Spread_Loop.png", 0, 3, 0.05f, true, false });
		RenderPtr->CreateAnimation({ "Death", "Spread_Death.png", 1, 4, 0.05f, true, true });
		RenderPtr->CreateAnimation({ "Death_Enemyhit", "Spread_Death_Enemyhit.png", 0, 2, 0.05f, true, true });
		RenderPtr->CreateAnimation({ "Weak_Loop", "Spread_Weak_Loop.png", 0, 3, 0.05f, true, true });
		RenderPtr->CreateAnimation({ "Weak_Death", "Spread_Weak_Death.png", 1, 4, 0.05f, true, true });
		RenderPtr->CreateAnimation({ "Weak_Death_Enemyhit", "Spread_Weak_Death_Enemyhit.png", 0, 2, 0.05f, true, true });

		RenderPtr->GetTransform()->SetLocalScale(float4{ 400, 400 });
		RenderPtr->ChangeAnimation("Loop");
	}

	if (nullptr == ProjectileCollisionPtr)
	{
		ProjectileCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Spread));
		ProjectileCollisionPtr->GetTransform()->SetLocalScale({ 20, 20, 1 });
		ProjectileCollisionPtr->GetTransform()->SetLocalPosition({ 0, 0 });
	}

	if (nullptr == ProjectileCollisionRenderPtr)
	{
		ProjectileCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ProjectileCollisionRenderPtr->SetTexture("GreenBox.png");
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalScale(ProjectileCollisionPtr->GetTransform()->GetLocalScale());
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalPosition(ProjectileCollisionPtr->GetTransform()->GetLocalPosition());
	}
}
void Spread::Update(float _DeltaTime)
{
	MoveDirection(_DeltaTime);
	HitCheck();
	PixelCheck();
	DeathCheck();
}

void Spread::MoveDirection(float _DeltaTime)
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

void Spread::HitCheck()
{
	if (true == IsHit)
	{
		IsHit = false;
		Player::MainPlayer->AddPlayerEXGauge_Peashooter();
	}
}

void Spread::PixelCheck()
{
	float4 ProjectilePosition = GetTransform()->GetLocalPosition();

	GameEnginePixelColor ColMapPixel = PixelCollisionCheck.PixelCheck(ProjectilePosition);

	if (true == PixelCollisionCheck.IsBlack(ColMapPixel))
	{
		if (false == Check)
		{
			SetSpreadDeath();
		}
	}
}

void Spread::DeathCheck()
{
	if (0.24f <= GetLiveTime())
	{
		SetSpreadDeathWeak();
	}

	if (true == RenderPtr->FindAnimation("Death")->IsEnd()
		|| true == RenderPtr->FindAnimation("Weak_Death")->IsEnd()
		|| true == RenderPtr->FindAnimation("Death_Enemyhit")->IsEnd()
		|| true == RenderPtr->FindAnimation("Weak_Death_Enemyhit")->IsEnd())
	{
		IsDeath = true;
	}

	if (true == IsDeath)
	{
		Death();
	}
}

void Spread::SetSpreadDeathWeak()
{
	Check = true;

	ProjectileCollisionRenderPtr->Death();
	ProjectileCollisionPtr->Death();

	if (true == DeathType)
	{
		RenderPtr->ChangeAnimation("Death", false);
	}
	else
	{
		RenderPtr->ChangeAnimation("Weak_Death", false);
	}
}

void Spread::SetSpreadDeath()
{
	Check = true;

	ProjectileCollisionRenderPtr->Death();
	ProjectileCollisionPtr->Death();

	if (true == DeathType)
	{
		RenderPtr->ChangeAnimation("Death_Enemyhit", false);
	}
	else
	{
		RenderPtr->ChangeAnimation("Weak_Death_Enemyhit", false);
	}
}
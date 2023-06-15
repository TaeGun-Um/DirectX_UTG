#include "PrecompileHeader.h"
#include "FistAttack_Projectile.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "FrogLevel.h"
#include "Player.h"

#include "You_Died.h"

FistAttack_Projectile::FistAttack_Projectile() 
{
}

FistAttack_Projectile::~FistAttack_Projectile() 
{
}

void FistAttack_Projectile::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "Normal_Spawn", .SpriteName = "Normal_Spawn", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Normal_Loop", .SpriteName = "Normal_Loop", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Pink_Spawn", .SpriteName = "Pink_Spawn", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Pink_Loop", .SpriteName = "Pink_Loop", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Death_FX", .SpriteName = "Death_FX", .FrameInter = 0.03f, .Loop = false, .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("Normal_Spawn");
	}

	if (nullptr == ProjectileCollisionPtr)
	{
		ProjectileCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
		ProjectileCollisionPtr->SetColType(ColType::SPHERE2D);
		ProjectileCollisionPtr->GetTransform()->SetLocalScale({ 60, 60, 1 });
		ProjectileCollisionPtr->GetTransform()->SetLocalPosition({ 40, 0 });
	}

	if (nullptr == ProjectileCollisionRenderPtr)
	{
		ProjectileCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ProjectileCollisionRenderPtr->SetTexture("RedBox.png");
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalScale(ProjectileCollisionPtr->GetTransform()->GetLocalScale());
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalPosition(ProjectileCollisionPtr->GetTransform()->GetLocalPosition());
		ProjectileCollisionRenderPtr->Off();
	}

	if (nullptr == ParryCollisionPtr)
	{
		ParryCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::ParrySpot));
		ParryCollisionPtr->SetColType(ColType::SPHERE2D);
		ParryCollisionPtr->GetTransform()->SetLocalScale({ 120, 120, 1 });
		ParryCollisionPtr->GetTransform()->SetLocalPosition({ 40, 0 });
		ParryCollisionPtr->Off();
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

void FistAttack_Projectile::Update(float _DeltaTime)
{
	if (true == FrogLevel::FrogLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	if (true == IsParryProjectile)
	{
		IsParryProjectile = false;
		ParryCollisionPtr->On();
		RenderPtr->ChangeAnimation("Pink_Spawn");
	}

	if (true == RenderPtr->FindAnimation("Pink_Spawn")->IsEnd() && false == IsDeath)
	{
		RenderPtr->ChangeAnimation("Pink_Loop", false);
	}

	if (true == RenderPtr->FindAnimation("Normal_Spawn")->IsEnd() && false == IsDeath)
	{
		RenderPtr->ChangeAnimation("Normal_Loop", false);
	}

	MoveDirection(_DeltaTime);
	DeathCheck();
	CollisionCheck();
}

void FistAttack_Projectile::MoveDirection(float _DeltaTime)
{
	if (true == IsDeath)
	{
		return;
	}

	float MoveDist = MoveSpeed * _DeltaTime;

	float4 MoveDist4 = float4::Zero;
	float4 Correction = float4::Zero;

	Correction = GetTransform()->GetWorldRightVector().NormalizeReturn();
	GetTransform()->AddLocalPosition(Correction * MoveSpeed * _DeltaTime);
}

void FistAttack_Projectile::CollisionCheck()
{
	if (nullptr != ParryCollisionPtr->Collision(static_cast<int>(CollisionOrder::PlayerParry), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		Player::MainPlayer->SetParryOn();
		IsDeath = true;
	}
}

void FistAttack_Projectile::DeathCheck()
{
	if (2.0f <= GetLiveTime())
	{
		IsDeath = true;
	}

	if (true == IsDeath)
	{
		RenderPtr->ChangeAnimation("Death_FX", false);
	}

	if (true == RenderPtr->IsAnimationEnd() && true == IsDeath)
	{
		Death();
	}
}

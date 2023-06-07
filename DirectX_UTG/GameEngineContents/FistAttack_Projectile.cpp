#include "PrecompileHeader.h"
#include "FistAttack_Projectile.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

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

		RenderPtr->ChangeAnimation("Normal_Spawn");
	}

	//if (nullptr == ProjectileCollisionPtr)
	//{
	//	ProjectileCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
	//	ProjectileCollisionPtr->SetColType(ColType::SPHERE2D);
	//	ProjectileCollisionPtr->GetTransform()->SetLocalScale({ 20, 20, 1 });
	//	ProjectileCollisionPtr->GetTransform()->SetLocalPosition({ 25, 0 });
	//}

	//if (nullptr == ProjectileCollisionRenderPtr)
	//{
	//	ProjectileCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	//	ProjectileCollisionRenderPtr->SetTexture("RedBox.png");
	//	ProjectileCollisionRenderPtr->GetTransform()->SetLocalScale(ProjectileCollisionPtr->GetTransform()->GetLocalScale());
	//	ProjectileCollisionRenderPtr->GetTransform()->SetLocalPosition(ProjectileCollisionPtr->GetTransform()->GetLocalPosition());
	//}

	//ParrySpot
}

void FistAttack_Projectile::Update(float _DeltaTime)
{
	if (true == RenderPtr->FindAnimation("Normal_Spawn")->IsEnd())
	{
		RenderPtr->ChangeAnimation("Normal_Loop", false);
	}

	MoveDirection(_DeltaTime);
	DeathCheck();
}

void FistAttack_Projectile::MoveDirection(float _DeltaTime)
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

void FistAttack_Projectile::DeathCheck()
{
	if (5.0f <= GetLiveTime())
	{
		if (false == Check)
		{
			//SetFistDeath();
			IsDeath = true;
		}
	}

	if (true == IsDeath)
	{
		Death();
	}
}

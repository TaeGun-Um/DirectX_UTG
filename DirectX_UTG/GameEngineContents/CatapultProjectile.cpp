#include "PrecompileHeader.h"
#include "CatapultProjectile.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "MouseLevel.h"
#include "You_Died.h"
#include "Player.h"

CatapultProjectile::CatapultProjectile() 
{
}

CatapultProjectile::~CatapultProjectile() 
{
}

void CatapultProjectile::SetProjectileRandomAnimation()
{
	int RandC = GameEngineRandom::MainRandom.RandomInt(0, 5);

	if (0 == RandC)
	{
		RenderPtr->ChangeAnimation("Bolt");
	}
	else if (1 == RandC)
	{
		RenderPtr->ChangeAnimation("Coin");
	}
	else if (2 == RandC)
	{
		RenderPtr->ChangeAnimation("Nut");
	}
	else if (3 == RandC)
	{
		RenderPtr->ChangeAnimation("Popcap");
	}
	else if (4 == RandC)
	{
		RenderPtr->ChangeAnimation("Tooth");
	}
}

void CatapultProjectile::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "Bolt", .SpriteName = "CatapultProjectile_Bolt", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin", .SpriteName = "CatapultProjectile_Coin", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Gum", .SpriteName = "CatapultProjectile_Gum", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Nut", .SpriteName = "CatapultProjectile_Nut", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Popcap", .SpriteName = "CatapultProjectile_Popcap", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Tooth", .SpriteName = "CatapultProjectile_Tooth", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("Bolt");
	}

	if (nullptr == ProjectileCollisionPtr)
	{
		ProjectileCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
		ProjectileCollisionPtr->SetColType(ColType::SPHERE2D);
		ProjectileCollisionPtr->GetTransform()->SetLocalScale({ 10, 10, 1 });
		ProjectileCollisionPtr->GetTransform()->SetLocalPosition({ 0, 0 });
	}

	if (nullptr == ProjectileCollisionRenderPtr)
	{
		ProjectileCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ProjectileCollisionRenderPtr->SetTexture("GreenBox.png");
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalScale(ProjectileCollisionPtr->GetTransform()->GetLocalScale());
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalPosition(ProjectileCollisionPtr->GetTransform()->GetLocalPosition());
		ProjectileCollisionRenderPtr->Off();
	}

	if (nullptr == ParryCollisionPtr)
	{
		ParryCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::ParrySpot));
		ParryCollisionPtr->SetColType(ColType::SPHERE2D);
		ParryCollisionPtr->GetTransform()->SetLocalScale({ 70, 70, 1 });
		ParryCollisionPtr->GetTransform()->SetLocalPosition({ 0, 0 });
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

void CatapultProjectile::Update(float _DeltaTime)
{
	if (true == MouseLevel::MouseLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	if (true == IsParryProjectile)
	{
		IsParryProjectile = false;
		ParryCollisionPtr->On();
		RenderPtr->ChangeAnimation("Gum");
	}

	MoveDirection(_DeltaTime);
	CollisionCheck();
	DeathCheck();
}

void CatapultProjectile::MoveDirection(float _DeltaTime)
{
	if (true == IsDeath)
	{
		return;
	}

	float4 MoveDist4 = float4::Zero;
	float4 Correction = float4::Zero;

	if (false == Directbool)
	{
		Correction = GetTransform()->GetWorldLeftVector().NormalizeReturn();

		float MoveDist = MoveSpeed * _DeltaTime;

		GetTransform()->AddLocalPosition(Correction * MoveSpeed * _DeltaTime);
	}
	else
	{
		Correction = GetTransform()->GetWorldRightVector().NormalizeReturn();

		float MoveDist = MoveSpeed * _DeltaTime;

		GetTransform()->AddLocalPosition(Correction * MoveSpeed * _DeltaTime);
	}
}

void CatapultProjectile::CollisionCheck()
{
	if (nullptr != ParryCollisionPtr->Collision(static_cast<int>(CollisionOrder::PlayerParry), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		Player::MainPlayer->SetParryOn();
		Death();
	}
}

void CatapultProjectile::DeathCheck()
{
	float4 CurPos = GetTransform()->GetLocalPosition();

	if (false == Directbool && StartPosition.x - 1100.0f >= CurPos.x)
	{
		Death();
	}
	else if (true == Directbool && StartPosition.x + 1100.0f <= CurPos.x)
	{
		Death();
	}
}

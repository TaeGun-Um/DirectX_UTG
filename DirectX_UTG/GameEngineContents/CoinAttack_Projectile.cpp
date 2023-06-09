#include "PrecompileHeader.h"
#include "CoinAttack_Projectile.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"
#include "FrogLevel.h"
#include "You_Died.h"

CoinAttack_Projectile::CoinAttack_Projectile() 
{
}

CoinAttack_Projectile::~CoinAttack_Projectile() 
{
}

void CoinAttack_Projectile::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Projectile", .SpriteName = "Coin_Projectile", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("Coin_Projectile");
	}

	if (nullptr == ProjectileCollisionPtr)
	{
		ProjectileCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
		ProjectileCollisionPtr->SetColType(ColType::SPHERE2D);
		ProjectileCollisionPtr->GetTransform()->SetLocalScale({ 45, 45, 1 });
		ProjectileCollisionPtr->GetTransform()->SetLocalPosition({ 0, 0 });
	}

	if (nullptr == ProjectileCollisionRenderPtr)
	{
		ProjectileCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ProjectileCollisionRenderPtr->SetTexture("RedLine.png");
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalScale(ProjectileCollisionPtr->GetTransform()->GetLocalScale());
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalPosition(ProjectileCollisionPtr->GetTransform()->GetLocalPosition());
		ProjectileCollisionRenderPtr->Off();
	}
}

void CoinAttack_Projectile::Update(float _DeltaTime)
{
	if (true == FrogLevel::FrogLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	MoveDirection(_DeltaTime);
	DeathCheck();
}

void CoinAttack_Projectile::MoveDirection(float _DeltaTime)
{
	if (1 == MoveSet)
	{
		MoveSet = 0;

		float4 PlayerPosition = Player::MainPlayer->GetTransform()->GetLocalPosition() + float4{0, 40, 0};
		float4 Direct = PlayerPosition - StartPosition;
		DirectNormal = Direct.NormalizeReturn();
	}

	float MoveDist = 30.0f * _DeltaTime;

	float4 MoveDist4 = float4::Zero;
	float4 Correction = float4::Zero;

	Correction = GetTransform()->GetWorldRightVector().NormalizeReturn();
	GetTransform()->AddLocalPosition(DirectNormal * MoveSpeed * _DeltaTime);
}

void CoinAttack_Projectile::DeathCheck()
{
	float4 CurPos = GetTransform()->GetLocalPosition();

	if (StartPosition.x - 1100.0f >= CurPos.x)
	{
		Death();
	}
}
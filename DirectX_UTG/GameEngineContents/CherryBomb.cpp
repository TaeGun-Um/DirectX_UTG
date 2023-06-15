#include "PrecompileHeader.h"
#include "CherryBomb.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"
#include "MouseLevel.h"
#include "You_Died.h"
#include "CherryBomb_Fire.h"

CherryBomb::CherryBomb() 
{
}

CherryBomb::~CherryBomb() 
{
}

void CherryBomb::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "CherryBomb_Normal", .SpriteName = "CherryBomb_Normal", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "CherryBomb_Pink", .SpriteName = "CherryBomb_Pink", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "CherryBomb_Explode", .SpriteName = "CherryBomb_Explode", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("CherryBomb_Normal");
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

void CherryBomb::Update(float _DeltaTime)
{
	if (true == MouseLevel::MouseLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	if (true == IsParryProjectile)
	{
		IsParryProjectile = false;
		ParryCollisionPtr->On();
		RenderPtr->ChangeAnimation("CherryBomb_Pink");
	}

	MoveDirection(_DeltaTime);
	PixelCheck(_DeltaTime);
	CollisionCheck();
	DeathCheck();
}

void CherryBomb::MoveDirection(float _DeltaTime)
{
	if (true == IsDeath)
	{
		MoveDirect = float4::Zero;
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

	if (false == Directbool)
	{
		GetTransform()->AddLocalPosition({ -MoveDist, 0 });
	}
	else
	{
		GetTransform()->AddLocalPosition({ MoveDist, 0 });
	}

	GetTransform()->AddLocalPosition(MoveDirect * _DeltaTime);
}

void CherryBomb::CollisionCheck()
{
	if (nullptr != ParryCollisionPtr->Collision(static_cast<int>(CollisionOrder::PlayerParry), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		Player::MainPlayer->SetParryOn();
		Death();
	}
}

void CherryBomb::DeathCheck()
{
	if (true == IsDeath)
	{
		ProjectileCollisionPtr->Off();
		ProjectileCollisionRenderPtr->Off();
		ParryCollisionPtr->Off();
		ParryCollisionRenderPtr->Off();
		
		RenderPtr->GetTransform()->SetLocalPosition({0, 170});
		RenderPtr->ChangeAnimation("CherryBomb_Explode", false);
	}

	if (true == RenderPtr->IsAnimationEnd() && true == IsDeath)
	{
		Death();
	}
}

void CherryBomb::PixelCheck(float _DeltaTime)
{
	if (true == IsDeath)
	{
		return;
	}

	float4 ProjectilePos = GetTransform()->GetLocalPosition();
	float4 ExplodePos = ProjectilePos + float4{ -10, 0 };

	GameEnginePixelColor ExplodePixel = PixelCollisionCheck.PixelCheck(ExplodePos);

	if (true == PixelCollisionCheck.IsBlack(ExplodePixel))
	{
		IsDeath = true;
		CreateBombSFX();
	}
}

void CherryBomb::CreateBombSFX()
{
	std::shared_ptr<CherryBomb_Fire> Object = GetLevel()->CreateActor<CherryBomb_Fire>();
	std::shared_ptr<CherryBomb_Fire> Object2 = GetLevel()->CreateActor<CherryBomb_Fire>();

	float4 StartPosition = GetTransform()->GetWorldPosition();
	float4 LeftObjectPosition = StartPosition + float4{ 120, 65, 3 };
	float4 RightObjectPosition = StartPosition + float4{ -120, 65, 3 };

	Object->SetStartPosition(LeftObjectPosition);
	Object2->SetStartPosition(RightObjectPosition);
	Object2->SetDirectionNegative();
}
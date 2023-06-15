#include "PrecompileHeader.h"
#include "CherryBomb_Fire.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "MouseLevel.h"
#include "You_Died.h"

CherryBomb_Fire::CherryBomb_Fire() 
{
}

CherryBomb_Fire::~CherryBomb_Fire() 
{
}

void CherryBomb_Fire::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "CherryBomb_Fire_Intro", .SpriteName = "CherryBomb_Fire_Intro", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "CherryBomb_Fire_Loop", .SpriteName = "CherryBomb_Fire_Loop", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("CherryBomb_Fire_Intro");
	}

	if (nullptr == ProjectileCollisionPtr)
	{
		ProjectileCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
		ProjectileCollisionPtr->SetColType(ColType::SPHERE2D);
		ProjectileCollisionPtr->GetTransform()->SetLocalScale({ 15, 15, 1 });
		ProjectileCollisionPtr->GetTransform()->SetLocalPosition({ -110, -50 });
	}

	if (nullptr == ProjectileCollisionRenderPtr)
	{
		ProjectileCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ProjectileCollisionRenderPtr->SetTexture("GreenBox.png");
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalScale(ProjectileCollisionPtr->GetTransform()->GetLocalScale());
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalPosition(ProjectileCollisionPtr->GetTransform()->GetLocalPosition());
		ProjectileCollisionRenderPtr->Off();
	}
}

void CherryBomb_Fire::Update(float _DeltaTime)
{
	if (true == MouseLevel::MouseLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	if (true == RenderPtr->FindAnimation("CherryBomb_Fire_Intro")->IsEnd())
	{
		RenderPtr->ChangeAnimation("CherryBomb_Fire_Loop", false);
	}

	MoveDirection(_DeltaTime);
	DeathCheck();
}

void CherryBomb_Fire::MoveDirection(float _DeltaTime)
{
	float MoveDist = MoveSpeed * _DeltaTime;

	if (true == Directbool)
	{
		GetTransform()->AddLocalPosition({ -MoveDist, 0 });
	}
	else
	{
		GetTransform()->AddLocalPosition({ MoveDist, 0 });
	}
}

void CherryBomb_Fire::DeathCheck()
{
	float4 CurPos = GetTransform()->GetLocalPosition();

	if (true == Directbool && StartPosition.x - 1000.0f >= CurPos.x)
	{
		Death();
	}
	else if (false == Directbool && StartPosition.x + 1000.0f <= CurPos.x)
	{
		Death();
	}
}
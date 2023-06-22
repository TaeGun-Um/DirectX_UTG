#include "PrecompileHeader.h"
#include "SmallBall.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "MouseLevel.h"
#include "You_Died.h"

SmallBall::SmallBall() 
{
}

SmallBall::~SmallBall() 
{
}

void SmallBall::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "GhostBullet_Blue_Loop", .SpriteName = "GhostBullet_Blue_Loop", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = false });
		RenderPtr->CreateAnimation({ .AnimationName = "GhostBullet_Pink_Loop", .SpriteName = "GhostBullet_Pink_Loop", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = false });
		RenderPtr->GetTransform()->SetLocalScale({140, 110, 1});
		RenderPtr->ChangeAnimation("GhostBullet_Blue_Loop", false);
	}

	if (nullptr == ProjectileCollisionPtr)
	{
		ProjectileCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
		ProjectileCollisionPtr->SetColType(ColType::SPHERE2D);
		ProjectileCollisionPtr->GetTransform()->SetLocalScale({ 15, 15, 1 });
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

void SmallBall::Update(float _DeltaTime)
{
	if (true == MouseLevel::MouseLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	if (true == IsPink)
	{
		RenderPtr->ChangeAnimation("GhostBullet_Pink_Loop", false);
	}
	else
	{
		RenderPtr->ChangeAnimation("GhostBullet_Blue_Loop", false);
	}

	MoveDirection(_DeltaTime);
	DeathCheck();
}

void SmallBall::MoveDirection(float _DeltaTime)
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

void SmallBall::DeathCheck()
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
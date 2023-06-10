#include "PrecompileHeader.h"
#include "Platform_Tiger.h"

#include <cmath>

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"
#include "FrogLevel.h"
#include "You_Died.h"

Platform_Tiger::Platform_Tiger() 
{
}

Platform_Tiger::~Platform_Tiger() 
{
}

void Platform_Tiger::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Tiger_Platform", .SpriteName = "Tiger_Platform", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Tiger_Platform");
	}

	if (nullptr == BallRenderPtr)
	{
		BallRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BallRenderPtr->CreateAnimation({ .AnimationName = "Tiger_Ball", .SpriteName = "Tiger_Ball", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		BallRenderPtr->ChangeAnimation("Tiger_Ball");
	}

	if (nullptr == FrontRenderPtr)
	{
		FrontRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		FrontRenderPtr->SetScaleToTexture("Platform_Tiger_Front_001.png");
	}

	if (nullptr == PlatformCollisionPtr)
	{
		PlatformCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Platform));
		PlatformCollisionPtr->GetTransform()->SetLocalScale({ 200, 25, -1 });
		PlatformCollisionPtr->GetTransform()->SetLocalPosition({ 0, 20 });
	}

	if (nullptr == PlatformCollisionRenderPtr)
	{
		PlatformCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		PlatformCollisionRenderPtr->GetTransform()->SetLocalScale(PlatformCollisionPtr->GetTransform()->GetLocalScale());
		PlatformCollisionRenderPtr->GetTransform()->SetLocalPosition(PlatformCollisionPtr->GetTransform()->GetLocalPosition());
		PlatformCollisionRenderPtr->SetTexture("GreenBox.png");
		PlatformCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.6f;
	}

	if (nullptr == DebugRenderPtr)
	{
		DebugRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr->GetTransform()->AddLocalPosition({ 0, -70 });
		DebugRenderPtr->SetTexture("RedDot.png");
	}

	if (nullptr == HitCollisionPtr)
	{
		HitCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
		HitCollisionPtr->GetTransform()->SetLocalScale({ 150, 50, 1 });
		HitCollisionPtr->GetTransform()->SetLocalPosition({ 0, -20 });
	}

	if (nullptr == HitCollisionRenderPtr)
	{
		HitCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		HitCollisionRenderPtr->GetTransform()->SetLocalScale(HitCollisionPtr->GetTransform()->GetLocalScale());
		HitCollisionRenderPtr->GetTransform()->SetLocalPosition(HitCollisionPtr->GetTransform()->GetLocalPosition());
		HitCollisionRenderPtr->SetTexture("RedLine.png");
	}

	if (nullptr == BallCollisionPtr)
	{
		BallCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
		BallCollisionPtr->GetTransform()->SetLocalScale({ 50, 50, 1 });
		BallCollisionPtr->GetTransform()->SetLocalPosition(BallRenderPtr->GetTransform()->GetLocalPosition());
	}

	if (nullptr == BallCollisionRenderPtr)
	{
		BallCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BallCollisionRenderPtr->GetTransform()->SetLocalScale(BallCollisionPtr->GetTransform()->GetLocalScale());
		BallCollisionRenderPtr->GetTransform()->SetLocalPosition(BallCollisionPtr->GetTransform()->GetLocalPosition());
		BallCollisionRenderPtr->SetTexture("RedBox.png");
	}
}

void Platform_Tiger::Update(float _DeltaTime)
{
	if (true == FrogLevel::FrogLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	FrontSet();
	BallMoveDirection(_DeltaTime);
	PixelCheck(_DeltaTime);
	MoveDirection(_DeltaTime);
	DeathCheck();
}

void Platform_Tiger::BallMoveDirection(float _DeltaTime)
{
	BallBountTime += _DeltaTime;

	float MoveDis = abs(sinf(BallBountTime * 3.f) * 500.0f) - 45.0f;
	
	BallRenderPtr->GetTransform()->SetLocalPosition({ 0, MoveDis });
	BallCollisionPtr->GetTransform()->SetLocalPosition(BallRenderPtr->GetTransform()->GetLocalPosition());
	BallCollisionRenderPtr->GetTransform()->SetLocalPosition(BallCollisionPtr->GetTransform()->GetLocalPosition());
}

void Platform_Tiger::MoveDirection(float _DeltaTime)
{
	if (false == IsBoundEnd)
	{
		MoveDirect.y -= 1000.0f * _DeltaTime;

		GetTransform()->AddLocalPosition(MoveDirect * _DeltaTime);
	}
	else
	{
		MoveDirect.y = 0;
	}

	float MoveDis = 500.0f * _DeltaTime;

	CollisionCheck(MoveDis);

	GetTransform()->AddLocalPosition({ -MoveDis, 0 });
	GetTransform()->AddLocalPosition(MoveDirect * _DeltaTime);
}

void Platform_Tiger::CollisionCheck(float _Value)
{
	if (nullptr != PlatformCollisionPtr->Collision(static_cast<int>(CollisionOrder::PlayerSensor), ColType::AABBBOX2D, ColType::SPHERE2D))
	{
		Player::MainPlayer->SetBottomJumpBlock();

		if (true == Player::MainPlayer->GetPlatformCheckAble())
		{
			Player::MainPlayer->PlayerMoveDisturbance(-_Value);
		}
	}
	else
	{
		Player::MainPlayer->SetBottomJumpBlockOff();
	}
}

void Platform_Tiger::DeathCheck()
{
	float4 CurPos = GetTransform()->GetLocalPosition();

	if (StartPosition.x - 1300.0f >= CurPos.x)
	{
		Death();
	}
}

void Platform_Tiger::PixelCheck(float _DeltaTime)
{
	if (2 == BoundCount)
	{
		return;
	}

	float4 PlatformPos = GetTransform()->GetLocalPosition();
	float4 BoundPos = PlatformPos + float4{ 0, -70 };

	GameEnginePixelColor BoundPixel = PixelCollisionCheck.PixelCheck(BoundPos);

	BoundBufferTime += _DeltaTime;

	if (0.05f <= BoundBufferTime)
	{
		if (true == PixelCollisionCheck.IsBlack(BoundPixel) && 1 == BoundCount)
		{
			BoundBufferTime = 0.0f;

			MoveDirect.y = 0;
			IsBoundEnd = true;
			++BoundCount;
		}
		if (true == PixelCollisionCheck.IsBlack(BoundPixel) && 0 == BoundCount)
		{
			BoundBufferTime = 0.0f;

			MoveDirect.y = 0;
			MoveDirect.y += 150.0f;
			++BoundCount;
		}
	}
}

void Platform_Tiger::FrontSet()
{
	if (9 == RenderPtr->GetCurrentFrame())
	{
		FrontRenderPtr->SetScaleToTexture("Platform_Tiger_Front_010.png");
	}
	else if (8 == RenderPtr->GetCurrentFrame())
	{
		FrontRenderPtr->SetScaleToTexture("Platform_Tiger_Front_009.png");
	}
	else if (7 == RenderPtr->GetCurrentFrame())
	{
		FrontRenderPtr->SetScaleToTexture("Platform_Tiger_Front_008.png");
	}
	else if (6 == RenderPtr->GetCurrentFrame())
	{
		FrontRenderPtr->SetScaleToTexture("Platform_Tiger_Front_007.png");
	}
	else if (5 == RenderPtr->GetCurrentFrame())
	{
		FrontRenderPtr->SetScaleToTexture("Platform_Tiger_Front_006.png");
	}
	else if (4 == RenderPtr->GetCurrentFrame())
	{
		FrontRenderPtr->SetScaleToTexture("Platform_Tiger_Front_005.png");
	}
	else if (3 == RenderPtr->GetCurrentFrame())
	{
		FrontRenderPtr->SetScaleToTexture("Platform_Tiger_Front_004.png");
	}
	else if (2 == RenderPtr->GetCurrentFrame())
	{
		FrontRenderPtr->SetScaleToTexture("Platform_Tiger_Front_003.png");
	}
	else if (1 == RenderPtr->GetCurrentFrame())
	{
		FrontRenderPtr->SetScaleToTexture("Platform_Tiger_Front_002.png");
	}
	else if (0 == RenderPtr->GetCurrentFrame())
	{
		FrontRenderPtr->SetScaleToTexture("Platform_Tiger_Front_001.png");
	}
}
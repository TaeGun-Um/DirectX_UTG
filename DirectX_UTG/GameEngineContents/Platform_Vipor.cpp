#include "PrecompileHeader.h"
#include "Platform_Vipor.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"
#include "FrogLevel.h"
#include "You_Died.h"

Platform_Vipor::Platform_Vipor() 
{
}

Platform_Vipor::~Platform_Vipor() 
{
}

void Platform_Vipor::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Snake_Platform", .SpriteName = "Snake_Platform", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Snake_Platform");
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
		HitCollisionPtr->GetTransform()->SetLocalScale({ 130, 40, 1 });
		HitCollisionPtr->GetTransform()->SetLocalPosition({ 0, -20 });
	}

	if (nullptr == HitCollisionRenderPtr)
	{
		HitCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		HitCollisionRenderPtr->GetTransform()->SetLocalScale(HitCollisionPtr->GetTransform()->GetLocalScale());
		HitCollisionRenderPtr->GetTransform()->SetLocalPosition(HitCollisionPtr->GetTransform()->GetLocalPosition());
		HitCollisionRenderPtr->SetTexture("RedLine.png");
	}
}

void Platform_Vipor::Update(float _DeltaTime)
{
	if (true == FrogLevel::FrogLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	PixelCheck(_DeltaTime);
	MoveDirection(_DeltaTime);
	DeathCheck();
}

void Platform_Vipor::MoveDirection(float _DeltaTime)
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

void Platform_Vipor::CollisionCheck(float _Value)
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

void Platform_Vipor::DeathCheck()
{
	float4 CurPos = GetTransform()->GetLocalPosition();

	if (StartPosition.x - 1300.0f >= CurPos.x)
	{
		Death();
	}
}

void Platform_Vipor::PixelCheck(float _DeltaTime)
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
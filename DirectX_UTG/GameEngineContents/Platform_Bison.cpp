#include "PrecompileHeader.h"
#include "Platform_Bison.h"

#include <cmath>

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"
#include "FrogLevel.h"
#include "You_Died.h"

Platform_Bison::Platform_Bison() 
{
}

Platform_Bison::~Platform_Bison() 
{
}

void Platform_Bison::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Bison_Platform", .SpriteName = "Bison_Platform", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Bison_Platform");
	}

	//if (nullptr == FireRenderPtr)
	//{
	//	FireRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	//	FireRenderPtr->CreateAnimation({ .AnimationName = "Tiger_Ball", .SpriteName = "Tiger_Ball", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	//	FireRenderPtr->ChangeAnimation("Tiger_Ball");
	//}

	if (nullptr == FrontRenderPtr)
	{
		FrontRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		FrontRenderPtr->SetScaleToTexture("Platform_Bison_Front_001.png");
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

	//if (nullptr == FireCollisionPtr)
	//{
	//	FireCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
	//	FireCollisionPtr->GetTransform()->SetLocalScale({ 50, 50, 1 });
	//	//FireCollisionPtr->GetTransform()->SetLocalPosition(FrontRenderPtr->GetTransform()->GetLocalPosition());
	//}

	//if (nullptr == FireCollisionRenderPtr)
	//{
	//	FireCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	//	FireCollisionRenderPtr->GetTransform()->SetLocalScale(FireCollisionPtr->GetTransform()->GetLocalScale());
	//	FireCollisionRenderPtr->GetTransform()->SetLocalPosition(FireCollisionPtr->GetTransform()->GetLocalPosition());
	//	FireCollisionRenderPtr->SetTexture("RedBox.png");
	//}
}

void Platform_Bison::Update(float _DeltaTime)
{
	if (true == FrogLevel::FrogLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	FrontSet();
	//FireChage(_DeltaTime);
	MoveDirection(_DeltaTime);
	DeathCheck();
}

//void Platform_Bison::FireChage(float _DeltaTime)
//{
//	BallBountTime += _DeltaTime;
//
//	float MoveDis = abs(sinf(BallBountTime * 3.f) * 500.0f) - 45.0f;
//
//	BallRenderPtr->GetTransform()->SetLocalPosition({ 0, MoveDis });
//	BallCollisionPtr->GetTransform()->SetLocalPosition(BallRenderPtr->GetTransform()->GetLocalPosition());
//	BallCollisionRenderPtr->GetTransform()->SetLocalPosition(BallCollisionPtr->GetTransform()->GetLocalPosition());
//}

void Platform_Bison::MoveDirection(float _DeltaTime)
{
	WaveTime += _DeltaTime;

	float MoveDisX = 500.0f * _DeltaTime;
	float MoveDisY = (sinf(WaveTime * 3.f) * 50.0f) + 240.0f;

	CollisionCheck(MoveDisX);

	GetTransform()->AddLocalPosition({ -MoveDisX, 0 });

	if (MoveDisY >= 280.0f)
	{
		IsWaveEnd = true;
	}

	if (false == IsWaveEnd)
	{
		float4 CurPos1 = GetTransform()->GetLocalPosition();

		GetTransform()->SetLocalPosition({ CurPos1.x, MoveDisY });
	}
	else
	{
		float MoveDisY_samll = (sinf(WaveTime * 18.f) * (25.0f - (WaveTime * 36.f))) + 280.0f;

		if (0.0f >= (WaveTime * 18.f) * (25.0f - (WaveTime * 36.f)))
		{
			MoveDisY = 0.0f;
			MoveDisY_samll = 0.0f;
			return;
		}
		else
		{
			float4 CurPos1 = GetTransform()->GetLocalPosition();

			GetTransform()->SetLocalPosition({ CurPos1.x, MoveDisY_samll });
		}
	}
}

void Platform_Bison::CollisionCheck(float _Value)
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

void Platform_Bison::DeathCheck()
{
	float4 CurPos = GetTransform()->GetLocalPosition();

	if (StartPosition.x - 1300.0f >= CurPos.x)
	{
		Death();
	}
}

void Platform_Bison::FrontSet()
{
	if (9 == RenderPtr->GetCurrentFrame())
	{
		FrontRenderPtr->SetScaleToTexture("Platform_Bison_Front_010.png");
	}
	else if (8 == RenderPtr->GetCurrentFrame())
	{
		FrontRenderPtr->SetScaleToTexture("Platform_Bison_Front_009.png");
	}
	else if (7 == RenderPtr->GetCurrentFrame())
	{
		FrontRenderPtr->SetScaleToTexture("Platform_Bison_Front_008.png");
	}
	else if (6 == RenderPtr->GetCurrentFrame())
	{
		FrontRenderPtr->SetScaleToTexture("Platform_Bison_Front_007.png");
	}
	else if (5 == RenderPtr->GetCurrentFrame())
	{
		FrontRenderPtr->SetScaleToTexture("Platform_Bison_Front_006.png");
	}
	else if (4 == RenderPtr->GetCurrentFrame())
	{
		FrontRenderPtr->SetScaleToTexture("Platform_Bison_Front_005.png");
	}
	else if (3 == RenderPtr->GetCurrentFrame())
	{
		FrontRenderPtr->SetScaleToTexture("Platform_Bison_Front_004.png");
	}
	else if (2 == RenderPtr->GetCurrentFrame())
	{
		FrontRenderPtr->SetScaleToTexture("Platform_Bison_Front_003.png");
	}
	else if (1 == RenderPtr->GetCurrentFrame())
	{
		FrontRenderPtr->SetScaleToTexture("Platform_Bison_Front_002.png");
	}
	else if (0 == RenderPtr->GetCurrentFrame())
	{
		FrontRenderPtr->SetScaleToTexture("Platform_Bison_Front_001.png");
	}
}
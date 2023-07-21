#include "PrecompileHeader.h"
#include "Platform_Bison.h"

#include <cmath>

#include <GameEngineBase/GameEngineRandom.h>
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

	if (nullptr == FireRenderPtr)
	{
		FireRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		FireRenderPtr->CreateAnimation({ .AnimationName = "Bison_Flame_Small_Loop", .SpriteName = "Bison_Flame_Small_Loop", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		FireRenderPtr->CreateAnimation({ .AnimationName = "Bison_Flame_Large_Intro", .SpriteName = "Bison_Flame_Large_Intro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		FireRenderPtr->CreateAnimation({ .AnimationName = "Bison_Flame_Large_Loop", .SpriteName = "Bison_Flame_Large_Loop", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		FireRenderPtr->GetTransform()->AddLocalPosition({ 0, 50 });
		FireRenderPtr->ChangeAnimation("Bison_Flame_Small_Loop");

		FireRenderPtr->SetAnimationStartEvent("Bison_Flame_Large_Intro", 1, std::bind(&Platform_Bison::FireSound, this));
	}

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

	if (nullptr == FireCollisionPtr)
	{
		FireCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
		FireCollisionPtr->GetTransform()->SetLocalScale({ 40, 500, 1 });
		FireCollisionPtr->GetTransform()->AddLocalPosition({ 0, 250 });
		FireCollisionPtr->Off();
	}

	if (nullptr == FireCollisionRenderPtr)
	{
		FireCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		FireCollisionRenderPtr->GetTransform()->SetLocalScale(FireCollisionPtr->GetTransform()->GetLocalScale());
		FireCollisionRenderPtr->GetTransform()->SetLocalPosition(FireCollisionPtr->GetTransform()->GetLocalPosition());
		FireCollisionRenderPtr->SetTexture("RedLine.png");
		FireCollisionRenderPtr->Off();
	}
}

void Platform_Bison::Update(float _DeltaTime)
{
	if (true == FrogLevel::FrogLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	FireChage(_DeltaTime);
	FrontSet();
	MoveDirection(_DeltaTime);
	DeathCheck();
}

void Platform_Bison::FireSound()
{
	if (true == Player::MainPlayer->GetIsPlayerDeath())
	{
		return;
	}

	int RandC = GameEngineRandom::MainRandom.RandomInt(0, 3);

	if (0 == RandC)
	{
		EffectPlayer = GameEngineSound::Play("frogs_flame_platform_fire_burst_01.wav");
	}
	else if (1 == RandC)
	{
		EffectPlayer = GameEngineSound::Play("frogs_flame_platform_fire_burst_02.wav");
	}
	else if (2 == RandC)
	{
		EffectPlayer = GameEngineSound::Play("frogs_flame_platform_fire_burst_03.wav");
	}
	else if (3 == RandC)
	{
		EffectPlayer = GameEngineSound::Play("frogs_flame_platform_fire_burst_04.wav");
	}
}

void Platform_Bison::FireChage(float _DeltaTime)
{
	FireChangeTime += _DeltaTime;

	if (1.0f <= FireChangeTime)
	{
		return;
	}

	if (FireRenderPtr->IsAnimationEnd() && false == FireEnd2 && true == FireEnd1)
	{
		FireEnd2 = true;
		FireRenderPtr->ChangeAnimation("Bison_Flame_Large_Loop");
	}
	else if (FireRenderPtr->IsAnimationEnd() && false == FireEnd1)
	{
		FireEnd1 = true;
		FireRenderPtr->ChangeAnimation("Bison_Flame_Large_Intro");
	}

	if (false == FireEnd2 && true == FireEnd1)
	{
		if (true == Directbool)
		{
			if (3 == FireRenderPtr->GetCurrentFrame())
			{
				FireRenderPtr->GetTransform()->SetLocalPosition({ 0, 270 });
				FireCollisionPtr->On();
			}
			else if (2 == FireRenderPtr->GetCurrentFrame())
			{
				FireRenderPtr->GetTransform()->SetLocalPosition({ 0, 270 });
				FireCollisionPtr->On();
			}
			else if (1 == FireRenderPtr->GetCurrentFrame())
			{
				FireRenderPtr->GetTransform()->SetLocalPosition({ 0, 370 });
			}
			else if (0 == FireRenderPtr->GetCurrentFrame())
			{
				FireRenderPtr->GetTransform()->SetLocalPosition({ 0, 370 });
			}
		}
		else
		{
			if (3 == FireRenderPtr->GetCurrentFrame())
			{
				FireRenderPtr->GetTransform()->SetLocalPosition({ 0, -320 });
				FireCollisionPtr->On();
			}
			else if (2 == FireRenderPtr->GetCurrentFrame())
			{
				FireRenderPtr->GetTransform()->SetLocalPosition({ 0, -320 });
				FireCollisionPtr->On();
			}
			else if (0 == FireRenderPtr->GetCurrentFrame())
			{
				FireRenderPtr->GetTransform()->SetLocalPosition({ 0, -420 });
			}
			else if (1 == FireRenderPtr->GetCurrentFrame())
			{
				FireRenderPtr->GetTransform()->SetLocalPosition({ 0, -420 });
			}
		}
	}
}

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
		float MoveDisY_samll = (sinf(WaveTime * 10.f) * (25.0f - (WaveTime * 30.f))) + 280.0f;

		if (0.0f >= (WaveTime * 10.f) * (25.0f - (WaveTime * 30.f)))
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


	FireCollisionRenderPtr->GetTransform()->SetLocalScale(FireCollisionPtr->GetTransform()->GetLocalScale());
	FireCollisionRenderPtr->GetTransform()->SetLocalPosition(FireCollisionPtr->GetTransform()->GetLocalPosition());
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
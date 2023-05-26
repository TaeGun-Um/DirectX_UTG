#include "PrecompileHeader.h"
#include "AppleTraveller.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"

AppleTraveller::AppleTraveller() 
{
}

AppleTraveller::~AppleTraveller() 
{
}

void AppleTraveller::Start()
{
	NPCLoad(NPCValue::AppleTraveller);
	InitRenderSetting();
	InitCollisionSetting();
}
void AppleTraveller::Update(float _DeltaTime)
{
	CollisionCheck(CollisionPtr);

	if (false == WaveInit)
	{
		WaveAcc += _DeltaTime;
	}

	if (false == WaveInit && WaveAcc >= 30.0f)
	{
		WaveCollisionPtr->On();
		WaveCollisionRenderPtr->On();
	}

	if (nullptr != WaveCollisionPtr->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		WaveInit = true;
		WaveCollisionPtr->Off();
		WaveCollisionRenderPtr->Off();
	}

	if (true == WaveInit)
	{
		if (WaveTime <= 1.0f)
		{
			if (false == IsWave)
			{
				WaveEnd = false;
				RenderPtr->ChangeAnimation("AppleTraveller_Wave_Intro", false);
			}

			if (true == RenderPtr->IsAnimationEnd())
			{
				IsWave = true;
				RenderPtr->ChangeAnimation("AppleTraveller_Wave");
			}
		}

		if (true == IsWave)
		{
			WaveTime += _DeltaTime;
		}

		if (WaveTime >= 3.0f && WaveEnd == false)
		{
			IsWave = false;
			RenderPtr->ChangeAnimation("AppleTraveller_Wave_Outro", false);

			if (true == RenderPtr->IsAnimationEnd())
			{
				WaveEnd = true;
				WaveInit = false;
				WaveTime = 0.0f;
				WaveAcc = 0.0f;
				RenderPtr->ChangeAnimation("AppleTraveller_Idle");
			}
		}
	}
	else
	{
		BlinkTime += _DeltaTime;

		if (5 == RenderPtr->GetCurrentFrame() && BlinkTime >= 3.0f)
		{
			IsBlink = true;
		}

		if (true == IsBlink)
		{
			RenderPtr->ChangeAnimation("AppleTraveller_Blink", false);

			if (true == RenderPtr->IsAnimationEnd())
			{
				BlinkTime = 0.0f;
				IsBlink = false;
				RenderPtr->ChangeAnimation("AppleTraveller_Idle");
				RenderPtr->FindAnimation("AppleTraveller_Idle")->CurFrame = 5;
			}
		}
	}
}

void AppleTraveller::InitRenderSetting()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr == AssitantRenderPtr)
	{
		AssitantRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr != RenderPtr)
	{
		RenderPtr->CreateAnimation({ .AnimationName = "AppleTraveller_Blink", .SpriteName = "AppleTraveller_Blink", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "AppleTraveller_Idle", .SpriteName = "AppleTraveller_Idle", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "AppleTraveller_Wave", .SpriteName = "AppleTraveller_Wave", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "AppleTraveller_Wave_Intro", .SpriteName = "AppleTraveller_Wave_Intro", .FrameInter = 0.09f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "AppleTraveller_Wave_Outro", .SpriteName = "AppleTraveller_Wave_Outro", .FrameInter = 0.09f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("AppleTraveller_Idle");
		RenderPtr->CameraCullingOn();
	}

	if (nullptr != AssitantRenderPtr)
	{
		AssitantRenderPtr->CreateAnimation({ .AnimationName = "AppleTraveller_HoboStick", .SpriteName = "AppleTraveller_HoboStick", .FrameInter = 0.1f, .ScaleToTexture = true });
		AssitantRenderPtr->GetTransform()->SetLocalPosition({ 40, -40 });
		AssitantRenderPtr->ChangeAnimation("AppleTraveller_HoboStick");
	}
}

void AppleTraveller::InitCollisionSetting()
{
	if (nullptr == CollisionRenderPtr)
	{
		CollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr == CollisionPtr)
	{
		CollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::NPC));
	}

	if (nullptr == WaveCollisionRenderPtr)
	{
		WaveCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr == WaveCollisionPtr)
	{
		WaveCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::NPC));
	}

	if (nullptr != CollisionPtr)
	{
		CollisionPtr->GetTransform()->SetLocalScale({ 50, 50, 1 });
		CollisionPtr->GetTransform()->SetLocalPosition({ 0, 0, -17 });
	}

	if (nullptr != CollisionRenderPtr)
	{
		CollisionRenderPtr->SetTexture("GreenLine.png");
		CollisionRenderPtr->GetTransform()->SetLocalScale(CollisionPtr->GetTransform()->GetLocalScale());
		CollisionRenderPtr->GetTransform()->SetLocalPosition(CollisionPtr->GetTransform()->GetLocalPosition());
	}

	if (nullptr != WaveCollisionPtr)
	{
		WaveCollisionPtr->GetTransform()->SetLocalScale({ 950, 500, 1 });
		WaveCollisionPtr->GetTransform()->SetLocalPosition({ 0, 0, -17 });
	}

	if (nullptr != WaveCollisionRenderPtr)
	{
		WaveCollisionRenderPtr->SetTexture("BlueLine.png");
		WaveCollisionRenderPtr->GetTransform()->SetLocalScale(WaveCollisionPtr->GetTransform()->GetLocalScale());
		WaveCollisionRenderPtr->GetTransform()->SetLocalPosition(WaveCollisionPtr->GetTransform()->GetLocalPosition());
		WaveCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.5f;
	}
}
#include "PrecompileHeader.h"
#include "Coin.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Coin::Coin() 
{
}

Coin::~Coin() 
{
}

void Coin::Start()
{
	NPCLoad(NPCValue::Coin);
	InitRenderSetting();
	InitCollisionSetting();
}
void Coin::Update(float _DeltaTime)
{
	CollisionCheck(CollisionPtr);

	TransitionTime += _DeltaTime;

	if (TransitionTime >= 1.0f)
	{
		if (1 == Count1)
		{
			Count1 = 0;
			RenderPtr->ChangeAnimation("Coin_Transition_A");
		}

		if (1 == Count2 && RenderPtr->FindAnimation("Coin_Transition_A")->IsEnd())
		{
			Count2 = 0;
			RenderPtr->ChangeAnimation("Coin_Hold_A");
		}

		if (0 == Count2)
		{
			EyeTime += _DeltaTime;
		}

		if (1 == Count3 && 1.0f <= EyeTime)
		{
			Count3 = 0;
			RenderPtr->ChangeAnimation("Coin_Transition_B");
		}

		if (1 == Count4 && RenderPtr->FindAnimation("Coin_Transition_B")->IsEnd())
		{
			Count4 = 0;
			RenderPtr->ChangeAnimation("Coin_Hold_B");
		}

		if (0 == Count4)
		{
			WaitTime1 += _DeltaTime;
		}

		if (1 == Count5 && 1.0f <= WaitTime1)
		{
			Count5 = 0;
			RenderPtr->ChangeAnimation("Coin_Transition_D");
		}

		if (1 == Count6 && RenderPtr->FindAnimation("Coin_Transition_D")->IsEnd())
		{
			Count6 = 0;
			RenderPtr->ChangeAnimation("Coin_Hold_C");
		}

		if (1 == Count6 && RenderPtr->FindAnimation("Coin_Transition_D")->IsEnd())
		{
			Count6 = 0;
			RenderPtr->ChangeAnimation("Coin_Hold_C");
		}

		if (0 == Count6)
		{
			WaitTime2 += _DeltaTime;
		}

		if (1 == Count7 && 1.0f <= WaitTime2)
		{
			Count7 = 0;
			RenderPtr->ChangeAnimation("Coin_Transition_E");
		}

		if (1 == Count8 && RenderPtr->FindAnimation("Coin_Transition_E")->IsEnd())
		{
			Count8 = 0;
			RenderPtr->ChangeAnimation("Coin_Hold_D");
		}

		if (0 == Count8)
		{
			WaitTime3 += _DeltaTime;
		}

		if (1 == Count9 && 1.0f <= WaitTime3)
		{
			Count9 = 0;
			RenderPtr->ChangeAnimation("Coin_Transition_F");
		}

		if (1 == Count10 && RenderPtr->FindAnimation("Coin_Transition_F")->IsEnd())
		{
			TransitionTime = 0.0f;
			EyeTime = 0.0f;
			WaitTime1 = 0.0f;
			WaitTime2 = 0.0f;
			WaitTime3 = 0.0f;

			Count1 = 1;
			Count2 = 1;
			Count3 = 1;
			Count4 = 1;
			Count5 = 1;
			Count6 = 1;
			Count7 = 1;
			Count8 = 1;
			Count9 = 1;
			Count10 = 1;

			RenderPtr->ChangeAnimation("Coin_Boil_A");
		}
	}
}

void Coin::InitRenderSetting()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr != RenderPtr)
	{
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Blink", .SpriteName = "Coin_Blink", .FrameInter = 0.09f, .ScaleToTexture = true });

		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Boil_A", .SpriteName = "Coin_Boil_A", .FrameInter = 0.09f, .ScaleToTexture = true });

		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Hold_A", .SpriteName = "Coin_Hold_A", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Hold_B", .SpriteName = "Coin_Hold_B", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Hold_C", .SpriteName = "Coin_Hold_C", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Hold_D", .SpriteName = "Coin_Hold_D", .FrameInter = 0.09f, .ScaleToTexture = true });

		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Transition_A", .SpriteName = "Coin_Transition_A", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Transition_B", .SpriteName = "Coin_Transition_B", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Transition_C", .SpriteName = "Coin_Transition_C", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Transition_D", .SpriteName = "Coin_Transition_D", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Transition_E", .SpriteName = "Coin_Transition_E", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Transition_F", .SpriteName = "Coin_Transition_F", .FrameInter = 0.09f, .ScaleToTexture = true });
		
		RenderPtr->ChangeAnimation("Coin_Boil_A");
	}
}

void Coin::InitCollisionSetting()
{
	if (nullptr == CollisionRenderPtr)
	{
		CollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr == CollisionPtr)
	{
		CollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::NPC));
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
}
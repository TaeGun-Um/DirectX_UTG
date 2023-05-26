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
		if (false == TransA)
		{
			RenderPtr->ChangeAnimation("Coin_Transition_A", false);
		}

		if (RenderPtr->IsAnimationEnd() && false == TransA)
		{
			TransA = true;
		}

		if (true == TransA && false == Set1)
		{
			EyeTime += _DeltaTime;
			RenderPtr->ChangeAnimation("Coin_Hold_A", false);
		}

		if (true == TransA)
		{
			EyeTime += _DeltaTime;
		}

		if (RenderPtr->IsAnimationEnd() && false == Set1)
		{
			Set1 = true;
		}

		if (EyeTime >= 1.0f && false == TransB)
		{
			RenderPtr->ChangeAnimation("Coin_Transition_B", false);
		}

		if (RenderPtr->IsAnimationEnd() && EyeTime >= 2.8f && false == TransB)
		{
			TransB = true;
		}

		if (true == TransB && Count == 1)
		{
			Count = 0;
			RenderPtr->ChangeAnimation("Coin_Hold_B", true);
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
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Boil_B", .SpriteName = "Coin_Boil_B", .FrameInter = 0.09f, .ScaleToTexture = true });

		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Hold_A", .SpriteName = "Coin_Hold_A", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Hold_B", .SpriteName = "Coin_Hold_B", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Hold_C", .SpriteName = "Coin_Hold_C", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Hold_D", .SpriteName = "Coin_Hold_D", .FrameInter = 0.09f, .ScaleToTexture = true });

		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Transition_A", .SpriteName = "Coin_Transition_A", .FrameInter = 0.09f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Transition_B", .SpriteName = "Coin_Transition_B", .FrameInter = 0.09f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Transition_C", .SpriteName = "Coin_Transition_C", .FrameInter = 0.09f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Transition_D", .SpriteName = "Coin_Transition_D", .FrameInter = 0.09f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Transition_E", .SpriteName = "Coin_Transition_E", .FrameInter = 0.09f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Transition_F", .SpriteName = "Coin_Transition_F", .FrameInter = 0.09f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Transition_G", .SpriteName = "Coin_Transition_G", .FrameInter = 0.09f, .Loop = false, .ScaleToTexture = true });
		
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
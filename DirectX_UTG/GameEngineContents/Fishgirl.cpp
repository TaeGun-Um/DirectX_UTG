#include "PrecompileHeader.h"
#include "Fishgirl.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Fishgirl::Fishgirl() 
{
}

Fishgirl::~Fishgirl() 
{
}

void Fishgirl::Start()
{
	NPCLoad(NPCValue::FishGirl);
	InitRenderSetting();
	InitCollisionSetting();
}
void Fishgirl::Update(float _DeltaTime)
{
	CollisionCheck(CollisionPtr);

	BlinkTime += _DeltaTime;

	if (4 == RenderPtr->GetCurrentFrame() && BlinkTime >= 3.0f)
	{
		IsBlink = true;
	}

	if (true == IsBlink)
	{
		RenderPtr->ChangeAnimation("FishGirl_Blink", false);

		if (true == RenderPtr->IsAnimationEnd())
		{
			BlinkTime = 0.0f;
			IsBlink = false;
			RenderPtr->ChangeAnimation("FishGirl_Idle");
		}
	}
}

void Fishgirl::InitRenderSetting()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr != RenderPtr)
	{
		RenderPtr->CreateAnimation({ .AnimationName = "FishGirl_Idle", .SpriteName = "FishGirl_Idle", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "FishGirl_Blink", .SpriteName = "FishGirl_Blink", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("FishGirl_Idle");
	}
}

void Fishgirl::InitCollisionSetting()
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
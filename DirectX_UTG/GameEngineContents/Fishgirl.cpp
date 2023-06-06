#include "PrecompileHeader.h"
#include "Fishgirl.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player_Overworld.h"
#include "NPC_TextBox.h"

Fishgirl* Fishgirl::FishgirlPtr = nullptr;

Fishgirl::Fishgirl() 
{
}

Fishgirl::~Fishgirl() 
{
}

void Fishgirl::Start()
{
	FishgirlPtr = this;
	NPCLoad(NPCValue::FishGirl);
	InitRenderSetting();
	InitCollisionSetting();
}

void Fishgirl::Update(float _DeltaTime)
{
	CollisionCheck(CollisionPtr);
	AnimationLoop(_DeltaTime);

	if (true == CreateBox)
	{
		TextBoxOn(_DeltaTime);
	}
}

void Fishgirl::TextBoxOn(float _DeltaTime)
{
	NPC_TextBoxRender->On();

	BoxInterActionDelayTime += _DeltaTime;

	if (0.5f >= BoxInterActionDelayTime)
	{
		return;
	}

	if (true == GameEngineInput::IsDown("Attack"))
	{
		CreateBox = false;
		Player_Overworld::MainPlayer->PlayerCollisionPtrOn();
		Player_Overworld::MainPlayer->SetIsPortalingfalse();
		NPC_TextBoxRender->Off();
		BoxInterActionDelayTime = 0.0f;
	}
}

void Fishgirl::AnimationLoop(float _DeltaTime)
{
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
		RenderPtr->CameraCullingOn();
	}

	NPC_TextBoxRender = GetLevel()->CreateActor<NPC_TextBox>();
	NPC_TextBoxRender->LocalPositionSetting(RenderPtr->GetTransform()->GetLocalPosition());
	NPC_TextBoxRender->Off();
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
		CollisionPtr->GetTransform()->SetLocalScale({ 60, 60, 1 });
		CollisionPtr->GetTransform()->SetLocalPosition({ 25, 35, -17 });
	}

	if (nullptr != CollisionRenderPtr)
	{
		CollisionRenderPtr->SetTexture("GreenLine.png");
		CollisionRenderPtr->GetTransform()->SetLocalScale(CollisionPtr->GetTransform()->GetLocalScale());
		CollisionRenderPtr->GetTransform()->SetLocalPosition(CollisionPtr->GetTransform()->GetLocalPosition());
	}
}
#include "PrecompileHeader.h"
#include "Axeman.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player_Overworld.h"
#include "NPC_TextBox.h"

Axeman* Axeman::AxemanPtr = nullptr;

Axeman::Axeman() 
{
}

Axeman::~Axeman() 
{
}

void Axeman::Start()
{
	AxemanPtr = this;
	NPCLoad(NPCValue::Axeman);
	InitRenderSetting();
	InitCollisionSetting();
}
void Axeman::Update(float _DeltaTime)
{
	CollisionCheck(CollisionPtr);

	if (true == CreateBox)
	{
		TextBoxOn(_DeltaTime);
	}
}

void Axeman::TextBoxOn(float _DeltaTime)
{
	NPC_TextBoxRender->On();

	BoxInterActionDelayTime += _DeltaTime;

	if (0.5f >= BoxInterActionDelayTime)
	{
		return;
	}

	if (true == GameEngineInput::IsDown("Attack") && TextEndCount > TextCount && false == NextStep)
	{
		NextStep = true;
		++TextCount;
	}
	else if (true == GameEngineInput::IsDown("Attack") && TextEndCount <= TextCount && false == NextStep)
	{
		TextCount = 0;
		CreateBox = false;
		Player_Overworld::MainPlayer->PlayerCollisionPtrOn();
		Player_Overworld::MainPlayer->SetIsPortalingfalse();
		NPC_TextBoxRender->Off();
		BoxInterActionDelayTime = 0.0f;
	}

	if (true == NextStep)
	{
		if (true == NPC_TextBoxRender->RenderAlphaSetting(_DeltaTime))
		{
			NextStep = false;
			NPC_TextBoxRender->BoxReset();
		}
	}
}

void Axeman::InitRenderSetting()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr != RenderPtr)
	{
		RenderPtr->CreateAnimation({ .AnimationName = "Axeman_Idle", .SpriteName = "Axeman_Idle", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Axeman_Idle");
		RenderPtr->CameraCullingOn();
	}

	NPC_TextBoxRender = GetLevel()->CreateActor<NPC_TextBox>();
	NPC_TextBoxRender->Off();
}

void Axeman::InitCollisionSetting()
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
		CollisionPtr->GetTransform()->SetLocalPosition({ 0, 0, -17 });
	}

	if (nullptr != CollisionRenderPtr)
	{
		CollisionRenderPtr->SetTexture("GreenLine.png");
		CollisionRenderPtr->GetTransform()->SetLocalScale(CollisionPtr->GetTransform()->GetLocalScale());
		CollisionRenderPtr->GetTransform()->SetLocalPosition(CollisionPtr->GetTransform()->GetLocalPosition());
	}
}
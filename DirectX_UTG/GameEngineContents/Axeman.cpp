#include "PrecompileHeader.h"
#include "Axeman.h"

#include <GameEngineCore/GameEngineFontRenderer.h>
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
		FontRender->On();
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

	if (true == GameEngineInput::IsDown("Attack") && false == NextStep)
	{
		NextStep = true;
		++TextCount;

		if (TextEndCount > TextCount)
		{
			FontRender->SetText(NPCScript[TextCount]);
		}
		else if (TextEndCount <= TextCount)
		{
			TextCount = 0;
			CreateBox = false;
			NextStep = false;
			Player_Overworld::MainPlayer->PlayerCollisionPtrOn();
			Player_Overworld::MainPlayer->SetIsPortalingfalse();
			NPC_TextBoxRender->Off();
			BoxInterActionDelayTime = 0.0f;
			FontRender->Off();
			FontRender->SetText(NPCScript[0]);
		}
	}

	if (true == NextStep)
	{
		if (true == NPC_TextBoxRender->RenderAlphaSetting(FontRender, _DeltaTime))
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

void Axeman::ScriptInit()
{
	FontRender = CreateComponent<GameEngineFontRenderer>();

	FontRender->SetFont("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");
	FontRender->SetScale(20.0f);
	FontRender->SetColor(float4::Black);

	FontRender->GetTransform()->SetWorldPosition(NPC_TextBoxRender->GetBoxCurPosition());

	TextEndCount = 4;

	NPCScript.resize(TextEndCount);

	{
		NPCScript[0] = "Say, fellas. thanks for settling things down around here.";
		NPCScript[1] = "Maybe now ican collect cnough dough to pay for my chipped balde.";
		NPCScript[2] = "Speakin' of which... i should get back to work.";
		NPCScript[3] = "Gatta make hay while the sun shines!";
	}

	FontRender->SetText(NPCScript[0]);
	FontRender->Off();
}
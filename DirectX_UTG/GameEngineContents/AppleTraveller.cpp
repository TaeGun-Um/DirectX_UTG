#include "PrecompileHeader.h"
#include "AppleTraveller.h"

#include <GameEngineCore/GameEngineFont.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player_Overworld.h"
#include "NPC_TextBox.h"

AppleTraveller* AppleTraveller::AppleTravellerPtr = nullptr;

AppleTraveller::AppleTraveller() 
{
}

AppleTraveller::~AppleTraveller() 
{
}

void AppleTraveller::Start()
{
	AppleTravellerPtr = this;
	NPCLoad(NPCValue::AppleTraveller);
	InitRenderSetting();
	InitCollisionSetting();
}
void AppleTraveller::Update(float _DeltaTime)
{
	CollisionCheck(CollisionPtr);
	AnimationLoop(_DeltaTime);

	if (true == CreateBox)
	{
		TextBoxOn(_DeltaTime);
	}
}

void AppleTraveller::TextBoxOn(float _DeltaTime)
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

		int SetCount = TextCount - 1;

		if (SetCount > 0)
		{
			NPCScript[TextCount - 1]->Off();
		}
		
		NPCScript[TextCount]->On();

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

		int SetCount = TextCount - 1;

		if (SetCount > 0)
		{
			NPCScript[TextCount - 1]->Off();
		}

		NPCScript[TextCount]->On();
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

void AppleTraveller::AnimationLoop(float _DeltaTime)
{
	if (false == WaveInit)
	{
		WaveAcc += _DeltaTime;
	}

	if (false == WaveInit && WaveAcc >= 30.0f)
	{
		WaveCollisionPtr->On();
	}

	if (nullptr != WaveCollisionPtr->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		WaveInit = true;
		WaveCollisionPtr->Off();
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

	NPC_TextBoxRender = GetLevel()->CreateActor<NPC_TextBox>();
	NPC_TextBoxRender->Off();
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
		CollisionPtr->GetTransform()->SetLocalScale({ 60, 60, 1 });
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

void AppleTraveller::ScriptInit()
{
	GameEngineFont::Load("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");

	TextRenderPtr = GetLevel()->CreateActor<NPC_TextBox>();

	std::shared_ptr<GameEngineFontRenderer> FontRender0 = TextRenderPtr->CreateComponent<GameEngineFontRenderer>();
	std::shared_ptr<GameEngineFontRenderer> FontRender1 = TextRenderPtr->CreateComponent<GameEngineFontRenderer>();
	std::shared_ptr<GameEngineFontRenderer> FontRender2 = TextRenderPtr->CreateComponent<GameEngineFontRenderer>();
	std::shared_ptr<GameEngineFontRenderer> FontRender3 = TextRenderPtr->CreateComponent<GameEngineFontRenderer>();
	std::shared_ptr<GameEngineFontRenderer> FontRender4 = TextRenderPtr->CreateComponent<GameEngineFontRenderer>();

	FontRender0->SetFont("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");
	FontRender1->SetFont("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");
	FontRender2->SetFont("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");
	FontRender3->SetFont("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");
	FontRender4->SetFont("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");

	FontRender0->SetText("¾È³çÇÏ¼¼¿ä.");
	FontRender1->SetText("¹Ý°©½À´Ï´Ù.");
	FontRender2->SetText("Ã³À½ºË°Ú½À´Ï´Ù.");
	FontRender3->SetText("È£È£È£È£");
	FontRender4->SetText("ÇÏÇÏÇÏ");

	FontRender0->SetScale(10.0f);
	FontRender1->SetScale(10.0f);
	FontRender2->SetScale(10.0f);
	FontRender3->SetScale(10.0f);
	FontRender4->SetScale(10.0f);

	FontRender0->GetTransform()->SetLocalPosition(NPC_TextBoxRender->GetTransform()->GetWorldPosition());
	FontRender1->GetTransform()->SetLocalPosition(NPC_TextBoxRender->GetTransform()->GetWorldPosition());
	FontRender2->GetTransform()->SetLocalPosition(NPC_TextBoxRender->GetTransform()->GetWorldPosition());
	FontRender3->GetTransform()->SetLocalPosition(NPC_TextBoxRender->GetTransform()->GetWorldPosition());
	FontRender4->GetTransform()->SetLocalPosition(NPC_TextBoxRender->GetTransform()->GetWorldPosition());

	FontRender0->Off();
	FontRender1->Off();
	FontRender2->Off();
	FontRender3->Off();
	FontRender4->Off();

	NPCScript.resize(5);

	{
		NPCScript[0] = FontRender0;
		NPCScript[1] = FontRender1;
		NPCScript[2] = FontRender2;
		NPCScript[3] = FontRender3;
		NPCScript[4] = FontRender4;
	}
}
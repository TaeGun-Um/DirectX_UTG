#include "PrecompileHeader.h"
#include "AppleTraveller.h"

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
		FontRender->On();
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

	if (true == GameEngineInput::IsDown("Attack") && false == NextStep)
	{
		NextStep = true;
		++TextCount;

		if (TextEndCount > TextCount)
		{
			FontRender->SetText(NPCScript[TextCount]);
			TextBoxSetting();
			
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
			TextBoxSetting();
			Player_Overworld::MainPlayer->SetTextBoxCameraAction(false);
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
	FontRender = CreateComponent<GameEngineFontRenderer>();

	FontRender->SetFont("Cuphead Felix");
	FontRender->SetScale(26.0f);
	FontRender->SetColor(float4::Black);

	TextEndCount = 3;

	NPCScript.resize(TextEndCount);

	{
		NPCScript[0] = "Hey, guys! Good to\nsee ya again!";
		NPCScript[1] = "Maybe check with other\nfolks arond here. They\nmight help ya too!";
		NPCScript[2] = "The ones not trayin'\nto kill ya, I mean.";
	}

	FontRender->SetText(NPCScript[0]);
	FontRender->Off();

	TextBoxSetting();
}

size_t AppleTraveller::NumberofLines()
{
	char ch = '\n';
	size_t Count = 0;

	for (size_t i = 0; (i = NPCScript[TextCount].find(ch, i)) != std::string::npos; i++)
	{
		Count++;
	}

	return Count;
}

size_t AppleTraveller::NumberofCharacters()
{
	char ch = '\n';
	size_t Count = 0;

	return Count = NPCScript[TextCount].find(ch);
}

void AppleTraveller::TextBoxSetting()
{
	float4 CurActorPosition = GetTransform()->GetWorldPosition();
	size_t LineCount = NumberofLines() + 1;
	size_t CharacterCount = NumberofCharacters();

	NPC_TextBoxRender->SetBox(CharacterCount, LineCount, CurActorPosition);

	FontPositionSetting();
}

void AppleTraveller::FontPositionSetting()
{
	float4 BoxScale = NPC_TextBoxRender->GetBoxScale();
	float Width = BoxScale.x;
	float Height = BoxScale.y;
	float Width_Half = Width / 2;
	float Height_Half = Height / 2;

	FontRender->GetTransform()->SetWorldPosition(NPC_TextBoxRender->GetBoxCurPosition());
	FontRender->GetTransform()->AddWorldPosition({ -Width_Half + 20, Height_Half - 10, -20 });
}
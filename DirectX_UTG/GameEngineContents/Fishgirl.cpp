#include "PrecompileHeader.h"
#include "Fishgirl.h"

#include <GameEngineCore/GameEngineFontRenderer.h>
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
		FontRender->On();
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

void Fishgirl::ScriptInit()
{
	FontRender = CreateComponent<GameEngineFontRenderer>();

	FontRender->SetFont("Cuphead Felix");
	FontRender->SetScale(26.0f);
	FontRender->SetColor(float4::Black);

	TextEndCount = 6;

	NPCScript.resize(TextEndCount);

	{
		NPCScript[0] = "Begone, spirits! Oh,\nwait... you're real.";
		NPCScript[1] = "I was about to hit you\nwith the parry move!";
		NPCScript[2] = "That's how you deal with\nghosts 'round here.";
		NPCScript[3] = "Only a nitwit tries shootin'\nsomeone who ain't really\nthere.";
		NPCScript[4] = "Speakin' of not bein'\nplace... would you\nfellas mind movin' on?";
		NPCScript[5] = "You're spookin' the fish.\n";
	}

	// 마우스 승리 시
	// TextEndCount = 4;
	// 0. so i hear you fellas gave some of them ghost what - for.
	// 1. glad someone finally sorted 'em out!
	// 2. might make the fishin' even better here.
	// 3. then again... might not.

	FontRender->SetText(NPCScript[0]);
	FontRender->Off();

	TextBoxSetting();
}

size_t Fishgirl::NumberofLines()
{
	char ch = '\n';
	size_t Count = 0;

	for (size_t i = 0; (i = NPCScript[TextCount].find(ch, i)) != std::string::npos; i++)
	{
		Count++;
	}

	return Count;
}

size_t Fishgirl::NumberofCharacters()
{
	char ch = '\n';
	size_t Count = 0;

	return Count = NPCScript[TextCount].find(ch);
}

void Fishgirl::TextBoxSetting()
{
	float4 CurActorPosition = GetTransform()->GetWorldPosition();
	size_t LineCount = NumberofLines() + 1;
	size_t CharacterCount = NumberofCharacters();

	NPC_TextBoxRender->SetBox(CharacterCount, LineCount, CurActorPosition);

	FontPositionSetting();
}

void Fishgirl::FontPositionSetting()
{
	float4 BoxScale = NPC_TextBoxRender->GetBoxScale();
	float Width = BoxScale.x;
	float Height = BoxScale.y;
	float Width_Half = Width / 2;
	float Height_Half = Height / 2;

	FontRender->GetTransform()->SetWorldPosition(NPC_TextBoxRender->GetBoxCurPosition());
	FontRender->GetTransform()->AddWorldPosition({ -Width_Half + 20, Height_Half - 10, -1 });
}
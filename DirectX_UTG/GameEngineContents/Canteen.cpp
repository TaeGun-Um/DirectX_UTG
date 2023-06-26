#include "PrecompileHeader.h"
#include "Canteen.h"

#include <GameEngineCore/GameEngineFontRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player_Overworld.h"
#include "NPC_TextBox.h"

Canteen* Canteen::CanteenPtr = nullptr;

Canteen::Canteen() 
{
}

Canteen::~Canteen() 
{
}

void Canteen::Start()
{
	CanteenPtr = this;
	NPCLoad(NPCValue::Canteen);
	InitRenderSetting();
	InitCollisionSetting();
}
void Canteen::Update(float _DeltaTime)
{
	CollisionCheck(CollisionPtr);

	if (true == CreateBox)
	{
		FontRender->On();
		TextBoxOn(_DeltaTime);
	}
}

void Canteen::TextBoxOn(float _DeltaTime)
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

void Canteen::InitRenderSetting()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr != RenderPtr)
	{
		RenderPtr->CreateAnimation({ .AnimationName = "Canteen_Idle", .SpriteName = "Canteen_Idle", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Canteen_Idle");
		RenderPtr->CameraCullingOn();
	}

	NPC_TextBoxRender = GetLevel()->CreateActor<NPC_TextBox>();
	NPC_TextBoxRender->Off();
}

void Canteen::InitCollisionSetting()
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

void Canteen::ScriptInit()
{
	FontRender = CreateComponent<GameEngineFontRenderer>();

	FontRender->SetFont("Cuphead Felix");
	FontRender->SetScale(26.0f);
	FontRender->SetColor(float4::Black);

	TextEndCount = 4;

	NPCScript.resize(TextEndCount);

	{
		NPCScript[0] = "Well? whaddaya think?\n";
		NPCScript[1] = "Are those new bombs the\ncat's phamas or\nwhat?";
		NPCScript[2] = "Aah, you can thank\nme later.";
		NPCScript[3] = "I'm just in it for\nthe kicks!";
	}

	FontRender->SetText(NPCScript[0]);
	FontRender->Off();

	TextBoxSetting();
}

size_t Canteen::NumberofLines()
{
	char ch = '\n';
	size_t Count = 0;

	for (size_t i = 0; (i = NPCScript[TextCount].find(ch, i)) != std::string::npos; i++)
	{
		Count++;
	}

	return Count;
}

size_t Canteen::NumberofCharacters()
{
	char ch = '\n';
	size_t Count = 0;

	return Count = NPCScript[TextCount].find(ch);
}

void Canteen::TextBoxSetting()
{
	float4 CurActorPosition = GetTransform()->GetWorldPosition();
	size_t LineCount = NumberofLines() + 1;
	size_t CharacterCount = NumberofCharacters();

	NPC_TextBoxRender->SetBox(CharacterCount, LineCount, CurActorPosition);

	FontPositionSetting();
}

void Canteen::FontPositionSetting()
{
	float4 BoxScale = NPC_TextBoxRender->GetBoxScale();
	float Width = BoxScale.x;
	float Height = BoxScale.y;
	float Width_Half = Width / 2;
	float Height_Half = Height / 2;

	FontRender->GetTransform()->SetWorldPosition(NPC_TextBoxRender->GetBoxCurPosition());
	FontRender->GetTransform()->AddWorldPosition({ -Width_Half + 20, Height_Half - 10, -1 });
}
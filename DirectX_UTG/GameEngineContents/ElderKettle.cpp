#include "PrecompileHeader.h"
#include "ElderKettle.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"

ElderKettle* ElderKettle::ElderKettlePtr = nullptr;

ElderKettle::ElderKettle() 
{
}

ElderKettle::~ElderKettle() 
{
}

void ElderKettle::Start()
{
	ElderKettlePtr = this;

	if (nullptr == GameEngineSprite::Find("Kettle_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("ElderKettle");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Kettle_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottle_Pop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottle_Pop_Boil").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottle_Pop_Trans_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Talk_A").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Talk_AToB").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Talk_B").GetFullPath());
	}

	if (RenderPtr == nullptr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Kettle_Idle", .SpriteName = "Kettle_Idle", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Bottle_Pop", .SpriteName = "Bottle_Pop", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Bottle_Pop_Boil", .SpriteName = "Bottle_Pop_Boil", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Bottle_Pop_Trans_Idle", .SpriteName = "Bottle_Pop_Trans_Idle", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Talk_A", .SpriteName = "Talk_A", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Talk_AToB", .SpriteName = "Talk_AToB", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Talk_B", .SpriteName = "Talk_B", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Kettle_Idle");
	}

	if (nullptr == CollisionRenderPtr)
	{
		CollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr == CollisionPtr)
	{
		CollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::ElderKettle));
	}

	if (nullptr != CollisionPtr)
	{
		CollisionPtr->GetTransform()->SetLocalScale({ 120, 200, 1 });
		CollisionPtr->GetTransform()->SetLocalPosition({ 10, -20, -17 });
	}

	if (nullptr != CollisionRenderPtr)
	{
		CollisionRenderPtr->SetTexture("GreenLine.png");
		CollisionRenderPtr->GetTransform()->SetLocalScale(CollisionPtr->GetTransform()->GetLocalScale());
		CollisionRenderPtr->GetTransform()->SetLocalPosition(CollisionPtr->GetTransform()->GetLocalPosition());
	}

	if (nullptr == EnterMessageRenderPtr)
	{
		EnterMessageRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		EnterMessageRenderPtr->SetScaleToTexture("EnterMessage.png");
		EnterMessageRenderMaxScale = EnterMessageRenderPtr->GetTransform()->GetLocalScale();
		EnterMessageRenderPtr->GetTransform()->SetLocalScale(float4{ 1, 1, 1 });
		EnterMessageRenderMinScale = EnterMessageRenderPtr->GetTransform()->GetLocalScale();
		EnterMessageRenderPtr->GetTransform()->SetLocalPosition(RenderPtr->GetTransform()->GetLocalPosition() + float4{ 15, 150, -20 });
		EnterMessageRenderPtr->Off();
	}

	NPC_TextBoxRender = GetLevel()->CreateActor<NPC_TextBox>();
	NPC_TextBoxRender->Off();
}

void ElderKettle::Update(float _DeltaTime)
{
	if (true == IsDebugRender)
	{
		CollisionRenderPtr->On();
	}
	else
	{
		CollisionRenderPtr->Off();
	}

	CollisionCheck(_DeltaTime);
	UpdateState(_DeltaTime);

	if (true == CreateBox)
	{
		FontRender->On();
		TextBoxOn(_DeltaTime);
	}
}

void ElderKettle::TextBoxOn(float _DeltaTime)
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
			//Player::MainPlayer->PlayerCollisionPtrOn();
			//Player::MainPlayer->SetIsPortalingfalse();
			NPC_TextBoxRender->Off();
			BoxInterActionDelayTime = 0.0f;
			FontRender->Off();
			FontRender->SetText(NPCScript[0]);
			TextBoxSetting();
			Player::MainPlayer->SetElderKettleInterActioning(false);
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

void ElderKettle::CollisionCheck(float _DeltaTime)
{
	if (nullptr != CollisionPtr->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		EnterMessageScaleUp(_DeltaTime);
		Isinteraction = true;
		Player::MainPlayer->SetElderKettleInterAction(true);
	}
	else
	{
		EnterMessageScaleDown(_DeltaTime);
		Isinteraction = false;
		Player::MainPlayer->SetElderKettleInterAction(false);
	}

	if (true == Isinteraction && true == GameEngineInput::IsDown("Attack"))
	{
		//Player::MainPlayer->PlayerCollisionPtrOff();
		//Player::MainPlayer->SetIsPortalingTrue();
		
		CreateBox = true;
	}
}

void ElderKettle::EnterMessageScaleUp(float _DeltaTime)
{
	ScaleCheckStart = true;
	ScaleMinTime = 0.0f;
	EnterMessageRenderPtr->On();
	ScaleCount = 1;

	ScaleMaxTime += _DeltaTime;

	float4 Scale = float4::LerpClamp(EnterMessageRenderMinScale, EnterMessageRenderMaxScale, ScaleMaxTime * 5.5f);

	EnterMessageRenderPtr->GetTransform()->SetLocalScale(Scale);
}

void ElderKettle::EnterMessageScaleDown(float _DeltaTime)
{
	if (false == ScaleCheckStart)
	{
		return;
	}

	ScaleMaxTime = 0.0f;
	EnterMessageRenderPtr->On();

	ScaleMinTime += _DeltaTime;

	if (1 == ScaleCount)
	{
		ScaleCount = 0;
		EnterMessageRenderDelayScale = EnterMessageRenderMaxScale * 1.35f;
	}

	float4 Scale = float4::LerpClamp(EnterMessageRenderDelayScale, EnterMessageRenderMinScale, ScaleMinTime * 5.f);

	EnterMessageRenderPtr->GetTransform()->SetLocalScale(Scale);

	if (EnterMessageRenderMinScale == EnterMessageRenderPtr->GetTransform()->GetLocalScale())
	{
		EnterMessageRenderPtr->Off();
	}
}

void ElderKettle::ScriptInit()
{
	FontRender = CreateComponent<GameEngineFontRenderer>();

	FontRender->SetFont("Cuphead Felix");
	FontRender->SetScale(26.0f);
	FontRender->SetColor(float4::Black);

	TextEndCount = 11;

	NPCScript.resize(TextEndCount);

	{
		NPCScript[0] = "What a fine pickle you\nboys have gotten\nyourselves into!";
		NPCScript[1] = "I know you don't want to\nbe pawns of the devil!";
		NPCScript[2] = "But if you refuse...\ni can't bear to\nimagine your fates!";
		NPCScript[3] = "You must Play along for\nnow, collect those\ncontracts!";
		NPCScript[4] = "And you'd best be ready for\nsome nasty business...!";
		NPCScript[5] = "Your debtor 'friends' won't\nbe very frindly once you\nconfront them!";
		NPCScript[6] = "In fact, i expect they'll\ntransform into trrible\nbeasts!";
		NPCScript[7] = "Take this potion so \nwon't hang you out\nto dry.";
		NPCScript[8] = "It will give you the most\nremarkable magical\nabilities!";
		NPCScript[9] = "Now go to my writing desk\nand use the mystical\ninkwell there.";
		NPCScript[10] = "You need to prepare\nyourselves for a\nscrap!!";
	}

	FontRender->SetText(NPCScript[0]);
	FontRender->Off();

	TextBoxSetting();
}

void ElderKettle::ScriptChange()
{
	TextEndCount = 3;

	NPCScript.clear();
	NPCScript.resize(TextEndCount);

	{
		NPCScript[0] = "well, what are you rascals waiting for ? off you go!";
		NPCScript[1] = "meanwhile, i shall try to figure some way out of this mess!";
		NPCScript[2] = "good luck.you troublesome little mugs!!";
	}

	FontRender->SetText(NPCScript[0]);
	FontRender->Off();

	TextBoxSetting();
}

size_t ElderKettle::NumberofLines()
{
	char ch = '\n';
	size_t Count = 0;

	for (size_t i = 0; (i = NPCScript[TextCount].find(ch, i)) != std::string::npos; i++)
	{
		Count++;
	}

	return Count;
}

size_t ElderKettle::NumberofCharacters()
{
	char ch = '\n';
	size_t Count = 0;

	return Count = NPCScript[TextCount].find(ch);
}

void ElderKettle::TextBoxSetting()
{
	float4 CurActorPosition = GetTransform()->GetWorldPosition();
	size_t LineCount = NumberofLines() + 1;
	size_t CharacterCount = NumberofCharacters();

	NPC_TextBoxRender->SetBoxKettle(CharacterCount, LineCount, CurActorPosition);

	FontPositionSetting();
}

void ElderKettle::FontPositionSetting()
{
	float4 BoxScale = NPC_TextBoxRender->GetBoxScale();
	float Width = BoxScale.x;
	float Height = BoxScale.y;
	float Width_Half = Width / 2;
	float Height_Half = Height / 2;

	FontRender->GetTransform()->SetWorldPosition(NPC_TextBoxRender->GetBoxCurPosition());
	FontRender->GetTransform()->AddWorldPosition({ -Width_Half + 20, Height_Half - 10, -20 });
}

void ElderKettle::ChangeState(KettleState _StateValue)
{
	KettleState NextState = _StateValue;
	KettleState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case KettleState::Idle:
		IdleStart();
		break;
	}
}

void ElderKettle::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case KettleState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	}
}

void ElderKettle::IdleStart()
{

}
void ElderKettle::IdleUpdate(float _DeltaTime)
{

}
void ElderKettle::IdleEnd()
{

}

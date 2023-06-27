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

	ActorInitSetting();
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

			if (7 == TextCount)
			{
				IsPop = true;
			}
			else
			{
				IsPop = false;
			}
		}
		else if (TextEndCount <= TextCount)
		{
			int Script = TextCount;

			TextCount = 0;
			CreateBox = false;
			NextStep = false;
			TextEnd = true;
			NPC_TextBoxRender->Off();
			BoxInterActionDelayTime = 0.0f;
			FontRender->Off();
			FontRender->SetText(NPCScript[0]);
			TextBoxSetting();
			Player::MainPlayer->SetElderKettleInterActioning(false);

			if (11 == Script)
			{
				ScriptChange();
			}
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
		NPCScript[0] = "well, what are you rascals\nwaiting for? off you\ngo!";
		NPCScript[1] = "meanwhile, i shall try\nto figure some way\nout of this mess!";
		NPCScript[2] = "good luck. you troublesome\nlittle mugs!!";
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
	case KettleState::TalkA:
		TalkAStart();
		break;
	case KettleState::TalkAtoB:
		TalkAtoBStart();
		break;
	case KettleState::TalkBtoA:
		TalkBtoAStart();
		break;
	case KettleState::TalkB:
		TalkBStart();
		break;
	case KettleState::Bottle_Intro:
		Bottle_IntroStart();
		break;
	case KettleState::Bottle_Loop:
		Bottle_LoopStart();
		break;
	case KettleState::Bottle_Outro:
		Bottle_OutroStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case KettleState::Idle:
		IdleEnd();
		break;
	case KettleState::TalkA:
		TalkAEnd();
		break;
	case KettleState::TalkAtoB:
		TalkAtoBEnd();
		break;
	case KettleState::TalkBtoA:
		TalkBtoAEnd();
		break;
	case KettleState::TalkB:
		TalkBEnd();
		break;
	case KettleState::Bottle_Intro:
		Bottle_IntroEnd();
		break;
	case KettleState::Bottle_Loop:
		Bottle_LoopEnd();
		break;
	case KettleState::Bottle_Outro:
		Bottle_OutroEnd();
		break;
	default:
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
	case KettleState::TalkA:
		TalkAUpdate(_DeltaTime);
		break;
	case KettleState::TalkAtoB:
		TalkAtoBUpdate(_DeltaTime);
		break;
	case KettleState::TalkBtoA:
		TalkBtoAUpdate(_DeltaTime);
		break;
	case KettleState::TalkB:
		TalkBUpdate(_DeltaTime);
		break;
	case KettleState::Bottle_Intro:
		Bottle_IntroUpdate(_DeltaTime);
		break;
	case KettleState::Bottle_Loop:
		Bottle_LoopUpdate(_DeltaTime);
		break;
	case KettleState::Bottle_Outro:
		Bottle_OutroUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void ElderKettle::IdleStart()
{
	RenderPtr->ChangeAnimation("Kettle_Idle");
}
void ElderKettle::IdleUpdate(float _DeltaTime)
{
	if (true == IsPop && 1 == PopCount)
	{
		PopCount = 0;
		ChangeState(KettleState::Bottle_Intro);
		return;
	}

	if (true == CreateBox)
	{
		ChangeState(KettleState::TalkA);
		return;
	}
}
void ElderKettle::IdleEnd()
{

}

void ElderKettle::TalkAStart()
{
	RenderPtr->ChangeAnimation("Talk_A");
}
void ElderKettle::TalkAUpdate(float _DeltaTime)
{
	if (true == TextEnd)
	{
		TextEnd = false;
		ChangeState(KettleState::Idle);
		return;
	}

	if (true == IsPop && 1 == PopCount)
	{
		PopCount = 0;
		ChangeState(KettleState::Bottle_Intro);
		return;
	}

	TalkStateChangeTime += _DeltaTime;

	if (7.0f <= TalkStateChangeTime)
	{
		ChangeState(KettleState::TalkAtoB);
		return;
	}
}
void ElderKettle::TalkAEnd()
{
	TalkStateChangeTime = 0.0f;
}
	 
void ElderKettle::TalkAtoBStart()
{
	RenderPtr->ChangeAnimation("Talk_AToB");
}
void ElderKettle::TalkAtoBUpdate(float _DeltaTime)
{
	if (true == TextEnd)
	{
		TextEnd = false;
		ChangeState(KettleState::Idle);
		return;
	}

	if (true == IsPop && 1 == PopCount)
	{
		PopCount = 0;
		ChangeState(KettleState::Bottle_Intro);
		return;
	}

	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(KettleState::TalkB);
		return;
	}
}
void ElderKettle::TalkAtoBEnd()
{

}

void ElderKettle::TalkBtoAStart()
{
	RenderPtr->ChangeAnimation("Talk_BToA");
}
void ElderKettle::TalkBtoAUpdate(float _DeltaTime)
{
	if (true == TextEnd)
	{
		TextEnd = false;
		ChangeState(KettleState::Idle);
		return;
	}

	if (true == IsPop && 1 == PopCount)
	{
		PopCount = 0;
		ChangeState(KettleState::Bottle_Intro);
		return;
	}

	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(KettleState::TalkA);
		return;
	}
}
void ElderKettle::TalkBtoAEnd()
{

}
	 
void ElderKettle::TalkBStart()
{
	RenderPtr->ChangeAnimation("Talk_B");
}
void ElderKettle::TalkBUpdate(float _DeltaTime)
{
	if (true == TextEnd)
	{
		TextEnd = false;
		ChangeState(KettleState::Idle);
		return;
	}

	if (true == IsPop && 1 == PopCount)
	{
		PopCount = 0;
		ChangeState(KettleState::Bottle_Intro);
		return;
	}

	TalkStateChangeTime += _DeltaTime;

	if (7.0f <= TalkStateChangeTime)
	{
		ChangeState(KettleState::TalkBtoA);
		return;
	}
}
void ElderKettle::TalkBEnd()
{
	TalkStateChangeTime = 0.0f;
}

void ElderKettle::Bottle_IntroStart()
{
	RenderPtr->ChangeAnimation("Bottle_Pop");
	BottleRenderPtr->ChangeAnimation("Bottle_Appear");
	BottleRenderPtr->On();

	BottleRenderPtr->GetTransform()->SetLocalPosition({ -20, 80 });
}
void ElderKettle::Bottle_IntroUpdate(float _DeltaTime)
{
	if (true == TextEnd)
	{
		BottleRenderPtr->Off();
		TextEnd = false;
		ChangeState(KettleState::Idle);
		return;
	}

	if (9 == BottleRenderPtr->GetCurrentFrame())
	{
		BottleRenderPtr->GetTransform()->SetLocalPosition({ -30, 70 });
	}
	else if (9 == BottleRenderPtr->GetCurrentFrame())
	{
		BottleRenderPtr->GetTransform()->SetLocalPosition({ -30, 50 });
	}
	else if (10 == BottleRenderPtr->GetCurrentFrame())
	{
		BottleRenderPtr->GetTransform()->SetLocalPosition({ -120, -15 });
	}

	if (true == BottleRenderPtr->IsAnimationEnd())
	{
		ChangeState(KettleState::Bottle_Loop);
		return;
	}
}
void ElderKettle::Bottle_IntroEnd()
{

}
	 
void ElderKettle::Bottle_LoopStart()
{
	RenderPtr->ChangeAnimation("Bottle_Pop_Boil");
	BottleRenderPtr->ChangeAnimation("Bottle_Hold");
	BottleRenderPtr->GetTransform()->SetLocalPosition({ -90, -15 });
}
void ElderKettle::Bottle_LoopUpdate(float _DeltaTime)
{
	if (true == TextEnd)
	{
		BottleRenderPtr->Off();
		TextEnd = false;
		ChangeState(KettleState::Idle);
		return;
	}

	if (true == BottleRenderPtr->IsAnimationEnd())
	{
		ChangeState(KettleState::Bottle_Outro);
		return;
	}
}
void ElderKettle::Bottle_LoopEnd()
{

}
	 
void ElderKettle::Bottle_OutroStart()
{
	RenderPtr->ChangeAnimation("Bottle_Pop_Trans_Idle");
	BottleRenderPtr->ChangeAnimation("Bottle_FX");
	BottleRenderPtr->GetTransform()->SetLocalScale({ 1024, 1024, 1 });
	Player::MainPlayer->SetPopInterAction();
}
void ElderKettle::Bottle_OutroUpdate(float _DeltaTime)
{
	if (true == TextEnd)
	{
		TextEnd = false;
		ChangeState(KettleState::Idle);
		return;
	}

	if (true == BottleRenderPtr->IsAnimationEnd())
	{
		//Player::MainPlayer->SetPopInterAction();
		ChangeState(KettleState::Idle);
		return;
	}
}
void ElderKettle::Bottle_OutroEnd()
{
	BottleRenderPtr->Off();
}

void ElderKettle::ActorInitSetting()
{
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
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Talk_BToA").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Talk_B").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Bottle_Appear.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("ElderKettle");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Bottle_Appear.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Bottle_Hold.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Bottle_FX.png").GetFullPath(), 5, 3);
	}

	if (RenderPtr == nullptr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Kettle_Idle", .SpriteName = "Kettle_Idle", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Bottle_Pop", .SpriteName = "Bottle_Pop", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Bottle_Pop_Boil", .SpriteName = "Bottle_Pop_Boil", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Bottle_Pop_Trans_Idle", .SpriteName = "Bottle_Pop_Trans_Idle", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Talk_A", .SpriteName = "Talk_A", .FrameInter = 0.04f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Talk_AToB", .SpriteName = "Talk_AToB", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Talk_BToA", .SpriteName = "Talk_BToA", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Talk_B", .SpriteName = "Talk_B", .FrameInter = 0.04f, .Loop = true, .ScaleToTexture = true });
		
		ChangeState(KettleState::Idle);
	}

	if (BottleRenderPtr == nullptr)
	{
		BottleRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BottleRenderPtr->CreateAnimation({ "Bottle_Appear", "Bottle_Appear.png", 0, 18, 0.05f, false, false });
		BottleRenderPtr->CreateAnimation({ "Bottle_Hold", "Bottle_Hold.png", 0, 2, 0.05f, true, false });
		BottleRenderPtr->CreateAnimation({ "Bottle_FX", "Bottle_FX.png", 0, 12, 0.05f, false, false });
		BottleRenderPtr->GetTransform()->SetLocalScale({ 512, 512, 1 });
		BottleRenderPtr->Off();
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
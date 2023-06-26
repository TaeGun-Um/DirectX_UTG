#include "PrecompileHeader.h"
#include "Coin.h"

#include <GameEngineCore/GameEngineFontRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player_Overworld.h"
#include "NPC_TextBox.h"

Coin* Coin::CoinPtr = nullptr;

Coin::Coin() 
{
}

Coin::~Coin() 
{
}

void Coin::Start()
{
	CoinPtr = this;
	NPCLoad(NPCValue::Coin);
	InitRenderSetting();
	InitCollisionSetting();
}

void Coin::Update(float _DeltaTime)
{
	CollisionCheck(CollisionPtr);
	UpdateState(_DeltaTime);

	if (true == CreateBox)
	{
		FontRender->On();
		TextBoxOn(_DeltaTime);
	}
}

void Coin::TextBoxOn(float _DeltaTime)
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

void Coin::ScriptInit()
{
	FontRender = CreateComponent<GameEngineFontRenderer>();

	FontRender->SetFont("Cuphead Felix");
	FontRender->SetScale(26.0f);
	FontRender->SetColor(float4::Black);

	TextEndCount = 5;

	NPCScript.resize(TextEndCount);

	{
		NPCScript[0] = "Harumph!! I'll be a\nmonkey' uncle if i'm\nputting my moolah\nin the bank!";
		NPCScript[1] = "For all i know. The devil\nprobably controls the\nplace too!";
		NPCScript[2] = "They'll never get ahold of my\ngold if i spread it all around.";
		NPCScript[3] = "And if some joe happens\nto find a coin or two...\ngood for him!";
		NPCScript[4] = "That's what i say,\nharumph!!";
	}

	FontRender->SetText(NPCScript[0]);
	FontRender->Off();

	TextBoxSetting();
}

size_t Coin::NumberofLines()
{
	char ch = '\n';
	size_t Count = 0;

	for (size_t i = 0; (i = NPCScript[TextCount].find(ch, i)) != std::string::npos; i++)
	{
		Count++;
	}

	return Count;
}

size_t Coin::NumberofCharacters()
{
	char ch = '\n';
	size_t Count = 0;

	return Count = NPCScript[TextCount].find(ch);
}

void Coin::TextBoxSetting()
{
	float4 CurActorPosition = GetTransform()->GetWorldPosition();
	size_t LineCount = NumberofLines() + 1;
	size_t CharacterCount = NumberofCharacters();

	NPC_TextBoxRender->SetBox(CharacterCount, LineCount, CurActorPosition);

	FontPositionSetting();
}

void Coin::FontPositionSetting()
{
	float4 BoxScale = NPC_TextBoxRender->GetBoxScale();
	float Width = BoxScale.x;
	float Height = BoxScale.y;
	float Width_Half = Width / 2;
	float Height_Half = Height / 2;

	FontRender->GetTransform()->SetWorldPosition(NPC_TextBoxRender->GetBoxCurPosition());
	FontRender->GetTransform()->AddWorldPosition({ -Width_Half + 20, Height_Half - 10, -1 });
}

void Coin::InitRenderSetting()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr != RenderPtr)
	{
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Blink", .SpriteName = "Coin_Blink", .FrameInter = 0.09f, .ScaleToTexture = true });

		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Boil_A", .SpriteName = "Coin_Boil_A", .FrameInter = 0.09f, .ScaleToTexture = true });

		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Hold_A", .SpriteName = "Coin_Hold_A", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Hold_B", .SpriteName = "Coin_Hold_B", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Hold_C", .SpriteName = "Coin_Hold_C", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Hold_D", .SpriteName = "Coin_Hold_D", .FrameInter = 0.09f, .ScaleToTexture = true });

		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Transition_A", .SpriteName = "Coin_Transition_A", .FrameInter = 0.09f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Transition_B", .SpriteName = "Coin_Transition_B", .FrameInter = 0.09f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Transition_C", .SpriteName = "Coin_Transition_C", .FrameInter = 0.09f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Transition_D", .SpriteName = "Coin_Transition_D", .FrameInter = 0.09f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Transition_E", .SpriteName = "Coin_Transition_E", .FrameInter = 0.09f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Coin_Transition_F", .SpriteName = "Coin_Transition_F", .FrameInter = 0.09f, .Loop = false, .ScaleToTexture = true });
		
		RenderPtr->CameraCullingOn();
	}

	ChangeState(CoinState::Idle);

	NPC_TextBoxRender = GetLevel()->CreateActor<NPC_TextBox>();
	NPC_TextBoxRender->Off();
}

void Coin::InitCollisionSetting()
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

void Coin::ChangeState(CoinState _StateValue)
{
	CoinState NextState = _StateValue;
	CoinState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case CoinState::Idle:
		IdleStart();
		break;
	case CoinState::LeftTurn:
		LeftTurnStart();
		break;
	case CoinState::LeftIdle_EyeLeft:
		LeftIdle_EyeLeftStart();
		break;
	case CoinState::TurnIdle_L:
		TurnIdle_LStart();
		break;
	case CoinState::LeftIdle_EyeTurn:
		LeftIdle_EyeTurnStart();
		break;
	case CoinState::LeftIdle_EyeRight:
		LeftIdle_EyeRightStart();
		break;
	case CoinState::RightTurn:
		RightTurnStart();
		break;
	case CoinState::RightTurn_EyeRight:
		RightTurn_EyeRightStart();
		break;
	case CoinState::RightTurn_EyeTurn:
		RightTurn_EyeTurnStart();
		break;
	case CoinState::RightTurn_EyeLeft:
		RightTurn_EyeLeftStart();
		break;
	case CoinState::TurnIdle:
		TurnIdleStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case CoinState::Idle:
		IdleEnd();
		break;
	case CoinState::LeftTurn:
		LeftTurnEnd();
		break;
	case CoinState::LeftIdle_EyeLeft:
		LeftIdle_EyeLeftEnd();
		break;
	case CoinState::TurnIdle_L:
		TurnIdle_LEnd();
		break;
	case CoinState::LeftIdle_EyeTurn:
		LeftIdle_EyeTurnEnd();
		break;
	case CoinState::LeftIdle_EyeRight:
		LeftIdle_EyeRightEnd();
		break;
	case CoinState::RightTurn:
		RightTurnEnd();
		break;
	case CoinState::RightTurn_EyeRight:
		RightTurn_EyeRightEnd();
		break;
	case CoinState::RightTurn_EyeTurn:
		RightTurn_EyeTurnEnd();
		break;
	case CoinState::RightTurn_EyeLeft:
		RightTurn_EyeLeftEnd();
		break;
	case CoinState::TurnIdle:
		TurnIdleEnd();
		break;
	default:
		break;
	}
}

void Coin::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case CoinState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	case CoinState::LeftTurn:
		LeftTurnUpdate(_DeltaTime);
		break;
	case CoinState::LeftIdle_EyeLeft:
		LeftIdle_EyeLeftUpdate(_DeltaTime);
		break;
	case CoinState::TurnIdle_L:
		TurnIdle_LUpdate(_DeltaTime);
		break;
	case CoinState::LeftIdle_EyeTurn:
		LeftIdle_EyeTurnUpdate(_DeltaTime);
		break;
	case CoinState::LeftIdle_EyeRight:
		LeftIdle_EyeRightUpdate(_DeltaTime);
		break;
	case CoinState::RightTurn:
		RightTurnUpdate(_DeltaTime);
		break;
	case CoinState::RightTurn_EyeRight:
		RightTurn_EyeRightUpdate(_DeltaTime);
		break;
	case CoinState::RightTurn_EyeTurn:
		RightTurn_EyeTurnUpdate(_DeltaTime);
		break;
	case CoinState::RightTurn_EyeLeft:
		RightTurn_EyeLeftUpdate(_DeltaTime);
		break;
	case CoinState::TurnIdle:
		TurnIdleUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Coin::IdleStart()
{
	RenderPtr->ChangeAnimation("Coin_Boil_A");
}
void Coin::IdleUpdate(float _DeltaTime)
{
	AccTime += _DeltaTime;

	if (5.0f <= AccTime)
	{
		int RandC = GameEngineRandom::MainRandom.RandomInt(1, 2);

		if (1 == RandC)
		{
			ChangeState(CoinState::LeftTurn);
			return;
		}
		else
		{
			ChangeState(CoinState::RightTurn);
			return;
		}
	}
}
void Coin::IdleEnd()
{
	AccTime = 0.0f;
}

void Coin::LeftTurnStart()
{
	RenderPtr->ChangeAnimation("Coin_Transition_A");
}
void Coin::LeftTurnUpdate(float _DeltaTime)
{
	if (RenderPtr->IsAnimationEnd())
	{
		ChangeState(CoinState::LeftIdle_EyeLeft);
		return;
	}
}
void Coin::LeftTurnEnd()
{

}

void Coin::LeftIdle_EyeLeftStart()
{
	RenderPtr->ChangeAnimation("Coin_Hold_A");
}
void Coin::LeftIdle_EyeLeftUpdate(float _DeltaTime)
{
	AccTime += _DeltaTime;

	if (3.0f <= AccTime)
	{
		int RandC = GameEngineRandom::MainRandom.RandomInt(1, 2);

		if (1 == RandC)
		{
			ChangeState(CoinState::TurnIdle_L);
			return;
		}
		else
		{
			ChangeState(CoinState::LeftIdle_EyeTurn);
			return;
		}
	}
}
void Coin::LeftIdle_EyeLeftEnd()
{
	AccTime = 0.0f;
}

void Coin::TurnIdle_LStart()
{
	RenderPtr->ChangeAnimation("Coin_Transition_C");
}
void Coin::TurnIdle_LUpdate(float _DeltaTime)
{
	if (RenderPtr->IsAnimationEnd())
	{
		ChangeState(CoinState::Idle);
		return;
	}
}
void Coin::TurnIdle_LEnd()
{

}

void Coin::LeftIdle_EyeTurnStart()
{
	RenderPtr->ChangeAnimation("Coin_Transition_B");
}
void Coin::LeftIdle_EyeTurnUpdate(float _DeltaTime)
{
	if (RenderPtr->IsAnimationEnd())
	{
		ChangeState(CoinState::LeftIdle_EyeRight);
		return;
	}
}
void Coin::LeftIdle_EyeTurnEnd()
{

}

void Coin::LeftIdle_EyeRightStart()
{
	RenderPtr->ChangeAnimation("Coin_Hold_B");
}
void Coin::LeftIdle_EyeRightUpdate(float _DeltaTime)
{
	AccTime += _DeltaTime;

	if (2.0f <= AccTime)
	{
		ChangeState(CoinState::RightTurn);
		return;
	}
}
void Coin::LeftIdle_EyeRightEnd()
{
	AccTime = 0.0f;
}

void Coin::RightTurnStart()
{
	RenderPtr->ChangeAnimation("Coin_Transition_D");
}
void Coin::RightTurnUpdate(float _DeltaTime)
{
	if (RenderPtr->IsAnimationEnd())
	{
		ChangeState(CoinState::RightTurn_EyeRight);
		return;
	}
}
void Coin::RightTurnEnd()
{

}

void Coin::RightTurn_EyeRightStart()
{
	RenderPtr->ChangeAnimation("Coin_Hold_C");
}
void Coin::RightTurn_EyeRightUpdate(float _DeltaTime)
{
	AccTime += _DeltaTime;

	if (2.0f <= AccTime)
	{
		ChangeState(CoinState::RightTurn_EyeTurn);
		return;
	}
}
void Coin::RightTurn_EyeRightEnd()
{
	AccTime = 0.0f;
}

void Coin::RightTurn_EyeTurnStart()
{
	RenderPtr->ChangeAnimation("Coin_Transition_E");
}
void Coin::RightTurn_EyeTurnUpdate(float _DeltaTime)
{
	if (RenderPtr->IsAnimationEnd())
	{
		ChangeState(CoinState::RightTurn_EyeLeft);
		return;
	}
}
void Coin::RightTurn_EyeTurnEnd()
{

}

void Coin::RightTurn_EyeLeftStart()
{
	RenderPtr->ChangeAnimation("Coin_Hold_D");
}
void Coin::RightTurn_EyeLeftUpdate(float _DeltaTime)
{
	AccTime += _DeltaTime;

	if (2.0f <= AccTime)
	{
		ChangeState(CoinState::TurnIdle);
		return;
	}
}
void Coin::RightTurn_EyeLeftEnd()
{
	AccTime = 0.0f;
}

void Coin::TurnIdleStart()
{
	RenderPtr->ChangeAnimation("Coin_Transition_F");
}
void Coin::TurnIdleUpdate(float _DeltaTime)
{
	if (RenderPtr->IsAnimationEnd())
	{
		ChangeState(CoinState::Idle);
		return;
	}
}
void Coin::TurnIdleEnd()
{

}
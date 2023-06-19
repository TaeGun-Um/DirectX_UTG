#include "PrecompileHeader.h"
#include "Stick.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "MouseLevel.h"
#include "You_Died.h"
#include "Werner_Werman.h"

Stick::Stick() 
{
}

Stick::~Stick() 
{
}

void Stick::SelectRenderType(RenderType _Type, bool _Direct)
{
	switch (_Type)
	{
	case RenderType::BottleA:
		BottleRenderPtr->ChangeAnimation("A_Loop");
		StickRenderPtr->ChangeAnimation("Stick_A");
		break;
	case RenderType::BottleB:
		BottleRenderPtr->ChangeAnimation("B_Loop");
		StickRenderPtr->ChangeAnimation("Stick_B");
		break;
	case RenderType::BottleC:
		BottleRenderPtr->ChangeAnimation("C_Loop");
		StickRenderPtr->ChangeAnimation("Stick_C");
		break;
	case RenderType::BottleD:
		BottleRenderPtr->ChangeAnimation("D_Loop");
		StickRenderPtr->ChangeAnimation("Stick_A");
		break;
	case RenderType::BottleE:
		BottleRenderPtr->ChangeAnimation("E_Loop");
		StickRenderPtr->ChangeAnimation("Stick_B");
		break;
	case RenderType::BottleF:
		BottleRenderPtr->ChangeAnimation("F_Loop");
		StickRenderPtr->ChangeAnimation("Stick_C");
		break;
	default:
		break;
	}

	Directbool = _Direct;

	AttackCollisionPtr->GetTransform()->SetLocalScale({ 80, 80, -10 });

	if (true == Directbool)
	{
		BottleRenderPtr->GetTransform()->SetLocalPosition({ 250, 0 });
		IdlePosition = InitPosition + float4{ 180, 0 };

		AttackCollisionPtr->GetTransform()->SetLocalPosition({ 250, 0 });
	}
	else
	{
		BottleRenderPtr->GetTransform()->SetLocalPosition({ -250, 0 });
		IdlePosition = InitPosition + float4{ -180, 0 };

		AttackCollisionPtr->GetTransform()->SetLocalPosition({ -250, 0 });
	}

	AttackCollisionRenderPtr->GetTransform()->SetLocalScale(AttackCollisionPtr->GetTransform()->GetLocalScale());
	AttackCollisionRenderPtr->GetTransform()->SetLocalPosition(AttackCollisionPtr->GetTransform()->GetLocalPosition());
}

void Stick::Start()
{
	if (nullptr == StickRenderPtr)
	{
		StickRenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		StickRenderPtr->CreateAnimation({ .AnimationName = "Stick_A", .SpriteName = "Stick_A", .FrameInter = 0.09f, .Loop = true, .ScaleToTexture = true });
		StickRenderPtr->CreateAnimation({ .AnimationName = "Stick_B", .SpriteName = "Stick_B", .FrameInter = 0.09f, .Loop = true, .ScaleToTexture = true });
		StickRenderPtr->CreateAnimation({ .AnimationName = "Stick_C", .SpriteName = "Stick_C", .FrameInter = 0.09f, .Loop = true, .ScaleToTexture = true });

		StickRenderPtr->ChangeAnimation("Stick_A");
	}

	if (nullptr == BottleRenderPtr)
	{
		BottleRenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		BottleRenderPtr->CreateAnimation({ .AnimationName = "A_Loop", .SpriteName = "Bottlecap_A", .FrameInter = 0.09f, .Loop = true, .ScaleToTexture = true });
		BottleRenderPtr->CreateAnimation({ .AnimationName = "B_Loop", .SpriteName = "Bottlecap_B", .FrameInter = 0.09f, .Loop = true, .ScaleToTexture = true });
		BottleRenderPtr->CreateAnimation({ .AnimationName = "C_Loop", .SpriteName = "Bottlecap_C", .FrameInter = 0.09f, .Loop = true, .ScaleToTexture = true });
		BottleRenderPtr->CreateAnimation({ .AnimationName = "D_Loop", .SpriteName = "Bottlecap_D", .FrameInter = 0.09f, .Loop = true, .ScaleToTexture = true });
		BottleRenderPtr->CreateAnimation({ .AnimationName = "E_Loop", .SpriteName = "Bottlecap_E", .FrameInter = 0.09f, .Loop = true, .ScaleToTexture = true });
		BottleRenderPtr->CreateAnimation({ .AnimationName = "F_Loop", .SpriteName = "Bottlecap_F", .FrameInter = 0.09f, .Loop = true, .ScaleToTexture = true });

		BottleRenderPtr->ChangeAnimation("A_Loop");
		ChangeState(SitckState::Intro);
	}

	if (nullptr == AttackCollisionPtr)
	{
		AttackCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
		AttackCollisionPtr->SetColType(ColType::SPHERE2D);
		AttackCollisionPtr->Off();
	}

	if (nullptr == AttackCollisionRenderPtr)
	{
		AttackCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		AttackCollisionRenderPtr->SetTexture("GreenLine.png");
		AttackCollisionRenderPtr->Off();
	}
}

void Stick::Update(float _DeltaTime)
{
	if (true == MouseLevel::MouseLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	UpdateState(_DeltaTime);
}

void Stick::BottleRotation(float _DeltaTime, float _Value)
{
	if (360.0f > Angle)
	{
		Angle += _DeltaTime * _Value;
	}
	else if (360.0f <= Angle)
	{
		Angle = 0.0f;
	}

	BottleRenderPtr->GetTransform()->SetLocalRotation({ 0, 0, Angle });

	VibrationTime += _DeltaTime;

	if (0.05f <= VibrationTime)
	{
		VibrationTime = 0.0f;
		Vibrationbool = !Vibrationbool;

		if (true == Vibrationbool)
		{
			GetTransform()->AddLocalPosition({ 0, 2 });
		}
		else
		{
			GetTransform()->AddLocalPosition({ 0, -2 });
		}
	}
}

void Stick::ChangeState(SitckState _StateValue)
{
	SitckState NextState = _StateValue;
	SitckState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case SitckState::Intro:
		IntroStart();
		break;
	case SitckState::Idle:
		IdleStart();
		break;
	case SitckState::Back:
		BackStart();
		break;
	case SitckState::Move:
		MoveStart();
		break;
	case SitckState::RollBack:
		RollBackStart();
		break;
	case SitckState::End:
		EndStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case SitckState::Intro:
		IntroEnd();
		break;
	case SitckState::Idle:
		IdleEnd();
		break;
	case SitckState::Back:
		BackEnd();
		break;
	case SitckState::Move:
		MoveEnd();
		break;
	case SitckState::RollBack:
		RollBackEnd();
		break;
	case SitckState::End:
		EndEnd();
		break;
	default:
		break;
	}
}
void Stick::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case SitckState::Intro:
		IntroUpdate(_DeltaTime);
		break;
	case SitckState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	case SitckState::Back:
		BackUpdate(_DeltaTime);
		break;
	case SitckState::Move:
		MoveUpdate(_DeltaTime);
		break;
	case SitckState::RollBack:
		RollBackUpdate(_DeltaTime);
		break;
	case SitckState::End:
		EndUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Stick::IntroStart()
{

}
void Stick::IntroUpdate(float _DeltaTime)
{
	if (true == Werner_Werman::WernerWermanPtr->GetPhase2End())
	{
		ChangeState(SitckState::End);
		return;
	}

	IsAction = false;

	float4 CurPos = GetTransform()->GetLocalPosition();
	float MoveDis = 30.0f * _DeltaTime;

	if (true == Directbool)
	{
		GetTransform()->AddLocalPosition({ MoveDis , 0 });
		
		if (IdlePosition.x <= CurPos.x)
		{
			GetTransform()->SetLocalPosition(IdlePosition);
			ChangeState(SitckState::Idle);
			return;
		}
	}
	else
	{
		GetTransform()->AddLocalPosition({ -MoveDis , 0 });

		if (IdlePosition.x >= CurPos.x)
		{
			GetTransform()->SetLocalPosition(IdlePosition);
			ChangeState(SitckState::Idle);
			return;
		}
	}
}
void Stick::IntroEnd()
{

}

void Stick::IdleStart()
{

}
void Stick::IdleUpdate(float _DeltaTime)
{
	if (true == Werner_Werman::WernerWermanPtr->GetPhase2End())
	{
		ChangeState(SitckState::End);
		return;
	}

	if (true == IsAction)
	{
		ChangeState(SitckState::Back);
		return;
	}
}
void Stick::IdleEnd()
{

}

void Stick::BackStart()
{
	AttackCollisionPtr->On();

	if (true == Directbool)
	{
		BackPosition = IdlePosition + float4{ -110, 0 };
	}
	else
	{
		BackPosition = IdlePosition + float4{ 110, 0 };
	}
}
void Stick::BackUpdate(float _DeltaTime)
{
	if (true == Werner_Werman::WernerWermanPtr->GetPhase2End())
	{
		ChangeState(SitckState::End);
		return;
	}

	float4 CurPos = GetTransform()->GetLocalPosition();
	float MoveDis = 30.0f * _DeltaTime;

	if (true == Directbool)
	{
		GetTransform()->AddLocalPosition({ -MoveDis , 0 });

		if (BackPosition.x >= CurPos.x)
		{
			GetTransform()->SetLocalPosition(BackPosition);
			ChangeState(SitckState::Move);
			return;
		}
	}
	else
	{
		GetTransform()->AddLocalPosition({ MoveDis , 0 });

		if (BackPosition.x <= CurPos.x)
		{
			GetTransform()->SetLocalPosition(BackPosition);
			ChangeState(SitckState::Move);
			return;
		}
	}

	BottleRotation(_DeltaTime, 500.0f);
}
void Stick::BackEnd()
{

}

void Stick::MoveStart()
{
	if (true == Directbool)
	{
		MovePosition = BackPosition + float4{ 480, 0 };
	}
	else
	{
		MovePosition = BackPosition + float4{ -480, 0 };
	}
}
void Stick::MoveUpdate(float _DeltaTime)
{
	if (true == Werner_Werman::WernerWermanPtr->GetPhase2End())
	{
		ChangeState(SitckState::End);
		return;
	}

	float4 CurPos = GetTransform()->GetLocalPosition();
	float4 Movedir = float4::Zero;

	Movedir = (MovePosition - CurPos);

	MoveDistance = Movedir * 1.5f * _DeltaTime;

	GetTransform()->AddWorldPosition(MoveDistance);

	if (true == Directbool)
	{
		if (MovePosition.x - 20.0f <= CurPos.x)
		{
			GetTransform()->SetLocalPosition(MovePosition + float4{ -20, 0 });
			ChangeState(SitckState::RollBack);
			return;
		}
	}
	else
	{
		if (MovePosition.x + 20.0f >= CurPos.x)
		{
			GetTransform()->SetLocalPosition(MovePosition + float4{ 20, 0 });
			ChangeState(SitckState::RollBack);
			return;
		}
	}

	BottleRotation(_DeltaTime, 1000.0f);
}
void Stick::MoveEnd()
{

}

void Stick::RollBackStart()
{

}
void Stick::RollBackUpdate(float _DeltaTime)
{
	if (true == Werner_Werman::WernerWermanPtr->GetPhase2End())
	{
		ChangeState(SitckState::End);
		return;
	}

	float4 CurPos = GetTransform()->GetLocalPosition();
	float MoveDis = 160.0f * _DeltaTime;

	if (true == Directbool)
	{
		GetTransform()->AddLocalPosition({ -MoveDis , 0 });

		if (IdlePosition.x >= CurPos.x)
		{
			GetTransform()->SetLocalPosition(IdlePosition);
			ChangeState(SitckState::Idle);
			return;
		}
	}
	else
	{
		GetTransform()->AddLocalPosition({ MoveDis , 0 });

		if (IdlePosition.x <= CurPos.x)
		{
			GetTransform()->SetLocalPosition(IdlePosition);
			ChangeState(SitckState::Idle);
			return;
		}
	}

	RollDesc += _DeltaTime * 500.0f;

	BottleRotation(_DeltaTime, 1000.0f - RollDesc);
}
void Stick::RollBackEnd()
{
	RollDesc = 0.0f;
	IsAction = false;
	AttackCollisionPtr->Off();
}

void Stick::EndStart()
{
	EndStartPosition = GetTransform()->GetLocalPosition();
}
void Stick::EndUpdate(float _DeltaTime)
{
	EndMoveTime += _DeltaTime;

	float4 CurPos = GetTransform()->GetLocalPosition();
	float4 MoveMount = float4::LerpClamp(EndStartPosition, InitPosition, EndMoveTime * 1.f);
	GetTransform()->SetLocalPosition(MoveMount);

	if (InitPosition.x + 5.0f >= CurPos.x && true == Directbool)
	{
		Death();
	}
	else if (InitPosition.x - 5.0f <= CurPos.x && false == Directbool)
	{
		Death();
	}
}
void Stick::EndEnd()
{

}
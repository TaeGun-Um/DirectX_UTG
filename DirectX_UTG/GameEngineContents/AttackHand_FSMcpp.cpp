#include "PrecompileHeader.h"
#include "Katzenwagen.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "Mouse_Map.h"

void Katzenwagen::ChangeState_AttackHand(AttackHandState _StateValue)
{
	AttackHandState NextState = _StateValue;
	AttackHandState PrevState = AttackHandStateValue;

	AttackHandStateValue = NextState;

	switch (NextState)
	{
	case AttackHandState::Intro:
		AttackHand_IntroStart();
		break;
	case AttackHandState::Loop:
		AttackHand_LoopStart();
		break;
	case AttackHandState::Hit:
		AttackHand_HitStart();
		break;
	case AttackHandState::Outro:
		AttackHand_OutroStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case AttackHandState::Intro:
		AttackHand_IntroEnd();
		break;
	case AttackHandState::Loop:
		AttackHand_LoopEnd();
		break;
	case AttackHandState::Hit:
		AttackHand_HitEnd();
		break;
	case AttackHandState::Outro:
		AttackHand_OutroEnd();
		break;
	default:
		break;
	}
}
void Katzenwagen::UpdateState_AttackHand(float _DeltaTime)
{
	switch (AttackHandStateValue)
	{
	case AttackHandState::Intro:
		AttackHand_IntroUpdate(_DeltaTime);
		break;
	case AttackHandState::Loop:
		AttackHand_LoopUpdate(_DeltaTime);
		break;
	case AttackHandState::Hit:
		AttackHand_HitUpdate(_DeltaTime);
		break;
	case AttackHandState::Outro:
		AttackHand_OutroUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Katzenwagen::AttackHand_IntroStart()
{
	if (false == Directbool)
	{
		AttackHandRenderPtr->GetTransform()->SetLocalPositiveScaleX();
		AttackHandRenderPtr->GetTransform()->SetLocalPosition({ -600, -90 });
	}
	else
	{
		AttackHandRenderPtr->GetTransform()->SetLocalNegativeScaleX();
		AttackHandRenderPtr->GetTransform()->SetLocalPosition({ 600, -90 });
	}

	AttackHandRenderPtr->On();
	AttackHandRenderPtr->ChangeAnimation("Cat_Claw_Hand_Intro");
}
void Katzenwagen::AttackHand_IntroUpdate(float _DeltaTime)
{
	if (AttackHandRenderPtr->IsAnimationEnd())
	{
		ChangeState_AttackHand(AttackHandState::Loop);
		return;
	}
}
void Katzenwagen::AttackHand_IntroEnd()
{

}

void Katzenwagen::AttackHand_LoopStart()
{
	CurHandPosition = AttackHandRenderPtr->GetTransform()->GetLocalPosition();

	if (false == Directbool)
	{
		HandLerpPosition = CurHandPosition + float4{ 600, 0 };
	}
	else
	{
		HandLerpPosition = CurHandPosition + float4{ -600, 0 };
	}

	AttackHandRenderPtr->ChangeAnimation("Cat_Claw_Hand_Loop");
	AttackHandRenderPtr->SetAnimationStartEvent("Cat_Claw_Hand_Loop", 3, std::bind(&Katzenwagen::HandAttackCountFunction, this));
	HandAttackCount = 0;
}
void Katzenwagen::AttackHand_LoopUpdate(float _DeltaTime)
{
	HandAttactTime += _DeltaTime;

	float4 NewPos = float4::LerpClamp(CurHandPosition, HandLerpPosition, HandAttactTime);

	AttackHandRenderPtr->GetTransform()->SetLocalPosition(NewPos);

	if (2 == HandAttackCount)
	{
		ChangeState_AttackHand(AttackHandState::Hit);
		return;
	}
}
void Katzenwagen::AttackHand_LoopEnd()
{
	HandAttactTime = 0.0f;
}

void Katzenwagen::AttackHand_HitStart()
{
	AttackHandRenderPtr->ChangeAnimation("Cat_Claw_Hand_Hit");
}
void Katzenwagen::AttackHand_HitUpdate(float _DeltaTime)
{
	HandAttactTime += _DeltaTime;

	if (0.1f <= HandAttactTime)
	{
		ChangeState_AttackHand(AttackHandState::Outro);
		return;
	}
}
void Katzenwagen::AttackHand_HitEnd()
{
	HandAttactTime = 0.0f;
}

void Katzenwagen::AttackHand_OutroStart()
{
	AttackHandRenderPtr->ChangeAnimation("Cat_Claw_Hand_Outro");
}
void Katzenwagen::AttackHand_OutroUpdate(float _DeltaTime)
{
	HandAttactTime += _DeltaTime;

	float4 NewPos = float4::LerpClamp(HandLerpPosition, CurHandPosition, HandAttactTime);

	AttackHandRenderPtr->GetTransform()->SetLocalPosition(NewPos);

	if (CurHandPosition == NewPos)
	{
		IsClawAttackEnd = true;
		AttackHandRenderPtr->Off();
	}
}
void Katzenwagen::AttackHand_OutroEnd()
{
	HandAttactTime = 0.0f;
}

void Katzenwagen::HandAttackCountFunction()
{
	HandAttackCount += 1;
}
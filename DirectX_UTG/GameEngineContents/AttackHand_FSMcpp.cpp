#include "PrecompileHeader.h"
#include "Katzenwagen.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
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
		AttackHandRenderPtr->GetTransform()->SetLocalPosition({ -800, -90 });
	}
	else
	{
		AttackHandRenderPtr->GetTransform()->SetLocalNegativeScaleX();
		AttackHandRenderPtr->GetTransform()->SetLocalPosition({ 800, -90 });
	}

	AttackHandRenderPtr->ChangeAnimation("Cat_Claw_Hand_Intro");
	InitHandPosition = AttackHandRenderPtr->GetTransform()->GetLocalPosition();

	AttackHandRenderPtr->SetAnimationStartEvent("Cat_Claw_Hand_Loop", 3, std::bind(&Katzenwagen::HandAttackCountFunction, this));
	AttackHandRenderPtr->SetAnimationStartEvent("Cat_Claw_Hand_Intro", 3, std::bind(&Katzenwagen::HandAttackShake, this));

	HandIntroDelayTime = 0.0f;
	HandAttackCount = 0;
	HandSpeed = 700.0f;
}
void Katzenwagen::AttackHand_IntroUpdate(float _DeltaTime)
{
	HandIntroDelayTime += _DeltaTime;

	if (0.35f >= HandIntroDelayTime)
	{
		return;
	}
	else
	{
		AttackCollisionPtr->On();
		AttackHandRenderPtr->On();
	}

	if (AttackHandRenderPtr->IsAnimationEnd())
	{
		ChangeState_AttackHand(AttackHandState::Hit);
		return;
	}

	float MoveDis = HandSpeed * _DeltaTime;

	if (false == Directbool)
	{
		AttackHandRenderPtr->GetTransform()->AddLocalPosition({ MoveDis, 0 });
		AttackCollisionPtr->GetTransform()->AddLocalPosition({ MoveDis, 0 });
	}
	else
	{
		AttackHandRenderPtr->GetTransform()->AddLocalPosition({ -MoveDis, 0 });
		AttackCollisionPtr->GetTransform()->AddLocalPosition({ -MoveDis, 0 });
	}
}
void Katzenwagen::AttackHand_IntroEnd()
{

}

void Katzenwagen::AttackHand_HitStart()
{
	AttackHandRenderPtr->ChangeAnimation("Cat_Claw_Hand_Hit");
}
void Katzenwagen::AttackHand_HitUpdate(float _DeltaTime)
{
	HandAttactTime += _DeltaTime;

	if (0.15f <= HandAttactTime)
	{
		ChangeState_AttackHand(AttackHandState::Outro);
		return;
	}

	if (2 == HandAttackCount)
	{
		return;
	}

	if (0.03f <= HandAttactTime)
	{
		ChangeState_AttackHand(AttackHandState::Loop);
		return;
	}
}
void Katzenwagen::AttackHand_HitEnd()
{
	HandAttactTime = 0.0f;
}

void Katzenwagen::AttackHand_LoopStart()
{
	AttackHandRenderPtr->ChangeAnimation("Cat_Claw_Hand_Loop");
}
void Katzenwagen::AttackHand_LoopUpdate(float _DeltaTime)
{
	float MoveDis = HandSpeed * _DeltaTime;

	if (false == Directbool)
	{
		AttackHandRenderPtr->GetTransform()->AddLocalPosition({ MoveDis, 0 });
		AttackCollisionPtr->GetTransform()->AddLocalPosition({ MoveDis, 0 });
	}
	else
	{
		AttackHandRenderPtr->GetTransform()->AddLocalPosition({ -MoveDis, 0 });
		AttackCollisionPtr->GetTransform()->AddLocalPosition({ -MoveDis, 0 });
	}

	if (true == AttackHandRenderPtr->IsAnimationEnd())
	{
		ChangeState_AttackHand(AttackHandState::Hit);
		return;
	}
}
void Katzenwagen::AttackHand_LoopEnd()
{
}

void Katzenwagen::AttackHand_OutroStart()
{
	CurHandPosition = AttackHandRenderPtr->GetTransform()->GetLocalPosition();

	if (false == Directbool)
	{
		InitHandPosition = InitHandPosition + float4{ -150.0f , 0 };
	}
	else
	{
		InitHandPosition = InitHandPosition + float4{ 150.0f , 0 };
	}

	AttackHandRenderPtr->ChangeAnimation("Cat_Claw_Hand_Outro");
	
	Player::MainPlayer->StartCameraShaking(12);
}
void Katzenwagen::AttackHand_OutroUpdate(float _DeltaTime)
{
	HandAttactTime += _DeltaTime;

	float4 NewPos = float4::LerpClamp(CurHandPosition, InitHandPosition, HandAttactTime * 0.8f);

	AttackHandRenderPtr->GetTransform()->SetLocalPosition(NewPos);
	AttackCollisionPtr->GetTransform()->SetLocalPosition(NewPos);

	if (InitHandPosition == NewPos)
	{
		IsClawAttackEnd = true;
		AttackHandRenderPtr->Off();
		AttackCollisionPtr->Off();
	}
}
void Katzenwagen::AttackHand_OutroEnd()
{
	HandAttactTime = 0.0f;
}

void Katzenwagen::HandAttackCountFunction()
{
	HandAttackCount += 1;
	Player::MainPlayer->StartCameraShaking(8);
}

void Katzenwagen::HandAttackShake()
{
	Player::MainPlayer->StartCameraShaking(8);
}
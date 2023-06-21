#include "PrecompileHeader.h"
#include "Katzenwagen.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "Player.h"
#include "Werner_Werman.h"
#include "Mouse_Map.h"

void Katzenwagen::ChangeState(KatzenwagenState _StateValue)
{
	KatzenwagenState NextState = _StateValue;
	KatzenwagenState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case KatzenwagenState::Intro:
		IntroStart();
		break;
	case KatzenwagenState::Idle:
		IdleStart();
		break;
	case KatzenwagenState::ArmAttack_Intro:
		ArmAttack_IntroStart();
		break;
	case KatzenwagenState::ArmAttack_Loop:
		ArmAttack_LoopStart();
		break;
	case KatzenwagenState::ArmAttack_Outro:
		ArmAttack_OutroStart();
		break;
	case KatzenwagenState::GhostSpawn_Intro:
		GhostSpawn_IntroStart();
		break;
	case KatzenwagenState::GhostSpawn_Loop:
		GhostSpawn_LoopStart();
		break;
	case KatzenwagenState::GhostSpawn_Outro:
		GhostSpawn_OutroStart();
		break;
	case KatzenwagenState::Death:
		DeathStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case KatzenwagenState::Intro:
		IntroEnd();
		break;
	case KatzenwagenState::Idle:
		IdleEnd();
		break;
	case KatzenwagenState::ArmAttack_Intro:
		ArmAttack_IntroEnd();
		break;
	case KatzenwagenState::ArmAttack_Loop:
		ArmAttack_LoopEnd();
		break;
	case KatzenwagenState::ArmAttack_Outro:
		ArmAttack_OutroEnd();
		break;
	case KatzenwagenState::GhostSpawn_Intro:
		GhostSpawn_IntroEnd();
		break;
	case KatzenwagenState::GhostSpawn_Loop:
		GhostSpawn_LoopEnd();
		break;
	case KatzenwagenState::GhostSpawn_Outro:
		GhostSpawn_OutroEnd();
		break;
	case KatzenwagenState::Death:
		DeathEnd();
		break;
	default:
		break;
	}
}

void Katzenwagen::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case KatzenwagenState::Intro:
		IntroUpdate(_DeltaTime);
		break;
	case KatzenwagenState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	case KatzenwagenState::ArmAttack_Intro:
		ArmAttack_IntroUpdate(_DeltaTime);
		break;
	case KatzenwagenState::ArmAttack_Loop:
		ArmAttack_LoopUpdate(_DeltaTime);
		break;
	case KatzenwagenState::ArmAttack_Outro:
		ArmAttack_OutroUpdate(_DeltaTime);
		break;
	case KatzenwagenState::GhostSpawn_Intro:
		GhostSpawn_IntroUpdate(_DeltaTime);
		break;
	case KatzenwagenState::GhostSpawn_Loop:
		GhostSpawn_LoopUpdate(_DeltaTime);
		break;
	case KatzenwagenState::GhostSpawn_Outro:
		GhostSpawn_OutroUpdate(_DeltaTime);
		break;
	case KatzenwagenState::Death:
		DeathUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Katzenwagen::IntroStart()
{
	BodyRenderPtr->On();

	BodyRenderPtr->ChangeAnimation("Cat_Intro_Body");

	BodyRenderPtr->SetAnimationStartEvent("Cat_Intro_Body", 8, std::bind(&Katzenwagen::IntroAnimationSetting, this));
}
void Katzenwagen::IntroUpdate(float _DeltaTime)
{
	if (true == HeadRenderPtr->IsUpdate())
	{
		IntroHeadPositionSetting();

		if (true == HeadRenderPtr->IsAnimationEnd())
		{
			ChangeState(KatzenwagenState::Idle);
			return;
		}
	}
}
void Katzenwagen::IntroEnd()
{

}

void Katzenwagen::IdleStart()
{
	if (nullptr == HeadParent)
	{
		HeadParent = CreateComponent<GameEngineSpriteRenderer>();
		HeadParent->SetScaleToTexture("RedBox.png");
		HeadParent->GetTransform()->SetLocalScale({ 1, 1, 1 });
		HeadParent->ColorOptionValue.MulColor.a = 0.0f;
	}

	HeadRenderPtr->ChangeAnimation("Cat_Idle_Head_Left");
	HeadRenderPtr->GetTransform()->SetParent(HeadParent->GetTransform());
	HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -20, -10 });

	EXCollisionPtr->On();
	BodyCollisionPtr->On();
	BodyUpRenderPtr->On();

	BodyCollisionPtr->GetTransform()->SetLocalPosition({ 0, 10, -50 });
	EXCollisionPtr->GetTransform()->SetLocalPosition({ 0, 10, -50 });
}
void Katzenwagen::IdleUpdate(float _DeltaTime)
{
	if (true == Werner_Werman::WernerWermanPtr->IsStageEnd)
	{
		ChangeState(KatzenwagenState::Death);
		return;
	}

	bool IsShakeEnd = false;

	if (true == HeadRenderPtr->FindAnimation("Cat_Idle_Head_Left")->IsEnd())
	{
		Directbool = true;
		HeadRenderPtr->ChangeAnimation("Cat_Idle_Head_Right", false);
	}

	if (true == HeadRenderPtr->FindAnimation("Cat_Idle_Head_Right")->IsEnd())
	{
		Directbool = false;
		HeadRenderPtr->ChangeAnimation("Cat_Idle_Head_Left", false);
	}

	AttactDelayTime += _DeltaTime;

	bool IsAttackStart = false;

	if (9 == HeadRenderPtr->GetCurrentFrame())
	{
		IsAttackStart = true;
	}
	else
	{
		IsAttackStart = false;
	}

	//if (true == IsAttackStart && 3.f <= AttactDelayTime)
	//{
	//	Directbool = !Directbool;

	//	if (true == IsLeft)
	//	{
	//		IsLeft = false;
	//		AttactDelayTime -= 1.5f;
	//		return;
	//	}

	//	ChangeState(KatzenwagenState::ArmAttack_Intro);
	//	return;
	//}

	if (true == IsAttackStart && 3.f <= AttactDelayTime)
	{
		Directbool = false;

		if (false == Directbool) // 왼쪽 고개
		{
			HeadParent->GetTransform()->SetLocalPositiveScaleX();
		}

		ChangeState(KatzenwagenState::GhostSpawn_Intro);
		return;
	}

	if (false == Directbool) // 왼쪽 고개
	{
		HeadParent->GetTransform()->SetLocalPositiveScaleX();
	}
	else                     // 오른쪽 고개
	{
		HeadParent->GetTransform()->SetLocalNegativeScaleX();
	}
}
void Katzenwagen::IdleEnd()
{
	AttactDelayTime = 0.0f;
}

void Katzenwagen::ArmAttack_IntroStart()
{
	HeadRenderPtr->GetTransform()->SetLocalPosition({ -125, -20, 1 });

	if (false == Directbool)
	{
		IsLeft = true;
		HeadParent->GetTransform()->SetLocalPositiveScaleX();
		LeftHandRenderPtr->Off();
	}
	else
	{
		IsLeft = false;
		HeadParent->GetTransform()->SetLocalNegativeScaleX();
		RightHandRenderPtr->Off();
	}

	HeadRenderPtr->ChangeAnimation("Cat_Claw_Head_Intro");
}
void Katzenwagen::ArmAttack_IntroUpdate(float _DeltaTime)
{
	if (true == Werner_Werman::WernerWermanPtr->IsStageEnd)
	{
		ChangeState(KatzenwagenState::Death);
		return;
	}

	if (true == HeadRenderPtr->IsAnimationEnd())
	{
		ChangeState(KatzenwagenState::ArmAttack_Loop);
		return;
	}
}
void Katzenwagen::ArmAttack_IntroEnd()
{

}

void Katzenwagen::ArmAttack_LoopStart()
{
	CurHeadPosition = HeadRenderPtr->GetTransform()->GetLocalPosition();
	LerpPosition = CurHeadPosition + float4{ -55, -20 };

	CurHeadPosition2 = BodyCollisionPtr->GetTransform()->GetLocalPosition() + float4{ 100, 0 };
	LerpPosition2 = CurHeadPosition2 + float4{ 55, -20 };

	HeadRenderPtr->ChangeAnimation("Cat_Claw_Head_Loop");
	ClawCreateCount = 1;
	IsClawAttackEnd = false;
}
void Katzenwagen::ArmAttack_LoopUpdate(float _DeltaTime)
{
	if (true == Werner_Werman::WernerWermanPtr->IsStageEnd)
	{
		ChangeState(KatzenwagenState::Death);
		return;
	}

	AttactDelayTime += _DeltaTime;

	float4 NewPos = float4::LerpClamp(CurHeadPosition, LerpPosition, AttactDelayTime);

	HeadRenderPtr->GetTransform()->SetLocalPosition(NewPos);

	if (false == Directbool)
	{
		BodyCollisionPtr->GetTransform()->SetLocalPosition(NewPos);
		EXCollisionPtr->GetTransform()->SetLocalPosition(NewPos);
	}
	else
	{
		float4 NewPos2 = float4::LerpClamp(CurHeadPosition2, LerpPosition2, AttactDelayTime);

		BodyCollisionPtr->GetTransform()->SetLocalPosition(NewPos2);
		EXCollisionPtr->GetTransform()->SetLocalPosition(NewPos2);
	}

	if (1 == ClawCreateCount)
	{
		ClawCreateCount = 0;
		ChangeState_AttackHand(AttackHandState::Intro);
	}

	UpdateState_AttackHand(_DeltaTime);

	if (true == HeadRenderPtr->IsAnimationEnd() && 2.0f <= AttactDelayTime && LerpPosition == NewPos && true == IsClawAttackEnd)
	{
		ChangeState(KatzenwagenState::ArmAttack_Outro);
		return;
	}
}
void Katzenwagen::ArmAttack_LoopEnd()
{
	AttactDelayTime = 0.0f;
}

void Katzenwagen::ArmAttack_OutroStart()
{
	HeadRenderPtr->ChangeAnimation("Cat_Claw_Head_Outro");
}
void Katzenwagen::ArmAttack_OutroUpdate(float _DeltaTime)
{
	if (true == Werner_Werman::WernerWermanPtr->IsStageEnd)
	{
		ChangeState(KatzenwagenState::Death);
		return;
	}

	if (true == HeadRenderPtr->IsAnimationEnd())
	{
		ChangeState(KatzenwagenState::Idle);
		return;
	}
}
void Katzenwagen::ArmAttack_OutroEnd()
{
	LeftHandRenderPtr->On();
	RightHandRenderPtr->On();
}

void Katzenwagen::GhostSpawn_IntroStart()
{
	HeadRenderPtr->GetTransform()->SetLocalPosition({ 10, -20, -10 });
	HeadRenderPtr->ChangeAnimation("Cat_Ghost_Spawn_Head_Intro");
}
void Katzenwagen::GhostSpawn_IntroUpdate(float _DeltaTime)
{
	if (true == Werner_Werman::WernerWermanPtr->IsStageEnd)
	{
		ChangeState(KatzenwagenState::Death);
		return;
	}

	if (true == HeadRenderPtr->IsAnimationEnd())
	{
		ChangeState(KatzenwagenState::GhostSpawn_Loop);
		return;
	}
}
void Katzenwagen::GhostSpawn_IntroEnd()
{

}

void Katzenwagen::GhostSpawn_LoopStart()
{
	HeadRenderPtr->ChangeAnimation("Cat_Ghost_Spawn_Head_Loop");
	HeadRenderPtr->SetAnimationStartEvent("Cat_Ghost_Spawn_Head_Loop", 7, std::bind(&Katzenwagen::CreateGhostMouse, this));
}
void Katzenwagen::GhostSpawn_LoopUpdate(float _DeltaTime)
{
	if (true == Werner_Werman::WernerWermanPtr->IsStageEnd)
	{
		ChangeState(KatzenwagenState::Death);
		return;
	}

	AttactDelayTime += _DeltaTime;

	if (2.0f <= AttactDelayTime)
	{
		ChangeState(KatzenwagenState::GhostSpawn_Outro);
		return;
	}
}
void Katzenwagen::GhostSpawn_LoopEnd()
{
	AttactDelayTime = 0.0f;
}

void Katzenwagen::GhostSpawn_OutroStart()
{
	HeadRenderPtr->ChangeAnimation("Cat_Ghost_Spawn_Head_Outro");
}
void Katzenwagen::GhostSpawn_OutroUpdate(float _DeltaTime)
{
	if (true == Werner_Werman::WernerWermanPtr->IsStageEnd)
	{
		ChangeState(KatzenwagenState::Death);
		return;
	}

	if (10 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -20, -10 });
	}

	if (true == HeadRenderPtr->IsAnimationEnd())
	{
		ChangeState(KatzenwagenState::Idle);
		return;
	}
}
void Katzenwagen::GhostSpawn_OutroEnd()
{

}

void Katzenwagen::DeathStart()
{
	BodyCollisionRenderPtr->Off();
	EXCollisionRenderPtr->Off();
	BodyCollisionPtr->Off();
	EXCollisionPtr->Off();

	BodyUpRenderPtr->Off();
	LeftHandRenderPtr->Off();
	RightHandRenderPtr->Off();

	HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -40, -10 });
	BodyRenderPtr->GetTransform()->AddLocalPosition({ 0, 20 });

	BodyRenderPtr->ChangeAnimation("Cat_Death_Body");
	HeadRenderPtr->ChangeAnimation("Cat_Death_HeadObject");
	HeadRenderPtr->SetAnimationStartEvent("Cat_Death_HeadObject", 13, std::bind(&Katzenwagen::DeathHeadObjectLoopAnimation, this));
	HeadRenderPtr->SetAnimationStartEvent("Cat_Death_HeadObject", 9, std::bind(&Katzenwagen::CreateDeathDust, this));

	ExplosionTime = 0.4f;
}
void Katzenwagen::DeathUpdate(float _DeltaTime)
{
	ExplosionTime += _DeltaTime;

	if (0.4f <= ExplosionTime)
	{
		ExplosionTime = 0.0f;
		Player::MainPlayer->StartCameraShaking(6);
		CreateDeathExplosion(_DeltaTime);
	}
}
void Katzenwagen::DeathEnd()
{

}

void Katzenwagen::DeathHeadObjectLoopAnimation()
{
	HeadRenderPtr->ChangeAnimation("Cat_Death_HeadObject_Loop");
}

void Katzenwagen::IntroHeadPositionSetting()
{
	if (54 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -20, -10 });
	}
	else if (53 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -20, -10 });
	}
	else if (52 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -20, -10 });
	}
	else if (51 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -20, -10 });
	}
	else if (50 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -40, -10 });
	}
	else if (49 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -60, -10 });
	}
	else if (48 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -80, -10 });
	}
	else if (37 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -105, -10 });
	}
}
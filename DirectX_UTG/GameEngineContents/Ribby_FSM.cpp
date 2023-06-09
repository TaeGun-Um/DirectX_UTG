#include "PrecompileHeader.h"
#include "Ribby.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Croak.h"

void Ribby::ChangeState(RibbyState _StateValue)
{
	RibbyState NextState = _StateValue;
	RibbyState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case RibbyState::Intro:
		IntroStart();
		break;
	case RibbyState::Intro_Loop:
		Intro_LoopStart();
		break;
	case RibbyState::Intro_End:
		Intro_EndStart();
		break;
	case RibbyState::Idle:
		IdleStart();
		break;
	case RibbyState::FistAttack_Intro:
		FistAttack_IntroStart();
		break;
	case RibbyState::FistAttack_Intro_Loop:
		FistAttack_Intro_LoopStart();
		break;
	case RibbyState::FistAttack_Intro_Out:
		FistAttack_Intro_OutStart();
		break;
	case RibbyState::FistAttack_Loop:
		FistAttack_LoopStart();
		break;
	case RibbyState::FistAttack_End:
		FistAttack_EndStart();
		break;
	case RibbyState::Roll_Intro:
		Roll_IntroStart();
		break;
	case RibbyState::Roll_Intro_Loop:
		Roll_Intro_LoopStart();
		break;
	case RibbyState::Roll_Intro_Out:
		Roll_Intro_OutStart();
		break;
	case RibbyState::Roll_Loop:
		Roll_LoopStart();
		break;
	case RibbyState::Roll_End:
		Roll_EndStart();
		break;
	case RibbyState::ClapAttack_Intro:
		ClapAttack_IntroStart();
		break;
	case RibbyState::ClapAttack:
		ClapAttackStart();
		break;
	case RibbyState::ClapAttack_Loop:
		ClapAttack_LoopStart();
		break;
	case RibbyState::ClapAttack_LoopBack:
		ClapAttack_LoopBackStart();
		break;
	case RibbyState::ClapAttack_End:
		ClapAttack_EndStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case RibbyState::Intro:
		IntroEnd();
		break;
	case RibbyState::Intro_Loop:
		Intro_LoopEnd();
		break;
	case RibbyState::Intro_End:
		Intro_EndEnd();
		break;
	case RibbyState::Idle:
		IdleEnd();
		break;
	case RibbyState::FistAttack_Intro:
		FistAttack_IntroEnd();
		break;
	case RibbyState::FistAttack_Intro_Loop:
		FistAttack_Intro_LoopEnd();
		break;
	case RibbyState::FistAttack_Intro_Out:
		FistAttack_Intro_OutEnd();
		break;
	case RibbyState::FistAttack_Loop:
		FistAttack_LoopEnd();
		break;
	case RibbyState::FistAttack_End:
		FistAttack_EndEnd();
		break;
	case RibbyState::Roll_Intro:
		Roll_IntroEnd();
		break;
	case RibbyState::Roll_Intro_Loop:
		Roll_Intro_LoopEnd();
		break;
	case RibbyState::Roll_Intro_Out:
		Roll_Intro_OutEnd();
		break;
	case RibbyState::Roll_Loop:
		Roll_LoopEnd();
		break;
	case RibbyState::Roll_End:
		Roll_EndEnd();
		break;
	case RibbyState::ClapAttack_Intro:
		ClapAttack_IntroEnd();
		break;
	case RibbyState::ClapAttack:
		ClapAttackEnd();
		break;
	case RibbyState::ClapAttack_Loop:
		ClapAttack_LoopEnd();
		break;
	case RibbyState::ClapAttack_LoopBack:
		ClapAttack_LoopBackEnd();
		break;
	case RibbyState::ClapAttack_End:
		ClapAttack_EndEnd();
		break;
	default:
		break;
	}
}

void Ribby::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case RibbyState::Intro:
		IntroUpdate(_DeltaTime);
		break;
	case RibbyState::Intro_Loop:
		Intro_LoopUpdate(_DeltaTime);
		break;
	case RibbyState::Intro_End:
		Intro_EndUpdate(_DeltaTime);
		break;
	case RibbyState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	case RibbyState::FistAttack_Intro:
		FistAttack_IntroUpdate(_DeltaTime);
		break;
	case RibbyState::FistAttack_Intro_Loop:
		FistAttack_Intro_LoopUpdate(_DeltaTime);
		break;
	case RibbyState::FistAttack_Intro_Out:
		FistAttack_Intro_OutUpdate(_DeltaTime);
		break;
	case RibbyState::FistAttack_Loop:
		FistAttack_LoopUpdate(_DeltaTime);
		break;
	case RibbyState::FistAttack_End:
		FistAttack_EndUpdate(_DeltaTime);
		break;
	case RibbyState::Roll_Intro:
		Roll_IntroUpdate(_DeltaTime);
		break;
	case RibbyState::Roll_Intro_Loop:
		Roll_Intro_LoopUpdate(_DeltaTime);
		break;
	case RibbyState::Roll_Intro_Out:
		Roll_Intro_OutUpdate(_DeltaTime);
		break;
	case RibbyState::Roll_Loop:
		Roll_LoopUpdate(_DeltaTime);
		break;
	case RibbyState::Roll_End:
		Roll_EndUpdate(_DeltaTime);
		break;
	case RibbyState::ClapAttack_Intro:
		ClapAttack_IntroUpdate(_DeltaTime);
		break;
	case RibbyState::ClapAttack:
		ClapAttackUpdate(_DeltaTime);
		break;
	case RibbyState::ClapAttack_Loop:
		ClapAttack_LoopUpdate(_DeltaTime);
		break;
	case RibbyState::ClapAttack_LoopBack:
		ClapAttack_LoopBackUpdate(_DeltaTime);
		break;
	case RibbyState::ClapAttack_End:
		ClapAttack_EndUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Ribby::IntroStart()
{
	RenderPtr->ChangeAnimation("Ribby_Intro");
	BodyCollisionPtr->GetTransform()->SetLocalScale({ 150, 270, 1 });
	EXCollisionPtr->GetTransform()->SetLocalScale({ 150, 270, 1 });

	BodyCollisionPtr->GetTransform()->SetLocalPosition({ 60, -40 });
	EXCollisionPtr->GetTransform()->SetLocalPosition({ 60, -40 });
}
void Ribby::IntroUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(RibbyState::Intro_Loop);
		return;
	}
}
void Ribby::IntroEnd()
{
	
}

void Ribby::Intro_LoopStart()
{
	RenderPtr->ChangeAnimation("Ribby_Intro_Loop");
}
void Ribby::Intro_LoopUpdate(float _DeltaTime)
{
	IntroLoopTime += _DeltaTime;

	if (true == RenderPtr->IsAnimationEnd() && 0.6f <= IntroLoopTime)
	{
		ChangeState(RibbyState::Intro_End);
		return;
	}
}
void Ribby::Intro_LoopEnd()
{
	IntroLoopTime = 0.0f;
}

void Ribby::Intro_EndStart()
{
	RenderPtr->ChangeAnimation("Ribby_Intro_End");
}
void Ribby::Intro_EndUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(RibbyState::Idle);
		return;
	}
}
void Ribby::Intro_EndEnd()
{
	IsIntro = false;
}

void Ribby::IdleStart()
{
	RenderPtr->ChangeAnimation("Ribby_Idle");
}
void Ribby::IdleUpdate(float _DeltaTime)
{
	if (true == IsClap)
	{
		ClapDelayTime += _DeltaTime;
	}

	if (true == IsClap && 1.5f <= ClapDelayTime)
	{
		ClapCount = 4;
		ChangeState(RibbyState::ClapAttack_Intro);
		return;
	}

	if (true == IsRoll)
	{
		ChangeState(RibbyState::Roll_Intro);
		return;
	}

	if (true == IsIntro)
	{
		ChangeState(RibbyState::Intro);
		return;
	}

	if (true == IsFistAttak)
	{
		ChangeState(RibbyState::FistAttack_Intro);
		return;
	}
}
void Ribby::IdleEnd()
{
	IdleDelayTime = 0.0f;
	ClapDelayTime = 0.0f;
}

void Ribby::FistAttack_IntroStart()
{
	RenderPtr->ChangeAnimation("Ribby_FistAttack_Intro");
}
void Ribby::FistAttack_IntroUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(RibbyState::FistAttack_Intro_Loop);
		return;
	}
}
void Ribby::FistAttack_IntroEnd()
{

}

void Ribby::FistAttack_Intro_LoopStart()
{
	RenderPtr->ChangeAnimation("Ribby_FistAttack_Intro_Loop");
}
void Ribby::FistAttack_Intro_LoopUpdate(float _DeltaTime)
{
	FistLoopDelayTime += _DeltaTime;

	if (true == RenderPtr->IsAnimationEnd() && 1.5f <= FistLoopDelayTime)
	{
		ChangeState(RibbyState::FistAttack_Intro_Out);
		return;
	}
}
void Ribby::FistAttack_Intro_LoopEnd()
{
	FistLoopDelayTime = 0.0f;
}

void Ribby::FistAttack_Intro_OutStart()
{
	RenderPtr->ChangeAnimation("Ribby_FistAttack_Intro_out");

	BodyCollisionPtr->GetTransform()->SetLocalScale({ 200, 270, 1 });
	EXCollisionPtr->GetTransform()->SetLocalScale({ 200, 270, 1 });

	BodyCollisionPtr->GetTransform()->SetLocalPosition({ -20, -40 });
	EXCollisionPtr->GetTransform()->SetLocalPosition({ -20, -40 });
}
void Ribby::FistAttack_Intro_OutUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(RibbyState::FistAttack_Loop);
		return;
	}
}
void Ribby::FistAttack_Intro_OutEnd()
{

}

void Ribby::FistAttack_LoopStart()
{
	RenderPtr->ChangeAnimation("Ribby_FistAttack_Loop");
}
void Ribby::FistAttack_LoopUpdate(float _DeltaTime)
{
	FistAttackDelayTime += _DeltaTime;

	if (0.9f <= FistAttackDelayTime && 9 > FistCreateCount)
	{
		FistAttackDelayTime = 0.0f;
		CreateFistProjectile();
		FistCreateCount++;
	}

	if (0.5f <= FistAttackDelayTime && 9 == FistCreateCount)
	{
		ChangeState(RibbyState::FistAttack_End);
		return;
	}
}
void Ribby::FistAttack_LoopEnd()
{
	FistCreateCount = 0;
	ParryFistCount = 1;
	ParryFistCreate = false;
	FistAttackDelayTime = 0.0f;
}

void Ribby::FistAttack_EndStart()
{
	RenderPtr->ChangeAnimation("Ribby_FistAttack_End");

	BodyCollisionPtr->GetTransform()->SetLocalScale({ 150, 270, 1 });
	EXCollisionPtr->GetTransform()->SetLocalScale({ 150, 270, 1 });

	BodyCollisionPtr->GetTransform()->SetLocalPosition({ 60, -40 });
	EXCollisionPtr->GetTransform()->SetLocalPosition({ 60, -40 });
}
void Ribby::FistAttack_EndUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(RibbyState::Idle);
		return;
	}
}
void Ribby::FistAttack_EndEnd()
{
	IsFistAttak = false;
}

void Ribby::Roll_IntroStart()
{
	RenderPtr->ChangeAnimation("Ribby_Roll_Intro");
}
void Ribby::Roll_IntroUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(RibbyState::Roll_Intro_Loop);
		return;
	}
}
void Ribby::Roll_IntroEnd()
{

}

void Ribby::Roll_Intro_LoopStart()
{
	RenderPtr->ChangeAnimation("Ribby_Roll_Intro_Loop");

	BodyCollisionPtr->GetTransform()->SetLocalScale({ 200, 200, 1 });
	EXCollisionPtr->GetTransform()->SetLocalScale({ 200, 200, 1 });

	BodyCollisionPtr->GetTransform()->SetLocalPosition({ -10, -100 });
	EXCollisionPtr->GetTransform()->SetLocalPosition({ -10, -100 });
}
void Ribby::Roll_Intro_LoopUpdate(float _DeltaTime)
{
	LoopInterDelayTime += _DeltaTime;

	if (1.5f <= LoopInterDelayTime)
	{
		ChangeState(RibbyState::Roll_Intro_Out);
		return;
	}
}
void Ribby::Roll_Intro_LoopEnd()
{
	LoopInterDelayTime = 0.0f;
}

void Ribby::Roll_Intro_OutStart()
{
	RenderPtr->ChangeAnimation("Ribby_Roll_Intro_Out");
}
void Ribby::Roll_Intro_OutUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(RibbyState::Roll_Loop);
		return;
	}
}
void Ribby::Roll_Intro_OutEnd()
{

}

void Ribby::Roll_LoopStart()
{
	RollStartPosition = GetTransform()->GetLocalPosition();

	if (false == Directbool)
	{
		RollEndPosition = { (RollStartPosition.x - 1500.0f) , RollStartPosition.y };
	}
	else if (true == Directbool)
	{
		float XPos = Croak::CroakPtr->GetTransform()->GetLocalPosition().x;
		float YPos = Croak::CroakPtr->GetTransform()->GetLocalPosition().y;

		RollEndPosition = float4{ XPos , YPos } + float4{ 0, -80 };

		BodyCollisionPtr->GetTransform()->SetLocalScale({ 170, 170, 1 });
		EXCollisionPtr->GetTransform()->SetLocalScale({ 170, 170, 1 });
	}

	BodyCollisionPtr->GetTransform()->SetLocalPosition({ -50, -100 });
	EXCollisionPtr->GetTransform()->SetLocalPosition({ -50, -100 });

	RenderPtr->ChangeAnimation("Ribby_Roll_Loop");
}
void Ribby::Roll_LoopUpdate(float _DeltaTime)
{
	float4 CurPos = GetTransform()->GetLocalPosition();

	if (false == Directbool)
	{
		if (RollEndPosition.x >= CurPos.x)
		{
			RollDelayTime += _DeltaTime;

			if (1.0f <= RollDelayTime)
			{
				ChangeState(RibbyState::Roll_End);
			}

			return;
		}

		RollStartPosition.x += 200.0f * _DeltaTime;
		float4 Movedir = float4::Zero;

		Movedir = (RollStartPosition - CurPos);

		MoveDistance = -(Movedir * 1.2f * _DeltaTime);

		GetTransform()->AddWorldPosition(MoveDistance);
	}
	else if (true == Directbool)
	{
		if (RollEndPosition.x - 315.0f <= CurPos.x)
		{
			Off();
			Croak::CroakPtr->IsMorph = true;
			return;
		}

		RollMoveTime += _DeltaTime * 0.8f;

		float4 Dist = float4::Lerp(RollStartPosition, RollEndPosition, RollMoveTime);

		float4 Movedir = float4::Zero;

		Movedir = (Dist - CurPos);

		MoveDistance = Movedir * 2.f * _DeltaTime;

		GetTransform()->AddLocalPosition(MoveDistance);
	}
}
void Ribby::Roll_LoopEnd()
{
	BodyCollisionPtr->Off();
	EXCollisionPtr->Off();

	BodyCollisionRenderPtr->Off();
	EXCollisionRenderPtr->Off();
}

void Ribby::Roll_EndStart()
{
	GetTransform()->SetLocalPosition({ RollEndPosition.x + 750.0f, RollEndPosition.y });
	Directbool = true;
	RenderPtr->ChangeAnimation("Ribby_Roll_End");

	BodyCollisionPtr->GetTransform()->SetLocalPosition({ 200, -100 });
	EXCollisionPtr->GetTransform()->SetLocalPosition({ 200, -100 });
}
void Ribby::Roll_EndUpdate(float _DeltaTime)
{
	if (9 == RenderPtr->GetCurrentFrame())
	{
		GetTransform()->SetLocalPosition({ RollEndPosition.x + 630.0f, RollEndPosition.y });

		BodyCollisionPtr->GetTransform()->SetLocalScale({ 150, 270, 1 });
		EXCollisionPtr->GetTransform()->SetLocalScale({ 150, 270, 1 });

		BodyCollisionPtr->GetTransform()->SetLocalPosition({ 60, -40 });
		EXCollisionPtr->GetTransform()->SetLocalPosition({ 60, -40 });
	}

	if (10 == RenderPtr->GetCurrentFrame())
	{
		BodyCollisionPtr->On();
		EXCollisionPtr->On();
	}

	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(RibbyState::Idle);
		return;
	}
}
void Ribby::Roll_EndEnd()
{
	IsRoll = false;
}

void Ribby::ClapAttack_IntroStart()
{
	RenderPtr->ChangeAnimation("Ribby_ClapAttack_Intro");
}
void Ribby::ClapAttack_IntroUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(RibbyState::ClapAttack);
		return;
	}
}
void Ribby::ClapAttack_IntroEnd()
{

}

void Ribby::ClapAttackStart()
{
	CreateBallCount = 1;
	--ClapCount;
	RenderPtr->ChangeAnimation("Ribby_ClapAttack");
}
void Ribby::ClapAttackUpdate(float _DeltaTime)
{
	if (3 == RenderPtr->GetCurrentFrame() && 1 == CreateBallCount)
	{
		CreateBallCount = 0;
		CreateBallProjectile();
	}

	if (true == RenderPtr->IsAnimationEnd() && 0 >= ClapCount)
	{
		ChangeState(RibbyState::ClapAttack_End);
		return;
	}
	else if (true == RenderPtr->IsAnimationEnd() && 0 < ClapCount)
	{
		if (1 == ClapCount)
		{
			int RandC = GameEngineRandom::MainRandom.RandomInt(0, 2);

			if (0 == RandC)
			{
				ClapCount = 0;
				ChangeState(RibbyState::ClapAttack_End);
				return;
			}
		}

		ChangeState(RibbyState::ClapAttack_LoopBack);
		return;
	}
}
void Ribby::ClapAttackEnd()
{

}

void Ribby::ClapAttack_LoopStart()
{
	RenderPtr->ChangeAnimation("Ribby_ClapAttack_Loop");
}
void Ribby::ClapAttack_LoopUpdate(float _DeltaTime)
{
	ClapLoopTime += _DeltaTime;

	if (1.0f <= ClapLoopTime)
	{
		ChangeState(RibbyState::ClapAttack);
		return;
	}
}
void Ribby::ClapAttack_LoopEnd()
{
	ClapLoopTime = 0.0f;
}

void Ribby::ClapAttack_LoopBackStart()
{
	RenderPtr->ChangeAnimation("Ribby_ClapAttack_LoopBack");
}
void Ribby::ClapAttack_LoopBackUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(RibbyState::ClapAttack_Loop);
		return;
	}
}
void Ribby::ClapAttack_LoopBackEnd()
{

}

void Ribby::ClapAttack_EndStart()
{
	RenderPtr->ChangeAnimation("Ribby_ClapAttack_End");
}
void Ribby::ClapAttack_EndUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(RibbyState::Idle);
		return;
	}
}
void Ribby::ClapAttack_EndEnd()
{
}
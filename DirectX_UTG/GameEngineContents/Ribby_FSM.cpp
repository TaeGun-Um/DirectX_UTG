#include "PrecompileHeader.h"
#include "Ribby.h"

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
	case RibbyState::Roll_Intro:
		Roll_IntroStart();
		break;
	case RibbyState::Roll_Intro_Loop:
		Roll_Intro_LoopStart();
		break;
	case RibbyState::Roll_Loop:
		Roll_LoopStart();
		break;
	case RibbyState::Roll_End:
		Roll_EndStart();
		break;
	case RibbyState::FistAttack_Intro:
		FistAttack_IntroStart();
		break;
	case RibbyState::FistAttack_Loop:
		FistAttack_LoopStart();
		break;
	case RibbyState::FistAttack_End:
		FistAttack_EndStart();
		break;
	case RibbyState::ClapAttack_Intro:
		ClapAttack_IntroStart();
		break;
	case RibbyState::ClapAttack_Boil:
		ClapAttack_BoilStart();
		break;
	case RibbyState::ClapAttack:
		ClapAttackStart();
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
	case RibbyState::Roll_Intro:
		Roll_IntroEnd();
		break;
	case RibbyState::Roll_Intro_Loop:
		Roll_Intro_LoopEnd();
		break;
	case RibbyState::Roll_Loop:
		Roll_LoopEnd();
		break;
	case RibbyState::Roll_End:
		Roll_EndEnd();
		break;
	case RibbyState::FistAttack_Intro:
		FistAttack_IntroEnd();
		break;
	case RibbyState::FistAttack_Loop:
		FistAttack_LoopEnd();
		break;
	case RibbyState::FistAttack_End:
		FistAttack_EndEnd();
		break;
	case RibbyState::ClapAttack_Intro:
		ClapAttack_IntroEnd();
		break;
	case RibbyState::ClapAttack_Boil:
		ClapAttack_BoilEnd();
		break;
	case RibbyState::ClapAttack:
		ClapAttackEnd();
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
	case RibbyState::Roll_Intro:
		Roll_IntroUpdate(_DeltaTime);
		break;
	case RibbyState::Roll_Intro_Loop:
		Roll_Intro_LoopUpdate(_DeltaTime);
		break;
	case RibbyState::Roll_Loop:
		Roll_LoopUpdate(_DeltaTime);
		break;
	case RibbyState::Roll_End:
		Roll_EndUpdate(_DeltaTime);
		break;
	case RibbyState::FistAttack_Intro:
		FistAttack_IntroUpdate(_DeltaTime);
		break;
	case RibbyState::FistAttack_Loop:
		FistAttack_LoopUpdate(_DeltaTime);
		break;
	case RibbyState::FistAttack_End:
		FistAttack_EndUpdate(_DeltaTime);
		break;
	case RibbyState::ClapAttack_Intro:
		ClapAttack_IntroUpdate(_DeltaTime);
		break;
	case RibbyState::ClapAttack_Boil:
		ClapAttack_BoilUpdate(_DeltaTime);
		break;
	case RibbyState::ClapAttack:
		ClapAttackUpdate(_DeltaTime);
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

	if (true == RenderPtr->IsAnimationEnd() && 1.f <= IntroLoopTime)
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
	if (true == IsIntro)
	{
		ChangeState(RibbyState::Intro);
		return;
	}
}
void Ribby::IdleEnd()
{

}

void Ribby::Roll_IntroStart()
{

}
void Ribby::Roll_IntroUpdate(float _DeltaTime)
{

}
void Ribby::Roll_IntroEnd()
{

}

void Ribby::Roll_Intro_LoopStart()
{

}
void Ribby::Roll_Intro_LoopUpdate(float _DeltaTime)
{

}
void Ribby::Roll_Intro_LoopEnd()
{

}
void Ribby::Roll_LoopStart()
{

}
void Ribby::Roll_LoopUpdate(float _DeltaTime)
{

}
void Ribby::Roll_LoopEnd()
{

}

void Ribby::Roll_EndStart()
{

}
void Ribby::Roll_EndUpdate(float _DeltaTime)
{

}
void Ribby::Roll_EndEnd()
{

}

void Ribby::FistAttack_IntroStart()
{

}
void Ribby::FistAttack_IntroUpdate(float _DeltaTime)
{

}
void Ribby::FistAttack_IntroEnd()
{

}

void Ribby::FistAttack_EndStart()
{

}
void Ribby::FistAttack_EndUpdate(float _DeltaTime) 
{

}
void Ribby::FistAttack_EndEnd()
{

}

void Ribby::FistAttack_LoopStart()
{

}
void Ribby::FistAttack_LoopUpdate(float _DeltaTime)
{

}
void Ribby::FistAttack_LoopEnd()
{

}

void Ribby::ClapAttack_IntroStart()
{

}
void Ribby::ClapAttack_IntroUpdate(float _DeltaTime)
{

}
void Ribby::ClapAttack_IntroEnd()
{

}

void Ribby::ClapAttack_BoilStart()
{

}
void Ribby::ClapAttack_BoilUpdate(float _DeltaTime)
{

}
void Ribby::ClapAttack_BoilEnd()
{

}

void Ribby::ClapAttackStart()
{

}
void Ribby::ClapAttackUpdate(float _DeltaTime)
{

}
void Ribby::ClapAttackEnd()
{

}

void Ribby::ClapAttack_EndStart()
{

}
void Ribby::ClapAttack_EndUpdate(float _DeltaTime)
{

}
void Ribby::ClapAttack_EndEnd()
{

}
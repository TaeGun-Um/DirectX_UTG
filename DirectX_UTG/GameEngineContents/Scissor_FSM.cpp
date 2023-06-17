#include "PrecompileHeader.h"
#include "Werner_Werman.h"

void Werner_Werman::ChangeState_Scissor(ScissorState _StateValue)
{
	ScissorState NextState = _StateValue;
	ScissorState PrevState = ScissorStateValue;

	ScissorStateValue = NextState;

	switch (NextState)
	{
	case ScissorState::Scissor_Intro:
		Scissor_IntroStart();
		break;
	case ScissorState::Down:
		DownStart();
		break;
	case ScissorState::Down_Loop:
		Down_LoopStart();
		break;
	case ScissorState::Up:
		UpStart();
		break;
	case ScissorState::Up_Loop:
		Up_LoopStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case ScissorState::Scissor_Intro:
		Scissor_IntroEnd();
		break;
	case ScissorState::Down:
		DownEnd();
		break;
	case ScissorState::Down_Loop:
		Down_LoopEnd();
		break;
	case ScissorState::Up:
		UpEnd();
		break;
	case ScissorState::Up_Loop:
		Up_LoopEnd();
		break;
	default:
		break;
	}
}
void Werner_Werman::UpdateState_Scissor(float _DeltaTime)
{
	switch (ScissorStateValue)
	{
	case ScissorState::Scissor_Intro:
		Scissor_IntroUpdate(_DeltaTime);
		break;
	case ScissorState::Down:
		DownUpdate(_DeltaTime);
		break;
	case ScissorState::Down_Loop:
		Down_LoopUpdate(_DeltaTime);
		break;
	case ScissorState::Up:
		UpUpdate(_DeltaTime);
		break;
	case ScissorState::Up_Loop:
		Up_LoopUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Werner_Werman::Scissor_IntroStart()
{
	WeaponRender->ChangeAnimation("Scissor_Intro");
}
void Werner_Werman::Scissor_IntroUpdate(float _DeltaTime)
{
	if (true == WeaponType)
	{
		ChangeState_Scissor(ScissorState::Up);
		return;
	}
}
void Werner_Werman::Scissor_IntroEnd()
{

}

void Werner_Werman::DownStart()
{
	WeaponRender->ChangeAnimation("Scissor_Down");
}
void Werner_Werman::DownUpdate(float _DeltaTime)
{

}
void Werner_Werman::DownEnd()
{

}

void Werner_Werman::Down_LoopStart()
{
	WeaponRender->ChangeAnimation("Scissor_Down_Loop");
}
void Werner_Werman::Down_LoopUpdate(float _DeltaTime)
{
	if (true == WeaponRender->IsAnimationEnd())
	{
		ChangeState_Scissor(ScissorState::Down_Loop);
		return;
	}
}
void Werner_Werman::Down_LoopEnd()
{

}

void Werner_Werman::UpStart()
{
	WeaponRender->ChangeAnimation("Scissor_Up");
}
void Werner_Werman::UpUpdate(float _DeltaTime)
{
	if (true == WeaponRender->IsAnimationEnd())
	{
		ChangeState_Scissor(ScissorState::Up_Loop);
		return;
	}
}
void Werner_Werman::UpEnd()
{

}

void Werner_Werman::Up_LoopStart()
{
	WeaponRender->ChangeAnimation("Scissor_Up_Loop");
}
void Werner_Werman::Up_LoopUpdate(float _DeltaTime)
{

}
void Werner_Werman::Up_LoopEnd()
{

}
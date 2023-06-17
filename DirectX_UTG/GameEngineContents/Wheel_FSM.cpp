#include "PrecompileHeader.h"
#include "Werner_Werman.h"

void Werner_Werman::ChangeState_Wheel(WheelState _StateValue)
{
	WheelState NextState = _StateValue;
	WheelState PrevState = WheelStateValue;

	WheelStateValue = NextState;

	switch (NextState)
	{
	case WheelState::Intro:
		Wheel_IntroStart();
		break;
	case WheelState::LeftMove:
		Wheel_LeftMoveStart();
		break;
	case WheelState::LeftMove_Loop:
		Wheel_LeftMove_LoopStart();
		break;
	case WheelState::RightMove:
		Wheel_RightMoveStart();
		break;
	case WheelState::RightMove_Loop:
		Wheel_RightMove_LoopStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case WheelState::Intro:
		Wheel_IntroEnd();
		break;
	case WheelState::LeftMove:
		Wheel_LeftMoveEnd();
		break;
	case WheelState::LeftMove_Loop:
		Wheel_LeftMove_LoopEnd();
		break;
	case WheelState::RightMove:
		Wheel_RightMoveEnd();
		break;
	case WheelState::RightMove_Loop:
		Wheel_RightMove_LoopEnd();
		break;
	default:
		break;
	}
}

void Werner_Werman::UpdateState_Wheel(float _DeltaTime)
{
	switch (WheelStateValue)
	{
	case WheelState::Intro:
		Wheel_IntroUpdate(_DeltaTime);
		break;
	case WheelState::LeftMove:
		Wheel_LeftMoveUpdate(_DeltaTime);
		break;
	case WheelState::LeftMove_Loop:
		Wheel_LeftMove_LoopUpdate(_DeltaTime);
		break;
	case WheelState::RightMove:
		Wheel_RightMoveUpdate(_DeltaTime);
		break;
	case WheelState::RightMove_Loop:
		Wheel_RightMove_LoopUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Werner_Werman::Wheel_IntroStart()
{
	WheelRenderPtr->ChangeAnimation("Plat_Loop", false);
}
void Werner_Werman::Wheel_IntroUpdate(float _DeltaTime)
{
	if (true == IsWheelStart)
	{
		IsWheelStart = false;
		ChangeState_Wheel(WheelState::LeftMove);
		return;
	}
}
void Werner_Werman::Wheel_IntroEnd()
{
	
}

void Werner_Werman::Wheel_LeftMoveStart()
{
	WheelRenderPtr->ChangeAnimation("Plat_MoveLeft");
}
void Werner_Werman::Wheel_LeftMoveUpdate(float _DeltaTime)
{
	if (true == WheelRenderPtr->IsAnimationEnd())
	{
		ChangeState_Wheel(WheelState::LeftMove_Loop);
		return;
	}
}
void Werner_Werman::Wheel_LeftMoveEnd()
{
	
}

void Werner_Werman::Wheel_LeftMove_LoopStart()
{
	WheelRenderPtr->ChangeAnimation("Plat_MoveLeft_Loop");
}
void Werner_Werman::Wheel_LeftMove_LoopUpdate(float _DeltaTime)
{
	if (true == IsWheelStart)
	{
		IsWheelStart = false;
		ChangeState_Wheel(WheelState::RightMove);
		return;
	}
}
void Werner_Werman::Wheel_LeftMove_LoopEnd()
{
	
}

void Werner_Werman::Wheel_RightMoveStart()
{
	WheelRenderPtr->ChangeAnimation("Plat_MoveRight");
}
void Werner_Werman::Wheel_RightMoveUpdate(float _DeltaTime)
{
	if (true == WheelRenderPtr->IsAnimationEnd())
	{
		ChangeState_Wheel(WheelState::RightMove_Loop);
		return;
	}
}
void Werner_Werman::Wheel_RightMoveEnd()
{

}

void Werner_Werman::Wheel_RightMove_LoopStart()
{
	WheelRenderPtr->ChangeAnimation("Plat_MoveRight_Loop");
}
void Werner_Werman::Wheel_RightMove_LoopUpdate(float _DeltaTime)
{
	if (true == IsWheelStart)
	{
		IsWheelStart = false;
		ChangeState_Wheel(WheelState::LeftMove);
		return;
	}
}
void Werner_Werman::Wheel_RightMove_LoopEnd()
{

}
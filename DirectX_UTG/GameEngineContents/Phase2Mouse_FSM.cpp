#include "PrecompileHeader.h"
#include "Werner_Werman.h"

#include <GameEngineBase/GameEngineRandom.h>

#include "Katzenwagen.h"

void Werner_Werman::ChangeState_Phase2(Phase2State _StateValue)
{
	Phase2State NextState = _StateValue;
	Phase2State PrevState = Phase2StateValue;

	Phase2StateValue = NextState;

	switch (NextState)
	{
	case Phase2State::Intro:
		Ph2MouseIntroStart();
		break;
	case Phase2State::TransA:
		TransAStart();
		break;
	case Phase2State::TransB:
		TransBStart();
		break;
	case Phase2State::Trans_LoopB:
		Trans_LoopBStart();
		break;
	case Phase2State::TransC:
		TransCStart();
		break;
	case Phase2State::TransD:
		TransDStart();
		break;
	case Phase2State::Trans_LoopD:
		Trans_LoopDStart();
		break;
	case Phase2State::Trans_EndLoop:
		Trans_EndLoopStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case Phase2State::Intro:
		Ph2MouseIntroEnd();
		break;
	case Phase2State::TransA:
		TransAEnd();
		break;
	case Phase2State::TransB:
		TransBEnd();
		break;
	case Phase2State::Trans_LoopB:
		Trans_LoopBEnd();
		break;
	case Phase2State::TransC:
		TransCEnd();
		break;
	case Phase2State::TransD:
		TransDEnd();
		break;
	case Phase2State::Trans_LoopD:
		Trans_LoopDEnd();
		break;
	case Phase2State::Trans_EndLoop:
		Trans_EndLoopEnd();
		break;
	default:
		break;
	}
}

void Werner_Werman::UpdateState_Phase2(float _DeltaTime)
{
	switch (Phase2StateValue)
	{
	case Phase2State::Intro:
		Ph2MouseIntroUpdate(_DeltaTime);
		break;
	case Phase2State::TransA:
		TransAUpdate(_DeltaTime);
		break;
	case Phase2State::TransB:
		TransBUpdate(_DeltaTime);
		break;
	case Phase2State::Trans_LoopB:
		Trans_LoopBUpdate(_DeltaTime);
		break;
	case Phase2State::TransC:
		TransCUpdate(_DeltaTime);
		break;
	case Phase2State::TransD:
		TransDUpdate(_DeltaTime);
		break;
	case Phase2State::Trans_LoopD:
		Trans_LoopDUpdate(_DeltaTime);
		break;
	case Phase2State::Trans_EndLoop:
		Trans_EndLoopUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Werner_Werman::Ph2MouseIntroStart()
{
	MouseRenderPtr->ChangeAnimation("Mouse_TransitionA_Loop");
}
void Werner_Werman::Ph2MouseIntroUpdate(float _DeltaTime)
{
	if (true == Phase2End)
	{
		ChangeState_Phase2(Phase2State::TransC);
	}

	if (false == IsMoveState)
	{
		ChangeState_Phase2(Phase2State::TransA);
	}
}
void Werner_Werman::Ph2MouseIntroEnd()
{

}

void Werner_Werman::TransAStart()
{
	MouseRenderPtr->ChangeAnimation("Mouse_TransitionA");
	StiecActivateDown(false);
}
void Werner_Werman::TransAUpdate(float _DeltaTime)
{
	if (true == Phase2End)
	{
		ChangeState_Phase2(Phase2State::TransC);
	}

	if (true == MouseRenderPtr->IsAnimationEnd())
	{
		ChangeState_Phase2(Phase2State::TransB);
	}
}
void Werner_Werman::TransAEnd()
{

}

void Werner_Werman::TransBStart()
{
	MouseRenderPtr->ChangeAnimation("Mouse_TransitionB");
}
void Werner_Werman::TransBUpdate(float _DeltaTime)
{
	if (true == Phase2End)
	{
		ChangeState_Phase2(Phase2State::TransC);
	}

	if (true == MouseRenderPtr->IsAnimationEnd())
	{
		ChangeState_Phase2(Phase2State::Trans_LoopB);
	}
}
void Werner_Werman::TransBEnd()
{

}

void Werner_Werman::Trans_LoopBStart()
{
	MouseRenderPtr->ChangeAnimation("Mouse_TransitionB_Loop");
}
void Werner_Werman::Trans_LoopBUpdate(float _DeltaTime)
{
	if (true == Phase2End)
	{
		ChangeState_Phase2(Phase2State::TransC);
	}

	if (true == IsMoveState)
	{
		ChangeState_Phase2(Phase2State::TransC);
	}
}
void Werner_Werman::Trans_LoopBEnd()
{

}

void Werner_Werman::TransCStart()
{
	MouseRenderPtr->ChangeAnimation("Mouse_TransitionC");
	StiecActivateUp(false);
}
void Werner_Werman::TransCUpdate(float _DeltaTime)
{
	if (true == MouseRenderPtr->IsAnimationEnd())
	{
		ChangeState_Phase2(Phase2State::TransD);
	}
}
void Werner_Werman::TransCEnd()
{

}

void Werner_Werman::TransDStart()
{
	MouseRenderPtr->ChangeAnimation("Mouse_TransitionD");
}
void Werner_Werman::TransDUpdate(float _DeltaTime)
{
	if (true == MouseRenderPtr->IsAnimationEnd())
	{
		ChangeState_Phase2(Phase2State::Trans_LoopD);
	}
}
void Werner_Werman::TransDEnd()
{

}

void Werner_Werman::Trans_LoopDStart()
{
	MouseRenderPtr->ChangeAnimation("Mouse_TransitionD_Loop");
}
void Werner_Werman::Trans_LoopDUpdate(float _DeltaTime)
{
	if (true == MouseTransitionEndLoop)
	{
		ChangeState_Phase2(Phase2State::Trans_EndLoop);
	}

	if (true == Phase2End)
	{
		return;
	}

	if (false == IsMoveState)
	{
		ChangeState_Phase2(Phase2State::TransA);
	}
}
void Werner_Werman::Trans_LoopDEnd()
{

}

void Werner_Werman::Trans_EndLoopStart()
{
	DelayTime = 0.0f;
	MouseRenderPtr->ChangeAnimation("Mouse_Transition_EndLoop");
}
void Werner_Werman::Trans_EndLoopUpdate(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (1.0f <= DelayTime)
	{
		Katzenwagen::KatzenwagenPtr->IsIntro = true;
	}
}
void Werner_Werman::Trans_EndLoopEnd()
{

}
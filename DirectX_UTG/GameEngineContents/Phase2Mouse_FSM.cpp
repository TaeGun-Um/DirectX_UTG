#include "PrecompileHeader.h"
#include "Werner_Werman.h"

#include <GameEngineBase/GameEngineRandom.h>

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
}
void Werner_Werman::TransAUpdate(float _DeltaTime)
{
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
	if (false == IsMoveState)
	{
		ChangeState_Phase2(Phase2State::TransA);
	}
}
void Werner_Werman::Trans_LoopDEnd()
{

}

// Up : A->B->BLoop
// Down : C->D->DLoop
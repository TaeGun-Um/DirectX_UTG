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
	case Phase2State::Trans:
		TransStart();
		break;
	case Phase2State::Trans_Loop:
		Trans_LoopStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case Phase2State::Trans:
		TransEnd();
		break;
	case Phase2State::Trans_Loop:
		Trans_LoopEnd();
		break;
	default:
		break;
	}
}

void Werner_Werman::UpdateState_Phase2(float _DeltaTime)
{
	switch (Phase2StateValue)
	{
	case Phase2State::Trans:
		TransUpdate(_DeltaTime);
		break;
	case Phase2State::Trans_Loop:
		Trans_LoopUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Werner_Werman::TransStart()
{
	MouseTransSetting = GameEngineRandom::MainRandom.RandomInt(0, 3);

	if (0 == MouseTransSetting)
	{
		MouseRenderPtr->ChangeAnimation("Mouse_TransitionA");
	}
	else if (1 == MouseTransSetting)
	{
		MouseRenderPtr->ChangeAnimation("Mouse_TransitionB");
	}
	else if (2 == MouseTransSetting)
	{
		MouseRenderPtr->ChangeAnimation("Mouse_TransitionC");
	}
	else if (3 == MouseTransSetting)
	{
		MouseRenderPtr->ChangeAnimation("Mouse_TransitionD");
	}
}
void Werner_Werman::TransUpdate(float _DeltaTime)
{
	if (true == MouseRenderPtr->IsAnimationEnd())
	{
		ChangeState_Phase2(Phase2State::Trans_Loop);
	}
}
void Werner_Werman::TransEnd()
{

}

void Werner_Werman::Trans_LoopStart()
{
	if (0 == MouseTransSetting)
	{
		MouseRenderPtr->ChangeAnimation("Mouse_TransitionA_Loop");
	}
	else if (1 == MouseTransSetting)
	{
		MouseRenderPtr->ChangeAnimation("Mouse_TransitionB_Loop");
	}
	else if (2 == MouseTransSetting)
	{
		MouseRenderPtr->ChangeAnimation("Mouse_TransitionC_Loop");
	}
	else if (3 == MouseTransSetting)
	{
		MouseRenderPtr->ChangeAnimation("Mouse_TransitionD_Loop");
	}
}
void Werner_Werman::Trans_LoopUpdate(float _DeltaTime)
{

}
void Werner_Werman::Trans_LoopEnd()
{

}

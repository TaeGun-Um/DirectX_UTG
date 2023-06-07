#include "PrecompileHeader.h"
#include "Croak.h"

#include <GameEngineBase/GameEngineRandom.h>

void Croak::ChangeState(CroakState _StateValue)
{
	CroakState NextState = _StateValue;
	CroakState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case CroakState::Intro:
		IntroStart();
		break;
	case CroakState::Idle:
		IdleStart();
		break;
	case CroakState::CreateMob_Start:
		CreateMob_StartStart();
		break;
	case CroakState::CreateMob_Start_Loop:
		CreateMob_Start_LoopStart();
		break;
	case CroakState::CreateMob_Start_Out:
		CreateMob_Start_OutStart();
		break;
	case CroakState::CreateMob:
		CreateMobStart();
		break;
	case CroakState::CreateMob_End:
		CreateMob_EndStart();
		break;
	case CroakState::Fan_Intro:
		Fan_IntroStart();
		break;
	case CroakState::Fan_Loop_A:
		Fan_Loop_AStart();
		break;
	case CroakState::Fan_Loop_B:
		Fan_Loop_BStart();
		break;
	case CroakState::Fan_End:
		Fan_EndStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case CroakState::Intro:
		IntroEnd();
		break;
	case CroakState::Idle:
		IdleEnd();
		break;
	case CroakState::CreateMob_Start:
		CreateMob_StartEnd();
		break;
	case CroakState::CreateMob_Start_Loop:
		CreateMob_Start_LoopEnd();
		break;
	case CroakState::CreateMob_Start_Out:
		CreateMob_Start_OutEnd();
		break;
	case CroakState::CreateMob:
		CreateMobEnd();
		break;
	case CroakState::CreateMob_End:
		CreateMob_EndEnd();
		break;
	case CroakState::Fan_Intro:
		Fan_IntroEnd();
		break;
	case CroakState::Fan_Loop_A:
		Fan_Loop_AEnd();
		break;
	case CroakState::Fan_Loop_B:
		Fan_Loop_BEnd();
		break;
	case CroakState::Fan_End:
		Fan_EndEnd();
		break;
	default:
		break;
	}
}

void Croak::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case CroakState::Intro:
		IntroUpdate(_DeltaTime);
		break;
	case CroakState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	case CroakState::CreateMob_Start:
		CreateMob_StartUpdate(_DeltaTime);
		break;
	case CroakState::CreateMob_Start_Loop:
		CreateMob_Start_LoopUpdate(_DeltaTime);
		break;
	case CroakState::CreateMob_Start_Out:
		CreateMob_Start_OutUpdate(_DeltaTime);
		break;
	case CroakState::CreateMob:
		CreateMobUpdate(_DeltaTime);
		break;
	case CroakState::CreateMob_End:
		CreateMob_EndUpdate(_DeltaTime);
		break;
	case CroakState::Fan_Intro:
		Fan_IntroUpdate(_DeltaTime);
		break;
	case CroakState::Fan_Loop_A:
		Fan_Loop_AUpdate(_DeltaTime);
		break;
	case CroakState::Fan_Loop_B:
		Fan_Loop_BUpdate(_DeltaTime);
		break;
	case CroakState::Fan_End:
		Fan_EndUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Croak::IntroStart()
{
	RenderPtr->ChangeAnimation("Croaks_Intro");
}
void Croak::IntroUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(CroakState::Idle);
		return;
	}
}
void Croak::IntroEnd()
{
	IsIntro = false;
}
	 
void Croak::IdleStart()
{
	RenderPtr->ChangeAnimation("Croaks_Idle");
}
void Croak::IdleUpdate(float _DeltaTime)
{
	if (true == IsIntro)
	{
		ChangeState(CroakState::Intro);
		return;
	}

	IdleDelayTime += _DeltaTime;

	if (IdleDelayTime >= 2.0f)
	{
		ChangeState(CroakState::CreateMob_Start);
		return;
	}
}
void Croak::IdleEnd()
{
	IdleDelayTime = 0.0f;
}
	 
void Croak::CreateMob_StartStart()
{
	IsCreatefly = true;
	RenderPtr->ChangeAnimation("Croaks_CreateMob_Start");
}
void Croak::CreateMob_StartUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(CroakState::CreateMob_Start_Loop);
		return;
	}
}
void Croak::CreateMob_StartEnd()
{

}
	 
void Croak::CreateMob_Start_LoopStart()
{
	RenderPtr->ChangeAnimation("Croaks_CreateMob_Start_Loop");
}
void Croak::CreateMob_Start_LoopUpdate(float _DeltaTime)
{
	CreateMob_LoopTime += _DeltaTime;

	if (CreateMob_LoopTime >= 1.0f)
	{
		ChangeState(CroakState::CreateMob_Start_Out);
		return;
	}
}
void Croak::CreateMob_Start_LoopEnd()
{
	CreateMob_LoopTime = 0.0f;
}

void Croak::CreateMob_Start_OutStart()
{
	RenderPtr->ChangeAnimation("Croaks_CreateMob_Start_Out");
}
void Croak::CreateMob_Start_OutUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		CreateMob = 1;
		CreateMobCount = 2;
		ChangeState(CroakState::CreateMob);
		return;
	}
}
void Croak::CreateMob_Start_OutEnd()
{

}

void Croak::CreateMobStart() 
{
	RenderPtr->ChangeAnimation("Croaks_CreateMob");
}
void Croak::CreateMobUpdate(float _DeltaTime) 
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		IsCreateMob = false;

		if (1 == CreateMob)
		{
			int RandC = GameEngineRandom::MainRandom.RandomInt(0, 1);

			if (RandC == 0)
			{
				CreateMobCount = 2;
				ChangeState(CroakState::CreateMob_End);
				return;
			}
			else
			{
				ChangeState(CroakState::CreateMob);
				return;
			}
		}
		else
		{
			ChangeState(CroakState::CreateMob_End);
			return;
		}
	}

	if (2 == RenderPtr->GetCurrentFrame() && 0 < CreateMobCount && false == IsCreateMob)
	{
		IsCreateMob = true;
		--CreateMobCount;
		CreateFirefly();
	}
}
void Croak::CreateMobEnd()
{
	CreateMob = 0;
}
	 
void Croak::CreateMob_EndStart()
{
	RenderPtr->ChangeAnimation("Croaks_CreateMob_End");
}
void Croak::CreateMob_EndUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(CroakState::Idle);
		return;
	}
}
void Croak::CreateMob_EndEnd()
{
	IsCreatefly = false;
}
	 
void Croak::Fan_IntroStart()
{

}
void Croak::Fan_IntroUpdate(float _DeltaTime)
{

}
void Croak::Fan_IntroEnd()
{

}
	 
void Croak::Fan_Loop_AStart()
{

}
void Croak::Fan_Loop_AUpdate(float _DeltaTime)
{

}
void Croak::Fan_Loop_AEnd()
{

}
	 
void Croak::Fan_Loop_BStart()
{

}
void Croak::Fan_Loop_BUpdate(float _DeltaTime)
{

}
void Croak::Fan_Loop_BEnd()
{

}
	 
void Croak::Fan_EndStart()
{

}
void Croak::Fan_EndUpdate(float _DeltaTime)
{

}
void Croak::Fan_EndEnd()
{

}
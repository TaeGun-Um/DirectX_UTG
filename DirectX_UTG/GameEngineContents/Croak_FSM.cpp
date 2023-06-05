#include "PrecompileHeader.h"
#include "Croak.h"

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
	case CroakState::CreateMob_Boil:
		CreateMob_BoilStart();
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
	case CroakState::CreateMob_Boil:
		CreateMob_BoilEnd();
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
	case CroakState::CreateMob_Boil:
		CreateMob_BoilUpdate(_DeltaTime);
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

}
void Croak::IdleEnd()
{

}
	 
void Croak::CreateMob_StartStart()
{

}
void Croak::CreateMob_StartUpdate(float _DeltaTime)
{

}
void Croak::CreateMob_StartEnd()
{

}
	 
void Croak::CreateMob_BoilStart()
{

}
void Croak::CreateMob_BoilUpdate(float _DeltaTime)
{

}
void Croak::CreateMob_BoilEnd()
{

}

void Croak::CreateMobStart() 
{

}
void Croak::CreateMobUpdate(float _DeltaTime) 
{

}
void Croak::CreateMobEnd()
{

}
	 
void Croak::CreateMob_EndStart()
{

}
void Croak::CreateMob_EndUpdate(float _DeltaTime)
{

}
void Croak::CreateMob_EndEnd()
{

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
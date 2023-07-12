#include "PrecompileHeader.h"
#include "GrimMatchstick.h"

void GrimMatchstick::ChangeState_FireRender(FireRenderState _StateValue)
{
	FireRenderState NextState = _StateValue;
	FireRenderState PrevState = FireStateValue;

	FireStateValue = NextState;

	switch (NextState)
	{
	case FireRenderState::Object_Fire_Intro:
		Object_Fire_IntroStart();
		break;
	case FireRenderState::Object_Fire_Loop:
		Object_Fire_LoopStart();
		break;
	case FireRenderState::Object_Fire_Outro:
		Object_Fire_OutroStart();
		break;
	case FireRenderState::Object_FireSmoke_Intro:
		Object_FireSmoke_IntroStart();
		break;
	case FireRenderState::Object_FireSmoke_Loop:
		Object_FireSmoke_LoopStart();
		break;
	case FireRenderState::Object_FireSmoke_Outro:
		Object_FireSmoke_OutroStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case FireRenderState::Object_Fire_Intro:
		Object_Fire_IntroEnd();
		break;
	case FireRenderState::Object_Fire_Loop:
		Object_Fire_LoopEnd();
		break;
	case FireRenderState::Object_Fire_Outro:
		Object_Fire_OutroEnd();
		break;
	case FireRenderState::Object_FireSmoke_Intro:
		Object_FireSmoke_IntroEnd();
		break;
	case FireRenderState::Object_FireSmoke_Loop:
		Object_FireSmoke_LoopEnd();
		break;
	case FireRenderState::Object_FireSmoke_Outro:
		Object_FireSmoke_OutroEnd();
		break;
	default:
		break;
	}
}
void GrimMatchstick::UpdateState_FireRender(float _DeltaTime)
{
	switch (FireStateValue)
	{
	case FireRenderState::Object_Fire_Intro:
		Object_Fire_IntroUpdate(_DeltaTime);
		break;
	case FireRenderState::Object_Fire_Loop:
		Object_Fire_LoopUpdate(_DeltaTime);
		break;
	case FireRenderState::Object_Fire_Outro:
		Object_Fire_OutroUpdate(_DeltaTime);
		break;
	case FireRenderState::Object_FireSmoke_Intro:
		Object_FireSmoke_IntroUpdate(_DeltaTime);
		break;
	case FireRenderState::Object_FireSmoke_Loop:
		Object_FireSmoke_LoopUpdate(_DeltaTime);
		break;
	case FireRenderState::Object_FireSmoke_Outro:
		Object_FireSmoke_OutroUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void GrimMatchstick::Object_Fire_IntroStart()
{

}
void GrimMatchstick::Object_Fire_IntroUpdate(float _DeltaTime)
{

}
void GrimMatchstick::Object_Fire_IntroEnd()
{

}

void GrimMatchstick::Object_Fire_LoopStart()
{

}
void GrimMatchstick::Object_Fire_LoopUpdate(float _DeltaTime)
{

}
void GrimMatchstick::Object_Fire_LoopEnd()
{

}

void GrimMatchstick::Object_Fire_OutroStart()
{

}
void GrimMatchstick::Object_Fire_OutroUpdate(float _DeltaTime)
{

}
void GrimMatchstick::Object_Fire_OutroEnd()
{

}

void GrimMatchstick::Object_FireSmoke_IntroStart()
{

}
void GrimMatchstick::Object_FireSmoke_IntroUpdate(float _DeltaTime)
{

}
void GrimMatchstick::Object_FireSmoke_IntroEnd()
{

}

void GrimMatchstick::Object_FireSmoke_LoopStart()
{

}
void GrimMatchstick::Object_FireSmoke_LoopUpdate(float _DeltaTime)
{

}
void GrimMatchstick::Object_FireSmoke_LoopEnd()
{

}

void GrimMatchstick::Object_FireSmoke_OutroStart()
{

}
void GrimMatchstick::Object_FireSmoke_OutroUpdate(float _DeltaTime)
{

}
void GrimMatchstick::Object_FireSmoke_OutroEnd()
{

}
#include "PrecompileHeader.h"
#include "GrimMatchstick.h"

void GrimMatchstick::ChangeState(DragonState _StateValue)
{
	DragonState NextState = _StateValue;
	DragonState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case DragonState::Intro:
		IntroStart();
		break;
	case DragonState::Idle:
		IdleStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case DragonState::Intro:
		IntroEnd();
		break;
	case DragonState::Idle:
		IdleEnd();
		break;
	default:
		break;
	}
}

void GrimMatchstick::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case DragonState::Intro:
		IntroUpdate(_DeltaTime);
		break;
	case DragonState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void GrimMatchstick::IntroStart()
{
	RenderPtr->ChangeAnimation("Dragon_Intro");
}
void GrimMatchstick::IntroUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(DragonState::Idle);
		return;
	}
}
void GrimMatchstick::IntroEnd()
{

}

void GrimMatchstick::IdleStart()
{
	RenderPtr->ChangeAnimation("Dragon_Idle");
}
void GrimMatchstick::IdleUpdate(float _DeltaTime)
{

}
void GrimMatchstick::IdleEnd()
{

}
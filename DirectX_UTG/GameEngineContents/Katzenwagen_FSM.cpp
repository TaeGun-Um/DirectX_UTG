#include "PrecompileHeader.h"
#include "Katzenwagen.h"

#include <GameEngineBase/GameEngineRandom.h>

void Katzenwagen::ChangeState(KatzenwagenState _StateValue)
{
	KatzenwagenState NextState = _StateValue;
	KatzenwagenState PrevState = StateValue;

	StateValue = NextState;
}

void Katzenwagen::UpdateState(float _DeltaTime)
{

}

void Katzenwagen::IntroStart()
{

}
void Katzenwagen::IntroUpdate(float _DeltaTime)
{

}
void Katzenwagen::IntroEnd()
{

}

void Katzenwagen::IdleStart()
{

}
void Katzenwagen::IdleUpdate(float _DeltaTime)
{

}
void Katzenwagen::IdleEnd()
{

}
#include "PrecompileHeader.h"
#include "Katzenwagen.h"

#include <GameEngineBase/GameEngineRandom.h>

#include "Mouse_Map.h"

void Katzenwagen::ChangeState(KatzenwagenState _StateValue)
{
	KatzenwagenState NextState = _StateValue;
	KatzenwagenState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case KatzenwagenState::Intro:
		IntroStart();
		break;
	case KatzenwagenState::Idle:
		IdleStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case KatzenwagenState::Intro:
		IntroEnd();
		break;
	case KatzenwagenState::Idle:
		IdleEnd();
		break;
	default:
		break;
	}
}

void Katzenwagen::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case KatzenwagenState::Intro:
		IntroUpdate(_DeltaTime);
		break;
	case KatzenwagenState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Katzenwagen::IntroStart()
{
	BodyRenderPtr->On();

	BodyRenderPtr->ChangeAnimation("Cat_Intro_Body");

	BodyRenderPtr->SetAnimationStartEvent("Cat_Intro_Body", 8, std::bind(&Katzenwagen::IntroAnimationSetting, this));
}
void Katzenwagen::IntroUpdate(float _DeltaTime)
{
	if (true == HeadRenderPtr->IsUpdate())
	{
		IntroHeadPositionSetting();

		if (true == HeadRenderPtr->IsAnimationEnd())
		{
			ChangeState(KatzenwagenState::Idle);
			return;
		}
	}
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

void Katzenwagen::IntroHeadPositionSetting()
{
	if (54 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 10, -60, -10 });
	}
	else if (53 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 10, -45, -10 });
	}
	else if (52 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 10, -30, -10 });
	}
	else if (51 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 10, -45, -10 });
	}
	else if (50 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 10, -60, -10 });
	}
	else if (49 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 10, -70, -10 });
	}
	else if (48 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 10, -90, -10 });
	}
	else if (37 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -105, -10 });
	}
}
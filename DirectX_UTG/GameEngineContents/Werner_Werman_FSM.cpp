#include "PrecompileHeader.h"
#include "Werner_Werman.h"

void Werner_Werman::ChangeState(MouseState _StateValue)
{
	MouseState NextState = _StateValue;
	MouseState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case MouseState::Intro:
		IntroStart();
		break;
	case MouseState::Idle:
		IdleStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case MouseState::Intro:
		IntroEnd();
		break;
	case MouseState::Idle:
		IdleEnd();
		break;
	default:
		break;
	}
}

void Werner_Werman::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case MouseState::Intro:
		IntroUpdate(_DeltaTime);
		break;
	case MouseState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Werner_Werman::IntroStart()
{
	IntroStartPos = MouseRenderPtr->GetTransform()->GetWorldPosition();
	IntroDownPos = IntroStartPos + float4{ 60, -250 };

	MouseRenderPtr->ChangeAnimation("Mouse_Intro");
	CanRenderPtr->ChangeAnimation("Mouse_Idle");
}
void Werner_Werman::IntroUpdate(float _DeltaTime)
{
	if (39 <= MouseRenderPtr->GetCurrentFrame())
	{
		IntroLerpTime += _DeltaTime * 1.2f;
		float4 LerpPos = float4::Lerp(IntroStartPos, IntroDownPos, IntroLerpTime);
		MouseRenderPtr->GetTransform()->SetWorldPosition(LerpPos);
	}

	if (true == MouseRenderPtr->IsAnimationEnd())
	{
		MouseRenderPtr->Off();
		ChangeState(MouseState::Idle);
		return;
	}
}
void Werner_Werman::IntroEnd()
{

}

void Werner_Werman::IdleStart()
{
	CanRenderPtr->ChangeAnimation("Mouse_Idle");
}
void Werner_Werman::IdleUpdate(float _DeltaTime)
{
	if (true == IsIntro)
	{
		ChangeState(MouseState::Intro);
		return;
	}
}
void Werner_Werman::IdleEnd()
{

}
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
	MouseRenderPtr->ChangeAnimation("Mouse_Intro");
	CanRenderPtr->ChangeAnimation("Can_Idle");
}
void Werner_Werman::IntroUpdate(float _DeltaTime)
{
	SetIntroTexture();

	if (2 == CanRenderPtr->GetCurrentFrame())
	{
		CanUpRenderPtr->SetScaleToTexture("Can_Idle_Up_003.png");
	}
	else if (1 == CanRenderPtr->GetCurrentFrame())
	{
		CanUpRenderPtr->SetScaleToTexture("Can_Idle_Up_002.png");
	}
	else if (0 == CanRenderPtr->GetCurrentFrame())
	{
		CanUpRenderPtr->SetScaleToTexture("Can_Idle_Up_001.png");
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
	CanRenderPtr->ChangeAnimation("Can_Idle");
}
void Werner_Werman::IdleUpdate(float _DeltaTime)
{
	if (true == IsIntro)
	{
		ChangeState(MouseState::Intro);
		return;
	}

	if (2 == CanRenderPtr->GetCurrentFrame())
	{
		CanUpRenderPtr->SetScaleToTexture("Can_Idle_Up_003.png");
	}
	else if (1 == CanRenderPtr->GetCurrentFrame())
	{
		CanUpRenderPtr->SetScaleToTexture("Can_Idle_Up_002.png");
	}
	else if (0 == CanRenderPtr->GetCurrentFrame())
	{
		CanUpRenderPtr->SetScaleToTexture("Can_Idle_Up_001.png");
	}
}
void Werner_Werman::IdleEnd()
{

}

void Werner_Werman::MoveStart()
{
	CanRenderPtr->ChangeAnimation("Can_Move");
}
void Werner_Werman::MoveUpdate(float _DeltaTime)
{

}
void Werner_Werman::MoveEnd()
{

}

void Werner_Werman::SetIntroTexture()
{
	if (48 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->Off();
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_049.png");
	}
	else if (47 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_048.png");
	}
	else if (46 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_047.png");
	}
	else if (45 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->On();
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_046.png");
	}
	else if (32 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->Off();
	}
	else if (31 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_032.png");
	}
	else if (30 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_031.png");
	}
	else if (29 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_030.png");
	}
	else if (28 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_029.png");
	}
	else if (27 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_028.png");
	}
	else if (26 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_027.png");
	}
	else if (25 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_026.png");
	}
	else if (24 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_025.png");
	}
	else if (23 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_024.png");
	}
	else if (22 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_023.png");
	}
	else if (21 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_022.png");
	}
	else if (20 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_021.png");
	}
	else if (19 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_020.png");
	}
	else if (18 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_019.png");
	}
	else if (17 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_018.png");
	}
	else if (16 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_017.png");
	}
	else if (15 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_016.png");
	}
	else if (14 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_015.png");
	}
	else if (13 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_014.png");
	}
	else if (12 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_013.png");
	}
	else if (11 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_012.png");
	}
	else if (10 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_011.png");
	}
	else if (9 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_010.png");
	}
	else if (8 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_009.png");
	}
	else if (7 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_008.png");
	}
	else if (6 == MouseRenderPtr->GetCurrentFrame())
	{
		MouseUpRenderPtr->On();
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_007.png");
	}
}
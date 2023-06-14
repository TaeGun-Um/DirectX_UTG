#include "PrecompileHeader.h"
#include "Werner_Werman.h"

#include <cmath>

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
	case MouseState::MouseIn:
		MouseInStart();
		break;
	case MouseState::MouseOut:
		MouseOutStart();
		break;
	case MouseState::Idle:
		IdleStart();
		break;
	case MouseState::Move:
		MoveStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case MouseState::Intro:
		IntroEnd();
		break;
	case MouseState::MouseIn:
		MouseInEnd();
		break;
	case MouseState::MouseOut:
		MouseOutEnd();
		break;
	case MouseState::Idle:
		IdleEnd();
		break;
	case MouseState::Move:
		MoveEnd();
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
	case MouseState::MouseIn:
		MouseInUpdate(_DeltaTime);
		break;
	case MouseState::MouseOut:
		MouseOutUpdate(_DeltaTime);
		break;
	case MouseState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	case MouseState::Move:
		MoveUpdate(_DeltaTime);
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
	SetIntroMouseUpTexture();
	SetIntroCanUpTexture();
	SetIntroCanBackTexture();

	if (true == MouseRenderPtr->IsAnimationEnd())
	{
		MouseRenderPtr->Off();
		CanUpRenderPtr->Off();
		ChangeState(MouseState::MouseIn);
		return;
	}
}
void Werner_Werman::IntroEnd()
{
	IsIntro = false;
}

void Werner_Werman::MouseInStart()
{
	CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 144 });
	CanRenderPtr->GetTransform()->SetLocalPosition({ 0, 0 });
	CanRenderPtr->ChangeAnimation("Can_MouseIn");
}
void Werner_Werman::MouseInUpdate(float _DeltaTime)
{
	SetMouseInCanBackTexture();

	DelayTime += _DeltaTime;

	if (true == MouseRenderPtr->IsAnimationEnd() && DelayTime >= 0.21f)
	{
		ChangeState(MouseState::Idle);
		return;
	}
}
void Werner_Werman::MouseInEnd()
{
	DelayTime = 0.0f;
}

void Werner_Werman::MouseOutStart()
{
	CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 144 });
	CanRenderPtr->GetTransform()->SetLocalPosition({ 0, 0 });
	CanRenderPtr->ChangeAnimation("Can_MouseOut");
}
void Werner_Werman::MouseOutUpdate(float _DeltaTime)
{
	SetMouseOutCanBackTexture();

	if (true == MouseRenderPtr->IsAnimationEnd() && DelayTime >= 0.21f)
	{
		//ChangeState(MouseState::Idle);
		//return;
	}
}
void Werner_Werman::MouseOutEnd()
{

}

void Werner_Werman::IdleStart()
{
	CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 144 });
	CanRenderPtr->GetTransform()->SetLocalPosition({ 0, 0 });
	CanRenderPtr->ChangeAnimation("Can_Idle");
}
void Werner_Werman::IdleUpdate(float _DeltaTime)
{
	SetIntroCanUpTexture();
	SetIntroCanBackTexture();

	if (true == IsIntro)
	{
		ChangeState(MouseState::Intro);
		return;
	}

	DelayTime += _DeltaTime;

	if (false == IsIntro && DelayTime >= 0.7f)
	{
		CanUpRenderPtr->Off();
		ChangeState(MouseState::Move);
		return;
	}
}
void Werner_Werman::IdleEnd()
{
	DelayTime = 0.0f;
}

void Werner_Werman::MoveStart()
{
	CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 150 });
	CanRenderPtr->GetTransform()->SetLocalPosition({ 0, 20 });

	WheelRenderPtr->On();

	CanRenderPtr->ChangeAnimation("Can_Move");
}
void Werner_Werman::MoveUpdate(float _DeltaTime)
{
	SetMoveCanBackTexture();
	
	MoveTime += _DeltaTime;

	if (false == CannonAble)
	{
		WeaponSwapTime += _DeltaTime;
	}

	if (false == CannonAble && 1.0f <= WeaponSwapTime)
	{
		CannonAble = true;
		ChangeState_Cannon(CannonState::Out);
	}

	if (true == CannonAble)
	{
		WeaponSwapTime = 0.0;
		UpdateState_Cannon(_DeltaTime);
	}

	float CosTime = MoveTime * 2.5f;

	float SinX = (sinf(CosTime + GameEngineMath::PIE) * 150.0f);

	if (GameEngineMath::PIE2 <= CosTime)
	{
		MoveTime = 0.0f;
		GetTransform()->SetWorldPosition(InitPosition);
	}

	GetTransform()->SetLocalPosition({ SinX + InitPosition.x, InitPosition.y });
}
void Werner_Werman::MoveEnd()
{

}

void Werner_Werman::SetMoveCanBackTexture()
{
	if (23 == CanRenderPtr->GetCurrentFrame()) // 316
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 143.5f });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_024.png");
	}
	else if (22 == CanRenderPtr->GetCurrentFrame()) // 312
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 141.5f });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_023.png");
	}
	else if (21 == CanRenderPtr->GetCurrentFrame()) // 300
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 135.5f });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_022.png");
	}
	else if (20 == CanRenderPtr->GetCurrentFrame()) // 312
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 141.5f });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_021.png");
	}
	else if (19 == CanRenderPtr->GetCurrentFrame()) // 314
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 142.5f });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_020.png");
	}
	else if (18 == CanRenderPtr->GetCurrentFrame()) // 316
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 143.5f });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_019.png");
	}
	else if (17 == CanRenderPtr->GetCurrentFrame()) // 319
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 145 });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_018.png");
	}
	else if (16 == CanRenderPtr->GetCurrentFrame()) // 319
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 145 });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_017.png");
	}
	else if (15 == CanRenderPtr->GetCurrentFrame()) // 316
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 143.5f });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_016.png");
	}
	else if (14 == CanRenderPtr->GetCurrentFrame()) // 323
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 147 });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_015.png");
	}
	else if (13 == CanRenderPtr->GetCurrentFrame()) // 326
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 148.5f });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_014.png");
	}
	else if (12 == CanRenderPtr->GetCurrentFrame()) // 324
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 147.5f });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_013.png");
	}
	else if (11 == CanRenderPtr->GetCurrentFrame()) // 317
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 144 });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_012.png");
	}
	else if (10 == CanRenderPtr->GetCurrentFrame()) // 311
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 141 });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_011.png");
	}
	else if (9 == CanRenderPtr->GetCurrentFrame()) // 302
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 136.5f });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_010.png");
	}
	else if (8 == CanRenderPtr->GetCurrentFrame()) // 309
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 140 });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_009.png");
	}
	else if (7 == CanRenderPtr->GetCurrentFrame()) // 311
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 141 });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_008.png");
	}
	else if (6 == CanRenderPtr->GetCurrentFrame()) // 323
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 147 });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_007.png");
	}
	else if (5 == CanRenderPtr->GetCurrentFrame()) // 320
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 145.5f });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_006.png");
	}
	else if (4 == CanRenderPtr->GetCurrentFrame()) // 321
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 146 });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_005.png");
	}
	else if (3 == CanRenderPtr->GetCurrentFrame()) // 315
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 143 });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_004.png");
	}
	else if (2 == CanRenderPtr->GetCurrentFrame()) // 321
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 146 });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_003.png");
	}
	else if (1 == CanRenderPtr->GetCurrentFrame()) // 327
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 149 });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_002.png");
	}
	else if (0 == CanRenderPtr->GetCurrentFrame()) // 329
	{
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 150 });
		CanBackRenderPtr->SetScaleToTexture("Can_Move_Back_001.png");
	}
}

void Werner_Werman::SetMouseInCanBackTexture()
{
	if (2 == CanRenderPtr->GetCurrentFrame())
	{
		CanBackRenderPtr->SetScaleToTexture("Can_Part_Back_InOut_001.png");
	}
	else if (1 == CanRenderPtr->GetCurrentFrame())
	{
		CanBackRenderPtr->SetScaleToTexture("Can_Part_Back_InOut_002.png");
	}
	else if (0 == CanRenderPtr->GetCurrentFrame())
	{
		CanBackRenderPtr->SetScaleToTexture("Can_Part_Back_InOut_003.png");
	}
}
void Werner_Werman::SetMouseOutCanBackTexture()
{
	if (2 == CanRenderPtr->GetCurrentFrame())
	{
		CanBackRenderPtr->SetScaleToTexture("Can_Part_Back_InOut_003.png");
	}
	else if (1 == CanRenderPtr->GetCurrentFrame())
	{
		CanBackRenderPtr->SetScaleToTexture("Can_Part_Back_InOut_002.png");
	}
	else if (0 == CanRenderPtr->GetCurrentFrame())
	{
		CanBackRenderPtr->SetScaleToTexture("Can_Part_Back_InOut_001.png");
	}
}

void Werner_Werman::SetIntroCanBackTexture()
{
	if (2 == CanRenderPtr->GetCurrentFrame())
	{
		CanBackRenderPtr->SetScaleToTexture("Can_Idle_Back_003.png");
	}
	else if (1 == CanRenderPtr->GetCurrentFrame())
	{
		CanBackRenderPtr->SetScaleToTexture("Can_Idle_Back_002.png");
	}
	else if (0 == CanRenderPtr->GetCurrentFrame())
	{
		CanBackRenderPtr->SetScaleToTexture("Can_Idle_Back_001.png");
	}
}

void Werner_Werman::SetIntroCanUpTexture()
{
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

void Werner_Werman::SetIntroMouseUpTexture()
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
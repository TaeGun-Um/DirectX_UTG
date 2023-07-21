#include "PrecompileHeader.h"
#include "Werner_Werman.h"

#include <cmath>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Mouse_Map.h"

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
	case MouseState::Dash_Intro:
		Dash_IntroStart();
		break;
	case MouseState::Dash:
		DashStart();
		break;
	case MouseState::Dash_Outro:
		Dash_OutroStart();
		break;
	case MouseState::Explosion_Intro:
		Explosion_IntroStart();
		break;
	case MouseState::Explosion_Loop:
		Explosion_LoopStart();
		break;
	case MouseState::Explosion:
		ExplosionStart();
		break;
	case MouseState::Idle_Phase2:
		Idle_Phase2Start();
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
	case MouseState::Dash_Intro:
		Dash_IntroEnd();
		break;
	case MouseState::Dash:
		DashEnd();
		break;
	case MouseState::Dash_Outro:
		Dash_OutroEnd();
		break;
	case MouseState::Explosion_Intro:
		Explosion_IntroEnd();
		break;
	case MouseState::Explosion_Loop:
		Explosion_LoopEnd();
		break;
	case MouseState::Explosion:
		ExplosionEnd();
		break;
	case MouseState::Idle_Phase2:
		Idle_Phase2End();
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
	case MouseState::Dash_Intro:
		Dash_IntroUpdate(_DeltaTime);
		break;
	case MouseState::Dash:
		DashUpdate(_DeltaTime);
		break;
	case MouseState::Dash_Outro:
		Dash_OutroUpdate(_DeltaTime);
		break;
	case MouseState::Explosion_Intro:
		Explosion_IntroUpdate(_DeltaTime);
		break;
	case MouseState::Explosion_Loop:
		Explosion_LoopUpdate(_DeltaTime);
		break;
	case MouseState::Explosion:
		ExplosionUpdate(_DeltaTime);
		break;
	case MouseState::Idle_Phase2:
		Idle_Phase2Update(_DeltaTime);
		break;
	default:
		break;
	}
}

void Werner_Werman::IntroStart()
{
	MouseRenderPtr->ChangeAnimation("Mouse_Intro");
	CanRenderPtr->ChangeAnimation("Can_Idle");

	MouseRenderPtr->SetAnimationStartEvent("Mouse_Intro", 9, std::bind(&Werner_Werman::IntroSound, this));
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
	WheelRenderPtr->Off();

	CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 144 });
	CanRenderPtr->GetTransform()->SetLocalPosition({ 0, 0 });
	CanRenderPtr->ChangeAnimation("Can_MouseOut");
}
void Werner_Werman::MouseOutUpdate(float _DeltaTime)
{
	SetMouseOutCanBackTexture();

	DelayTime += _DeltaTime;

	if (true == MouseRenderPtr->IsAnimationEnd() && DelayTime >= 0.21f)
	{
		EffectPlayer = GameEngineSound::Play("mouse_snarky_voice_02.wav");
		ChangeState(MouseState::Dash_Intro);
		return;
	}
}
void Werner_Werman::MouseOutEnd()
{
	DelayTime = 0.0f;
}

void Werner_Werman::IdleStart()
{
	DirectCheck();

	CanBackRenderPtr->On();
	CanRenderPtr->On();

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

	if (true == IsDash)
	{
		ChangeState(MouseState::MouseOut);
		return;
	}

	DelayTime += _DeltaTime;

	if (false == IsIntro && false == IsDash && DelayTime >= 0.3f)
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

	IsCreateSpringObject = true;

	if (HP <= 750.0f)
	{
		WeaponSwapCount = 2;
	}
}
void Werner_Werman::MoveUpdate(float _DeltaTime)
{
	SetMoveCanBackTexture();
	
	MoveTime += _DeltaTime;

	if (false == CannonAble || false == CatapultAble)
	{
		WeaponSwapTime += _DeltaTime;
	}

	if (false == CannonAble && 1.0f <= WeaponSwapTime
		|| false == CatapultAble && 1.0f <= WeaponSwapTime)
	{
		if (2 <= WeaponSwapCount)
		{
			++WeaponSwapCount;
		}
		else
		{
			if (false == AlreadyCannonOn && false == AlreadyCatapultOn)
			{
				int RandC = GameEngineRandom::MainRandom.RandomInt(0, 1);

				if (0 == RandC)
				{
					AlreadyCannonOn = true;
					++WeaponSwapCount;
					CannonAble = true;
					ChangeState_Cannon(CannonState::Out);
				}
				else
				{
					AlreadyCatapultOn = true;
					++WeaponSwapCount;
					CatapultAble = true;
					ChangeState_Catapult(CatapultState::Out);
				}
			}
			else if (true == AlreadyCannonOn)
			{
				++WeaponSwapCount;
				CatapultAble = true;
				ChangeState_Catapult(CatapultState::Out);
			}
			else if (true == AlreadyCatapultOn)
			{
				++WeaponSwapCount;
				CannonAble = true;
				ChangeState_Cannon(CannonState::Out);
			}
		}
	}

	if (2 >= WeaponSwapCount && 1 == Phase2PositionSetting)
	{
		if (true == CannonAble)
		{
			WeaponSwapTime = 0.0f;
			UpdateState_Cannon(_DeltaTime);
		}
		else if (true == CatapultAble)
		{
			WeaponSwapTime = 0.0f;
			UpdateState_Catapult(_DeltaTime);
		}
	}

	if (false == Directbool)
	{
		float CosTime = MoveTime * 2.5f;

		float SinX = (sinf(CosTime + GameEngineMath::PIE) * 150.0f);

		if (GameEngineMath::PIE2 <= CosTime)
		{
			MoveTime = 0.0f;
			GetTransform()->SetWorldPosition(InitPosition);
		}

		GetTransform()->SetLocalPosition({ SinX + InitPosition.x, InitPosition.y });

		if ((GameEngineMath::PIE / 4) <= CosTime && 3 <= WeaponSwapCount && true == IsCreateSpringObject)
		{
			IsCreateSpringObject = false;

			EffectPlayer = GameEngineSound::Play("mouse_can_springboard_shoot.wav");

			CreateSpringObject();
		}

		if ((GameEngineMath::PIE + (GameEngineMath::PIE / 2)) <= CosTime && 3 <= WeaponSwapCount)
		{
			MoveTime = 0.0f;
			IsDash = true;
			ChangeState(MouseState::Idle);
			return;
		}
	}
	else
	{
		if (3 <= WeaponSwapCount && HP <= 700.0f)
		{
			if (1 == Phase2PositionSetting)
			{
				Phase2PositionSetting = 0;
				Phase2InitPosition = float4{ 700.0f , InitPosition.y, 0.0f };
			}
			
			float4 CurPos = GetTransform()->GetWorldPosition();
			float4 Movedir = float4::Zero;

			Movedir = (Phase2InitPosition - CurPos);

			MoveDistance = Movedir * 1.2f * _DeltaTime;
			MoveDistance.z = 0.0f;

			GetTransform()->AddWorldPosition(MoveDistance);

			if ((Phase2InitPosition.x - 60.0f) <= CurPos.x)
			{
				GetTransform()->SetLocalPosition({ (Phase2InitPosition.x - 60.0f) , Phase2InitPosition.y, 0.0f });
				ChangeState(MouseState::Explosion_Intro);
				return;
			}
		}

		float CosTime = MoveTime * 2.5f;

		if (1 == Phase2PositionSetting)
		{
			if ((GameEngineMath::PIE / 4) <= CosTime && 3 <= WeaponSwapCount)
			{
				WeaponSwapCount = 0;
				AlreadyCannonOn = false;
				AlreadyCatapultOn = false;
			}
			else
			{
				float SinX = (sinf(CosTime) * 150.0f);

				if (GameEngineMath::PIE2 <= CosTime)
				{
					MoveTime = 0.0f;
					GetTransform()->SetWorldPosition(LeftInitPosition);
				}

				GetTransform()->SetLocalPosition({ SinX + LeftInitPosition.x, LeftInitPosition.y });
			}
		}
	}
}
void Werner_Werman::MoveEnd()
{
	AlreadyCannonOn = false;
	AlreadyCatapultOn = false;
	WeaponSwapCount = 0;
}

void Werner_Werman::Dash_IntroStart()
{
	CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 144 });
	MouseRenderPtr->GetTransform()->SetLocalPosition({ -70, 190, -1 });
	
	MouseRenderPtr->On();
	CanUpRenderPtr->On();

	MouseRenderPtr->ChangeAnimation("Mouse_PopOut");
	CanRenderPtr->ChangeAnimation("Can_Idle");

	MouseRenderPtr->SetAnimationStartEvent("Mouse_Dash_Intro", 20, std::bind(&Werner_Werman::CanDashStartSound, this));
	MouseRenderPtr->SetAnimationStartEvent("Mouse_Dash_Intro", 22, std::bind(&Werner_Werman::DashStartVoiceSound, this));
}
void Werner_Werman::Dash_IntroUpdate(float _DeltaTime)
{
	SetIntroCanUpTexture();
	SetIntroCanBackTexture();

	if (true == MouseRenderPtr->FindAnimation("Mouse_PopOut")->IsEnd() && false == IsShake)
	{
		IsShake = true;
		MouseRenderPtr->ChangeAnimation("Mouse_ShakeFist", false);
	}

	if (true == MouseRenderPtr->FindAnimation("Mouse_ShakeFist")->IsEnd())
	{
		CanBackRenderPtr->Off();
		CanRenderPtr->Off();
		CanUpRenderPtr->Off();
		MouseRenderPtr->GetTransform()->SetLocalPosition({ -20, 150 });
		MouseRenderPtr->ChangeAnimation("Mouse_Dash_Intro", false);
	}

	if (true == MouseRenderPtr->FindAnimation("Mouse_Dash_Intro")->IsEnd())
	{
		ChangeState(MouseState::Dash);
		return;
	}
}
void Werner_Werman::Dash_IntroEnd()
{
	IsShake = false;
}

void Werner_Werman::DashStart()
{
	LeftInitPosition = float4{ InitPosition.x - 800.0f, InitPosition.y, 0.0f };
	FowardPosition = GetTransform()->GetLocalPosition();
	FowardPosition.z = 0.0f;
	MouseRenderPtr->ChangeAnimation("Mouse_Dash_Loop");
}
void Werner_Werman::DashUpdate(float _DeltaTime)
{
	float4 CurPos = GetTransform()->GetLocalPosition();

	if (LeftInitPosition.x >= CurPos.x)
	{
		GetTransform()->SetLocalPosition(LeftInitPosition);
		ChangeState(MouseState::Dash_Outro);
		return;
	}

	FowardPosition.x += 200.0f * _DeltaTime;
	float4 Movedir = float4::Zero;

	Movedir = (FowardPosition - CurPos);

	MoveDistance = -(Movedir * 2.0f * _DeltaTime);

	GetTransform()->AddWorldPosition(MoveDistance);
}
void Werner_Werman::DashEnd()
{
	IsDash = false;
}

void Werner_Werman::Explosion_IntroStart()
{
	WheelRenderPtr->Off();
	CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 144 });
	CanRenderPtr->GetTransform()->SetLocalPosition({ 0, 0 });

	WeaponRender->GetTransform()->SetLocalPosition({ -50, 230 });

	WeaponRender->On();

	WeaponRender->ChangeAnimation("Object_IntroBomb");
	CanRenderPtr->ChangeAnimation("Can_Idle");

	EffectPlayer = GameEngineSound::Play("mouse_can_explode_pre.wav");
}
void Werner_Werman::Explosion_IntroUpdate(float _DeltaTime)
{
	SetIntroCanBackTexture();
	
	if (0 == WeaponRender->GetCurrentFrame())
	{
		WeaponRender->GetTransform()->SetLocalPosition({ -30, 230 });
	}
	else if (1 == WeaponRender->GetCurrentFrame())
	{
		WeaponRender->GetTransform()->SetLocalPosition({ -45, 230 });
	}
	else
	{
		WeaponRender->GetTransform()->SetLocalPosition({ -50, 230 });
	}

	if (true == WeaponRender->IsAnimationEnd())
	{
		CanBackRenderPtr->Off();
		WeaponRender->Off();
		CanRenderPtr->GetTransform()->SetLocalPosition({ -10, 105 });
		CanRenderPtr->ChangeAnimation("Can_Explosion_Intro", false);

		if (CanRenderPtr->FindAnimation("Can_Explosion_Intro")->IsEnd())
		{
			ChangeState(MouseState::Explosion_Loop);
			return;
		}
	}
}
void Werner_Werman::Explosion_IntroEnd()
{

}

void Werner_Werman::Explosion_LoopStart()
{
	CanRenderPtr->ChangeAnimation("Can_Explosion_Loop");
	CreateStick();
}
void Werner_Werman::Explosion_LoopUpdate(float _DeltaTime)
{
	ExplosionLoopTime += _DeltaTime;

	if (0.5f <= ExplosionLoopTime)
	{
		ChangeState(MouseState::Explosion);
		return;
	}
}
void Werner_Werman::Explosion_LoopEnd()
{
	ExplosionLoopTime = 0.0f;
}

void Werner_Werman::ExplosionStart()
{
	Mouse_Map::MouseMapPtr->IsPhase2 = true;

	CanUpRenderPtr->CreateAnimation({ .AnimationName = "Can_Tin_Up", .SpriteName = "Can_Tin_Up", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
	CanRenderPtr->SetAnimationStartEvent("Can_Explosion_Outro", 4, std::bind(&Werner_Werman::CreateExplosionSFX, this));
	CanRenderPtr->ChangeAnimation("Can_Explosion_Outro");
	WheelRenderPtr->ChangeAnimation("Plat_Loop", false);
	WeaponRender->ChangeAnimation("Scissor_Down_Loop");
	CanUpRenderPtr->ChangeAnimation("Can_Tin_Up");
	CanBackRenderPtr->SetScaleToTexture("Tin_Boil_Back_001.png");

	WeaponRender->GetTransform()->SetLocalPosition({ 0, 100 });
	CanUpRenderPtr->GetTransform()->SetLocalPosition({ -10, 0 });
	CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 40 });
	MouseRenderPtr->GetTransform()->SetLocalPosition({ -10, 130 });
	WheelRenderPtr->GetTransform()->SetLocalPosition({ -10, -90 });

	WheelRenderPtr->GetTransform()->AddLocalPosition({ 0, 0, 1 });

	FlamecannonRenderPtr_Left->GetTransform()->SetLocalRotation({ 0, 180, 0 });

	FlamecannonRenderPtr_Left->GetTransform()->SetLocalPosition({ 50, -55 });
	FlamecannonRenderPtr_Right->GetTransform()->SetLocalPosition({ -60, -55 });

	if (nullptr == Phase2Parent)
	{
		Phase2Parent = CreateComponent<GameEngineSpriteRenderer>();
		Phase2Parent->SetScaleToTexture("RedBox.png");
		Phase2Parent->GetTransform()->SetLocalScale({ 1, 1, 1 });
		Phase2Parent->ColorOptionValue.MulColor.a = 0.0f;
	}

	BodyCollisionPtr->GetTransform()->SetLocalScale({ 160, 320, -2 });
	EXCollisionPtr->GetTransform()->SetLocalScale({ 160, 320, -2 });
	BodyCollisionPtr->GetTransform()->SetLocalPosition({ 0, 100 });
	EXCollisionPtr->GetTransform()->SetLocalPosition({ 0, 100 });

	BodyCollisionPtr->GetTransform()->SetParent(Phase2Parent->GetTransform());
	EXCollisionPtr->GetTransform()->SetParent(Phase2Parent->GetTransform());
	CanUpRenderPtr->GetTransform()->SetParent(Phase2Parent->GetTransform());
	CanBackRenderPtr->GetTransform()->SetParent(Phase2Parent->GetTransform());
	MouseRenderPtr->GetTransform()->SetParent(Phase2Parent->GetTransform());
	FlamecannonRenderPtr_Left->GetTransform()->SetParent(Phase2Parent->GetTransform());
	FlamecannonRenderPtr_Right->GetTransform()->SetParent(Phase2Parent->GetTransform());

	EffectPlayer = GameEngineSound::Play("mouse_can_explode.wav");
}
void Werner_Werman::ExplosionUpdate(float _DeltaTime)
{
	if (7 == CanRenderPtr->GetCurrentFrame())
	{
		IsPhase2 = true;
		WheelRenderPtr->On();
		PlatformCollisionPtr->On();
	}

	if (true == CanRenderPtr->IsAnimationEnd())
	{
		CanRenderPtr->Off();
		MouseRenderPtr->On();
		CanUpRenderPtr->On();
		CanBackRenderPtr->On();
		WeaponRender->On();
		FlamecannonRenderPtr_Left->On();
		FlamecannonRenderPtr_Right->On();

		DelayTime = 0.0f;
		MoveTime = 0.0f;
		WeaponType = false;
		IsShake = false;

		ChangeState(MouseState::Idle_Phase2);
		return;
	}
}
void Werner_Werman::ExplosionEnd()
{

}

void Werner_Werman::Idle_Phase2Start()
{
	Phase2IdleDownPosition = Phase2Parent->GetTransform()->GetLocalPosition() + float4{ 0, 50, 0 };
	Phase2IdleUpPosition = Phase2IdleDownPosition + float4{0, 250, 0};

	Phase2IdleRightMovePosition = GetTransform()->GetLocalPosition();
	Phase2IdleLeftMovePosition = Phase2IdleRightMovePosition + float4{ -70, 0 };

	ChangeState_Phase2(Phase2State::Intro);
}
void Werner_Werman::Idle_Phase2Update(float _DeltaTime)
{
	SetCanTinBackTexture();

	float4 CurPos = Phase2Parent->GetTransform()->GetLocalPosition();

	if (false == Phase2InitCorrection)
	{
		float Movedis = 700.0f * _DeltaTime;

		if (Phase2IdleDownPosition.y >= CurPos.y)
		{
			Phase2Parent->GetTransform()->AddLocalPosition({ 0, Movedis, 0 });
			return;
		}
		else
		{
			Phase2InitCorrection = true;
			Phase2Parent->GetTransform()->SetLocalPosition(Phase2IdleDownPosition);
		}
	}

	if (HP <= 450.0f)
	{
		Phase2End = true;

		float4 ParentCurPos = Phase2Parent->GetTransform()->GetLocalPosition();
		float4 ActorCurPos = GetTransform()->GetLocalPosition();
		bool YEnd = false;
		bool XEnd = false;
		
		if (Phase2IdleDownPosition.y + 10.0f < ParentCurPos.y)
		{
			float MoveDis = 500.0f * _DeltaTime;
			Phase2Parent->GetTransform()->AddLocalPosition({ 0, -MoveDis });
		}
		else if (Phase2IdleDownPosition.y + 10.0f >= ParentCurPos.y)
		{
			Phase2Parent->GetTransform()->SetLocalPosition({ Phase2IdleDownPosition.x , Phase2IdleDownPosition.y + 10.0f });
			YEnd = true;
		}

		if (Phase2IdleRightMovePosition.x > ActorCurPos.x)
		{
			float MoveDis = 200.0f * _DeltaTime;
			GetTransform()->AddLocalPosition({ MoveDis , 0 });
			Phase2MoveDistance = -MoveDis;
		}
		else if (Phase2IdleRightMovePosition.x <= ActorCurPos.x)
		{
			GetTransform()->SetLocalPosition(Phase2IdleRightMovePosition);
			Phase2MoveDistance = 0.0f;
			XEnd = true;
		}

		if (true == YEnd && true == XEnd)
		{
			MouseTransitionEndLoop = true;
		}

		PlatformCollisionCheck(-Phase2MoveDistance);
		UpdateState_Phase2(_DeltaTime);
		UpdateState_Scissor(_DeltaTime);
		UpdateState_Wheel(_DeltaTime);

		return;
	}

	if (false == IsMoveState)
	{
		WeaponType = true;

		if (Phase2IdleUpPosition.y > CurPos.y && false == IsPhase2UpPosition)
		{
			MoveTime += _DeltaTime;
			Phase2Parent->GetTransform()->SetLocalPosition(float4::Lerp(Phase2IdleDownPosition, Phase2IdleUpPosition, MoveTime * 2.5f));
		}
		else if (true == IsPhase2UpPosition)
		{
			Phase2Parent->GetTransform()->SetLocalPosition({ Phase2IdleUpPosition.x , Phase2IdleUpPosition.y - 20.0f });
		}
		else if (Phase2IdleUpPosition.y <= CurPos.y)
		{
			IsPhase2UpPosition = true;
			IsCreateFlamethrower = true;
		}

		if (true == IsCreateFlamethrower)
		{
			IsCreateFlamethrower = false;
			CreateFlamethrower();
		}

		if (true == IsFlameEnd)
		{
			DelayTime += _DeltaTime;
		}

		if (0.8f <= DelayTime)
		{
			MoveTime = 0.0f;
			DelayTime = 0.0f;
			IsFlameEnd = false;
			IsMoveState = true;
			IsPhase2UpPosition = false;
		}
	}
	else
	{
		WeaponType = false;

		if (Phase2IdleDownPosition.y < CurPos.y && false == IsPhase2DownPosition)
		{
			MoveTime += _DeltaTime;
			Phase2Parent->GetTransform()->SetLocalPosition(float4::Lerp(Phase2IdleUpPosition, Phase2IdleDownPosition, MoveTime * 2.5f));
		}
		else if (true == IsPhase2DownPosition)
		{
			Phase2Parent->GetTransform()->SetLocalPosition({ Phase2IdleDownPosition.x , Phase2IdleDownPosition.y + 10.0f });
		}
		else if (Phase2IdleDownPosition.y >= CurPos.y)
		{
			IsPhase2DownPosition = true;
			IsCreateFlamethrower = true;
		}

		if (true == IsCreateFlamethrower)
		{
			IsCreateFlamethrower = false;
			CreateFlamethrower();
		}

		if (true == IsFlameEnd)
		{
			DelayTime += _DeltaTime;
		}

		if (0.8f <= DelayTime)
		{
			MoveTime = 0.0f;
			DelayTime = 0.0f;
			IsFlameEnd = false;
			IsMoveState = false;
			IsPhase2DownPosition = false;
		}
	}

	UpdateState_Phase2(_DeltaTime);
	UpdateState_Scissor(_DeltaTime);

	if (GetTransform()->GetLocalPosition().x == Phase2IdleLeftMovePosition.x)
	{
		MoveLoopTime = 0.0f;

		if (false == IsShake)
		{
			MoveDelayTime = 0.0f;
			IsShake = true;
			WheelMoveCount = 1;
		}
	}
	else if (GetTransform()->GetLocalPosition().x == Phase2IdleRightMovePosition.x)
	{
		MoveLoopTime = 0.0f;

		if (true == IsShake)
		{
			MoveDelayTime = 0.0f;
			IsShake = false;
			WheelMoveCount = 1;
		}
	}

	MoveDelayTime += _DeltaTime;

	if (1.0f <= MoveDelayTime)
	{
		if (1 == WheelMoveCount)
		{
			WheelMoveCount = 0;
			IsWheelStart = true;
		}

		MoveLoopTime += _DeltaTime;
	}
	
	float4 CurPosision = GetTransform()->GetLocalPosition();
	float4 MoveMount = float4::Zero;

	if (false == IsShake)
	{
		MoveMount = float4::LerpClamp(Phase2IdleRightMovePosition, Phase2IdleLeftMovePosition, MoveLoopTime * 1.5f);
		GetTransform()->SetLocalPosition(MoveMount);
	}
	else
	{
		MoveMount = float4::LerpClamp(Phase2IdleLeftMovePosition, Phase2IdleRightMovePosition, MoveLoopTime * 1.5f);
		GetTransform()->SetLocalPosition(MoveMount);
	}

	Phase2MoveDistance = CurPosision.x - MoveMount.x;

	PlatformCollisionCheck(-Phase2MoveDistance);
	UpdateState_Wheel(_DeltaTime);
}
void Werner_Werman::Idle_Phase2End()
{

}

void Werner_Werman::Dash_OutroStart()
{
	MouseRenderPtr->ChangeAnimation("Mouse_Dash_Outro");

	MouseRenderPtr->SetAnimationStartEvent("Mouse_Dash_Outro", 0, std::bind(&Werner_Werman::DashStopSound, this));
	MouseRenderPtr->SetAnimationStartEvent("Mouse_Dash_Outro", 21, std::bind(&Werner_Werman::MouseRollSound, this));
}
void Werner_Werman::Dash_OutroUpdate(float _DeltaTime)
{
	if (false == Directbool)
	{
		if (41 == MouseRenderPtr->GetCurrentFrame())
		{
			MouseRenderPtr->GetTransform()->SetLocalPosition({ -2, 150 });
		}
		else if (40 == MouseRenderPtr->GetCurrentFrame())
		{
			MouseRenderPtr->GetTransform()->SetLocalPosition({ -4, 150 });
		}
		else if (39 == MouseRenderPtr->GetCurrentFrame())
		{
			MouseRenderPtr->GetTransform()->SetLocalPosition({ -6, 150 });
		}
		else if (38 == MouseRenderPtr->GetCurrentFrame())
		{
			MouseRenderPtr->GetTransform()->SetLocalPosition({ -8, 150 });
		}
		else if (37 == MouseRenderPtr->GetCurrentFrame())
		{
			MouseRenderPtr->GetTransform()->SetLocalPosition({ -10, 150 });
		}
		else if (36 == MouseRenderPtr->GetCurrentFrame())
		{
			MouseRenderPtr->GetTransform()->SetLocalPosition({ -12, 150 });
		}
		else if (35 == MouseRenderPtr->GetCurrentFrame())
		{
			MouseRenderPtr->GetTransform()->SetLocalPosition({ -14, 150 });
		}
		else if (34 == MouseRenderPtr->GetCurrentFrame())
		{
			MouseRenderPtr->GetTransform()->SetLocalPosition({ -16, 150 });
		}
		else if (33 == MouseRenderPtr->GetCurrentFrame())
		{
			MouseRenderPtr->GetTransform()->SetLocalPosition({ -18, 150 });
		}
	}

	if (true == MouseRenderPtr->IsAnimationEnd())
	{
		MouseRenderPtr->Off();
		Directbool = true;
		ChangeState(MouseState::Idle);
		return;
	}
}
void Werner_Werman::Dash_OutroEnd()
{
	IsDash = false;
}

void Werner_Werman::SetCanTinBackTexture()
{
	if (2 == CanUpRenderPtr->GetCurrentFrame())
	{
		CanBackRenderPtr->SetScaleToTexture("Tin_Boil_Back_003.png");
	}
	else if (1 == CanUpRenderPtr->GetCurrentFrame())
	{
		CanBackRenderPtr->SetScaleToTexture("Tin_Boil_Back_002.png");
	}
	else if (0 == CanUpRenderPtr->GetCurrentFrame())
	{
		CanBackRenderPtr->SetScaleToTexture("Tin_Boil_Back_001.png");
	}
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

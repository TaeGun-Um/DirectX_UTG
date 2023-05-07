#include "PrecompileHeader.h"
#include "Player.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Peashooter.h"
#include "Peashooter_EX.h"
#include "Spread.h"
#include "Spread_EX.h"
#include "EXDust.h"
#include "MoveDust.h"
#include "LandDust.h"
#include "ParryEffect.h"

Player* Player::MainPlayer = nullptr;

Player::Player() 
{
	MainPlayer = this;
}

Player::~Player() 
{
}

void Player::Start()
{
	RenderPtr = AnimationCreate_Field();
	SetCameraFollowType(CameraFollowType::Field);
	SetMoveSpeed(380.0f);
	ChangeState(PlayerState::Idle);

	// 픽셀체크 디버깅용 닷
	{
		DebugRenderPtr0 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr1 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr2 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr3 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr4 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr5 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr6 = CreateComponent<GameEngineSpriteRenderer>();

		DebugRenderPtr0->SetScaleToTexture("RedDot.png");
		DebugRenderPtr1->SetScaleToTexture("RedDot.png");
		DebugRenderPtr2->SetScaleToTexture("RedDot.png");
		DebugRenderPtr3->SetScaleToTexture("RedDot.png");
		DebugRenderPtr4->SetScaleToTexture("RedDot.png");
		DebugRenderPtr5->SetScaleToTexture("RedDot.png");
		DebugRenderPtr6->SetScaleToTexture("RedDot.png");

		DebugRenderPtr1->GetTransform()->SetLocalPosition({ -40, 10 }); // 왼쪽 벽
		DebugRenderPtr2->GetTransform()->SetLocalPosition({ 25, 10 });  // 오른쪽 벽
		DebugRenderPtr1->GetTransform()->SetLocalPosition({ -40, -2 }); // 왼쪽 낙하
		DebugRenderPtr2->GetTransform()->SetLocalPosition({ 25, -2 });  // 오른쪽 낙하
		//DebugRenderPtr5->Off();
		//DebugRenderPtr6->Off();

		DebugRenderPtr0->Off();
		DebugRenderPtr1->Off();
		DebugRenderPtr2->Off();
		DebugRenderPtr3->Off();
		DebugRenderPtr4->Off();
		DebugRenderPtr5->Off();
		DebugRenderPtr6->Off();
	}
}
void Player::Update(float _DeltaTime)
{
	if (false == IsCorrection)
	{
		PositionCorrection();
		return;
	}

	MoveCamera(_DeltaTime);
	DirectCheck();
	UpdateState(_DeltaTime);
	ProjectileCreate(_DeltaTime);
	PixelCheck(_DeltaTime);

	if (true == GameEngineInput::IsDown("Dash"))
	{
		int a = 0;
	}

	if (true == IsDebugRender)
	{
		DebugRenderPtr0->On();
		DebugRenderPtr1->On();
		DebugRenderPtr2->On();
		DebugRenderPtr3->On();
		DebugRenderPtr4->On();
		DebugRenderPtr5->On();
		DebugRenderPtr6->On();
	}
	else
	{
		DebugRenderPtr0->Off();
		DebugRenderPtr1->Off();
		DebugRenderPtr2->Off();
		DebugRenderPtr3->Off();
		DebugRenderPtr4->Off();
		DebugRenderPtr5->Off();
		DebugRenderPtr6->Off();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     AssistFunction                       //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 플레이어 위치 보정 함수(최초 레벨 init 시 실시)
void Player::PositionCorrection()
{
	float4 PlayerPos = GetTransform()->GetLocalPosition();

	if (0 >= PlayerPos.y)
	{
		MsgAssert("플레이어의 위치는 y = 0 위로 세팅해야 합니다. 비정상적인 플레이어 위치입니다.");
		return;
	}

	GameEnginePixelColor ColMapPixel = PixelCollisionCheck.PixelCheck(PlayerPos);

	// 현재 위치의 Pixel이 Black이라면 이후 PixelCheck에서 연산 실시
	if (true == PixelCollisionCheck.IsBlack(ColMapPixel))
	{
		IsCorrection = true;
	}

	// 현재 위치의 Pixel이 Black이 아니라면 위치를 밑으로 이동
	if (false == PixelCollisionCheck.IsBlack(ColMapPixel))
	{
		while (true)
		{
			GetTransform()->AddLocalPosition({ 0, -1 });

			PlayerPos = GetTransform()->GetLocalPosition();

			GameEnginePixelColor GravityPixel = PixelCollisionCheck.PixelCheck(PlayerPos);

			if (true == PixelCollisionCheck.IsBlack(GravityPixel))
			{
				IsCorrection = true;
				break;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     CreateActor                       /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::ProjectileCreate(float _DeltaTime)
{
	ProjectileCreateTime += _DeltaTime;

	if (true == GameEngineInput::IsDown("WeaponSwap"))
	{
		WeaponType = !WeaponType;
		bool Check = WeaponType;
		ProjectileCreateTime = 0.0f;
	}

	// WeaponType = true : Peashooter
	// WeaponType = false : Spread

	if (0.15f <= ProjectileCreateTime && false == IsDash && GameEngineInput::IsPress("Attack"))
	{
		if (true == WeaponType)
		{
			ProjectileCreateTime = 0.0f;
			CreatePeashooter();
		}
		else if (false == WeaponType)
		{
			ProjectileCreateTime = 0.0f;
			// CreateSpread();
		}
	}

}

// 기본 공격
void Player::CreatePeashooter()
{
	std::shared_ptr<Peashooter> Projectile = GetLevel()->CreateActor<Peashooter>(1);

	float4 PlayerPosition = GetTransform()->GetLocalPosition();
	float4 ProjectilePosition = PlayerPosition;

	switch (ADValue)
	{
	case AttackDirection::Right_Up:
	{
		ProjectilePosition += float4{ 10, 100 };
	}
	break;
	case AttackDirection::Right_DiagonalUp:
	{

	}
	break;
	case AttackDirection::Right_Front:
	{
		ProjectilePosition += float4{ 60, 70 };
	}
	break;
	case AttackDirection::Right_DiagonalDown:
	{

	}
	break;
	case AttackDirection::Right_Down:
	{

	}
	break;
	case AttackDirection::Left_Up:
	{
		ProjectilePosition += float4{ -10, 100 };
	}
	break;
	case AttackDirection::Left_DiagonalUp:
	{

	}
	break;
	case AttackDirection::Left_Front:
	{
		ProjectilePosition += float4{ -70, 70 };
	}
	break;
	case AttackDirection::Left_DiagonalDown:
	{

	}
	break;
	case AttackDirection::Left_Down:
	{

	}
	break;
	default:
		break;
	}

	Projectile->SetStartPosition(ProjectilePosition);
	Projectile->SetADValue(ADValue);
	Projectile->SetDirection(Directbool);

}

// 기본 EX 공격
void Player::CreatePeashooter_EX() {}

// 2번 공격
void Player::CreateSpread()
{
	std::shared_ptr<Peashooter> Projectile = GetLevel()->CreateActor<Peashooter>(1);

	float4 PlayerPosition = GetTransform()->GetLocalPosition();

	Projectile->SetStartPosition(PlayerPosition);
	Projectile->SetDirection(Directbool);
}

// 2번 EX 공격 
void Player::CreateSpread_EX() {}

// EX 공격 시 Dust 생성
void Player::CreateEXDust() {}

// 움직일 때 Dust 생성
void Player::CreateMoveDust() {}

// 점프나 Fall 후 Land시 Dust 생성
void Player::CreateLandDust() {}

// Parry시 생성되는 Effect
void Player::CreateParryEffect() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                         FSM                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::DirectCheck()
{
	if (true == IsDash)
	{
		return;
	}

	if (true == GameEngineInput::IsPress("MoveRight"))
	{
		Directbool = true;
		GetTransform()->SetLocalPositiveScaleX();
		RenderPtr->GetTransform()->SetLocalPosition({ 0, 90 });
		
		{
			DebugRenderPtr1->GetTransform()->SetLocalPosition({ -40, 10 });
			DebugRenderPtr2->GetTransform()->SetLocalPosition({ 25, 10 });
			DebugRenderPtr3->GetTransform()->SetLocalPosition({ -40, -2 });
			DebugRenderPtr4->GetTransform()->SetLocalPosition({ 25, -2 });
			//DebugRenderPtr5->Off();
			//DebugRenderPtr6->Off();
		}
	}
	
	if (true == GameEngineInput::IsPress("MoveLeft"))
	{
		Directbool = false;
		GetTransform()->SetLocalNegativeScaleX();
		RenderPtr->GetTransform()->SetLocalPosition({ 10, 90 });

		{
			DebugRenderPtr1->GetTransform()->SetLocalPosition({ -25, 10 });
			DebugRenderPtr2->GetTransform()->SetLocalPosition({ 40, 10 });
			DebugRenderPtr3->GetTransform()->SetLocalPosition({ -25, -2 });
			DebugRenderPtr4->GetTransform()->SetLocalPosition({ 40, -2 });
			//DebugRenderPtr5->Off();
			//DebugRenderPtr6->Off();
		}
	}

	AttackDirectCheck();
}

void Player::AttackDirectCheck()
{
	if (true == Directbool)
	{
		if (true == GameEngineInput::IsPress("MoveUp") && true == GameEngineInput::IsPress("MoveRight"))
		{
			ADValue = AttackDirection::Right_DiagonalUp;
		}
		else if (true == GameEngineInput::IsPress("MoveDown") && true == GameEngineInput::IsPress("MoveRight"))
		{
			ADValue = AttackDirection::Right_DiagonalDown;
		}
		else if (true == GameEngineInput::IsPress("MoveUp"))
		{
			ADValue = AttackDirection::Right_Up;
		}
		else if (true == GameEngineInput::IsPress("MoveRight"))
		{
			ADValue = AttackDirection::Right_Front;
		}
		else if (true == GameEngineInput::IsPress("MoveDown"))
		{
			ADValue = AttackDirection::Right_Down;
		}
	}
	else
	{
		if (true == GameEngineInput::IsPress("MoveUp") && true == GameEngineInput::IsPress("MoveLeft"))
		{
			ADValue = AttackDirection::Left_DiagonalUp;
		}
		else if (true == GameEngineInput::IsPress("MoveDown") && true == GameEngineInput::IsPress("MoveLeft"))
		{
			ADValue = AttackDirection::Left_DiagonalDown;
		}
		else if (true == GameEngineInput::IsPress("MoveUp"))
		{
			ADValue = AttackDirection::Left_Up;
		}
		else if (true == GameEngineInput::IsPress("MoveLeft"))
		{
			ADValue = AttackDirection::Left_Front;
		}
		else if (true == GameEngineInput::IsPress("MoveDown"))
		{
			ADValue = AttackDirection::Left_Down;
		}
	}
}

void Player::ChangeState(PlayerState _StateValue)
{
	PlayerState NextState = _StateValue;
	PlayerState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case PlayerState::Fall:
		FallStart();
		break;
	case PlayerState::Idle:
		IdleStart();
		break;
	case PlayerState::Move:
		MoveStart();
		break;
	case PlayerState::Dash:
		DashStart();
		break;
	case PlayerState::DuckReady:
		DuckReadyStart();
		break;
	case PlayerState::Duck:
		DuckStart();
		break;
	case PlayerState::Jump:
		JumpStart();
		break;
	case PlayerState::Slap:
		SlapStart();
		break;
	case PlayerState::AttackReady:
		AttackReadyStart();
		break;
	case PlayerState::Attack:
		AttackStart();
		break;
	case PlayerState::RunAttack:
		RunAttackStart();
		break;
	case PlayerState::DuckAttack:
		DuckAttackStart();
		break;
	case PlayerState::EXAttack:
		EXAttackStart();
		break;
	case PlayerState::Holding:
		HoldingStart();
		break;
	case PlayerState::HoldingAttack:
		HoldingAttackStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case PlayerState::Fall:
		FallEnd();
		break;
	case PlayerState::Idle:
		IdleEnd();
		break;
	case PlayerState::Move:
		MoveEnd();
		break;
	case PlayerState::Dash:
		DashEnd();
		break;
	case PlayerState::DuckReady:
		DuckReadyEnd();
		break;
	case PlayerState::Duck:
		DuckEnd();
		break;
	case PlayerState::Jump:
		JumpEnd();
		break;
	case PlayerState::Slap:
		SlapEnd();
		break;
	case PlayerState::AttackReady:
		AttackReadyEnd();
		break;
	case PlayerState::Attack:
		AttackEnd();
		break;
	case PlayerState::RunAttack:
		RunAttackEnd();
		break;
	case PlayerState::DuckAttack:
		DuckAttackEnd();
		break;
	case PlayerState::EXAttack:
		EXAttackEnd();
		break;
	case PlayerState::Holding:
		HoldingEnd();
		break;
	case PlayerState::HoldingAttack:
		HoldingAttackEnd();
		break;
	default:
		break;
	}
}

void Player::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case PlayerState::Fall:
		FallUpdate(_DeltaTime);
		break;
	case PlayerState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	case PlayerState::Move:
		MoveUpdate(_DeltaTime);
		break;
	case PlayerState::Dash:
		DashUpdate(_DeltaTime);
		break;
	case PlayerState::DuckReady:
		DuckReadyUpdate(_DeltaTime);
		break;
	case PlayerState::Duck:
		DuckUpdate(_DeltaTime);
		break;
	case PlayerState::Jump:
		JumpUpdate(_DeltaTime);
		break;
	case PlayerState::Slap:
		SlapUpdate(_DeltaTime);
		break;
	case PlayerState::AttackReady:
		AttackReadyUpdate(_DeltaTime);
		break;
	case PlayerState::Attack:
		AttackUpdate(_DeltaTime);
		break;
	case PlayerState::RunAttack:
		RunAttackUpdate(_DeltaTime);
		break;
	case PlayerState::DuckAttack:
		DuckAttackUpdate(_DeltaTime);
		break;
	case PlayerState::EXAttack:
		EXAttackUpdate(_DeltaTime);
		break;
	case PlayerState::Holding:
		HoldingUpdate(_DeltaTime);
		break;
	case PlayerState::HoldingAttack:
		HoldingAttackUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Player::FallStart()
{
	RenderPtr->SetTexture("Ground_Jump_002.png");
	RenderPtr->GetTransform()->SetLocalScale({ 170, 220, 1 });
}
void Player::FallUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("Dash") && true == AirDash) // AirDash true는 PixelCheck에서 진행
	{
		AirDash = false;
		ChangeState(PlayerState::Dash);
		return;
	}

	// 낙하 시 이동
	float MoveDis = MoveSpeed * _DeltaTime;

	if (true == GameEngineInput::IsPress("MoveRight"))
	{
		GetTransform()->AddLocalPosition({ MoveDis, 0 });
	}
	if (true == GameEngineInput::IsPress("MoveLeft"))
	{
		GetTransform()->AddLocalPosition({ -MoveDis, 0 });
	}

	if (true == IsFall)
	{
		MoveDirect.y += -3000.0f * _DeltaTime;
		GetTransform()->AddLocalPosition(MoveDirect * _DeltaTime);
	}
	else if (false == IsFall)
	{
		MoveDirect.y = 0;
	}

	if (false == IsFall)
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}
void Player::FallEnd()
{
	MoveDirect = float4::Zero;
	// IsFall의 false는 PixelCheck에서 실시
}

void Player::IdleStart()
{
	RenderPtr->SetTexture("Ground_Idle_001.png");
	RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
}
void Player::IdleUpdate(float _DeltaTime)
{
	if (true == IsFall)
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	if (true == GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	if (true == GameEngineInput::IsDown("Dash"))
	{
		ChangeState(PlayerState::Dash);
		return;
	}

	if (true == GameEngineInput::IsPress("Hold"))
	{
		ChangeState(PlayerState::Holding);
		return;
	}

	if (true == GameEngineInput::IsPress("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	if (true == GameEngineInput::IsPress("MoveUp"))
	{
		ChangeState(PlayerState::AttackReady);
		return;
	}

	if (true == GameEngineInput::IsPress("MoveLeft") && true == GameEngineInput::IsPress("MoveRight"))
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	if (true == GameEngineInput::IsPress("MoveDown"))
	{
		ChangeState(PlayerState::DuckReady);
		return;
	}

	if (true == GameEngineInput::IsPress("MoveRight") || true == GameEngineInput::IsPress("MoveLeft"))
	{
		ChangeState(PlayerState::Move);
		return;
	}
}
void Player::IdleEnd()
{
}

void Player::MoveStart()
{
	RenderPtr->SetTexture("Run_Normal_001.png");
	RenderPtr->GetTransform()->SetLocalScale({ 170, 200, 1 });
}
void Player::MoveUpdate(float _DeltaTime)
{
	if (true == IsFall)
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	if (true == GameEngineInput::IsDown("Dash"))
	{
		ChangeState(PlayerState::Dash);
		return;
	}

	if (true == GameEngineInput::IsPress("Hold"))
	{
		ChangeState(PlayerState::Holding);
		return;
	}

	if (true == GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	if (false == IsHold)
	{
		float MoveDis = MoveSpeed * _DeltaTime;

		if (true == GameEngineInput::IsPress("MoveRight"))
		{
			GetTransform()->AddLocalPosition({ MoveDis, 0 });
		}
		if (true == GameEngineInput::IsPress("MoveLeft"))
		{
			GetTransform()->AddLocalPosition({ -MoveDis, 0 });
		}
	}

	if (true == GameEngineInput::IsPress("Attack"))
	{
		ChangeState(PlayerState::RunAttack);
		return;
	}

	if (true == GameEngineInput::IsPress("MoveDown"))
	{
		ChangeState(PlayerState::DuckReady);
		return;
	}

	if (false == GameEngineInput::IsPress("MoveLeft") && false == GameEngineInput::IsPress("MoveRight"))
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}
void Player::MoveEnd()
{
}

void Player::DashStart()
{
	if (true == IsFall)
	{
		RenderPtr->SetTexture("Dash_Air_008.png");
		RenderPtr->GetTransform()->SetLocalScale({ 350, 200, 1 });
	}
	else
	{
		RenderPtr->SetTexture("Dash_Ground_008.png");
		RenderPtr->GetTransform()->SetLocalScale({ 350, 200, 1 });
	}

	if (true == Directbool)
	{
		RenderPtr->GetTransform()->AddLocalPosition({ -100, 0 });
	}
	else
	{
		RenderPtr->GetTransform()->AddLocalPosition({ -10, 0 });
	}
	
	IsDash = true;
}
void Player::DashUpdate(float _DeltaTime)
{
	DashTime += _DeltaTime;

	float MoveDis = (MoveSpeed * 2) * _DeltaTime;

	if (true == Directbool && 0.4f >= DashTime) // 오른쪽
	{
		AirDash = false;
		GetTransform()->AddLocalPosition({ MoveDis, 0 });
		return;
	}
	else if (false == Directbool && 0.4f >= DashTime)
	{
		AirDash = false;
		GetTransform()->AddLocalPosition({ -MoveDis, 0 });
		return;
	}

	if (true == IsFall && 0.4f <= DashTime)
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	if (0.4f <= DashTime)
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}
void Player::DashEnd()
{
	if (true == Directbool)
	{
		RenderPtr->GetTransform()->AddLocalPosition({ 100, 0 });
	}
	else
	{
		RenderPtr->GetTransform()->AddLocalPosition({ 10, 0 });
	}

	DashTime = 0.0f;
	IsDash = false;
}

void Player::DuckReadyStart()
{
	RenderPtr->SetTexture("Ground_Duck_001.png");
	RenderPtr->GetTransform()->SetLocalScale({ 220, 220, 1 });
}
void Player::DuckReadyUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	if (true == GameEngineInput::IsDown("Dash"))
	{
		ChangeState(PlayerState::Dash);
		return;
	}

	if (false == GameEngineInput::IsPress("MoveDown"))
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	DuckTime += _DeltaTime;

	if (DuckTime >= 0.05f)
	{
		if (true == GameEngineInput::IsPress("Attack"))
		{
			ChangeState(PlayerState::DuckAttack);
			return;
		}
		else
		{
			ChangeState(PlayerState::Duck);
			return;
		}
	}
}
void Player::DuckReadyEnd()
{
	DuckTime = 0.0f;
}

void Player::DuckStart()
{
	RenderPtr->SetTexture("Ground_Duck_008.png");
	RenderPtr->GetTransform()->SetLocalScale({ 220, 220, 1 });
}
void Player::DuckUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	if (true == GameEngineInput::IsDown("Dash"))
	{
		ChangeState(PlayerState::Dash);
		return;
	}

	if (true == GameEngineInput::IsPress("Attack"))
	{
		ChangeState(PlayerState::DuckAttack);
		return;
	}

	if (false == GameEngineInput::IsPress("MoveDown"))
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}
void Player::DuckEnd()
{
}
	 
void Player::JumpStart()
{
	RenderPtr->SetTexture("Ground_Jump_002.png");
	RenderPtr->GetTransform()->SetLocalScale({ 170, 220, 1 });

	// 점프력
	if (false == IsJump)
	{
		MoveDirect.y = 900.0f;
		IsJump = true;
	}
}
void Player::JumpUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("Dash") && true == AirDash)  // AirDash true는 PixelCheck에서 진행
	{
		AirDash = false;
		ChangeState(PlayerState::Dash);
		return;
	}

	JumpTime += _DeltaTime;

	// 점프 시 이동
	float MoveDis = MoveSpeed * _DeltaTime;

	if (true == GameEngineInput::IsPress("MoveRight"))
	{
		GetTransform()->AddLocalPosition({ MoveDis, 0 });
	}
	if (true == GameEngineInput::IsPress("MoveLeft"))
	{
		GetTransform()->AddLocalPosition({ -MoveDis, 0 });
	}

	// 점프
	if (true == GameEngineInput::IsPress("Jump") && 0.01f <= JumpTime)
	{
		if (0.15f >= JumpTime)
		{
			MoveDirect.y += 2200.0f * _DeltaTime;
		}
	}

	if (true == IsJump && 0.01f <= JumpTime)
	{
		MoveDirect.y += -3000.0f * _DeltaTime;
		GetTransform()->AddLocalPosition(MoveDirect * _DeltaTime);
	}
	else if (false == IsJump && 0.01f <= JumpTime)
	{
		MoveDirect.y = 0;
	}

	if (false == IsJump)
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}
void Player::JumpEnd()
{
	MoveDirect = float4::Zero;
	JumpTime = 0.0f;
	// IsJump의 false는 PixelCheck에서 실시
}

void Player::SlapStart()
{
}
void Player::SlapUpdate(float _DeltaTime)
{
}
void Player::SlapEnd()
{
}

// MoveUp 전용 FSM
void Player::AttackReadyStart()
{
	RenderPtr->SetTexture("Normal_Up_001.png");
	RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
}
void Player::AttackReadyUpdate(float _DeltaTime)
{
	if (true == IsFall)
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	if (true == GameEngineInput::IsDown("Dash"))
	{
		ChangeState(PlayerState::Dash);
		return;
	}

	if (true == GameEngineInput::IsPress("Hold"))
	{
		ChangeState(PlayerState::Holding);
		return;
	}

	if (true == GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	if (false == GameEngineInput::IsPress("MoveUp"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	if (true == GameEngineInput::IsPress("MoveRight") || true == GameEngineInput::IsPress("MoveLeft"))
	{
		ChangeState(PlayerState::Move);
		return;
	}

	if (true == GameEngineInput::IsPress("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}
}
void Player::AttackReadyEnd()
{

}

void Player::AttackStart()
{
}
void Player::AttackUpdate(float _DeltaTime)
{
	if (true == IsFall)
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	if (true == GameEngineInput::IsDown("Dash"))
	{
		ChangeState(PlayerState::Dash);
		return;
	}

	if (true == GameEngineInput::IsPress("Hold"))
	{
		ChangeState(PlayerState::HoldingAttack);
		return;
	}

	if (true == GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	switch (ADValue)
	{
	case AttackDirection::Right_Up:
	{
		RenderPtr->SetTexture("Shoot_Up_001.png");
		RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
	}
	break;
	case AttackDirection::Right_Front:
	{
		RenderPtr->SetTexture("Shoot_Straight_001.png");
		RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
	}
	break;
	case AttackDirection::Left_Up:
	{
		RenderPtr->SetTexture("Shoot_Up_001.png");
		RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
	}
	break;
	case AttackDirection::Left_Front:
	{
		RenderPtr->SetTexture("Shoot_Straight_001.png");
		RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
	}
	break;
	default:
		break;
	}
	
	// 방향키 안누르면 Front로 고정
	if (true == Directbool)
	{
		if (false == GameEngineInput::IsPress("MoveUp"))
		{
			ADValue = AttackDirection::Right_Front;
		}
	}
	else
	{
		if (false == GameEngineInput::IsPress("MoveUp"))
		{
			ADValue = AttackDirection::Left_Front;
		}
	}

	if (true == GameEngineInput::IsPress("MoveRight") && true == GameEngineInput::IsPress("Attack")
		|| true == GameEngineInput::IsPress("MoveLeft") && true == GameEngineInput::IsPress("Attack"))
	{
		ChangeState(PlayerState::RunAttack);
		return;
	}

	if (true == GameEngineInput::IsPress("MoveRight") || true == GameEngineInput::IsPress("MoveLeft"))
	{
		ChangeState(PlayerState::RunAttack);
		return;
	}

	if (true == GameEngineInput::IsPress("MoveDown"))
	{
		ChangeState(PlayerState::DuckReady);
		return;
	}

	if (false == GameEngineInput::IsPress("Attack"))
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}
void Player::AttackEnd()
{
}

void Player::RunAttackStart()
{
}
void Player::RunAttackUpdate(float _DeltaTime)
{
	if (true == IsFall)
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	if (true == GameEngineInput::IsDown("Dash"))
	{
		ChangeState(PlayerState::Dash);
		return;
	}

	if (true == GameEngineInput::IsPress("Hold"))
	{
		ChangeState(PlayerState::HoldingAttack);
		return;
	}

	if (true == GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	float MoveDis = MoveSpeed * _DeltaTime;

	if (true == GameEngineInput::IsPress("MoveRight"))
	{
		GetTransform()->AddLocalPosition({ MoveDis, 0 });
	}
	if (true == GameEngineInput::IsPress("MoveLeft"))
	{
		GetTransform()->AddLocalPosition({ -MoveDis, 0 });
	}

	switch (ADValue)
	{
	case AttackDirection::Right_DiagonalUp:
	{
		RenderPtr->SetTexture("Run_Shooting_DiagonalUp_001.png");
		RenderPtr->GetTransform()->SetLocalScale({ 170, 200, 1 });
	}
	break;
	case AttackDirection::Right_Front:
	{
		RenderPtr->SetTexture("Run_Shooting_Straight_001.png");
		RenderPtr->GetTransform()->SetLocalScale({ 170, 200, 1 });
	}
	break;
	case AttackDirection::Left_DiagonalUp:
	{
		RenderPtr->SetTexture("Run_Shooting_DiagonalUp_001.png");
		RenderPtr->GetTransform()->SetLocalScale({ 170, 200, 1 });
	}
	break;
	case AttackDirection::Left_Front:
	{
		RenderPtr->SetTexture("Run_Shooting_Straight_001.png");
		RenderPtr->GetTransform()->SetLocalScale({ 170, 200, 1 });
	}
	break;
	default:
		break;
	}

	// 방향키 안누르면 Front로 고정
	if (true == Directbool)
	{
		if (false == GameEngineInput::IsPress("MoveUp"))
		{
			ADValue = AttackDirection::Right_Front;
		}
	}
	else
	{
		if (false == GameEngineInput::IsPress("MoveUp"))
		{
			ADValue = AttackDirection::Left_Front;
		}
	}

	if (false == GameEngineInput::IsPress("MoveRight") && false == GameEngineInput::IsPress("MoveLeft"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	if (true == GameEngineInput::IsPress("MoveDown"))
	{
		ChangeState(PlayerState::DuckReady);
		return;
	}

	if (false == GameEngineInput::IsPress("Attack"))
	{
		ChangeState(PlayerState::Move);
		return;
	}
}
void Player::RunAttackEnd()
{
}

void Player::DuckAttackStart()
{
	RenderPtr->SetTexture("Ground_DuckShoot_001.png");
	RenderPtr->GetTransform()->SetLocalScale({ 220, 220, 1 });

	IsDuckAttack = true;
}
void Player::DuckAttackUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	if (true == GameEngineInput::IsDown("Dash"))
	{
		ChangeState(PlayerState::Dash);
		return;
	}

	// Duck은 위치 고정
	if (true == Directbool)
	{
		ADValue = AttackDirection::Right_Front;
	}
	else
	{
		ADValue = AttackDirection::Left_Front;
	}

	if (false == GameEngineInput::IsPress("Attack"))
	{
		ChangeState(PlayerState::Duck);
		return;
	}

	if (false == GameEngineInput::IsPress("MoveDown"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}
}
void Player::DuckAttackEnd()
{
	IsDuckAttack = false;
}
	
void Player::EXAttackStart()
{
}
void Player::EXAttackUpdate(float _DeltaTime)
{
}
void Player::EXAttackEnd()
{
}

void Player::HoldingStart()
{

}
void Player::HoldingUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("Hold"))
	{
		IsHold = true;

		if (true == GameEngineInput::IsDown("Dash"))
		{
			ChangeState(PlayerState::Dash);
			return;
		}

		if (true == GameEngineInput::IsDown("Jump"))
		{
			ChangeState(PlayerState::Jump);
			return;
		}

		if (true == GameEngineInput::IsPress("Attack"))
		{
			ChangeState(PlayerState::HoldingAttack);
			return;
		}

		switch (ADValue)
		{
		case AttackDirection::Right_Up:
		{
			RenderPtr->SetTexture("Normal_Up_001.png");
			RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
		}
			break;
		case AttackDirection::Right_DiagonalUp:
		{
			RenderPtr->SetTexture("Normal_DiagonalUp_001.png");
			RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
		}
			break;
		case AttackDirection::Right_Front:
		{
			RenderPtr->SetTexture("Normal_Straight_001.png");
			RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
		}
			break;
		case AttackDirection::Right_DiagonalDown:
		{
			RenderPtr->SetTexture("Normal_DiagonalDown_001.png");
			RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
		}
			break;
		case AttackDirection::Right_Down:
		{
			RenderPtr->SetTexture("Normal_Down_001.png");
			RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
		}
			break;
		case AttackDirection::Left_Up:
		{
			RenderPtr->SetTexture("Normal_Up_001.png");
			RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
		}
			break;
		case AttackDirection::Left_DiagonalUp:
		{
			RenderPtr->SetTexture("Normal_DiagonalUp_001.png");
			RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
		}
			break;
		case AttackDirection::Left_Front:
		{
			RenderPtr->SetTexture("Normal_Straight_001.png");
			RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
		}
			break;
		case AttackDirection::Left_DiagonalDown:
		{
			RenderPtr->SetTexture("Normal_DiagonalDown_001.png");
			RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
		}
			break;
		case AttackDirection::Left_Down:
		{
			RenderPtr->SetTexture("Normal_Down_001.png");
			RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
		}
			break;
		default:
			break;
		}
	}
	else
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}
void Player::HoldingEnd()
{
	IsHold = false;

	if (true == Directbool)
	{
		ADValue = AttackDirection::Right_Front;
	}
	else
	{
		ADValue = AttackDirection::Left_Front;
	}
}

void Player::HoldingAttackStart()
{

}
void Player::HoldingAttackUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("Hold"))
	{
		IsHold = true;

		if (true == GameEngineInput::IsDown("Dash"))
		{
			ChangeState(PlayerState::Dash);
			return;
		}

		if (true == GameEngineInput::IsDown("Jump"))
		{
			ChangeState(PlayerState::Jump);
			return;
		}

		if (false == GameEngineInput::IsPress("Hold"))
		{
			ChangeState(PlayerState::Attack);
			return;
		}

		if (false == GameEngineInput::IsPress("Attack"))
		{
			ChangeState(PlayerState::Holding);
			return;
		}

		switch (ADValue)
		{
		case AttackDirection::Right_Up:
		{
			RenderPtr->SetTexture("Shoot_Up_001.png");
			RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
		}
		break;
		case AttackDirection::Right_DiagonalUp:
		{
			RenderPtr->SetTexture("Shoot_DiagonalUp_003.png");
			RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
		}
		break;
		case AttackDirection::Right_Front:
		{
			RenderPtr->SetTexture("Shoot_Straight_001.png");
			RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
		}
		break;
		case AttackDirection::Right_DiagonalDown:
		{
			RenderPtr->SetTexture("Shoot_DiagonalDown_001.png");
			RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
		}
		break;
		case AttackDirection::Right_Down:
		{
			RenderPtr->SetTexture("Shoot_Down_001.png");
			RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
		}
		break;
		case AttackDirection::Left_Up:
		{
			RenderPtr->SetTexture("Shoot_Up_001.png");
			RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
		}
		break;
		case AttackDirection::Left_DiagonalUp:
		{
			RenderPtr->SetTexture("Shoot_DiagonalUp_003.png");
			RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
		}
		break;
		case AttackDirection::Left_Front:
		{
			RenderPtr->SetTexture("Shoot_Straight_001.png");
			RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
		}
		break;
		case AttackDirection::Left_DiagonalDown:
		{
			RenderPtr->SetTexture("Shoot_DiagonalDown_001.png");
			RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
		}
		break;
		case AttackDirection::Left_Down:
		{
			RenderPtr->SetTexture("Shoot_Down_001.png");
			RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
		}
		break;
		default:
			break;
		}
	}
	else
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}
void Player::HoldingAttackEnd()
{
	IsHold = false;

	if (true == Directbool)
	{
		ADValue = AttackDirection::Right_Front;
	}
	else
	{
		ADValue = AttackDirection::Left_Front;
	}
}
#include "PrecompileHeader.h"
#include "Player.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

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
	case PlayerState::Hit:
		HitStart();
		break;
	case PlayerState::Portal:
		PortalStart();
		break;
	case PlayerState::Death:
		DeathStart();
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
	case PlayerState::Hit:
		HitEnd();
		break;
	case PlayerState::Portal:
		PortalEnd();
		break;
	case PlayerState::Death:
		DeathEnd();
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
	case PlayerState::Hit:
		HitUpdate(_DeltaTime);
		break;
	case PlayerState::Portal:
		PortalUpdate(_DeltaTime);
		break;
	case PlayerState::Death:
		DeathUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

// 낙하 상태 체크
void Player::FallStart()
{
	RenderPtr->ChangeAnimation("Jump");
	RenderPtr->GetTransform()->SetLocalScale({ 170, 220, 1 });

	IsJump = true;
}
void Player::FallUpdate(float _DeltaTime)
{
	if (true == IsHit)
	{
		ChangeState(PlayerState::Hit);
		return;
	}
	
	if (true == GameEngineInput::IsDown("EX") && true == AirEXAttackAble && 0 < PlayerEXStack)
	{
		ChangeState(PlayerState::EXAttack);
		return;
	}

	if (true == GameEngineInput::IsDown("Dash") && true == AirDash) // AirDash true는 PixelCheck에서 진행
	{
		AirDash = false;
		ChangeState(PlayerState::Dash);
		return;
	}

	// 방향키 안누르면 Front로 고정
	if (true == Directbool)
	{
		if (false == GameEngineInput::IsPress("MoveUp") && false == GameEngineInput::IsPress("MoveDown"))
		{
			ADValue = AttackDirection::Right_Front;
		}
	}
	else
	{
		if (false == GameEngineInput::IsPress("MoveUp") && false == GameEngineInput::IsPress("MoveDown"))
		{
			ADValue = AttackDirection::Left_Front;
		}
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
		MoveDirect.y += -3300.0f * _DeltaTime;
		GetTransform()->AddLocalPosition(MoveDirect * _DeltaTime);
	}
	else if (false == IsFall)
	{
		MoveDirect.y = 0;
	}

	if (false == IsFall && true == GameEngineInput::IsPress("MoveRight") && true == GameEngineInput::IsPress("Attack")
		|| false == IsFall && true == GameEngineInput::IsPress("MoveLeft") && true == GameEngineInput::IsPress("Attack"))
	{
		ChangeState(PlayerState::RunAttack);
		return;
	}

	if (false == IsFall && true == GameEngineInput::IsPress("MoveRight")
		|| false == IsFall && true == GameEngineInput::IsPress("MoveLeft"))
	{
		ChangeState(PlayerState::Move);
		return;
	}

	if (false == IsFall)
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	if (true == GameEngineInput::IsDown("Jump"))
	{
		IsSlap = true;
		ChangeState(PlayerState::Slap);
		return;
	}
}
void Player::FallEnd()
{
	if (false == IsSlap)
	{
		MoveDirect = float4::Zero;
	}
	// IsFall의 false는 PixelCheck에서 실시
}

// Idle 상태 체크
void Player::IdleStart()
{
	AirEXAttackAble = true;
	RenderPtr->ChangeAnimation("Idle", false);
	RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
}
void Player::IdleUpdate(float _DeltaTime)
{
	if (true == IsHit)
	{
		ChangeState(PlayerState::Hit);
		return;
	}

	if (true == IsFall)
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	if (true == GameEngineInput::IsPress("MoveDown") && true == GameEngineInput::IsDown("Jump") && true == BottomJumpAble)
	{
		IsBottomJump = true;
		IsFall = true;
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

	if (true == GameEngineInput::IsDown("EX") && 0 < PlayerEXStack)
	{
		ChangeState(PlayerState::EXAttack);
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

	if (true == GameEngineInput::IsPress("MoveRight") || true == GameEngineInput::IsPress("MoveLeft"))
	{
		ChangeState(PlayerState::Move);
		return;
	}

	if (true == GameEngineInput::IsPress("MoveDown"))
	{
		ChangeState(PlayerState::DuckReady);
		return;
	}

	if (1 == RenderPtr->GetCurrentFrame())
	{
		int a = 0;
	}
}
void Player::IdleEnd()
{
}

// Move(Run) 상태 체크
void Player::MoveStart()
{
	AirEXAttackAble = true;
	RenderPtr->ChangeAnimation("Move");
	RenderPtr->GetTransform()->SetLocalScale({ 170, 200, 1 });
}
void Player::MoveUpdate(float _DeltaTime)
{
	MoveTime += _DeltaTime;

	if (true == IsHit)
	{
		ChangeState(PlayerState::Hit);
		return;
	}

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
		else if (true == GameEngineInput::IsPress("MoveLeft"))
		{
			GetTransform()->AddLocalPosition({ -MoveDis, 0 });
		}
	}

	if (true == GameEngineInput::IsDown("EX") && 0 < PlayerEXStack)
	{
		ChangeState(PlayerState::EXAttack);
		return;
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
	MoveTime = 0.0f;
}

// Dash(Shift 입력) 상태 체크
void Player::DashStart()
{
	if (true == IsFall)
	{
		RenderPtr->ChangeAnimation("AirDash");
		RenderPtr->GetTransform()->SetLocalScale({ 350, 200, 1 });
	}
	else
	{
		RenderPtr->ChangeAnimation("Dash");
		RenderPtr->GetTransform()->SetLocalScale({ 350, 200, 1 });
	}

	if (true == Directbool)
	{
		RenderPtr->GetTransform()->AddLocalPosition({ -70, 0 });
	}
	else
	{
		RenderPtr->GetTransform()->AddLocalPosition({ -60, 0 });
	}

	IsDash = true;
	CreateDashDust();
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
		RenderPtr->GetTransform()->AddLocalPosition({ 70, 0 });
	}
	else
	{
		RenderPtr->GetTransform()->AddLocalPosition({ 60, 0 });
	}

	DashTime = 0.0f;
	IsDash = false;
}

// Another -> Duck 전환 사이 상태 체크
void Player::DuckReadyStart()
{
	RenderPtr->ChangeAnimation("DuckReady");
	RenderPtr->GetTransform()->SetLocalScale({ 220, 220, 1 });

	if (true == Directbool)
	{
		ADValue = AttackDirection::Right_Front;
	}
	else
	{
		ADValue = AttackDirection::Left_Front;
	}
}
void Player::DuckReadyUpdate(float _DeltaTime)
{
	if (true == IsHit)
	{
		ChangeState(PlayerState::Hit);
		return;
	}

	if (true == GameEngineInput::IsDown("EX") && 0 < PlayerEXStack)
	{
		ChangeState(PlayerState::EXAttack);
		return;
	}

	if (true == Directbool)
	{
		ADValue = AttackDirection::Right_Front;
	}
	else
	{
		ADValue = AttackDirection::Left_Front;
	}

	if (true == IsFall)
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	if (true == GameEngineInput::IsPress("MoveDown") && true == GameEngineInput::IsDown("Jump") && true == BottomJumpAble)
	{
		IsBottomJump = true;
		IsFall = true;
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

// Duck(Crounch) 상태 체크
void Player::DuckStart()
{
	IsDuck = true;

	RenderPtr->ChangeAnimation("Duck");
	RenderPtr->GetTransform()->SetLocalScale({ 220, 220, 1 });

	if (true == Directbool)
	{
		ADValue = AttackDirection::Right_Front;
	}
	else
	{
		ADValue = AttackDirection::Left_Front;
	}
}
void Player::DuckUpdate(float _DeltaTime)
{
	if (true == IsHit)
	{
		ChangeState(PlayerState::Hit);
		return;
	}

	if (true == GameEngineInput::IsDown("EX") && 0 < PlayerEXStack)
	{
		ChangeState(PlayerState::EXAttack);
		return;
	}

	if (true == Directbool)
	{
		ADValue = AttackDirection::Right_Front;
	}
	else
	{
		ADValue = AttackDirection::Left_Front;
	}

	if (true == IsFall)
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	if (true == GameEngineInput::IsPress("MoveDown") && true == GameEngineInput::IsDown("Jump") && true == BottomJumpAble)
	{
		IsBottomJump = true;
		IsFall = true;
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
	IsDuck = false;
}

// Jump 상태 체크
void Player::JumpStart()
{
	RenderPtr->ChangeAnimation("Jump");
	RenderPtr->GetTransform()->SetLocalScale({ 170, 220, 1 });

	// 점프력
	if (false == IsJump && false == IsSlap)
	{
		MoveDirect.y = 850.0f;
		IsJump = true;
	}
}
void Player::JumpUpdate(float _DeltaTime)
{
	if (true == IsHit)
	{
		ChangeState(PlayerState::Hit);
		return;
	}

	if (true == GameEngineInput::IsDown("EX") && true == AirEXAttackAble && 0 < PlayerEXStack)
	{
		ChangeState(PlayerState::EXAttack);
		return;
	}

	if (true == GameEngineInput::IsDown("Dash") && true == AirDash)  // AirDash true는 PixelCheck에서 진행
	{
		AirDash = false;
		ChangeState(PlayerState::Dash);
		return;
	}

	// 방향키 안누르면 Front로 고정
	if (true == Directbool)
	{
		if (false == GameEngineInput::IsPress("MoveUp") && false == GameEngineInput::IsPress("MoveDown"))
		{
			ADValue = AttackDirection::Right_Front;
		}
	}
	else
	{
		if (false == GameEngineInput::IsPress("MoveUp") && false == GameEngineInput::IsPress("MoveDown"))
		{
			ADValue = AttackDirection::Left_Front;
		}
	}

	if (true == GameEngineInput::IsDown("Jump"))
	{
		IsSlap = true;
		ChangeState(PlayerState::Slap);
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
	if (true == GameEngineInput::IsPress("Jump") && 0.2f >= JumpTime)
	{
		MoveDirect.y += 2450.0f * _DeltaTime;
	}

	if (true == IsJump)
	{
		MoveDirect.y += -3300.0f * _DeltaTime;
		GetTransform()->AddLocalPosition(MoveDirect * _DeltaTime);
	}
	else if (false == IsJump)
	{
		MoveDirect.y = 0;
	}

	if (false == IsJump && true == GameEngineInput::IsPress("MoveRight") && true == GameEngineInput::IsPress("Attack")
		|| false == IsJump && true == GameEngineInput::IsPress("MoveLeft") && true == GameEngineInput::IsPress("Attack"))
	{
		ChangeState(PlayerState::RunAttack);
		return;
	}

	if (false == IsJump && true == GameEngineInput::IsPress("MoveRight")
		|| false == IsJump && true == GameEngineInput::IsPress("MoveLeft"))
	{
		ChangeState(PlayerState::Move);
		return;
	}

	if (false == IsJump)
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}
void Player::JumpEnd()
{
	if (false == IsSlap)
	{
		MoveDirect = float4::Zero;
		JumpTime = 0.0f;
	}
	// IsJump의 false는 PixelCheck에서 실시
}

// Parry(Slap) 상태 체크
void Player::SlapStart()
{
	RenderPtr->ChangeAnimation("Parry");
	RenderPtr->GetTransform()->SetLocalScale({ 170, 220, 1 });

	ParryCollisionPtr->On();
	ParryCollisionRenderPtr->On();
}
void Player::SlapUpdate(float _DeltaTime)
{
	if (true == IsHit)
	{
		ChangeState(PlayerState::Hit);
		return;
	}

	// 패리 성공 시
	if (true == ParryCheck)
	{
		IsSlap = false;
		IsJump = false;
		MoveDirect.y = 0;
		JumpTime = 0.0f;
		ChangeState(PlayerState::Jump);
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

	if (true == IsJump)
	{
		MoveDirect.y += -3000.0f * _DeltaTime;
		GetTransform()->AddLocalPosition(MoveDirect * _DeltaTime);
	}
	else if (false == IsJump)
	{
		MoveDirect.y = 0;
	}

	if (false == IsJump)
	{
		IsSlap = false;
		MoveDirect.y = 0;
		JumpTime = 0.0f;
		ChangeState(PlayerState::Idle);
		return;
	}

	if (true == RenderPtr->IsAnimationEnd())
	{
		IsSlap = false;
		ChangeState(PlayerState::Jump);
		return;
	}
}
void Player::SlapEnd()
{
	ParryCheck = false;
	ParryCollisionPtr->Off();
	ParryCollisionRenderPtr->Off();
}

// Idle에서 MoveUp 입력 시 상태 체크
void Player::AttackReadyStart()
{
	RenderPtr->ChangeAnimation("Hold_Normal_Up");
	RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
}
void Player::AttackReadyUpdate(float _DeltaTime)
{
	if (true == IsHit)
	{
		ChangeState(PlayerState::Hit);
		return;
	}

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

	if (true == GameEngineInput::IsDown("EX") && 0 < PlayerEXStack)
	{
		ChangeState(PlayerState::EXAttack);
		return;
	}

	if (true == GameEngineInput::IsPress("Attack"))
	{
		IsAttackReady = true;
		ChangeState(PlayerState::Attack);
		return;
	}
}
void Player::AttackReadyEnd()
{

}

// Idle에서 Attack 입력 시 상태 체크
void Player::AttackStart()
{
	RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });

	if (false == IsAttackReady)
	{
		if (true == Directbool)
		{
			ADValue = AttackDirection::Right_Front;
		}
		else
		{
			ADValue = AttackDirection::Left_Front;
		}
	}

	IsAttackReady = false;
}
void Player::AttackUpdate(float _DeltaTime)
{
	if (true == IsHit)
	{
		ChangeState(PlayerState::Hit);
		return;
	}

	if (true == IsFall)
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	if (true == GameEngineInput::IsDown("EX") && 0 < PlayerEXStack)
	{
		ChangeState(PlayerState::EXAttack);
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
		RenderPtr->ChangeAnimation("Hold_Shoot_Up", false);
	}
	break;
	case AttackDirection::Right_Front:
	{
		RenderPtr->ChangeAnimation("Hold_Shoot_Straight", false);
	}
	break;
	case AttackDirection::Left_Up:
	{
		RenderPtr->ChangeAnimation("Hold_Shoot_Up", false);
	}
	break;
	case AttackDirection::Left_Front:
	{
		RenderPtr->ChangeAnimation("Hold_Shoot_Straight", false);
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

// Move(Run)에서 Attack 입력 시 상태 체크
void Player::RunAttackStart()
{
	AirEXAttackAble = true;
	RenderPtr->GetTransform()->SetLocalScale({ 170, 200, 1 });
}
void Player::RunAttackUpdate(float _DeltaTime)
{
	MoveTime += _DeltaTime;

	if (true == IsHit)
	{
		ChangeState(PlayerState::Hit);
		return;
	}

	if (true == IsFall)
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	if (true == GameEngineInput::IsDown("EX") && 0 < PlayerEXStack)
	{
		ChangeState(PlayerState::EXAttack);
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
	else if (true == GameEngineInput::IsPress("MoveLeft"))
	{
		GetTransform()->AddLocalPosition({ -MoveDis, 0 });
	}

	switch (ADValue)
	{
	case AttackDirection::Right_DiagonalUp:
	{
		RenderPtr->ChangeAnimation("Move_Attak_DiagonalUp", false);
	}
	break;
	case AttackDirection::Right_Front:
	{
		RenderPtr->ChangeAnimation("Move_Attak_Straight", false);
	}
	break;
	case AttackDirection::Left_DiagonalUp:
	{
		RenderPtr->ChangeAnimation("Move_Attak_DiagonalUp", false);
	}
	break;
	case AttackDirection::Left_Front:
	{
		RenderPtr->ChangeAnimation("Move_Attak_Straight", false);
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
	MoveTime = 0.0f;
}

// Duck에서 Attack 입력 시 상태 체크
void Player::DuckAttackStart()
{
	IsDuck = true;
	IsDuckAttack = true;

	RenderPtr->ChangeAnimation("DuckAttack");
	RenderPtr->GetTransform()->SetLocalScale({ 220, 220, 1 });
}
void Player::DuckAttackUpdate(float _DeltaTime)
{
	if (true == IsHit)
	{
		ChangeState(PlayerState::Hit);
		return;
	}

	if (true == GameEngineInput::IsDown("EX") && 0 < PlayerEXStack)
	{
		ChangeState(PlayerState::EXAttack);
		return;
	}

	if (true == IsFall)
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	if (true == GameEngineInput::IsPress("MoveDown") && true == GameEngineInput::IsDown("Jump") && true == BottomJumpAble)
	{
		IsBottomJump = true;
		IsFall = true;
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
	IsDuck = false;
}

// EX Attack 상태 체크
void Player::EXAttackStart()
{
	--PlayerEXStack;

	if (0 > PlayerEXStack)
	{
		MsgAssert("EX 몬가 잘못됨");
		return;
	}

	IsEXAttack = true;
	AirEXAttackAble = false;
	ChargeUpRenderPtr->ChangeAnimation("EX_ChargeUp", true);
	ChargeUpRenderPtr->On();
	ChargeUpRenderPtr->GetTransform()->SetLocalPosition(float4{ -10, 80 });
}
void Player::EXAttackUpdate(float _DeltaTime)
{
	switch (ADValue)
	{
	case AttackDirection::Right_Up:
	{
		if (true == IsJump || true == IsFall)
		{
			RenderPtr->ChangeAnimation("AirEx_Up", false);

		}
		else
		{
			RenderPtr->ChangeAnimation("Ex_Up", false);
		}

		PushBackAble = false;
	}
	break;
	case AttackDirection::Right_DiagonalUp:
	{
		if (true == IsJump || true == IsFall)
		{
			RenderPtr->ChangeAnimation("AirEx_DiagonalUp", false);
		}
		else
		{
			RenderPtr->ChangeAnimation("Ex_DiagonalUp", false);
		}

		PushBackAble = true;
	}
	break;
	case AttackDirection::Right_Front:
	{
		if (true == IsJump || true == IsFall)
		{
			RenderPtr->ChangeAnimation("AirEx_Straight", false);
		}
		else
		{
			RenderPtr->ChangeAnimation("Ex_Straight", false);
		}

		PushBackAble = true;
	}
	break;
	case AttackDirection::Right_DiagonalDown:
	{
		if (true == IsJump || true == IsFall)
		{
			RenderPtr->ChangeAnimation("AirEx_DiagonalDown", false);
		}
		else
		{
			RenderPtr->ChangeAnimation("Ex_DiagonalDown", false);
		}

		PushBackAble = true;
	}
	break;
	case AttackDirection::Right_Down:
	{
		if (true == IsJump || true == IsFall)
		{
			RenderPtr->ChangeAnimation("AirEx_Down", false);
		}
		else
		{
			RenderPtr->ChangeAnimation("Ex_Down", false);
		}

		PushBackAble = false;
	}
	break;
	case AttackDirection::Left_Up:
	{
		if (true == IsJump || true == IsFall)
		{
			RenderPtr->ChangeAnimation("AirEx_Up", false);
		}
		else
		{
			RenderPtr->ChangeAnimation("Ex_Up", false);
		}

		PushBackAble = false;
	}
	break;
	case AttackDirection::Left_DiagonalUp:
	{
		if (true == IsJump || true == IsFall)
		{
			RenderPtr->ChangeAnimation("AirEx_DiagonalUp", false);
		}
		else
		{
			RenderPtr->ChangeAnimation("Ex_DiagonalUp", false);
		}

		PushBackAble = true;
	}
	break;
	case AttackDirection::Left_Front:
	{
		if (true == IsJump || true == IsFall)
		{
			RenderPtr->ChangeAnimation("AirEx_Straight", false);
		}
		else
		{
			RenderPtr->ChangeAnimation("Ex_Straight", false);
		}

		PushBackAble = true;
	}
	break;
	case AttackDirection::Left_DiagonalDown:
	{
		if (true == IsJump || true == IsFall)
		{
			RenderPtr->ChangeAnimation("AirEx_DiagonalDown", false);
		}
		else
		{
			RenderPtr->ChangeAnimation("Ex_DiagonalDown", false);
		}

		PushBackAble = true;
	}
	break;
	case AttackDirection::Left_Down:
	{
		if (true == IsJump || true == IsFall)
		{
			RenderPtr->ChangeAnimation("AirEx_Down", false);
		}
		else
		{
			RenderPtr->ChangeAnimation("Ex_Down", false);
		}

		PushBackAble = false;
	}
	break;
	default:
		break;
	}

	if (true == ChargeUpRenderPtr->IsAnimationEnd())
	{
		ChargeUpRenderPtr->Off();
	}

	if (7 == RenderPtr->GetCurrentFrame() && 1 == CreateEXCount)
	{
		EXPushBack = true;
		CreateEXCount = 0;
		EXCreate();
	}

	if (true == EXPushBack && true == PushBackAble)
	{
		float MoveDis = (MoveSpeed / 3) * _DeltaTime;

		if (true == Directbool)
		{
			GetTransform()->AddLocalPosition({ -MoveDis, 0 });
		}
		else
		{
			GetTransform()->AddLocalPosition({ MoveDis, 0 });
		}
	}

	if (RenderPtr->IsAnimationEnd() && true == IsJump
		|| RenderPtr->IsAnimationEnd() && true == IsFall)
	{
		ChangeState(PlayerState::Fall);
		return;
	}
	else if (RenderPtr->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}
void Player::EXAttackEnd()
{
	EXPushBack = false;
	PushBackAble = false;
	IsEXAttack = false;
	CreateEXCount = 1;

	if (true == WeaponType)
	{
		PeashooterRenderPtr->ChangeAnimation("Peashooter_Spawn");
		PeashooterRenderPtr->On();
	}
	else
	{
		PeashooterRenderPtr->ChangeAnimation("Spread_Spawn");
		PeashooterRenderPtr->On();
	}
}

// Hold 입력 시 상태 체크
void Player::HoldingStart()
{
	RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
}
void Player::HoldingUpdate(float _DeltaTime)
{
	if (true == IsHit)
	{
		ChangeState(PlayerState::Hit);
		return;
	}

	if (true == GameEngineInput::IsPress("Hold"))
	{
		IsHold = true;

		if (true == GameEngineInput::IsDown("EX") && 0 < PlayerEXStack)
		{
			ChangeState(PlayerState::EXAttack);
			return;
		}

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
			RenderPtr->ChangeAnimation("Hold_Normal_Up", false);
		}
		break;
		case AttackDirection::Right_DiagonalUp:
		{
			RenderPtr->ChangeAnimation("Hold_Normal_DiagonalUp", false);
		}
		break;
		case AttackDirection::Right_Front:
		{
			RenderPtr->ChangeAnimation("Hold_Normal_Straight", false);
		}
		break;
		case AttackDirection::Right_DiagonalDown:
		{
			RenderPtr->ChangeAnimation("Hold_Normal_DiagonalDown", false);
		}
		break;
		case AttackDirection::Right_Down:
		{
			RenderPtr->ChangeAnimation("Hold_Normal_Down", false);
		}
		break;
		case AttackDirection::Left_Up:
		{
			RenderPtr->ChangeAnimation("Hold_Normal_Up", false);
		}
		break;
		case AttackDirection::Left_DiagonalUp:
		{
			RenderPtr->ChangeAnimation("Hold_Normal_DiagonalUp", false);
		}
		break;
		case AttackDirection::Left_Front:
		{
			RenderPtr->ChangeAnimation("Hold_Normal_Straight", false);
		}
		break;
		case AttackDirection::Left_DiagonalDown:
		{
			RenderPtr->ChangeAnimation("Hold_Normal_DiagonalDown", false);
		}
		break;
		case AttackDirection::Left_Down:
		{
			RenderPtr->ChangeAnimation("Hold_Normal_Down", false);
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
}

// Hold 이후 Attack 입력 시 상태 체크
void Player::HoldingAttackStart()
{
	RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
}
void Player::HoldingAttackUpdate(float _DeltaTime)
{
	if (true == IsHit)
	{
		ChangeState(PlayerState::Hit);
		return;
	}

	if (true == GameEngineInput::IsPress("Hold"))
	{
		IsHold = true;

		if (true == GameEngineInput::IsDown("EX") && 0 < PlayerEXStack)
		{
			ChangeState(PlayerState::EXAttack);
			return;
		}

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
			RenderPtr->ChangeAnimation("Hold_Shoot_Up", false);
		}
		break;
		case AttackDirection::Right_DiagonalUp:
		{
			RenderPtr->ChangeAnimation("Hold_Shoot_DiagonalUp", false);
		}
		break;
		case AttackDirection::Right_Front:
		{
			RenderPtr->ChangeAnimation("Hold_Shoot_Straight", false);
		}
		break;
		case AttackDirection::Right_DiagonalDown:
		{
			RenderPtr->ChangeAnimation("Hold_Shoot_DiagonalDown", false);
		}
		break;
		case AttackDirection::Right_Down:
		{
			RenderPtr->ChangeAnimation("Hold_Shoot_Down", false);
		}
		break;
		case AttackDirection::Left_Up:
		{
			RenderPtr->ChangeAnimation("Hold_Shoot_Up", false);
		}
		break;
		case AttackDirection::Left_DiagonalUp:
		{
			RenderPtr->ChangeAnimation("Hold_Shoot_DiagonalUp", false);
		}
		break;
		case AttackDirection::Left_Front:
		{
			RenderPtr->ChangeAnimation("Hold_Shoot_Straight", false);
		}
		break;
		case AttackDirection::Left_DiagonalDown:
		{
			RenderPtr->ChangeAnimation("Hold_Shoot_DiagonalDown", false);
		}
		break;
		case AttackDirection::Left_Down:
		{
			RenderPtr->ChangeAnimation("Hold_Shoot_Down", false);
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
}

void Player::HitStart()
{
	if (true == IsJump || true == IsFall)
	{
		RenderPtr->ChangeAnimation("AirHit");
	}
	else
	{
		RenderPtr->ChangeAnimation("Hit");
	}

	RenderPtr->GetTransform()->SetLocalScale({ 300, 330 });
}
void Player::HitUpdate(float _DeltaTime)
{
	if (0 == RenderPtr->GetCurrentFrame() || 5 == RenderPtr->GetCurrentFrame())
	{
		RenderPtr->GetTransform()->SetLocalPosition({ 0, 160 });
	}
	else if (1 == RenderPtr->GetCurrentFrame() || 4 == RenderPtr->GetCurrentFrame())
	{
		RenderPtr->GetTransform()->SetLocalPosition({ 0, 170 });
	}
	else if (2 == RenderPtr->GetCurrentFrame() || 3 == RenderPtr->GetCurrentFrame())
	{
		RenderPtr->GetTransform()->SetLocalPosition({ 0, 180 });
	}

	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}
void Player::HitEnd()
{
	IsHit = false;
}

void Player::PortalStart()
{
	RenderPtr->ChangeAnimation("Portal");
}
void Player::PortalUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}
void Player::PortalEnd()
{

}

void Player::DeathStart()
{

}
void Player::DeathUpdate(float _DeltaTime)
{

}
void Player::DeathEnd()
{

}
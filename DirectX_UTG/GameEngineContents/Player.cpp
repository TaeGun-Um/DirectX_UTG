#include "PrecompileHeader.h"
#include "Player.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

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
	SetMoveSpeed(330.0f);
	ChangeState(PlayerState::Idle);
}
void Player::Update(float _DeltaTime)
{
	DirectCheck();
	PlayerMove(_DeltaTime);
	UpdateState(_DeltaTime);
	PixelCheck();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                         FSM                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::DirectCheck()
{
	if (true == GameEngineInput::IsDown("MoveRight"))
	{
		Directbool = true;
		RenderPtr->GetTransform()->SetLocalPositiveScaleX();
	}
	else if (true == GameEngineInput::IsDown("MoveLeft"))
	{
		Directbool = false;
		RenderPtr->GetTransform()->SetLocalNegativeScaleX();
	}
}

void Player::ChangeState(PlayerState _StateValue)
{
	PlayerState NextState = _StateValue;
	PlayerState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case PlayerState::Idle:
		IdleStart();
		break;
	case PlayerState::Move:
		MoveStart();
		break;
	case PlayerState::Dash:
		DashStart();
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
	case PlayerState::Attack:
		AttackStart();
		break;
	case PlayerState::RunAttack:
		RunAttackStart();
		break;
	case PlayerState::EXAttack:
		EXAttackStart();
		break;
	case PlayerState::Holding:
		HoldingStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case PlayerState::Idle:
		IdleEnd();
		break;
	case PlayerState::Move:
		MoveEnd();
		break;
	case PlayerState::Dash:
		DashEnd();
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
	case PlayerState::Attack:
		AttackEnd();
		break;
	case PlayerState::RunAttack:
		RunAttackEnd();
		break;
	case PlayerState::EXAttack:
		EXAttackEnd();
		break;
	case PlayerState::Holding:
		HoldingEnd();
		break;
	default:
		break;
	}
}

void Player::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case PlayerState::Idle:
		IdleUpdate();
		break;
	case PlayerState::Move:
		MoveUpdate();
		break;
	case PlayerState::Dash:
		DashUpdate();
		break;
	case PlayerState::Duck:
		DuckUpdate();
		break;
	case PlayerState::Jump:
		JumpUpdate();
		break;
	case PlayerState::Slap:
		SlapUpdate();
		break;
	case PlayerState::Attack:
		AttackUpdate();
		break;
	case PlayerState::RunAttack:
		RunAttackUpdate();
		break;
	case PlayerState::EXAttack:
		EXAttackUpdate();
		break;
	case PlayerState::Holding:
		HoldingUpdate();
		break;
	default:
		break;
	}
}

void Player::IdleStart()
{
}
void Player::IdleUpdate()
{
}
void Player::IdleEnd()
{
}

void Player::MoveStart()
{
}
void Player::MoveUpdate()
{
}
void Player::MoveEnd()
{
}

void Player::DashStart()
{
}
void Player::DashUpdate()
{
}
void Player::DashEnd()
{
}

void Player::DuckStart()
{
}
void Player::DuckUpdate()
{
}
void Player::DuckEnd()
{
}
	 
void Player::JumpStart()
{
}
void Player::JumpUpdate()
{
}
void Player::JumpEnd()
{
}

void Player::SlapStart()
{
}
void Player::SlapUpdate()
{
}
void Player::SlapEnd()
{
}

void Player::AttackStart()
{
}
void Player::AttackUpdate()
{
}
void Player::AttackEnd()
{
}

void Player::RunAttackStart()
{
}
void Player::RunAttackUpdate()
{
}
void Player::RunAttackEnd()
{
}
	
void Player::EXAttackStart()
{
}
void Player::EXAttackUpdate()
{
}
void Player::EXAttackEnd()
{
}

void Player::HoldingStart()
{
}
void Player::HoldingUpdate()
{
}
void Player::HoldingEnd()
{
}
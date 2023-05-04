#include "PrecompileHeader.h"
#include "Player.h"

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
}
void Player::Update(float _DeltaTime)
{
	PlayerMove(_DeltaTime);

	PixelCheck();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                         FSM                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// state
// 

void Player::IdleStart()
{}
void Player::IdleUpdate()
{}
void Player::IdleEnd()
{}

void Player::MoveStart()
{}
void Player::MoveUpdate()
{}
void Player::MoveEnd()
{}

void Player::DashStart()
{}
void Player::DashUpdate()
{}
void Player::DashEnd()
{}

void Player::DuckStart()
{}
void Player::DuckUpdate()
{}
void Player::DuckEnd()
{}
	 
void Player::JumpStart()
{}
void Player::JumpUpdate()
{}
void Player::JumpEnd()
{}

void Player::SlapStart()
{}
void Player::SlapUpdate()
{}
void Player::SlapEnd()
{}

void Player::AttackStart()
{}
void Player::AttackUpdate()
{}
void Player::AttackEnd()
{}

void Player::RunAttackStart()
{}
void Player::RunAttackUpdate()
{}
void Player::RunAttackEnd()
{}
	
void Player::EXAttackStart()
{}
void Player::EXAttackUpdate()
{}
void Player::EXAttackEnd()
{}

void Player::HoldingStart()
{}
void Player::HoldingUpdate()
{}
void Player::HoldingEnd()
{}
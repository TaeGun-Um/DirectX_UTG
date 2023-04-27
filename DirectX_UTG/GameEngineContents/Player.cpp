#include "PrecompileHeader.h"
#include "Player.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Player::Player() 
{
}

Player::~Player() 
{
}

void Player::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetTexture("Ground_Idle_001.png");
	RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
}
void Player::Update(float _DeltaTime)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                         FSM                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::IdleStart() {}
void Player::IdleUpdate() {}
void Player::IdleEnd() {}

void Player::MoveStart() {}
void Player::MoveUpdate() {}
void Player::MoveEnd() {}

void Player::DashStart() {}
void Player::DashUpdate() {}
void Player::DashEnd() {}

void Player::DuckStart() {}
void Player::DuckUpdate() {}
void Player::DuckEnd() {}
	 
void Player::JumpStart() {}
void Player::JumpUpdate() {}
void Player::JumpEnd() {}

void Player::SlapStart() {}
void Player::SlapUpdate() {}
void Player::SlapEnd() {}

void Player::AttackStart() {}
void Player::AttackUpdate() {}
void Player::AttackEnd() {}

void Player::RunAttackStart() {}
void Player::RunAttackUpdate() {}
void Player::RunAttackEnd() {}
	
void Player::EXAttackStart() {}
void Player::EXAttackUpdate() {}
void Player::EXAttackEnd() {}

void Player::HoldingStart() {}
void Player::HoldingUpdate() {}
void Player::HoldingEnd() {}
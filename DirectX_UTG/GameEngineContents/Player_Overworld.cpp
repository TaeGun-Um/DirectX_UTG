#include "PrecompileHeader.h"
#include "Player_Overworld.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Player_Overworld::Player_Overworld() 
{
}

Player_Overworld::~Player_Overworld() 
{
}

void Player_Overworld::Start()
{
	/*RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetTexture("Ground_Idle_001.png");
	RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });*/

	RenderPtr = AnimationCreate_Overworld();
	SetCameraFollowType(CameraFollowType::Overworld);
	SetMoveSpeed(230.0f);
}
void Player_Overworld::Update(float _DeltaTime)
{
	PlayerMove_Overworld(_DeltaTime);

	// colmap
	std::shared_ptr<GameEngineTexture> Ptr = GameEngineTexture::Find("Overworld_ColMap.png");

	GameEnginePixelColor Pixel = Ptr->GetPixel(910, 467);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                         FSM                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player_Overworld::IdleStart() {}
void Player_Overworld::IdleUpdate() {}
void Player_Overworld::IdleEnd() {}

void Player_Overworld::MoveStart() {}
void Player_Overworld::MoveUpdate() {}
void Player_Overworld::MoveEnd() {}

void Player_Overworld::DashStart() {}
void Player_Overworld::DashUpdate() {}
void Player_Overworld::DashEnd() {}

void Player_Overworld::DuckStart() {}
void Player_Overworld::DuckUpdate() {}
void Player_Overworld::DuckEnd() {}

void Player_Overworld::JumpStart() {}
void Player_Overworld::JumpUpdate() {}
void Player_Overworld::JumpEnd() {}

void Player_Overworld::SlapStart() {}
void Player_Overworld::SlapUpdate() {}
void Player_Overworld::SlapEnd() {}

void Player_Overworld::AttackStart() {}
void Player_Overworld::AttackUpdate() {}
void Player_Overworld::AttackEnd() {}

void Player_Overworld::RunAttackStart() {}
void Player_Overworld::RunAttackUpdate() {}
void Player_Overworld::RunAttackEnd() {}

void Player_Overworld::EXAttackStart() {}
void Player_Overworld::EXAttackUpdate() {}
void Player_Overworld::EXAttackEnd() {}

void Player_Overworld::HoldingStart() {}
void Player_Overworld::HoldingUpdate() {}
void Player_Overworld::HoldingEnd() {}
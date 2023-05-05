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
void Player_Overworld::IdleUpdate(float _DeltaTime) {}
void Player_Overworld::IdleEnd() {}

void Player_Overworld::MoveStart() {}
void Player_Overworld::MoveUpdate(float _DeltaTime) {}
void Player_Overworld::MoveEnd() {}

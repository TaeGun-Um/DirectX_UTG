#include "PrecompileHeader.h"
#include "Player_Overworld.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Player_Overworld::Player_Overworld() 
{
}

Player_Overworld::~Player_Overworld() 
{
}

void Player_Overworld::Start()
{
	RenderPtr = AnimationCreate_Overworld();
	SetCameraFollowType(CameraFollowType::Overworld);
	SetPlayerMoveSpeed(230.0f);
}
void Player_Overworld::Update(float _DeltaTime)
{
	PlayerMove_Overworld(_DeltaTime);
	MoveCamera(_DeltaTime);

	// colmap
	std::shared_ptr<GameEngineTexture> Ptr = GameEngineTexture::Find("Overworld_ColMap.png");

	GameEnginePixelColor Pixel = Ptr->GetPixel(910, 467);
}

void Player_Overworld::PlayerMove_Overworld(float _DeltaTime)
{


	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     AssistFunction                       //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                         FSM                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player_Overworld::IdleStart() {}
void Player_Overworld::IdleUpdate(float _DeltaTime) {}
void Player_Overworld::IdleEnd() {}

void Player_Overworld::MoveStart() {}
void Player_Overworld::MoveUpdate(float _DeltaTime) 
{
	float MoveDis = MoveSpeed * _DeltaTime;

	if (true == GameEngineInput::IsPress("MoveUp"))
	{
		GetTransform()->AddLocalPosition({ 0, MoveDis });
	}
	if (true == GameEngineInput::IsPress("MoveDown"))
	{
		GetTransform()->AddLocalPosition({ 0, -MoveDis });
	}
	if (true == GameEngineInput::IsPress("MoveRight"))
	{
		GetTransform()->AddLocalPosition({ MoveDis, 0 });
	}
	if (true == GameEngineInput::IsPress("MoveLeft"))
	{
		GetTransform()->AddLocalPosition({ -MoveDis, 0 });
	}
}
void Player_Overworld::MoveEnd() {}

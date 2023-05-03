#include "PrecompileHeader.h"
#include "PlayerDataBase.h"

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

PlayerDataBase::PlayerDataBase() 
{
	if (false == GameEngineInput::IsKey("MoveUp"))
	{
		GameEngineInput::CreateKey("MoveUp", VK_UP);
		GameEngineInput::CreateKey("MoveDown", VK_DOWN);
		GameEngineInput::CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::CreateKey("Attack", 'Z');
		GameEngineInput::CreateKey("Jump", 'X');
		GameEngineInput::CreateKey("Hold", 'C');
		GameEngineInput::CreateKey("Dash", VK_SHIFT);
	}
}

PlayerDataBase::~PlayerDataBase() 
{
}

void PlayerDataBase::SetCameraFollowType(CameraFollowType _Type)
{
	CameraType = _Type;
}

void PlayerDataBase::MoveCamera(float _DeltaTime)
{
	switch (CameraType)
	{
	case PlayerDataBase::CameraFollowType::Normal:
	{
		float PlayerPosX = GetTransform()->GetWorldPosition().x;
		float PlayerPosY = GetTransform()->GetWorldPosition().y;
		float CameraPosZ = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition().z;
		
		float4 CameraPos = { PlayerPosX, PlayerPosY, CameraPosZ };

		GetLevel()->GetMainCamera()->GetTransform()->SetWorldPosition(CameraPos);
	}
		break;
	case PlayerDataBase::CameraFollowType::Field:
	{
		TargetPosition = GetTransform()->GetWorldPosition();

		float CameraPosX = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition().x;
		float CameraPosY = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition().y;

		PrevCameraPosition = { CameraPosX, CameraPosY };

		float4 Movedir = (TargetPosition - PrevCameraPosition);

		MoveDistance = Movedir * 2.0f * _DeltaTime;
		MoveDistance.y = 0.0f;

		GetLevel()->GetMainCamera()->GetTransform()->AddWorldPosition(MoveDistance);
	}
		break;
	case PlayerDataBase::CameraFollowType::Overworld:
	{
		TargetPosition = GetTransform()->GetWorldPosition();

		float CameraPosX = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition().x;
		float CameraPosY = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition().y;

		PrevCameraPosition = { CameraPosX, CameraPosY };

		float4 Movedir = (TargetPosition - PrevCameraPosition);

		MoveDistance = Movedir * 4.5f * _DeltaTime;

		GetLevel()->GetMainCamera()->GetTransform()->AddWorldPosition(MoveDistance);
	}
		break;
	case PlayerDataBase::CameraFollowType::None:
	{
		MsgAssert("필드에서 따라오는 카메라 형식을 설정해주지 않았습니다.");
		return;
	}
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     ANIMATION                       ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<GameEngineSpriteRenderer> PlayerDataBase::AnimationCreate_Tutorial()
{
	std::shared_ptr<GameEngineSpriteRenderer> RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetTexture("Ground_Idle_001.png");
	RenderPtr->GetTransform()->SetLocalScale({ 140, 187, 1 });
	RenderPtr->GetTransform()->SetLocalPosition({ 0, 0, 5 });

	return RenderPtr;
}

std::shared_ptr<GameEngineSpriteRenderer> PlayerDataBase::AnimationCreate_Field()
{
	std::shared_ptr<GameEngineSpriteRenderer> RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetTexture("Ground_Idle_001.png");
	RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
	RenderPtr->GetTransform()->SetLocalPosition({ 0, 0, 5 });

	return RenderPtr;
}

std::shared_ptr<GameEngineSpriteRenderer> PlayerDataBase::AnimationCreate_Overworld()
{
	std::shared_ptr<GameEngineSpriteRenderer> RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetTexture("Idle.png");
	RenderPtr->GetTransform()->SetLocalScale({ 49, 96, 1 });
	RenderPtr->GetTransform()->SetLocalPosition({ 0, 0, 5 });

	return RenderPtr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                        MOVE                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float4 Gravity = float4::Zero; // 지워라
bool IsGravity = true;

void PlayerDataBase::PlayerMove(float _DeltaTime)
{
	// 임시 중력
	{
		if (true == IsGravity)
		{
			Gravity.y += -100.0f * _DeltaTime;
			GetTransform()->AddLocalPosition(Gravity * _DeltaTime);
		}
	}

	if (true == GameEngineInput::IsPress("MoveRight"))
	{
		GetTransform()->AddLocalPosition({ MoveSpeed * _DeltaTime, 0 });
	}
	if (true == GameEngineInput::IsPress("MoveLeft"))
	{
		GetTransform()->AddLocalPosition({ -MoveSpeed * _DeltaTime, 0 });
	}

	if (true == GameEngineInput::IsDown("Jump") && false == IsJump)
	{
		GetTransform()->AddLocalPosition({ 0, 300.0f });
		IsJump = true;
		IsGravity = true;
	}

	MoveCamera(_DeltaTime);
}

void PlayerDataBase::PlayerMove_Overworld(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("MoveUp"))
	{
		GetTransform()->AddLocalPosition({ 0, MoveSpeed * _DeltaTime });
	}
	if (true == GameEngineInput::IsPress("MoveDown"))
	{
		GetTransform()->AddLocalPosition({ 0, -MoveSpeed * _DeltaTime });
	}
	if (true == GameEngineInput::IsPress("MoveRight"))
	{
		GetTransform()->AddLocalPosition({ MoveSpeed * _DeltaTime, 0 });
	}
	if (true == GameEngineInput::IsPress("MoveLeft"))
	{
		GetTransform()->AddLocalPosition({ -MoveSpeed * _DeltaTime, 0 });
	}

	MoveCamera(_DeltaTime);
}

void PlayerDataBase::PixelCheck()
{
	// colmap
	std::shared_ptr<GameEngineTexture> ColMap = GameEngineTexture::Find("TestLevel_Map.png");

	float PosfX = GetTransform()->GetLocalPosition().x;
	float PosFY = GetTransform()->GetLocalPosition().y;

	int PlayerPosX = static_cast<int>(PosfX);
	int PlayerPosY = static_cast<int>(PosFY);

	GameEnginePixelColor Default(static_cast<char>(10), static_cast<char>(10), static_cast<char>(10), static_cast<char>(255));
	GameEnginePixelColor ColBlack(static_cast<char>(0), static_cast<char>(0), static_cast<char>(0), static_cast<char>(255));

	// 240, -450
	// 

	GameEnginePixelColor ColMapPixel = ColMap->GetPixel(PlayerPosX, -PlayerPosY, Default);

	if (ColBlack == ColMapPixel)
	{
		IsGravity = false;
		IsJump = false;

		while (true)
		{
			GetTransform()->AddLocalPosition({ 0, 1 });

			PosfX = GetTransform()->GetLocalPosition().x;
			PosFY = GetTransform()->GetLocalPosition().y;

			PlayerPosX = static_cast<int>(PosfX);
			PlayerPosY = static_cast<int>(PosFY);

			GameEnginePixelColor GravityPixel = ColMap->GetPixel(PlayerPosX, -PlayerPosY, Default);

			if (ColBlack != GravityPixel)
			{
				break;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                         FSM                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
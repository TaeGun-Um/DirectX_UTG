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
		GameEngineInput::CreateKey("EX", 'V');
		GameEngineInput::CreateKey("Dash", VK_SHIFT);
		GameEngineInput::CreateKey("WeaponSwap", VK_TAB);
	}
}

PlayerDataBase::~PlayerDataBase() 
{
}

void PlayerDataBase::SetCameraFollowType(CameraFollowType _Type)
{
	CameraType = _Type;
}

void PlayerDataBase::FieldCameraPivotCheck()
{
	CameraXEnd = ColMapWidth_Half - CameraWidth_Half;
	CameraYEnd = ColMapHegiht_Half - CameraHegiht_Half;

	// 현재 위치에서 카메라의 이동 가능 영역 필요
	float XLeftEnd = ColMapWidth_Half - CameraXEnd;
	float XRightEnd = ColMapWidth_Half + CameraXEnd;

	if (XLeftEnd >= TargetPosition.x)
	{
		if (1 == LeftCount)
		{
			LeftCount = 0;
			IsLeftEndPosition = true;

			float4 EndPos = { XLeftEnd, TargetPosition.y, TargetPosition.z };

			CameraEndPosition = EndPos;
		}
	}
	else
	{
		LeftCount = 1;
		IsLeftEndPosition = false;
	}

	if (XRightEnd <= TargetPosition.x)
	{
		if (1 == RightCount)
		{
			RightCount = 0;
			IsRightEndPosition = true;

			float4 EndPos = { XRightEnd, TargetPosition.y, TargetPosition.z };

			CameraEndPosition = EndPos;
		}
	}
	else
	{
		RightCount = 1;
		IsRightEndPosition = false;
	}
}

void PlayerDataBase::OverwolrdCameraPivotCheck()
{
	CameraXEnd = ColMapWidth_Half - CameraWidth_Half;
	CameraYEnd = ColMapHegiht_Half - CameraHegiht_Half;

	// 현재 위치에서 카메라의 이동 가능 영역 필요
	float XLeftEnd = ColMapWidth_Half - CameraXEnd;
	float XRightEnd = ColMapWidth_Half + CameraXEnd;
	float YUpEnd = ColMapHegiht_Half + CameraYEnd - 15.0f;
	float YDownEnd = ColMapHegiht_Half - CameraYEnd;

	if (XLeftEnd >= TargetPosition.x)
	{
		TargetPosition.x = XLeftEnd;
	}

	if (XRightEnd <= TargetPosition.x)
	{
		TargetPosition.x = XRightEnd;
	}

	if (YUpEnd <= TargetPosition.y)
	{
		TargetPosition.y = YUpEnd;
	}

	if (YDownEnd >= TargetPosition.y)
	{
		TargetPosition.y = YDownEnd;
	}
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

		//CameraPivotCheck();

		GetLevel()->GetMainCamera()->GetTransform()->SetWorldPosition(CameraPos);
	}
		break;
	case PlayerDataBase::CameraFollowType::Field:
	{
		TargetPosition = GetTransform()->GetWorldPosition();

		float CameraPosX = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition().x;
		float CameraPosY = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition().y;

		PrevCameraPosition = { CameraPosX, CameraPosY };
		float4 Movedir = float4::Zero;
		FieldCameraPivotCheck();

		if (true == IsLeftEndPosition || true == IsRightEndPosition)
		{
			Movedir = (CameraEndPosition - PrevCameraPosition);
		}
		else
		{
			Movedir = (TargetPosition - PrevCameraPosition);
		}

		MoveDistance = Movedir * 2.0f * _DeltaTime;
		MoveDistance.z = 0.0f;
		MoveDistance.y = 0.0f;

		GetLevel()->GetMainCamera()->GetTransform()->AddWorldPosition(MoveDistance);
	}
		break;
	case PlayerDataBase::CameraFollowType::Overworld:
	{
		TargetPosition = GetTransform()->GetLocalPosition();

		float CameraPosX = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition().x;
		float CameraPosY = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition().y;

		PrevCameraPosition = { CameraPosX, CameraPosY };
		float4 Movedir = float4::Zero;

		OverwolrdCameraPivotCheck();

		Movedir = (TargetPosition - PrevCameraPosition);

		MoveDistance = Movedir * 4.5f * _DeltaTime;
		MoveDistance.z = 0.0f;

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
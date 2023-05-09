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

	// ���� ��ġ���� ī�޶��� �̵� ���� ���� �ʿ�
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

	// ���� ��ġ���� ī�޶��� �̵� ���� ���� �ʿ�
	float XLeftEnd = ColMapWidth_Half - CameraXEnd;
	float XRightEnd = ColMapWidth_Half + CameraXEnd;
	float YUpEnd = ColMapHegiht_Half + CameraYEnd;
	float YDownEnd = ColMapHegiht_Half - CameraYEnd;

	if (XLeftEnd >= TargetPosition.x)
	{
	}

	if (XRightEnd <= TargetPosition.x)
	{
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

		if (true == IsLeftEndPosition)
		{
			Movedir = (CameraEndPosition - PrevCameraPosition);
		}
		else if (true == IsRightEndPosition)
		{
			Movedir = (CameraEndPosition - PrevCameraPosition);
		}
		else
		{
			Movedir = (TargetPosition - PrevCameraPosition);
		}

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

		OverwolrdCameraPivotCheck();

		float4 Movedir = (TargetPosition - PrevCameraPosition);

		MoveDistance = Movedir * 4.5f * _DeltaTime;

		GetLevel()->GetMainCamera()->GetTransform()->AddWorldPosition(MoveDistance);
	}
		break;
	case PlayerDataBase::CameraFollowType::None:
	{
		MsgAssert("�ʵ忡�� ������� ī�޶� ������ ���������� �ʾҽ��ϴ�.");
		return;
	}
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     ANIMATION                       ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<GameEngineSpriteRenderer> PlayerDataBase::AnimationCreate_Field()
{
	std::shared_ptr<GameEngineSpriteRenderer> RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetTexture("Ground_Idle_001.png");
	RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
	RenderPtr->GetTransform()->SetLocalPosition({ 0, 90 });

	return RenderPtr;
}

std::shared_ptr<GameEngineSpriteRenderer> PlayerDataBase::AnimationCreate_Overworld()
{
	std::shared_ptr<GameEngineSpriteRenderer> RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetTexture("Idle.png");
	RenderPtr->GetTransform()->SetLocalScale({ 49, 96, 1 });
	RenderPtr->GetTransform()->SetLocalPosition({ 0, 0 });

	return RenderPtr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                        Pixel                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlayerDataBase::AirDashCheck(const GameEnginePixelColor& _LeftFallMapPixel, const GameEnginePixelColor& _RightFallMapPixel)
{
	// Fall üũ �ȼ� ��� Black�̳� Blue�� ��쿡�� AirDash ����
	if (true == PixelCollisionCheck.IsBlack(_LeftFallMapPixel) && true == PixelCollisionCheck.IsBlack(_RightFallMapPixel))
	{
		AirDash = true;
	}
	else if (true == PixelCollisionCheck.IsBlue(_LeftFallMapPixel) && true == PixelCollisionCheck.IsBlack(_RightFallMapPixel))
	{
		AirDash = true;
	}
	else if (true == PixelCollisionCheck.IsBlack(_LeftFallMapPixel) && true == PixelCollisionCheck.IsBlue(_RightFallMapPixel))
	{
		AirDash = true;
	}
	else if (true == PixelCollisionCheck.IsBlue(_LeftFallMapPixel) && true == PixelCollisionCheck.IsBlue(_RightFallMapPixel))
	{
		AirDash = true;
	}
}

void PlayerDataBase::WallCheck(const GameEnginePixelColor& _LeftWallMapPixel, const GameEnginePixelColor& _RightWallMapPixel, float _DeltaTime)
{
	float DashFalseDist = MoveSpeed * _DeltaTime;
	float DashTureDist = (MoveSpeed * 2) * _DeltaTime;

	if (true == IsDash)
	{
		if (true == PixelCollisionCheck.IsBlack(_LeftWallMapPixel))
		{
			GetTransform()->AddLocalPosition({ DashTureDist, 0 });
		}
		if (true == PixelCollisionCheck.IsBlack(_RightWallMapPixel))
		{
			GetTransform()->AddLocalPosition({ -DashTureDist, 0 });
		}
	}
	else
	{
		if (true == PixelCollisionCheck.IsBlack(_LeftWallMapPixel))
		{
			GetTransform()->AddLocalPosition({ DashFalseDist, 0 });
		}
		if (true == PixelCollisionCheck.IsBlack(_RightWallMapPixel))
		{
			GetTransform()->AddLocalPosition({ -DashFalseDist, 0 });
		}
	}
}

// BlackPixel�� üũ
void PlayerDataBase::PixelCheck(float _DeltaTime)
{
	// ���� üũ
	float4 PlayerPos = GetTransform()->GetLocalPosition();
	float4 LeftFallPos = PlayerPos + float4{ -40, -2 };
	float4 RightFallPos = PlayerPos + float4{ 25, -2 };

	GameEnginePixelColor LeftFallMapPixel = PixelCollisionCheck.PixelCheck(LeftFallPos);
	GameEnginePixelColor RightFallMapPixel = PixelCollisionCheck.PixelCheck(RightFallPos);

	// Fall üũ �ȼ� ��� Black�� �ƴ϶�� Fall ���·� ����
	if (false == PixelCollisionCheck.IsBlack(LeftFallMapPixel) && false == PixelCollisionCheck.IsBlack(RightFallMapPixel))
	{
		IsFall = true;
	}
	else // �̿� ��� ��Ȳ ������ �Ұ�
	{
		BottomJumpAble = false;
	}

	// ����뽬 ���� ���� üũ
	AirDashCheck(LeftFallMapPixel, RightFallMapPixel);

	// �ٴ� üũ
	GameEnginePixelColor ColMapPixel = PixelCollisionCheck.PixelCheck(PlayerPos);

	if (true == PixelCollisionCheck.IsBlack(ColMapPixel))
	{
		IsJump = false;

		while (true)
		{
			GetTransform()->AddLocalPosition({ 0, 1 });

			PlayerPos = GetTransform()->GetLocalPosition();

			GameEnginePixelColor GravityPixel = PixelCollisionCheck.PixelCheck(PlayerPos);

			if (false == PixelCollisionCheck.IsBlack(GravityPixel))
			{
				IsFall = false;
				break;
			}
		}
	}

	// �� üũ
	float4 LeftWallCheckPos = PlayerPos + float4{-40, 10};
	float4 RightWallCheckPos = PlayerPos + float4{ 25, 10 };
	
	GameEnginePixelColor LeftWallPixel = PixelCollisionCheck.PixelCheck(LeftWallCheckPos);
	GameEnginePixelColor RightWallPixel = PixelCollisionCheck.PixelCheck(RightWallCheckPos);

	WallCheck(LeftWallPixel, RightWallPixel, _DeltaTime);
}

// BluePixel�� üũ
void PlayerDataBase::BottomJump(float _DeltaTime)
{
	// ������ üũ
	float4 PlayerPos = GetTransform()->GetLocalPosition();
	float4 LeftFallPos = PlayerPos + float4{ -40, -2 };
	float4 RightFallPos = PlayerPos + float4{ 25, -2 };

	GameEnginePixelColor LeftFallMapPixel = PixelCollisionCheck.PixelCheck(LeftFallPos);
	GameEnginePixelColor RightFallMapPixel = PixelCollisionCheck.PixelCheck(RightFallPos);

	// ����뽬 ���� ���� üũ
	AirDashCheck(LeftFallMapPixel, RightFallMapPixel);

	// Fall üũ �ȼ� ��� Blue��� ������ ���� ���·� ����
	if (true == PixelCollisionCheck.IsBlue(LeftFallMapPixel) && true == PixelCollisionCheck.IsBlue(RightFallMapPixel))
	{
		BottomJumpAble = true;
	}

	// �ٴ� üũ
	GameEnginePixelColor ColMapPixel = PixelCollisionCheck.PixelCheck(PlayerPos);

	if (true == PixelCollisionCheck.IsBlue(ColMapPixel))
	{
		IsJump = false;

		while (true)
		{
			GetTransform()->AddLocalPosition({ 0, 1 });

			PlayerPos = GetTransform()->GetLocalPosition();

			GameEnginePixelColor GravityPixel = PixelCollisionCheck.PixelCheck(PlayerPos);

			if (false == PixelCollisionCheck.IsBlue(GravityPixel))
			{
				IsFall = false;
				break;
			}
		}
	}

	// �� üũ
	float4 LeftWallCheckPos = PlayerPos + float4{ -40, 10 };
	float4 RightWallCheckPos = PlayerPos + float4{ 25, 10 };

	GameEnginePixelColor LeftWallPixel = PixelCollisionCheck.PixelCheck(LeftWallCheckPos);
	GameEnginePixelColor RightWallPixel = PixelCollisionCheck.PixelCheck(RightWallCheckPos);

	WallCheck(LeftWallPixel, RightWallPixel, _DeltaTime);
}

void PlayerDataBase::BottomJumpStateCheck()
{
	float4 BottomJumpCheck = GetTransform()->GetLocalPosition() + float4{ 0, -1 };

	GameEnginePixelColor BottomJumpPixel = PixelCollisionCheck.PixelCheck(BottomJumpCheck);

	if (true == IsBottomJump)
	{
		if (true == PixelCollisionCheck.IsBlue(BottomJumpPixel))
		{
			IsBottomJump = true;
			return;
		}
		else
		{
			IsBottomJump = false;
		}
	}
}
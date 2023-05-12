#include "PrecompileHeader.h"
#include "Player.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Peashooter.h"
#include "Peashooter_EX.h"
#include "Spread.h"
#include "Spread_EX.h"
#include "EXDust.h"
#include "MoveDust.h"
#include "LandDust.h"
#include "ParryEffect.h"

Player* Player::MainPlayer = nullptr;

Player::Player() 
{
	MainPlayer = this;
	int a = 0;
}

Player::~Player() 
{
}

void Player::Start()
{
	PlayerInitialSetting();
	DebugRendererSetting();
	SetCameraFollowType(CameraFollowType::Field);
	SetPlayerMoveSpeed(380.0f);
	
	RenderPtr->GetTransform()->SetLocalPosition({ 0, 90 });
	RenderPtr->ChangeAnimation("Idle");
	ChangeState(PlayerState::Idle);

	PeashooterRenderPtr->GetTransform()->SetLocalScale(float4{300, 300});
	PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 100, 40 });
	PeashooterRenderPtr->GetTransform()->SetParent(GetTransform());
	PeashooterRenderPtr->ChangeAnimation("Peashooter_Spawn");
	PeashooterRenderPtr->Off();
}
void Player::Update(float _DeltaTime)
{
	if (false == IsCorrection)
	{
		PositionCorrection();		// 최초 레벨 진입 시 위치 세팅
		return;
	}

	MoveCamera(_DeltaTime);         // 카메라 이동 연산
	DirectCheck();				    // 플레이어 위치 판정
	UpdateState(_DeltaTime);		// 플레이어 FSM 업데이트
	ProjectileCreate(_DeltaTime);	// 총알, EX, Dust 생성
	// 충돌체 필요
	PixelCalculation(_DeltaTime);	// 플레이어 픽셀 충돌 계산
	PlayerDebugRenderer();			// 플레이어 디버깅 랜더 온오프
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     AssistFunction                       //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 플레이어 위치 보정 함수(최초 레벨 init 시 실시)
void Player::PositionCorrection()
{
	float4 PlayerPos = GetTransform()->GetLocalPosition();

	if (0 >= PlayerPos.y)
	{
		MsgAssert("플레이어의 위치는 y = 0 위로 세팅해야 합니다. 비정상적인 플레이어 위치입니다.");
		return;
	}

	GameEnginePixelColor ColMapPixel = PixelCollisionCheck.PixelCheck(PlayerPos);

	// 현재 위치의 Pixel이 Black이라면 이후 PixelCheck에서 연산 실시
	if (true == PixelCollisionCheck.IsBlack(ColMapPixel))
	{
		IsCorrection = true;
	}

	// 현재 위치의 Pixel이 Black이 아니라면 위치를 밑으로 이동
	if (false == PixelCollisionCheck.IsBlack(ColMapPixel))
	{
		while (true)
		{
			GetTransform()->AddLocalPosition({ 0, -1 });

			PlayerPos = GetTransform()->GetLocalPosition();

			GameEnginePixelColor GravityPixel = PixelCollisionCheck.PixelCheck(PlayerPos);

			if (true == PixelCollisionCheck.IsBlack(GravityPixel))
			{
				IsCorrection = true;
				break;
			}
		}
	}
}

// 플레이어 GetPixel 연산 모음
void Player::PixelCalculation(float _DeltaTime)
{
	// 위로 솓아오르는 점프 상태일 경우에만 BluePixel 통과 가능
	if (true == IsJump && 0.0f <= MoveDirect.y)
	{
		BluePixelCheckAble = false;
	}
	else
	{
		BluePixelCheckAble = true;
	}

	float4 PlayerPosCheck = GetTransform()->GetLocalPosition() + float4{ 0, -1 };
	GameEnginePixelColor BluePixelCheck = PixelCollisionCheck.PixelCheck(PlayerPosCheck);

	if (true == IsBottomJump)
	{
		BottomJumpStateCheck(); // 밑점프 상태일 경우 기존과 다른 픽셀충돌 연산 실시
	}
	else if (false == PixelCollisionCheck.IsBlue(BluePixelCheck))
	{
		PixelCheck(_DeltaTime);
	}
	else
	{
		if (false == BluePixelCheckAble)
		{
			return;
		}

		BottomJump(_DeltaTime);
	}
}

// 플레이어 GetPixel 연산 모음
void Player::PlayerDebugRenderer()
{
	if (true == IsDebugRender)
	{
		DebugRenderPtr0->On();
		DebugRenderPtr1->On();
		DebugRenderPtr2->On();
		DebugRenderPtr3->On();
		DebugRenderPtr4->On();
		DebugRenderPtr5->On();
		DebugRenderPtr6->On();
	}
	else
	{
		DebugRenderPtr0->Off();
		DebugRenderPtr1->Off();
		DebugRenderPtr2->Off();
		DebugRenderPtr3->Off();
		DebugRenderPtr4->Off();
		DebugRenderPtr5->Off();
		DebugRenderPtr6->Off();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     CreateActor                       /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::ProjectileCreate(float _DeltaTime)
{
	if (true == IsDash || true == IsSlap)
	{
		return;
	}

	ProjectileCreateTime += _DeltaTime;

	if (true == GameEngineInput::IsDown("WeaponSwap"))
	{
		WeaponType = !WeaponType;
		bool Check = WeaponType;
		ProjectileCreateTime = 0.06f;

		if (true == WeaponType)
		{
			PeashooterRenderPtr->ChangeAnimation("Peashooter_Spawn");
		}
		else
		{
			PeashooterRenderPtr->ChangeAnimation("Spread_Spawn");
		}
	}

	if (true == GameEngineInput::IsPress("Attack"))
	{
		PeashooterRenderPtr->On();
	}
	else
	{
		PeashooterRenderPtr->Off();
	}

	// WeaponType = true : Peashooter
	// WeaponType = false : Spread
	if (0.12f <= ProjectileCreateTime && GameEngineInput::IsPress("Attack"))
	{
		if (true == WeaponType)
		{
			ProjectileCreateTime = 0.0f;
			CreatePeashooter();
		}
		else if (false == WeaponType)
		{
			ProjectileCreateTime = 0.0f;
			CreateSpread();
		}
	}
}

// 기본 공격
void Player::CreatePeashooter()
{
	std::shared_ptr<Peashooter> Projectile = GetLevel()->CreateActor<Peashooter>(1);

	float4 PlayerPosition = GetTransform()->GetLocalPosition();
	float4 ProjectilePosition = PlayerPosition;
	float4 ProjectileRotation = float4::Zero;

	if (5 > ProjectileSet)
	{
		++ProjectileSet;
	}
	else if (5 == ProjectileSet)
	{
		ProjectileSet = 0;
	}

	switch (ADValue)
	{
	case AttackDirection::Right_Up:
	{
		ProjectilePosition += float4{ 15, 180 };
		ProjectileRotation += float4{ 0, 0, 90 };

		if (3 > ProjectileSet && 0 != ProjectileSet)
		{
			ProjectilePosition += float4{ 8, 0 };
		}
		else if (5 > ProjectileSet && 3 <= ProjectileSet)
		{
			ProjectilePosition += float4{ -8 , 0 };
		}

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 15, 180 });
	}
	break;
	case AttackDirection::Right_DiagonalUp:
	{
		ProjectilePosition += float4{ 70, 120 };
		ProjectileRotation += float4{ 0, 0, 45 };

		if (3 > ProjectileSet && 0 != ProjectileSet)
		{
			ProjectilePosition += float4{ 5, -5 };
		}
		else if (5 > ProjectileSet && 3 <= ProjectileSet)
		{
			ProjectilePosition += float4{ -5, 5 };
		}

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 70, 120 });
	}
	break;
	case AttackDirection::Right_Front:
	{
		if (true == IsDuckAttack)
		{
			ProjectilePosition += float4{ 100, 40 };
			ProjectileRotation += float4{ 0, 0, 0 };

			PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 100, 40 });
		}
		else
		{
			ProjectilePosition += float4{ 80, 70 };
			ProjectileRotation += float4{ 0, 0, 0 };

			PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 80, 70 });
		}


		if (3 > ProjectileSet && 0 != ProjectileSet)
		{
			ProjectilePosition += float4{ 0, 8 };
		}
		else if (5 > ProjectileSet && 3 <= ProjectileSet)
		{
			ProjectilePosition += float4{ 0, -8 };
		}
	}
	break;
	case AttackDirection::Right_DiagonalDown:
	{
		ProjectilePosition += float4{ 70, 30 };
		ProjectileRotation += float4{ 0, 0, 315 };

		if (3 > ProjectileSet && 0 != ProjectileSet)
		{
			ProjectilePosition += float4{ 5, 5 };
		}
		else if (5 > ProjectileSet && 3 <= ProjectileSet)
		{
			ProjectilePosition += float4{ -5, -5 };
		}

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 70, 30 });
	}
	break;
	case AttackDirection::Right_Down:
	{
		ProjectilePosition += float4{ 30, -10 };
		ProjectileRotation += float4{ 0, 0, 270 };

		if (3 > ProjectileSet && 0 != ProjectileSet)
		{
			ProjectilePosition += float4{ 8, 0 };
		}
		else if (5 > ProjectileSet && 3 <= ProjectileSet)
		{
			ProjectilePosition += float4{ -8 , 0 };
		}

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 30, -10 });
	}
	break;
	case AttackDirection::Left_Up:
	{
		ProjectilePosition += float4{ -25, 180 };
		ProjectileRotation += float4{ 0, 0, 270 };

		if (3 > ProjectileSet && 0 != ProjectileSet)
		{
			ProjectilePosition += float4{ 8, 0 };
		}
		else if (5 > ProjectileSet && 3 <= ProjectileSet)
		{
			ProjectilePosition += float4{ -8 , 0 };
		}

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 25, 180 });
	}
	break;
	case AttackDirection::Left_DiagonalUp:
	{
		ProjectilePosition += float4{ -80, 120 };
		ProjectileRotation += float4{ 0, 0, 315 };

		if (3 > ProjectileSet && 0 != ProjectileSet)
		{
			ProjectilePosition += float4{ 5, 5 };
		}
		else if (5 > ProjectileSet && 3 <= ProjectileSet)
		{
			ProjectilePosition += float4{ -5, -5 };
		}

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 80, 120 });
	}
	break;
	case AttackDirection::Left_Front:
	{
		if (true == IsDuckAttack)
		{
			ProjectilePosition += float4{ -110, 40 };
			ProjectileRotation += float4{ 0, 0, 0 };

			PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 120, 40 });
		}
		else
		{
			ProjectilePosition += float4{ -80, 70 };
			ProjectileRotation += float4{ 0, 0, 0 };

			PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 90, 70 });
		}

		if (3 > ProjectileSet && 0 != ProjectileSet)
		{
			ProjectilePosition += float4{ 0, 8 };
		}
		else if (5 > ProjectileSet && 3 <= ProjectileSet)
		{
			ProjectilePosition += float4{ 0, -8 };
		}
	}
	break;
	case AttackDirection::Left_DiagonalDown:
	{
		ProjectilePosition += float4{ -80, 30 };
		ProjectileRotation += float4{ 0, 0, 45 };

		if (3 > ProjectileSet && 0 != ProjectileSet)
		{
			ProjectilePosition += float4{ 5, -5 };
		}
		else if (5 > ProjectileSet && 3 <= ProjectileSet)
		{
			ProjectilePosition += float4{ -5, 5 };
		}

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 80, 30 });
	}
	break;
	case AttackDirection::Left_Down:
	{
		ProjectilePosition += float4{ -40, -10 };
		ProjectileRotation += float4{ 0, 0, 90 };

		if (3 > ProjectileSet && 0 != ProjectileSet)
		{
			ProjectilePosition += float4{ 8, 0 };
		}
		else if (5 > ProjectileSet && 3 <= ProjectileSet)
		{
			ProjectilePosition += float4{ -8 , 0 };
		}

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 40, -10 });
	}
	break;
	default:
		break;
	}

	Projectile->SetStartPosition(ProjectilePosition);
	Projectile->SetProjectileRotation(ProjectileRotation);
	Projectile->SetDirection(Directbool);
}

// 기본 EX 공격
void Player::CreatePeashooter_EX() {}

// 2번 공격
void Player::CreateSpread()
{
	std::shared_ptr<Spread> Projectile0 = GetLevel()->CreateActor<Spread>(1);
	std::shared_ptr<Spread> Projectile1 = GetLevel()->CreateActor<Spread>(1);
	std::shared_ptr<Spread> Projectile2 = GetLevel()->CreateActor<Spread>(1);
	std::shared_ptr<Spread> Projectile3 = GetLevel()->CreateActor<Spread>(1);
	std::shared_ptr<Spread> Projectile4 = GetLevel()->CreateActor<Spread>(1);

	float4 PlayerPosition = GetTransform()->GetLocalPosition();

	float4 ProjectilePosition0 = PlayerPosition;
	float4 ProjectilePosition1 = PlayerPosition;
	float4 ProjectilePosition2 = PlayerPosition;
	float4 ProjectilePosition3 = PlayerPosition;
	float4 ProjectilePosition4 = PlayerPosition;

	float4 ProjectileRotation0 = float4::Zero;
	float4 ProjectileRotation1 = float4::Zero;
	float4 ProjectileRotation2 = float4::Zero;
	float4 ProjectileRotation3 = float4::Zero;
	float4 ProjectileRotation4 = float4::Zero;

	// 기본 로테이션은 Right_Front 기준
	ProjectileRotation0 += float4{ 0, 0, 330 };
	ProjectileRotation1 += float4{ 0, 0, 345 };
	ProjectileRotation2 += float4{ 0, 0, 15 };
	ProjectileRotation3 += float4{ 0, 0, 30 };

	switch (ADValue)
	{
	case AttackDirection::Right_Up:
	{
		ProjectilePosition0 += float4{ 15, 160 };
		ProjectilePosition1 += float4{ 15, 160 };
		ProjectilePosition2 += float4{ 15, 160 };
		ProjectilePosition3 += float4{ 15, 160 };
		ProjectilePosition4 += float4{ 15, 160 };

		ProjectileRotation0 += float4{ 0, 0, 90 }; 
		ProjectileRotation1 += float4{ 0, 0, 90 };
		ProjectileRotation2 += float4{ 0, 0, 90 };
		ProjectileRotation3 += float4{ 0, 0, 90 };
		ProjectileRotation4 += float4{ 0, 0, 90 };

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 15, 180 });
	}
	break;
	case AttackDirection::Right_DiagonalUp:
	{
		ProjectilePosition0 += float4{ 60, 120 };
		ProjectilePosition1 += float4{ 60, 120 };
		ProjectilePosition2 += float4{ 60, 120 };
		ProjectilePosition3 += float4{ 60, 120 };
		ProjectilePosition4 += float4{ 60, 120 };

		ProjectileRotation0 += float4{ 0, 0, 45 };
		ProjectileRotation1 += float4{ 0, 0, 45 };
		ProjectileRotation2 += float4{ 0, 0, 45 };
		ProjectileRotation3 += float4{ 0, 0, 45 };
		ProjectileRotation4 += float4{ 0, 0, 45 };

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 70, 120 });
	}
	break;
	case AttackDirection::Right_Front:
	{
		if (true == IsDuckAttack)
		{
			ProjectilePosition0 += float4{ 90, 40 };
			ProjectilePosition1 += float4{ 90, 40 };
			ProjectilePosition2 += float4{ 90, 40 };
			ProjectilePosition3 += float4{ 90, 40 };
			ProjectilePosition4 += float4{ 90, 40 };

			PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 90, 40 });
		}
		else
		{
			ProjectilePosition0 += float4{ 70, 70 };
			ProjectilePosition1 += float4{ 70, 70 };
			ProjectilePosition2 += float4{ 70, 70 };
			ProjectilePosition3 += float4{ 70, 70 };
			ProjectilePosition4 += float4{ 70, 70 };

			PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 70, 70 });
		}
	}
	break;
	case AttackDirection::Right_DiagonalDown:
	{
		ProjectilePosition0 += float4{ 60, 30 };
		ProjectilePosition1 += float4{ 60, 30 };
		ProjectilePosition2 += float4{ 60, 30 };
		ProjectilePosition3 += float4{ 60, 30 };
		ProjectilePosition4 += float4{ 60, 30 };

		ProjectileRotation0 += float4{ 0, 0, 315 };
		ProjectileRotation1 += float4{ 0, 0, 315 };
		ProjectileRotation2 += float4{ 0, 0, 315 };
		ProjectileRotation3 += float4{ 0, 0, 315 };
		ProjectileRotation4 += float4{ 0, 0, 315 };

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 70, 30 });
	}
	break;
	case AttackDirection::Right_Down:
	{
		ProjectilePosition0 += float4{ 20, -10 };
		ProjectilePosition1 += float4{ 20, -10 };
		ProjectilePosition2 += float4{ 20, -10 };
		ProjectilePosition3 += float4{ 20, -10 };

		ProjectileRotation0 += float4{ 0, 0, 270 };
		ProjectileRotation1 += float4{ 0, 0, 270 };
		ProjectileRotation2 += float4{ 0, 0, 270 };
		ProjectileRotation3 += float4{ 0, 0, 270 };
		ProjectileRotation4 += float4{ 0, 0, 270 };

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 30, -10 });
	}
	break;
	case AttackDirection::Left_Up:
	{
		ProjectilePosition0 += float4{ -30, 160 };
		ProjectilePosition1 += float4{ -30, 160 };
		ProjectilePosition2 += float4{ -30, 160 };
		ProjectilePosition3 += float4{ -30, 160 };
		ProjectilePosition4 += float4{ -30, 160 };

		ProjectileRotation0 += float4{ 0, 0, 270 };
		ProjectileRotation1 += float4{ 0, 0, 270 };
		ProjectileRotation2 += float4{ 0, 0, 270 };
		ProjectileRotation3 += float4{ 0, 0, 270 };
		ProjectileRotation4 += float4{ 0, 0, 270 };

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 25, 180 });
	}
	break;
	case AttackDirection::Left_DiagonalUp:
	{
		ProjectilePosition0 += float4{ -70, 120 };
		ProjectilePosition1 += float4{ -70, 120 };
		ProjectilePosition2 += float4{ -70, 120 };
		ProjectilePosition3 += float4{ -70, 120 };
		ProjectilePosition4 += float4{ -70, 120 };

		ProjectileRotation0 += float4{ 0, 0, 315 };
		ProjectileRotation1 += float4{ 0, 0, 315 };
		ProjectileRotation2 += float4{ 0, 0, 315 };
		ProjectileRotation3 += float4{ 0, 0, 315 };
		ProjectileRotation4 += float4{ 0, 0, 315 };

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 80, 120 });
	}
	break;
	case AttackDirection::Left_Front:
	{
		if (true == IsDuckAttack)
		{
			ProjectilePosition0 += float4{ -110, 40 };
			ProjectilePosition1 += float4{ -110, 40 };
			ProjectilePosition2 += float4{ -110, 40 };
			ProjectilePosition3 += float4{ -110, 40 };
			ProjectilePosition4 += float4{ -110, 40 };

			ProjectileRotation0 += float4{ 0, 0, 0 };
			ProjectileRotation1 += float4{ 0, 0, 0 };
			ProjectileRotation2 += float4{ 0, 0, 0 };
			ProjectileRotation3 += float4{ 0, 0, 0 };
			ProjectileRotation4 += float4{ 0, 0, 0 };

			PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 120, 40 });
		}
		else
		{
			ProjectilePosition0 += float4{ -80, 70 };
			ProjectilePosition1 += float4{ -80, 70 };
			ProjectilePosition2 += float4{ -80, 70 };
			ProjectilePosition3 += float4{ -80, 70 };
			ProjectilePosition4 += float4{ -80, 70 };

			ProjectileRotation0 += float4{ 0, 0, 0 };
			ProjectileRotation1 += float4{ 0, 0, 0 };
			ProjectileRotation2 += float4{ 0, 0, 0 };
			ProjectileRotation3 += float4{ 0, 0, 0 };
			ProjectileRotation4 += float4{ 0, 0, 0 };

			PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 90, 70 });
		}
	}
	break;
	case AttackDirection::Left_DiagonalDown:
	{
		ProjectilePosition0 += float4{ -70, 30 };
		ProjectilePosition1 += float4{ -70, 30 };
		ProjectilePosition2 += float4{ -70, 30 };
		ProjectilePosition3 += float4{ -70, 30 };
		ProjectilePosition4 += float4{ -70, 30 };

		ProjectileRotation0 += float4{ 0, 0, 45 };
		ProjectileRotation1 += float4{ 0, 0, 45 };
		ProjectileRotation2 += float4{ 0, 0, 45 };
		ProjectileRotation3 += float4{ 0, 0, 45 };
		ProjectileRotation4 += float4{ 0, 0, 45 };

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 80, 30 });
	}
	break;
	case AttackDirection::Left_Down:
	{
		ProjectilePosition0 += float4{ -30, -10 };
		ProjectilePosition1 += float4{ -30, -10 };
		ProjectilePosition2 += float4{ -30, -10 };
		ProjectilePosition3 += float4{ -30, -10 };
		ProjectilePosition4 += float4{ -30, -10 };

		ProjectileRotation0 += float4{ 0, 0, 90 };
		ProjectileRotation1 += float4{ 0, 0, 90 };
		ProjectileRotation2 += float4{ 0, 0, 90 };
		ProjectileRotation3 += float4{ 0, 0, 90 };
		ProjectileRotation4 += float4{ 0, 0, 90 };

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 40, -10 });
	}
	break;
	default:
		break;
	}

	Projectile0->SetStartPosition(ProjectilePosition0);
	Projectile1->SetStartPosition(ProjectilePosition1);
	Projectile2->SetStartPosition(ProjectilePosition2);
	Projectile3->SetStartPosition(ProjectilePosition3);
	Projectile4->SetStartPosition(ProjectilePosition4);

	Projectile0->SetProjectileRotation(ProjectileRotation0);
	Projectile1->SetProjectileRotation(ProjectileRotation1);
	Projectile2->SetProjectileRotation(ProjectileRotation2);
	Projectile3->SetProjectileRotation(ProjectileRotation3);
	Projectile4->SetProjectileRotation(ProjectileRotation4);

	Projectile0->SetDirection(Directbool);
	Projectile1->SetDirection(Directbool);
	Projectile2->SetDirection(Directbool);
	Projectile3->SetDirection(Directbool);
	Projectile4->SetDirection(Directbool);

	Projectile0->SetMoveSpeed(1200);
	Projectile1->SetMoveSpeed(1100);
	Projectile2->SetMoveSpeed(1100);
	Projectile3->SetMoveSpeed(1200);
	Projectile4->SetMoveSpeed(1200);

	Projectile0->SetDeathType(true);
	Projectile1->SetDeathType(false);
	Projectile2->SetDeathType(false);
	Projectile3->SetDeathType(true);
	Projectile4->SetDeathType(true);
}

// 2번 EX 공격 
void Player::CreateSpread_EX() {}

// EX 공격 시 Dust 생성
void Player::CreateEXDust() {}

// 움직일 때 Dust 생성
void Player::CreateMoveDust() {}

// 점프나 Fall 후 Land시 Dust 생성
void Player::CreateLandDust() {}

// Parry시 생성되는 Effect
void Player::CreateParryEffect() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                         FSM                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::DirectCheck()
{
	if (true == IsDash)
	{
		return;
	}

	if (true == IsEXAttack)
	{
		return;
	}

	if (true == GameEngineInput::IsPress("MoveRight"))
	{
		Directbool = true;
	}
	else if (true == GameEngineInput::IsPress("MoveLeft"))
	{
		Directbool = false;
	}

	if (true == Directbool)
	{
		GetTransform()->SetLocalPositiveScaleX();
		RenderPtr->GetTransform()->SetLocalPosition({ 0, 90 });

		{
			DebugRenderPtr1->GetTransform()->SetLocalPosition({ -40, 10 });
			DebugRenderPtr2->GetTransform()->SetLocalPosition({ 25, 10 });
			DebugRenderPtr3->GetTransform()->SetLocalPosition({ -40, -2 });
			DebugRenderPtr4->GetTransform()->SetLocalPosition({ 25, -2 });
			// DebugRenderPtr5는 액터 바로 밑(y-1)이기 때문에 필요 없음
			// DebugRenderPtr6->Off();
		}
	}
	else
	{
		GetTransform()->SetLocalNegativeScaleX();
		RenderPtr->GetTransform()->SetLocalPosition({ 15, 90 });

		{
			DebugRenderPtr1->GetTransform()->SetLocalPosition({ -25, 10 });
			DebugRenderPtr2->GetTransform()->SetLocalPosition({ 40, 10 });
			DebugRenderPtr3->GetTransform()->SetLocalPosition({ -25, -2 });
			DebugRenderPtr4->GetTransform()->SetLocalPosition({ 40, -2 });
			// DebugRenderPtr5는 액터 바로 밑(y-1)이기 때문에 필요 없음
			// DebugRenderPtr6->Off();
		}
	}

	AttackDirectCheck();
}

void Player::AttackDirectCheck()
{
	if (true == Directbool)
	{
		if (true == GameEngineInput::IsPress("MoveUp") && true == GameEngineInput::IsPress("MoveRight"))
		{
			ADValue = AttackDirection::Right_DiagonalUp;
		}
		else if (true == GameEngineInput::IsPress("MoveDown") && true == GameEngineInput::IsPress("MoveRight"))
		{
			ADValue = AttackDirection::Right_DiagonalDown;
		}
		else if (true == GameEngineInput::IsPress("MoveUp"))
		{
			ADValue = AttackDirection::Right_Up;
		}
		else if (true == GameEngineInput::IsPress("MoveRight"))
		{
			ADValue = AttackDirection::Right_Front;
		}
		else if (true == GameEngineInput::IsPress("MoveDown"))
		{
			ADValue = AttackDirection::Right_Down;
		}
	}
	else
	{
		if (true == GameEngineInput::IsPress("MoveUp") && true == GameEngineInput::IsPress("MoveLeft"))
		{
			ADValue = AttackDirection::Left_DiagonalUp;
		}
		else if (true == GameEngineInput::IsPress("MoveDown") && true == GameEngineInput::IsPress("MoveLeft"))
		{
			ADValue = AttackDirection::Left_DiagonalDown;
		}
		else if (true == GameEngineInput::IsPress("MoveUp"))
		{
			ADValue = AttackDirection::Left_Up;
		}
		else if (true == GameEngineInput::IsPress("MoveLeft"))
		{
			ADValue = AttackDirection::Left_Front;
		}
		else if (true == GameEngineInput::IsPress("MoveDown"))
		{
			ADValue = AttackDirection::Left_Down;
		}
	}
}

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
	if (true == GameEngineInput::IsDown("EX"))
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
		MoveDirect.y += -3000.0f * _DeltaTime;
		GetTransform()->AddLocalPosition(MoveDirect * _DeltaTime);
	}
	else if (false == IsFall)
	{
		MoveDirect.y = 0;
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
	RenderPtr->ChangeAnimation("Idle");
	RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
}
void Player::IdleUpdate(float _DeltaTime)
{
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

	if (true == GameEngineInput::IsDown("EX"))
	{
		ChangeState(PlayerState::EXAttack);
		return;
	}

	if (true == GameEngineInput::IsPress("MoveRight") || true == GameEngineInput::IsPress("MoveLeft"))
	{
		ChangeState(PlayerState::Move);
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

	if (true == GameEngineInput::IsPress("MoveLeft") && true == GameEngineInput::IsPress("MoveRight"))
	{
		ChangeState(PlayerState::Idle);
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
	RenderPtr->ChangeAnimation("Move");
	RenderPtr->GetTransform()->SetLocalScale({ 170, 200, 1 });
}
void Player::MoveUpdate(float _DeltaTime)
{
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
		if (true == GameEngineInput::IsPress("MoveLeft"))
		{
			GetTransform()->AddLocalPosition({ -MoveDis, 0 });
		}
	}

	if (true == GameEngineInput::IsDown("EX"))
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
	if (true == GameEngineInput::IsDown("EX"))
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
	if (true == GameEngineInput::IsDown("EX"))
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
}

// Jump 상태 체크
void Player::JumpStart()
{
	RenderPtr->ChangeAnimation("Jump");
	RenderPtr->GetTransform()->SetLocalScale({ 170, 220, 1 });

	// 점프력
	if (false == IsJump && false == IsSlap)
	{
		MoveDirect.y = 900.0f;
		IsJump = true;
	}
}
void Player::JumpUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("EX"))
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
	if (true == GameEngineInput::IsPress("Jump") && 0.01f <= JumpTime)
	{
		if (0.15f >= JumpTime)
		{
			MoveDirect.y += 2200.0f * _DeltaTime;
		}
	}

	if (true == IsJump && 0.01f <= JumpTime)
	{
		MoveDirect.y += -3000.0f * _DeltaTime;
		GetTransform()->AddLocalPosition(MoveDirect * _DeltaTime);
	}
	else if (false == IsJump && 0.01f <= JumpTime)
	{
		MoveDirect.y = 0;
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
}
void Player::SlapUpdate(float _DeltaTime)
{
	// 패리 성공 시
	//if (true)
	//{
	//	IsSlap = false;
	//	IsJump = false;
	//	MoveDirect.y = 0;
	//	JumpTime = 0.0f;
	//	ChangeState(PlayerState::Jump);
	//	return;
	//}

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

}

// Idle에서 MoveUp 입력 시 상태 체크
void Player::AttackReadyStart()
{
	RenderPtr->ChangeAnimation("Hold_Normal_Up");
	RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
}
void Player::AttackReadyUpdate(float _DeltaTime)
{
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

	if (true == GameEngineInput::IsDown("EX"))
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
	if (true == IsFall)
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	if (true == GameEngineInput::IsDown("EX"))
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
	RenderPtr->GetTransform()->SetLocalScale({ 170, 200, 1 });
}
void Player::RunAttackUpdate(float _DeltaTime)
{
	if (true == IsFall)
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	if (true == GameEngineInput::IsDown("EX"))
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
	if (true == GameEngineInput::IsPress("MoveLeft"))
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
}

// Duck에서 Attack 입력 시 상태 체크
void Player::DuckAttackStart()
{
	RenderPtr->ChangeAnimation("DuckAttack");
	RenderPtr->GetTransform()->SetLocalScale({ 220, 220, 1 });

	IsDuckAttack = true;
}
void Player::DuckAttackUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("EX"))
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
}

// EX Attack 상태 체크
void Player::EXAttackStart()
{
	IsEXAttack = true;
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
	}
	break;
	default:
		break;
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
	IsEXAttack = false;
}

// Hold 입력 시 상태 체크
void Player::HoldingStart()
{
	RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
}
void Player::HoldingUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("Hold"))
	{
		IsHold = true;

		if (true == GameEngineInput::IsDown("EX"))
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
	if (true == GameEngineInput::IsPress("Hold"))
	{
		IsHold = true;

		if (true == GameEngineInput::IsDown("EX"))
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////             Init(Animation & Collision)            /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::PlayerInitialSetting()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	PeashooterRenderPtr = CreateComponent<GameEngineSpriteRenderer>();

	if (nullptr == GameEngineSprite::Find("Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Action");

		// Idle
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Idle").GetFullPath());

		// Move
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Move").GetFullPath());

		// Jump & Parry(Slap)
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Jump").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Parry").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Parry_Pink").GetFullPath());

		// Dash
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirDash").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dash").GetFullPath());

		// Duck
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DuckReady").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Duck").GetFullPath());

		// Hit & Death
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirHit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ghost").GetFullPath());

		// Hold
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_Up").GetFullPath());

		// Attack(Move, Duck, Hold(==Idle))
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Move_Attak_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Move_Attak_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DuckAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_Up").GetFullPath());

		// EX
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_Up").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_Up").GetFullPath());

		// Interaction & Intro
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ElderKettleInteraction").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Intro_Flex").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Intro_Regular").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Peashooter\\Peashooter_Spawn"))
	{
		// 스프레드 시트 애니메이션
		// RenderPtr->CreateAnimation({ "Win", "TestAnimation.png", 0, 5, 0.1f, true, true });

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("Attack");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter\\Peashooter_Spawn.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter\\Peashooter_Loop.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter\\Peashooter_Death.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter\\Peashooter_EX_Loop.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter\\Peashooter_EX_Death.png").GetFullPath(), 5, 2);

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread\\Spread_Spawn.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread\\Spread_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread\\Spread_Death.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread\\Spread_Death_Enemyhit.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread\\Spread_Weak_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread\\Spread_Weak_Death.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread\\Spread_Weak_Death_Enemyhit.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread\\Spread_EX_Spawn.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread\\Spread_EX_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread\\Spread_EX_Flame.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread\\Spread_EX_Death.png").GetFullPath(), 6, 1);

		//std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		//for (size_t i = 0; i < File.size(); i++)
		//{
		//	GameEngineTexture::Load(File[i].GetFullPath());
		//}
	}

	if (nullptr == GameEngineSprite::Find("Ex_SFX"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("SFX");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_SFX").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("JumpDust").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ParryEffect").GetFullPath());
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("PlayerDust\\Dust_A.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("PlayerDust\\Dust_B.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("PlayerDust\\Dust_C.png").GetFullPath(), 5, 4);
	}

	// Idle
	RenderPtr->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Idle", .FrameInter = 0.07f });

	// Move
	RenderPtr->CreateAnimation({ .AnimationName = "Move", .SpriteName = "Move", .FrameInter = 0.05f });

	// Jump & Parry(Slap)
	RenderPtr->CreateAnimation({ .AnimationName = "Jump", .SpriteName = "Jump", .FrameInter = 0.05f });
	RenderPtr->CreateAnimation({ .AnimationName = "Parry", .SpriteName = "Parry", .FrameInter = 0.05f });
	RenderPtr->CreateAnimation({ .AnimationName = "Parry_Pink", .SpriteName = "Parry_Pink", .FrameInter = 0.05f });

	// Dash
	RenderPtr->CreateAnimation({ .AnimationName = "AirDash", .SpriteName = "AirDash", .FrameInter = 0.05f });
	RenderPtr->CreateAnimation({ .AnimationName = "Dash", .SpriteName = "Dash", .FrameInter = 0.05f });

	// Duck
	RenderPtr->CreateAnimation({ .AnimationName = "DuckReady", .SpriteName = "DuckReady", .FrameInter = 0.05f });
	RenderPtr->CreateAnimation({ .AnimationName = "Duck", .SpriteName = "Duck", .FrameInter = 0.07f });

	// Hit & Death
	RenderPtr->CreateAnimation({ .AnimationName = "AirHit", .SpriteName = "AirHit", .FrameInter = 0.05f });
	RenderPtr->CreateAnimation({ .AnimationName = "Hit", .SpriteName = "Hit", .FrameInter = 0.05f });
	RenderPtr->CreateAnimation({ .AnimationName = "Death", .SpriteName = "Death", .FrameInter = 0.05f });
	RenderPtr->CreateAnimation({ .AnimationName = "Ghost", .SpriteName = "Ghost", .FrameInter = 0.05f });

	// Hold
	RenderPtr->CreateAnimation({ .AnimationName = "Hold_Normal_DiagonalDown", .SpriteName = "Hold_Normal_DiagonalDown", .FrameInter = 0.07f });
	RenderPtr->CreateAnimation({ .AnimationName = "Hold_Normal_DiagonalUp", .SpriteName = "Hold_Normal_DiagonalUp", .FrameInter = 0.07f });
	RenderPtr->CreateAnimation({ .AnimationName = "Hold_Normal_Down", .SpriteName = "Hold_Normal_Down", .FrameInter = 0.07f });
	RenderPtr->CreateAnimation({ .AnimationName = "Hold_Normal_Straight", .SpriteName = "Hold_Normal_Straight", .FrameInter = 0.07f });
	RenderPtr->CreateAnimation({ .AnimationName = "Hold_Normal_Up", .SpriteName = "Hold_Normal_Up", .FrameInter = 0.07f });

	// Attack(Move, Duck, Hold(==Idle))
	RenderPtr->CreateAnimation({ .AnimationName = "Move_Attak_DiagonalUp", .SpriteName = "Move_Attak_DiagonalUp", .FrameInter = 0.05f });
	RenderPtr->CreateAnimation({ .AnimationName = "Move_Attak_Straight", .SpriteName = "Move_Attak_Straight", .FrameInter = 0.05f });
	RenderPtr->CreateAnimation({ .AnimationName = "DuckAttack", .SpriteName = "DuckAttack", .FrameInter = 0.05f });
	RenderPtr->CreateAnimation({ .AnimationName = "Hold_Shoot_DiagonalDown", .SpriteName = "Hold_Shoot_DiagonalDown", .FrameInter = 0.05f });
	RenderPtr->CreateAnimation({ .AnimationName = "Hold_Shoot_DiagonalUp", .SpriteName = "Hold_Shoot_DiagonalUp", .FrameInter = 0.05f });
	RenderPtr->CreateAnimation({ .AnimationName = "Hold_Shoot_Down", .SpriteName = "Hold_Shoot_Down", .FrameInter = 0.05f });
	RenderPtr->CreateAnimation({ .AnimationName = "Hold_Shoot_Straight", .SpriteName = "Hold_Shoot_Straight", .FrameInter = 0.05f });
	RenderPtr->CreateAnimation({ .AnimationName = "Hold_Shoot_Up", .SpriteName = "Hold_Shoot_Up", .FrameInter = 0.05f });

	// EX
	RenderPtr->CreateAnimation({ .AnimationName = "AirEx_DiagonalDown", .SpriteName = "AirEX_DiagonalDown", .FrameInter = 0.05f, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "AirEx_DiagonalUp", .SpriteName = "AirEx_DiagonalUp", .FrameInter = 0.05f, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "AirEx_Down", .SpriteName = "AirEx_Down", .FrameInter = 0.05f, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "AirEx_Straight", .SpriteName = "AirEx_Straight", .FrameInter = 0.05f, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "AirEx_Up", .SpriteName = "AirEx_Up", .FrameInter = 0.05f, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "Ex_DiagonalDown", .SpriteName = "Ex_DiagonalDown", .FrameInter = 0.05f, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "Ex_DiagonalUp", .SpriteName = "Ex_DiagonalUp", .FrameInter = 0.05f, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "Ex_Down", .SpriteName = "Ex_Down", .FrameInter = 0.05f, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "Ex_Straight", .SpriteName = "Ex_Straight", .FrameInter = 0.05f, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "Ex_Up", .SpriteName = "Ex_Up", .FrameInter = 0.05f, .ScaleToTexture = true });

	// Interaction & Intro
	RenderPtr->CreateAnimation({ .AnimationName = "ElderKettleInteraction", .SpriteName = "ElderKettleInteraction", .FrameInter = 0.07f });
	RenderPtr->CreateAnimation({ .AnimationName = "Intro_Flex", .SpriteName = "Intro_Flex", .FrameInter = 0.07f });
	RenderPtr->CreateAnimation({ .AnimationName = "Intro_Regular", .SpriteName = "Intro_Regular", .FrameInter = 0.07f });

	PeashooterRenderPtr->CreateAnimation({ "Peashooter_Spawn", "Peashooter_Spawn.png", 0, 3, 0.05f, true, false });
	PeashooterRenderPtr->CreateAnimation({ "Spread_Spawn", "Spread_Spawn.png", 0, 3, 0.05f, true, false });
}

void Player::DebugRendererSetting()
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("CupHead_Resource");
	NewDir.Move("CupHead_Resource");
	NewDir.Move("Image");
	NewDir.Move("Character");
	NewDir.Move("CupHead");
	NewDir.Move("DebugImage");

	std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

	for (size_t i = 0; i < File.size(); i++)
	{
		GameEngineTexture::Load(File[i].GetFullPath());
	}

	DebugRenderPtr0 = CreateComponent<GameEngineSpriteRenderer>();
	DebugRenderPtr1 = CreateComponent<GameEngineSpriteRenderer>();
	DebugRenderPtr2 = CreateComponent<GameEngineSpriteRenderer>();
	DebugRenderPtr3 = CreateComponent<GameEngineSpriteRenderer>();
	DebugRenderPtr4 = CreateComponent<GameEngineSpriteRenderer>();
	DebugRenderPtr5 = CreateComponent<GameEngineSpriteRenderer>();
	DebugRenderPtr6 = CreateComponent<GameEngineSpriteRenderer>();

	DebugRenderPtr0->SetScaleToTexture("RedDot.png");
	DebugRenderPtr1->SetScaleToTexture("RedDot.png");
	DebugRenderPtr2->SetScaleToTexture("RedDot.png");
	DebugRenderPtr3->SetScaleToTexture("RedDot.png");
	DebugRenderPtr4->SetScaleToTexture("RedDot.png");
	DebugRenderPtr5->SetScaleToTexture("GreenDot.png");
	DebugRenderPtr6->SetScaleToTexture("RedDot.png");   // 미사용

	DebugRenderPtr1->GetTransform()->SetLocalPosition({ -40, 10 }); // 왼쪽 벽
	DebugRenderPtr2->GetTransform()->SetLocalPosition({ 25, 10 });  // 오른쪽 벽
	DebugRenderPtr1->GetTransform()->SetLocalPosition({ -40, -2 }); // 왼쪽 낙하
	DebugRenderPtr2->GetTransform()->SetLocalPosition({ 25, -2 });  // 오른쪽 낙하
	DebugRenderPtr5->GetTransform()->SetLocalPosition({ 0, -1 });   // 밑점프 체크
	//DebugRenderPtr6->Off();

	DebugRenderPtr0->Off();
	DebugRenderPtr1->Off();
	DebugRenderPtr2->Off();
	DebugRenderPtr3->Off();
	DebugRenderPtr4->Off();
	DebugRenderPtr5->Off();
	DebugRenderPtr6->Off();
}
#include "PrecompileHeader.h"
#include "Player.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Peashooter.h"
#include "Peashooter_EX.h"
#include "Spread.h"
#include "Spread_EX.h"
#include "DashDust.h"
#include "EXDust.h"
#include "HitSFX.h"
#include "MoveDust.h"
#include "LandDust.h"
#include "ParryEffect.h"

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
	PlayerInitialSetting();
	DebugRendererSetting();
	PlayerCollisionSetting();
	SetCameraFollowType(CameraFollowType::Field);
	SetPlayerMoveSpeed(420.0f);

	ChangeState(PlayerState::Idle);
}
void Player::Update(float _DeltaTime)
{
	if (false == IsCorrection)
	{
		On();
		PositionCorrection();			// 최초 레벨 진입 시 위치 세팅
		SetPlayerHP(GetHP());           // 레벨 진입 시 스탯 세팅
		SetPlayerEXGauge(GetEXGauge());
		SetPlayerEXStack(GetEXStack());
		return;
	}

	MoveCamera(_DeltaTime);			    // 카메라 이동 연산
	DirectCheck();					    // 플레이어 위치 판정
	UpdateState(_DeltaTime);			// 플레이어 FSM 업데이트
	ProjectileCreate(_DeltaTime);		// 총알 생성
	CreateMoveDust();					// 움직일 때 Dust 생성
	CollisionSetting();                 // 프레임마다 콜리전 위치 체크
	CollisionCalculation(_DeltaTime);	// 플레이어 맵충돌(픽셀, 충돌체) 계산
	PlayerDebugRenderer();				// 플레이어 디버깅 랜더 온오프
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

			if (-10000.0f >= PlayerPos.y)
			{
				MsgAssert("픽셀 충돌에 문제가 생겼다");
				return;
			}

			if (true == PixelCollisionCheck.IsBlack(GravityPixel))
			{
				IsCorrection = true;
				break;
			}
		}
	}
}

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
		BodyCollisionRenderPtr->On();
		StandCollisionRenderPtr->On();
		BottomSensorCollisionRenderPtr->On();
		FrontSensorCollisionRenderPtr->On();
	}
	else
	{
		DebugRenderPtr0->Off();
		DebugRenderPtr1->Off();
		DebugRenderPtr2->Off();
		DebugRenderPtr3->Off();
		DebugRenderPtr4->Off();
		DebugRenderPtr5->Off();
		BodyCollisionRenderPtr->Off();
		StandCollisionRenderPtr->Off();
		BottomSensorCollisionRenderPtr->Off();
		FrontSensorCollisionRenderPtr->Off();
	}
}

// 플레이어 충돌 연산(픽셀, 충돌체) 모음
void Player::CollisionCalculation(float _DeltaTime)
{
	// 위로 솓아오르는 점프 상태일 경우에만 BluePixel 통과 가능
	if (true == IsJump && 0.0f <= MoveDirect.y)
	{
		PlatformCheckAble = false;
	}
	else
	{
		PlatformCheckAble = true;
	}

	if (true == IsBottomJump)
	{
		PlatformBottomJumpStateCheck(_DeltaTime);
	}
	else if (nullptr == BottomSensorCollisionPtr->Collision(static_cast<int>(CollisionOrder::Platform), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		PixelCheck(_DeltaTime);
	}
	else
	{
		if (false == PlatformCheckAble)
		{
			return;
		}

		PlatformBottomJump(_DeltaTime);
	}

	if (true == IsSlap)
	{
		ParryCollisionCheck();
	}

	HitCollisionCheck(_DeltaTime);

	PortalCheck();

	WallCollisionCheck(_DeltaTime);

	ElderKettleCheck();
}

void Player::HitBlink(float _DeltaTime)
{
	if (true == IsHit)
	{
		return;
	}

	if (2.95f <= HitTime)
	{
		Inter = 0.0f;
		MulColorCheck = false;
		RenderPtr->ColorOptionValue.MulColor.a = OriginMulColor;
		return;
	}

	if (false == MulColorCheck)
	{
		MulColorCheck = true;
		OriginMulColor = RenderPtr->ColorOptionValue.MulColor.a;
		BlinkMulColor = 0.4f;
	}

	Inter += _DeltaTime;

	if (0.4f < Inter)
	{
		Inter = 0.0f;
	}
	else if (0.3f < Inter && Inter <= 0.4f)
	{
		RenderPtr->ColorOptionValue.MulColor.a = OriginMulColor;
	}
	else if (0.2f < Inter && Inter <= 0.3f)
	{
		RenderPtr->ColorOptionValue.MulColor.a = BlinkMulColor;
	}
}

void Player::PortalCheck()
{
	if (nullptr != BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Portal), ColType::AABBBOX2D, ColType::AABBBOX2D)
		&& PlayerState::Idle == StateValue
		|| PlayerState::Portal == StateValue)
	{
		PortalAble = true;
	}
	else
	{
		PortalAble = false;
	}
}

void Player::ElderKettleCheck()
{
	if (nullptr != BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::ElderKettle), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		ElderKettleInterAction = true;
	}
	else
	{
		ElderKettleInterAction = false;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                        Pixel                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// BlackPixel 픽셀 체크
void Player::PixelCheck(float _DeltaTime)
{
	// 낙하 체크
	float4 PlayerPos = GetTransform()->GetLocalPosition();
	float4 LeftFallPos = PlayerPos + float4{ -25, -2 };
	float4 RightFallPos = PlayerPos + float4{ 15, -2 };

	GameEnginePixelColor LeftFallMapPixel = PixelCollisionCheck.PixelCheck(LeftFallPos);
	GameEnginePixelColor RightFallMapPixel = PixelCollisionCheck.PixelCheck(RightFallPos);

	// Fall 체크 픽셀 모두 Black이 아니라면 Fall 상태로 진입
	if (false == PixelCollisionCheck.IsBlack(LeftFallMapPixel) && false == PixelCollisionCheck.IsBlack(RightFallMapPixel))
	{
		IsFall = true;
	}
	else // 이외 모든 상황 밑점프 불가
	{
		BottomJumpAble = false;
	}

	// 에어대쉬 가능 상태 체크
	// Fall 체크 픽셀 모두 Black이나 Blue인 경우에만 AirDash 가능
	if (true == PixelCollisionCheck.IsBlack(LeftFallMapPixel) && true == PixelCollisionCheck.IsBlack(RightFallMapPixel))
	{
		AirDash = true;
	}

	// 바닥 체크
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
				CreateLandDust();
				IsFall = false;
				break;
			}
		}
	}

	// 벽 체크
	float4 LeftWallCheckPos = PlayerPos + float4{ -25, 10 };
	float4 RightWallCheckPos = PlayerPos + float4{ 15, 10 };

	GameEnginePixelColor LeftWallPixel = PixelCollisionCheck.PixelCheck(LeftWallCheckPos);
	GameEnginePixelColor RightWallPixel = PixelCollisionCheck.PixelCheck(RightWallCheckPos);

	WallCheck(LeftWallPixel, RightWallPixel, _DeltaTime);
}

// Black 픽셀 벽 체크
void Player::WallCheck(const GameEnginePixelColor& _LeftWallMapPixel, const GameEnginePixelColor& _RightWallMapPixel, float _DeltaTime)
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                    Collision                    ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::CollisionSetting()
{
	if (true == Directbool)
	{
		StandCollisionPtr->GetTransform()->SetLocalScale({ 40, 10 });
		StandCollisionPtr->GetTransform()->SetLocalPosition({ -5, 5 });

		BottomSensorCollisionPtr->GetTransform()->SetLocalScale({ 15, -6 });
		BottomSensorCollisionPtr->GetTransform()->SetLocalPosition({ -5, -3 });

		FrontSensorCollisionPtr->GetTransform()->SetLocalScale({ 8, 100 });
		FrontSensorCollisionPtr->GetTransform()->SetLocalPosition({ 40, 50 });
	}
	else
	{
		StandCollisionPtr->GetTransform()->SetLocalScale({ 40, 10 });
		StandCollisionPtr->GetTransform()->SetLocalPosition({ 5, 5 });

		BottomSensorCollisionPtr->GetTransform()->SetLocalScale({ 15, -6 });
		BottomSensorCollisionPtr->GetTransform()->SetLocalPosition({ 5, -3 });

		FrontSensorCollisionPtr->GetTransform()->SetLocalScale({ 8, 100 });
		FrontSensorCollisionPtr->GetTransform()->SetLocalPosition({ 55, 50 });
	}

	if (true == IsSlap && true == ParryCollisionRenderPtr->IsUpdate() && true == ParryCollisionPtr->IsUpdate())
	{
		if (true == Directbool)
		{
			ParryCollisionPtr->GetTransform()->SetLocalPosition({ -5, 85 });
			ParryCollisionPtr->GetTransform()->SetLocalScale({ 100, 100, 1 });
		}
		else
		{
			ParryCollisionPtr->GetTransform()->SetLocalPosition({ 10, 85 });
			ParryCollisionPtr->GetTransform()->SetLocalScale({ 100, 100, -1 });
		}
	}

	if (true == IsDash || true == IsEXAttack || true == HitTimeCheck)
	{
		BodyCollisionRenderPtr->Off();
		BodyCollisionPtr->Off();
	}
	else
	{
		BodyCollisionRenderPtr->On();
		BodyCollisionPtr->On();
	}

	if (true == IsDuck)
	{
		if (true == Directbool)
		{
			BodyCollisionPtr->GetTransform()->SetLocalScale({ 140, 60, 1 });
			BodyCollisionPtr->GetTransform()->SetLocalPosition({ -5, 30 });
		}
		else
		{
			BodyCollisionPtr->GetTransform()->SetLocalPosition({ 10, 30 });
			BodyCollisionPtr->GetTransform()->SetLocalScale({ 140, 60, -1 });
		}
	}
	else if (true == IsJump || true == IsFall)
	{
		if (true == Directbool)
		{
			BodyCollisionPtr->GetTransform()->SetLocalScale({ 90, 80, 1 });
			BodyCollisionPtr->GetTransform()->SetLocalPosition({ -5, 80 });
		}
		else
		{
			BodyCollisionPtr->GetTransform()->SetLocalPosition({ 10, 80 });
			BodyCollisionPtr->GetTransform()->SetLocalScale({ 90, 80, -1 });
		}
	}
	else
	{
		if (true == Directbool)
		{
			BodyCollisionPtr->GetTransform()->SetLocalScale({ 90, 120, 1 });
			BodyCollisionPtr->GetTransform()->SetLocalPosition({ -5, 60 });
		}
		else
		{
			BodyCollisionPtr->GetTransform()->SetLocalPosition({ 10, 60 });
			BodyCollisionPtr->GetTransform()->SetLocalScale({ 90, 120, -1 });
		}
	}

	BodyCollisionRenderPtr->GetTransform()->SetLocalScale(BodyCollisionPtr->GetTransform()->GetLocalScale());
	BodyCollisionRenderPtr->GetTransform()->SetLocalPosition(BodyCollisionPtr->GetTransform()->GetLocalPosition());

	ParryCollisionRenderPtr->GetTransform()->SetLocalScale(ParryCollisionPtr->GetTransform()->GetLocalScale());
	ParryCollisionRenderPtr->GetTransform()->SetLocalPosition(ParryCollisionPtr->GetTransform()->GetLocalPosition());

	StandCollisionRenderPtr->GetTransform()->SetLocalScale(StandCollisionPtr->GetTransform()->GetLocalScale());
	StandCollisionRenderPtr->GetTransform()->SetLocalPosition(StandCollisionPtr->GetTransform()->GetLocalPosition());

	BottomSensorCollisionRenderPtr->GetTransform()->SetLocalScale(BottomSensorCollisionPtr->GetTransform()->GetLocalScale());
	BottomSensorCollisionRenderPtr->GetTransform()->SetLocalPosition(BottomSensorCollisionPtr->GetTransform()->GetLocalPosition());

	FrontSensorCollisionRenderPtr->GetTransform()->SetLocalScale(FrontSensorCollisionPtr->GetTransform()->GetLocalScale());
	FrontSensorCollisionRenderPtr->GetTransform()->SetLocalPosition(FrontSensorCollisionPtr->GetTransform()->GetLocalPosition());
}

// BluePixel을 체크
void Player::PlatformBottomJump(float _DeltaTime)
{
	// 에어대쉬 가능 상태 체크
	if (nullptr != BottomSensorCollisionPtr->Collision(static_cast<int>(CollisionOrder::Platform), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		AirDash = true;
		BottomJumpAble = true;
	}

	// 바닥 체크
	if (nullptr != StandCollisionPtr->Collision(static_cast<int>(CollisionOrder::Platform), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		IsJump = false;

		while (true)
		{
			GetTransform()->AddLocalPosition({ 0, 1 });

			if (nullptr == StandCollisionPtr->Collision(static_cast<int>(CollisionOrder::Platform), ColType::AABBBOX2D, ColType::AABBBOX2D))
			{
				CreateLandDust();
				IsFall = false;
				break;
			}
		}
	}

	// 벽 체크
	float4 PlayerPos = GetTransform()->GetLocalPosition();
	float4 LeftWallCheckPos = PlayerPos + float4{ -25, 10 };
	float4 RightWallCheckPos = PlayerPos + float4{ 15, 10 };

	GameEnginePixelColor LeftWallPixel = PixelCollisionCheck.PixelCheck(LeftWallCheckPos);
	GameEnginePixelColor RightWallPixel = PixelCollisionCheck.PixelCheck(RightWallCheckPos);

	WallCheck(LeftWallPixel, RightWallPixel, _DeltaTime);
}

void Player::PlatformBottomJumpStateCheck(float _DeltaTime)
{
	// 벽 체크
	float4 PlayerPos = GetTransform()->GetLocalPosition();

	float4 LeftWallCheckPos = PlayerPos + float4{ -25, 10 };
	float4 RightWallCheckPos = PlayerPos + float4{ 15, 10 };

	GameEnginePixelColor LeftWallPixel = PixelCollisionCheck.PixelCheck(LeftWallCheckPos);
	GameEnginePixelColor RightWallPixel = PixelCollisionCheck.PixelCheck(RightWallCheckPos);

	WallCheck(LeftWallPixel, RightWallPixel, _DeltaTime);

	if (true == IsBottomJump)
	{
		if (nullptr != BottomSensorCollisionPtr->Collision(static_cast<int>(CollisionOrder::Platform), ColType::AABBBOX2D, ColType::AABBBOX2D))
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

void Player::ParryCollisionCheck()
{
	if (nullptr != ParryCollisionPtr->Collision(static_cast<int>(CollisionOrder::ParrySpot), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		ParryCheck = true;
		CreateParryEffect();
		AddPlayerEXStack();
	}
}

void Player::HitCollisionCheck(float _DeltaTime)
{
	if (nullptr != BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::MonsterAttack), ColType::AABBBOX2D, ColType::AABBBOX2D)
		|| nullptr != BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Monster), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		IsHit = true;
		HitTimeCheck = true;

		MinusPlayerHP();
		CreateHitEffect();

		BodyCollisionPtr->Off();
	}

	if (true == HitTimeCheck)
	{
		HitTime += _DeltaTime;
		HitBlink(_DeltaTime);
	}

	if (3.0f <= HitTime)
	{
		HitTimeCheck = false;
		HitTime = 0.0f;
		BodyCollisionPtr->On();
	}
}

void Player::WallCollisionCheck(float _DeltaTime)
{
	if (nullptr != FrontSensorCollisionPtr->Collision(static_cast<int>(CollisionOrder::Wall), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		if (true == IsDash)
		{
			float DashDist = (MoveSpeed * 2) * _DeltaTime;

			if (true == Directbool)
			{
				GetTransform()->AddLocalPosition({ -DashDist, 0 });
			}
			else
			{
				GetTransform()->AddLocalPosition({ DashDist, 0 });
			}
		}
		else
		{
			float MoveDis = MoveSpeed * _DeltaTime;

			if (true == Directbool)
			{
				GetTransform()->AddLocalPosition({ -MoveDis, 0 });
			}
			else
			{
				GetTransform()->AddLocalPosition({ MoveDis, 0 });
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     CreateActor                       /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::ProjectileCreate(float _DeltaTime)
{
	if (true == IsDash || true == IsSlap || true == IsEXAttack || true == IsHit || true == PortalAble || true == ElderKettleInterAction || true == ElderKettleInterActioning)
	{
		PeashooterRenderPtr->Off();
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

void Player::EXCreate()
{
	if (true == WeaponType)
	{
		CreatePeashooter_EX();
	}
	else if (false == WeaponType)
	{
		CreateSpread_EX();
	}

	CreateEXDust();
}

// 기본 공격
void Player::CreatePeashooter()
{
	std::shared_ptr<Peashooter> Projectile = GetLevel()->CreateActor<Peashooter>();

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

		if (1 == ProjectileSet || 4 == ProjectileSet)
		{
			ProjectilePosition += float4{ 10, 0 };
		}
		else if (2 == ProjectileSet || 3 == ProjectileSet)
		{
			ProjectilePosition += float4{ -10 , 0 };
		}

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 15, 180 });
	}
	break;
	case AttackDirection::Right_DiagonalUp:
	{
		ProjectilePosition += float4{ 70, 120 };
		ProjectileRotation += float4{ 0, 0, 45 };

		if (1 == ProjectileSet || 4 == ProjectileSet)
		{
			ProjectilePosition += float4{ 7, -7 };
		}
		else if (2 == ProjectileSet || 3 == ProjectileSet)
		{
			ProjectilePosition += float4{ -7, 7 };
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

		if (1 == ProjectileSet || 4 == ProjectileSet)
		{
			ProjectilePosition += float4{ 0, 10 };
		}
		else if (2 == ProjectileSet || 3 == ProjectileSet)
		{
			ProjectilePosition += float4{ 0, -10 };
		}
	}
	break;
	case AttackDirection::Right_DiagonalDown:
	{
		ProjectilePosition += float4{ 70, 30 };
		ProjectileRotation += float4{ 0, 0, 315 };

		if (1 == ProjectileSet || 4 == ProjectileSet)
		{
			ProjectilePosition += float4{ 7, 7 };
		}
		else if (2 == ProjectileSet || 3 == ProjectileSet)
		{
			ProjectilePosition += float4{ -7, -7 };
		}

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 70, 30 });
	}
	break;
	case AttackDirection::Right_Down:
	{
		ProjectilePosition += float4{ 30, -10 };
		ProjectileRotation += float4{ 0, 0, 270 };

		if (1 == ProjectileSet || 4 == ProjectileSet)
		{
			ProjectilePosition += float4{ 10, 0 };
		}
		else if (2 == ProjectileSet || 3 == ProjectileSet)
		{
			ProjectilePosition += float4{ -10 , 0 };
		}

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 30, -10 });
	}
	break;
	case AttackDirection::Left_Up:
	{
		ProjectilePosition += float4{ -25, 180 };
		ProjectileRotation += float4{ 0, 0, 270 };

		if (1 == ProjectileSet || 4 == ProjectileSet)
		{
			ProjectilePosition += float4{ 10, 0 };
		}
		else if (2 == ProjectileSet || 3 == ProjectileSet)
		{
			ProjectilePosition += float4{ -10, 0 };
		}

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 25, 180 });
	}
	break;
	case AttackDirection::Left_DiagonalUp:
	{
		ProjectilePosition += float4{ -80, 120 };
		ProjectileRotation += float4{ 0, 0, 315 };

		if (1 == ProjectileSet || 4 == ProjectileSet)
		{
			ProjectilePosition += float4{ 7, 7 };
		}
		else if (2 == ProjectileSet || 3 == ProjectileSet)
		{
			ProjectilePosition += float4{ -7, -7 };
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

		if (1 == ProjectileSet || 4 == ProjectileSet)
		{
			ProjectilePosition += float4{ 0, 10 };
		}
		else if (2 == ProjectileSet || 3 == ProjectileSet)
		{
			ProjectilePosition += float4{ 0, -10 };
		}
	}
	break;
	case AttackDirection::Left_DiagonalDown:
	{
		ProjectilePosition += float4{ -80, 30 };
		ProjectileRotation += float4{ 0, 0, 45 };

		if (1 == ProjectileSet || 4 == ProjectileSet)
		{
			ProjectilePosition += float4{ 7, -7 };
		}
		else if (2 == ProjectileSet || 3 == ProjectileSet)
		{
			ProjectilePosition += float4{ -7, 7 };
		}

		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 80, 30 });
	}
	break;
	case AttackDirection::Left_Down:
	{
		ProjectilePosition += float4{ -40, -10 };
		ProjectileRotation += float4{ 0, 0, 90 };

		if (1 == ProjectileSet || 4 == ProjectileSet)
		{
			ProjectilePosition += float4{ 10, 0 };
		}
		else if (2 == ProjectileSet || 3 == ProjectileSet)
		{
			ProjectilePosition += float4{ -10, 0 };
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
	Projectile->SetColMap(ColMap, Pivot);

	if (true == IsDebugRender)
	{
		Projectile->SetCollisionRenderOn();
	}
	else
	{
		Projectile->SetCollisionRenderOff();
	}
}

// 2번 공격
void Player::CreateSpread()
{
	std::shared_ptr<Spread> Projectile0 = GetLevel()->CreateActor<Spread>();
	std::shared_ptr<Spread> Projectile1 = GetLevel()->CreateActor<Spread>();
	std::shared_ptr<Spread> Projectile2 = GetLevel()->CreateActor<Spread>();
	std::shared_ptr<Spread> Projectile3 = GetLevel()->CreateActor<Spread>();
	std::shared_ptr<Spread> Projectile4 = GetLevel()->CreateActor<Spread>();

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

	Projectile0->SetColMap(ColMap, Pivot);
	Projectile1->SetColMap(ColMap, Pivot);
	Projectile2->SetColMap(ColMap, Pivot);
	Projectile3->SetColMap(ColMap, Pivot);
	Projectile4->SetColMap(ColMap, Pivot);

	if (true == IsDebugRender)
	{
		Projectile0->SetCollisionRenderOn();
		Projectile1->SetCollisionRenderOn();
		Projectile2->SetCollisionRenderOn();
		Projectile3->SetCollisionRenderOn();
		Projectile4->SetCollisionRenderOn();
	}
	else
	{
		Projectile0->SetCollisionRenderOff();
		Projectile1->SetCollisionRenderOff();
		Projectile2->SetCollisionRenderOff();
		Projectile3->SetCollisionRenderOff();
		Projectile4->SetCollisionRenderOff();
	}
}

// 기본 EX 공격
void Player::CreatePeashooter_EX()
{
	std::shared_ptr<Peashooter_EX> Projectile = GetLevel()->CreateActor<Peashooter_EX>();

	float4 PlayerPosition = GetTransform()->GetLocalPosition();
	float4 ProjectilePosition = PlayerPosition;
	float4 ProjectileRotation = float4::Zero;

	switch (ADValue)
	{
	case AttackDirection::Right_Up:
	{
		ProjectilePosition += float4{ 15, 180 };
		ProjectileRotation += float4{ 0, 0, 90 };
	}
	break;
	case AttackDirection::Right_DiagonalUp:
	{
		ProjectilePosition += float4{ 70, 120 };
		ProjectileRotation += float4{ 0, 0, 45 };
	}
	break;
	case AttackDirection::Right_Front:
	{
		ProjectilePosition += float4{ 80, 70 };
		ProjectileRotation += float4{ 0, 0, 0 };
	}
	break;
	case AttackDirection::Right_DiagonalDown:
	{
		ProjectilePosition += float4{ 70, 30 };
		ProjectileRotation += float4{ 0, 0, 315 };
	}
	break;
	case AttackDirection::Right_Down:
	{
		ProjectilePosition += float4{ 30, -10 };
		ProjectileRotation += float4{ 0, 0, 270 };
	}
	break;
	case AttackDirection::Left_Up:
	{
		ProjectilePosition += float4{ -25, 180 };
		ProjectileRotation += float4{ 0, 0, 270 };
	}
	break;
	case AttackDirection::Left_DiagonalUp:
	{
		ProjectilePosition += float4{ -80, 120 };
		ProjectileRotation += float4{ 0, 0, 315 };
	}
	break;
	case AttackDirection::Left_Front:
	{
		ProjectilePosition += float4{ -80, 70 };
		ProjectileRotation += float4{ 0, 0, 0 };
	}
	break;
	case AttackDirection::Left_DiagonalDown:
	{
		ProjectilePosition += float4{ -80, 30 };
		ProjectileRotation += float4{ 0, 0, 45 };
	}
	break;
	case AttackDirection::Left_Down:
	{
		ProjectilePosition += float4{ -40, -10 };
		ProjectileRotation += float4{ 0, 0, 90 };
	}
	break;
	default:
		break;
	}

	Projectile->SetStartPosition(ProjectilePosition);
	Projectile->SetProjectileRotation(ProjectileRotation);
	Projectile->SetDirection(Directbool);
	Projectile->SetMoveSpeed(900.0f);

	if (true == IsDebugRender)
	{
		Projectile->SetCollisionRenderOn();
	}
	else
	{
		Projectile->SetCollisionRenderOff();
	}
}

// 2번 EX 공격 
void Player::CreateSpread_EX() 
{
	std::shared_ptr<Spread_EX> Projectile0 = GetLevel()->CreateActor<Spread_EX>();
	std::shared_ptr<Spread_EX> Projectile1 = GetLevel()->CreateActor<Spread_EX>();
	std::shared_ptr<Spread_EX> Projectile2 = GetLevel()->CreateActor<Spread_EX>();
	std::shared_ptr<Spread_EX> Projectile3 = GetLevel()->CreateActor<Spread_EX>();
	std::shared_ptr<Spread_EX> Projectile4 = GetLevel()->CreateActor<Spread_EX>();
	std::shared_ptr<Spread_EX> Projectile5 = GetLevel()->CreateActor<Spread_EX>();
	std::shared_ptr<Spread_EX> Projectile6 = GetLevel()->CreateActor<Spread_EX>();
	std::shared_ptr<Spread_EX> Projectile7 = GetLevel()->CreateActor<Spread_EX>();

	float4 PlayerPosition = GetTransform()->GetLocalPosition();

	float4 ProjectilePosition0 = PlayerPosition + float4{ 90, 60 };  
	float4 ProjectilePosition1 = PlayerPosition + float4{ 40, 110 }; 
	float4 ProjectilePosition2 = PlayerPosition + float4{ -10, 160 };
	float4 ProjectilePosition3 = PlayerPosition + float4{ -60, 110 };
	float4 ProjectilePosition4 = PlayerPosition + float4{ -110, 60 };
	float4 ProjectilePosition5 = PlayerPosition + float4{ -60, 10 }; 
	float4 ProjectilePosition6 = PlayerPosition + float4{ -10, -40 };
	float4 ProjectilePosition7 = PlayerPosition + float4{ 40, 10 };  

	float4 ProjectileRotation0 = float4::Zero;
	float4 ProjectileRotation1 = float4::Zero;
	float4 ProjectileRotation2 = float4::Zero;
	float4 ProjectileRotation3 = float4::Zero;
	float4 ProjectileRotation4 = float4::Zero;
	float4 ProjectileRotation5 = float4::Zero;
	float4 ProjectileRotation6 = float4::Zero;
	float4 ProjectileRotation7 = float4::Zero;

	ProjectileRotation0 += float4{ 0, 0 };
	ProjectileRotation1 += float4{ 0, 0, 45 };
	ProjectileRotation2 += float4{ 0, 0, 90 };
	ProjectileRotation3 += float4{ 0, 0, 135 };
	ProjectileRotation4 += float4{ 0, 0, 180 };
	ProjectileRotation5 += float4{ 0, 0, 225 };
	ProjectileRotation6 += float4{ 0, 0, 270 };
	ProjectileRotation7 += float4{ 0, 0, 315 };

	Projectile0->SetStartPosition(ProjectilePosition0);
	Projectile1->SetStartPosition(ProjectilePosition1);
	Projectile2->SetStartPosition(ProjectilePosition2);
	Projectile3->SetStartPosition(ProjectilePosition3);
	Projectile4->SetStartPosition(ProjectilePosition4);
	Projectile5->SetStartPosition(ProjectilePosition5);
	Projectile6->SetStartPosition(ProjectilePosition6);
	Projectile7->SetStartPosition(ProjectilePosition7);

	Projectile0->SetProjectileRotation(ProjectileRotation0);
	Projectile1->SetProjectileRotation(ProjectileRotation1);
	Projectile2->SetProjectileRotation(ProjectileRotation2);
	Projectile3->SetProjectileRotation(ProjectileRotation3);
	Projectile4->SetProjectileRotation(ProjectileRotation4);
	Projectile5->SetProjectileRotation(ProjectileRotation5);
	Projectile6->SetProjectileRotation(ProjectileRotation6);
	Projectile7->SetProjectileRotation(ProjectileRotation7);

	if (true == IsDebugRender)
	{
		Projectile0->SetCollisionRenderOn();
		Projectile1->SetCollisionRenderOn();
		Projectile2->SetCollisionRenderOn();
		Projectile3->SetCollisionRenderOn();
		Projectile4->SetCollisionRenderOn();
		Projectile5->SetCollisionRenderOn();
		Projectile6->SetCollisionRenderOn();
		Projectile7->SetCollisionRenderOn();
	}
	else
	{
		Projectile0->SetCollisionRenderOff();
		Projectile1->SetCollisionRenderOff();
		Projectile2->SetCollisionRenderOff();
		Projectile3->SetCollisionRenderOff();
		Projectile4->SetCollisionRenderOff();
		Projectile5->SetCollisionRenderOff();
		Projectile6->SetCollisionRenderOff();
		Projectile7->SetCollisionRenderOff();
	}
}

// EX 공격 시 Dust 생성
void Player::CreateEXDust()
{
	std::shared_ptr<EXDust> Projectile = GetLevel()->CreateActor<EXDust>();
	
	float4 PlayerPosition = GetTransform()->GetLocalPosition();
	float4 ProjectilePosition = PlayerPosition;
	float4 ProjectileRotation = float4::Zero;

	// 기본 로테이션은 Right_Front 기준
	ProjectileRotation += float4{ 0, 0, 0 };

	switch (ADValue)
	{
	case AttackDirection::Right_Up:
	{
		ProjectilePosition += float4{ -5, 0 };
		ProjectileRotation += float4{ 0, 0, 90 };
	}
	break;
	case AttackDirection::Right_DiagonalUp:
	{
		ProjectilePosition += float4{ -60, 40 };
		ProjectileRotation += float4{ 0, 0, 45 };
	}
	break;
	case AttackDirection::Right_Front:
	{
		ProjectilePosition += float4{ -70, 70 };
		ProjectileRotation += float4{ 0, 0, 0 };
	}
	break;
	case AttackDirection::Right_DiagonalDown:
	{
		ProjectilePosition += float4{ -60, 130 };
		ProjectileRotation += float4{ 0, 0, 315 };
	}
	break;
	case AttackDirection::Right_Down:
	{
		ProjectilePosition += float4{ 20, 130 };
		ProjectileRotation += float4{ 0, 0, 270 };
	}
	break;
	case AttackDirection::Left_Up:
	{
		ProjectilePosition += float4{ -5, 0 };
		ProjectileRotation += float4{ 0, 0, 270 };
	}
	break;
	case AttackDirection::Left_DiagonalUp:
	{
		ProjectilePosition += float4{ 50, 20 };
		ProjectileRotation += float4{ 0, 0, 315 };
	}
	break;
	case AttackDirection::Left_Front:
	{
		ProjectilePosition += float4{ 70, 70 };
	}
	break;
	case AttackDirection::Left_DiagonalDown:
	{
		ProjectilePosition += float4{ 50, 130 };
		ProjectileRotation += float4{ 0, 0, 45 };
	}
	break;
	case AttackDirection::Left_Down:
	{
		ProjectilePosition += float4{ -20, 130 };
		ProjectileRotation += float4{ 0, 0, 90 };
	}
	break;
	default:
		break;
	}

	ProjectilePosition += float4{ 0, 0, 4 };

	Projectile->SetStartPosition(ProjectilePosition);
	Projectile->SetProjectileRotation(ProjectileRotation);
	Projectile->SetDirection(Directbool);
}

// 대쉬 시 Dust 생성
void Player::CreateDashDust()
{
	std::shared_ptr<DashDust> Dust = GetLevel()->CreateActor<DashDust>();

	float4 PlayerPosition = GetTransform()->GetLocalPosition();
	float4 DustPosition = PlayerPosition;

	DustPosition += float4{ -10, 60, 3 };

	Dust->SetStartPosition(DustPosition);
	Dust->SetDirection(Directbool);
}

// 움직일 때 Dust 생성
void Player::CreateMoveDust()
{
	if (0.4f >= MoveTime)
	{
		return;
	}

	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, 2);

	MoveTime = 0.0f;

	std::shared_ptr<MoveDust> Dust = GetLevel()->CreateActor<MoveDust>();
	float4 PlayerPosition = GetTransform()->GetLocalPosition();
	float4 DustPosition = PlayerPosition;

	if (0 == RandValue)
	{
		DustPosition += float4{ 0, 55 };
		
	}
	else if (1 == RandValue)
	{
		DustPosition += float4{ 0, 60 };
	}
	else if (2 == RandValue)
	{
		DustPosition += float4{ 0, 65 };
	}

	if (true == Directbool)
	{
		DustPosition += float4{ -15, 0 };
	}
	else
	{
		DustPosition += float4{ 15, 0 };
	}

	DustPosition += float4{ 0, 0, 3 };

	Dust->SetStartPosition(DustPosition);
	Dust->SetDirection(Directbool);
	Dust->SetDustType(static_cast<DustType>(RandValue));
}

// 점프나 Fall 후 Land시 Dust 생성
void Player::CreateLandDust()
{
	if (true == IsJump)
	{
		return;
	}

	std::shared_ptr<LandDust> Dust = GetLevel()->CreateActor<LandDust>();
	float4 PlayerPosition = GetTransform()->GetLocalPosition();
	float4 DustPosition = PlayerPosition;

	DustPosition += float4{ 0, 30, 3 };

	Dust->SetStartPosition(DustPosition);
	Dust->SetDirection(Directbool);
}

// Parry시 생성되는 Effect
void Player::CreateParryEffect()
{
	std::shared_ptr<ParryEffect> Effect = GetLevel()->CreateActor<ParryEffect>();
	float4 PlayerPosition = GetTransform()->GetLocalPosition();
	float4 EffectPosition = PlayerPosition;

	EffectPosition += float4{ 0, 90, 3 };

	Effect->SetStartPosition(EffectPosition);
	Effect->SetDirection(Directbool);
}

void Player::CreateHitEffect()
{
	std::shared_ptr<HitSFX> Effect = GetLevel()->CreateActor<HitSFX>();
	float4 PlayerPosition = GetTransform()->GetLocalPosition();
	float4 EffectPosition = PlayerPosition;

	EffectPosition += float4{ -10, 110 };

	Effect->SetStartPosition(EffectPosition);
	Effect->SetDirection(Directbool);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                         FSM                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::DirectCheck()
{
	if (true == IsDash || true == IsEXAttack || true == Portaling || true == ParryCheck || true == ElderKettleInterActioning)
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
			DebugRenderPtr1->GetTransform()->SetLocalPosition({ -25, 10 });
			DebugRenderPtr2->GetTransform()->SetLocalPosition({ 15, 10 });
			DebugRenderPtr3->GetTransform()->SetLocalPosition({ -25, -2 });
			DebugRenderPtr4->GetTransform()->SetLocalPosition({ 15, -2 });
		}
	}
	else
	{
		GetTransform()->SetLocalNegativeScaleX();
		RenderPtr->GetTransform()->SetLocalPosition({ 15, 90 });

		{
			DebugRenderPtr1->GetTransform()->SetLocalPosition({ -15, 10 });
			DebugRenderPtr2->GetTransform()->SetLocalPosition({ 25, 10 });
			DebugRenderPtr3->GetTransform()->SetLocalPosition({ -15, -2 });
			DebugRenderPtr4->GetTransform()->SetLocalPosition({ 25, -2 });
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////             Init(Animation & Collision)            /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::PlayerInitialSetting()
{
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
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Portal").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Parry_Pink_0.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Action");
		NewDir.Move("Parry_Pink");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_0.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_1.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_2.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_3.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_4.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_5.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_6.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_7.png").GetFullPath(), 1, 1);
	}

	if (nullptr == GameEngineTexture::Find("Peashooter_Spawn.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("Attack");
		NewDir.Move("Peashooter");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_Spawn.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_Loop.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_Death.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_EX_Loop.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_EX_Death.png").GetFullPath(), 5, 2);
	}

	if (nullptr == GameEngineTexture::Find("Spread_Spawn.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("Attack");
		NewDir.Move("Spread");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Spawn.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Death.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Death_Enemyhit.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Weak_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Weak_Death.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Weak_Death_Enemyhit.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Spawn.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Flame.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Death.png").GetFullPath(), 6, 1);
	}

	if (nullptr == GameEngineTexture::Find("Dust_A.png"))
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
		NewDir.Move("PlayerDust");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_A.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_B.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_C.png").GetFullPath(), 5, 4);
	}

	if (nullptr == GameEngineSprite::Find("JumpDust"))
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

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("JumpDust").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DashDust").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("EXDust").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("EX_ChargeUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ParryEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("HitSFX").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == PeashooterRenderPtr)
	{
		PeashooterRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == ChargeUpRenderPtr)
	{
		ChargeUpRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr != RenderPtr)
	{
		// Idle
		RenderPtr->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Idle", .FrameInter = 0.07f });

		// Move
		RenderPtr->CreateAnimation({ .AnimationName = "Move", .SpriteName = "Move", .FrameInter = 0.04f });

		// Jump & Parry(Slap)
		RenderPtr->CreateAnimation({ .AnimationName = "Jump", .SpriteName = "Jump", .FrameInter = 0.05f });
		RenderPtr->CreateAnimation({ .AnimationName = "Parry", .SpriteName = "Parry", .FrameInter = 0.05f, .Loop = false });
		RenderPtr->CreateAnimation({ "Parry_Pink_0", "Parry_Pink_0.png", 0, 0, 0.05f, false, true });
		RenderPtr->CreateAnimation({ "Parry_Pink_1", "Parry_Pink_1.png", 0, 0, 0.05f, false, true });
		RenderPtr->CreateAnimation({ "Parry_Pink_2", "Parry_Pink_2.png", 0, 0, 0.05f, false, true });
		RenderPtr->CreateAnimation({ "Parry_Pink_3", "Parry_Pink_3.png", 0, 0, 0.05f, false, true });
		RenderPtr->CreateAnimation({ "Parry_Pink_4", "Parry_Pink_4.png", 0, 0, 0.05f, false, true });
		RenderPtr->CreateAnimation({ "Parry_Pink_5", "Parry_Pink_5.png", 0, 0, 0.05f, false, true });
		RenderPtr->CreateAnimation({ "Parry_Pink_6", "Parry_Pink_6.png", 0, 0, 0.05f, false, true });
		RenderPtr->CreateAnimation({ "Parry_Pink_7", "Parry_Pink_7.png", 0, 0, 0.05f, false, true });

		// Dash
		RenderPtr->CreateAnimation({ .AnimationName = "AirDash", .SpriteName = "AirDash", .FrameInter = 0.05f, .Loop = false });
		RenderPtr->CreateAnimation({ .AnimationName = "Dash", .SpriteName = "Dash", .FrameInter = 0.05f, .Loop = false });

		// Duck
		RenderPtr->CreateAnimation({ .AnimationName = "DuckReady", .SpriteName = "DuckReady", .FrameInter = 0.05f });
		RenderPtr->CreateAnimation({ .AnimationName = "Duck", .SpriteName = "Duck", .FrameInter = 0.07f });

		// Hit & Death
		RenderPtr->CreateAnimation({ .AnimationName = "AirHit", .SpriteName = "AirHit", .FrameInter = 0.04f, .Loop = false });
		RenderPtr->CreateAnimation({ .AnimationName = "Hit", .SpriteName = "Hit", .FrameInter = 0.04f, .Loop = false });
		RenderPtr->CreateAnimation({ .AnimationName = "Death", .SpriteName = "Death", .FrameInter = 0.05f, .Loop = false });
		RenderPtr->CreateAnimation({ .AnimationName = "Ghost", .SpriteName = "Ghost", .FrameInter = 0.05f });

		// Hold
		RenderPtr->CreateAnimation({ .AnimationName = "Hold_Normal_DiagonalDown", .SpriteName = "Hold_Normal_DiagonalDown", .FrameInter = 0.07f });
		RenderPtr->CreateAnimation({ .AnimationName = "Hold_Normal_DiagonalUp", .SpriteName = "Hold_Normal_DiagonalUp", .FrameInter = 0.07f });
		RenderPtr->CreateAnimation({ .AnimationName = "Hold_Normal_Down", .SpriteName = "Hold_Normal_Down", .FrameInter = 0.07f });
		RenderPtr->CreateAnimation({ .AnimationName = "Hold_Normal_Straight", .SpriteName = "Hold_Normal_Straight", .FrameInter = 0.07f });
		RenderPtr->CreateAnimation({ .AnimationName = "Hold_Normal_Up", .SpriteName = "Hold_Normal_Up", .FrameInter = 0.07f });

		// Attack(Move, Duck, Hold(==Idle))
		RenderPtr->CreateAnimation({ .AnimationName = "Move_Attak_DiagonalUp", .SpriteName = "Move_Attak_DiagonalUp", .FrameInter = 0.04f });
		RenderPtr->CreateAnimation({ .AnimationName = "Move_Attak_Straight", .SpriteName = "Move_Attak_Straight", .FrameInter = 0.04f });
		RenderPtr->CreateAnimation({ .AnimationName = "DuckAttack", .SpriteName = "DuckAttack", .FrameInter = 0.05f });
		RenderPtr->CreateAnimation({ .AnimationName = "Hold_Shoot_DiagonalDown", .SpriteName = "Hold_Shoot_DiagonalDown", .FrameInter = 0.05f });
		RenderPtr->CreateAnimation({ .AnimationName = "Hold_Shoot_DiagonalUp", .SpriteName = "Hold_Shoot_DiagonalUp", .FrameInter = 0.05f });
		RenderPtr->CreateAnimation({ .AnimationName = "Hold_Shoot_Down", .SpriteName = "Hold_Shoot_Down", .FrameInter = 0.05f });
		RenderPtr->CreateAnimation({ .AnimationName = "Hold_Shoot_Straight", .SpriteName = "Hold_Shoot_Straight", .FrameInter = 0.05f });
		RenderPtr->CreateAnimation({ .AnimationName = "Hold_Shoot_Up", .SpriteName = "Hold_Shoot_Up", .FrameInter = 0.05f });

		// EX
		RenderPtr->CreateAnimation({ .AnimationName = "AirEx_DiagonalDown", .SpriteName = "AirEX_DiagonalDown", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "AirEx_DiagonalUp", .SpriteName = "AirEx_DiagonalUp", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "AirEx_Down", .SpriteName = "AirEx_Down", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "AirEx_Straight", .SpriteName = "AirEx_Straight", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "AirEx_Up", .SpriteName = "AirEx_Up", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ex_DiagonalDown", .SpriteName = "Ex_DiagonalDown", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ex_DiagonalUp", .SpriteName = "Ex_DiagonalUp", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ex_Down", .SpriteName = "Ex_Down", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ex_Straight", .SpriteName = "Ex_Straight", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ex_Up", .SpriteName = "Ex_Up", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

		// Interaction & Intro
		RenderPtr->CreateAnimation({ .AnimationName = "ElderKettleInteraction", .SpriteName = "ElderKettleInteraction", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Intro_Flex", .SpriteName = "Intro_Flex", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Intro_Regular", .SpriteName = "Intro_Regular", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Portal", .SpriteName = "Portal", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
	}

	if (nullptr != PeashooterRenderPtr)
	{
		PeashooterRenderPtr->CreateAnimation({ "Peashooter_Spawn", "Peashooter_Spawn.png", 0, 3, 0.05f, true, false });
		PeashooterRenderPtr->CreateAnimation({ "Spread_Spawn", "Spread_Spawn.png", 0, 3, 0.05f, true, false });
	}

	if (nullptr != ChargeUpRenderPtr)
	{
		ChargeUpRenderPtr->CreateAnimation({ .AnimationName = "EX_ChargeUp", .SpriteName = "EX_ChargeUp", .FrameInter = 0.05f, .ScaleToTexture = true });
	}

	// Setting
	if (nullptr != RenderPtr)
	{
		RenderPtr->GetTransform()->SetLocalPosition({ 0, 90 });
		RenderPtr->ChangeAnimation("Idle");
	}

	if (nullptr != PeashooterRenderPtr)
	{
		PeashooterRenderPtr->GetTransform()->SetLocalScale(float4{ 300, 300 });
		PeashooterRenderPtr->GetTransform()->SetLocalPosition(float4{ 100, 40 });
		PeashooterRenderPtr->ChangeAnimation("Peashooter_Spawn");
		PeashooterRenderPtr->Off();
	}
}

void Player::DebugRendererSetting()
{
	if (nullptr == DebugRenderPtr0)
	{
		DebugRenderPtr0 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr0->SetScaleToTexture("RedDot.png");
	}
	if (nullptr == DebugRenderPtr1)
	{
		DebugRenderPtr1 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr1->SetScaleToTexture("RedDot.png");
	}
	if (nullptr == DebugRenderPtr2)
	{
		DebugRenderPtr2 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr2->SetScaleToTexture("RedDot.png");
	}
	if (nullptr == DebugRenderPtr3)
	{
		DebugRenderPtr3 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr3->SetScaleToTexture("RedDot.png");
	}
	if (nullptr == DebugRenderPtr4)
	{
		DebugRenderPtr4 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr4->SetScaleToTexture("RedDot.png");
	}
	if (nullptr == DebugRenderPtr5)
	{
		DebugRenderPtr5 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr5->SetScaleToTexture("RedDot.png");
	}
	
	if (nullptr != DebugRenderPtr1
		&& nullptr != DebugRenderPtr2
		&& nullptr != DebugRenderPtr3
		&& nullptr != DebugRenderPtr4
		&& nullptr != DebugRenderPtr5)
	{
		DebugRenderPtr1->GetTransform()->SetLocalPosition({ -25, 10 }); // 왼쪽 벽
		DebugRenderPtr2->GetTransform()->SetLocalPosition({ 15, 10 });  // 오른쪽 벽
		DebugRenderPtr1->GetTransform()->SetLocalPosition({ -25, -2 }); // 왼쪽 낙하
		DebugRenderPtr2->GetTransform()->SetLocalPosition({ 15, -2 });  // 오른쪽 낙하
		DebugRenderPtr5->GetTransform()->SetLocalPosition({ 0, 0 });    // 플레이어 위치

		DebugRenderPtr1->Off();
		DebugRenderPtr2->Off();
		DebugRenderPtr3->Off();
		DebugRenderPtr4->Off();
		DebugRenderPtr5->Off();
	}
}

void Player::PlayerCollisionSetting()
{
	if (nullptr == BodyCollisionPtr)
	{
		BodyCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Player));
		BodyCollisionPtr->GetTransform()->SetLocalScale({ 90, 120, 1 });
		BodyCollisionPtr->GetTransform()->SetLocalPosition({ -5, 60 });
	}

	if (nullptr == StandCollisionPtr)
	{
		StandCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::PlayerSensor));
		StandCollisionPtr->GetTransform()->SetLocalScale({ 66, 10 });
		StandCollisionPtr->GetTransform()->SetLocalPosition({ -7, 5 });
	}

	if (nullptr == BottomSensorCollisionPtr)
	{
		BottomSensorCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::PlayerSensor));
		BottomSensorCollisionPtr->GetTransform()->SetLocalScale({ 30, -6 });
		BottomSensorCollisionPtr->GetTransform()->SetLocalPosition({ -7, -3 });
	}

	if (nullptr == FrontSensorCollisionPtr)
	{
		FrontSensorCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::PlayerSensor));
		FrontSensorCollisionPtr->GetTransform()->SetLocalScale({ 8, 100 });
		FrontSensorCollisionPtr->GetTransform()->SetLocalPosition({ 40, 50 });
	}

	if (nullptr == ParryCollisionPtr)
	{
		ParryCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::PlayerSensor));
		ParryCollisionPtr->GetTransform()->SetLocalScale({ 90, 80, 1 });
		ParryCollisionPtr->GetTransform()->SetLocalPosition({ -5, 80 });
		ParryCollisionPtr->Off();
	}

	if (nullptr == BodyCollisionRenderPtr)
	{
		BodyCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BodyCollisionRenderPtr->GetTransform()->SetLocalScale(BodyCollisionPtr->GetTransform()->GetLocalScale());
		BodyCollisionRenderPtr->GetTransform()->SetLocalPosition(BodyCollisionPtr->GetTransform()->GetLocalPosition());
		BodyCollisionRenderPtr->SetTexture("GreenLine.png");
		BodyCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
	}

	if (nullptr == StandCollisionRenderPtr)
	{
		StandCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		StandCollisionRenderPtr->GetTransform()->SetLocalScale(StandCollisionPtr->GetTransform()->GetLocalScale());
		StandCollisionRenderPtr->GetTransform()->SetLocalPosition(StandCollisionPtr->GetTransform()->GetLocalPosition());
		StandCollisionRenderPtr->SetTexture("BlueBox.png");
		StandCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
	}

	if (nullptr == BottomSensorCollisionRenderPtr)
	{
		BottomSensorCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BottomSensorCollisionRenderPtr->GetTransform()->SetLocalScale(BottomSensorCollisionPtr->GetTransform()->GetLocalScale());
		BottomSensorCollisionRenderPtr->GetTransform()->SetLocalPosition(BottomSensorCollisionPtr->GetTransform()->GetLocalPosition());
		BottomSensorCollisionRenderPtr->SetTexture("RedBox.png");
		BottomSensorCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
	}

	if (nullptr == FrontSensorCollisionRenderPtr)
	{
		FrontSensorCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		FrontSensorCollisionRenderPtr->GetTransform()->SetLocalScale(FrontSensorCollisionPtr->GetTransform()->GetLocalScale());
		FrontSensorCollisionRenderPtr->GetTransform()->SetLocalPosition(FrontSensorCollisionPtr->GetTransform()->GetLocalPosition());
		FrontSensorCollisionRenderPtr->SetTexture("GreenBox.png");
		FrontSensorCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
	}

	if (nullptr == ParryCollisionRenderPtr)
	{
		ParryCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ParryCollisionRenderPtr->GetTransform()->SetLocalScale(ParryCollisionPtr->GetTransform()->GetLocalScale());
		ParryCollisionRenderPtr->GetTransform()->SetLocalPosition(ParryCollisionPtr->GetTransform()->GetLocalPosition());
		ParryCollisionRenderPtr->SetTexture("RedLine.png");
		ParryCollisionRenderPtr->Off();
	}
}
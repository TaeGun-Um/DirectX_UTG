#include "PrecompileHeader.h"
#include "Player_Overworld.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "MoveDust.h"

Player_Overworld* Player_Overworld::MainPlayer = nullptr;

Player_Overworld::Player_Overworld() 
{
}

Player_Overworld::~Player_Overworld() 
{
}

void Player_Overworld::Start()
{
	MainPlayer = this;

	PlayerInitialSetting();
	DebugRendererSetting();
	PlayerCollisionSetting();
	SetCameraFollowType(CameraFollowType::Overworld);
	SetPlayerMoveSpeed(250.0f);
}
void Player_Overworld::Update(float _DeltaTime)
{
	MoveCamera(_DeltaTime);

	MoveAbleTime += _DeltaTime;

	if (MoveAbleTime <= 0.5f)
	{
		return;
	}

	CheatKey();

	DirectCheck();
	CollisionCheck(_DeltaTime);
	PixelCheck(_DeltaTime);
	UpdateState(_DeltaTime);
	CreateMoveDust();
	PlayerDebugRenderer();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     AssistFunction                       //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player_Overworld::WinFSMSetting()
{
	WinSetting = true;
	Directbool = true;
	EnterMessageRenderPtr->GetTransform()->SetLocalPositiveScaleX();
	ADValue = AttackDirection::Right_Down;
	RenderPtr->ChangeAnimation("Down_Idle", false);
}

void Player_Overworld::InitReset()
{
	MoveAbleTime = 0.0f;
	IsPortaling = false;
	CollisionPtr->On();
}

void Player_Overworld::CheatKey()
{
	if (true == GameEngineInput::IsDown("SpeedUp"))
	{
		IsSpeedUp = !IsSpeedUp;
	}

	if (true == IsSpeedUp)
	{
		SetPlayerMoveSpeed(700.0f);
	}
	else
	{
		SetPlayerMoveSpeed(250.0f);
	}
}

void Player_Overworld::PlayerDebugRenderer()
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
		DebugRenderPtr7->On();
		DebugRenderPtr8->On();
		CollisionRenderPtr->On();
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
		DebugRenderPtr7->Off();
		DebugRenderPtr8->Off();
		CollisionRenderPtr->Off();
	}
}

void Player_Overworld::EnterMessageScaleUp(float _DeltaTime)
{
	ScaleCheckStart = true;
	ScaleMinTime = 0.0f;
	EnterMessageRenderPtr->On();
	ScaleCount = 1;

	ScaleMaxTime += _DeltaTime;

	float4 Scale = float4::LerpClamp(EnterMessageRenderMinScale, EnterMessageRenderMaxScale, ScaleMaxTime * 5.5f);

	EnterMessageRenderPtr->GetTransform()->SetLocalScale(Scale);

	if (true == Directbool)
	{
		EnterMessageRenderPtr->GetTransform()->SetLocalPositiveScaleX();
	}
	else
	{
		EnterMessageRenderPtr->GetTransform()->SetLocalNegativeScaleX();
	}
}

void Player_Overworld::EnterMessageScaleDown(float _DeltaTime)
{
	if (false == ScaleCheckStart)
	{
		return;
	}

	ScaleMaxTime = 0.0f;
	EnterMessageRenderPtr->On();

	ScaleMinTime += _DeltaTime;

	if (1 == ScaleCount)
	{
		ScaleCount = 0;
		EnterMessageRenderDelayScale = EnterMessageRenderMaxScale * 1.35f;
	}

	float4 Scale = float4::LerpClamp(EnterMessageRenderDelayScale, EnterMessageRenderMinScale, ScaleMinTime * 5.f);

	EnterMessageRenderPtr->GetTransform()->SetLocalScale(Scale);

	if (EnterMessageRenderMinScale == EnterMessageRenderPtr->GetTransform()->GetLocalScale())
	{
		EnterMessageRenderPtr->Off();
	}

	if (true == Directbool)
	{
		EnterMessageRenderPtr->GetTransform()->SetLocalPositiveScaleX();
	}
	else
	{
		EnterMessageRenderPtr->GetTransform()->SetLocalNegativeScaleX();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                   CollisionCheck                     //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player_Overworld::CollisionCheck(float _DeltaTime)
{
	if (true == IsPortaling)
	{
		EnterMessageScaleDown(_DeltaTime);
		return;
	}

	if (nullptr != CollisionPtr->Collision(static_cast<int>(CollisionOrder::NPC), ColType::AABBBOX2D, ColType::AABBBOX2D)
		|| nullptr != CollisionPtr->Collision(static_cast<int>(CollisionOrder::Building), ColType::AABBBOX2D, ColType::AABBBOX2D)
		&& true == IsCollisionOn)
	{
		EnterMessageScaleUp(_DeltaTime);
	}
	else
	{
		EnterMessageScaleDown(_DeltaTime);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                       PixelCheck                         //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player_Overworld::PixelCheck(float _DeltaTime)
{
	// 낙하 체크
	float4 PlayerPos = GetTransform()->GetLocalPosition();

	float4 LeftUpPos = PlayerPos + float4{ -10, 10 };
	float4 RightUpPos = PlayerPos + float4{ 10, 10 };
	float4 RightDownPos = PlayerPos + float4{ 10, -10 };
	float4 LeftDownPos = PlayerPos + float4{ -10, -10 };

	float4 LeftPos = PlayerPos + float4{ -10, 0 };
	float4 RightPos = PlayerPos + float4{ 10, 0 };
	float4 UpPos = PlayerPos + float4{ 0, 10 };
	float4 DownPos = PlayerPos + float4{ 0, -10 };

	GameEnginePixelColor LeftUpPixel = PixelCollisionCheck.PixelCheck(LeftUpPos);
	GameEnginePixelColor RightUpPixel = PixelCollisionCheck.PixelCheck(RightUpPos);
	GameEnginePixelColor RightDownPixel = PixelCollisionCheck.PixelCheck(RightDownPos);
	GameEnginePixelColor LeftDownPixel = PixelCollisionCheck.PixelCheck(LeftDownPos);

	GameEnginePixelColor LeftPixel = PixelCollisionCheck.PixelCheck(LeftPos);
	GameEnginePixelColor RightPixel = PixelCollisionCheck.PixelCheck(RightPos);
	GameEnginePixelColor UpPixel = PixelCollisionCheck.PixelCheck(UpPos);
	GameEnginePixelColor DownPixel = PixelCollisionCheck.PixelCheck(DownPos);

	float4 LeftUp_DD = float4{ 10, -10 }.NormalizeReturn();
	float4 RightUp_DD = float4{ -10, -10 }.NormalizeReturn();
	float4 RightDown_DD = float4{ -10, 10 }.NormalizeReturn();
	float4 LeftDown_DD = float4{ 10, 10 }.NormalizeReturn();

	float4 Left_B = float4{ 10, 0 }.NormalizeReturn();
	float4 Right_B = float4{ -10, 0 }.NormalizeReturn();
	float4 Up_B = float4{ 0, -10 }.NormalizeReturn();
	float4 Down_B = float4{ 0, 10 }.NormalizeReturn();

	float Speed = (MoveSpeed) * _DeltaTime;

	LUD = LeftUp_DD * Speed;
	RUD = RightUp_DD * Speed;
	RDD = RightDown_DD * Speed;
	LDD = LeftDown_DD * Speed;

	LD = Left_B * Speed;
	RD = Right_B * Speed;
	UD = Up_B * Speed;
	DD = Down_B * Speed;

	if (AttackDirection::Right_DiagonalUp == ADValue)
	{
		if (true == PixelCollisionCheck.IsBlack(UpPixel)
			&& true == PixelCollisionCheck.IsBlack(RightPixel))
		{
			GetTransform()->AddLocalPosition(RUD);
		}
		else if (true == PixelCollisionCheck.IsBlack(UpPixel))
		{
			GetTransform()->AddLocalPosition(float4{ 0, -Speed });
		}
		else if (true == PixelCollisionCheck.IsBlack(RightPixel))
		{
			GetTransform()->AddLocalPosition(float4{ -Speed, 0 });
		}
	}
	else if (AttackDirection::Right_DiagonalDown == ADValue)
	{
		if (true == PixelCollisionCheck.IsBlack(DownPixel)
			&& true == PixelCollisionCheck.IsBlack(RightPixel))
		{
			GetTransform()->AddLocalPosition(RDD);
		}
		else if (true == PixelCollisionCheck.IsBlack(DownPixel))
		{
			GetTransform()->AddLocalPosition(float4{ 0, Speed });
		}
		else if (true == PixelCollisionCheck.IsBlack(RightPixel))
		{
			GetTransform()->AddLocalPosition(float4{ -Speed, 0 });
		}
	}
	else if (AttackDirection::Left_DiagonalUp == ADValue)
	{
		if (true == PixelCollisionCheck.IsBlack(UpPixel)
			&& true == PixelCollisionCheck.IsBlack(LeftPixel))
		{
			GetTransform()->AddLocalPosition(LUD);
		}
		else if (true == PixelCollisionCheck.IsBlack(UpPixel))
		{
			GetTransform()->AddLocalPosition(float4{ 0, -Speed });
		}
		else if (true == PixelCollisionCheck.IsBlack(LeftPixel))
		{
			GetTransform()->AddLocalPosition(float4{ Speed, 0 });
		}
	}
	else if (AttackDirection::Left_DiagonalDown == ADValue)
	{
		if (true == PixelCollisionCheck.IsBlack(DownPixel)
			&& true == PixelCollisionCheck.IsBlack(LeftPixel))
		{
			GetTransform()->AddLocalPosition(LDD);
		}
		else if (true == PixelCollisionCheck.IsBlack(DownPixel))
		{
			GetTransform()->AddLocalPosition(float4{ 0, Speed });
		}
		else if (true == PixelCollisionCheck.IsBlack(LeftPixel))
		{
			GetTransform()->AddLocalPosition(float4{ Speed, 0 });
		}
	}
	else if (AttackDirection::Right_Up == ADValue || AttackDirection::Left_Up == ADValue)
	{
		if (true == PixelCollisionCheck.IsBlack(LeftUpPixel)
			&& true == PixelCollisionCheck.IsBlack(RightUpPixel))
		{
			GetTransform()->AddLocalPosition(float4{0, -Speed});
		}
		else if (true == PixelCollisionCheck.IsBlack(LeftUpPixel))
		{
			GetTransform()->AddLocalPosition(LUD);
		}
		else if (true == PixelCollisionCheck.IsBlack(RightUpPixel))
		{
			GetTransform()->AddLocalPosition(RUD);
		}
	}
	else if (AttackDirection::Right_Down == ADValue || AttackDirection::Left_Down == ADValue)
	{
		if (true == PixelCollisionCheck.IsBlack(RightDownPixel)
			&& true == PixelCollisionCheck.IsBlack(LeftDownPixel))
		{
			GetTransform()->AddLocalPosition(float4{ 0, Speed });
		}
		else if (true == PixelCollisionCheck.IsBlack(RightDownPixel))
		{
			GetTransform()->AddLocalPosition(RDD);
		}
		else if (true == PixelCollisionCheck.IsBlack(LeftDownPixel))
		{
			GetTransform()->AddLocalPosition(LDD);
		}
	}
	else if (AttackDirection::Right_Front == ADValue)
	{
		if (true == PixelCollisionCheck.IsBlack(RightUpPixel)
			&& true == PixelCollisionCheck.IsBlack(RightDownPixel))
		{
			GetTransform()->AddLocalPosition(float4{ -Speed, 0 });
		}
		else if (true == PixelCollisionCheck.IsBlack(RightUpPixel))
		{
			GetTransform()->AddLocalPosition(RUD);
		}
		else if (true == PixelCollisionCheck.IsBlack(RightDownPixel))
		{
			GetTransform()->AddLocalPosition(RDD);
		}
	}
	else if (AttackDirection::Left_Front == ADValue)
	{
		if (true == PixelCollisionCheck.IsBlack(LeftUpPixel)
			&& true == PixelCollisionCheck.IsBlack(LeftDownPixel))
		{
			GetTransform()->AddLocalPosition(float4{ Speed, 0 });
		}
		else if (true == PixelCollisionCheck.IsBlack(LeftUpPixel))
		{
			GetTransform()->AddLocalPosition(LUD);
		}
		else if (true == PixelCollisionCheck.IsBlack(LeftDownPixel))
		{
			GetTransform()->AddLocalPosition(LDD);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     CreateActor                   /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player_Overworld::CreateMoveDust()
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
		DustPosition += float4{ 0, 35 };

	}
	else if (1 == RandValue)
	{
		DustPosition += float4{ 0, 40 };
	}
	else if (2 == RandValue)
	{
		DustPosition += float4{ 0, 45 };
	}

	if (true == Directbool)
	{
		DustPosition += float4{ -20, 0 };
	}
	else
	{
		DustPosition += float4{ 20, 0 };
	}

	DustPosition += float4{ 0, 0, 1 };

	Dust->SetStartPosition(DustPosition);
	Dust->SetDirection(Directbool);
	Dust->SetDustType(static_cast<DustType>(RandValue));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                         FSM                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player_Overworld::DirectCheck()
{
	if (true == IsWin || true ==  IsPortaling)
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
	}
	else
	{
		GetTransform()->SetLocalNegativeScaleX();
	}

	MoveDirectCheck();
}

void Player_Overworld::MoveDirectCheck()
{
	if (true == IsWin || true == IsPortaling)
	{
		return;
	}

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

void Player_Overworld::ChangeState(OverworldState _StateValue)
{
	OverworldState NextState = _StateValue;
	OverworldState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case OverworldState::Idle:
		IdleStart();
		break;
	case OverworldState::Move:
		MoveStart();
		break;
	case OverworldState::Portal:
		PortalStart();
		break;
	case OverworldState::Win:
		WinStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case OverworldState::Idle:
		IdleEnd();
		break;
	case OverworldState::Move:
		MoveEnd();
		break;
	case OverworldState::Portal:
		PortalEnd();
		break;
	case OverworldState::Win:
		WinEnd();
		break;
	default:
		break;
	}
}

void Player_Overworld::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case OverworldState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	case OverworldState::Move:
		MoveUpdate(_DeltaTime);
		break;
	case OverworldState::Portal:
		PortalUpdate(_DeltaTime);
		break;
	case OverworldState::Win:
		WinUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Player_Overworld::IdleStart()
{
	IsIdle = true;
}
void Player_Overworld::IdleUpdate(float _DeltaTime)
{
	if (true == WinSetting)
	{
		ChangeState(OverworldState::Win);
		return;
	}

	if (true == IsPortaling)
	{
		ChangeState(OverworldState::Portal);
		return;
	}

	switch (ADValue)
	{
	case AttackDirection::Right_Up:
	{
		RenderPtr->ChangeAnimation("Up_Idle", false);
	}
	break;
	case AttackDirection::Right_DiagonalUp:
	{
		RenderPtr->ChangeAnimation("DU_Idle", false);
	}
	break;
	case AttackDirection::Right_Front:
	{
		RenderPtr->ChangeAnimation("Side_Idle", false);
	}
	break;
	case AttackDirection::Right_DiagonalDown:
	{
		RenderPtr->ChangeAnimation("DD_Idle", false);
	}
	break;
	case AttackDirection::Right_Down:
	{
		RenderPtr->ChangeAnimation("Down_Idle", false);
	}
	break;
	case AttackDirection::Left_Up:
	{
		RenderPtr->ChangeAnimation("Up_Idle", false);
	}
	break;
	case AttackDirection::Left_DiagonalUp:
	{
		RenderPtr->ChangeAnimation("DU_Idle", false);
	}
	break;
	case AttackDirection::Left_Front:
	{
		RenderPtr->ChangeAnimation("Side_Idle", false);
	}
	break;
	case AttackDirection::Left_DiagonalDown:
	{
		RenderPtr->ChangeAnimation("DD_Idle", false);
	}
	break;
	case AttackDirection::Left_Down:
	{
		RenderPtr->ChangeAnimation("Down_Idle", false);
	}
	break;
	default:
		break;
	}

	if (true == GameEngineInput::IsPress("MoveUp")
		|| true == GameEngineInput::IsPress("MoveDown")
		|| true == GameEngineInput::IsPress("MoveRight")
		|| true == GameEngineInput::IsPress("MoveLeft"))
	{
		ChangeState(OverworldState::Move);
		return;
	}
}
void Player_Overworld::IdleEnd()
{
	IsIdle = false;
}

void Player_Overworld::MoveStart()
{
}
void Player_Overworld::MoveUpdate(float _DeltaTime)
{
	if (true == WinSetting)
	{
		ChangeState(OverworldState::Win);
		return;
	}

	if (true == IsPortaling)
	{
		ChangeState(OverworldState::Portal);
		return;
	}

	MoveTime += _DeltaTime;

	switch (ADValue)
	{
	case AttackDirection::Right_Up:
	{
		RenderPtr->ChangeAnimation("Up_Move", false);
	}
	break;
	case AttackDirection::Right_DiagonalUp:
	{
		RenderPtr->ChangeAnimation("DU_Move", false);
	}
	break;
	case AttackDirection::Right_Front:
	{
		RenderPtr->ChangeAnimation("Side_Move", false);
	}
	break;
	case AttackDirection::Right_DiagonalDown:
	{
		RenderPtr->ChangeAnimation("DD_Move", false);
	}
	break;
	case AttackDirection::Right_Down:
	{
		RenderPtr->ChangeAnimation("Down_Move", false);
	}
	break;
	case AttackDirection::Left_Up:
	{
		RenderPtr->ChangeAnimation("Up_Move", false);
	}
	break;
	case AttackDirection::Left_DiagonalUp:
	{
		RenderPtr->ChangeAnimation("DU_Move", false);
	}
	break;
	case AttackDirection::Left_Front:
	{
		RenderPtr->ChangeAnimation("Side_Move", false);
	}
	break;
	case AttackDirection::Left_DiagonalDown:
	{
		RenderPtr->ChangeAnimation("DD_Move", false);
	}
	break;
	case AttackDirection::Left_Down:
	{
		RenderPtr->ChangeAnimation("Down_Move", false);
	}
	break;
	default:
		break;
	}

	float MoveDis = MoveSpeed * _DeltaTime;

	if (true == GameEngineInput::IsPress("MoveUp") && true == GameEngineInput::IsPress("MoveRight"))
	{
		float4 MoveDis4 = { MoveDis, MoveDis };
		float4 MoveNormal = MoveDis4.NormalizeReturn();

		GetTransform()->AddLocalPosition(MoveNormal * MoveSpeed * _DeltaTime);
	}
	else if (true == GameEngineInput::IsPress("MoveDown") && true == GameEngineInput::IsPress("MoveRight"))
	{
		float4 MoveDis4 = { MoveDis, -MoveDis };
		float4 MoveNormal = MoveDis4.NormalizeReturn();

		GetTransform()->AddLocalPosition(MoveNormal * MoveSpeed * _DeltaTime);
	}
	else if (true == GameEngineInput::IsPress("MoveUp") && true == GameEngineInput::IsPress("MoveLeft"))
	{
		float4 MoveDis4 = { -MoveDis, MoveDis };
		float4 MoveNormal = MoveDis4.NormalizeReturn();

		GetTransform()->AddLocalPosition(MoveNormal * MoveSpeed * _DeltaTime);
	}
	else if (true == GameEngineInput::IsPress("MoveDown") && true == GameEngineInput::IsPress("MoveLeft"))
	{
		float4 MoveDis4 = { -MoveDis, -MoveDis };
		float4 MoveNormal = MoveDis4.NormalizeReturn();

		GetTransform()->AddLocalPosition(MoveNormal * MoveSpeed * _DeltaTime);
	}
	else if (true == GameEngineInput::IsPress("MoveUp"))
	{
		float4 MoveDis4 = { 0, MoveDis };
		float4 MoveNormal = MoveDis4.NormalizeReturn();

		GetTransform()->AddLocalPosition(MoveNormal * MoveSpeed * _DeltaTime);
	}
	else if (true == GameEngineInput::IsPress("MoveRight"))
	{
		float4 MoveDis4 = { MoveDis, 0 };
		float4 MoveNormal = MoveDis4.NormalizeReturn();

		GetTransform()->AddLocalPosition(MoveNormal * MoveSpeed * _DeltaTime);
	}
	else if (true == GameEngineInput::IsPress("MoveLeft"))
	{
		float4 MoveDis4 = { -MoveDis, 0 };
		float4 MoveNormal = MoveDis4.NormalizeReturn();

		GetTransform()->AddLocalPosition(MoveNormal* MoveSpeed* _DeltaTime);
	}
	else if (true == GameEngineInput::IsPress("MoveDown"))
	{
		float4 MoveDis4 = { 0, -MoveDis };
		float4 MoveNormal = MoveDis4.NormalizeReturn();

		GetTransform()->AddLocalPosition(MoveNormal* MoveSpeed* _DeltaTime);
	}

	if (false == GameEngineInput::IsPress("MoveUp")
		&& false == GameEngineInput::IsPress("MoveDown")
		&& false == GameEngineInput::IsPress("MoveRight")
		&& false == GameEngineInput::IsPress("MoveLeft"))
	{
		ChangeState(OverworldState::Idle);
		return;
	}
}
void Player_Overworld::MoveEnd()
{
	MoveTime = 0.0f;
}

void Player_Overworld::PortalStart() 
{

}
void Player_Overworld::PortalUpdate(float _DeltaTime)
{
	if (false == IsPortaling)
	{
		ChangeState(OverworldState::Idle);
		return;
	}

	if (true == WinSetting)
	{
		ChangeState(OverworldState::Win);
		return;
	}

	switch (ADValue)
	{
	case AttackDirection::Right_Up:
	{
		RenderPtr->ChangeAnimation("Up_Idle", false);
	}
	break;
	case AttackDirection::Right_DiagonalUp:
	{
		RenderPtr->ChangeAnimation("DU_Idle", false);
	}
	break;
	case AttackDirection::Right_Front:
	{
		RenderPtr->ChangeAnimation("Side_Idle", false);
	}
	break;
	case AttackDirection::Right_DiagonalDown:
	{
		RenderPtr->ChangeAnimation("DD_Idle", false);
	}
	break;
	case AttackDirection::Right_Down:
	{
		RenderPtr->ChangeAnimation("Down_Idle", false);
	}
	break;
	case AttackDirection::Left_Up:
	{
		RenderPtr->ChangeAnimation("Up_Idle", false);
	}
	break;
	case AttackDirection::Left_DiagonalUp:
	{
		RenderPtr->ChangeAnimation("DU_Idle", false);
	}
	break;
	case AttackDirection::Left_Front:
	{
		RenderPtr->ChangeAnimation("Side_Idle", false);
	}
	break;
	case AttackDirection::Left_DiagonalDown:
	{
		RenderPtr->ChangeAnimation("DD_Idle", false);
	}
	break;
	case AttackDirection::Left_Down:
	{
		RenderPtr->ChangeAnimation("Down_Idle", false);
	}
	break;
	default:
		break;
	}
}
void Player_Overworld::PortalEnd()
{

}

void Player_Overworld::WinStart()
{
	WinSetting = false;
	IsWin = true;
	RenderPtr->ChangeAnimation("InterAction_Win");
}
void Player_Overworld::WinUpdate(float _DeltaTime)
{
	WinTime += _DeltaTime;

	if (true == RenderPtr->IsAnimationEnd() && WinTime >= 2.0f)
	{
		ChangeState(OverworldState::Idle);
		return;
	}
}
void Player_Overworld::WinEnd()
{
	IsWin = false;
	WinTime = 0.0f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////             Init(Animation & Collision)            /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player_Overworld::PlayerInitialSetting()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	
	if (nullptr == GameEngineSprite::Find("DD_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Overworld");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DD_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DD_Move").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Down_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Down_Move").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DU_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DU_Move").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Side_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Side_Move").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Up_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Up_Move").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("InterAction_Win").GetFullPath());
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

	// Idle
	RenderPtr->CreateAnimation({ .AnimationName = "Up_Idle", .SpriteName = "Up_Idle", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "DU_Idle", .SpriteName = "DU_Idle", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "Side_Idle", .SpriteName = "Side_Idle", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "DD_Idle", .SpriteName = "DD_Idle", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "Down_Idle", .SpriteName = "Down_Idle", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
	
	// Move
	RenderPtr->CreateAnimation({ .AnimationName = "Up_Move", .SpriteName = "Up_Move", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "DU_Move", .SpriteName = "DU_Move", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "Side_Move", .SpriteName = "Side_Move", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "DD_Move", .SpriteName = "DD_Move", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "Down_Move", .SpriteName = "Down_Move", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });

	// Win
	RenderPtr->CreateAnimation({ .AnimationName = "InterAction_Win", .SpriteName = "InterAction_Win", .FrameInter = 0.045f, .Loop = true, .ScaleToTexture = true });

	// Setting
	RenderPtr->GetTransform()->SetLocalScale({103, 113});
	RenderPtr->GetTransform()->SetLocalPosition({ 0, 40 });
	RenderPtr->ChangeAnimation("Down_Idle");

	if (nullptr == EnterMessageRenderPtr)
	{
		EnterMessageRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		EnterMessageRenderPtr->SetScaleToTexture("EnterMessage.png");
		EnterMessageRenderMaxScale = EnterMessageRenderPtr->GetTransform()->GetLocalScale();
		EnterMessageRenderPtr->GetTransform()->SetLocalScale(float4{ 1, 1, 1 });
		EnterMessageRenderMinScale = EnterMessageRenderPtr->GetTransform()->GetLocalScale();
		EnterMessageRenderPtr->GetTransform()->SetLocalPosition(RenderPtr->GetTransform()->GetLocalPosition() + float4{ 0, 80, -20 });
		EnterMessageRenderPtr->Off();
	}
}

void Player_Overworld::DebugRendererSetting()
{
	if (nullptr == DebugRenderPtr0)
	{
		DebugRenderPtr0 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr0->SetScaleToTexture("RedDot.png");
	}
	if (nullptr == DebugRenderPtr1)
	{
		DebugRenderPtr1 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr1->SetScaleToTexture("BlueDot.png");
	}
	if (nullptr == DebugRenderPtr2)
	{
		DebugRenderPtr2 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr2->SetScaleToTexture("BlueDot.png");
	}
	if (nullptr == DebugRenderPtr3)
	{
		DebugRenderPtr3 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr3->SetScaleToTexture("BlueDot.png");
	}
	if (nullptr == DebugRenderPtr4)
	{
		DebugRenderPtr4 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr4->SetScaleToTexture("BlueDot.png");
	}

	if (nullptr == DebugRenderPtr5)
	{
		DebugRenderPtr5 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr5->SetScaleToTexture("GreenDot.png");
	}
	if (nullptr == DebugRenderPtr6)
	{
		DebugRenderPtr6 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr6->SetScaleToTexture("GreenDot.png");
	}
	if (nullptr == DebugRenderPtr7)
	{
		DebugRenderPtr7 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr7->SetScaleToTexture("GreenDot.png");
	}
	if (nullptr == DebugRenderPtr8)
	{
		DebugRenderPtr8 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr8->SetScaleToTexture("GreenDot.png");
	}

	if (nullptr != DebugRenderPtr1
		&& nullptr != DebugRenderPtr2
		&& nullptr != DebugRenderPtr3
		&& nullptr != DebugRenderPtr4)
	{
		DebugRenderPtr1->GetTransform()->SetLocalPosition({ -10, 10, -3 });		// 왼쪽 상단
		DebugRenderPtr2->GetTransform()->SetLocalPosition({ 10, 10, -3 });		// 오른쪽 상단
		DebugRenderPtr3->GetTransform()->SetLocalPosition({ 10, -10, -3 });		// 오른쪽 하단
		DebugRenderPtr4->GetTransform()->SetLocalPosition({ -10, -10, -3 });    // 왼쪽 하단
		DebugRenderPtr5->GetTransform()->SetLocalPosition({ -10, 0, -3 });		// 왼쪽
		DebugRenderPtr6->GetTransform()->SetLocalPosition({ 10, 0, -3 });		// 오른쪽
		DebugRenderPtr7->GetTransform()->SetLocalPosition({ 0, 10, -3 });		// 상단
		DebugRenderPtr8->GetTransform()->SetLocalPosition({ 0, -10, -3 });      // 하단

		DebugRenderPtr1->Off();
		DebugRenderPtr2->Off();
		DebugRenderPtr3->Off();
		DebugRenderPtr4->Off();
		DebugRenderPtr5->Off();
		DebugRenderPtr6->Off();
		DebugRenderPtr7->Off();
		DebugRenderPtr8->Off();
	}
}

void Player_Overworld::PlayerCollisionSetting()
{
	if (nullptr == CollisionRenderPtr)
	{
		CollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr == CollisionPtr)
	{
		CollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Player));
		CollisionPtr->SetColType(ColType::AABBBOX2D);
	}

	if (nullptr != CollisionPtr)
	{
		CollisionPtr->GetTransform()->SetLocalScale({ 50, 75, 1 });
		CollisionPtr->GetTransform()->SetLocalPosition({ 0, 25, -17 });
	}

	if (nullptr != CollisionRenderPtr)
	{
		CollisionRenderPtr->SetTexture("GreenLine.png");
		CollisionRenderPtr->GetTransform()->SetLocalScale(CollisionPtr->GetTransform()->GetLocalScale());
		CollisionRenderPtr->GetTransform()->SetLocalPosition(CollisionPtr->GetTransform()->GetLocalPosition());
		CollisionRenderPtr->Off();
	}
}
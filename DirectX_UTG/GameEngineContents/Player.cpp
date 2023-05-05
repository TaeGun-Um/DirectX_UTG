#include "PrecompileHeader.h"
#include "Player.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

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
	RenderPtr = AnimationCreate_Tutorial();
	SetCameraFollowType(CameraFollowType::Field);
	SetMoveSpeed(380.0f);
	ChangeState(PlayerState::Idle);

	// 픽셀체크 디버깅용 닷
	{
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
		DebugRenderPtr5->SetScaleToTexture("RedDot.png");
		DebugRenderPtr6->SetScaleToTexture("RedDot.png");

		DebugRenderPtr1->GetTransform()->SetLocalPosition({ -40, 10 });
		DebugRenderPtr2->GetTransform()->SetLocalPosition({ 25, 10 });
		//DebugRenderPtr3->Off();
		//DebugRenderPtr4->Off();
		//DebugRenderPtr5->Off();
		//DebugRenderPtr6->Off();

		DebugRenderPtr0->Off();
		DebugRenderPtr1->Off();
		DebugRenderPtr2->Off();
		DebugRenderPtr3->Off();
		DebugRenderPtr4->Off();
		DebugRenderPtr5->Off();
		DebugRenderPtr6->Off();
	}
}
void Player::Update(float _DeltaTime)
{
	if (false == IsCorrection)
	{
		PositionCorrection();
		return;
	}

	MoveCamera(_DeltaTime);
	DirectCheck();
	UpdateState(_DeltaTime);
	PixelCheck(_DeltaTime);

	if (true == GameEngineInput::IsDown("Dash"))
	{
		int a = 0;
	}

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

	if (true == PixelCollisionCheck.IsBlack(ColMapPixel))
	{
		IsCorrection = true;
	}

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                         FSM                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::DirectCheck()
{
	if (true == GameEngineInput::IsPress("MoveRight"))
	{
		Directbool = true;
		GetTransform()->SetLocalPositiveScaleX();
		RenderPtr->GetTransform()->SetLocalPosition({ 0, 90 });
		
		{
			DebugRenderPtr1->GetTransform()->SetLocalPosition({ -40, 10 });
			DebugRenderPtr2->GetTransform()->SetLocalPosition({ 25, 10 });
			//DebugRenderPtr3->Off();
			//DebugRenderPtr4->Off();
			//DebugRenderPtr5->Off();
			//DebugRenderPtr6->Off();
		}
	}
	
	if (true == GameEngineInput::IsPress("MoveLeft"))
	{
		Directbool = false;
		GetTransform()->SetLocalNegativeScaleX();
		RenderPtr->GetTransform()->SetLocalPosition({ 10, 90 });

		{
			DebugRenderPtr1->GetTransform()->SetLocalPosition({ -25, 10 });
			DebugRenderPtr2->GetTransform()->SetLocalPosition({ 40, 10 });
			//DebugRenderPtr3->Off();
			//DebugRenderPtr4->Off();
			//DebugRenderPtr5->Off();
			//DebugRenderPtr6->Off();
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
	case PlayerState::Idle:
		IdleStart();
		break;
	case PlayerState::Move:
		MoveStart();
		break;
	case PlayerState::Dash:
		DashStart();
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
	case PlayerState::Attack:
		AttackStart();
		break;
	case PlayerState::RunAttack:
		RunAttackStart();
		break;
	case PlayerState::EXAttack:
		EXAttackStart();
		break;
	case PlayerState::Holding:
		HoldingStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case PlayerState::Idle:
		IdleEnd();
		break;
	case PlayerState::Move:
		MoveEnd();
		break;
	case PlayerState::Dash:
		DashEnd();
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
	case PlayerState::Attack:
		AttackEnd();
		break;
	case PlayerState::RunAttack:
		RunAttackEnd();
		break;
	case PlayerState::EXAttack:
		EXAttackEnd();
		break;
	case PlayerState::Holding:
		HoldingEnd();
		break;
	default:
		break;
	}
}

void Player::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case PlayerState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	case PlayerState::Move:
		MoveUpdate(_DeltaTime);
		break;
	case PlayerState::Dash:
		DashUpdate(_DeltaTime);
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
	case PlayerState::Attack:
		AttackUpdate(_DeltaTime);
		break;
	case PlayerState::RunAttack:
		RunAttackUpdate(_DeltaTime);
		break;
	case PlayerState::EXAttack:
		EXAttackUpdate(_DeltaTime);
		break;
	case PlayerState::Holding:
		HoldingUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Player::IdleStart()
{
	RenderPtr->SetTexture("Ground_Idle_001.png");
	RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
}
void Player::IdleUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("Hold"))
	{
		ChangeState(PlayerState::Holding);
		return;
	}

	if (true == GameEngineInput::IsPress("MoveLeft") && true == GameEngineInput::IsPress("MoveRight"))
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	if (true == GameEngineInput::IsPress("MoveDown"))
	{
		ChangeState(PlayerState::Duck);
		return;
	}

	if (true == GameEngineInput::IsPress("MoveRight") || true == GameEngineInput::IsPress("MoveLeft"))
	{
		ChangeState(PlayerState::Move);
		return;
	}

	if (true == GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::Jump);
		return;
	}
}
void Player::IdleEnd()
{
}

void Player::MoveStart()
{
	RenderPtr->SetTexture("Run_Normal_001.png");
	RenderPtr->GetTransform()->SetLocalScale({ 170, 200, 1 });
}
void Player::MoveUpdate(float _DeltaTime)
{
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

	if (true == GameEngineInput::IsPress("MoveLeft") && true == GameEngineInput::IsPress("MoveRight"))
	{
		ChangeState(PlayerState::Idle);
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

void Player::DashStart()
{
}
void Player::DashUpdate(float _DeltaTime)
{
}
void Player::DashEnd()
{
}

void Player::DuckStart()
{
	RenderPtr->SetTexture("Ground_Duck_001.png");
	RenderPtr->GetTransform()->SetLocalScale({ 220, 220, 1 });
}
void Player::DuckUpdate(float _DeltaTime)
{
	DuckTime += _DeltaTime;

	if (DuckTime >= 0.2f)
	{
		RenderPtr->SetTexture("Ground_Duck_008.png");
	}

	if (false == GameEngineInput::IsPress("MoveDown"))
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}
void Player::DuckEnd()
{
	DuckTime = 0.0f;
}
	 
void Player::JumpStart()
{
	RenderPtr->SetTexture("Ground_Jump_002.png");
	RenderPtr->GetTransform()->SetLocalScale({ 170, 220, 1 });

	if (false == IsJump)
	{
		MoveDirect.y = 900.0f;
		IsJump = true;
	}
}
void Player::JumpUpdate(float _DeltaTime)
{
	JumpTime += _DeltaTime;

	float MoveDis = MoveSpeed * _DeltaTime;

	if (true == GameEngineInput::IsPress("MoveRight"))
	{
		GetTransform()->AddLocalPosition({ MoveDis, 0 });
	}
	if (true == GameEngineInput::IsPress("MoveLeft"))
	{
		GetTransform()->AddLocalPosition({ -MoveDis, 0 });
	}

	if (true == GameEngineInput::IsPress("Jump") && 0.01f <= JumpTime)
	{
		if (0.15f >= JumpTime)
		{
			MoveDirect.y += 2000.0f * _DeltaTime;
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
	JumpTime = 0.0f;
}

void Player::SlapStart()
{
}
void Player::SlapUpdate(float _DeltaTime)
{
}
void Player::SlapEnd()
{
}

void Player::AttackStart()
{
}
void Player::AttackUpdate(float _DeltaTime)
{
}
void Player::AttackEnd()
{
}

void Player::RunAttackStart()
{
}
void Player::RunAttackUpdate(float _DeltaTime)
{
}
void Player::RunAttackEnd()
{
}
	
void Player::EXAttackStart()
{
}
void Player::EXAttackUpdate(float _DeltaTime)
{
}
void Player::EXAttackEnd()
{
}

void Player::HoldingStart()
{
	RenderPtr->SetTexture("Normal_Straight_001.png");
	RenderPtr->GetTransform()->SetLocalScale({ 150, 200, 1 });
}
void Player::HoldingUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("Hold"))
	{
		IsHold = true;

		if (true == GameEngineInput::IsDown("Jump"))
		{
			IsHold = false;
			ChangeState(PlayerState::Jump);
		}

		return;
	}
	else
	{
		IsHold = false;
		ChangeState(PlayerState::Idle);
		return;
	}
}
void Player::HoldingEnd()
{
}
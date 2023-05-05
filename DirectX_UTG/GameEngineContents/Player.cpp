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
	SetMoveSpeed(330.0f);
	ChangeState(PlayerState::Idle);

	// ÇÈ¼¿Ã¼Å© µð¹ö±ë¿ë ´å
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
	MoveCamera(_DeltaTime);
	DirectCheck();
	UpdateState(_DeltaTime);
	PixelCheck();

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
///////////////////////////////////////////                         FSM                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::DirectCheck()
{
	if (true == GameEngineInput::IsDown("MoveRight"))
	{
		Directbool = true;
		GetTransform()->SetLocalPositiveScaleX();
		RenderPtr->GetTransform()->SetLocalPosition({ 0, 90 });
	}
	
	if (true == GameEngineInput::IsDown("MoveLeft"))
	{
		Directbool = false;
		GetTransform()->SetLocalNegativeScaleX();
		RenderPtr->GetTransform()->SetLocalPosition({ 10, 90 });
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

	if (true == GameEngineInput::IsPress("MoveDown"))
	{
		ChangeState(PlayerState::Duck);
		return;
	}

	if (true == GameEngineInput::IsPress("MoveRight"))
	{
		ChangeState(PlayerState::Move);
		return;
	}
	else if (true == GameEngineInput::IsPress("MoveLeft"))
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
		MoveDirect.y = 500.0f;
		IsJump = true;
		IsGravity = true;
	}
}
void Player::JumpUpdate(float _DeltaTime)
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

	if (true == IsJump)
	{
		MoveDirect.y += -1000.0f * _DeltaTime;
		GetTransform()->AddLocalPosition(MoveDirect * _DeltaTime);
	}
	else
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
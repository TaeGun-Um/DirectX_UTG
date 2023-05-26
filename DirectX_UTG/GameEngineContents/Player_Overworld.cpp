#include "PrecompileHeader.h"
#include "Player_Overworld.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

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
	SetPlayerMoveSpeed(230.0f); // 230
}
void Player_Overworld::Update(float _DeltaTime)
{
	MoveCamera(_DeltaTime);
	DirectCheck();
	PixelCheck(_DeltaTime);
	UpdateState(_DeltaTime);
	PlayerDebugRenderer();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     AssistFunction                       //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
///////////////////////////////////////////                         FSM                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player_Overworld::DirectCheck()
{
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
	case OverworldState::Win:
		WinUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Player_Overworld::IdleStart()
{
}
void Player_Overworld::IdleUpdate(float _DeltaTime)
{
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
}

void Player_Overworld::MoveStart()
{
}
void Player_Overworld::MoveUpdate(float _DeltaTime)
{
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
}

void Player_Overworld::WinStart()
{

}
void Player_Overworld::WinUpdate(float _DeltaTime)
{

}
void Player_Overworld::WinEnd()
{

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
	
	if (nullptr == GameEngineSprite::Find("DashDust"))
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

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DashDust").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Overworld"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Overworld");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Overworld.png").GetFullPath(), 16, 8);
	}

	// Idle
	RenderPtr->CreateAnimation({ "Up_Idle", "Overworld.png", 0, 3, 0.1f, true});
	RenderPtr->CreateAnimation({ "DU_Idle", "Overworld.png", 16, 18, 0.1f, true});
	RenderPtr->CreateAnimation({ "Side_Idle", "Overworld.png", 32, 37, 0.1f, true});
	RenderPtr->CreateAnimation({ "DD_Idle", "Overworld.png", 64, 67, 0.1f, true});
	RenderPtr->CreateAnimation({ "Down_Idle", "Overworld.png", 80, 82, 0.1f, true});

	// Move
	RenderPtr->CreateAnimation({ "Up_Move", "Overworld.png", 4, 15, 0.07f, true, false });
	RenderPtr->CreateAnimation({ "DU_Move", "Overworld.png", 19, 30, 0.07f, true, false });
	RenderPtr->CreateAnimation({ "Side_Move", "Overworld.png", 51, 61, 0.07f, true, false });
	RenderPtr->CreateAnimation({ "DD_Move", "Overworld.png", 68, 79, 0.07f, true, false });
	RenderPtr->CreateAnimation({ "Down_Move", "Overworld.png", 96, 108, 0.07f, true, false });

	// Setting
	RenderPtr->GetTransform()->SetLocalScale({103, 113});
	RenderPtr->GetTransform()->SetLocalPosition({ 0, 30 });
	RenderPtr->ChangeAnimation("Down_Idle");
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
	}
}
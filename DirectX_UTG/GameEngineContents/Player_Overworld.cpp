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
	PlayerInitialSetting();
	DebugRendererSetting();
	SetCameraFollowType(CameraFollowType::Overworld);
	SetPlayerMoveSpeed(230.0f);
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
	}
	else
	{
		DebugRenderPtr0->Off();
		DebugRenderPtr1->Off();
		DebugRenderPtr2->Off();
		DebugRenderPtr3->Off();
		DebugRenderPtr4->Off();
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

	GameEnginePixelColor LeftUpPixel = PixelCollisionCheck.PixelCheck(LeftUpPos);
	GameEnginePixelColor RightUpPixel = PixelCollisionCheck.PixelCheck(RightUpPos);
	GameEnginePixelColor RightDownPixel = PixelCollisionCheck.PixelCheck(RightDownPos);
	GameEnginePixelColor LeftDownPixel = PixelCollisionCheck.PixelCheck(LeftDownPos);

	float4 LeftUp_DD = float4{ 10, -10 }.NormalizeReturn();
	float4 RightUp_DD = float4{ -10, -10 }.NormalizeReturn();
	float4 RightDown_DD = float4{ -10, 10 }.NormalizeReturn();
	float4 LeftDown_DD = float4{ 10, 10 }.NormalizeReturn();

	float Speed = (MoveSpeed) * _DeltaTime;

	LUD = LeftUp_DD * Speed;
	RUD = RightUp_DD * Speed;
	RDD = RightDown_DD * Speed;
	LDD = LeftDown_DD * Speed;

	if (AttackDirection::Right_DiagonalUp == ADValue)
	{
		if (true == PixelCollisionCheck.IsBlack(RightUpPixel))
		{
			GetTransform()->AddLocalPosition(RUD);
		}
	}
	else if (AttackDirection::Right_DiagonalDown == ADValue)
	{
		if (true == PixelCollisionCheck.IsBlack(RightDownPixel))
		{
			GetTransform()->AddLocalPosition(RDD);
		}
	}
	else if (AttackDirection::Left_DiagonalUp == ADValue)
	{
		if (true == PixelCollisionCheck.IsBlack(LeftUpPixel))
		{
			GetTransform()->AddLocalPosition(LUD);
		}
	}
	else if (AttackDirection::Left_DiagonalDown == ADValue)
	{
		if (true == PixelCollisionCheck.IsBlack(LeftDownPixel))
		{
			GetTransform()->AddLocalPosition(LDD);
		}
	}
	if (AttackDirection::Right_Up == ADValue || AttackDirection::Left_Up == ADValue)
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
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

	if (nullptr == GameEngineSprite::Find("Up_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Overworld");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Up_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DU_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Side_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DD_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Down_Idle").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Up_Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DU_Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Side_Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DD_Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Down_Move").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("InterAction_Win").GetFullPath());
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

	// Idle
	RenderPtr->CreateAnimation({ .AnimationName = "Up_Idle", .SpriteName = "Up_Idle", .FrameInter = 0.07f, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "DU_Idle", .SpriteName = "DU_Idle", .FrameInter = 0.07f, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "Side_Idle", .SpriteName = "Side_Idle", .FrameInter = 0.07f, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "DD_Idle", .SpriteName = "DD_Idle", .FrameInter = 0.07f, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "Down_Idle", .SpriteName = "Down_Idle", .FrameInter = 0.07f, .ScaleToTexture = true });

	// Move
	RenderPtr->CreateAnimation({ .AnimationName = "Up_Move", .SpriteName = "Up_Move", .FrameInter = 0.07f, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "DU_Move", .SpriteName = "DU_Move", .FrameInter = 0.07f, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "Side_Move", .SpriteName = "Side_Move", .FrameInter = 0.07f, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "DD_Move", .SpriteName = "DD_Move", .FrameInter = 0.07f, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "Down_Move", .SpriteName = "Down_Move", .FrameInter = 0.07f, .ScaleToTexture = true });

	// Setting
	RenderPtr->GetTransform()->SetLocalPosition({ 0, 30 });
	RenderPtr->ChangeAnimation("Down_Idle");
}

void Player_Overworld::DebugRendererSetting()
{
	if (nullptr == DebugRenderPtr0)
	{
		DebugRenderPtr0 = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr0->SetScaleToTexture("GreenDot.png");
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

	if (nullptr != DebugRenderPtr1
		&& nullptr != DebugRenderPtr2
		&& nullptr != DebugRenderPtr3
		&& nullptr != DebugRenderPtr4)
	{
		DebugRenderPtr1->GetTransform()->SetLocalPosition({ -10, 10, -3 });		// 왼쪽 상단
		DebugRenderPtr2->GetTransform()->SetLocalPosition({ 10, 10, -3 });		// 오른쪽 상단
		DebugRenderPtr3->GetTransform()->SetLocalPosition({ 10, -10, -3 });		// 오른쪽 하단
		DebugRenderPtr4->GetTransform()->SetLocalPosition({ -10, -10, -3 });    // 왼쪽 하단

		DebugRenderPtr1->Off();
		DebugRenderPtr2->Off();
		DebugRenderPtr3->Off();
		DebugRenderPtr4->Off();
	}
}
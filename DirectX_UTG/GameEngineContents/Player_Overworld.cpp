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
	SetCameraFollowType(CameraFollowType::Overworld);
	SetPlayerMoveSpeed(230.0f);
}
void Player_Overworld::Update(float _DeltaTime)
{
	MoveCamera(_DeltaTime);
	DirectCheck();
	UpdateState(_DeltaTime);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     AssistFunction                       //////////////////////////////////////////////
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
		//RenderPtr->GetTransform()->SetLocalPosition({ 0, 90 });
	}
	else
	{
		GetTransform()->SetLocalNegativeScaleX();
		//RenderPtr->GetTransform()->SetLocalPosition({ 15, 90 });
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                         FSM                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
	// RenderPtr->GetTransform()->SetLocalPosition({ 0, 90 });
	RenderPtr->ChangeAnimation("Down_Idle");
}
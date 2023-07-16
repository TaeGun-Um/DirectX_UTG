#include "PrecompileHeader.h"
#include "BuildingDataBase.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "LoadingLevel.h"

#include "Player_Overworld.h"
#include "OverworldLevel.h"
#include "RoundBlackBox.h"
#include "Stage_Title.h"

BuildingDataBase* BuildingDataBase::HomePtr = nullptr;
BuildingDataBase* BuildingDataBase::Tutorial_FlyPtr = nullptr;
BuildingDataBase* BuildingDataBase::MousePtr = nullptr;
BuildingDataBase* BuildingDataBase::FrogPtr = nullptr;
BuildingDataBase* BuildingDataBase::DragonPtr = nullptr;
BuildingDataBase* BuildingDataBase::ZeplinPtr = nullptr;
BuildingDataBase* BuildingDataBase::DjimmiPtr = nullptr;

BuildingDataBase::BuildingDataBase() 
{
}

BuildingDataBase::~BuildingDataBase() 
{
}

void BuildingDataBase::Start()
{
	if (nullptr == GameEngineSprite::Find("Flag.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Overworld");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Flag.png").GetFullPath(), 5, 6);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("FlagShadow.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Djimmi_The_Great.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Grim_Matchstick.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Hilda_Berg.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Ribby_and_Croaks.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Ribby_and_Croaks_Wave.png").GetFullPath(), 7, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Tutorial_Fly.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_WaittingRoom.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Werner_Werman.png").GetFullPath(), 3, 1);
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CameraCullingOn();
	}
	if (nullptr == FlagRenderPtr)
	{
		FlagRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		FlagRenderPtr->CreateAnimation({ .AnimationName = "FlagUp", .SpriteName = "Flag.png", .Start = 0, .End = 27, .FrameInter = 0.1f, .ScaleToTexture = true });
		FlagRenderPtr->CreateAnimation({ .AnimationName = "FlagOn", .SpriteName = "Flag.png", .Start = 15, .End = 27, .FrameInter = 0.1f, .ScaleToTexture = true });
		FlagRenderPtr->ChangeAnimation("FlagUp");
		FlagRenderPtr->CameraCullingOn();
		FlagRenderPtr->Off();
	}

	if (nullptr == CollisionPtr)
	{
		CollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Building));
	}

	if (nullptr == CollisionRenderPtr)
	{
		CollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		CollisionRenderPtr->SetTexture("GreenLine.png");
		CollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
		CollisionRenderPtr->CameraCullingOn();
	}

	Stage_TitleCard = GetLevel()->CreateActor<Stage_Title>();
}

void BuildingDataBase::Update(float _DeltaTime)
{
	if (true == FlagCall)
	{
		FlagRenderPtr->On();
	}

	if (1 == AnimationCount && FlagRenderPtr->IsAnimationEnd())
	{
		AnimationCount = 0;
		FlagRenderPtr->ChangeAnimation("FlagOn");
	}

	if (true == IsCollisionOff)
	{
		CollisionPtr->Off();
		return;
	}

	CollisionCheck(_DeltaTime);

	if (true == CreateCard)
	{
		CardUIOn(_DeltaTime);
	}

	if (true == NextLevelPortal)
	{
		InterAction();
	}
}

void BuildingDataBase::CollisionCheck(float _DeltaTime)
{
	if (nullptr != CollisionPtr->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		Isinteraction = true;
	}
	else
	{
		Isinteraction = false;
	}

	if (true == Isinteraction && true == GameEngineInput::IsDown("Attack"))
	{
		Player_Overworld::MainPlayer->PlayerCollisionPtrOff();
		Player_Overworld::MainPlayer->SetIsPortalingTrue();
		CreateCard = true;
	}
}

void BuildingDataBase::CardUIOn(float _DeltaTime)
{
	Stage_TitleCard->On();

	CardInterActionDelayTime += _DeltaTime;

	if (0.5f >= CardInterActionDelayTime)
	{
		return;
	}

	if (0 == Stage_TitleCard->GetSelectInt() && true == GameEngineInput::IsDown("Attack"))
	{
		NextLevelPortal = true;
	}
	else if (1 == Stage_TitleCard->GetSelectInt() && true == GameEngineInput::IsDown("Attack"))
	{
		Player_Overworld::MainPlayer->PlayerCollisionPtrOn();
		Player_Overworld::MainPlayer->SetIsPortalingfalse();
		Stage_TitleCard->Off();
		Stage_TitleCard->BoxPositionReset();
		CardInterActionDelayTime = 0.0f;
		CreateCard = false;
	}
	else if (true == GameEngineInput::IsDown("Jump"))
	{
		Player_Overworld::MainPlayer->PlayerCollisionPtrOn();
		Player_Overworld::MainPlayer->SetIsPortalingfalse();
		Stage_TitleCard->Off();
		Stage_TitleCard->BoxPositionReset();
		CardInterActionDelayTime = 0.0f;
		CreateCard = false;
	}
}

// Frog 이외에 임시
void BuildingDataBase::InterAction()
{
	switch (BValue)
	{
	case BuildingValue::Home:
	{
		NextLevelPortal = false;
		Player_Overworld::MainPlayer->SetIsPortalingfalse();
		Player_Overworld::MainPlayer->PlayerCollisionPtrOn();

		MsgTextBox("Home");
	}
	break;
	case BuildingValue::Tutorial_Fly:
	{
		NextLevelPortal = false;
		Player_Overworld::MainPlayer->SetIsPortalingfalse();
		Player_Overworld::MainPlayer->PlayerCollisionPtrOn();
		MsgTextBox("Tutorial_Fly");
	}
	break;
	case BuildingValue::Mouse:
	{
		if (1 == BlackBoxCount)
		{
			BlackBoxCount = 0;
			OverworldLevel::OverworldLevelPtr->GetBlackBoxPtr()->BoxSettingReset();
			OverworldLevel::OverworldLevelPtr->GetBlackBoxPtr()->SetEnter();
		}

		if (true == OverworldLevel::OverworldLevelPtr->GetBlackBoxPtr()->GetIsEnd())
		{
			Player_Overworld::MainPlayer->PlayerCollisionPtrOff();
			LoadingLevel::LoadingLevelPtr->SetLevelState(LevelValue::MouseLevel);
			GameEngineCore::ChangeLevel("LoadingLevel");
		}
	}
	break;
	case BuildingValue::Frog:
	{
		if (1 == BlackBoxCount)
		{
			BlackBoxCount = 0;
			OverworldLevel::OverworldLevelPtr->GetBlackBoxPtr()->BoxSettingReset();
			OverworldLevel::OverworldLevelPtr->GetBlackBoxPtr()->SetEnter();
		}

		if (true == OverworldLevel::OverworldLevelPtr->GetBlackBoxPtr()->GetIsEnd())
		{
			Player_Overworld::MainPlayer->PlayerCollisionPtrOff();
			LoadingLevel::LoadingLevelPtr->SetLevelState(LevelValue::FrogLevel);
			GameEngineCore::ChangeLevel("LoadingLevel");
		}
	}
	break;
	case BuildingValue::Dragon:
	{
		if (1 == BlackBoxCount)
		{
			BlackBoxCount = 0;
			OverworldLevel::OverworldLevelPtr->GetBlackBoxPtr()->BoxSettingReset();
			OverworldLevel::OverworldLevelPtr->GetBlackBoxPtr()->SetEnter();
		}

		if (true == OverworldLevel::OverworldLevelPtr->GetBlackBoxPtr()->GetIsEnd())
		{
			Player_Overworld::MainPlayer->PlayerCollisionPtrOff();
			LoadingLevel::LoadingLevelPtr->SetLevelState(LevelValue::DragonLevel);
			GameEngineCore::ChangeLevel("LoadingLevel");
		}
	}
	break;
	case BuildingValue::Zeplin:
	{
		NextLevelPortal = false;
		Player_Overworld::MainPlayer->SetIsPortalingfalse();
		Player_Overworld::MainPlayer->PlayerCollisionPtrOn();
		MsgTextBox("Zeplin");
	}
	break;
	case BuildingValue::Djimmi:
	{
		NextLevelPortal = false;
		Player_Overworld::MainPlayer->SetIsPortalingfalse();
		Player_Overworld::MainPlayer->PlayerCollisionPtrOn();
		MsgTextBox("Djimmi");
	}
	break;
	}
}

void BuildingDataBase::BuildingSetting(BuildingValue _BValue)
{
	BValue = _BValue;

	switch (BValue)
	{
	case BuildingValue::Home:
	{
		RenderPtr->CreateAnimation({ .AnimationName = "To_WaittingRoom", .SpriteName = "To_WaittingRoom.png", .Start = 0, .End = 2, .FrameInter = 0.1f, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("To_WaittingRoom");

		CollisionPtr->GetTransform()->SetLocalScale({ 200, 100, 1 });
		CollisionPtr->GetTransform()->SetLocalPosition({ 0, 0, -17 });
		CollisionPtr->Off();

		CollisionRenderPtr->GetTransform()->SetLocalScale(CollisionPtr->GetTransform()->GetLocalScale());
		CollisionRenderPtr->GetTransform()->SetLocalPosition(CollisionPtr->GetTransform()->GetLocalPosition());

		HomePtr = this;
		Stage_TitleCard->TitleWordSetting(CardValue::Frog);
		Stage_TitleCard->Off();
	}
	break;
	case BuildingValue::Tutorial_Fly:
	{
		RenderPtr->CreateAnimation({ .AnimationName = "To_Tutorial_Fly", .SpriteName = "To_Tutorial_Fly.png", .Start = 0, .End = 2, .FrameInter = 0.1f, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("To_Tutorial_Fly");

		CollisionPtr->GetTransform()->SetLocalScale({ 200, 100, 1 });
		CollisionPtr->GetTransform()->SetLocalPosition({ 0, 0, -17 });
		CollisionPtr->Off();

		CollisionRenderPtr->GetTransform()->SetLocalScale(CollisionPtr->GetTransform()->GetLocalScale());
		CollisionRenderPtr->GetTransform()->SetLocalPosition(CollisionPtr->GetTransform()->GetLocalPosition());
		CollisionRenderPtr->Off();

		Tutorial_FlyPtr = this;
		Stage_TitleCard->TitleWordSetting(CardValue::Tutorial_Fly);
		Stage_TitleCard->SmallBoxSetting();
		Stage_TitleCard->Off();
	}
	break;
	case BuildingValue::Mouse:
	{
		RenderPtr->CreateAnimation({ .AnimationName = "To_Werner_Werman", .SpriteName = "To_Werner_Werman.png", .Start = 0, .End = 2, .FrameInter = 0.1f, .ScaleToTexture = false });
		RenderPtr->GetTransform()->SetLocalScale({ 400, 400, 1 });
		RenderPtr->ChangeAnimation("To_Werner_Werman");

		CollisionPtr->GetTransform()->SetLocalScale({ 200, 200, 1 });
		CollisionPtr->GetTransform()->SetLocalPosition({ -50, -50, -17 });

		CollisionRenderPtr->GetTransform()->SetLocalScale(CollisionPtr->GetTransform()->GetLocalScale());
		CollisionRenderPtr->GetTransform()->SetLocalPosition(CollisionPtr->GetTransform()->GetLocalPosition());

		FlagRenderPtr->GetTransform()->SetLocalPosition({ 10, -75, -1 });

		MousePtr = this;
		Stage_TitleCard->TitleWordSetting(CardValue::Mouse);
		Stage_TitleCard->Off();
	}
	break;
	case BuildingValue::Frog:
	{
		RenderPtr->CreateAnimation({ .AnimationName = "To_Ribby_and_Croaks", .SpriteName = "To_Ribby_and_Croaks.png", .Start = 0, .End = 2, .FrameInter = 0.1f, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("To_Ribby_and_Croaks");

		if (nullptr == AssitantRenderPtr)
		{
			AssitantRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
			AssitantRenderPtr->CreateAnimation({ .AnimationName = "To_Ribby_and_Croaks_Wave", .SpriteName = "To_Ribby_and_Croaks_Wave.png", .Start = 0, .End = 6, .FrameInter = 0.1f, .ScaleToTexture = true });
			AssitantRenderPtr->ChangeAnimation("To_Ribby_and_Croaks_Wave");
			AssitantRenderPtr->GetTransform()->SetLocalPosition({ -25, -110 });
		}

		CollisionPtr->GetTransform()->SetLocalScale({ 200, 200, 1 });
		CollisionPtr->GetTransform()->SetLocalPosition({ 0, 20, -17 });

		CollisionRenderPtr->GetTransform()->SetLocalScale(CollisionPtr->GetTransform()->GetLocalScale());
		CollisionRenderPtr->GetTransform()->SetLocalPosition(CollisionPtr->GetTransform()->GetLocalPosition());

		FlagRenderPtr->GetTransform()->SetLocalPosition({ -20, 150, 1 });

		FrogPtr = this;
		Stage_TitleCard->TitleWordSetting(CardValue::Frog);
		Stage_TitleCard->Off();
	}
	break;
	case BuildingValue::Dragon:
	{
		RenderPtr->CreateAnimation({ .AnimationName = "To_Grim_Matchstick", .SpriteName = "To_Grim_Matchstick.png", .Start = 0, .End = 2, .FrameInter = 0.1f, .ScaleToTexture = false });
		RenderPtr->GetTransform()->SetLocalScale({ 400, 400, 1 });
		RenderPtr->ChangeAnimation("To_Grim_Matchstick");

		CollisionPtr->GetTransform()->SetLocalScale({ 100, 120, 1 });
		CollisionPtr->GetTransform()->SetLocalPosition({ -10, -100, -17 });

		CollisionRenderPtr->GetTransform()->SetLocalScale(CollisionPtr->GetTransform()->GetLocalScale());
		CollisionRenderPtr->GetTransform()->SetLocalPosition(CollisionPtr->GetTransform()->GetLocalPosition());

		FlagRenderPtr->GetTransform()->SetLocalPosition({ 95, -55, 1 });

		DragonPtr = this;
		Stage_TitleCard->TitleWordSetting(CardValue::Dragon);
		Stage_TitleCard->Off();
	}
	break;
	case BuildingValue::Zeplin:
	{
		RenderPtr->CreateAnimation({ .AnimationName = "To_Hilda_Berg", .SpriteName = "To_Hilda_Berg.png", .Start = 0, .End = 2, .FrameInter = 0.1f, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("To_Hilda_Berg");

		CollisionPtr->GetTransform()->SetLocalScale({ 250, 100, 1 });
		CollisionPtr->GetTransform()->SetLocalPosition({ -10, -50, -17 });

		CollisionRenderPtr->GetTransform()->SetLocalScale(CollisionPtr->GetTransform()->GetLocalScale());
		CollisionRenderPtr->GetTransform()->SetLocalPosition(CollisionPtr->GetTransform()->GetLocalPosition());

		FlagRenderPtr->GetTransform()->SetLocalPosition({ -50, 0, -1 });

		ZeplinPtr = this;
		Stage_TitleCard->TitleWordSetting(CardValue::Zeplin);
		Stage_TitleCard->Off();
	}
	break;
	case BuildingValue::Djimmi:
	{
		RenderPtr->CreateAnimation({ .AnimationName = "To_Djimmi_The_Great", .SpriteName = "To_Djimmi_The_Great.png", .Start = 0, .End = 2, .FrameInter = 0.1f, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("To_Djimmi_The_Great");

		CollisionPtr->GetTransform()->SetLocalScale({ 200, 200, 1 });
		CollisionPtr->GetTransform()->SetLocalPosition({ -60, -50, -17 });

		CollisionRenderPtr->GetTransform()->SetLocalScale(CollisionPtr->GetTransform()->GetLocalScale());
		CollisionRenderPtr->GetTransform()->SetLocalPosition(CollisionPtr->GetTransform()->GetLocalPosition());

		FlagRenderPtr->GetTransform()->SetLocalPosition({ -30, -60, -1 });

		DjimmiPtr = this;
		Stage_TitleCard->TitleWordSetting(CardValue::Djimmi);
		Stage_TitleCard->Off();
	}
	break;
	case BuildingValue::Unknown:
	{
		MsgAssert("BuildingSetting()를 실시하지 않았습니다. BuildingValue가 Unknown입니다.");
		return;
	}
	break;
	default:
		break;
	}
}
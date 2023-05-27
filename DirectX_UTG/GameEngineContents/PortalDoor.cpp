#include "PrecompileHeader.h"
#include "PortalDoor.h"

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "WaitingRoomLevel.h"
#include "TutorialLevel.h"
#include "OverworldLevel.h"
#include "FrogLevel.h"
#include "DragonLevel.h"
#include "MouseLevel.h"

#include "Player.h"

PortalDoor::PortalDoor() 
{
}

PortalDoor::~PortalDoor() 
{
}

void PortalDoor::Start()
{
	if (nullptr == RenderPtrCollisionPtr)
	{
		RenderPtrCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Portal));
		RenderPtrCollisionPtr->GetTransform()->SetLocalScale({ 170, 150, 1 });
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->GetTransform()->SetLocalScale(RenderPtrCollisionPtr->GetTransform()->GetLocalScale());
		RenderPtr->GetTransform()->SetLocalPosition(RenderPtrCollisionPtr->GetTransform()->GetLocalPosition());
		RenderPtr->SetTexture("GreenBox.png");
		RenderPtr->ColorOptionValue.MulColor.a = 0.6f;
	}
}

void PortalDoor::Update(float _DeltaTime)
{
	if (true == IsDebugRender)
	{
		RenderPtr->On();
	}
	else
	{
		RenderPtr->Off();
	}

	if (false == Player::MainPlayer->GetPlayerPortalAble())
	{
		return;
	}

	if (true == Player::MainPlayer->GetPlayerPortaling()
		&& Player::MainPlayer->GetPlayerMainRenderPtr()->FindAnimation("Portal")->IsEnd())
	{
		LevelChange();
	}
}

void PortalDoor::LevelChange()
{
	switch (PV)
	{
	case PortalValue::WaitingRoom:
	{
		GameEngineCore::ChangeLevel("WaitingRoomLevel");
	}
	break;
	case PortalValue::Tutorial:
	{
		GameEngineCore::ChangeLevel("TutorialLevel");
	}
	break;
	case PortalValue::Overworld:
	{
		TutorialLevel::TutorialLevelPtr->LoadingOn();
		GameEngineCore::ChangeLevel("OverworldLevel");
	}
	break;
	case PortalValue::Frog:
	{
		GameEngineCore::ChangeLevel("FrogLevel");
	}
	break;
	case PortalValue::Dragon:
	{
		GameEngineCore::ChangeLevel("DragonLevel");
	}
	break;
	case PortalValue::Mouse:
	{
		GameEngineCore::ChangeLevel("MouseLevel");
	}
	break;
	case PortalValue::Unknown:
	{
		MsgAssert("PortalValue를 설정하지 않았습니다. Unknown으로는 갈 수 없습니다.");
		return;
	}
	break;
	default:
	break;
	}
}
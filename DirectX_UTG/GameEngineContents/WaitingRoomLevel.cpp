#include "PrecompileHeader.h"
#include "WaitingRoomLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "PortalDoor.h"
#include "Loading.h"
#include "Player.h"
#include "WaitingRoom_Map.h"
#include "WaitingRoom_ColMap.h"
#include "RoundBlackBox.h"
#include "TransformGUI.h"

WaitingRoomLevel* WaitingRoomLevel::WaitingRoomLevelPtr = nullptr;

WaitingRoomLevel::WaitingRoomLevel() 
{
}

WaitingRoomLevel::~WaitingRoomLevel() 
{
}

void WaitingRoomLevel::Start()
{
	WaitingRoomLevelPtr = this;
}
void WaitingRoomLevel::Update(float _DeltaTime)
{
}

void WaitingRoomLevel::LevelChangeStart()
{
	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });

	if (nullptr == GameEngineTexture::Find("WaitingRoom_Background.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("WaitingRoom");

		GameEngineTexture::Load(NewDir.GetPlusFileName("WaitingRoom_ColMap.png").GetFullPath());
	}

	// ColMap
	std::shared_ptr<GameEngineTexture> PlayMap = GameEngineTexture::Find("WaitingRoom_ColMap.png");
	int PlayMapWidth = PlayMap->GetWidth();
	int PlayMapHeight = PlayMap->GetHeight();
	float PlayMapWidth_Half = static_cast<float>(PlayMapWidth / 2);
	float PlayMapHeight_Half = static_cast<float>(PlayMapHeight / 2);

	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 640, PlayMapHeight_Half + 10, -620.0f });
	GetMainCamera()->SetSortType(0, SortType::ZSort);

	{
		if (BlackBoxPtr == nullptr)
		{
			BlackBoxPtr = CreateActor<RoundBlackBox>();
		}

		BlackBoxPtr->BoxSettingReset();
		BlackBoxPtr->SetExit();
	}

	if (nullptr == MapObject)
	{
		MapObject = CreateActor<WaitingRoom_Map>();
		MapObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, 10 });
	}

	if (nullptr == PlayerObject)
	{
		PlayerObject = CreateActor<Player>();
		PlayerObject->GetTransform()->SetLocalPosition({ 385 , PlayMapHeight_Half });
		PlayerObject->SetColMap(PlayMap, PixelCollision::Coordinate::Custom);
		PlayerObject->SetCameraSpeedRatio(1.0f);
	}
	if (nullptr == PortalDoorObject)
	{
		PortalDoorObject = CreateActor<PortalDoor>();
		PortalDoorObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half + 20, PlayMapHeight_Half - 100, -5 });
		PortalDoorObject->SetPortalValue(PortalValue::Tutorial);
		PortalDoorObject->SetEnterMessageRenderPtrPos({-5, -150});
	}
	if (nullptr == ThisColMap)
	{
		ThisColMap = CreateActor<WaitingRoom_ColMap>();
		ThisColMap->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, -5 });
	}

	// GUI
	if (nullptr == GUI)
	{
		GUI = GameEngineGUI::FindGUIWindowConvert<TransformGUI>("TransformGUI");
		GUI->SetTarget(PlayerObject->GetTransform());
		GUI->SetMainPalyer(PlayerObject);

		GUI->PlayerDebugRenderOn = std::bind(&WaitingRoomLevel::PlayerDebugRenderOn, this);
		GUI->PlayerDebugRenderOff = std::bind(&WaitingRoomLevel::PlayerDebugRenderOff, this);
		GUI->ColMapRenderOn = std::bind(&WaitingRoomLevel::LevelDebugOn, this);
		GUI->ColMapRenderOff = std::bind(&WaitingRoomLevel::LevelDebugOff, this);
	}

	if (nullptr == LoadingPtr)
	{
		LoadingPtr = CreateActor<Loading>();
		LoadingPtr->SetLoadingPtrOff();
	}
}

void WaitingRoomLevel::LevelChangeEnd()
{
	if (nullptr != GameEngineTexture::Find("WaitingRoom_Background.png"))
	{
		GameEngineTexture::UnLoad("WaitingRoom_Background.png");
		GameEngineTexture::UnLoad("WaitingRoom_Chair.png");
		GameEngineTexture::UnLoad("WaitingRoom_Couch.png");
		GameEngineTexture::UnLoad("WaitingRoom_Vignette.png");
	}

	if (nullptr != GameEngineTexture::Find("WaitingRoom_ColMap.png"))
	{
		GameEngineTexture::UnLoad("WaitingRoom_ColMap.png");
	}

	ThisColMap = nullptr;
	MapObject = nullptr;
}

void WaitingRoomLevel::PlayerDebugRenderOn()
{
	if (nullptr != PlayerObject)
	{
		PlayerObject->PlayerDebugRenderOn();
	}
}

void WaitingRoomLevel::PlayerDebugRenderOff()
{
	if (nullptr != PlayerObject)
	{
		PlayerObject->PlayerDebugRenderOff();
	}
}

void WaitingRoomLevel::LevelDebugOn()
{
	if (nullptr != ThisColMap)
	{
		ThisColMap->ColMapDebugRenderOn();
	}
	if (nullptr != MapObject)
	{
		MapObject->MapDebugRenderOn();
	}
	if (nullptr != PortalDoorObject)
	{
		PortalDoorObject->PortalDebugRenderOn();
	}
}
void WaitingRoomLevel::LevelDebugOff()
{
	if (nullptr != ThisColMap)
	{
		ThisColMap->ColMapDebugRenderOff();
	}
	if (nullptr != MapObject)
	{
		MapObject->MapDebugRenderOff();
	}
	if (nullptr != PortalDoorObject)
	{
		PortalDoorObject->PortalDebugRenderOff();
	}
}
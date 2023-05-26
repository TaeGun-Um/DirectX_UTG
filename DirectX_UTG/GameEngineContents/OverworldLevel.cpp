#include "PrecompileHeader.h"
#include "OverworldLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Overworld_Map.h"
#include "Overworld_ColMap.h"
#include "Player_Overworld.h"

#include "AppleTraveller.h"
#include "Axeman.h"
#include "Canteen.h"
#include "Coin.h"
#include "Fishgirl.h"

#include "TransformGUI.h"
#include "Screen_FX.h"
#include "Loading.h"

OverworldLevel::OverworldLevel() 
{
}

OverworldLevel::~OverworldLevel() 
{
}

void OverworldLevel::Start()
{

}

void OverworldLevel::PlayerDebugRenderOn()
{
	if (nullptr != PlayerObject)
	{
		PlayerObject->PlayerDebugRenderOn();
	}
}

void OverworldLevel::PlayerDebugRenderOff()
{
	if (nullptr != PlayerObject)
	{
		PlayerObject->PlayerDebugRenderOff();
	}
}

void OverworldLevel::LevelDebugOn()
{
	if (nullptr != ThisColMap)
	{
		ThisColMap->ColMapDebugRenderOn();
	}
	if (nullptr != MapObject)
	{
		//MapObject->MapDebugRenderOn();
	}
	if (nullptr != PortalDoorObject)
	{
		//PortalDoorObject->PortalDebugRenderOn();
	}
}
void OverworldLevel::LevelDebugOff()
{
	if (nullptr != ThisColMap)
	{
		ThisColMap->ColMapDebugRenderOff();
	}
	if (nullptr != MapObject)
	{
		//MapObject->MapDebugRenderOff();
	}
	if (nullptr != PortalDoorObject)
	{
		//PortalDoorObject->PortalDebugRenderOff();
	}
}

void OverworldLevel::Update(float _DeltaTime)
{
}

void OverworldLevel::LevelChangeStart()
{
	// 콜맵용
	if (nullptr == GameEngineTexture::Find("Tutorial_ColMap.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Overworld");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Overworld_ColMap.png").GetFullPath());
	}

	// ColMap
	std::shared_ptr<GameEngineTexture> PlayMap = GameEngineTexture::Find("Overworld_ColMap.png");
	int PlayMapWidth = PlayMap->GetWidth();
	int PlayMapHeight = PlayMap->GetHeight();
	float PlayMapWidth_Half = static_cast<float>(PlayMapWidth / 2);
	float PlayMapHeight_Half = static_cast<float>(PlayMapHeight / 2);

	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half - 300, -620.0f });
	GetMainCamera()->SetSortType(0, SortType::ZSort);

	// CreateActor
	// Map
	{
		MapObject = CreateActor<Overworld_Map>();
		MapObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, 5 });
	}
	// NPC
	{
		std::shared_ptr<AppleTraveller> NPCObject0 = CreateActor<AppleTraveller>();
		NPCObject0->GetTransform()->SetLocalPosition({ 1680 , 1325, 1 });

		std::shared_ptr<Axeman> NPCObject1 = CreateActor<Axeman>();
		NPCObject1->GetTransform()->SetLocalPosition({ 3170 , 1350, 1 });

		std::shared_ptr<Canteen> NPCObject2 = CreateActor<Canteen>();
		NPCObject2->GetTransform()->SetLocalPosition({ 2595 , 2040, 1 });

		std::shared_ptr<Coin> NPCObject3 = CreateActor<Coin>();
		NPCObject3->GetTransform()->SetLocalPosition({ 2330 , 770, 1 });

		std::shared_ptr<Fishgirl> NPCObject4 = CreateActor<Fishgirl>();
		NPCObject4->GetTransform()->SetLocalPosition({ 2860 , 445, 1 });
	}
	// Character
	if (nullptr == PlayerObject)
	{
		PlayerObject = CreateActor<Player_Overworld>();
		PlayerObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half , PlayMapHeight_Half - 300, 1 });
		PlayerObject->SetColMap(PlayMap, PixelCollision::Coordinate::Custom);
	}
	// Portal
	{
		//PortalDoorObject = CreateActor<PortalDoor>();
		//PortalDoorObject->GetTransform()->SetLocalPosition({ 5840, 150 });
		//PortalDoorObject->SetPortalValue(PortalValue::Overworld);
	}
	// Wall Actor
	{
	}
	// ColMap
	if (nullptr == ThisColMap)
	{
		ThisColMap = CreateActor<Overworld_ColMap>();
		ThisColMap->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, -15 });
	}
	// Layer
	{
	}
	// ScreenSFX
	{
		//std::shared_ptr<Screen_FX> Object = CreateActor<Screen_FX>();
		//Object->GetTransform()->SetLocalPosition({ 640 , PlayMapHeight_Half - 100, -10 });
	}

	// GUI
	if (nullptr == GUI)
	{
		GUI = GameEngineGUI::FindGUIWindowConvert<TransformGUI>("TransformGUI");
		GUI->SetTarget(PlayerObject->GetTransform());
		GUI->SetOverworldPalyer(PlayerObject);

		GUI->PlayerDebugRenderOn = std::bind(&OverworldLevel::PlayerDebugRenderOn, this);
		GUI->PlayerDebugRenderOff = std::bind(&OverworldLevel::PlayerDebugRenderOff, this);
		GUI->ColMapRenderOn = std::bind(&OverworldLevel::LevelDebugOn, this);
		GUI->ColMapRenderOff = std::bind(&OverworldLevel::LevelDebugOff, this);
	}
}
void OverworldLevel::LevelChangeEnd()
{

}
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
#include "PortalDoor.h"

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
		//PlayerObject->PlayerDebugRenderOn();
	}
}

void OverworldLevel::PlayerDebugRenderOff()
{
	if (nullptr != PlayerObject)
	{
		//PlayerObject->PlayerDebugRenderOff();
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
	if (nullptr == GameEngineSprite::Find("BlueBox"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("DebugImage");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}
	// 레벨 리소스 로드
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
	GetMainCamera()->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, -620.0f });
	GetMainCamera()->SetSortType(0, SortType::ZSort);

	// CreateActor
	// Map
	{
		MapObject = CreateActor<Overworld_Map>();
		MapObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, 100 });
	}
	// Character
	if (nullptr == PlayerObject)
	{
		PlayerObject = CreateActor<Player_Overworld>();
		PlayerObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half , PlayMapHeight_Half, -1 });
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
		ThisColMap->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, -2 });
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
	GameEngineSprite::ResourcesClear();
	GameEngineTexture::ResourcesClear();
}
#include "PrecompileHeader.h"
#include "TutorialLevel.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h> // 지울것
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Tutorial_BackGround.h"
#include "Tutorial_BackLayer.h"
#include "Tutorial_Map.h"
#include "Tutorial_ColMap.h"
#include "Tutorial_Target.h"

#include "Player.h"
#include "PortalDoor.h"
#include "Screen_FX.h"
#include "Loading.h"

#include "TransformGUI.h"

TutorialLevel* TutorialLevel::TutorialLevelPtr = nullptr;

TutorialLevel::TutorialLevel() 
{
}

TutorialLevel::~TutorialLevel() 
{
}

void TutorialLevel::Start()
{
	TutorialLevelPtr = this;
}

void TutorialLevel::Update(float _DeltaTime)
{
}

void TutorialLevel::LevelChangeStart()
{
	// 콜맵용
	if (nullptr == GameEngineTexture::Find("Tutorial_ColMap.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Tutorial_Normal");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Tutorial_ColMap.png").GetFullPath());
	}

	// ColMap
	std::shared_ptr<GameEngineTexture> PlayMap = GameEngineTexture::Find("Tutorial_ColMap.png");
	int PlayMapWidth = PlayMap->GetWidth();
	int PlayMapHeight = PlayMap->GetHeight();
	float PlayMapWidth_Half = static_cast<float>(PlayMapWidth / 2);
	float PlayMapHeight_Half = static_cast<float>(PlayMapHeight / 2);

	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 640, PlayMapHeight_Half - 100, -620.0f });
	//GetMainCamera()->GetTransform()->SetLocalPosition({ 5500, PlayMapHeight_Half - 100, -620.0f });
	GetMainCamera()->SetSortType(0, SortType::ZSort);

	// CreateActor
	// Background
	{
		std::shared_ptr<Tutorial_BackGround> Object = CreateActor<Tutorial_BackGround>();
		Object->GetTransform()->SetLocalPosition({ 640 , PlayMapHeight_Half - 100, 100 });
	}
	// Map
	if (nullptr == MapObject)
	{
		MapObject = CreateActor<Tutorial_Map>();
		MapObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, 50 });
	}
	// Character
	if (nullptr == PlayerObject)
	{
		PlayerObject = CreateActor<Player>();
		PlayerObject->GetTransform()->SetLocalPosition({ 300 , PlayMapHeight_Half });
		//PlayerObject->GetTransform()->SetLocalPosition({ 5500 , PlayMapHeight_Half, 1 });
		PlayerObject->SetColMap(PlayMap, PixelCollision::Coordinate::Custom);
	}
	// Portal
	if (nullptr == PortalDoorObject)
	{
		PortalDoorObject = CreateActor<PortalDoor>();
		PortalDoorObject->GetTransform()->SetLocalPosition({ 5840, 150 });
		PortalDoorObject->SetPortalValue(PortalValue::Overworld);
	}
	// Wall Actor
	if (nullptr == TargetObject)
	{
		TargetObject = CreateActor<Tutorial_Target>();
		TargetObject->GetTransform()->SetLocalPosition({ 3447, 305 });
	}
	// ColMap
	if (nullptr == ThisColMap)
	{
		ThisColMap = CreateActor<Tutorial_ColMap>();
		ThisColMap->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, -5 });
	}
	// Layer
	{
		std::shared_ptr<Tutorial_BackLayer> Object = CreateActor<Tutorial_BackLayer>();
		Object->GetTransform()->SetLocalPosition({ 640 , PlayMapHeight_Half - 100, -10 });
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
		GUI->SetMainPalyer(PlayerObject);

		GUI->PlayerDebugRenderOn = std::bind(&TutorialLevel::PlayerDebugRenderOn, this);
		GUI->PlayerDebugRenderOff = std::bind(&TutorialLevel::PlayerDebugRenderOff, this);
		GUI->ColMapRenderOn = std::bind(&TutorialLevel::LevelDebugOn, this);
		GUI->ColMapRenderOff = std::bind(&TutorialLevel::LevelDebugOff, this);
	}

	if (nullptr == LoadingPtr)
	{
		LoadingPtr = CreateActor<Loading>();
		LoadingPtr->SetLoadingPtrOff();
	}
}
void TutorialLevel::LevelChangeEnd()
{
}

void TutorialLevel::PlayerDebugRenderOn()
{
	if (nullptr != PlayerObject)
	{
		PlayerObject->PlayerDebugRenderOn();
	}
}

void TutorialLevel::PlayerDebugRenderOff()
{
	if (nullptr != PlayerObject)
	{
		PlayerObject->PlayerDebugRenderOff();
	}
}

void TutorialLevel::LevelDebugOn()
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
	if (nullptr != TargetObject)
	{
		TargetObject->TargetDebugRenderOn();
	}
}
void TutorialLevel::LevelDebugOff()
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
	if (nullptr != TargetObject)
	{
		TargetObject->TargetDebugRenderOff();
	}
}
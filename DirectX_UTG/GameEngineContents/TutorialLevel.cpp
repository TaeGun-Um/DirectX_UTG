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
#include "CardUI.h"
#include "HealthUI.h"
#include "PortalDoor.h"
#include "Screen_FX.h"
#include "Loading.h"
#include "RoundBlackBox.h"

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
	if (true == GameEngineInput::IsDown("PrevLevel"))
	{
		GameEngineCore::ChangeLevel("WaitingRoomLevel");
	}
	if (true == GameEngineInput::IsDown("NextLevel"))
	{
		GameEngineCore::ChangeLevel("OverworldLevel");
	}
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
	GetMainCamera()->SetSortType(0, SortType::ZSort);

	// CreateActor
	// Background
	{
		if (nullptr == BGObject)
		{
			BGObject = CreateActor<Tutorial_BackGround>();
		}
		
		BGObject->GetTransform()->SetLocalPosition({ 640 , PlayMapHeight_Half - 100, 100 });
	}
	// Map
	{
		if (nullptr == MapObject)
		{
			MapObject = CreateActor<Tutorial_Map>();
		}
		
		MapObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, 50 });
	}
	// Character
	{
		if (nullptr == PlayerObject)
		{
			PlayerObject = CreateActor<Player>();
		}
		
		PlayerObject->GetTransform()->SetLocalPosition({ 300 , PlayMapHeight_Half });
		PlayerObject->SetColMap(PlayMap, PixelCollision::Coordinate::Custom);
		PlayerObject->SetCameraSpeedRatio(2.f);
		PlayerObject->SetCorrectionFalse();
	}
	// Portal
	{
		if (nullptr == PortalDoorObject)
		{
			PortalDoorObject = CreateActor<PortalDoor>();
		}
		
		PortalDoorObject->GetTransform()->SetLocalPosition({ 5840, 150 });
		PortalDoorObject->SetPortalValue(PortalValue::Overworld);
	}
	// Wall Actor
	{
		if (nullptr == TargetObject)
		{
			TargetObject = CreateActor<Tutorial_Target>();
		}
		
		TargetObject->GetTransform()->SetLocalPosition({ 3447, 305 });
	}
	// ColMap
	{
		if (nullptr == ThisColMap)
		{
			ThisColMap = CreateActor<Tutorial_ColMap>();
		}
		
		ThisColMap->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, -5 });
	}
	// Layer
	{
		if (nullptr == LayerObject)
		{
			LayerObject = CreateActor<Tutorial_BackLayer>();
		}
		
		LayerObject->GetTransform()->SetLocalPosition({ 640 , PlayMapHeight_Half - 100, -10 });
	}
	{
		if (nullptr == HealthObject)
		{
			HealthObject = CreateActor<HealthUI>();
		}

		if (nullptr == CardObject)
		{
			CardObject = CreateActor<CardUI>();
		}

		HealthObject->GetTransform()->SetLocalPosition({ -585, -335 });
		HealthObject->SetMainPalyer(PlayerObject);
		CardObject->GetTransform()->SetLocalPosition({ -525, -350 });
		CardObject->SetMainPalyer(PlayerObject);
	}
	{
		if (BlackBoxPtr == nullptr)
		{
			BlackBoxPtr = CreateActor<RoundBlackBox>();
		}

		BlackBoxPtr->BoxSettingReset();
		BlackBoxPtr->SetExit();
	}

	// GUI
	{
		if (nullptr == GUI)
		{
			GUI = GameEngineGUI::FindGUIWindowConvert<TransformGUI>("TransformGUI");
		}
		
		GUI->SetTarget(PlayerObject->GetTransform());
		GUI->SetMainPalyer(PlayerObject);

		GUI->PlayerDebugRenderOn = std::bind(&TutorialLevel::PlayerDebugRenderOn, this);
		GUI->PlayerDebugRenderOff = std::bind(&TutorialLevel::PlayerDebugRenderOff, this);
		GUI->ColMapRenderOn = std::bind(&TutorialLevel::LevelDebugOn, this);
		GUI->ColMapRenderOff = std::bind(&TutorialLevel::LevelDebugOff, this);
	}
	{
		if (nullptr == LoadingPtr)
		{
			LoadingPtr = CreateActor<Loading>();
		}
		
		LoadingPtr->SetLoadingPtrOff();
	}
}
void TutorialLevel::LevelChangeEnd()
{
	if (nullptr != GameEngineTexture::Find("Tutorial_BackLayer_001.png"))
	{
		GameEngineTexture::UnLoad("Tutorial_BackLayer_001.png");
		GameEngineTexture::UnLoad("Tutorial_BackLayer_002.png");
	}
	if (nullptr != GameEngineTexture::Find("Tutorial_ColMap.png"))
	{
		GameEngineTexture::UnLoad("Tutorial_ColMap.png");
	}
	if (nullptr != GameEngineTexture::Find("Tutorial_Map.png"))
	{
		GameEngineTexture::UnLoad("Tutorial_Map.png");
	}
	if (nullptr != GameEngineTexture::Find("tutorial_pink_sphere_1.png"))
	{
		GameEngineTexture::UnLoad("tutorial_pink_sphere_1.png");
		GameEngineTexture::UnLoad("tutorial_pink_sphere_2.png");
	}
	if (nullptr != GameEngineTexture::Find("tutorial_pyramid_topper.png"))
	{
		GameEngineTexture::UnLoad("tutorial_pyramid_topper.png");
	}
	if (nullptr != GameEngineSprite::Find("Target"))
	{
		GameEngineSprite::UnLoad("Target");
	}
	if (nullptr != GameEngineSprite::Find("Explosion"))
	{
		GameEngineSprite::UnLoad("Explosion");
	}

	CardObject->CartUIReset();
	PlayerObject->MoveAbleTimeReset();
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
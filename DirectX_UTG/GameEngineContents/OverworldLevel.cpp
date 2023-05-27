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
#include "BuildingDataBase.h"

#include "FadeEffect.h"
#include "TransformGUI.h"
#include "Screen_FX.h"
#include "Loading.h"

OverworldLevel* OverworldLevel::OverworldLevelPtr = nullptr;

OverworldLevel::OverworldLevel()
{
}

OverworldLevel::~OverworldLevel()
{
}

void OverworldLevel::Start()
{
	OverworldLevelPtr = this;
}

void OverworldLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("FadeIn"))
	{
		FEffect->FadeIn();
	}

	if (true == GameEngineInput::IsDown("FadeOut"))
	{
		FEffect->FadeOut();
	}
}

void OverworldLevel::LevelChangeStart()
{
	FEffect = GetLastTarget()->CreateEffect<FadeEffect>();

	// 콜맵용
	if (nullptr == GameEngineTexture::Find("Overworld_ColMap.png"))
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
	if (nullptr == MapObject)
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
		NPCObject4->GetTransform()->SetLocalPosition({ 2860 , 445, -1 });
	}
	// Building
	{
		std::shared_ptr<BuildingDataBase> HomeObject = CreateActor<BuildingDataBase>();
		HomeObject->BuildingSetting(BuildingValue::Home);
		HomeObject->GetTransform()->SetLocalPosition({ 780 , 1560, 1 });

		std::shared_ptr<BuildingDataBase> ZeplinObject = CreateActor<BuildingDataBase>();
		ZeplinObject->BuildingSetting(BuildingValue::Zeplin);
		ZeplinObject->GetTransform()->SetLocalPosition({ 3370 , 2015, 1 });

		std::shared_ptr<BuildingDataBase> FrogObject = CreateActor<BuildingDataBase>();
		FrogObject->BuildingSetting(BuildingValue::Frog);
		FrogObject->GetTransform()->SetLocalPosition({ 2200 , 370, -1 });

		std::shared_ptr<BuildingDataBase> Tutorial_FlyObject = CreateActor<BuildingDataBase>();
		Tutorial_FlyObject->BuildingSetting(BuildingValue::Tutorial_Fly);
		Tutorial_FlyObject->GetTransform()->SetLocalPosition({ 2800 , 2030, 1 });

		std::shared_ptr<BuildingDataBase> MouseObject = CreateActor<BuildingDataBase>();
		MouseObject->BuildingSetting(BuildingValue::Mouse);
		MouseObject->GetTransform()->SetLocalPosition({ 3280 , 620, 1 });

		std::shared_ptr<BuildingDataBase> DjimmiObject = CreateActor<BuildingDataBase>();
		DjimmiObject->BuildingSetting(BuildingValue::Djimmi);
		DjimmiObject->GetTransform()->SetLocalPosition({ 3670 , 1480, 1 });

		std::shared_ptr<BuildingDataBase> DragonObject = CreateActor<BuildingDataBase>();
		DragonObject->BuildingSetting(BuildingValue::Dragon);
		DragonObject->GetTransform()->SetLocalPosition({ 2280 , 1650, 1 });
	}
	// Character
	if (nullptr == PlayerObject)
	{
		PlayerObject = CreateActor<Player_Overworld>();
		PlayerObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half , PlayMapHeight_Half, 1 });
		PlayerObject->SetColMap(PlayMap, PixelCollision::Coordinate::Custom);
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

	if (nullptr == LoadingPtr)
	{
		LoadingPtr = CreateActor<Loading>();
		LoadingPtr->SetLoadingPtrOff();
	}
}
void OverworldLevel::LevelChangeEnd()
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
	if (nullptr != AppleTraveller::AppleTravellerPtr)
	{
		AppleTraveller::AppleTravellerPtr->CollisionRenderOn();
	}
	if (nullptr != Axeman::AxemanPtr)
	{
		Axeman::AxemanPtr->CollisionRenderOn();
	}
	if (nullptr != Canteen::CanteenPtr)
	{
		Canteen::CanteenPtr->CollisionRenderOn();
	}
	if (nullptr != Coin::CoinPtr)
	{
		Coin::CoinPtr->CollisionRenderOn();
	}
	if (nullptr != Fishgirl::FishgirlPtr)
	{
		Fishgirl::FishgirlPtr->CollisionRenderOn();
	}
	if (nullptr != BuildingDataBase::HomePtr)
	{
		BuildingDataBase::HomePtr->CollisionRenderOn();
	}
	if (nullptr != BuildingDataBase::Tutorial_FlyPtr)
	{
		BuildingDataBase::Tutorial_FlyPtr->CollisionRenderOn();
	}
	if (nullptr != BuildingDataBase::MousePtr)
	{
		BuildingDataBase::MousePtr->CollisionRenderOn();
	}
	if (nullptr != BuildingDataBase::FrogPtr)
	{
		BuildingDataBase::FrogPtr->CollisionRenderOn();
	}
	if (nullptr != BuildingDataBase::DragonPtr)
	{
		BuildingDataBase::DragonPtr->CollisionRenderOn();
	}
	if (nullptr != BuildingDataBase::ZeplinPtr)
	{
		BuildingDataBase::ZeplinPtr->CollisionRenderOn();
	}
	if (nullptr != BuildingDataBase::DjimmiPtr)
	{
		BuildingDataBase::DjimmiPtr->CollisionRenderOn();
	}
}
void OverworldLevel::LevelDebugOff()
{
	if (nullptr != ThisColMap)
	{
		ThisColMap->ColMapDebugRenderOff();
	}
	if (nullptr != AppleTraveller::AppleTravellerPtr)
	{
		AppleTraveller::AppleTravellerPtr->CollisionRenderOff();
	}
	if (nullptr != Axeman::AxemanPtr)
	{
		Axeman::AxemanPtr->CollisionRenderOff();
	}
	if (nullptr != Canteen::CanteenPtr)
	{
		Canteen::CanteenPtr->CollisionRenderOff();
	}
	if (nullptr != Coin::CoinPtr)
	{
		Coin::CoinPtr->CollisionRenderOff();
	}
	if (nullptr != Fishgirl::FishgirlPtr)
	{
		Fishgirl::FishgirlPtr->CollisionRenderOff();
	}
	if (nullptr != BuildingDataBase::HomePtr)
	{
		BuildingDataBase::HomePtr->CollisionRenderOff();
	}
	if (nullptr != BuildingDataBase::Tutorial_FlyPtr)
	{
		BuildingDataBase::Tutorial_FlyPtr->CollisionRenderOff();
	}
	if (nullptr != BuildingDataBase::MousePtr)
	{
		BuildingDataBase::MousePtr->CollisionRenderOff();
	}
	if (nullptr != BuildingDataBase::FrogPtr)
	{
		BuildingDataBase::FrogPtr->CollisionRenderOff();
	}
	if (nullptr != BuildingDataBase::DragonPtr)
	{
		BuildingDataBase::DragonPtr->CollisionRenderOff();
	}
	if (nullptr != BuildingDataBase::ZeplinPtr)
	{
		BuildingDataBase::ZeplinPtr->CollisionRenderOff();
	}
	if (nullptr != BuildingDataBase::DjimmiPtr)
	{
		BuildingDataBase::DjimmiPtr->CollisionRenderOff();
	}
}
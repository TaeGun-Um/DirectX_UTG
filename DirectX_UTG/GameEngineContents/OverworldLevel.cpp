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
#include "OverworldGUI.h"
#include "Screen_FX.h"
#include "Loading.h"
#include "RoundBlackBox.h"

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
	if (true == GameEngineInput::IsDown("PrevLevel"))
	{
		GameEngineCore::ChangeLevel("TutorialLevel");
	}
	if (true == GameEngineInput::IsDown("NextLevel"))
	{
		GameEngineCore::ChangeLevel("FrogLevel");
	}

	BuildingFlagOn();

	if (true == GameEngineInput::IsDown("FadeIn"))
	{
		FEffect->FadeIn();
	}

	if (true == GameEngineInput::IsDown("FadeOut"))
	{
		FEffect->FadeOut();
	}

	if (true == GameEngineInput::IsDown("NextLevel") && 1 == DebugBoxCount)
	{
		DebugBoxCount = 0;
		BlackBoxPtr->BoxSettingReset();
		BlackBoxPtr->SetEnter();
	}

	if (true == BlackBoxPtr->GetIsEnd() && 0 == DebugBoxCount)
	{
		LoadingOn();
		GameEngineCore::ChangeLevel("FrogLevel");
	}
}

void OverworldLevel::BuildingFlagOn()
{
	if (true == FrogEnd && 1 == FrogEndCount)
	{
		FrogEndCount = 0;
		BuildingDataBase::FrogPtr->InterActionOff();
		BuildingDataBase::FrogPtr->FlagUpSetting();
		PlayerObject->WinFSMSetting();
	}

	if (true == MouseEnd && 1 == MouseEndCount)
	{
		MouseEndCount = 0;
		BuildingDataBase::MousePtr->InterActionOff();
		BuildingDataBase::MousePtr->FlagUpSetting();
		PlayerObject->WinFSMSetting();
	}
}

void OverworldLevel::LevelChangeStart()
{
	if (nullptr == FEffect)
	{
		FEffect = GetLastTarget()->CreateEffect<FadeEffect>();
	}
	
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

	if (false == IsSet1)
	{
		// 카메라 세팅
		GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
		//GetMainCamera()->GetTransform()->SetLocalPosition({ 805, 1435, -620.0f });
		GetMainCamera()->GetTransform()->SetLocalPosition({ 1680, 1260, -620.0f });
		GetMainCamera()->SetSortType(0, SortType::ZSort);

		IsSet1 = true;
	}

	// CreateActor
	// Map
	{
		if (nullptr == MapObject)
		{
			MapObject = CreateActor<Overworld_Map>();
		}
		
		MapObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, 5 });
	}

	if (false == IsSet2)
	{
		// NPC
		{
			std::shared_ptr<AppleTraveller> NPCObject0 = CreateActor<AppleTraveller>();
			NPCObject0->GetTransform()->SetLocalPosition({ 1680 , 1325, 3 });
			NPCObject0->TextBoxPositionSetting();

			std::shared_ptr<Axeman> NPCObject1 = CreateActor<Axeman>();
			NPCObject1->GetTransform()->SetLocalPosition({ 3170 , 1350, 3 });
			NPCObject1->TextBoxPositionSetting();

			std::shared_ptr<Canteen> NPCObject2 = CreateActor<Canteen>();
			NPCObject2->GetTransform()->SetLocalPosition({ 2595 , 2040, 3 });
			NPCObject2->TextBoxPositionSetting();

			std::shared_ptr<Coin> NPCObject3 = CreateActor<Coin>();
			NPCObject3->GetTransform()->SetLocalPosition({ 2330 , 770, 3 });
			NPCObject3->TextBoxPositionSetting();

			std::shared_ptr<Fishgirl> NPCObject4 = CreateActor<Fishgirl>();
			NPCObject4->GetTransform()->SetLocalPosition({ 2860 , 445, -1 });
			NPCObject4->TextBoxPositionSetting();
		}
		// Building
		{
			std::shared_ptr<BuildingDataBase> HomeObject = CreateActor<BuildingDataBase>();
			HomeObject->BuildingSetting(BuildingValue::Home);
			HomeObject->GetTransform()->SetLocalPosition({ 780 , 1560, 3 });

			std::shared_ptr<BuildingDataBase> ZeplinObject = CreateActor<BuildingDataBase>();
			ZeplinObject->BuildingSetting(BuildingValue::Zeplin);
			ZeplinObject->GetTransform()->SetLocalPosition({ 3370 , 2015, 3 });

			std::shared_ptr<BuildingDataBase> FrogObject = CreateActor<BuildingDataBase>();
			FrogObject->BuildingSetting(BuildingValue::Frog);
			FrogObject->GetTransform()->SetLocalPosition({ 2200 , 370, -1 });

			std::shared_ptr<BuildingDataBase> Tutorial_FlyObject = CreateActor<BuildingDataBase>();
			Tutorial_FlyObject->BuildingSetting(BuildingValue::Tutorial_Fly);
			Tutorial_FlyObject->GetTransform()->SetLocalPosition({ 2800 , 2030, 3 });

			std::shared_ptr<BuildingDataBase> MouseObject = CreateActor<BuildingDataBase>();
			MouseObject->BuildingSetting(BuildingValue::Mouse);
			MouseObject->GetTransform()->SetLocalPosition({ 3280 , 620, 3 });

			std::shared_ptr<BuildingDataBase> DjimmiObject = CreateActor<BuildingDataBase>();
			DjimmiObject->BuildingSetting(BuildingValue::Djimmi);
			DjimmiObject->GetTransform()->SetLocalPosition({ 3670 , 1480, 3 });

			std::shared_ptr<BuildingDataBase> DragonObject = CreateActor<BuildingDataBase>();
			DragonObject->BuildingSetting(BuildingValue::Dragon);
			DragonObject->GetTransform()->SetLocalPosition({ 2280 , 1650, 3 });
		}

		IsSet2 = true;
	}
	// Character
	{
		if (nullptr == PlayerObject)
		{
			PlayerObject = CreateActor<Player_Overworld>();
			PlayerObject->GetTransform()->SetLocalPosition({ 1680 , 1260, 1 });
			//PlayerObject->GetTransform()->SetLocalPosition({ 805 , 1435, 1 });
			PlayerObject->SetColMap(PlayMap, PixelCollision::Coordinate::Custom);
		}
		
		PlayerObject->PlayerCollisionPtrOn();
	}
	// ColMap
	if (nullptr == ThisColMap)
	{
		ThisColMap = CreateActor<Overworld_ColMap>();
		ThisColMap->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, -15 });
	}
	{
		if (BlackBoxPtr == nullptr)
		{
			BlackBoxPtr = CreateActor<RoundBlackBox>();
		}

		BlackBoxPtr->BoxSettingReset();
		BlackBoxPtr->SetExit();
	}
	// ScreenSFX
	{
		//std::shared_ptr<Screen_FX> Object = CreateActor<Screen_FX>();
		//Object->GetTransform()->SetLocalPosition({ 640 , PlayMapHeight_Half - 100, -10 });
	}

	// GUI
	{
		if (nullptr == GUI)
		{
			GUI = GameEngineGUI::FindGUIWindowConvert<OverworldGUI>("OverworldGUI");
		}
		
		GUI->SetTarget(PlayerObject->GetTransform());
		GUI->SetOverworldPalyer(PlayerObject);

		GUI->PlayerDebugRenderOn = std::bind(&OverworldLevel::PlayerDebugRenderOn, this);
		GUI->PlayerDebugRenderOff = std::bind(&OverworldLevel::PlayerDebugRenderOff, this);
		GUI->ColMapRenderOn = std::bind(&OverworldLevel::LevelDebugOn, this);
		GUI->ColMapRenderOff = std::bind(&OverworldLevel::LevelDebugOff, this);
	}
	{
		if (nullptr == LoadingPtr)
		{
			LoadingPtr = CreateActor<Loading>();
		}
		LoadingPtr->SetLoadingPtrOff();
	}

	ReLoadSetting();
}
void OverworldLevel::LevelChangeEnd()
{
	if (nullptr != GameEngineTexture::Find("Overworld_Map.png"))
	{
		GameEngineTexture::UnLoad("Overworld_Map.png");
	}
	if (nullptr != GameEngineSprite::Find("Flag.png"))
	{
		GameEngineSprite::UnLoad("Flag.png");
		GameEngineSprite::UnLoad("FlagShadow.png");
		GameEngineSprite::UnLoad("To_Djimmi_The_Great.png");
		GameEngineSprite::UnLoad("To_Grim_Matchstick.png");
		GameEngineSprite::UnLoad("To_Hilda_Berg.png");
		GameEngineSprite::UnLoad("To_Ribby_and_Croaks.png");
		GameEngineSprite::UnLoad("To_Ribby_and_Croaks_Wave.png");
		GameEngineSprite::UnLoad("To_Tutorial_Fly.png");
		GameEngineSprite::UnLoad("To_WaittingRoom.png");
		GameEngineSprite::UnLoad("To_Werner_Werman.png");
	}
	if (nullptr != GameEngineTexture::Find("TitleCard_Back.png"))
	{
		GameEngineTexture::UnLoad("TitleCard_Back.png");
		GameEngineTexture::UnLoad("TitleCard_Title.png");
		GameEngineTexture::UnLoad("AND.png");
		GameEngineTexture::UnLoad("INS.png");
		GameEngineTexture::UnLoad("Logo.png");
		GameEngineTexture::UnLoad("CONFIRM_BACK.png");
		GameEngineTexture::UnLoad("Wouldyou.png");
		GameEngineTexture::UnLoad("Yes.png");
		GameEngineTexture::UnLoad("No.png");
		GameEngineTexture::UnLoad("SelectBox.png");
		GameEngineTexture::UnLoad("EnterSelectBox.png");
		GameEngineTexture::UnLoad("TitleCard_Title_Small.png");
		GameEngineTexture::UnLoad("Airplane_One.png");
		GameEngineTexture::UnLoad("Airplane_Two.png");
		GameEngineTexture::UnLoad("Enter.png");
	}
	if (nullptr != GameEngineSprite::Find("Title_Card.png"))
	{
		GameEngineSprite::UnLoad("Title_Card.png");
	}
	if (nullptr != GameEngineSprite::Find("AppleTraveller_Blink"))
	{
		GameEngineSprite::UnLoad("AppleTraveller_Blink");
		GameEngineSprite::UnLoad("AppleTraveller_HoboStick");
		GameEngineSprite::UnLoad("AppleTraveller_Idle");
		GameEngineSprite::UnLoad("AppleTraveller_Wave");
		GameEngineSprite::UnLoad("AppleTraveller_Wave_Intro");
		GameEngineSprite::UnLoad("AppleTraveller_Wave_Outro");
	}
	if (nullptr != GameEngineSprite::Find("Axeman_Idle"))
	{
		GameEngineSprite::UnLoad("Axeman_Idle");
	}
	if (nullptr != GameEngineSprite::Find("Canteen_Idle"))
	{
		GameEngineSprite::UnLoad("Canteen_Idle");
	}
	if (nullptr != GameEngineSprite::Find("Coin_Blink"))
	{
		GameEngineSprite::UnLoad("Coin_Blink");
		GameEngineSprite::UnLoad("Coin_Boil_A");
		GameEngineSprite::UnLoad("Coin_Hold_A");
		GameEngineSprite::UnLoad("Coin_Hold_B");
		GameEngineSprite::UnLoad("Coin_Hold_C");
		GameEngineSprite::UnLoad("Coin_Hold_D");
		GameEngineSprite::UnLoad("Coin_Transition_A");
		GameEngineSprite::UnLoad("Coin_Transition_B");
		GameEngineSprite::UnLoad("Coin_Transition_C");
		GameEngineSprite::UnLoad("Coin_Transition_D");
		GameEngineSprite::UnLoad("Coin_Transition_E");
		GameEngineSprite::UnLoad("Coin_Transition_F");
	}
	if (nullptr != GameEngineSprite::Find("FishGirl_Idle"))
	{
		GameEngineSprite::UnLoad("FishGirl_Idle");
		GameEngineSprite::UnLoad("FishGirl_Blink");
	}
	if (nullptr != GameEngineSprite::Find("DD_Idle"))
	{
		GameEngineSprite::UnLoad("DD_Idle");
		GameEngineSprite::UnLoad("DD_Move");
		GameEngineSprite::UnLoad("Down_Idle");
		GameEngineSprite::UnLoad("Down_Move");
		GameEngineSprite::UnLoad("DU_Idle");
		GameEngineSprite::UnLoad("DU_Move");
		GameEngineSprite::UnLoad("Side_Idle");
		GameEngineSprite::UnLoad("Side_Move");
		GameEngineSprite::UnLoad("Up_Idle");
		GameEngineSprite::UnLoad("Up_Move");
		GameEngineSprite::UnLoad("InterAction_Win");
	}
	if (nullptr != GameEngineTexture::Find("speech_bubble_box.png"))
	{
		GameEngineTexture::UnLoad("speech_bubble_box.png");
		GameEngineTexture::UnLoad("speech_balloon_tail_0001.png");
		GameEngineTexture::UnLoad("speech_balloon_tail_0004.png");
		GameEngineTexture::UnLoad("speech_balloon_tail_0009.png");
		GameEngineSprite::UnLoad("Arrow");
	}
	if (nullptr != GameEngineSprite::Find("Dust_A.png"))
	{
		GameEngineSprite::UnLoad("Dust_A.png");
		GameEngineSprite::UnLoad("Dust_B.png");
		GameEngineSprite::UnLoad("Dust_C.png");
	}

	{
		DebugBoxCount = 1;
		PlayerObject->InitReset();

		if (nullptr != BuildingDataBase::DjimmiPtr)
		{
			BuildingDataBase::DjimmiPtr->IsLevelChangeReset();
		}
		if (nullptr != BuildingDataBase::DragonPtr)
		{
			BuildingDataBase::DragonPtr->IsLevelChangeReset();
		}
		if (nullptr != BuildingDataBase::FrogPtr)
		{
			BuildingDataBase::FrogPtr->IsLevelChangeReset();
		}
		if (nullptr != BuildingDataBase::HomePtr)
		{
			BuildingDataBase::HomePtr->IsLevelChangeReset();
		}
		if (nullptr != BuildingDataBase::MousePtr)
		{
			BuildingDataBase::MousePtr->IsLevelChangeReset();
		}
		if (nullptr != BuildingDataBase::Tutorial_FlyPtr)
		{
			BuildingDataBase::Tutorial_FlyPtr->IsLevelChangeReset();
		}
		if (nullptr != BuildingDataBase::ZeplinPtr)
		{
			BuildingDataBase::ZeplinPtr->IsLevelChangeReset();
		}
	}
}

void OverworldLevel::ReLoadSetting()
{
	if (nullptr != GameEngineTexture::Find("Overworld_Map.png"))
	{
		GameEngineTexture::ReLoad("Overworld_Map.png");
	}
	if (nullptr != GameEngineSprite::Find("Flag.png"))
	{
		GameEngineSprite::ReLoad("Flag.png");
		GameEngineSprite::ReLoad("FlagShadow.png");
		GameEngineSprite::ReLoad("To_Djimmi_The_Great.png");
		GameEngineSprite::ReLoad("To_Grim_Matchstick.png");
		GameEngineSprite::ReLoad("To_Hilda_Berg.png");
		GameEngineSprite::ReLoad("To_Ribby_and_Croaks.png");
		GameEngineSprite::ReLoad("To_Ribby_and_Croaks_Wave.png");
		GameEngineSprite::ReLoad("To_Tutorial_Fly.png");
		GameEngineSprite::ReLoad("To_WaittingRoom.png");
		GameEngineSprite::ReLoad("To_Werner_Werman.png");
	}
	if (nullptr != GameEngineTexture::Find("TitleCard_Back.png"))
	{
		GameEngineTexture::ReLoad("TitleCard_Back.png");
		GameEngineTexture::ReLoad("TitleCard_Title.png");
		GameEngineTexture::ReLoad("AND.png");
		GameEngineTexture::ReLoad("INS.png");
		GameEngineTexture::ReLoad("Logo.png");
		GameEngineTexture::ReLoad("CONFIRM_BACK.png");
		GameEngineTexture::ReLoad("Wouldyou.png");
		GameEngineTexture::ReLoad("Yes.png");
		GameEngineTexture::ReLoad("No.png");
		GameEngineTexture::ReLoad("SelectBox.png");
		GameEngineTexture::ReLoad("EnterSelectBox.png");
		GameEngineTexture::ReLoad("TitleCard_Title_Small.png");
		GameEngineTexture::ReLoad("Airplane_One.png");
		GameEngineTexture::ReLoad("Airplane_Two.png");
		GameEngineTexture::ReLoad("Enter.png");
	}
	if (nullptr != GameEngineSprite::Find("Title_Card.png"))
	{
		GameEngineSprite::ReLoad("Title_Card.png");
	}
	if (nullptr != GameEngineSprite::Find("AppleTraveller_Blink"))
	{
		GameEngineSprite::ReLoad("AppleTraveller_Blink");
		GameEngineSprite::ReLoad("AppleTraveller_HoboStick");
		GameEngineSprite::ReLoad("AppleTraveller_Idle");
		GameEngineSprite::ReLoad("AppleTraveller_Wave");
		GameEngineSprite::ReLoad("AppleTraveller_Wave_Intro");
		GameEngineSprite::ReLoad("AppleTraveller_Wave_Outro");
	}
	if (nullptr != GameEngineSprite::Find("Axeman_Idle"))
	{
		GameEngineSprite::ReLoad("Axeman_Idle");
	}
	if (nullptr != GameEngineSprite::Find("Canteen_Idle"))
	{
		GameEngineSprite::ReLoad("Canteen_Idle");
	}
	if (nullptr != GameEngineSprite::Find("Coin_Blink"))
	{
		GameEngineSprite::ReLoad("Coin_Blink");
		GameEngineSprite::ReLoad("Coin_Boil_A");
		GameEngineSprite::ReLoad("Coin_Hold_A");
		GameEngineSprite::ReLoad("Coin_Hold_B");
		GameEngineSprite::ReLoad("Coin_Hold_C");
		GameEngineSprite::ReLoad("Coin_Hold_D");
		GameEngineSprite::ReLoad("Coin_Transition_A");
		GameEngineSprite::ReLoad("Coin_Transition_B");
		GameEngineSprite::ReLoad("Coin_Transition_C");
		GameEngineSprite::ReLoad("Coin_Transition_D");
		GameEngineSprite::ReLoad("Coin_Transition_E");
		GameEngineSprite::ReLoad("Coin_Transition_F");
	}
	if (nullptr != GameEngineSprite::Find("FishGirl_Idle"))
	{
		GameEngineSprite::ReLoad("FishGirl_Idle");
		GameEngineSprite::ReLoad("FishGirl_Blink");
	}
	if (nullptr != GameEngineTexture::Find("speech_bubble_box.png"))
	{
		GameEngineTexture::ReLoad("speech_bubble_box.png");
		GameEngineTexture::ReLoad("speech_balloon_tail_0001.png");
		GameEngineTexture::ReLoad("speech_balloon_tail_0004.png");
		GameEngineTexture::ReLoad("speech_balloon_tail_0009.png");
		GameEngineSprite::ReLoad("Arrow");
	}
	if (nullptr != GameEngineSprite::Find("DD_Idle"))
	{
		GameEngineSprite::ReLoad("DD_Idle");
		GameEngineSprite::ReLoad("DD_Move");
		GameEngineSprite::ReLoad("Down_Idle");
		GameEngineSprite::ReLoad("Down_Move");
		GameEngineSprite::ReLoad("DU_Idle");
		GameEngineSprite::ReLoad("DU_Move");
		GameEngineSprite::ReLoad("Side_Idle");
		GameEngineSprite::ReLoad("Side_Move");
		GameEngineSprite::ReLoad("Up_Idle");
		GameEngineSprite::ReLoad("Up_Move");
		GameEngineSprite::ReLoad("InterAction_Win");
	}
	if (nullptr != GameEngineSprite::Find("Dust_A.png"))
	{
		GameEngineSprite::ReLoad("Dust_A.png");
		GameEngineSprite::ReLoad("Dust_B.png");
		GameEngineSprite::ReLoad("Dust_C.png");
	}
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
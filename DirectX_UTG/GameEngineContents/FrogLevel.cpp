#include "PrecompileHeader.h"
#include "FrogLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "Frog_FrontObject.h"
#include "Frog_Map.h"
#include "Frog_ColMap.h"

#include "Player.h"
#include "Croak.h"
#include "Ribby.h"

#include "Cheerer.h"
#include "Craber.h"
#include "Crowd.h"
#include "Dancer.h"
#include "Deliver.h"

#include "CardUI.h"
#include "HealthUI.h"
#include "WeaponUI.h"

#include "Knockout.h"
#include "Ready_Wallop.h"
#include "You_Died.h"

#include "Loading.h"
#include "RoundBlackBox.h"
#include "OverworldLevel.h"
#include "TransformGUI.h"

FrogLevel* FrogLevel::FrogLevelPtr = nullptr;

FrogLevel::FrogLevel() 
{
}

FrogLevel::~FrogLevel() 
{
}

void FrogLevel::Start()
{
	FrogLevelPtr = this;
}
void FrogLevel::Update(float _DeltaTime)
{
	////////////////////////////////////////// Boss Clear //////////////////////////////////////////

	if (true == RibbyObject->GetIsStageEnd() && 1 == EndSetCount)
	{
		EndSetCount = 0;
		KnockoutPtr->StartMessage();
		IsBossEnd = true;
		GameEngineTime::GlobalTime.SetUpdateOrderTimeScale(0, 0.0f);
	}

	if (true == IsBossEnd)
	{
		EndTime += _DeltaTime;

		if (true == KnockoutPtr->GetIsEnd())
		{
			GameEngineTime::GlobalTime.SetUpdateOrderTimeScale(0, 1.0f);

			if (EndTime >= 3.0f && 1 == EndSetCount2)
			{
				EndSetCount2 = 0;
				BlackBoxPtr->BoxSettingReset();
				BlackBoxPtr->SetEnter();
			}
		}

		if (true == BlackBoxPtr->GetIsEnd() && 0 == EndSetCount2)
		{
			IsFrogLevelEnd = true;
			OverworldLevel::OverworldLevelPtr->SetFrogEnd();
			LoadingOn();
			GameEngineCore::ChangeLevel("OverworldLevel");
		}

		return;
	}

	////////////////////////////////////////// Player Death //////////////////////////////////////////

	if (true == PlayerObject->GetIsPlayerDeath() && 1 == EndSetCount)
	{
		EndSetCount = 0;
		YouDiedPtr->StartMessage();
		IsPlayerEnd = true;
	}

	if (true == IsPlayerEnd)
	{
		EndTime += _DeltaTime;

		if (true == YouDiedPtr->GetIsEnd())
		{
			if (EndTime >= 3.0f && 1 == EndSetCount2)
			{
				EndSetCount2 = 0;
				BlackBoxPtr->BoxSettingReset();
				BlackBoxPtr->SetEnter();
			}
		}

		if (true == BlackBoxPtr->GetIsEnd() && 0 == EndSetCount2)
		{
			LoadingOn();
			GameEngineCore::ChangeLevel("OverworldLevel");
		}

		return;
	}

	////////////////////////////////////////// Ready Wallop //////////////////////////////////////////

	ReadyWallopTime += _DeltaTime;

	if (1.5f <= ReadyWallopTime && 1 == ReadyWallopCount)
	{
		ReadyWallopCount = 0;
		ReadyWallopPtr->StartMessage();
	}

	// readywallop이 끝나는 시점에 게임 시작
	if (true == ReadyWallopPtr->GetIsEnd())
	{
		int a = 0;
	}

	if (true == GameEngineInput::IsDown("PrevLevel"))
	{
		GameEngineCore::ChangeLevel("OverworldLevel");
	}
}

void FrogLevel::LevelChangeStart()
{
	if (nullptr == GameEngineTexture::Find("Frog_ColMap.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("1_Ribby_and_Croaks");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Frog_ColMap.png").GetFullPath());
	}

	// ColMap
	std::shared_ptr<GameEngineTexture> PlayMap = GameEngineTexture::Find("Frog_ColMap.png");
	int PlayMapWidth = PlayMap->GetWidth();
	int PlayMapHeight = PlayMap->GetHeight();
	float PlayMapWidth_Half = static_cast<float>(PlayMapWidth / 2);
	float PlayMapHeight_Half = static_cast<float>(PlayMapHeight / 2);

	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 640, PlayMapHeight_Half + 10, -620.0f });
	GetMainCamera()->SetSortType(0, SortType::ZSort);

	{
		if (nullptr == MapObject)
		{
			MapObject = CreateActor<Frog_Map>();
		}
		
		MapObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, 10 });
	}
	{
		if (nullptr == DancerObject)
		{
			DancerObject = CreateActor<Dancer>();
		}
		if (nullptr == CheererObject)
		{
			CheererObject = CreateActor<Cheerer>();
		}
		if (nullptr == CraberObject)
		{
			CraberObject = CreateActor<Craber>();
		}
		if (nullptr == DeliverObject)
		{
			DeliverObject = CreateActor<Deliver>();
		}
		if (nullptr == CrowdObject)
		{
			CrowdObject = CreateActor<Crowd>();
		}

		DancerObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half + 20, PlayMapHeight_Half + 88, 10 });
		CheererObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half - 210, PlayMapHeight_Half + 50, 10 });
		CraberObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half - 530, PlayMapHeight_Half + 30, 10 });
		DeliverObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half - 750, PlayMapHeight_Half + 30, 10 });
		DeliverObject->SetStartPosition(DeliverObject->GetTransform()->GetLocalPosition());
		CrowdObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half + 15, PlayMapHeight_Half, 7 });
	}
	{
		if (nullptr == RibbyObject)
		{
			RibbyObject = CreateActor<Ribby>();
		}
		if (nullptr == CroakObject)
		{
			CroakObject = CreateActor<Croak>();
		}
		
		RibbyObject->GetTransform()->SetLocalPosition({ 1020 , 280 });
		RibbyObject->SetInitReset();

		CroakObject->GetTransform()->SetLocalPosition({ 1120 , 440, 1 });
		CroakObject->SetInitReset();
	}
	{
		if (nullptr == PlayerObject)
		{
			PlayerObject = CreateActor<Player>();
		}
		
		PlayerObject->GetTransform()->SetLocalPosition({ 220 , PlayMapHeight_Half });
		PlayerObject->SetColMap(PlayMap, PixelCollision::Coordinate::Custom);
		PlayerObject->SetCameraSpeedRatio(1.0f);
		PlayerObject->SetCorrectionFalse();
		PlayerObject->PlayerReset();
		PlayerObject->SetIntro();
	}
	{
		if (nullptr == FrontObject)
		{
			FrontObject = CreateActor<Frog_FrontObject>();
		}

		FrontObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, -4 });
	}
	{
		if (nullptr == ThisColMap)
		{
			ThisColMap = CreateActor<Frog_ColMap>();
		}
		
		ThisColMap->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, -5 });
	}
	{
		if (nullptr == WeaponObject)
		{
			WeaponObject = CreateActor<WeaponUI>();
		}
		if (nullptr == HealthObject)
		{
			HealthObject = CreateActor<HealthUI>();
		}
		if (nullptr == CardObject)
		{
			CardObject = CreateActor<CardUI>();
		}

		WeaponObject->GetTransform()->SetLocalPosition({ -585, -335 });
		WeaponObject->SetMainPalyer(PlayerObject);
		WeaponObject->StartPositionSetting(WeaponObject->GetTransform()->GetLocalPosition());
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
	{
		if (KnockoutPtr == nullptr)
		{
			KnockoutPtr = CreateActor<Knockout>(1);
		}

		KnockoutPtr->MessageReset();
	}
	{
		if (YouDiedPtr == nullptr)
		{
			YouDiedPtr = CreateActor<You_Died>();
		}

		YouDiedPtr->MessageReset();
	}
	{
		if (ReadyWallopPtr == nullptr)
		{
			ReadyWallopPtr = CreateActor<Ready_Wallop>();
		}

		ReadyWallopPtr->MessageReset();
	}

	// GUI
	{
		if (nullptr == GUI)
		{
			GUI = GameEngineGUI::FindGUIWindowConvert<TransformGUI>("TransformGUI");
		}

		GUI->SetTarget(PlayerObject->GetTransform());
		GUI->SetMainPalyer(PlayerObject);
		GUI->SetFrogBoss(CroakObject);

		GUI->PlayerDebugRenderOn = std::bind(&FrogLevel::PlayerDebugRenderOn, this);
		GUI->PlayerDebugRenderOff = std::bind(&FrogLevel::PlayerDebugRenderOff, this);
		GUI->ColMapRenderOn = std::bind(&FrogLevel::LevelDebugOn, this);
		GUI->ColMapRenderOff = std::bind(&FrogLevel::LevelDebugOff, this);
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

void FrogLevel::LevelChangeEnd()
{
	if (nullptr != GameEngineTexture::Find("Backstage_1.png"))
	{
		GameEngineTexture::UnLoad("Backstage_1.png");
		GameEngineTexture::UnLoad("Backstage_2.png");
		GameEngineTexture::UnLoad("Backstage_3.png");
	}
	if (nullptr != GameEngineSprite::Find("Cheerer"))
	{
		GameEngineSprite::UnLoad("Cheerer");
		GameEngineSprite::UnLoad("Craber");
		GameEngineSprite::UnLoad("Crowd");
		GameEngineSprite::UnLoad("Dancer");
		GameEngineSprite::UnLoad("Deliver");
	}
	if (nullptr != GameEngineTexture::Find("Plant_1.png"))
	{
		GameEngineTexture::UnLoad("Table_1.png");
		GameEngineTexture::UnLoad("Table_2.png");
		GameEngineTexture::UnLoad("Plant_1.png");
		GameEngineTexture::UnLoad("Plant_2.png");
		GameEngineTexture::UnLoad("Plant_3.png");
	}
	if (nullptr != GameEngineSprite::Find("Ribby_Idle"))
	{
		GameEngineSprite::UnLoad("Ribby_Intro");
		GameEngineSprite::UnLoad("Ribby_Intro_Loop");
		GameEngineSprite::UnLoad("Ribby_Intro_End");
		GameEngineSprite::UnLoad("Ribby_Idle");
	}
	if (nullptr != GameEngineTexture::Find("Peashooter_Spawn.png"))
	{
		GameEngineSprite::UnLoad("Peashooter_Spawn.png");
		GameEngineSprite::UnLoad("Peashooter_Loop.png");
		GameEngineSprite::UnLoad("Peashooter_Death.png");
		GameEngineSprite::UnLoad("Peashooter_EX_Loop.png");
		GameEngineSprite::UnLoad("Peashooter_EX_Death.png");
	}
	if (nullptr != GameEngineTexture::Find("Spread_Spawn.png"))
	{
		GameEngineSprite::UnLoad("Spread_Spawn.png");
		GameEngineSprite::UnLoad("Spread_Loop.png");
		GameEngineSprite::UnLoad("Spread_Death.png");
		GameEngineSprite::UnLoad("Spread_Death_Enemyhit.png");
		GameEngineSprite::UnLoad("Spread_Weak_Loop.png");
		GameEngineSprite::UnLoad("Spread_Weak_Death.png");
		GameEngineSprite::UnLoad("Spread_Weak_Death_Enemyhit.png");
		GameEngineSprite::UnLoad("Spread_EX_Spawn.png");
		GameEngineSprite::UnLoad("Spread_EX_Loop.png");
		GameEngineSprite::UnLoad("Spread_EX_Flame.png");
		GameEngineSprite::UnLoad("Spread_EX_Death.png");
	}
	if (nullptr != GameEngineTexture::Find("Dust_A.png"))
	{
		GameEngineSprite::UnLoad("Dust_A.png");
		GameEngineSprite::UnLoad("Dust_B.png");
		GameEngineSprite::UnLoad("Dust_C.png");
	}
	if (nullptr != GameEngineSprite::Find("JumpDust"))
	{
		GameEngineSprite::UnLoad("JumpDust");
		GameEngineSprite::UnLoad("DashDust");
		GameEngineSprite::UnLoad("EXDust");
		GameEngineSprite::UnLoad("EX_ChargeUp");
		GameEngineSprite::UnLoad("ParryEffect");
		GameEngineSprite::UnLoad("HitSFX");
	}
	if (nullptr != GameEngineSprite::Find("KNOCKOUT"))
	{
		GameEngineSprite::UnLoad("KNOCKOUT");
	}
	if (nullptr != GameEngineSprite::Find("YOU_DIED.png"))
	{
		GameEngineSprite::UnLoad("YOU_DIED.png");
	}
	if (nullptr != GameEngineSprite::Find("Ready_WALLOP"))
	{
		GameEngineSprite::UnLoad("Ready_WALLOP");
	}

	{
		ReadyWallopCount = 1;
		ReadyWallopTime = 0.0f;
		EndTime = 0.0f;
		IsBossEnd = false;
		IsFrogLevelEnd = false;
		IsPlayerEnd = false;
		EndSetCount = 1;
		EndSetCount2 = 1;

		CardObject->CartUIReset();
		PlayerObject->MoveAbleTimeReset();
	}

}

void FrogLevel::ReLoadSetting()
{
	if (nullptr != GameEngineTexture::Find("Backstage_1.png"))
	{
		GameEngineTexture::ReLoad("Backstage_1.png");
		GameEngineTexture::ReLoad("Backstage_2.png");
		GameEngineTexture::ReLoad("Backstage_3.png");
	}
	if (nullptr != GameEngineSprite::Find("Cheerer"))
	{
		GameEngineSprite::ReLoad("Cheerer");
		GameEngineSprite::ReLoad("Craber");
		GameEngineSprite::ReLoad("Crowd");
		GameEngineSprite::ReLoad("Dancer");
		GameEngineSprite::ReLoad("Deliver");
	}
	if (nullptr != GameEngineTexture::Find("Plant_1.png"))
	{
		GameEngineTexture::ReLoad("Table_1.png");
		GameEngineTexture::ReLoad("Table_2.png");
		GameEngineTexture::ReLoad("Plant_1.png");
		GameEngineTexture::ReLoad("Plant_2.png");
		GameEngineTexture::ReLoad("Plant_3.png");
	}
	if (nullptr != GameEngineSprite::Find("Ribby_Idle"))
	{
		GameEngineSprite::ReLoad("Ribby_Intro");
		GameEngineSprite::ReLoad("Ribby_Intro_Loop");
		GameEngineSprite::ReLoad("Ribby_Intro_End");
		GameEngineSprite::ReLoad("Ribby_Idle");
	}
	if (nullptr != GameEngineTexture::Find("Peashooter_Spawn.png"))
	{
		GameEngineSprite::ReLoad("Peashooter_Spawn.png");
		GameEngineSprite::ReLoad("Peashooter_Loop.png");
		GameEngineSprite::ReLoad("Peashooter_Death.png");
		GameEngineSprite::ReLoad("Peashooter_EX_Loop.png");
		GameEngineSprite::ReLoad("Peashooter_EX_Death.png");
	}
	if (nullptr != GameEngineTexture::Find("Spread_Spawn.png"))
	{
		GameEngineSprite::ReLoad("Spread_Spawn.png");
		GameEngineSprite::ReLoad("Spread_Loop.png");
		GameEngineSprite::ReLoad("Spread_Death.png");
		GameEngineSprite::ReLoad("Spread_Death_Enemyhit.png");
		GameEngineSprite::ReLoad("Spread_Weak_Loop.png");
		GameEngineSprite::ReLoad("Spread_Weak_Death.png");
		GameEngineSprite::ReLoad("Spread_Weak_Death_Enemyhit.png");
		GameEngineSprite::ReLoad("Spread_EX_Spawn.png");
		GameEngineSprite::ReLoad("Spread_EX_Loop.png");
		GameEngineSprite::ReLoad("Spread_EX_Flame.png");
		GameEngineSprite::ReLoad("Spread_EX_Death.png");
	}
	if (nullptr != GameEngineTexture::Find("Dust_A.png"))
	{
		GameEngineSprite::ReLoad("Dust_A.png");
		GameEngineSprite::ReLoad("Dust_B.png");
		GameEngineSprite::ReLoad("Dust_C.png");
	}
	if (nullptr != GameEngineSprite::Find("JumpDust"))
	{
		GameEngineSprite::ReLoad("JumpDust");
		GameEngineSprite::ReLoad("DashDust");
		GameEngineSprite::ReLoad("EXDust");
		GameEngineSprite::ReLoad("EX_ChargeUp");
		GameEngineSprite::ReLoad("ParryEffect");
		GameEngineSprite::ReLoad("HitSFX");
	}
	if (nullptr != GameEngineSprite::Find("KNOCKOUT"))
	{
		GameEngineSprite::ReLoad("KNOCKOUT");
	}
	if (nullptr != GameEngineSprite::Find("YOU_DIED.png"))
	{
		GameEngineSprite::ReLoad("YOU_DIED.png");
	}
	if (nullptr != GameEngineSprite::Find("Ready_WALLOP"))
	{
		GameEngineSprite::ReLoad("Ready_WALLOP");
	}
}

void FrogLevel::PlayerDebugRenderOn()
{
	if (nullptr != PlayerObject)
	{
		PlayerObject->PlayerDebugRenderOn();
	}
}

void FrogLevel::PlayerDebugRenderOff()
{
	if (nullptr != PlayerObject)
	{
		PlayerObject->PlayerDebugRenderOff();
	}
}

void FrogLevel::LevelDebugOn()
{
	if (nullptr != ThisColMap)
	{
		ThisColMap->ColMapDebugRenderOn();
	}
	if (nullptr != RibbyObject)
	{
		RibbyObject->DebugRenderOn();
		CroakObject->DebugRenderOn();
	}
}
void FrogLevel::LevelDebugOff()
{
	if (nullptr != ThisColMap)
	{
		ThisColMap->ColMapDebugRenderOff();
	}
	if (nullptr != RibbyObject)
	{
		RibbyObject->DebugRenderOff();
		CroakObject->DebugRenderOff();
	}
}
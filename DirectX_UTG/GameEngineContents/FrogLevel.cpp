#include "PrecompileHeader.h"
#include "FrogLevel.h"

#include <GameEngineBase/GameEngineRandom.h>
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

#include "LoadingLevel.h"
#include "OverworldLevel.h"

#include "RoundBlackBox.h"
#include "TransformGUI.h"

#include <GameEngineCore/BlurEffect.h>
#include "OldFilm.h"

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
	GetLastTarget()->CreateEffect<BlurEffect>();
	GetLastTarget()->CreateEffect<OldFilm>();

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Sound");
		NewDir.Move("1_Ribby_and_Croaks");

		GameEngineSound::Load(NewDir.GetPlusFileName("Clip Joint Calamity.mp3").GetFullPath());
	}
}
void FrogLevel::Update(float _DeltaTime)
{
	if (false == IsVoiceOn)
	{
		IsVoiceOn = true;
		StartVoiceSound();
	}

	BGMDelayTime += _DeltaTime;

	if (false == IsBGMOn && 0.4f <= BGMDelayTime)
	{
		IsBGMOn = true;
		BGMPlayer = GameEngineSound::Play("Clip Joint Calamity.mp3");
		BGMPlayer.SetLoop(100);
	}

	////////////////////////////////////////// Boss Clear //////////////////////////////////////////

	if (true == CroakObject->GetIsStageEnd() && 1 == EndSetCount)
	{
		KnockSound();
		BGMPlayer.Stop();
		PlayerObject->SetPlayerSoundOff();
		PlayerObject->SetStageEndHP();
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

			if (false == IsEndSound)
			{
				IsEndSound = true;
				BGMPlayer = GameEngineSound::Play("knockout_boom_01.wav");
			}

			if (false == IsEndSound2 && EndTime >= 3.4f)
			{
				IsEndSound2 = true;
				BGMPlayer = GameEngineSound::Play("level_boss_defeat_sting_08.wav");
			}

			if (EndTime >= 4.5f && 1 == EndSetCount2)
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
			LoadingLevel::LoadingLevelPtr->SetLevelState(LevelValue::OverworldLevel);
			GameEngineCore::ChangeLevel("LoadingLevel");
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
				BGMPlayer.Stop();
				BGMPlayer = GameEngineSound::Play("WorldMap_LevelSelect_DiffucultySettings_Appear.wav");
				BlackBoxPtr->BoxSettingReset();
				BlackBoxPtr->SetEnter();
			}
		}

		if (true == BlackBoxPtr->GetIsEnd() && 0 == EndSetCount2)
		{
			LoadingLevel::LoadingLevelPtr->SetLevelState(LevelValue::OverworldLevel);
			GameEngineCore::ChangeLevel("LoadingLevel");
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

	if (true == GameEngineInput::IsDown("BossHpDown"))
	{
		CroakObject->CroakPtr->BossHPDown();
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
		
		PlayerObject->GetTransform()->SetLocalPosition({ 220 , PlayMapHeight_Half, -1 });
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

	ReLoadSetting();
}

void FrogLevel::LevelChangeEnd()
{
	BGMPlayer.Stop();

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
	if (nullptr != GameEngineSprite::Find("Ribby_Idle"))
	{
		GameEngineSprite::UnLoad("Ribby_Intro");
		GameEngineSprite::UnLoad("Ribby_Intro_Loop");
		GameEngineSprite::UnLoad("Ribby_Intro_End");
		GameEngineSprite::UnLoad("Ribby_Idle");

		GameEngineSprite::UnLoad("Ribby_FistAttack_Intro");
		GameEngineSprite::UnLoad("Ribby_FistAttack_Intro_Loop");
		GameEngineSprite::UnLoad("Ribby_FistAttack_Intro_out");
		GameEngineSprite::UnLoad("Ribby_FistAttack_Loop");
		GameEngineSprite::UnLoad("Ribby_FistAttack_End");

		GameEngineSprite::UnLoad("Ribby_Roll_Intro");
		GameEngineSprite::UnLoad("Ribby_Roll_Intro_Loop");
		GameEngineSprite::UnLoad("Ribby_Roll_Intro_Out");
		GameEngineSprite::UnLoad("Ribby_Roll_Loop");
		GameEngineSprite::UnLoad("Ribby_Roll_End");

		GameEngineSprite::UnLoad("Ribby_ClapAttack_Intro");
		GameEngineSprite::UnLoad("Ribby_ClapAttack");
		GameEngineSprite::UnLoad("Ribby_ClapAttack_Loop");
		GameEngineSprite::UnLoad("Ribby_ClapAttack_LoopBack");
		GameEngineSprite::UnLoad("Ribby_ClapAttack_End");
	}
	if (nullptr != GameEngineSprite::Find("Normal_Loop"))
	{
		GameEngineSprite::UnLoad("Normal_Loop");
		GameEngineSprite::UnLoad("Normal_Spawn");
		GameEngineSprite::UnLoad("Pink_Loop");
		GameEngineSprite::UnLoad("Pink_Spawn");
		GameEngineSprite::UnLoad("Spark");
		GameEngineSprite::UnLoad("Death_FX");
	}
	if (nullptr != GameEngineSprite::Find("Clap_Ball"))
	{
		GameEngineSprite::UnLoad("Clap_Ball");
		GameEngineSprite::UnLoad("Clap_FX");
	}
	if (nullptr != GameEngineSprite::Find("Croaks_Intro"))
	{
		GameEngineSprite::UnLoad("Croaks_Intro");
		GameEngineSprite::UnLoad("Croaks_Idle");

		GameEngineSprite::UnLoad("Croaks_CreateMob_Start");
		GameEngineSprite::UnLoad("Croaks_CreateMob_Start_Loop");
		GameEngineSprite::UnLoad("Croaks_CreateMob_Start_Out");
		GameEngineSprite::UnLoad("Croaks_CreateMob");
		GameEngineSprite::UnLoad("Croaks_CreateMob_End");

		GameEngineSprite::UnLoad("Croaks_Fan_Intro");
		GameEngineSprite::UnLoad("Croaks_Fan_LoopA");
		GameEngineSprite::UnLoad("Croaks_Fan_LoopB");
		GameEngineSprite::UnLoad("Croaks_Fan_Outro");

		GameEngineSprite::UnLoad("Croaks_Fan_Wind_Intro");
		GameEngineSprite::UnLoad("Croaks_Fan_Wind_Loop");
	}
	if (nullptr != GameEngineSprite::Find("Slot_Idle"))
	{
		GameEngineSprite::UnLoad("Slot_Morph_Intro");
		GameEngineSprite::UnLoad("Slot_Morph_Intro_Loop");
		GameEngineSprite::UnLoad("Slot_Morph_Outro");

		GameEngineSprite::UnLoad("Slot_Idle");
		GameEngineSprite::UnLoad("Slot_InitialOpen");
		GameEngineSprite::UnLoad("Slot_ArmMove_Intro");
		GameEngineSprite::UnLoad("Slot_ArmMove_Loop");
		GameEngineSprite::UnLoad("Slot_ArmMove_Outro");

		GameEngineSprite::UnLoad("Slot_Attack_Intro");
		GameEngineSprite::UnLoad("Slot_Attack_Loop");
		GameEngineSprite::UnLoad("Slot_Attack_Outro");

		GameEngineSprite::UnLoad("Slot_Death_Intro");
		GameEngineSprite::UnLoad("Slot_Death_Loop");
	}
	if (nullptr != GameEngineSprite::Find("Firefly_Death"))
	{
		GameEngineSprite::UnLoad("Firefly_Death");
		GameEngineSprite::UnLoad("Firefly_Down");
		GameEngineSprite::UnLoad("Firefly_Idle");
		GameEngineSprite::UnLoad("Firefly_Left");
		GameEngineSprite::UnLoad("Firefly_Up");
	}
	if (nullptr != GameEngineSprite::Find("Slot_CoinMouth"))
	{
		GameEngineSprite::UnLoad("Slot_CoinMouth");
		GameEngineSprite::UnLoad("Coin_Projectile");
	}
	if (nullptr != GameEngineSprite::Find("Slot_Dust_Front"))
	{
		GameEngineSprite::UnLoad("Slot_Dust_Front");
	}
	if (nullptr != GameEngineTexture::Find("Slot_TEMP.png"))
	{
		GameEngineTexture::UnLoad("Slot_TEMP.png");
		GameEngineTexture::UnLoad("Slot_flash_TEMP.png");
		GameEngineTexture::UnLoad("Slot_ImageBack.png");
	}
	if (nullptr != GameEngineTexture::Find("SlotMachine_Attack_Front_001.png"))
	{
		GameEngineTexture::UnLoad("SlotMachine_Attack_Front_001.png");
		GameEngineTexture::UnLoad("SlotMachine_Attack_Front_002.png");
		GameEngineTexture::UnLoad("SlotMachine_Attack_Front_003.png");
		GameEngineTexture::UnLoad("SlotMachine_Attack_Front_004.png");
		GameEngineTexture::UnLoad("SlotMachine_Attack_Front_005.png");
		GameEngineTexture::UnLoad("SlotMachine_Attack_Front_006.png");
	}
	if (nullptr != GameEngineSprite::Find("Explosion"))
	{
		GameEngineSprite::UnLoad("Explosion");
	}
	if (nullptr != GameEngineSprite::Find("Snake_Platform"))
	{
		GameEngineSprite::UnLoad("Snake_Platform");
		GameEngineSprite::UnLoad("Tiger_Ball");
		GameEngineSprite::UnLoad("Tiger_Platform");
		GameEngineSprite::UnLoad("Bison_Flame_Large_Intro");
		GameEngineSprite::UnLoad("Bison_Flame_Large_Loop");
		GameEngineSprite::UnLoad("Bison_Flame_Small_Loop");
		GameEngineSprite::UnLoad("Bison_Platform");
	}
	if (nullptr != GameEngineTexture::Find("Platform_Bison_Front_001.png"))
	{
		GameEngineTexture::UnLoad("Platform_Bison_Front_001.png");
		GameEngineTexture::UnLoad("Platform_Bison_Front_002.png");
		GameEngineTexture::UnLoad("Platform_Bison_Front_003.png");
		GameEngineTexture::UnLoad("Platform_Bison_Front_004.png");
		GameEngineTexture::UnLoad("Platform_Bison_Front_005.png");
		GameEngineTexture::UnLoad("Platform_Bison_Front_006.png");
		GameEngineTexture::UnLoad("Platform_Bison_Front_007.png");
		GameEngineTexture::UnLoad("Platform_Bison_Front_008.png");
		GameEngineTexture::UnLoad("Platform_Bison_Front_009.png");
		GameEngineTexture::UnLoad("Platform_Bison_Front_010.png");
	}
	if (nullptr != GameEngineTexture::Find("Platform_Tiger_Front_001.png"))
	{
		GameEngineTexture::UnLoad("Platform_Tiger_Front_001.png");
		GameEngineTexture::UnLoad("Platform_Tiger_Front_002.png");
		GameEngineTexture::UnLoad("Platform_Tiger_Front_003.png");
		GameEngineTexture::UnLoad("Platform_Tiger_Front_004.png");
		GameEngineTexture::UnLoad("Platform_Tiger_Front_005.png");
		GameEngineTexture::UnLoad("Platform_Tiger_Front_006.png");
		GameEngineTexture::UnLoad("Platform_Tiger_Front_007.png");
		GameEngineTexture::UnLoad("Platform_Tiger_Front_008.png");
		GameEngineTexture::UnLoad("Platform_Tiger_Front_009.png");
		GameEngineTexture::UnLoad("Platform_Tiger_Front_010.png");
	}

	{
		BGMDelayTime = 0.0f;
		IsVoiceOn = false;
		IsBGMOn = false;
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
	if (nullptr != GameEngineSprite::Find("Ribby_Idle"))
	{
		GameEngineSprite::ReLoad("Ribby_Intro");
		GameEngineSprite::ReLoad("Ribby_Intro_Loop");
		GameEngineSprite::ReLoad("Ribby_Intro_End");
		GameEngineSprite::ReLoad("Ribby_Idle");

		GameEngineSprite::ReLoad("Ribby_FistAttack_Intro");
		GameEngineSprite::ReLoad("Ribby_FistAttack_Intro_Loop");
		GameEngineSprite::ReLoad("Ribby_FistAttack_Intro_out");
		GameEngineSprite::ReLoad("Ribby_FistAttack_Loop");
		GameEngineSprite::ReLoad("Ribby_FistAttack_End");

		GameEngineSprite::ReLoad("Ribby_Roll_Intro");
		GameEngineSprite::ReLoad("Ribby_Roll_Intro_Loop");
		GameEngineSprite::ReLoad("Ribby_Roll_Intro_Out");
		GameEngineSprite::ReLoad("Ribby_Roll_Loop");
		GameEngineSprite::ReLoad("Ribby_Roll_End");

		GameEngineSprite::ReLoad("Ribby_ClapAttack_Intro");
		GameEngineSprite::ReLoad("Ribby_ClapAttack");
		GameEngineSprite::ReLoad("Ribby_ClapAttack_Loop");
		GameEngineSprite::ReLoad("Ribby_ClapAttack_LoopBack");
		GameEngineSprite::ReLoad("Ribby_ClapAttack_End");
	}
	if (nullptr != GameEngineSprite::Find("Normal_Loop"))
	{
		GameEngineSprite::ReLoad("Normal_Loop");
		GameEngineSprite::ReLoad("Normal_Spawn");
		GameEngineSprite::ReLoad("Pink_Loop");
		GameEngineSprite::ReLoad("Pink_Spawn");
		GameEngineSprite::ReLoad("Spark");
		GameEngineSprite::ReLoad("Death_FX");
	}
	if (nullptr != GameEngineSprite::Find("Clap_Ball"))
	{
		GameEngineSprite::ReLoad("Clap_Ball");
		GameEngineSprite::ReLoad("Clap_FX");
	}
	if (nullptr != GameEngineSprite::Find("Croaks_Intro"))
	{
		GameEngineSprite::ReLoad("Croaks_Intro");
		GameEngineSprite::ReLoad("Croaks_Idle");

		GameEngineSprite::ReLoad("Croaks_CreateMob_Start");
		GameEngineSprite::ReLoad("Croaks_CreateMob_Start_Loop");
		GameEngineSprite::ReLoad("Croaks_CreateMob_Start_Out");
		GameEngineSprite::ReLoad("Croaks_CreateMob");
		GameEngineSprite::ReLoad("Croaks_CreateMob_End");

		GameEngineSprite::ReLoad("Croaks_Fan_Intro");
		GameEngineSprite::ReLoad("Croaks_Fan_LoopA");
		GameEngineSprite::ReLoad("Croaks_Fan_LoopB");
		GameEngineSprite::ReLoad("Croaks_Fan_Outro");

		GameEngineSprite::ReLoad("Croaks_Fan_Wind_Intro");
		GameEngineSprite::ReLoad("Croaks_Fan_Wind_Loop");
	}
	if (nullptr != GameEngineSprite::Find("Slot_Idle"))
	{
		GameEngineSprite::ReLoad("Slot_Morph_Intro");
		GameEngineSprite::ReLoad("Slot_Morph_Intro_Loop");
		GameEngineSprite::ReLoad("Slot_Morph_Outro");

		GameEngineSprite::ReLoad("Slot_Idle");
		GameEngineSprite::ReLoad("Slot_InitialOpen");
		GameEngineSprite::ReLoad("Slot_ArmMove_Intro");
		GameEngineSprite::ReLoad("Slot_ArmMove_Loop");
		GameEngineSprite::ReLoad("Slot_ArmMove_Outro");

		GameEngineSprite::ReLoad("Slot_Attack_Intro");
		GameEngineSprite::ReLoad("Slot_Attack_Loop");
		GameEngineSprite::ReLoad("Slot_Attack_Outro");

		GameEngineSprite::ReLoad("Slot_Death_Intro");
		GameEngineSprite::ReLoad("Slot_Death_Loop");
	}
	if (nullptr != GameEngineSprite::Find("Firefly_Death"))
	{
		GameEngineSprite::ReLoad("Firefly_Death");
		GameEngineSprite::ReLoad("Firefly_Down");
		GameEngineSprite::ReLoad("Firefly_Idle");
		GameEngineSprite::ReLoad("Firefly_Left");
		GameEngineSprite::ReLoad("Firefly_Up");
	}
	if (nullptr != GameEngineSprite::Find("Slot_CoinMouth"))
	{
		GameEngineSprite::ReLoad("Slot_CoinMouth");
		GameEngineSprite::ReLoad("Coin_Projectile");
	}
	if (nullptr != GameEngineSprite::Find("Slot_Dust_Front"))
	{
		GameEngineSprite::ReLoad("Slot_Dust_Front");
	}
	if (nullptr != GameEngineTexture::Find("Slot_TEMP.png"))
	{
		GameEngineTexture::ReLoad("Slot_TEMP.png");
		GameEngineTexture::ReLoad("Slot_flash_TEMP.png");
		GameEngineTexture::ReLoad("Slot_ImageBack.png");
	}
	if (nullptr != GameEngineTexture::Find("SlotMachine_Attack_Front_001.png"))
	{
		GameEngineTexture::ReLoad("SlotMachine_Attack_Front_001.png");
		GameEngineTexture::ReLoad("SlotMachine_Attack_Front_002.png");
		GameEngineTexture::ReLoad("SlotMachine_Attack_Front_003.png");
		GameEngineTexture::ReLoad("SlotMachine_Attack_Front_004.png");
		GameEngineTexture::ReLoad("SlotMachine_Attack_Front_005.png");
		GameEngineTexture::ReLoad("SlotMachine_Attack_Front_006.png");
	}
	if (nullptr != GameEngineSprite::Find("Explosion"))
	{
		GameEngineSprite::ReLoad("Explosion");
	}
	if (nullptr != GameEngineSprite::Find("Snake_Platform"))
	{
		GameEngineSprite::ReLoad("Snake_Platform");
		GameEngineSprite::ReLoad("Tiger_Ball");
		GameEngineSprite::ReLoad("Tiger_Platform");
		GameEngineSprite::ReLoad("Bison_Flame_Large_Intro");
		GameEngineSprite::ReLoad("Bison_Flame_Large_Loop");
		GameEngineSprite::ReLoad("Bison_Flame_Small_Loop");
		GameEngineSprite::ReLoad("Bison_Platform");
	}
	if (nullptr != GameEngineTexture::Find("Platform_Bison_Front_001.png"))
	{
		GameEngineTexture::ReLoad("Platform_Bison_Front_001.png");
		GameEngineTexture::ReLoad("Platform_Bison_Front_002.png");
		GameEngineTexture::ReLoad("Platform_Bison_Front_003.png");
		GameEngineTexture::ReLoad("Platform_Bison_Front_004.png");
		GameEngineTexture::ReLoad("Platform_Bison_Front_005.png");
		GameEngineTexture::ReLoad("Platform_Bison_Front_006.png");
		GameEngineTexture::ReLoad("Platform_Bison_Front_007.png");
		GameEngineTexture::ReLoad("Platform_Bison_Front_008.png");
		GameEngineTexture::ReLoad("Platform_Bison_Front_009.png");
		GameEngineTexture::ReLoad("Platform_Bison_Front_010.png");
	}
	if (nullptr != GameEngineTexture::Find("Platform_Tiger_Front_001.png"))
	{
		GameEngineTexture::ReLoad("Platform_Tiger_Front_001.png");
		GameEngineTexture::ReLoad("Platform_Tiger_Front_002.png");
		GameEngineTexture::ReLoad("Platform_Tiger_Front_003.png");
		GameEngineTexture::ReLoad("Platform_Tiger_Front_004.png");
		GameEngineTexture::ReLoad("Platform_Tiger_Front_005.png");
		GameEngineTexture::ReLoad("Platform_Tiger_Front_006.png");
		GameEngineTexture::ReLoad("Platform_Tiger_Front_007.png");
		GameEngineTexture::ReLoad("Platform_Tiger_Front_008.png");
		GameEngineTexture::ReLoad("Platform_Tiger_Front_009.png");
		GameEngineTexture::ReLoad("Platform_Tiger_Front_010.png");
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

void FrogLevel::StartVoiceSound()
{
	int RandC = GameEngineRandom::MainRandom.RandomInt(0, 2);

	if (0 == RandC)
	{
		VoicePlayer = GameEngineSound::Play("announcer_Start_A.wav");
	}
	else if (1 == RandC)
	{
		VoicePlayer = GameEngineSound::Play("announcer_Start_A.wav");
	}
	else if (2 == RandC)
	{
		VoicePlayer = GameEngineSound::Play("announcer_Start_A.wav");
	}
}

void FrogLevel::KnockSound()
{
	VoicePlayer = GameEngineSound::Play("announcer_knockout_0004.wav");
}

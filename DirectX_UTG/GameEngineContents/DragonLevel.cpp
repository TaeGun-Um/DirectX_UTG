#include "PrecompileHeader.h"
#include "DragonLevel.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "LoadingLevel.h"

#include "Player.h"
#include "CardUI.h"
#include "HealthUI.h"
#include "WeaponUI.h"
#include "GrimMatchstick.h"
#include "Dragon_BackGround.h"
#include "Dragon_FrontGround.h"
#include "Dragon_CloudPlatform.h"
#include "Dragon_ColMap.h"
#include "Dragon_FallPoint.h"

#include "OverworldLevel.h"

#include "RoundBlackBox.h"
#include "Knockout.h"
#include "Ready_Wallop.h"
#include "You_Died.h"
#include "TransformGUI.h"

#include <GameEngineCore/BlurEffect.h>
#include "OldFilm.h"

DragonLevel* DragonLevel::DragonLevelPtr = nullptr;

DragonLevel::DragonLevel() 
{
}

DragonLevel::~DragonLevel() 
{
}

void DragonLevel::Start()
{
	DragonLevelPtr = this;
	GetLastTarget()->CreateEffect<BlurEffect>();
	GetLastTarget()->CreateEffect<OldFilm>();

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Sound");
		NewDir.Move("2_Grim_Matchstick");

		GameEngineSound::Load(NewDir.GetPlusFileName("Fiery Frolic.mp3").GetFullPath());

		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_peashot_in.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_peashot_fire_03.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_peashot_out.wav").GetFullPath());

		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_tail_appear.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_tail_attack.wav").GetFullPath());

		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_meteor_anticipation_loop.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_meteor_attack_01.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_meteor_attack_02.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_meteor_attack_03.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_meteor_attack_04.wav").GetFullPath());

		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_left_dragon_intro.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_left_dragon_tongue_intro.wav").GetFullPath());

		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_left_dragon_smoke_start.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_left_dragon_smoke_loop.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_left_dragon_smoke_end.wav").GetFullPath());

		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_left_dragon_fire_start.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_left_dragon_fire_loop.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_left_dragon_fire_end.wav").GetFullPath());

		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_fire_marcher_B_crouch_start_01.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_fire_marcher_B_crouch_start_02.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_fire_marcher_B_crouch_start_03.wav").GetFullPath());

		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_fire_marcher_B_jump_start_01.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_fire_marcher_B_jump_start_02.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_fire_marcher_B_jump_start_03.wav").GetFullPath());

		GameEngineSound::Load(NewDir.GetPlusFileName("dragon_dash.wav").GetFullPath());
	}
}
void DragonLevel::Update(float _DeltaTime)
{
	if (false == IsVoiceOn)
	{
		IsVoiceOn = true;
		StartVoiceSound();
	}

	BGMDelayTime += _DeltaTime;

	if (false == IsBGMOn && 0.6f <= BGMDelayTime)
	{
		IsBGMOn = true;
		BGMPlayer = GameEngineSound::Play("Fiery Frolic.mp3");
		BGMPlayer.SetLoop(100);
	}

	////////////////////////////////////////// Boss Clear //////////////////////////////////////////

	if (true == DragonObject->GetIsStageEnd() && 1 == EndSetCount)
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
			IsDragonLevelEnd = true;
			OverworldLevel::OverworldLevelPtr->SetDragonEnd();
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

	if (true == GameEngineInput::IsDown("PrevLevel"))
	{
		GameEngineCore::ChangeLevel("OverworldLevel");
	}

	if (false == Player::MainPlayer->GetIsIntro() && 1 == CloudMoveCount)
	{
		CloudMoveCount = 0;

		CloudPlatformObject0->SetIsMove();
		CloudPlatformObject1->SetIsMove();
		CloudPlatformObject2->SetIsMove();
		CloudPlatformObject3->SetIsMove();
		CloudPlatformObject4->SetIsMove();
		CloudPlatformObject5->SetIsMove();
		CloudPlatformObject6->SetIsMove();
		CloudPlatformObject7->SetIsMove();
		CloudPlatformObject8->SetIsMove();
	}

	if (true == GameEngineInput::IsDown("BossHpDown"))
	{
		DragonObject->GrimMatchstickPtr->BossHPDown();
	}
}

void DragonLevel::LevelChangeStart()
{
	if (nullptr == GameEngineTexture::Find("Dragon_ColMap.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("2_Grim_Matchstick");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Dragon_ColMap.png").GetFullPath());
	}

	// ColMap
	std::shared_ptr<GameEngineTexture> PlayMap = GameEngineTexture::Find("Dragon_ColMap.png");
	int PlayMapWidth = PlayMap->GetWidth();
	int PlayMapHeight = PlayMap->GetHeight();
	float PlayMapWidth_Half = static_cast<float>(PlayMapWidth / 2);
	float PlayMapHeight_Half = static_cast<float>(PlayMapHeight / 2);

	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 640, PlayMapHeight_Half + 10, -620.0f });
	GetMainCamera()->SetSortType(0, SortType::ZSort);

	// back
	{
		if (nullptr == BackGroundObject)
		{
			BackGroundObject = CreateActor<Dragon_BackGround>();
		}

		BackGroundObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half + 20, PlayMapHeight_Half, 100 });
	}
	{
		if (nullptr == FrontGroundObject)
		{
			FrontGroundObject = CreateActor<Dragon_FrontGround>();
		}

		FrontGroundObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half + 20, PlayMapHeight_Half, -100 });
	}

	{
		if (nullptr == CloudPlatformObject0)
		{
			CloudPlatformObject0 = CreateActor<Dragon_CloudPlatform>();
			CloudPlatformObject1 = CreateActor<Dragon_CloudPlatform>();
			CloudPlatformObject2 = CreateActor<Dragon_CloudPlatform>();
			CloudPlatformObject3 = CreateActor<Dragon_CloudPlatform>();
			CloudPlatformObject4 = CreateActor<Dragon_CloudPlatform>();
			CloudPlatformObject5 = CreateActor<Dragon_CloudPlatform>();
			CloudPlatformObject6 = CreateActor<Dragon_CloudPlatform>();
			CloudPlatformObject7 = CreateActor<Dragon_CloudPlatform>();
			CloudPlatformObject8 = CreateActor<Dragon_CloudPlatform>();
		}
		{
			float4 CloudPlatformObjectPosition0 = { PlayMapWidth_Half - 480, PlayMapHeight_Half - 120 , 10 };
			float4 CloudPlatformObjectPosition1 = { PlayMapWidth_Half - 450, PlayMapHeight_Half + 200 , 10 };
			float4 CloudPlatformObjectPosition2 = { PlayMapWidth_Half - 200, PlayMapHeight_Half + 20 , 10 };
			float4 CloudPlatformObjectPosition3 = { PlayMapWidth_Half - 160, PlayMapHeight_Half - 220 , 10 };
			float4 CloudPlatformObjectPosition4 = { PlayMapWidth_Half + 65, PlayMapHeight_Half + 160 , 10 };
			float4 CloudPlatformObjectPosition5 = { PlayMapWidth_Half + 170, PlayMapHeight_Half - 170 , 10 };
			float4 CloudPlatformObjectPosition6 = { PlayMapWidth_Half + 365, PlayMapHeight_Half - 5 , 10 };
			float4 CloudPlatformObjectPosition7 = { PlayMapWidth_Half + 550, PlayMapHeight_Half + 250 , 10 };
			float4 CloudPlatformObjectPosition8 = { PlayMapWidth_Half + 630, PlayMapHeight_Half - 250 , 10 };

			CloudPlatformObject0->GetTransform()->SetLocalPosition(CloudPlatformObjectPosition0);
			CloudPlatformObject1->GetTransform()->SetLocalPosition(CloudPlatformObjectPosition1);
			CloudPlatformObject2->GetTransform()->SetLocalPosition(CloudPlatformObjectPosition2);
			CloudPlatformObject3->GetTransform()->SetLocalPosition(CloudPlatformObjectPosition3);
			CloudPlatformObject4->GetTransform()->SetLocalPosition(CloudPlatformObjectPosition4);
			CloudPlatformObject5->GetTransform()->SetLocalPosition(CloudPlatformObjectPosition5);
			CloudPlatformObject6->GetTransform()->SetLocalPosition(CloudPlatformObjectPosition6);
			CloudPlatformObject7->GetTransform()->SetLocalPosition(CloudPlatformObjectPosition7);
			CloudPlatformObject8->GetTransform()->SetLocalPosition(CloudPlatformObjectPosition8);

			CloudPlatformObject0->SetActorInitPosition(CloudPlatformObjectPosition0);
			CloudPlatformObject1->SetActorInitPosition(CloudPlatformObjectPosition1);
			CloudPlatformObject2->SetActorInitPosition(CloudPlatformObjectPosition2);
			CloudPlatformObject3->SetActorInitPosition(CloudPlatformObjectPosition3);
			CloudPlatformObject4->SetActorInitPosition(CloudPlatformObjectPosition4);
			CloudPlatformObject5->SetActorInitPosition(CloudPlatformObjectPosition5);
			CloudPlatformObject6->SetActorInitPosition(CloudPlatformObjectPosition6);
			CloudPlatformObject7->SetActorInitPosition(CloudPlatformObjectPosition7);
			CloudPlatformObject8->SetActorInitPosition(CloudPlatformObjectPosition8);

			CloudPlatformObject0->SetStandingAnimation();
		}
	}

	{
		if (nullptr == FallPointObject)
		{
			FallPointObject = CreateActor<Dragon_FallPoint>();
			FallPointObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half + 330, PlayMapHeight_Half - 300 , -10 });
		}
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

		PlayerObject->SetIsDragonSetting();
	}

	// Boss
	{
		if (nullptr == DragonObject)
		{
			DragonObject = CreateActor<GrimMatchstick>();
		}

		DragonObject->GetTransform()->SetLocalPosition({ 1150 , 300, -1 });
	}

	{
		if (nullptr == ThisColMap)
		{
			ThisColMap = CreateActor<Dragon_ColMap>();
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
		GUI->SetDragonBoss(DragonObject);

		GUI->PlayerDebugRenderOn = std::bind(&DragonLevel::PlayerDebugRenderOn, this);
		GUI->PlayerDebugRenderOff = std::bind(&DragonLevel::PlayerDebugRenderOff, this);
		GUI->ColMapRenderOn = std::bind(&DragonLevel::LevelDebugOn, this);
		GUI->ColMapRenderOff = std::bind(&DragonLevel::LevelDebugOff, this);
	}

	ReLoadSetting();
}

void DragonLevel::LevelChangeEnd()
{
	BGMPlayer.Stop();

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

	if (nullptr != GameEngineSprite::Find("Dragon_Idle"))
	{
		GameEngineSprite::UnLoad("Dragon_Intro");
		GameEngineSprite::UnLoad("Dragon_Idle");

		GameEngineSprite::UnLoad("Dragon_MeteorAttack_Intro");
		GameEngineSprite::UnLoad("Dragon_MeteorAttack_Intro_Loop");
		GameEngineSprite::UnLoad("Dragon_MeteorAttack_Shoot_Front");
		GameEngineSprite::UnLoad("Dragon_MeteorAttack_Shoot_LollBack");
		GameEngineSprite::UnLoad("Dragon_MeteorAttack_Outro");

		GameEngineSprite::UnLoad("Dragon_PeashotAttack_Intro");
		GameEngineSprite::UnLoad("Dragon_PeashotAttack_Shoot");
		GameEngineSprite::UnLoad("Dragon_PeashotAttack_Outro");
	}
	if (nullptr != GameEngineSprite::Find("Dragon_Ph2_Idle"))
	{
		GameEngineSprite::UnLoad("Dragon_Ph2_Intro_Loop");
		GameEngineSprite::UnLoad("Dragon_Ph2_Intro");
		GameEngineSprite::UnLoad("Dragon_Ph2_Idle");
		GameEngineSprite::UnLoad("Dragon_Ph2_Death");
	}

	if (nullptr != GameEngineTexture::Find("Ph2_IdleUp_000.png"))
	{
		GameEngineTexture::UnLoad("Ph2_IdleUp_000.png");
		GameEngineTexture::UnLoad("Ph2_IdleUp_001.png");
		GameEngineTexture::UnLoad("Ph2_IdleUp_002.png");
		GameEngineTexture::UnLoad("Ph2_IdleUp_003.png");
		GameEngineTexture::UnLoad("Ph2_IdleUp_004.png");
		GameEngineTexture::UnLoad("Ph2_IdleUp_005.png");
		GameEngineTexture::UnLoad("Ph2_IdleUp_006.png");
		GameEngineTexture::UnLoad("Ph2_IdleUp_007.png");
		GameEngineTexture::UnLoad("Ph2_IdleUp_008.png");
		GameEngineTexture::UnLoad("Ph2_IdleUp_009.png");
		GameEngineTexture::UnLoad("Ph2_IdleUp_010.png");
		GameEngineTexture::UnLoad("Ph2_IdleUp_011.png");
		GameEngineTexture::UnLoad("Ph2_IdleUp_012.png");
		GameEngineTexture::UnLoad("Ph2_IdleUp_013.png");
	}
	if (nullptr != GameEngineTexture::Find("Ph2_DeathUp_000.png"))
	{
		GameEngineTexture::UnLoad("Ph2_DeathUp_000.png");
		GameEngineTexture::UnLoad("Ph2_DeathUp_001.png");
		GameEngineTexture::UnLoad("Ph2_DeathUp_002.png");
		GameEngineTexture::UnLoad("Ph2_DeathUp_003.png");
		GameEngineTexture::UnLoad("Ph2_DeathUp_004.png");
		GameEngineTexture::UnLoad("Ph2_DeathUp_005.png");
		GameEngineTexture::UnLoad("Ph2_DeathUp_006.png");
		GameEngineTexture::UnLoad("Ph2_DeathUp_007.png");
	}
	if (nullptr != GameEngineSprite::Find("Dragon_Ph2_Tounge_Intro"))
	{
		GameEngineSprite::UnLoad("Dragon_Ph2_Tounge_Intro");
		GameEngineSprite::UnLoad("Dragon_Ph2_Tounge_Intro_Loop");
		GameEngineSprite::UnLoad("Dragon_Ph2_Tounge_Outro");
		GameEngineSprite::UnLoad("Object_Fire_Intro");
		GameEngineSprite::UnLoad("Object_Fire_Loop");
		GameEngineSprite::UnLoad("Object_Fire_Outro");
		GameEngineSprite::UnLoad("Object_FireSmoke_Intro");
		GameEngineSprite::UnLoad("Object_FireSmoke_Loop");
		GameEngineSprite::UnLoad("Object_FireSmoke_Outro");
		GameEngineSprite::UnLoad("SFX_AttackSmoke_A");
		GameEngineSprite::UnLoad("SFX_AttackSmoke_B");
	}
	if (nullptr != GameEngineSprite::Find("Object_Firework_A_Move"))
	{
		GameEngineSprite::UnLoad("Object_Firework_Leader");
		GameEngineSprite::UnLoad("Object_Firework_A_Move");
		GameEngineSprite::UnLoad("Object_Firework_B_Move");
		GameEngineSprite::UnLoad("Object_Firework_C_Move");
		GameEngineSprite::UnLoad("Object_Firework_C_Jump_Intro");
		GameEngineSprite::UnLoad("Object_Firework_C_Jump_Inter");
		GameEngineSprite::UnLoad("Object_Firework_C_Jump_Loop");
	}
	if (nullptr != GameEngineSprite::Find("Object_GreenRing"))
	{
		GameEngineSprite::UnLoad("Object_GreenRing");
		GameEngineSprite::UnLoad("Object_PinkRing");
		GameEngineSprite::UnLoad("SFX_EyesAttack");

		GameEngineSprite::UnLoad("Object_Meteor");
		GameEngineSprite::UnLoad("SFX_MeteorSmoke");

		GameEngineSprite::UnLoad("Object_Tail");
	}
	if (nullptr != GameEngineSprite::Find("Explosion"))
	{
		GameEngineSprite::UnLoad("Explosion");
	}

	if (nullptr != GameEngineTexture::Find("Dragon_Foreground_Clouds_001.png"))
	{
		GameEngineTexture::UnLoad("Dragon_Foreground_Clouds_001.png");
		GameEngineTexture::UnLoad("Dragon_Foreground_Clouds_002.png");
	}
	if (nullptr != GameEngineTexture::Find("Dragon_ColMap.png"))
	{
		GameEngineTexture::UnLoad("Dragon_ColMap.png");
	}
	if (nullptr != GameEngineSprite::Find("Cloud_Platform_Idle"))
	{
		GameEngineSprite::UnLoad("Cloud_Platform_Idle");
		GameEngineSprite::UnLoad("Standing_Intro");
		GameEngineSprite::UnLoad("Standing_Outro");
		GameEngineSprite::UnLoad("Standing_Idle");
	}
	if (nullptr != GameEngineTexture::Find("Dragon_Background_Sky_Normal.png"))
	{
		GameEngineTexture::UnLoad("Dragon_Background_Sky_Normal.png");
	}
	if (nullptr != GameEngineTexture::Find("Dragon_Background_Clouds1.png"))
	{
		GameEngineTexture::UnLoad("Dragon_Background_Clouds1.png");
		GameEngineTexture::UnLoad("Dragon_Background_Clouds2.png");
		GameEngineTexture::UnLoad("Dragon_Background_Clouds3.png");
		GameEngineTexture::UnLoad("Dragon_Background_Clouds4.png");
		GameEngineTexture::UnLoad("Dragon_Background_Clouds5.png");
	}
	if (nullptr != GameEngineTexture::Find("Dragon_Foreground_Clouds_003.png"))
	{
		GameEngineTexture::UnLoad("Dragon_Foreground_Clouds_003.png");
	}
	if (nullptr != GameEngineSprite::Find("Tower_Light"))
	{
		GameEngineSprite::UnLoad("Tower_Light");
	}

	if (nullptr == GameEngineSprite::Find("Dragon_Ph2_Dash"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_Ph2_Dash").GetFullPath());
	}

	{
		BGMDelayTime = 0.0f;
		IsVoiceOn = false;
		IsBGMOn = false;
		ReadyWallopCount = 1;
		ReadyWallopTime = 0.0f;
		EndTime = 0.0f;
		IsBossEnd = false;
		IsDragonLevelEnd = false;
		IsPlayerEnd = false;
		EndSetCount = 1;
		EndSetCount2 = 1;

		CardObject->CartUIReset();
		PlayerObject->MoveAbleTimeReset();
		CloudMoveCount = 1;

		CloudPlatformObject0->SetIsMoveFalse();
		CloudPlatformObject1->SetIsMoveFalse();
		CloudPlatformObject2->SetIsMoveFalse();
		CloudPlatformObject3->SetIsMoveFalse();
		CloudPlatformObject4->SetIsMoveFalse();
		CloudPlatformObject5->SetIsMoveFalse();
		CloudPlatformObject6->SetIsMoveFalse();
		CloudPlatformObject7->SetIsMoveFalse();
		CloudPlatformObject8->SetIsMoveFalse();

		DragonObject->Death();
		FallPointObject->Death();

		DragonObject = nullptr;
		FallPointObject = nullptr;

		BackGroundObject->SetDashSoundFalse();
	}
}

void DragonLevel::ReLoadSetting()
{
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

	if (nullptr != GameEngineSprite::Find("Dragon_Idle"))
	{
		GameEngineSprite::ReLoad("Dragon_Intro");
		GameEngineSprite::ReLoad("Dragon_Idle");

		GameEngineSprite::ReLoad("Dragon_MeteorAttack_Intro");
		GameEngineSprite::ReLoad("Dragon_MeteorAttack_Intro_Loop");
		GameEngineSprite::ReLoad("Dragon_MeteorAttack_Shoot_Front");
		GameEngineSprite::ReLoad("Dragon_MeteorAttack_Shoot_LollBack");
		GameEngineSprite::ReLoad("Dragon_MeteorAttack_Outro");

		GameEngineSprite::ReLoad("Dragon_PeashotAttack_Intro");
		GameEngineSprite::ReLoad("Dragon_PeashotAttack_Shoot");
		GameEngineSprite::ReLoad("Dragon_PeashotAttack_Outro");
	}
	if (nullptr != GameEngineSprite::Find("Dragon_Ph2_Idle"))
	{
		GameEngineSprite::ReLoad("Dragon_Ph2_Intro_Loop");
		GameEngineSprite::ReLoad("Dragon_Ph2_Intro");
		GameEngineSprite::ReLoad("Dragon_Ph2_Idle");
		GameEngineSprite::ReLoad("Dragon_Ph2_Death");
	}

	if (nullptr != GameEngineTexture::Find("Ph2_IdleUp_000.png"))
	{
		GameEngineTexture::ReLoad("Ph2_IdleUp_000.png");
		GameEngineTexture::ReLoad("Ph2_IdleUp_001.png");
		GameEngineTexture::ReLoad("Ph2_IdleUp_002.png");
		GameEngineTexture::ReLoad("Ph2_IdleUp_003.png");
		GameEngineTexture::ReLoad("Ph2_IdleUp_004.png");
		GameEngineTexture::ReLoad("Ph2_IdleUp_005.png");
		GameEngineTexture::ReLoad("Ph2_IdleUp_006.png");
		GameEngineTexture::ReLoad("Ph2_IdleUp_007.png");
		GameEngineTexture::ReLoad("Ph2_IdleUp_008.png");
		GameEngineTexture::ReLoad("Ph2_IdleUp_009.png");
		GameEngineTexture::ReLoad("Ph2_IdleUp_010.png");
		GameEngineTexture::ReLoad("Ph2_IdleUp_011.png");
		GameEngineTexture::ReLoad("Ph2_IdleUp_012.png");
		GameEngineTexture::ReLoad("Ph2_IdleUp_013.png");
	}
	if (nullptr != GameEngineTexture::Find("Ph2_DeathUp_000.png"))
	{
		GameEngineTexture::ReLoad("Ph2_DeathUp_000.png");
		GameEngineTexture::ReLoad("Ph2_DeathUp_001.png");
		GameEngineTexture::ReLoad("Ph2_DeathUp_002.png");
		GameEngineTexture::ReLoad("Ph2_DeathUp_003.png");
		GameEngineTexture::ReLoad("Ph2_DeathUp_004.png");
		GameEngineTexture::ReLoad("Ph2_DeathUp_005.png");
		GameEngineTexture::ReLoad("Ph2_DeathUp_006.png");
		GameEngineTexture::ReLoad("Ph2_DeathUp_007.png");
	}
	if (nullptr != GameEngineSprite::Find("Dragon_Ph2_Tounge_Intro"))
	{
		GameEngineSprite::ReLoad("Dragon_Ph2_Tounge_Intro");
		GameEngineSprite::ReLoad("Dragon_Ph2_Tounge_Intro_Loop");
		GameEngineSprite::ReLoad("Dragon_Ph2_Tounge_Outro");
		GameEngineSprite::ReLoad("Object_Fire_Intro");
		GameEngineSprite::ReLoad("Object_Fire_Loop");
		GameEngineSprite::ReLoad("Object_Fire_Outro");
		GameEngineSprite::ReLoad("Object_FireSmoke_Intro");
		GameEngineSprite::ReLoad("Object_FireSmoke_Loop");
		GameEngineSprite::ReLoad("Object_FireSmoke_Outro");
		GameEngineSprite::ReLoad("SFX_AttackSmoke_A");
		GameEngineSprite::ReLoad("SFX_AttackSmoke_B");
	}
	if (nullptr != GameEngineSprite::Find("Object_Firework_A_Move"))
	{
		GameEngineSprite::ReLoad("Object_Firework_Leader");
		GameEngineSprite::ReLoad("Object_Firework_A_Move");
		GameEngineSprite::ReLoad("Object_Firework_B_Move");
		GameEngineSprite::ReLoad("Object_Firework_C_Move");
		GameEngineSprite::ReLoad("Object_Firework_C_Jump_Intro");
		GameEngineSprite::ReLoad("Object_Firework_C_Jump_Inter");
		GameEngineSprite::ReLoad("Object_Firework_C_Jump_Loop");
	}
	if (nullptr != GameEngineSprite::Find("Object_GreenRing"))
	{
		GameEngineSprite::ReLoad("Object_GreenRing");
		GameEngineSprite::ReLoad("Object_PinkRing");
		GameEngineSprite::ReLoad("SFX_EyesAttack");

		GameEngineSprite::ReLoad("Object_Meteor");
		GameEngineSprite::ReLoad("SFX_MeteorSmoke");

		GameEngineSprite::ReLoad("Object_Tail");
	}
	if (nullptr != GameEngineSprite::Find("Explosion"))
	{
		GameEngineSprite::ReLoad("Explosion");
	}

	if (nullptr != GameEngineTexture::Find("Dragon_Foreground_Clouds_001.png"))
	{
		GameEngineTexture::ReLoad("Dragon_Foreground_Clouds_001.png");
		GameEngineTexture::ReLoad("Dragon_Foreground_Clouds_002.png");
	}
	if (nullptr != GameEngineTexture::Find("Dragon_ColMap.png"))
	{
		GameEngineTexture::ReLoad("Dragon_ColMap.png");
	}
	if (nullptr != GameEngineSprite::Find("Cloud_Platform_Idle"))
	{
		GameEngineSprite::ReLoad("Cloud_Platform_Idle");
		GameEngineSprite::ReLoad("Standing_Intro");
		GameEngineSprite::ReLoad("Standing_Outro");
		GameEngineSprite::ReLoad("Standing_Idle");
	}
	if (nullptr != GameEngineTexture::Find("Dragon_Background_Sky_Normal.png"))
	{
		GameEngineTexture::ReLoad("Dragon_Background_Sky_Normal.png");
	}
	if (nullptr != GameEngineTexture::Find("Dragon_Background_Clouds1.png"))
	{
		GameEngineTexture::ReLoad("Dragon_Background_Clouds1.png");
		GameEngineTexture::ReLoad("Dragon_Background_Clouds2.png");
		GameEngineTexture::ReLoad("Dragon_Background_Clouds3.png");
		GameEngineTexture::ReLoad("Dragon_Background_Clouds4.png");
		GameEngineTexture::ReLoad("Dragon_Background_Clouds5.png");
	}
	if (nullptr != GameEngineTexture::Find("Dragon_Foreground_Clouds_003.png"))
	{
		GameEngineTexture::ReLoad("Dragon_Foreground_Clouds_003.png");
	}
	if (nullptr != GameEngineSprite::Find("Tower_Light"))
	{
		GameEngineSprite::ReLoad("Tower_Light");
	}
}

void DragonLevel::PlayerDebugRenderOn()
{
	if (nullptr != PlayerObject)
	{
		PlayerObject->PlayerDebugRenderOn();
	}
}
void DragonLevel::PlayerDebugRenderOff()
{
	if (nullptr != PlayerObject)
	{
		PlayerObject->PlayerDebugRenderOff();
	}
}
void DragonLevel::LevelDebugOn()
{
	if (nullptr != ThisColMap)
	{
		ThisColMap->ColMapDebugRenderOn();
	}
	if (nullptr != DragonObject)
	{
		DragonObject->DebugRenderOn();
	}
	if (nullptr != FallPointObject)
	{
		FallPointObject->DebugRenderOn();
	}
	if (nullptr != CloudPlatformObject0)
	{
		CloudPlatformObject0->DebugRenderOn();
		CloudPlatformObject1->DebugRenderOn();
		CloudPlatformObject2->DebugRenderOn();
		CloudPlatformObject3->DebugRenderOn();
		CloudPlatformObject4->DebugRenderOn();
		CloudPlatformObject5->DebugRenderOn();
		CloudPlatformObject6->DebugRenderOn();
		CloudPlatformObject7->DebugRenderOn();
		CloudPlatformObject8->DebugRenderOn();
	}
}
void DragonLevel::LevelDebugOff()
{
	if (nullptr != ThisColMap)
	{
		ThisColMap->ColMapDebugRenderOff();
	}
	if (nullptr != DragonObject)
	{
		DragonObject->DebugRenderOff();
	}
	if (nullptr != FallPointObject)
	{
		FallPointObject->DebugRenderOff();
	}
	if (nullptr != CloudPlatformObject0)
	{
		CloudPlatformObject0->DebugRenderOff();
		CloudPlatformObject1->DebugRenderOff();
		CloudPlatformObject2->DebugRenderOff();
		CloudPlatformObject3->DebugRenderOff();
		CloudPlatformObject4->DebugRenderOff();
		CloudPlatformObject5->DebugRenderOff();
		CloudPlatformObject6->DebugRenderOff();
		CloudPlatformObject7->DebugRenderOff();
		CloudPlatformObject8->DebugRenderOff();
	}
}

void DragonLevel::StartVoiceSound()
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

void DragonLevel::KnockSound()
{
	VoicePlayer = GameEngineSound::Play("announcer_knockout_0004.wav");
}

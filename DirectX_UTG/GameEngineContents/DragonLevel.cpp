#include "PrecompileHeader.h"
#include "DragonLevel.h"

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
#include "Dragon_ColMap.h"

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
}
void DragonLevel::Update(float _DeltaTime)
{
	////////////////////////////////////////// Boss Clear //////////////////////////////////////////

	//if (true == DragonObject->GetIsStageEnd() && 1 == EndSetCount)
	//{
	//	PlayerObject->SetStageEndHP();
	//	EndSetCount = 0;
	//	KnockoutPtr->StartMessage();
	//	IsBossEnd = true;
	//	GameEngineTime::GlobalTime.SetUpdateOrderTimeScale(0, 0.0f);
	//}

	//if (true == IsBossEnd)
	//{
	//	EndTime += _DeltaTime;

	//	if (true == KnockoutPtr->GetIsEnd())
	//	{
	//		GameEngineTime::GlobalTime.SetUpdateOrderTimeScale(0, 1.0f);

	//		if (EndTime >= 4.5f && 1 == EndSetCount2)
	//		{
	//			EndSetCount2 = 0;
	//			BlackBoxPtr->BoxSettingReset();
	//			BlackBoxPtr->SetEnter();
	//		}
	//	}

	//	if (true == BlackBoxPtr->GetIsEnd() && 0 == EndSetCount2)
	//	{
	//		IsDragonLevelEnd = true;
	//		OverworldLevel::OverworldLevelPtr->SetMouseEnd();
	//		LoadingLevel::LoadingLevelPtr->SetLevelState(LevelValue::OverworldLevel);
	//		GameEngineCore::ChangeLevel("LoadingLevel");
	//	}

	//	return;
	//}

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
			LoadingLevel::LoadingLevelPtr->SetLevelState(LevelValue::OverworldLevel);
			GameEngineCore::ChangeLevel("LoadingLevel");
		}

		return;
	}

	////////////////////////////////////////// Ready Wallop //////////////////////////////////////////

	//ReadyWallopTime += _DeltaTime;

	//if (1.5f <= ReadyWallopTime && 1 == ReadyWallopCount)
	//{
	//	ReadyWallopCount = 0;
	//	ReadyWallopPtr->StartMessage();
	//}

	//// readywallop�� ������ ������ ���� ����
	//if (true == ReadyWallopPtr->GetIsEnd())
	//{
	//	int a = 0;
	//}

	//if (true == GameEngineInput::IsDown("PrevLevel"))
	//{
	//	GameEngineCore::ChangeLevel("OverworldLevel");
	//}
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

	// ī�޶� ����
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 640, PlayMapHeight_Half + 10, -620.0f });
	GetMainCamera()->SetSortType(0, SortType::ZSort);

	// back
	//{
	//	if (nullptr == BackMapObject)
	//	{
	//		BackMapObject = CreateActor<Mouse_BackObject>();
	//	}

	//	BackMapObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half + 20, PlayMapHeight_Half, 9 });
	//}
	//{
	//	if (nullptr == MapObject)
	//	{
	//		MapObject = CreateActor<Mouse_Map>();
	//	}

	//	MapObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half + 20, PlayMapHeight_Half, 10 });
	//}
	// Boss
	{
		//if (nullptr == DragonObject)
		//{
		//	DragonObject = CreateActor<GrimMatchstick>();
		//}

		//DragonObject->GetTransform()->SetLocalPosition({ 1040 , 225, -1 });	
	}
	{
		if (nullptr == PlayerObject)
		{
			PlayerObject = CreateActor<Player>();
		}

		PlayerObject->GetTransform()->SetLocalPosition({ 220 , PlayMapHeight_Half, -3 });
		PlayerObject->SetColMap(PlayMap, PixelCollision::Coordinate::Custom);
		PlayerObject->SetCameraSpeedRatio(1.0f);
		PlayerObject->SetCorrectionFalse();
		PlayerObject->PlayerReset();
		PlayerObject->SetIntro();
	}
	//{
	//	if (nullptr == FrontMapObject)
	//	{
	//		FrontMapObject = CreateActor<Mouse_FrontObject>();
	//	}

	//	FrontMapObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, -4 });
	//}
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

	ReadyWallopCount = 1;
	ReadyWallopTime = 0.0f;
	CardObject->CartUIReset();
	PlayerObject->MoveAbleTimeReset();
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
}

void DragonLevel::PlayerDebugRenderOn()
{

}
void DragonLevel::PlayerDebugRenderOff()
{

}
void DragonLevel::LevelDebugOn()
{

}
void DragonLevel::LevelDebugOff()
{

}
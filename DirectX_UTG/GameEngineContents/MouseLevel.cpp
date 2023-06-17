#include "PrecompileHeader.h"
#include "MouseLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "Mouse_Map.h"
#include "Mouse_ColMap.h"
#include "Mouse_FrontObject.h"
#include "Mouse_BackObject.h"
#include "Player.h"
#include "WeaponUI.h"
#include "CardUI.h"
#include "HealthUI.h"
#include "Werner_Werman.h"

#include "OverworldLevel.h"

#include "Loading.h"
#include "RoundBlackBox.h"
#include "Knockout.h"
#include "Ready_Wallop.h"
#include "You_Died.h"
#include "TransformGUI.h"

MouseLevel* MouseLevel::MouseLevelPtr = nullptr;

MouseLevel::MouseLevel() 
{
}

MouseLevel::~MouseLevel() 
{
}

void MouseLevel::Start()
{
	MouseLevelPtr = this;
}
void MouseLevel::Update(float _DeltaTime)
{
	////////////////////////////////////////// Boss Clear //////////////////////////////////////////

	if (true == MouseObject->GetIsStageEnd() && 1 == EndSetCount)
	{
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

			if (EndTime >= 4.5f && 1 == EndSetCount2)
			{
				EndSetCount2 = 0;
				BlackBoxPtr->BoxSettingReset();
				BlackBoxPtr->SetEnter();
			}
		}

		if (true == BlackBoxPtr->GetIsEnd() && 0 == EndSetCount2)
		{
			IsMouseLevelEnd = true;
			OverworldLevel::OverworldLevelPtr->SetMouseEnd();
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

	//ReadyWallopTime += _DeltaTime;

	//if (1.5f <= ReadyWallopTime && 1 == ReadyWallopCount)
	//{
	//	ReadyWallopCount = 0;
	//	ReadyWallopPtr->StartMessage();
	//}

	//// readywallop이 끝나는 시점에 게임 시작
	//if (true == ReadyWallopPtr->GetIsEnd())
	//{
	//	int a = 0;
	//}

	//if (true == GameEngineInput::IsDown("PrevLevel"))
	//{
	//	GameEngineCore::ChangeLevel("OverworldLevel");
	//}
}

void MouseLevel::LevelChangeStart()
{
	if (nullptr == GameEngineTexture::Find("Mouse_ColMap.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("3_Werner_Werman");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_ColMap.png").GetFullPath());
	}

	// ColMap
	std::shared_ptr<GameEngineTexture> PlayMap = GameEngineTexture::Find("Mouse_ColMap.png");
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
			MapObject = CreateActor<Mouse_Map>();
		}

		MapObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half + 20, PlayMapHeight_Half, 10 });
	}
	// back
	{
		if (nullptr == BackMapObject)
		{
			BackMapObject = CreateActor<Mouse_BackObject>();
		}

		BackMapObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half + 20, PlayMapHeight_Half, 9 });
	}
	// Boss
	{
		if (nullptr == MouseObject)
		{
			MouseObject = CreateActor<Werner_Werman>();
		}

		MouseObject->GetTransform()->SetLocalPosition({ 1040 , 225, -1 });
		MouseObject->SetInitPosition(MouseObject->GetTransform()->GetWorldPosition());
		//MouseObject->SetInitReset();
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
	{
		if (nullptr == FrontMapObject)
		{
			FrontMapObject = CreateActor<Mouse_FrontObject>();
		}

		FrontMapObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, -4 });
	}
	{
		if (nullptr == ThisColMap)
		{
			ThisColMap = CreateActor<Mouse_ColMap>();
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
		GUI->SetMouseBoss(MouseObject);

		GUI->PlayerDebugRenderOn = std::bind(&MouseLevel::PlayerDebugRenderOn, this);
		GUI->PlayerDebugRenderOff = std::bind(&MouseLevel::PlayerDebugRenderOff, this);
		GUI->ColMapRenderOn = std::bind(&MouseLevel::LevelDebugOn, this);
		GUI->ColMapRenderOff = std::bind(&MouseLevel::LevelDebugOff, this);
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

void MouseLevel::LevelChangeEnd()
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

void MouseLevel::ReLoadSetting()
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

void MouseLevel::PlayerDebugRenderOn()
{
	if (nullptr != PlayerObject)
	{
		PlayerObject->PlayerDebugRenderOn();
	}
}
void MouseLevel::PlayerDebugRenderOff()
{
	if (nullptr != PlayerObject)
	{
		PlayerObject->PlayerDebugRenderOff();
	}
}
void MouseLevel::LevelDebugOn()
{
	if (nullptr != ThisColMap)
	{
		ThisColMap->ColMapDebugRenderOn();
	}
	if (nullptr != MouseObject)
	{
		MouseObject->DebugRenderOn();
	}
	if (nullptr != MapObject)
	{
		MapObject->DebugRenderOn();
	}
}
void MouseLevel::LevelDebugOff()
{
	if (nullptr != ThisColMap)
	{
		ThisColMap->ColMapDebugRenderOff();
	}
	if (nullptr != MouseObject)
	{
		MouseObject->DebugRenderOff();
	}
	if (nullptr != MapObject)
	{
		MapObject->DebugRenderOff();
	}
}
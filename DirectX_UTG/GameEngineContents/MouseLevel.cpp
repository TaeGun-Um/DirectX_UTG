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
#include "Katzenwagen.h"

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

		if (nullptr == CatObject)
		{
			CatObject = CreateActor<Katzenwagen>();
		}

		CatObject->GetTransform()->SetLocalPosition({ 640 , 470, 10 });
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

	if (nullptr != GameEngineSprite::Find("Mouse_Intro"))
	{
		GameEngineSprite::UnLoad("Mouse_Intro");
		GameEngineSprite::UnLoad("Mouse_Intro_Front");
		GameEngineSprite::UnLoad("Mouse_Intro_Smoke");
		GameEngineSprite::UnLoad("Mouse_PopOut");
		GameEngineSprite::UnLoad("Mouse_ShakeFist");
		GameEngineSprite::UnLoad("Mouse_Dash_Intro");
		GameEngineSprite::UnLoad("Mouse_Dash_Loop");
		GameEngineSprite::UnLoad("Mouse_Dash_Outro");
	}
	if (nullptr != GameEngineSprite::Find("Cannon_In"))
	{
		GameEngineSprite::UnLoad("Cannon_In");
		GameEngineSprite::UnLoad("Cannon_Out");
		GameEngineSprite::UnLoad("Cannon_Idle");
		GameEngineSprite::UnLoad("Cannon_Shoot");
	}
	if (nullptr != GameEngineSprite::Find("Catapult_Loop"))
	{
		GameEngineSprite::UnLoad("Catapult_Loop");
		GameEngineSprite::UnLoad("Catapult_Reload");
		GameEngineSprite::UnLoad("Catapult_Reload_Loop");
		GameEngineSprite::UnLoad("Catapult_Fire");
	}
	if (nullptr != GameEngineSprite::Find("Can_Part_Body_Idle"))
	{
		GameEngineSprite::UnLoad("Can_Part_Body_Idle");
		GameEngineSprite::UnLoad("Can_Part_Body_Move");
		GameEngineSprite::UnLoad("Can_Part_Body_In");
		GameEngineSprite::UnLoad("Can_Part_Body_Out");
		GameEngineSprite::UnLoad("Can_Part_Wheels");
	}
	if (nullptr != GameEngineSprite::Find("CherryBomb_Normal"))
	{
		GameEngineSprite::UnLoad("CherryBomb_Normal");
		GameEngineSprite::UnLoad("CherryBomb_Pink");
		GameEngineSprite::UnLoad("CherryBomb_Explode");
		GameEngineSprite::UnLoad("CherryBomb_Fire_Intro");
		GameEngineSprite::UnLoad("CherryBomb_Fire_Loop");
	}
	if (nullptr != GameEngineSprite::Find("CatapultProjectile_Bolt"))
	{
		GameEngineSprite::UnLoad("CatapultProjectile_Bolt");
		GameEngineSprite::UnLoad("CatapultProjectile_Coin");
		GameEngineSprite::UnLoad("CatapultProjectile_Gum");
		GameEngineSprite::UnLoad("CatapultProjectile_Nut");
		GameEngineSprite::UnLoad("CatapultProjectile_Popcap");
		GameEngineSprite::UnLoad("CatapultProjectile_Tooth");
	}
	if (nullptr != GameEngineSprite::Find("Spring_Intro"))
	{
		GameEngineSprite::UnLoad("Spring_Intro");
		GameEngineSprite::UnLoad("Spring_Land");
		GameEngineSprite::UnLoad("Spring_Idle_Loop");
		GameEngineSprite::UnLoad("Spring_Launch");
		GameEngineSprite::UnLoad("Spring_Death");
	}
	if (nullptr != GameEngineSprite::Find("Can_Explosion_Intro"))
	{
		GameEngineSprite::UnLoad("Can_Explosion_Intro");
		GameEngineSprite::UnLoad("Can_Explosion_Loop");
		GameEngineSprite::UnLoad("Can_Explosion_Outro");
		GameEngineSprite::UnLoad("Can_Explosion_SFX");
		GameEngineSprite::UnLoad("Object_IntroBomb");
	}
	if (nullptr != GameEngineSprite::Find("Can_Explosion_SFX"))
	{
		GameEngineSprite::UnLoad("Can_Explosion_SFX");
	}
	if (nullptr != GameEngineSprite::Find("Plat_Loop"))
	{
		GameEngineSprite::UnLoad("Plat_Loop");
		GameEngineSprite::UnLoad("Plat_MoveLeft");
		GameEngineSprite::UnLoad("Plat_MoveLeft_Loop");
		GameEngineSprite::UnLoad("Plat_MoveRight");
		GameEngineSprite::UnLoad("Plat_MoveRight_Loop");
	}
	if (nullptr != GameEngineSprite::Find("Mouse_TransitionA"))
	{
		GameEngineSprite::UnLoad("Mouse_TransitionA");
		GameEngineSprite::UnLoad("Mouse_TransitionA_Loop");
		GameEngineSprite::UnLoad("Mouse_TransitionB");
		GameEngineSprite::UnLoad("Mouse_TransitionB_Loop");
		GameEngineSprite::UnLoad("Mouse_TransitionC");
		GameEngineSprite::UnLoad("Mouse_TransitionC_Loop");
		GameEngineSprite::UnLoad("Mouse_TransitionD");
		GameEngineSprite::UnLoad("Mouse_TransitionD_Loop");
		GameEngineSprite::UnLoad("Mouse_Transition_EndLoop");
	}
	if (nullptr != GameEngineSprite::Find("Can_Tin_Up"))
	{
		GameEngineSprite::UnLoad("Can_Tin_Up");
	}
	if (nullptr != GameEngineSprite::Find("Object_Flamecannon"))
	{
		GameEngineSprite::UnLoad("Object_Flamecannon");
	}
	if (nullptr != GameEngineSprite::Find("Scissor_Intro"))
	{
		GameEngineSprite::UnLoad("Scissor_Intro");
		GameEngineSprite::UnLoad("Scissor_Down");
		GameEngineSprite::UnLoad("Scissor_Down_Loop");
		GameEngineSprite::UnLoad("Scissor_Up");
		GameEngineSprite::UnLoad("Scissor_Up_Loop");
	}
	if (nullptr != GameEngineSprite::Find("Flamethrower_Intro_Loop"))
	{
		GameEngineSprite::UnLoad("Flamethrower_Intro_Loop");
		GameEngineSprite::UnLoad("Flamethrower_Fire_Outro");
		GameEngineSprite::UnLoad("Flamethrower_Fire_Loop");
		GameEngineSprite::UnLoad("Flamethrower_Fire");
	}
	if (nullptr != GameEngineSprite::Find("Stick_A"))
	{
		GameEngineSprite::UnLoad("Stick_A");
		GameEngineSprite::UnLoad("Stick_B");
		GameEngineSprite::UnLoad("Stick_C");
	}
	if (nullptr != GameEngineSprite::Find("Bottlecap_A"))
	{
		GameEngineSprite::UnLoad("Bottlecap_A");
		GameEngineSprite::UnLoad("Bottlecap_B");
		GameEngineSprite::UnLoad("Bottlecap_C");
		GameEngineSprite::UnLoad("Bottlecap_D");
		GameEngineSprite::UnLoad("Bottlecap_E");
		GameEngineSprite::UnLoad("Bottlecap_F");
	}
	if (nullptr != GameEngineTexture::Find("Can_Idle_Up_001.png"))
	{
		GameEngineTexture::UnLoad("Can_Idle_Up_001.png");
		GameEngineTexture::UnLoad("Can_Idle_Up_002.png");
		GameEngineTexture::UnLoad("Can_Idle_Up_003.png");
	}
	if (nullptr != GameEngineTexture::Find("Can_Idle_Back_001.png"))
	{
		GameEngineTexture::UnLoad("Can_Idle_Back_001.png");
		GameEngineTexture::UnLoad("Can_Idle_Back_002.png");
		GameEngineTexture::UnLoad("Can_Idle_Back_003.png");
	}
	if (nullptr != GameEngineTexture::Find("Can_Part_Back_InOut_001.png"))
	{
		GameEngineTexture::UnLoad("Can_Part_Back_InOut_001.png");
		GameEngineTexture::UnLoad("Can_Part_Back_InOut_002.png");
		GameEngineTexture::UnLoad("Can_Part_Back_InOut_003.png");
	}
	if (nullptr != GameEngineTexture::Find("Can_Move_Back_001.png"))
	{
		GameEngineTexture::UnLoad("Can_Move_Back_001.png");
		GameEngineTexture::UnLoad("Can_Move_Back_002.png");
		GameEngineTexture::UnLoad("Can_Move_Back_003.png");
		GameEngineTexture::UnLoad("Can_Move_Back_004.png");
		GameEngineTexture::UnLoad("Can_Move_Back_005.png");
		GameEngineTexture::UnLoad("Can_Move_Back_006.png");
		GameEngineTexture::UnLoad("Can_Move_Back_007.png");
		GameEngineTexture::UnLoad("Can_Move_Back_008.png");
		GameEngineTexture::UnLoad("Can_Move_Back_009.png");
		GameEngineTexture::UnLoad("Can_Move_Back_010.png");
		GameEngineTexture::UnLoad("Can_Move_Back_011.png");
		GameEngineTexture::UnLoad("Can_Move_Back_012.png");
		GameEngineTexture::UnLoad("Can_Move_Back_013.png");
		GameEngineTexture::UnLoad("Can_Move_Back_014.png");
		GameEngineTexture::UnLoad("Can_Move_Back_015.png");
		GameEngineTexture::UnLoad("Can_Move_Back_016.png");
		GameEngineTexture::UnLoad("Can_Move_Back_017.png");
		GameEngineTexture::UnLoad("Can_Move_Back_018.png");
		GameEngineTexture::UnLoad("Can_Move_Back_019.png");
		GameEngineTexture::UnLoad("Can_Move_Back_020.png");
		GameEngineTexture::UnLoad("Can_Move_Back_021.png");
		GameEngineTexture::UnLoad("Can_Move_Back_022.png");
		GameEngineTexture::UnLoad("Can_Move_Back_023.png");
		GameEngineTexture::UnLoad("Can_Move_Back_024.png");
	}
	if (nullptr != GameEngineTexture::Find("Mouse_Intro_Top_007.png"))
	{
		GameEngineTexture::UnLoad("Mouse_Intro_Top_007.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_008.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_009.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_010.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_011.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_012.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_013.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_014.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_015.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_016.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_017.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_018.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_019.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_020.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_021.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_022.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_023.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_024.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_025.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_026.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_027.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_028.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_029.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_030.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_031.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_032.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_046.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_047.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_048.png");
		GameEngineTexture::UnLoad("Mouse_Intro_Top_049.png");
	}
	if (nullptr != GameEngineTexture::Find("Tin_Boil_Back_001.png"))
	{
		GameEngineTexture::UnLoad("Tin_Boil_Back_001.png");
		GameEngineTexture::UnLoad("Tin_Boil_Back_002.png");
		GameEngineTexture::UnLoad("Tin_Boil_Back_003.png");
	}

	if (nullptr != GameEngineSprite::Find("Cat_Intro_Body"))
	{
		GameEngineSprite::UnLoad("Cat_Intro_Body");
		GameEngineSprite::UnLoad("Cat_Idle_Body");
		GameEngineSprite::UnLoad("Cat_Death_Body");
		GameEngineSprite::UnLoad("Cat_Intro_Head");
		GameEngineSprite::UnLoad("Cat_Idle_Head");
		GameEngineSprite::UnLoad("Cat_Claw_Head_Intro");
		GameEngineSprite::UnLoad("Cat_Claw_Head_Loop");
		GameEngineSprite::UnLoad("Cat_Claw_Head_Outro");
		GameEngineSprite::UnLoad("Cat_Death_HeadObject");
		GameEngineSprite::UnLoad("Cat_Death_HeadObject_Loop");
		GameEngineSprite::UnLoad("Cat_Idle_LeftHand");
		GameEngineSprite::UnLoad("Cat_Idle_RightHand");
		GameEngineSprite::UnLoad("Cat_Claw_Hand_Intro");
		GameEngineSprite::UnLoad("Cat_Claw_Hand_Loop");
		GameEngineSprite::UnLoad("Cat_Claw_Hand_Outro");
		GameEngineSprite::UnLoad("Cat_Claw_Hand_Hit");
		GameEngineSprite::UnLoad("Cat_Death_SFX");
	}
	if (nullptr != GameEngineSprite::Find("Object_WoodPiece_Loop"))
	{
		GameEngineSprite::UnLoad("Object_WoodPiece_Loop");
		GameEngineSprite::UnLoad("Object_WoodPiece_Death");
	}
	if (nullptr != GameEngineSprite::Find("Explosion"))
	{
		GameEngineSprite::UnLoad("Explosion");
	}
	if (nullptr != GameEngineTexture::Find("UpTexture.png"))
	{
		GameEngineTexture::UnLoad("UpTexture.png");
	}

	{
		ReadyWallopCount = 1;
		ReadyWallopTime = 0.0f;
		EndTime = 0.0f;
		IsBossEnd = false;
		IsMouseLevelEnd = false;
		IsPlayerEnd = false;
		EndSetCount = 1;
		EndSetCount2 = 1;

		CardObject->CartUIReset();
		PlayerObject->MoveAbleTimeReset();

		MouseObject->Death();
		CatObject->Death();
		MapObject->Death();
		BackMapObject->Death();

		MouseObject = nullptr;
		CatObject = nullptr;
		MapObject = nullptr;
		BackMapObject = nullptr;
	}
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

	if (nullptr != GameEngineSprite::Find("Mouse_Intro"))
	{
		GameEngineSprite::ReLoad("Mouse_Intro");
		GameEngineSprite::ReLoad("Mouse_Intro_Front");
		GameEngineSprite::ReLoad("Mouse_Intro_Smoke");
		GameEngineSprite::ReLoad("Mouse_PopOut");
		GameEngineSprite::ReLoad("Mouse_ShakeFist");
		GameEngineSprite::ReLoad("Mouse_Dash_Intro");
		GameEngineSprite::ReLoad("Mouse_Dash_Loop");
		GameEngineSprite::ReLoad("Mouse_Dash_Outro");
	}
	if (nullptr != GameEngineSprite::Find("Cannon_In"))
	{
		GameEngineSprite::ReLoad("Cannon_In");
		GameEngineSprite::ReLoad("Cannon_Out");
		GameEngineSprite::ReLoad("Cannon_Idle");
		GameEngineSprite::ReLoad("Cannon_Shoot");
	}
	if (nullptr != GameEngineSprite::Find("Catapult_Loop"))
	{
		GameEngineSprite::ReLoad("Catapult_Loop");
		GameEngineSprite::ReLoad("Catapult_Reload");
		GameEngineSprite::ReLoad("Catapult_Reload_Loop");
		GameEngineSprite::ReLoad("Catapult_Fire");
	}
	if (nullptr != GameEngineSprite::Find("Can_Part_Body_Idle"))
	{
		GameEngineSprite::ReLoad("Can_Part_Body_Idle");
		GameEngineSprite::ReLoad("Can_Part_Body_Move");
		GameEngineSprite::ReLoad("Can_Part_Body_In");
		GameEngineSprite::ReLoad("Can_Part_Body_Out");
		GameEngineSprite::ReLoad("Can_Part_Wheels");
	}
	if (nullptr != GameEngineSprite::Find("CherryBomb_Normal"))
	{
		GameEngineSprite::ReLoad("CherryBomb_Normal");
		GameEngineSprite::ReLoad("CherryBomb_Pink");
		GameEngineSprite::ReLoad("CherryBomb_Explode");
		GameEngineSprite::ReLoad("CherryBomb_Fire_Intro");
		GameEngineSprite::ReLoad("CherryBomb_Fire_Loop");
	}
	if (nullptr != GameEngineSprite::Find("CatapultProjectile_Bolt"))
	{
		GameEngineSprite::ReLoad("CatapultProjectile_Bolt");
		GameEngineSprite::ReLoad("CatapultProjectile_Coin");
		GameEngineSprite::ReLoad("CatapultProjectile_Gum");
		GameEngineSprite::ReLoad("CatapultProjectile_Nut");
		GameEngineSprite::ReLoad("CatapultProjectile_Popcap");
		GameEngineSprite::ReLoad("CatapultProjectile_Tooth");
	}
	if (nullptr != GameEngineSprite::Find("Spring_Intro"))
	{
		GameEngineSprite::ReLoad("Spring_Intro");
		GameEngineSprite::ReLoad("Spring_Land");
		GameEngineSprite::ReLoad("Spring_Idle_Loop");
		GameEngineSprite::ReLoad("Spring_Launch");
		GameEngineSprite::ReLoad("Spring_Death");
	}
	if (nullptr != GameEngineSprite::Find("Can_Explosion_Intro"))
	{
		GameEngineSprite::ReLoad("Can_Explosion_Intro");
		GameEngineSprite::ReLoad("Can_Explosion_Loop");
		GameEngineSprite::ReLoad("Can_Explosion_Outro");
		GameEngineSprite::ReLoad("Can_Explosion_SFX");
		GameEngineSprite::ReLoad("Object_IntroBomb");
	}
	if (nullptr != GameEngineSprite::Find("Can_Explosion_SFX"))
	{
		GameEngineSprite::ReLoad("Can_Explosion_SFX");
	}
	if (nullptr != GameEngineSprite::Find("Plat_Loop"))
	{
		GameEngineSprite::ReLoad("Plat_Loop");
		GameEngineSprite::ReLoad("Plat_MoveLeft");
		GameEngineSprite::ReLoad("Plat_MoveLeft_Loop");
		GameEngineSprite::ReLoad("Plat_MoveRight");
		GameEngineSprite::ReLoad("Plat_MoveRight_Loop");
	}
	if (nullptr != GameEngineSprite::Find("Mouse_TransitionA"))
	{
		GameEngineSprite::ReLoad("Mouse_TransitionA");
		GameEngineSprite::ReLoad("Mouse_TransitionA_Loop");
		GameEngineSprite::ReLoad("Mouse_TransitionB");
		GameEngineSprite::ReLoad("Mouse_TransitionB_Loop");
		GameEngineSprite::ReLoad("Mouse_TransitionC");
		GameEngineSprite::ReLoad("Mouse_TransitionC_Loop");
		GameEngineSprite::ReLoad("Mouse_TransitionD");
		GameEngineSprite::ReLoad("Mouse_TransitionD_Loop");
		GameEngineSprite::ReLoad("Mouse_Transition_EndLoop");
	}
	if (nullptr != GameEngineSprite::Find("Can_Tin_Up"))
	{
		GameEngineSprite::ReLoad("Can_Tin_Up");
	}
	if (nullptr != GameEngineSprite::Find("Object_Flamecannon"))
	{
		GameEngineSprite::ReLoad("Object_Flamecannon");
	}
	if (nullptr != GameEngineSprite::Find("Scissor_Intro"))
	{
		GameEngineSprite::ReLoad("Scissor_Intro");
		GameEngineSprite::ReLoad("Scissor_Down");
		GameEngineSprite::ReLoad("Scissor_Down_Loop");
		GameEngineSprite::ReLoad("Scissor_Up");
		GameEngineSprite::ReLoad("Scissor_Up_Loop");
	}
	if (nullptr != GameEngineSprite::Find("Flamethrower_Intro_Loop"))
	{
		GameEngineSprite::ReLoad("Flamethrower_Intro_Loop");
		GameEngineSprite::ReLoad("Flamethrower_Fire_Outro");
		GameEngineSprite::ReLoad("Flamethrower_Fire_Loop");
		GameEngineSprite::ReLoad("Flamethrower_Fire");
	}
	if (nullptr != GameEngineSprite::Find("Stick_A"))
	{
		GameEngineSprite::ReLoad("Stick_A");
		GameEngineSprite::ReLoad("Stick_B");
		GameEngineSprite::ReLoad("Stick_C");
	}
	if (nullptr != GameEngineSprite::Find("Bottlecap_A"))
	{
		GameEngineSprite::ReLoad("Bottlecap_A");
		GameEngineSprite::ReLoad("Bottlecap_B");
		GameEngineSprite::ReLoad("Bottlecap_C");
		GameEngineSprite::ReLoad("Bottlecap_D");
		GameEngineSprite::ReLoad("Bottlecap_E");
		GameEngineSprite::ReLoad("Bottlecap_F");
	}
	if (nullptr != GameEngineTexture::Find("Can_Idle_Up_001.png"))
	{
		GameEngineTexture::ReLoad("Can_Idle_Up_001.png");
		GameEngineTexture::ReLoad("Can_Idle_Up_002.png");
		GameEngineTexture::ReLoad("Can_Idle_Up_003.png");
	}
	if (nullptr != GameEngineTexture::Find("Can_Idle_Back_001.png"))
	{
		GameEngineTexture::ReLoad("Can_Idle_Back_001.png");
		GameEngineTexture::ReLoad("Can_Idle_Back_002.png");
		GameEngineTexture::ReLoad("Can_Idle_Back_003.png");
	}
	if (nullptr != GameEngineTexture::Find("Can_Part_Back_InOut_001.png"))
	{
		GameEngineTexture::ReLoad("Can_Part_Back_InOut_001.png");
		GameEngineTexture::ReLoad("Can_Part_Back_InOut_002.png");
		GameEngineTexture::ReLoad("Can_Part_Back_InOut_003.png");
	}
	if (nullptr != GameEngineTexture::Find("Can_Move_Back_001.png"))
	{
		GameEngineTexture::ReLoad("Can_Move_Back_001.png");
		GameEngineTexture::ReLoad("Can_Move_Back_002.png");
		GameEngineTexture::ReLoad("Can_Move_Back_003.png");
		GameEngineTexture::ReLoad("Can_Move_Back_004.png");
		GameEngineTexture::ReLoad("Can_Move_Back_005.png");
		GameEngineTexture::ReLoad("Can_Move_Back_006.png");
		GameEngineTexture::ReLoad("Can_Move_Back_007.png");
		GameEngineTexture::ReLoad("Can_Move_Back_008.png");
		GameEngineTexture::ReLoad("Can_Move_Back_009.png");
		GameEngineTexture::ReLoad("Can_Move_Back_010.png");
		GameEngineTexture::ReLoad("Can_Move_Back_011.png");
		GameEngineTexture::ReLoad("Can_Move_Back_012.png");
		GameEngineTexture::ReLoad("Can_Move_Back_013.png");
		GameEngineTexture::ReLoad("Can_Move_Back_014.png");
		GameEngineTexture::ReLoad("Can_Move_Back_015.png");
		GameEngineTexture::ReLoad("Can_Move_Back_016.png");
		GameEngineTexture::ReLoad("Can_Move_Back_017.png");
		GameEngineTexture::ReLoad("Can_Move_Back_018.png");
		GameEngineTexture::ReLoad("Can_Move_Back_019.png");
		GameEngineTexture::ReLoad("Can_Move_Back_020.png");
		GameEngineTexture::ReLoad("Can_Move_Back_021.png");
		GameEngineTexture::ReLoad("Can_Move_Back_022.png");
		GameEngineTexture::ReLoad("Can_Move_Back_023.png");
		GameEngineTexture::ReLoad("Can_Move_Back_024.png");
	}
	if (nullptr != GameEngineTexture::Find("Mouse_Intro_Top_007.png"))
	{
		GameEngineTexture::ReLoad("Mouse_Intro_Top_007.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_008.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_009.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_010.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_011.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_012.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_013.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_014.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_015.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_016.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_017.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_018.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_019.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_020.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_021.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_022.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_023.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_024.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_025.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_026.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_027.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_028.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_029.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_030.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_031.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_032.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_046.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_047.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_048.png");
		GameEngineTexture::ReLoad("Mouse_Intro_Top_049.png");
	}
	if (nullptr != GameEngineTexture::Find("Tin_Boil_Back_001.png"))
	{
		GameEngineTexture::ReLoad("Tin_Boil_Back_001.png");
		GameEngineTexture::ReLoad("Tin_Boil_Back_002.png");
		GameEngineTexture::ReLoad("Tin_Boil_Back_003.png");
	}

	if (nullptr != GameEngineSprite::Find("Cat_Intro_Body"))
	{
		GameEngineSprite::ReLoad("Cat_Intro_Body");
		GameEngineSprite::ReLoad("Cat_Idle_Body");
		GameEngineSprite::ReLoad("Cat_Death_Body");
		GameEngineSprite::ReLoad("Cat_Intro_Head");
		GameEngineSprite::ReLoad("Cat_Idle_Head");
		GameEngineSprite::ReLoad("Cat_Claw_Head_Intro");
		GameEngineSprite::ReLoad("Cat_Claw_Head_Loop");
		GameEngineSprite::ReLoad("Cat_Claw_Head_Outro");
		GameEngineSprite::ReLoad("Cat_Death_HeadObject");
		GameEngineSprite::ReLoad("Cat_Death_HeadObject_Loop");
		GameEngineSprite::ReLoad("Cat_Idle_LeftHand");
		GameEngineSprite::ReLoad("Cat_Idle_RightHand");
		GameEngineSprite::ReLoad("Cat_Claw_Hand_Intro");
		GameEngineSprite::ReLoad("Cat_Claw_Hand_Loop");
		GameEngineSprite::ReLoad("Cat_Claw_Hand_Outro");
		GameEngineSprite::ReLoad("Cat_Claw_Hand_Hit");
		GameEngineSprite::ReLoad("Cat_Death_SFX");
	}
	if (nullptr != GameEngineSprite::Find("Object_WoodPiece_Loop"))
	{
		GameEngineSprite::ReLoad("Object_WoodPiece_Loop");
		GameEngineSprite::ReLoad("Object_WoodPiece_Death");
	}
	if (nullptr != GameEngineSprite::Find("Explosion"))
	{
		GameEngineSprite::ReLoad("Explosion");
	}
	if (nullptr != GameEngineTexture::Find("UpTexture.png"))
	{
		GameEngineTexture::ReLoad("UpTexture.png");
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
	if (nullptr != CatObject)
	{
		CatObject->DebugRenderOn();
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
	if (nullptr != CatObject)
	{
		CatObject->DebugRenderOff();
	}
	if (nullptr != MapObject)
	{
		MapObject->DebugRenderOff();
	}
}
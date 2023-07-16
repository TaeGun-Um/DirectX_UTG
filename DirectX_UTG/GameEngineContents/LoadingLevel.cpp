#include "PrecompileHeader.h"
#include "LoadingLevel.h"

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCamera.h>

#include <GameEngineCore/BlurEffect.h>
#include "OldFilm.h"

#include "OverworldLevel.h"
#include "Loading.h"

LoadingLevel* LoadingLevel::LoadingLevelPtr = nullptr;
std::atomic_bool IsTextureLoadEnd = false;

LoadingLevel::LoadingLevel() 
{
}

LoadingLevel::~LoadingLevel() 
{
}

void LoadingLevel::Start()
{
	LoadingLevelPtr = this;
	GetLastTarget()->CreateEffect<BlurEffect>();
	GetLastTarget()->CreateEffect<OldFilm>();
}

void LoadingLevel::Update(float _DeltaTime)
{
	EndTime += _DeltaTime;

	if (EndTime >= 1.0f && true == IsTextureLoadEnd)
	{
		LoadingObject->SetOutro();
	}

	if (true == LoadingObject->GetIsEnd())
	{
		LevelChange();
	}
}

void LoadingLevel::LevelChangeStart()
{
	IsTextureLoadEnd = false;

	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });

	if (true == OverworldLevel::OverworldLevelPtr->GetIsGameEnd())
	{
		LevelState = LevelValue::EndingLevel;
	}

	TextureLoadLevelSelect();

	// CreateActor
	if (nullptr == LoadingObject)
	{
		LoadingObject = CreateActor<Loading>();
		LoadingObject->GetTransform()->SetLocalPosition({ 0 , 0, -10.0f });
		LoadingObject->SetStart();
	}
}

void LoadingLevel::LevelChangeEnd()
{
	EndTime = 0.0f;
	IsTextureLoadEnd = false;
	LoadingObject->Death();
	LoadingObject = nullptr;
}

void LoadingLevel::LevelChange()
{
	switch (LevelState)
	{
	case LevelValue::First_OpeningLevel:
		GameEngineCore::ChangeLevel("First_OpeningLevel");
		break;
	case LevelValue::Second_OpeningLevel:
		GameEngineCore::ChangeLevel("Second_OpeningLevel");
		break;
	case LevelValue::WaitingRoomLevel:
		GameEngineCore::ChangeLevel("WaitingRoomLevel");
		break;
	case LevelValue::TutorialLevel:
		GameEngineCore::ChangeLevel("TutorialLevel");
		break;
	case LevelValue::OverworldLevel:
		GameEngineCore::ChangeLevel("OverworldLevel");
		break;
	case LevelValue::FrogLevel:
		GameEngineCore::ChangeLevel("FrogLevel");
		break;
	case LevelValue::DragonLevel:
		GameEngineCore::ChangeLevel("DragonLevel");
		break;
	case LevelValue::MouseLevel:
		GameEngineCore::ChangeLevel("MouseLevel");
		break;
	case LevelValue::EndingLevel:
		GameEngineCore::ChangeLevel("EndingLevel");
		break;
	default:
		break;
	}
}

void First_OpeningTexture(GameEngineThread* Thread)
{
	if (nullptr == GameEngineTexture::Find("cuphead_startscreen.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("MainMenu");

		GameEngineTexture::Load(NewDir.GetPlusFileName("cuphead_startscreen.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("START.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("EXIT.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Cuphead_and_Mugman"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Opening1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cuphead_and_Mugman").GetFullPath());

		if (nullptr == GameEngineTexture::Find("PressAnyButton.png"))
		{
			NewDir.Move("Title");

			GameEngineTexture::Load(NewDir.GetPlusFileName("Title_Background.png").GetFullPath());
			GameEngineTexture::Load(NewDir.GetPlusFileName("PressAnyButton.png").GetFullPath());
		}
	}

	if (nullptr == GameEngineSprite::Find("MDHR_Logo.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Opening1");
		NewDir.Move("MDHR_Logo");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("MDHR_Logo.png").GetFullPath(), 5, 20);
	}

	IsTextureLoadEnd = true;
} 

void Second_OpeningTexture(GameEngineThread* Thread)
{
	if (nullptr == GameEngineSprite::Find("Page_01"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Opening2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_01").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_01-02").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_02-03").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_03-04").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_04-05").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_05-06").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_06-07").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_07-08").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_08-09").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_09-10").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_10-11").GetFullPath());
	}

	IsTextureLoadEnd = true;
}

void WaitingTexture(GameEngineThread* Thread)
{
	if (nullptr == GameEngineTexture::Find("WaitingRoom_Background.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("WaitingRoom");

		GameEngineTexture::Load(NewDir.GetPlusFileName("WaitingRoom_ColMap.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Kettle_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("ElderKettle");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Kettle_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottle_Pop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottle_Pop_Boil").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottle_Pop_Trans_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Talk_A").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Talk_AToB").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Talk_BToA").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Talk_B").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("WaitingRoom_Background.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("WaitingRoom");

		GameEngineTexture::Load(NewDir.GetPlusFileName("WaitingRoom_Background.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("WaitingRoom_Chair.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("WaitingRoom_Couch.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("WaitingRoom_Vignette.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Note_One"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("WaitingRoom");
		NewDir.Move("Note");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Note_One").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Note_Two").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Bottle_Appear.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("ElderKettle");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Bottle_Appear.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Bottle_Hold.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Bottle_FX.png").GetFullPath(), 5, 3);
	}

	if (nullptr == GameEngineSprite::Find("Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Action");

		// Idle
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Idle").GetFullPath());

		// Move
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Move").GetFullPath());

		// Jump & Parry(Slap)
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Jump").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Parry").GetFullPath());

		// Dash
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirDash").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dash").GetFullPath());

		// Duck
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DuckReady").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Duck").GetFullPath());

		// Hit & Death
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirHit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ghost").GetFullPath());

		// Hold
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_Up").GetFullPath());

		// Attack(Move, Duck, Hold(==Idle))
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Move_Attak_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Move_Attak_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DuckAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_Up").GetFullPath());

		// EX
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_Up").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_Up").GetFullPath());

		// Interaction & Intro
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ElderKettleInteraction").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Intro_Flex").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Intro_Regular").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Portal").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Parry_Pink_0.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Action");
		NewDir.Move("Parry_Pink");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_0.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_1.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_2.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_3.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_4.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_5.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_6.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_7.png").GetFullPath(), 1, 1);
	}

	if (nullptr == GameEngineTexture::Find("Peashooter_Spawn.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("Attack");
		NewDir.Move("Peashooter");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_Spawn.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_Loop.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_Death.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_EX_Loop.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_EX_Death.png").GetFullPath(), 5, 2);
	}

	if (nullptr == GameEngineTexture::Find("Spread_Spawn.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("Attack");
		NewDir.Move("Spread");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Spawn.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Death.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Death_Enemyhit.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Weak_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Weak_Death.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Weak_Death_Enemyhit.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Spawn.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Flame.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Death.png").GetFullPath(), 6, 1);
	}

	if (nullptr == GameEngineTexture::Find("Dust_A.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("SFX");
		NewDir.Move("PlayerDust");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_A.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_B.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_C.png").GetFullPath(), 5, 4);
	}

	if (nullptr == GameEngineSprite::Find("JumpDust"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("SFX");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("JumpDust").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DashDust").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("EXDust").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("EX_ChargeUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ParryEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("HitSFX").GetFullPath());
	}

	IsTextureLoadEnd = true;
} 

void TutorialTexture(GameEngineThread* Thread)
{
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

	if (nullptr == GameEngineTexture::Find("Tutorial_BackLayer_001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Tutorial_Normal");
		NewDir.Move("Drawing");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Tutorial_BackLayer_001.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("tutorial_pyramid_topper.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Tutorial_Normal");
		NewDir.Move("Shapes_and_Exit_Door");

		GameEngineTexture::Load(NewDir.GetPlusFileName("tutorial_pyramid_topper.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Target"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Tutorial_Normal");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Target").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Explosion"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Tutorial_Normal");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Explosion").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Tutorial_BackLayer_002.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Tutorial_Normal");
		NewDir.Move("Drawing");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Tutorial_BackLayer_002.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Health.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");

		GameEngineTexture::Load(NewDir.GetPlusFileName("PeashooterUI.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("SpreadUI.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Health.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Health");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Health.png").GetFullPath(), 6, 2);
	}

	if (nullptr == GameEngineSprite::Find("CardUI"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CardUI").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Action");

		// Idle
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Idle").GetFullPath());

		// Move
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Move").GetFullPath());

		// Jump & Parry(Slap)
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Jump").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Parry").GetFullPath());

		// Dash
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirDash").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dash").GetFullPath());

		// Duck
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DuckReady").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Duck").GetFullPath());

		// Hit & Death
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirHit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ghost").GetFullPath());

		// Hold
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_Up").GetFullPath());

		// Attack(Move, Duck, Hold(==Idle))
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Move_Attak_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Move_Attak_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DuckAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_Up").GetFullPath());

		// EX
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_Up").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_Up").GetFullPath());

		// Interaction & Intro
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ElderKettleInteraction").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Intro_Flex").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Intro_Regular").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Portal").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Parry_Pink_0.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Action");
		NewDir.Move("Parry_Pink");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_0.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_1.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_2.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_3.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_4.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_5.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_6.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_7.png").GetFullPath(), 1, 1);
	}

	if (nullptr == GameEngineTexture::Find("Peashooter_Spawn.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("Attack");
		NewDir.Move("Peashooter");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_Spawn.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_Loop.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_Death.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_EX_Loop.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_EX_Death.png").GetFullPath(), 5, 2);
	}

	if (nullptr == GameEngineTexture::Find("Spread_Spawn.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("Attack");
		NewDir.Move("Spread");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Spawn.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Death.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Death_Enemyhit.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Weak_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Weak_Death.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Weak_Death_Enemyhit.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Spawn.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Flame.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Death.png").GetFullPath(), 6, 1);
	}

	if (nullptr == GameEngineTexture::Find("Dust_A.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("SFX");
		NewDir.Move("PlayerDust");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_A.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_B.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_C.png").GetFullPath(), 5, 4);
	}

	if (nullptr == GameEngineSprite::Find("JumpDust"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("SFX");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("JumpDust").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DashDust").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("EXDust").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("EX_ChargeUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ParryEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("HitSFX").GetFullPath());
	}

	IsTextureLoadEnd = true;
}

void OverworldTexture(GameEngineThread* Thread)
{
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

	if (nullptr == GameEngineTexture::Find("Overworld_Map.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Overworld");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Overworld_Map.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Overworld_Bush_Left.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Overworld");

		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\Bush\\Overworld_Bush_Left.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\Bush\\Overworld_Bush_Right.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\2.Right\\Mausoleum_Bush.png").GetFullPath());

		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\0.Small_Island\\Dock&Boat\\Dock.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\0.Small_Island\\Dock&Boat\\Boat.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\0.Small_Island\\Lighthouse&Bouy\\Lighthouse.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\0.Small_Island\\Lighthouse&Bouy\\Lighthouse_Buoy.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Tree_Island.png").GetFullPath());

		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\0.Small_Island\\MainBridge\\MainBridge_FrontTopper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Bridges\\ClipBridge\\ClipBridge_FrontTopper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Bridges\\ForestBridge\\ForestBridge_FrontTopper.png").GetFullPath());

		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Stairs\\BotanicStair\\BotanicStair_FrontTopper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Stairs\\RuseStair\\RuseStair_Topper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Stairs\\TreetopStair\\TreetopStair_FrontTopper.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("AppleTraveller_Blink"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("Overworld_NPCs");
		NewDir.Move("AppleTraveller");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AppleTraveller_Blink").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AppleTraveller_HoboStick").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AppleTraveller_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AppleTraveller_Wave").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AppleTraveller_Wave_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AppleTraveller_Wave_Outro").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Axeman_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("Overworld_NPCs");
		NewDir.Move("Axeman");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Axeman_Idle").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Canteen_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("Overworld_NPCs");
		NewDir.Move("Canteen");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Canteen_Idle").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Coin_Blink"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("Overworld_NPCs");
		NewDir.Move("Coin");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Blink").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Boil_A").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Hold_A").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Hold_B").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Hold_C").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Hold_D").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Transition_A").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Transition_B").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Transition_C").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Transition_D").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Transition_E").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Transition_F").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("FishGirl_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("Overworld_NPCs");
		NewDir.Move("FishGirl");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("FishGirl_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("FishGirl_Blink").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Flag.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Overworld");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Flag.png").GetFullPath(), 5, 6);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("FlagShadow.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Djimmi_The_Great.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Grim_Matchstick.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Hilda_Berg.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Ribby_and_Croaks.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Ribby_and_Croaks_Wave.png").GetFullPath(), 7, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Tutorial_Fly.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_WaittingRoom.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Werner_Werman.png").GetFullPath(), 3, 1);
	}

	if (nullptr == GameEngineSprite::Find("DD_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Overworld");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DD_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DD_Move").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Down_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Down_Move").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DU_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DU_Move").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Side_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Side_Move").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Up_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Up_Move").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("InterAction_Win").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Dust_A.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("SFX");
		NewDir.Move("PlayerDust");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_A.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_B.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_C.png").GetFullPath(), 5, 4);
	}

	IsTextureLoadEnd = true;
}

void FrogTexture(GameEngineThread* Thread)
{
	if (nullptr == GameEngineTexture::Find("Health.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");

		GameEngineTexture::Load(NewDir.GetPlusFileName("PeashooterUI.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("SpreadUI.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Health.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Health");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Health.png").GetFullPath(), 6, 2);
	}

	if (nullptr == GameEngineSprite::Find("CardUI"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CardUI").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Action");

		// Idle
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Idle").GetFullPath());

		// Move
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Move").GetFullPath());

		// Jump & Parry(Slap)
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Jump").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Parry").GetFullPath());

		// Dash
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirDash").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dash").GetFullPath());

		// Duck
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DuckReady").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Duck").GetFullPath());

		// Hit & Death
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirHit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ghost").GetFullPath());

		// Hold
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_Up").GetFullPath());

		// Attack(Move, Duck, Hold(==Idle))
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Move_Attak_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Move_Attak_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DuckAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_Up").GetFullPath());

		// EX
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_Up").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_Up").GetFullPath());

		// Interaction & Intro
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ElderKettleInteraction").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Intro_Flex").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Intro_Regular").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Portal").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Parry_Pink_0.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Action");
		NewDir.Move("Parry_Pink");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_0.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_1.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_2.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_3.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_4.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_5.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_6.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_7.png").GetFullPath(), 1, 1);
	}

	if (nullptr == GameEngineTexture::Find("Peashooter_Spawn.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("Attack");
		NewDir.Move("Peashooter");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_Spawn.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_Loop.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_Death.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_EX_Loop.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_EX_Death.png").GetFullPath(), 5, 2);
	}

	if (nullptr == GameEngineTexture::Find("Spread_Spawn.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("Attack");
		NewDir.Move("Spread");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Spawn.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Death.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Death_Enemyhit.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Weak_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Weak_Death.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Weak_Death_Enemyhit.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Spawn.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Flame.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Death.png").GetFullPath(), 6, 1);
	}

	if (nullptr == GameEngineTexture::Find("Dust_A.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("SFX");
		NewDir.Move("PlayerDust");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_A.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_B.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_C.png").GetFullPath(), 5, 4);
	}

	if (nullptr == GameEngineSprite::Find("JumpDust"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("SFX");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("JumpDust").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DashDust").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("EXDust").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("EX_ChargeUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ParryEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("HitSFX").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Deliver"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("1_Ribby_and_Croaks");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Deliver").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Dancer"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("1_Ribby_and_Croaks");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dancer").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Crowd"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("1_Ribby_and_Croaks");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Crowd").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Craber"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("1_Ribby_and_Croaks");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Craber").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Cheerer"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("1_Ribby_and_Croaks");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cheerer").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Croaks_Intro"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Croaks");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_Idle").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_CreateMob_Start").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_CreateMob_Start_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_CreateMob_Start_Out").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_CreateMob").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_CreateMob_End").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_Fan_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_Fan_LoopA").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_Fan_LoopB").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_Fan_Outro").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_Fan_Wind_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_Fan_Wind_Loop").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Slot_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Croaks");
		NewDir.Move("Croaks_SlotMachine");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_Morph_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_Morph_Intro_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_Morph_Outro").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_InitialOpen").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_ArmMove_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_ArmMove_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_ArmMove_Outro").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_Attack_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_Attack_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_Attack_Outro").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_Death_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_Death_Loop").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Firefly_Death"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Croaks");
		NewDir.Move("Croaks_Firefly");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Firefly_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Firefly_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Firefly_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Firefly_Left").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Firefly_Up").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Slot_CoinMouth"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Croaks");
		NewDir.Move("Croaks_SlotMachine");
		NewDir.Move("Slot_Coin");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_CoinMouth").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Projectile").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Slot_Dust_Front"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Croaks");
		NewDir.Move("Croaks_SlotMachine");
		NewDir.Move("Slot_Dust");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_Dust_Front").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Slot_TEMP.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Croaks");
		NewDir.Move("Croaks_SlotMachine");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Slot_TEMP.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Slot_flash_TEMP.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Slot_ImageBack.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("SlotMachine_Attack_Front_001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Croaks");
		NewDir.Move("Croaks_SlotMachine");
		NewDir.Move("Attack_Front");

		GameEngineTexture::Load(NewDir.GetPlusFileName("SlotMachine_Attack_Front_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("SlotMachine_Attack_Front_002.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("SlotMachine_Attack_Front_003.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("SlotMachine_Attack_Front_004.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("SlotMachine_Attack_Front_005.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("SlotMachine_Attack_Front_006.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Explosion"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Tutorial_Normal");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Explosion").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Snake_Platform"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Croaks");
		NewDir.Move("Croaks_SlotMachine");
		NewDir.Move("Attack_Platforms");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Snake_Platform").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Tiger_Ball").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Tiger_Platform").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bison_Flame_Large_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bison_Flame_Large_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bison_Flame_Small_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bison_Platform").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Platform_Bison_Front_001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Croaks");
		NewDir.Move("Croaks_SlotMachine");
		NewDir.Move("Attack_Platforms");
		NewDir.Move("Bison_Front");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Platform_Bison_Front_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Platform_Bison_Front_002.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Platform_Bison_Front_003.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Platform_Bison_Front_004.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Platform_Bison_Front_005.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Platform_Bison_Front_006.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Platform_Bison_Front_007.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Platform_Bison_Front_008.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Platform_Bison_Front_009.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Platform_Bison_Front_010.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Platform_Tiger_Front_001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Croaks");
		NewDir.Move("Croaks_SlotMachine");
		NewDir.Move("Attack_Platforms");
		NewDir.Move("Tiger_Front");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Platform_Tiger_Front_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Platform_Tiger_Front_002.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Platform_Tiger_Front_003.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Platform_Tiger_Front_004.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Platform_Tiger_Front_005.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Platform_Tiger_Front_006.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Platform_Tiger_Front_007.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Platform_Tiger_Front_008.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Platform_Tiger_Front_009.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Platform_Tiger_Front_010.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Ribby_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Ribby");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_Intro_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_Intro_End").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_Idle").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_FistAttack_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_FistAttack_Intro_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_FistAttack_Intro_out").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_FistAttack_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_FistAttack_End").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_Roll_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_Roll_Intro_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_Roll_Intro_Out").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_Roll_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_Roll_End").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_ClapAttack_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_ClapAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_ClapAttack_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_ClapAttack_LoopBack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_ClapAttack_End").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Normal_Loop"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Ribby");
		NewDir.Move("Fist_Projectile");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Normal_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Normal_Spawn").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Pink_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Pink_Spawn").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Spark").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Death_FX").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Clap_Ball"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Ribby");
		NewDir.Move("Clap_Projectile");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Clap_Ball").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Clap_FX").GetFullPath());
	}

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

	if (nullptr == GameEngineTexture::Find("Backstage_1.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("1_Ribby_and_Croaks");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Backstage_1.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Backstage_2.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Backstage_3.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Plant_1.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("1_Ribby_and_Croaks");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Table_1.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Table_2.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Plant_1.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Plant_2.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Plant_3.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("KNOCKOUT"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Font");
		NewDir.Move("Message");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("KNOCKOUT").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("YOU_DIED.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Font");
		NewDir.Move("Message");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("YOU_DIED.png").GetFullPath(), 3, 7);
	}

	if (nullptr == GameEngineSprite::Find("Ready_WALLOP"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Font");
		NewDir.Move("Message");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ready_WALLOP").GetFullPath());
	}

	IsTextureLoadEnd = true;
}

void MouseTexture(GameEngineThread* Thread)
{
	if (nullptr == GameEngineSprite::Find("KNOCKOUT"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Font");
		NewDir.Move("Message");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("KNOCKOUT").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("YOU_DIED.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Font");
		NewDir.Move("Message");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("YOU_DIED.png").GetFullPath(), 3, 7);
	}

	if (nullptr == GameEngineSprite::Find("Ready_WALLOP"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Font");
		NewDir.Move("Message");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ready_WALLOP").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Health.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");

		GameEngineTexture::Load(NewDir.GetPlusFileName("PeashooterUI.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("SpreadUI.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Health.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Health");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Health.png").GetFullPath(), 6, 2);
	}

	if (nullptr == GameEngineSprite::Find("CardUI"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CardUI").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Action");

		// Idle
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Idle").GetFullPath());

		// Move
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Move").GetFullPath());

		// Jump & Parry(Slap)
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Jump").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Parry").GetFullPath());

		// Dash
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirDash").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dash").GetFullPath());

		// Duck
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DuckReady").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Duck").GetFullPath());

		// Hit & Death
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirHit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ghost").GetFullPath());

		// Hold
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_Up").GetFullPath());

		// Attack(Move, Duck, Hold(==Idle))
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Move_Attak_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Move_Attak_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DuckAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_Up").GetFullPath());

		// EX
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_Up").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_Up").GetFullPath());

		// Interaction & Intro
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ElderKettleInteraction").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Intro_Flex").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Intro_Regular").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Portal").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Parry_Pink_0.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Action");
		NewDir.Move("Parry_Pink");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_0.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_1.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_2.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_3.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_4.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_5.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_6.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_7.png").GetFullPath(), 1, 1);
	}

	if (nullptr == GameEngineTexture::Find("Peashooter_Spawn.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("Attack");
		NewDir.Move("Peashooter");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_Spawn.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_Loop.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_Death.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_EX_Loop.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_EX_Death.png").GetFullPath(), 5, 2);
	}

	if (nullptr == GameEngineTexture::Find("Spread_Spawn.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("Attack");
		NewDir.Move("Spread");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Spawn.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Death.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Death_Enemyhit.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Weak_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Weak_Death.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Weak_Death_Enemyhit.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Spawn.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Flame.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Death.png").GetFullPath(), 6, 1);
	}

	if (nullptr == GameEngineTexture::Find("Dust_A.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("SFX");
		NewDir.Move("PlayerDust");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_A.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_B.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_C.png").GetFullPath(), 5, 4);
	}

	if (nullptr == GameEngineSprite::Find("JumpDust"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("SFX");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("JumpDust").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DashDust").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("EXDust").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("EX_ChargeUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ParryEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("HitSFX").GetFullPath());
	}

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

	if (nullptr == GameEngineTexture::Find("Mouse_BackGround_Phase_1.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("3_Werner_Werman");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_BackGround_Phase_1.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_BackGround_Phase_2.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_House_BackGround.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_BackGround_Phase_3B.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Phase2_Platform"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("3_Werner_Werman");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase2_Platform").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase3_WallBrake").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("mouse_bg_bullet_a.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Mouse_BackMapObject");

		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_bullet_a.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_bullet_b.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_bullet_c.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_bullet_d.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_blue_stool.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_red_stool.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_thimble_a.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_thimble_b.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_die.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_table.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Mouse_Intro"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_Intro_Front").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_Intro_Smoke").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_PopOut").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_ShakeFist").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_Dash_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_Dash_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_Dash_Outro").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Cannon_In"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");
		NewDir.Move("Object_Cannon");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cannon_In").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cannon_Out").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cannon_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cannon_Shoot").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Catapult_Loop"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");
		NewDir.Move("Object_Catapult");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Catapult_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Catapult_Reload").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Catapult_Reload_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Catapult_Fire").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Can_Part_Body_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Part_Body_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Part_Body_Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Part_Body_In").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Part_Body_Out").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Part_Wheels").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("CherryBomb_Normal"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");
		NewDir.Move("Object_CherryBomb");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CherryBomb_Normal").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CherryBomb_Pink").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CherryBomb_Explode").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CherryBomb_Fire_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CherryBomb_Fire_Loop").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("CatapultProjectile_Bolt"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");
		NewDir.Move("Object_CatapultProjectile");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CatapultProjectile_Bolt").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CatapultProjectile_Coin").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CatapultProjectile_Gum").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CatapultProjectile_Nut").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CatapultProjectile_Popcap").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CatapultProjectile_Tooth").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Spring_Intro"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");
		NewDir.Move("Object_Spring");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Spring_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Spring_Land").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Spring_Idle_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Spring_Launch").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Spring_Death").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Can_Explosion_Intro"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Explosion_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Explosion_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Explosion_Outro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Explosion_SFX").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_IntroBomb").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Can_Explosion_SFX"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Explosion_SFX").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Plat_Loop"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Plat_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Plat_MoveLeft").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Plat_MoveLeft_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Plat_MoveRight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Plat_MoveRight_Loop").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Mouse_TransitionA"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_TransitionA").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_TransitionA_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_TransitionB").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_TransitionB_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_TransitionC").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_TransitionC_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_TransitionD").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_TransitionD_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_Transition_EndLoop").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Can_Tin_Up"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Tin_Up").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Object_Flamecannon"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Flamecannon").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Scissor_Intro"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase2");
		NewDir.Move("Object_Scissor");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Scissor_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Scissor_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Scissor_Down_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Scissor_Up").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Scissor_Up_Loop").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Flamethrower_Intro_Loop"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase2");
		NewDir.Move("Object_Flamethrower");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Flamethrower_Intro_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Flamethrower_Fire_Outro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Flamethrower_Fire_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Flamethrower_Fire").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Stick_A"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase2");
		NewDir.Move("Sidsticks_Stick");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Stick_A").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Stick_B").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Stick_C").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Bottlecap_A"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase2");
		NewDir.Move("Sidsticks_Bottlecap");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottlecap_A").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottlecap_B").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottlecap_C").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottlecap_D").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottlecap_E").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottlecap_F").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Can_Idle_Up_001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");
		NewDir.Move("Can_Part_Body_IdleUp");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Idle_Up_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Idle_Up_002.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Idle_Up_003.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Can_Idle_Back_001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");
		NewDir.Move("Can_Part_Back_Idle");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Idle_Back_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Idle_Back_002.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Idle_Back_003.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Can_Part_Back_InOut_001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");
		NewDir.Move("Can_Part_Back_InOut");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Part_Back_InOut_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Part_Back_InOut_002.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Part_Back_InOut_003.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Can_Move_Back_001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");
		NewDir.Move("Can_Part_Back_Move");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_002.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_003.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_004.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_005.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_006.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_007.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_008.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_009.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_010.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_011.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_012.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_013.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_014.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_015.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_016.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_017.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_018.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_019.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_020.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_021.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_022.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_023.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_024.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Mouse_Intro_Top_007.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");
		NewDir.Move("Mouse_Intro_Front");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_007.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_008.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_009.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_010.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_011.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_012.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_013.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_014.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_015.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_016.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_017.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_018.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_019.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_020.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_021.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_022.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_023.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_024.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_025.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_026.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_027.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_028.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_029.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_030.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_031.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_032.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_046.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_047.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_048.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_049.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Tin_Boil_Back_001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase2");
		NewDir.Move("Can_Tin_Back");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Tin_Boil_Back_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Tin_Boil_Back_002.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Tin_Boil_Back_003.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Cat_Intro_Body"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase3");

		// Body
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Intro_Body").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Idle_Body").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Death_Body").GetFullPath());

		// Head
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Intro_Head").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Idle_Head").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Claw_Head_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Claw_Head_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Claw_Head_Outro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Death_HeadObject").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Death_HeadObject_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Ghost_Spawn_Head_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Ghost_Spawn_Head_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Ghost_Spawn_Head_Outro").GetFullPath());

		// Arm
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Idle_LeftHand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Idle_RightHand").GetFullPath());

		// AttackArm
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Claw_Hand_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Claw_Hand_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Claw_Hand_Outro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Claw_Hand_Hit").GetFullPath());

		// SFX
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Death_SFX").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Object_WoodPiece_Loop"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase3");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_WoodPiece_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_WoodPiece_Death").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Explosion"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Tutorial_Normal");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Explosion").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Ghost_Intro"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase3");
		NewDir.Move("Object_Ghost");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ghost_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ghost_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ghost_Attack_Pink").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ghost_Attack_Blue").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ghost_Attack_Outro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ghost_Death").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("GhostBullet_Blue_Intro"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase3");
		NewDir.Move("Object_GhostBullet_Blue");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GhostBullet_Blue_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GhostBullet_Blue_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GhostBullet_Blue_Death").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("GhostBullet_Pink_Intro"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase3");
		NewDir.Move("Object_GhostBullet_Pink");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GhostBullet_Pink_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GhostBullet_Pink_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GhostBullet_Pink_Death").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("UpTexture.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase3");

		GameEngineTexture::Load(NewDir.GetPlusFileName("UpTexture.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("mouse_bg_foreground_a.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Mouse_FrontMapObject");

		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_foreground_a.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_foreground_b1.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_foreground_b2.png").GetFullPath());
	}

	IsTextureLoadEnd = true;
}

void DragonTexture(GameEngineThread* Thread)
{
	if (nullptr == GameEngineSprite::Find("KNOCKOUT"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Font");
		NewDir.Move("Message");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("KNOCKOUT").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("YOU_DIED.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Font");
		NewDir.Move("Message");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("YOU_DIED.png").GetFullPath(), 3, 7);
	}

	if (nullptr == GameEngineSprite::Find("Ready_WALLOP"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Font");
		NewDir.Move("Message");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ready_WALLOP").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Health.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");

		GameEngineTexture::Load(NewDir.GetPlusFileName("PeashooterUI.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("SpreadUI.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Health.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Health");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Health.png").GetFullPath(), 6, 2);
	}

	if (nullptr == GameEngineSprite::Find("CardUI"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CardUI").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Action");

		// Idle
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Idle").GetFullPath());

		// Move
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Move").GetFullPath());

		// Jump & Parry(Slap)
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Jump").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Parry").GetFullPath());

		// Dash
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirDash").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dash").GetFullPath());

		// Duck
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DuckReady").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Duck").GetFullPath());

		// Hit & Death
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirHit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ghost").GetFullPath());

		// Hold
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Normal_Up").GetFullPath());

		// Attack(Move, Duck, Hold(==Idle))
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Move_Attak_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Move_Attak_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DuckAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Hold_Shoot_Up").GetFullPath());

		// EX
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AirEX_Up").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_DiagonalDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_DiagonalUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_Straight").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ex_Up").GetFullPath());

		// Interaction & Intro
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ElderKettleInteraction").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Intro_Flex").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Intro_Regular").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Portal").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Parry_Pink_0.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Action");
		NewDir.Move("Parry_Pink");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_0.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_1.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_2.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_3.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_4.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_5.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_6.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Parry_Pink_7.png").GetFullPath(), 1, 1);
	}

	if (nullptr == GameEngineTexture::Find("Peashooter_Spawn.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("Attack");
		NewDir.Move("Peashooter");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_Spawn.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_Loop.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_Death.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_EX_Loop.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Peashooter_EX_Death.png").GetFullPath(), 5, 2);
	}

	if (nullptr == GameEngineTexture::Find("Spread_Spawn.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("Attack");
		NewDir.Move("Spread");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Spawn.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Death.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Death_Enemyhit.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Weak_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Weak_Death.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_Weak_Death_Enemyhit.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Spawn.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Loop.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Flame.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Spread_EX_Death.png").GetFullPath(), 6, 1);
	}

	if (nullptr == GameEngineTexture::Find("Dust_A.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("SFX");
		NewDir.Move("PlayerDust");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_A.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_B.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Dust_C.png").GetFullPath(), 5, 4);
	}

	if (nullptr == GameEngineSprite::Find("JumpDust"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("Ground");
		NewDir.Move("Effect");
		NewDir.Move("SFX");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("JumpDust").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DashDust").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("EXDust").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("EX_ChargeUp").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ParryEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("HitSFX").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Dragon_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Phase1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_Idle").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_MeteorAttack_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_MeteorAttack_Intro_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_MeteorAttack_Shoot_Front").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_MeteorAttack_Shoot_LollBack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_MeteorAttack_Outro").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_PeashotAttack_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_PeashotAttack_Shoot").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_PeashotAttack_Outro").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Dragon_Ph2_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_Ph2_Intro_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_Ph2_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_Ph2_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_Ph2_Death").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Ph2_IdleUp_000.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Phase2");
		NewDir.Move("Dragon_Ph2_Idle_T");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_000.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_002.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_003.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_004.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_005.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_006.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_007.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_008.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_009.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_010.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_011.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_012.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_013.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Ph2_DeathUp_000.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Phase2");
		NewDir.Move("Dragon_Ph2_Death_T");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_DeathUp_000.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_DeathUp_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_DeathUp_002.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_DeathUp_003.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_DeathUp_004.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_DeathUp_005.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_DeathUp_006.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_DeathUp_007.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Dragon_Ph2_Tounge_Intro"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_Ph2_Tounge_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_Ph2_Tounge_Intro_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_Ph2_Tounge_Outro").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Fire_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Fire_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Fire_Outro").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_FireSmoke_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_FireSmoke_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_FireSmoke_Outro").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SFX_AttackSmoke_A").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SFX_AttackSmoke_B").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Object_Firework_A_Move"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Firework_Leader").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Firework_A_Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Firework_B_Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Firework_C_Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Firework_C_Jump_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Firework_C_Jump_Inter").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Firework_C_Jump_Loop").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Object_GreenRing"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Phase1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_GreenRing").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_PinkRing").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SFX_EyesAttack").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Meteor").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SFX_MeteorSmoke").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Tail").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Explosion"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Tutorial_Normal");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Explosion").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Dragon_Foreground_Clouds_001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("FrontClouds");
		NewDir.Move("FrontWhite");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Dragon_Foreground_Clouds_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Dragon_Foreground_Clouds_002.png").GetFullPath());
	}

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

	if (nullptr == GameEngineSprite::Find("Cloud_Platform_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Cloud_Platform");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cloud_Platform_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Standing_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Standing_Outro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Standing_Idle").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Dragon_Background_Sky_Normal.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Background");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Dragon_Background_Sky_Normal.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Dragon_Background_Clouds1.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("BackClouds");
		NewDir.Move("Cloud_White");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Dragon_Background_Clouds1.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Dragon_Background_Clouds2.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Dragon_Background_Clouds3.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Dragon_Background_Clouds4.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Dragon_Background_Clouds5.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Dragon_Foreground_Clouds_003.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("FrontClouds");
		NewDir.Move("FrontWhite");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Dragon_Foreground_Clouds_003.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Tower_Light"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Tower");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Tower_Light").GetFullPath());
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

	IsTextureLoadEnd = true;
}

void EndingTexture(GameEngineThread* Thread)
{
	if (nullptr == GameEngineSprite::Find("Page_12-13"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Ending");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_12-13").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_13-14").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_14-15").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_15-16").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_16-17").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_17-18").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_18-End").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Arrow"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("TextBox");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Arrow").GetFullPath());
	}

	IsTextureLoadEnd = true;
}

void LoadingLevel::TextureLoadLevelSelect()
{
	switch (LevelState)
	{
	case LevelValue::First_OpeningLevel:
		GameEngineCore::JobQueue.Work(First_OpeningTexture);
		break;
	case LevelValue::Second_OpeningLevel:
		GameEngineCore::JobQueue.Work(Second_OpeningTexture);
		break;
	case LevelValue::WaitingRoomLevel:
		GameEngineCore::JobQueue.Work(WaitingTexture);
		break;
	case LevelValue::TutorialLevel:
		GameEngineCore::JobQueue.Work(TutorialTexture);
		break;
	case LevelValue::OverworldLevel:
		GameEngineCore::JobQueue.Work(OverworldTexture);
		break;
	case LevelValue::FrogLevel:
		GameEngineCore::JobQueue.Work(FrogTexture);
		break;
	case LevelValue::DragonLevel:
		GameEngineCore::JobQueue.Work(DragonTexture);
		break;
	case LevelValue::MouseLevel:
		GameEngineCore::JobQueue.Work(MouseTexture);
		break;
	case LevelValue::EndingLevel:
		GameEngineCore::JobQueue.Work(EndingTexture);
		break;
	default:
		break;
	}
}
#include "PrecompileHeader.h"
#include "WaitingRoomLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "LoadingLevel.h"

#include "PortalDoor.h"
#include "Player.h"
#include "ElderKettle.h"
#include "WaitingRoom_Map.h"
#include "WaitingRoom_ColMap.h"
#include "RoundBlackBox.h"
#include "TransformGUI.h"

#include <GameEngineCore/BlurEffect.h>
#include "OldFilm.h"

WaitingRoomLevel* WaitingRoomLevel::WaitingRoomLevelPtr = nullptr;

WaitingRoomLevel::WaitingRoomLevel() 
{
}

WaitingRoomLevel::~WaitingRoomLevel() 
{
}

void WaitingRoomLevel::Start()
{
	WaitingRoomLevelPtr = this;
	GetLastTarget()->CreateEffect<BlurEffect>();
	GetLastTarget()->CreateEffect<OldFilm>();

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Sound");
		NewDir.Move("WattingRoom");

		GameEngineSound::Load(NewDir.GetPlusFileName("Elder Kettle.mp3").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("platform_trampoline_bounce_07.wav").GetFullPath());

		GameEngineSound::Load(NewDir.GetPlusFileName("EK_WarStory_001.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("EK_WarStory_002.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("EK_WarStory_003.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("EK_WarStory_004.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("EK_WarStory_005.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("EK_WarStory_006.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("EK_WarStory_007.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("EK_WarStory_008.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("EK_WarStory_009.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("EK_WarStory_010.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("EK_WarStory_011.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("EK_WarStory_012.wav").GetFullPath());
	}

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Sound");
		NewDir.Move("No_Classification");
		NewDir.Move("Menu");

		GameEngineSound::Load(NewDir.GetPlusFileName("Menu_Locked.wav").GetFullPath());
	}

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Sound");
		NewDir.Move("Player");
		NewDir.Move("Player");

		GameEngineSound::Load(NewDir.GetPlusFileName("player_land_ground_01.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("player_powerup_01.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("player_parry_power_up_full.wav").GetFullPath());

		GameEngineSound::Load(NewDir.GetPlusFileName("sfx_player_parry_slap_01.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("player_parry_power_up_hit_01.wav").GetFullPath());

		GameEngineSound::Load(NewDir.GetPlusFileName("player_ex_forward_ground_01.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("player_ex_forward_ground_02.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("player_ex_forward_ground_03.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("player_ex_forward_ground_04.wav").GetFullPath());

		GameEngineSound::Load(NewDir.GetPlusFileName("player_dash_01.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("player_dash_02.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("player_dash_03.wav").GetFullPath());

		GameEngineSound::Load(NewDir.GetPlusFileName("player_jump_01.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("player_jump_02.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("player_jump_03.wav").GetFullPath());

		GameEngineSound::Load(NewDir.GetPlusFileName("sfx_player_default_fire_loop_01.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("sfx_player_spreadshot_fire_loop.wav").GetFullPath());

		GameEngineSound::Load(NewDir.GetPlusFileName("sfx_player_parry_slap_01.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("sfx_player_hit_01.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("sfx_player_damage_crack_level3.wav").GetFullPath());
	}
}
void WaitingRoomLevel::Update(float _DeltaTime)
{
	if (false == IsBGMOn)
	{
		IsBGMOn = true;
		BGMPlayer = GameEngineSound::Play("Elder Kettle.mp3");
		BGMPlayer.SetLoop(100);
	}

	if (true == GameEngineInput::IsDown("PrevLevel"))
	{
		GameEngineCore::ChangeLevel("Second_OpeningLevel");
	}
	if (true == GameEngineInput::IsDown("NextLevel"))
	{
		GameEngineCore::ChangeLevel("TutorialLevel");
	}

	float PlusDist = PlayerObject->GetTransform()->GetLocalPosition().x;
	float Mount = PlayerDist - PlusDist;

	GetMainCamera()->GetTransform()->SetLocalPosition(CameraOriginPos + float4{-Mount / 25 , 0});

	if (true == PlayerObject->GetIsElderKettleEnd() && 1 == PortalCount)
	{
		PortalCount = 0;

		if (nullptr == PortalDoorObject)
		{
			PortalDoorObject = CreateActor<PortalDoor>();
			PortalDoorObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half + 20, PlayMapHeight_Half - 100, -5 });
			PortalDoorObject->SetPortalValue(PortalValue::Tutorial);
			PortalDoorObject->SetEnterMessageRenderPtrPos({ -5, -150 });
		}
	}
}

void WaitingRoomLevel::LevelChangeStart()
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

	// ColMap
	std::shared_ptr<GameEngineTexture> PlayMap = GameEngineTexture::Find("WaitingRoom_ColMap.png");
	int PlayMapWidth = PlayMap->GetWidth();
	int PlayMapHeight = PlayMap->GetHeight();
	PlayMapWidth_Half = static_cast<float>(PlayMapWidth / 2);
	PlayMapHeight_Half = static_cast<float>(PlayMapHeight / 2);

	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 640, PlayMapHeight_Half + 10, -620.0f });
	GetMainCamera()->SetSortType(0, SortType::ZSort);

	CameraOriginPos = GetMainCamera()->GetTransform()->GetLocalPosition();

	{
		if (BlackBoxPtr == nullptr)
		{
			BlackBoxPtr = CreateActor<RoundBlackBox>();
		}

		BlackBoxPtr->BoxSettingReset();
		BlackBoxPtr->SetExit();
	}
	{
		if (nullptr == MapObject)
		{
			MapObject = CreateActor<WaitingRoom_Map>();
		}
		
		MapObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, 10 });
	}
	{
		if (nullptr == KettleObject)
		{
			KettleObject = CreateActor<ElderKettle>();
		}
		
		KettleObject->GetTransform()->SetLocalPosition({ PlayMapWidth_Half + 470 , PlayMapHeight_Half - 110});
		KettleObject->TextBoxPositionSetting();
	}
	{
		if (nullptr == PlayerObject)
		{
			PlayerObject = CreateActor<Player>();
		}
		
		PlayerObject->GetTransform()->SetLocalPosition({ 275 , PlayMapHeight_Half });
		PlayerObject->SetColMap(PlayMap, PixelCollision::Coordinate::Custom);
		PlayerObject->SetCameraSpeedRatio(1.0f);
		PlayerObject->SetCorrectionFalse();
		PlayerObject->SetIsWattingRoomIntroTrue();

		PlayerDist = PlayerObject->GetTransform()->GetLocalPosition().x;
	}
	{
		if (nullptr == ThisColMap)
		{
			ThisColMap = CreateActor<WaitingRoom_ColMap>();
		}
		
		ThisColMap->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, -5 });
	}
	{
		if (nullptr != PortalDoorObject)
		{
			PortalDoorObject->BlackBoxCountReset();
		}
	}

	// GUI
	{
		if (nullptr == GUI)
		{
			GUI = GameEngineGUI::FindGUIWindowConvert<TransformGUI>("TransformGUI");
		}
		
		GUI->SetTarget(PlayerObject->GetTransform());
		GUI->SetMainPalyer(PlayerObject);

		GUI->PlayerDebugRenderOn = std::bind(&WaitingRoomLevel::PlayerDebugRenderOn, this);
		GUI->PlayerDebugRenderOff = std::bind(&WaitingRoomLevel::PlayerDebugRenderOff, this);
		GUI->ColMapRenderOn = std::bind(&WaitingRoomLevel::LevelDebugOn, this);
		GUI->ColMapRenderOff = std::bind(&WaitingRoomLevel::LevelDebugOff, this);
	}
}

void WaitingRoomLevel::LevelChangeEnd()
{
	bool playing = false;

	BGMPlayer.isPlaying(&playing);

	if (true == playing)
	{
		BGMPlayer.Stop();
	}

	if (nullptr != GameEngineTexture::Find("WaitingRoom_Background.png"))
	{
		GameEngineTexture::UnLoad("WaitingRoom_Background.png");
		GameEngineTexture::UnLoad("WaitingRoom_Chair.png");
		GameEngineTexture::UnLoad("WaitingRoom_Couch.png");
		GameEngineTexture::UnLoad("WaitingRoom_Vignette.png");
	}

	if (nullptr != GameEngineSprite::Find("Note_One"))
	{
		GameEngineSprite::UnLoad("Note_One");
		GameEngineSprite::UnLoad("Note_Two");
	}

	if (nullptr != GameEngineSprite::Find("Kettle_Idle"))
	{
		GameEngineSprite::UnLoad("Kettle_Idle");
		GameEngineSprite::UnLoad("Bottle_Pop");
		GameEngineSprite::UnLoad("Bottle_Pop_Boil");
		GameEngineSprite::UnLoad("Bottle_Pop_Trans_Idle");
		GameEngineSprite::UnLoad("Talk_A");
		GameEngineSprite::UnLoad("Talk_AToB");
		GameEngineSprite::UnLoad("Talk_BToA");
		GameEngineSprite::UnLoad("Talk_B");
	}

	if (nullptr != GameEngineSprite::Find("Bottle_Appear.png"))
	{
		GameEngineSprite::UnLoad("Bottle_Appear.png");
		GameEngineSprite::UnLoad("Bottle_Hold.png");
		GameEngineSprite::UnLoad("Bottle_FX.png");
	}

	if (nullptr != GameEngineTexture::Find("WaitingRoom_ColMap.png"))
	{
		GameEngineTexture::UnLoad("WaitingRoom_ColMap.png");
	}

	{
		IsBGMOn = false;
		PlayMapWidth_Half = 0.0f;
		PlayMapHeight_Half = 0.0f;
		PlayerDist = 0.0f;
		CameraOriginPos = float4::Zero;
	}
}

void WaitingRoomLevel::PlayerDebugRenderOn()
{
	if (nullptr != PlayerObject)
	{
		PlayerObject->PlayerDebugRenderOn();
	}
}

void WaitingRoomLevel::PlayerDebugRenderOff()
{
	if (nullptr != PlayerObject)
	{
		PlayerObject->PlayerDebugRenderOff();
	}
}

void WaitingRoomLevel::LevelDebugOn()
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
	if (nullptr != KettleObject)
	{
		KettleObject->DebugRenderOn();
	}
}
void WaitingRoomLevel::LevelDebugOff()
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
	if (nullptr != KettleObject)
	{
		KettleObject->DebugRenderOff();
	}
}
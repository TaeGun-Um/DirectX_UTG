#include "PrecompileHeader.h"
#include "FrogLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "Frog_Map.h"
#include "Frog_ColMap.h"
#include "Player.h"
#include "CardUI.h"
#include "HealthUI.h"
#include "Ribby.h"

#include "OverworldLevel.h"

#include "Loading.h"
#include "RoundBlackBox.h"
#include "Knockout.h"
#include "Ready_Wallop.h"
#include "You_Died.h"
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
	if (true == RibbyObject->GetIsStageEnd() && 1 == EndSetCount)
	{
		EndSetCount = 0;
		KnockoutPtr->StartMessage();
		IsBossEnd = true;
		GameEngineTime::GlobalTime.SetTimeScale(0.0f);
	}

	if (true == IsBossEnd)
	{
		//NormalDeltaTime += GameEngineTime::GlobalTime.GetNormalDeltaTime();

		EndTime += _DeltaTime;

		if (true == KnockoutPtr->GetIsEnd())
		{
			GameEngineTime::GlobalTime.SetTimeScale(1.0f);

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

	ReadyWallopTime += _DeltaTime;

	if (1.0f <= ReadyWallopTime && 1 == ReadyWallopCount)
	{
		ReadyWallopCount = 0;
		ReadyWallopPtr->StartMessage();
	}

	if (true == ReadyWallopPtr->GetIsEnd())
	{
		int a = 0;
	}

	if (true == GameEngineInput::IsDown("PrevLevel") && 1 == DebugBoxCount)
	{
		DebugBoxCount = 0;
		BlackBoxPtr->BoxSettingReset();
		BlackBoxPtr->SetEnter();
	}

	if (true == BlackBoxPtr->GetIsEnd() && 0 == DebugBoxCount)
	{
		LoadingOn();
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
		if (nullptr == RibbyObject)
		{
			RibbyObject = CreateActor<Ribby>();
		}
		
		RibbyObject->GetTransform()->SetLocalPosition({ 1000 , 250 });
		RibbyObject->SetInitReset();
	}
	{
		if (nullptr == PlayerObject)
		{
			PlayerObject = CreateActor<Player>();
		}
		
		PlayerObject->GetTransform()->SetLocalPosition({ 220 , PlayMapHeight_Half });
		PlayerObject->SetCorrectionFalse();
		PlayerObject->SetColMap(PlayMap, PixelCollision::Coordinate::Custom);
		PlayerObject->SetCameraSpeedRatio(1.0f);
	}
	{
		if (nullptr == ThisColMap)
		{
			ThisColMap = CreateActor<Frog_ColMap>();
		}
		
		ThisColMap->GetTransform()->SetLocalPosition({ PlayMapWidth_Half, PlayMapHeight_Half, -5 });
	}
	{
		if (nullptr == HealthObject)
		{
			HealthObject = CreateActor<HealthUI>();
		}

		if (nullptr == CardObject)
		{
			CardObject = CreateActor<CardUI>();
		}
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
			KnockoutPtr = CreateActor<Knockout>();
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
		GUI->SetForgBoss(RibbyObject);

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
}
void FrogLevel::LevelChangeEnd()
{
	DebugBoxCount = 1;
	ReadyWallopCount = 1;
	ReadyWallopTime = 0.0f;
	PlayerObject->PlayerStatusReset();
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
	if (nullptr != ThisColMap)
	{
		RibbyObject->DebugRenderOn();
	}
}
void FrogLevel::LevelDebugOff()
{
	if (nullptr != ThisColMap)
	{
		ThisColMap->ColMapDebugRenderOff();
	}
	if (nullptr != ThisColMap)
	{
		RibbyObject->DebugRenderOff();
	}
}
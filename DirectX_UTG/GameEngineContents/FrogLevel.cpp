#include "PrecompileHeader.h"
#include "FrogLevel.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "Frog_Map.h"
#include "Frog_ColMap.h"
#include "Player.h"
#include "Ribby.h"

#include "Loading.h"
#include "RoundBlackBox.h"
#include "TransformGUI.h"

FrogLevel::FrogLevel() 
{
}

FrogLevel::~FrogLevel() 
{
}

void FrogLevel::Start()
{

}
void FrogLevel::Update(float _DeltaTime)
{

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
	}
	{
		if (nullptr == PlayerObject)
		{
			PlayerObject = CreateActor<Player>();
		}
		
		PlayerObject->GetTransform()->SetLocalPosition({ 220 , PlayMapHeight_Half });
		PlayerObject->SetCorrectionTrue();
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

	// GUI
	if (nullptr == GUI)
	{
		GUI = GameEngineGUI::FindGUIWindowConvert<TransformGUI>("TransformGUI");
		GUI->SetTarget(PlayerObject->GetTransform());
		GUI->SetMainPalyer(PlayerObject);

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
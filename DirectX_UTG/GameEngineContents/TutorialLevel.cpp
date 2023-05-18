#include "PrecompileHeader.h"
#include "TutorialLevel.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h> // 지울것
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Tutorial_BackGround.h"
#include "Tutorial_BackLayer.h"
#include "Tutorial_Map.h"
#include "Tutorial_ColMap.h"
#include "PortalDoor.h"
#include "Player.h"

#include "Screen_FX.h"
#include "Loading.h"
#include "TestPlatform.h"

#include "TransformGUI.h"

TutorialLevel::TutorialLevel() 
{
}

TutorialLevel::~TutorialLevel() 
{
}

void TutorialLevel::Start()
{
}

void TutorialLevel::PlayerDebugRenderOn()
{
	PlayerObject->PlayerDebugRenderOn();
}

void TutorialLevel::PlayerDebugRenderOff()
{
	PlayerObject->PlayerDebugRenderOff();
}

void TutorialLevel::TutorialColMapOn()
{
	ThisColMap->ColMapDebugRenderOn();
}
void TutorialLevel::TutorialColMapOff()
{
	ThisColMap->ColMapDebugRenderOff();
}

void TutorialLevel::Update(float _DeltaTime)
{
}

void TutorialLevel::LevelChangeStart()
{
	// 레벨 리소스 로드
	if (nullptr == GameEngineTexture::Find("Tutorial_Map"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Tutorial_Normal");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	// ColMap
	std::shared_ptr<GameEngineTexture> PlayMap = GameEngineTexture::Find("Tutorial_ColMap.png");
	int PlayMapWidth = PlayMap->GetWidth();
	int PlayMapHeight = PlayMap->GetHeight();
	float PlayMapWidth_Half = static_cast<float>(PlayMapWidth / 2);
	float PlayMapHeight_Half = static_cast<float>(PlayMapHeight / 2);
	float4 PlayMapPosition = { PlayMapWidth_Half, PlayMapHeight_Half, 1 };

	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	//GetMainCamera()->GetTransform()->SetLocalPosition({ 640, PlayMapHeight_Half - 100, -620.0f });
	GetMainCamera()->GetTransform()->SetLocalPosition({ 3600, PlayMapHeight_Half - 100, -620.0f });

	// CreateActor
	// Character
	{
		if (nullptr == PlayerObject)
		{
			PlayerObject = CreateActor<Player>(-1);
			// PlayerObject->GetTransform()->SetLocalPosition({ 300 , PlayMapHeight_Half, 1 });
			PlayerObject->GetTransform()->SetLocalPosition({ 3600 , PlayMapHeight_Half, 1 });
			PlayerObject->SetColMap(PlayMap, PixelCollision::Coordinate::Custom);
		}
	}
	// Background, Map
	{
		std::shared_ptr<Tutorial_BackGround> Object0 = CreateActor<Tutorial_BackGround>(-100);
		Object0->GetTransform()->SetLocalPosition({ 640 , PlayMapHeight_Half - 100, 100 });

		std::shared_ptr<Tutorial_Map> Object1 = CreateActor<Tutorial_Map>(-50);
		Object1->GetTransform()->SetLocalPosition(PlayMapPosition + float4{ 0, 0, 50 });

		std::shared_ptr<Tutorial_BackLayer> Object2 = CreateActor<Tutorial_BackLayer>(-10);
		Object2->GetTransform()->SetLocalPosition({ 640 , PlayMapHeight_Half - 100, 10 });

		if (nullptr == ThisColMap)
		{
			ThisColMap = CreateActor<Tutorial_ColMap>(-30);
			ThisColMap->GetTransform()->SetLocalPosition(PlayMapPosition);
		}
	}
	// Actor
	{
		std::shared_ptr<PortalDoor> Object = CreateActor<PortalDoor>(-100);
		Object->GetTransform()->SetLocalPosition({ 5840, 150, 1 });
		Object->SetPortalValue(PortalValue::Overworld);
	}
	// GUI
	{
		if (nullptr == GUI)
		{
			GUI = GameEngineGUI::FindGUIWindowConvert<TransformGUI>("TransformGUI");
			GUI->SetTarget(PlayerObject->GetTransform());
			GUI->SetMainPalyer(PlayerObject);

			GUI->PlayerDebugRenderOn = std::bind(&TutorialLevel::PlayerDebugRenderOn, this);
			GUI->PlayerDebugRenderOff = std::bind(&TutorialLevel::PlayerDebugRenderOff, this);
			GUI->ColMapRenderOn = std::bind(&TutorialLevel::TutorialColMapOn, this);
			GUI->ColMapRenderOff = std::bind(&TutorialLevel::TutorialColMapOff, this);
		}
	}

	// 지울 것(테스트)
	{
		std::shared_ptr<TestPlatform> PlatformObject0 = CreateActor<TestPlatform>(-100);
		PlatformObject0->GetTransform()->SetLocalPosition({ 640 , PlayMapHeight_Half - 200, 1 });

		std::shared_ptr<TestPlatform> PlatformObject1 = CreateActor<TestPlatform>(-100);
		PlatformObject1->GetTransform()->SetLocalPosition({ 400 , PlayMapHeight_Half, 1 });

		std::shared_ptr<TestPlatform> PlatformObject2 = CreateActor<TestPlatform>(-100);
		PlatformObject2->GetTransform()->SetLocalPosition({ 640 , PlayMapHeight_Half + 100, 1 });

		std::shared_ptr<TestPlatform> PlatformObject3 = CreateActor<TestPlatform>(-100);
		PlatformObject3->GetTransform()->SetLocalPosition({ 900 , PlayMapHeight_Half + 100, 1 });

		std::shared_ptr<TestPlatform> PlatformObject4 = CreateActor<TestPlatform>(-100);
		PlatformObject4->GetTransform()->SetLocalPosition({ 900 , PlayMapHeight_Half + -200, 1 });

		std::shared_ptr<TestPlatform> PlatformObject5 = CreateActor<TestPlatform>(-100);
		PlatformObject5->GetTransform()->SetLocalPosition({ 400 , PlayMapHeight_Half - 200, 1 });
	}

	{
		//std::shared_ptr<Screen_FX> Object = CreateActor<Screen_FX>();
		//Object->GetTransform()->SetLocalPosition({ 640 , PlayMapHeight_Half - 100, -10 });
	}
}
void TutorialLevel::LevelChangeEnd()
{
}
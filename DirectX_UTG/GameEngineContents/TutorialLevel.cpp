#include "PrecompileHeader.h"
#include "TutorialLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Tutorial_BackGround.h"
#include "Tutorial_BackLayer.h"
#include "Tutorial_Map.h"
#include "Tutorial_ColMap.h"
#include "Player.h"

#include "TransformGUI.h"

TutorialLevel::TutorialLevel() 
{
}

TutorialLevel::~TutorialLevel() 
{
}

void TutorialLevel::Start()
{
	// 레벨 리소스 로드
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
	// 플레이어 리소스 로드
	//{
	//	GameEngineDirectory NewDir;
	//	NewDir.MoveParentToDirectory("CupHead_Resource");
	//	NewDir.Move("CupHead_Resource");
	//	NewDir.Move("Image");
	//	NewDir.Move("Character");
	//	NewDir.Move("CupHead");
	//	NewDir.Move("Ground");

	//	std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

	//	for (size_t i = 0; i < File.size(); i++)
	//	{
	//		GameEngineTexture::Load(File[i].GetFullPath());
	//	}
	//}
	// 디버그용 이미지 로드
	{
		

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
	GetMainCamera()->GetTransform()->SetLocalPosition({ 640, PlayMapHeight_Half - 100, -620.0f });

	// CreateActor
	// Background, Map
	{

		std::shared_ptr<Tutorial_BackGround> Object0 = CreateActor<Tutorial_BackGround>(-100);
		Object0->GetTransform()->SetLocalPosition({ 640 , PlayMapHeight_Half - 100, 100 });

		std::shared_ptr<Tutorial_Map> Object1 = CreateActor<Tutorial_Map>(-50);
		Object1->GetTransform()->SetLocalPosition(PlayMapPosition + float4{0, 0, 50});

		std::shared_ptr<Tutorial_BackLayer> Object2 = CreateActor<Tutorial_BackLayer>(-10);
		Object2->GetTransform()->SetLocalPosition({ 640 , PlayMapHeight_Half - 100, 10 });

		ThisColMap = CreateActor<Tutorial_ColMap>(-30);
		ThisColMap->GetTransform()->SetLocalPosition(PlayMapPosition);
	}
	// Character
	{
		PlayerObject = CreateActor<Player>(1);
		PlayerObject->GetTransform()->SetLocalPosition({ 300 , PlayMapHeight_Half, 1});
		PlayerObject->SetColMap(PlayMap, PixelCollision::Coordinate::Custom);
	}

	// GUI
	{
		GUI = GameEngineGUI::FindGUIWindowConvert<TransformGUI>("TransformGUI");
		GUI->SetTarget(PlayerObject->GetTransform());

		GUI->PlayerDebugRenderOn = std::bind(&TutorialLevel::PlayerDebugRenderOn, this);
		GUI->PlayerDebugRenderOff = std::bind(&TutorialLevel::PlayerDebugRenderOff, this);
		GUI->ColMapRenderOn = std::bind(&TutorialLevel::TutorialColMapOn, this);
		GUI->ColMapRenderOff = std::bind(&TutorialLevel::TutorialColMapOff, this);
	}
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

}
void TutorialLevel::LevelChangeEnd()
{

}
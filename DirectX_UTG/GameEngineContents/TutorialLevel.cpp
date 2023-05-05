#include "PrecompileHeader.h"
#include "TutorialLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Tutorial_BackGround.h"
#include "Tutorial_BackLayer.h"
#include "Tutorial_Map.h"
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
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("CH_Action");
		NewDir.Move("CHAc_Ground");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}
	// 디버그용 이미지 로드
	{
		
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("DebugImage");

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
	GetMainCamera()->GetTransform()->SetLocalPosition({ 300, PlayMapHeight_Half - 100, -620.0f });

	// CreateActor
	// Background, Map
	{
		std::shared_ptr<Tutorial_BackLayer> Object0 = CreateActor<Tutorial_BackLayer>(-10);
		Object0->GetTransform()->SetLocalPosition({ 300 , PlayMapHeight_Half - 100, 1 });
		std::shared_ptr<Tutorial_BackGround> Object1 = CreateActor<Tutorial_BackGround>(-100);
		Object1->GetTransform()->SetLocalPosition({ 300 , PlayMapHeight_Half - 100, 1 });

		std::shared_ptr<Tutorial_Map> Object2 = CreateActor<Tutorial_Map>(-50);
		Object2->GetTransform()->SetLocalPosition(PlayMapPosition);
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

void TutorialLevel::Update(float _DeltaTime)
{

}

void TutorialLevel::LevelChangeStart()
{

}
void TutorialLevel::LevelChangeEnd()
{

}
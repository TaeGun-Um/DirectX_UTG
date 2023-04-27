#include "PrecompileHeader.h"
#include "TutorialLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Tutorial_BackLayer.h"
#include "Player.h"

TutorialLevel::TutorialLevel() 
{
}

TutorialLevel::~TutorialLevel() 
{
}

void TutorialLevel::Start()
{
	// 리소스 로드
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
	// 임시 플레이어 이미지 로드
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("CH_Action");
		NewDir.Move("CHAc_Ground");
		NewDir.Move("CHAc_Ground_Idle");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });

	// CreateActor
	std::shared_ptr<Tutorial_BackLayer> Object1 = CreateActor<Tutorial_BackLayer>("Tutorial_BackLayer");
	//Object1->GetTransform()->AddWorldPosition({ 0, -3 });

	std::shared_ptr<Player> Object2 = CreateActor<Player>("Player");
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
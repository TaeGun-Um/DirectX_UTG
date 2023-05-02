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

TutorialLevel::TutorialLevel() 
{
}

TutorialLevel::~TutorialLevel() 
{
}

void TutorialLevel::Start()
{
	// ���ҽ� �ε�
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
	// �ӽ� �÷��̾� �̹��� �ε�
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

	// ī�޶� ����
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });

	// CreateActor
	// Background, Map
	{
		std::shared_ptr<Tutorial_BackLayer> Object = CreateActor<Tutorial_BackLayer>(-10);
		std::shared_ptr<Tutorial_Map> Object2 = CreateActor<Tutorial_Map>(-50);
		std::shared_ptr<Tutorial_BackGround> Object1 = CreateActor<Tutorial_BackGround>(-100);
		
		Object2->GetTransform()->AddWorldPosition({ 2500, 100 });
	}
	// Character
	{
		std::shared_ptr<Player> Object3 = CreateActor<Player>(1);
	}
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
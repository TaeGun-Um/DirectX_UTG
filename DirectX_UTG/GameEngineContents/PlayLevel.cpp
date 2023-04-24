#include "PrecompileHeader.h"
#include "PlayLevel.h"
#include "Player.h"
#include "TestObject.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}


void PlayLevel::Start()
{
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("Overworld_NPCs");
		NewDir.Move("Axeman");
		NewDir.Move("Axeman_Idle");
		
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}

		int a = 0;

	}

	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	{
		std::shared_ptr<TestObject> Object = CreateActor<TestObject>();
		Object->GetTransform()->SetLocalScale({ 1000, 1000, 1000 });
		Object->GetTransform()->SetLocalPosition({ 0, 0, 100.0f });
	}

	{
		std::shared_ptr<Player> Object = CreateActor<Player>("Player");
	}

}
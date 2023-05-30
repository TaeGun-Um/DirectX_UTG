#include "PrecompileHeader.h"
#include "DragonLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "GrimMatchstick.h"
#include "TestActor.h"

DragonLevel::DragonLevel() 
{
}

DragonLevel::~DragonLevel() 
{
}

void DragonLevel::Start()
{

}
void DragonLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("NextLevel"))
	{
		GameEngineCore::ChangeLevel("MouseLevel");
	}
}

//void DragonLevel::LevelChangeStart()
//{
//	// 카메라 세팅
//	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
//	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });
//	GetMainCamera()->SetSortType(0, SortType::ZSort);
//
//	{
//		if (nullptr == DragonObject)
//		{
//			DragonObject = CreateActor<GrimMatchstick>();
//		}
//	}
//
//}
//
//void DragonLevel::LevelChangeEnd()
//{
//	if (nullptr != GameEngineSprite::Find("Dragon_Idle"))
//	{
//		GameEngineDirectory NewDir;
//		NewDir.MoveParentToDirectory("CupHead_Resource");
//		NewDir.Move("CupHead_Resource");
//		NewDir.Move("Image");
//		NewDir.Move("Character");
//		NewDir.Move("2_Grim_Matchstick");
//		NewDir.Move("Phase1");
//		NewDir.Move("Dragon_Idle");
//
//		std::vector<GameEngineFile> AllFile = NewDir.GetAllFile({ ".png" });
//
//		for (size_t i = 0; i < AllFile.size(); i++)
//		{
//			GameEngineFile& File = AllFile[i];
//
//			std::filesystem::path Path = File.GetFullPath();
//
//			std::string Target = Path.filename().string();
//
//			GameEngineTexture::UnLoad(Target);
//		}
//
//		// GameEngineSprite::TargetSpriteRelease("Ribby_Idle");
//	}
//}

void DragonLevel::LevelChangeStart()
{
	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });
	GetMainCamera()->SetSortType(0, SortType::ZSort);

	{
		if (nullptr == DragonObject)
		{
			TestActorObject = CreateActor<TestActor>();
		}
	}

}

void DragonLevel::LevelChangeEnd()
{
	if (nullptr != GameEngineTexture::Find("dragon_idle_0001.png"))
	{
		GameEngineTexture::UnLoad("dragon_idle_0001.png");
	}
}
#include "PrecompileHeader.h"
#include "FrogLevel.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>

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
	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });
	GetMainCamera()->SetSortType(0, SortType::ZSort);

	if (nullptr == GameEngineSprite::Find("BlueBox"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("DebugImage");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	if (nullptr == GameEngineSprite::Find("BlueBox"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}
}
void FrogLevel::LevelChangeEnd()
{
	GameEngineSprite::ResourcesClear();
	GameEngineTexture::ResourcesClear();
}
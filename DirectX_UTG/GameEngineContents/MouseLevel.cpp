#include "PrecompileHeader.h"
#include "MouseLevel.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>

MouseLevel::MouseLevel() 
{
}

MouseLevel::~MouseLevel() 
{
}

void MouseLevel::Start()
{

}
void MouseLevel::Update(float _DeltaTime)
{

}

void MouseLevel::LevelChangeStart()
{
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
}
void MouseLevel::LevelChangeEnd()
{
	GameEngineTexture::ResourcesClear();
	GameEngineSprite::ResourcesClear();
}
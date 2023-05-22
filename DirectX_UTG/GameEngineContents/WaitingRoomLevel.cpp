#include "PrecompileHeader.h"
#include "WaitingRoomLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCamera.h>

WaitingRoomLevel::WaitingRoomLevel() 
{
}

WaitingRoomLevel::~WaitingRoomLevel() 
{
}

void WaitingRoomLevel::Start()
{
}
void WaitingRoomLevel::Update(float _DeltaTime)
{

}

void WaitingRoomLevel::LevelChangeStart()
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

	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });

	// CreateActor
	//std::shared_ptr<BookRender> Object1 = CreateActor<BookRender>("BookRender");
	//Object1->GetTransform()->AddWorldPosition({ 0, -3 });
}
void WaitingRoomLevel::LevelChangeEnd()
{
	GameEngineSprite::ResourcesClear();
	GameEngineTexture::ResourcesClear();
}
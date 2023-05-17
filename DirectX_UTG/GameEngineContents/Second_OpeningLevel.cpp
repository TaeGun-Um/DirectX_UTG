#include "PrecompileHeader.h"
#include "Second_OpeningLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "WaitingRoomLevel.h"
#include "TutorialLevel.h"

#include "BookRender.h"

Second_OpeningLevel::Second_OpeningLevel() 
{
}

Second_OpeningLevel::~Second_OpeningLevel()
{
}

void Second_OpeningLevel::Start()
{
	// 리소스 로드
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Opening2");

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
	std::shared_ptr<BookRender> Object1 = CreateActor<BookRender>();
	Object1->GetTransform()->AddWorldPosition({ 0, -3 });
}
void Second_OpeningLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("Action"))
	{
		//GameEngineCore::CreateLevel<WaitingRoomLevel>();
		//GameEngineCore::ChangeLevel("WaitingRoomLevel");
		GameEngineCore::CreateLevel<TutorialLevel>();
		GameEngineCore::ChangeLevel("TutorialLevel");
	}
}

void Second_OpeningLevel::LevelChangeStart()
{

}
void Second_OpeningLevel::LevelChangeEnd()
{

}
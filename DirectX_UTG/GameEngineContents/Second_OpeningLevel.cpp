#include "PrecompileHeader.h"
#include "Second_OpeningLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "WaitingRoomLevel.h"
#include "TutorialLevel.h"

#include "RoundBlackBox.h"
#include "Screen_FX.h"
#include "BookRender.h"
#include "Loading.h"

Second_OpeningLevel::Second_OpeningLevel() 
{
}

Second_OpeningLevel::~Second_OpeningLevel()
{
}

void Second_OpeningLevel::Start()
{

}
void Second_OpeningLevel::Update(float _DeltaTime)
{
	if (true == BookRender::GetBookAnimationIsEnd() && false == IsEnd)
	{
		IsEnd = true;
		BlackBoxPtr->BoxSettingReset();
		BlackBoxPtr->SetEnter();
	}
	
	if (true == BlackBoxPtr->GetIsEnd() && true == IsEnd)
	{
		LoadingPtr->SetLoadingPtrOn();
		GameEngineCore::ChangeLevel("WaitingRoomLevel");
	}
}

void Second_OpeningLevel::LevelChangeStart()
{
	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });

	// CreateActor
	{
		BookRenderObject = CreateActor<BookRender>();
		BookRenderObject->GetTransform()->AddWorldPosition({ 0, -3 });
	}
	{
		BlackBoxPtr = CreateActor<RoundBlackBox>();
		BlackBoxPtr->SetExit();
	}

	if (nullptr == LoadingPtr)
	{
		LoadingPtr = CreateActor<Loading>();
		LoadingPtr->SetLoadingPtrOff();
	}
}
void Second_OpeningLevel::LevelChangeEnd()
{
	if (nullptr != GameEngineSprite::Find("Page_01"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Opening2");

		std::vector<GameEngineFile> AllFile = NewDir.GetAllFile({ ".png" });

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineFile& File = AllFile[i];

			std::filesystem::path Path = File.GetFullPath();

			std::string Target = Path.filename().string();

			GameEngineTexture::UnLoad(Target);
		}
	}

	BookRenderObject = nullptr;
}
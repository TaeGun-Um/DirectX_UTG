#include "PrecompileHeader.h"
#include "First_OpeningLevel.h"

#include <filesystem>

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Second_OpeningLevel.h"

#include "TitleMenu.h"
#include "RoundBlackBox.h"
#include "Screen_FX.h"
#include "MDHR_Logo.h"
#include "Title_Background.h"
#include "Loading.h"

First_OpeningLevel* First_OpeningLevel::First_OpeningLevelPtr = nullptr;

First_OpeningLevel::First_OpeningLevel() 
{
}

First_OpeningLevel::~First_OpeningLevel() 
{
}

void First_OpeningLevel::Start()
{
	First_OpeningLevelPtr = this;

	if (false == GameEngineInput::IsKey("NextLevel"))
	{
		GameEngineInput::CreateKey("NextLevel", 'P');
		GameEngineInput::CreateKey("PrevLevel", 'O');
	}
}
void First_OpeningLevel::Update(float _DeltaTime)
{
	if (true == MDHR_Logo::LogoPtr->GetLogoAnimationIsEnd())
	{
		AccessTime += _DeltaTime;
	}

	if (true == GameEngineInput::IsAnyKey() && AccessTime >= 1.0f)
	{
		NextStep1 = true;

	}

	if (true == NextStep1 && 1 == NextStep1Count)
	{
		NextStep1Count = 0;
		BlackBoxPtr->SetEnter();
	}

	if (true == BlackBoxPtr->GetIsEnd() && 1 == NextStep2Count)
	{
		BackgroundObject->Off();
		TitleMenuObject->On();
		NextStep2Count = 0;
		BlackBoxPtr->SetExit();

		TitleMove = true;
	}

	if (true == TitleMenuObject->GetIsEnd() && false == EndStep)
	{
		EndStep = true;
		BlackBoxPtr->BoxSettingReset();
		BlackBoxPtr->SetEnter();
	}

	if (true == BlackBoxPtr->GetIsEnd() && true == EndStep)
	{
		GameEngineWindow::AppOff();
	}

	if (true == TitleMenuObject->GetIsStart() && false == StartStep)
	{
		StartStep = true;
		BlackBoxPtr->BoxSettingReset();
		BlackBoxPtr->SetEnter();
	}

	if (true == BlackBoxPtr->GetIsEnd() && true == StartStep)
	{
		LoadingPtr->SetLoadingPtrOn();
		GameEngineCore::ChangeLevel("Second_OpeningLevel");
	}

	//if (true == GameEngineInput::IsDown("NextLevel"))
	//{
	//	GameEngineCore::ChangeLevel("WaitingRoomLevel");
	//}
}

void First_OpeningLevel::LevelChangeStart()
{
	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });

	// CreateActor
	{
		TitleMenuObject = CreateActor<TitleMenu>();
		TitleMenuObject->Off();
	}
	if (nullptr == BackgroundObject)
	{
		BackgroundObject = CreateActor<Title_Background>();
		BackgroundObject->GetTransform()->AddWorldPosition({ 0, -3 });
	}
	{
		std::shared_ptr<MDHR_Logo> Object = CreateActor<MDHR_Logo>();
	}
	{
		BlackBoxPtr = CreateActor<RoundBlackBox>();
	}

	if (nullptr == LoadingPtr)
	{
		LoadingPtr = CreateActor<Loading>();
		LoadingPtr->SetLoadingPtrOff();
	}
}
void First_OpeningLevel::LevelChangeEnd()
{
	//BlackBoxPtr->BoxSettingReset();

	if (nullptr != GameEngineSprite::Find("Cuphead_and_Mugman"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Opening1");
		NewDir.Move("Cuphead_and_Mugman");

		std::vector<GameEngineFile> AllFile = NewDir.GetAllFile({ ".png" });

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineFile& File = AllFile[i];

			std::filesystem::path Path = File.GetFullPath();

			std::string Target = Path.filename().string();

			GameEngineTexture::UnLoad(Target);
		}
	}

	if (nullptr != GameEngineTexture::Find("PressAnyButton.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Opening1");
		NewDir.Move("Title");

		GameEngineTexture::UnLoad("PressAnyButton.png");
		GameEngineTexture::UnLoad("Title_Background.png");
	}

	if (nullptr != GameEngineSprite::Find("MDHR_Logo.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Opening1");
		NewDir.Move("MDHR_Logo");

		GameEngineTexture::UnLoad("MDHR_Logo.png");
	}

	if (nullptr != GameEngineTexture::Find("cuphead_startscreen.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Opening1");
		NewDir.Move("Title");

		GameEngineTexture::UnLoad("PressAnyButton.png");
		GameEngineTexture::UnLoad("Title_Background.png");
	}

	TitleMenuObject = nullptr;
	BackgroundObject = nullptr;
}
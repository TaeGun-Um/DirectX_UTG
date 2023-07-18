#include "PrecompileHeader.h"
#include "First_OpeningLevel.h"

#include <filesystem>

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "LoadingLevel.h"
#include "Second_OpeningLevel.h"

#include "TitleMenu.h"
#include "RoundBlackBox.h"
#include "Screen_FX.h"
#include "MDHR_Logo.h"
#include "Title_Background.h"
#include "Opening_BlackBox.h"

#include <GameEngineCore/BlurEffect.h>
#include "OldFilm.h"

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
	GetLastTarget()->CreateEffect<BlurEffect>();
	GetLastTarget()->CreateEffect<OldFilm>();

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Sound");
		NewDir.Move("OpeningMenu");

		GameEngineSound::Load(NewDir.GetPlusFileName("Optical_Start_001.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("MDHR_LOGO_STING.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("Menu_Equipment_Move.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("Menu_Move.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("Menu_Category_Select.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("Don't Deal with the Devil.mp3").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("Don't Deal with the Devil (Instrumental).mp3").GetFullPath());
	}
	
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Sound");
		NewDir.Move("UISFX");

		GameEngineSound::Load(NewDir.GetPlusFileName("WorldMap_LevelSelect_BubbleAppear.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("WorldMap_LevelSelect_BubbleDisappear.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("WorldMap_LevelSelect_DiffucultySettings_Appear.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("WorldMap_LevelSelect_DiffucultySettings_Hover.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("WorldMap_LevelSelect_StartLevel.wav").GetFullPath());
	}
}
void First_OpeningLevel::Update(float _DeltaTime)
{
	if (false == OpeningBlackBoxObject->GetIsEnd())
	{
		return;
	}
	
	if (true == GameEngineInput::IsDown("NextLevel"))
	{
		GameEngineCore::ChangeLevel("Second_OpeningLevel");
	}

	if (true == MDHR_Logo::LogoPtr->GetLogoAnimationIsEnd())
	{
		if (false == IsBGMOn)
		{
			IsBGMOn = true;
			BGMPlayer = GameEngineSound::Play("Don't Deal with the Devil.mp3");
		}

		AccessTime += _DeltaTime;
	}

	if (true == IsBGMOn)
	{
		bool playing = false;

		BGMPlayer.isPlaying(&playing);
		
		if (false == playing && false == IsBGMLoopOn)
		{
			IsBGMLoopOn = true;
			BGMPlayer = GameEngineSound::Play("Don't Deal with the Devil (Instrumental).mp3");
			BGMPlayer.SetLoop(100);
		}
	}

	if (true == GameEngineInput::IsAnyKey() && AccessTime >= 1.0f)
	{
		NextStep1 = true;
	}

	if (true == NextStep1 && 1 == NextStep1Count)
	{
		NextStep1Count = 0;

		EffectPlayer = GameEngineSound::Play("WorldMap_LevelSelect_DiffucultySettings_Appear.wav");

		BlackBoxPtr->BoxSettingReset();
		BlackBoxPtr->SetEnter();
	}

	if (true == BlackBoxPtr->GetIsEnd() && 1 == NextStep2Count)
	{
		BackgroundObject->Off();
		TitleMenuObject->On();
		NextStep2Count = 0;
		BlackBoxPtr->BoxSettingReset();
		BlackBoxPtr->SetExit();
	}

	if (true == BlackBoxPtr->GetIsEnd() && 0 == NextStep2Count)
	{
		TitleMove = true;
	}

	if (true == TitleMenuObject->GetIsEnd() && false == EndStep)
	{
		EndStep = true;

		BGMPlayer.Stop();
		EffectPlayer = GameEngineSound::Play("Menu_Category_Select.wav");

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

		BGMPlayer.Stop();
		EffectPlayer = GameEngineSound::Play("WorldMap_LevelSelect_StartLevel.wav");

		BlackBoxPtr->BoxSettingReset();
		BlackBoxPtr->SetEnter();
	}

	if (true == BlackBoxPtr->GetIsEnd() && true == StartStep)
	{
		LoadingLevel::LoadingLevelPtr->SetLevelState(LevelValue::Second_OpeningLevel);
		GameEngineCore::ChangeLevel("LoadingLevel");
	}
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
		if (nullptr == MDHR_LogoObject)
		{
			MDHR_LogoObject = CreateActor<MDHR_Logo>();
			MDHR_LogoObject->Off();
		}
	}
	{
		if (nullptr == OpeningBlackBoxObject)
		{
			OpeningBlackBoxObject = CreateActor<Opening_BlackBox>();
		}
	}
	{
		BlackBoxPtr = CreateActor<RoundBlackBox>();
	}

	ReLoadSetting();
}
void First_OpeningLevel::LevelChangeEnd()
{
	if (true == IsBGMOn)
	{
		bool playing = false;

		BGMPlayer.isPlaying(&playing);

		if (true == playing)
		{
			BGMPlayer.Stop();
		}
	}

	if (nullptr != GameEngineSprite::Find("Cuphead_and_Mugman"))
	{
		GameEngineSprite::UnLoad("Cuphead_and_Mugman");
	}

	if (nullptr != GameEngineTexture::Find("PressAnyButton.png"))
	{
		GameEngineTexture::UnLoad("PressAnyButton.png");
		GameEngineTexture::UnLoad("Title_Background.png");
	}

	if (nullptr != GameEngineSprite::Find("MDHR_Logo.png"))
	{
		GameEngineSprite::UnLoad("MDHR_Logo.png");
	}

	if (nullptr != GameEngineTexture::Find("cuphead_startscreen.png"))
	{
		GameEngineTexture::UnLoad("cuphead_startscreen.png");
		GameEngineTexture::UnLoad("START.png");
		GameEngineTexture::UnLoad("EXIT.png");
	}

	{
		IsBGMOn = false;
		IsBGMLoopOn = false;
		NextStep1 = false;
		NextStep1Count = 1;
		NextStep2 = false;
		NextStep2Count = 1;
		TitleMove = false;
		EndStep = false;
		StartStep = false;
		AccessTime = 0.0f;
		BlackBoxPtr->BoxSettingReset();

		MDHR_LogoObject->Death();
		OpeningBlackBoxObject->Death();
		MDHR_LogoObject = nullptr;
		OpeningBlackBoxObject = nullptr;
	}
}

void First_OpeningLevel::ReLoadSetting()
{
	if (nullptr != GameEngineSprite::Find("Cuphead_and_Mugman"))
	{
		GameEngineSprite::ReLoad("Cuphead_and_Mugman");
	}

	if (nullptr != GameEngineTexture::Find("PressAnyButton.png"))
	{
		GameEngineTexture::ReLoad("PressAnyButton.png");
		GameEngineTexture::ReLoad("Title_Background.png");
	}

	if (nullptr != GameEngineSprite::Find("MDHR_Logo.png"))
	{
		GameEngineSprite::ReLoad("MDHR_Logo.png");
	}

	if (nullptr != GameEngineTexture::Find("cuphead_startscreen.png"))
	{
		GameEngineTexture::ReLoad("cuphead_startscreen.png");
		GameEngineTexture::ReLoad("START.png");
		GameEngineTexture::ReLoad("EXIT.png");
	}
}
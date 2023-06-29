#include "PrecompileHeader.h"
#include "Second_OpeningLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "LoadingLevel.h"
#include "WaitingRoomLevel.h"
#include "TutorialLevel.h"

#include "RoundBlackBox.h"
#include "Screen_FX.h"
#include "BookRender.h"

#include <GameEngineCore/BlurEffect.h>
#include "OldFilm.h"

Second_OpeningLevel::Second_OpeningLevel() 
{
}

Second_OpeningLevel::~Second_OpeningLevel()
{
}

void Second_OpeningLevel::Start()
{
	GetLastTarget()->CreateEffect<BlurEffect>();
	GetLastTarget()->CreateEffect<OldFilm>();
}

void Second_OpeningLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("PrevLevel"))
	{
		GameEngineCore::ChangeLevel("First_OpeningLevel");
	}
	if (true == GameEngineInput::IsDown("NextLevel"))
	{
		GameEngineCore::ChangeLevel("WaitingRoomLevel");
	}

	if (true == BookRender::GetBookAnimationIsEnd() && false == IsEnd)
	{
		IsEnd = true;
		BlackBoxPtr->BoxSettingReset();
		BlackBoxPtr->SetEnter();
	}
	
	if (true == BlackBoxPtr->GetIsEnd() && true == IsEnd)
	{
		//GameEngineCore::ChangeLevel("WaitingRoomLevel");
		LoadingLevel::LoadingLevelPtr->SetLevelState(LevelValue::WaitingRoomLevel);
		GameEngineCore::ChangeLevel("LoadingLevel");
	}

	ReLoadSetting();
}

void Second_OpeningLevel::LevelChangeStart()
{
	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });

	{
		if (nullptr == BookRenderObject)
		{
			BookRenderObject = CreateActor<BookRender>();
		}
		
		BookRenderObject->GetTransform()->AddWorldPosition({ 0, -3 });
		BookRenderObject->BookRenderEndReset();
	}
	{
		if (nullptr == BlackBoxPtr)
		{
			BlackBoxPtr = CreateActor<RoundBlackBox>();
		}
		
		BlackBoxPtr->BoxSettingReset();
		BlackBoxPtr->SetExit();
	}
}
void Second_OpeningLevel::LevelChangeEnd()
{
	if (nullptr != GameEngineSprite::Find("Page_01"))
	{
		GameEngineSprite::UnLoad("Page_01");
		GameEngineSprite::UnLoad("Page_01-02");
		GameEngineSprite::UnLoad("Page_02-03");
		GameEngineSprite::UnLoad("Page_03-04");
		GameEngineSprite::UnLoad("Page_04-05");
		GameEngineSprite::UnLoad("Page_05-06");
		GameEngineSprite::UnLoad("Page_06-07");
		GameEngineSprite::UnLoad("Page_07-08");
		GameEngineSprite::UnLoad("Page_08-09");
		GameEngineSprite::UnLoad("Page_09-10");
		GameEngineSprite::UnLoad("Page_10-11");
	}

	if (nullptr != GameEngineTexture::Find("Arrow"))
	{
		GameEngineSprite::UnLoad("Arrow");
	}

	{
		BlackBoxPtr->BoxSettingReset();
		IsEnd = false;
	}
}

void Second_OpeningLevel::ReLoadSetting()
{
	if (nullptr != GameEngineSprite::Find("Page_01"))
	{
		GameEngineSprite::ReLoad("Page_01");
		GameEngineSprite::ReLoad("Page_01-02");
		GameEngineSprite::ReLoad("Page_02-03");
		GameEngineSprite::ReLoad("Page_03-04");
		GameEngineSprite::ReLoad("Page_04-05");
		GameEngineSprite::ReLoad("Page_05-06");
		GameEngineSprite::ReLoad("Page_06-07");
		GameEngineSprite::ReLoad("Page_07-08");
		GameEngineSprite::ReLoad("Page_08-09");
		GameEngineSprite::ReLoad("Page_09-10");
		GameEngineSprite::ReLoad("Page_10-11");
	}

	if (nullptr != GameEngineTexture::Find("Arrow"))
	{
		GameEngineSprite::ReLoad("Arrow");
	}
}
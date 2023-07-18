#include "PrecompileHeader.h"
#include "EndingLevel.h"

#include "BookEndRender.h"
#include "LoadingLevel.h"
#include "RoundBlackBox.h"

#include <GameEngineCore/BlurEffect.h>
#include "OldFilm.h"

EndingLevel::EndingLevel() 
{
}

EndingLevel::~EndingLevel() 
{
}

void EndingLevel::Start()
{
	GetLastTarget()->CreateEffect<BlurEffect>();
	GetLastTarget()->CreateEffect<OldFilm>();

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Sound");
		NewDir.Move("Book_Cutscene");

		GameEngineSound::Load(NewDir.GetPlusFileName("Winner Takes All.mp3").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("outro_cheering.wav").GetFullPath());
	}
}
void EndingLevel::Update(float _DeltaTime)
{
	if (false == IsBGMOn)
	{
		IsBGMOn = true;
		BGMPlayer = GameEngineSound::Play("Winner Takes All.mp3");
		BGMPlayer.SetLoop(100);
	}

	if (true == BookEndRender::GetBookAnimationIsEnd() && false == IsEnd)
	{
		IsEnd = true;

		BGMPlayer.Stop();
		EffectPlayer = GameEngineSound::Play("WorldMap_LevelSelect_DiffucultySettings_Appear.wav");

		BlackBoxPtr->BoxSettingReset();
		BlackBoxPtr->SetEnter();
	}

	if (true == BlackBoxPtr->GetIsEnd() && true == IsEnd)
	{
		LoadingLevel::LoadingLevelPtr->SetLevelState(LevelValue::First_OpeningLevel);
		GameEngineCore::ChangeLevel("LoadingLevel");
	}

	ReLoadSetting();
}

void EndingLevel::LevelChangeStart()
{
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });

	{
		if (nullptr == BookRenderObject)
		{
			BookRenderObject = CreateActor<BookEndRender>();
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

void EndingLevel::LevelChangeEnd()
{
	if (nullptr != GameEngineSprite::Find("Page_12-13"))
	{
		GameEngineSprite::UnLoad("Page_12-13");
		GameEngineSprite::UnLoad("Page_13-14");
		GameEngineSprite::UnLoad("Page_14-15");
		GameEngineSprite::UnLoad("Page_15-16");
		GameEngineSprite::UnLoad("Page_16-17");
		GameEngineSprite::UnLoad("Page_17-18");
		GameEngineSprite::UnLoad("Page_18-End");
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

void EndingLevel::ReLoadSetting()
{
	if (nullptr != GameEngineSprite::Find("Page_12-13"))
	{
		GameEngineSprite::ReLoad("Page_12-13");
		GameEngineSprite::ReLoad("Page_13-14");
		GameEngineSprite::ReLoad("Page_14-15");
		GameEngineSprite::ReLoad("Page_15-16");
		GameEngineSprite::ReLoad("Page_16-17");
		GameEngineSprite::ReLoad("Page_17-18");
		GameEngineSprite::ReLoad("Page_18-End");
	}

	if (nullptr != GameEngineTexture::Find("Arrow"))
	{
		GameEngineSprite::ReLoad("Arrow");
	}
}
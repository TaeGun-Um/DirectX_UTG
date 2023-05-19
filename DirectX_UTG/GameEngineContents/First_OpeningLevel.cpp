#include "PrecompileHeader.h"
#include "First_OpeningLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Second_OpeningLevel.h"

#include "Screen_FX.h"
#include "MDHR_Logo.h"
#include "Title_Background.h"
#include "Loading.h"

First_OpeningLevel::First_OpeningLevel() 
{
}

First_OpeningLevel::~First_OpeningLevel() 
{
}

void First_OpeningLevel::Start()
{
}
void First_OpeningLevel::Update(float _DeltaTime)
{
	if (true == MDHR_Logo::LogoPtr->GetLogoAnimationIsEnd())
	{
		AccessTime += _DeltaTime;
	}

	if (true == GameEngineInput::IsAnyKey() && AccessTime >= 1.0f)
	{
		LoadingPtr->SetLoadingPtrOn();
		GameEngineCore::ChangeLevel("Second_OpeningLevel");
	}
}

void First_OpeningLevel::LevelChangeStart()
{
	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });

	//std::shared_ptr<Screen_FX> Object2 = CreateActor<Screen_FX>();
	
	// CreateActor
	std::shared_ptr<Title_Background> Object1 = CreateActor<Title_Background>();
	std::shared_ptr<MDHR_Logo> Object0 = CreateActor<MDHR_Logo>();
	Object1->GetTransform()->AddWorldPosition({ 0, -3 });
	

	LoadingPtr = CreateActor<Loading>();
	LoadingPtr->SetLoadingPtrOff();
}
void First_OpeningLevel::LevelChangeEnd()
{
}
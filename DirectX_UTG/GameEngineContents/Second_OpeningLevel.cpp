#include "PrecompileHeader.h"
#include "Second_OpeningLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "WaitingRoomLevel.h"
#include "TutorialLevel.h"

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
	if (true == BookRender::GetBookAnimationIsEnd())
	{
		LoadingPtr->SetLoadingPtrOn();
		GameEngineCore::ChangeLevel("TutorialLevel");
	}
}

void Second_OpeningLevel::LevelChangeStart()
{
	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });

	//std::shared_ptr<Screen_FX> Object2 = CreateActor<Screen_FX>();
	
	// CreateActor
	std::shared_ptr<BookRender> Object1 = CreateActor<BookRender>();
	Object1->GetTransform()->AddWorldPosition({ 0, -3 });

	LoadingPtr = CreateActor<Loading>();
	LoadingPtr->SetLoadingPtrOff();
}
void Second_OpeningLevel::LevelChangeEnd()
{
}
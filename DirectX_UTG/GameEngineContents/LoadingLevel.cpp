#include "PrecompileHeader.h"
#include "LoadingLevel.h"

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCamera.h>

#include <GameEngineCore/BlurEffect.h>
#include "OldFilm.h"

#include "Loading.h"

LoadingLevel* LoadingLevel::LoadingLevelPtr = nullptr;

LoadingLevel::LoadingLevel() 
{
}

LoadingLevel::~LoadingLevel() 
{
}

void LoadingLevel::Start()
{
	LoadingLevelPtr = this;
	GetLastTarget()->CreateEffect<BlurEffect>();
	GetLastTarget()->CreateEffect<OldFilm>();
}

void LoadingLevel::Update(float _DeltaTime)
{
	EndTime += _DeltaTime;

	if (EndTime >= 5.0f)
	{
		LoadingObject->SetOutro();
	}

	if (true == LoadingObject->GetIsEnd())
	{
		int a = 0;
	}
}

void LoadingLevel::LevelChangeStart()
{
	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });

	// CreateActor
	if (nullptr == LoadingObject)
	{
		LoadingObject = CreateActor<Loading>();
		LoadingObject->GetTransform()->SetLocalPosition({ 0 , 0, -10.0f });
		LoadingObject->SetStart();
	}
	
}

void LoadingLevel::LevelChangeEnd()
{
	LoadingObject->Death();
	LoadingObject = nullptr;
}

void LoadingLevel::LevelChange()
{
	switch (LevelState)
	{
	case LevelValue::First_OpeningLevel:
		GameEngineCore::ChangeLevel("First_OpeningLevel");
		break;
	case LevelValue::Second_OpeningLevel:
		GameEngineCore::ChangeLevel("Second_OpeningLevel");
		break;
	case LevelValue::WaitingRoomLevel:
		GameEngineCore::ChangeLevel("WaitingRoomLevel");
		break;
	case LevelValue::TutorialLevel:
		GameEngineCore::ChangeLevel("TutorialLevel");
		break;
	case LevelValue::OverworldLevel:
		GameEngineCore::ChangeLevel("OverworldLevel");
		break;
	case LevelValue::FrogLevel:
		GameEngineCore::ChangeLevel("FrogLevel");
		break;
	case LevelValue::DragonLevel:
		GameEngineCore::ChangeLevel("DragonLevel");
		break;
	case LevelValue::MouseLevel:
		GameEngineCore::ChangeLevel("MouseLevel");
		break;
	case LevelValue::EndingLevel:
		GameEngineCore::ChangeLevel("EndingLevel");
		break;
	default:
		break;
	}
}

void LoadingLevel::OpeningTexture()
{

} 

void LoadingLevel::WaitingTexture()
{

} 

void LoadingLevel::TutorialTexture()
{

}

void LoadingLevel::OverworldTexture()
{

}

void LoadingLevel::FrogTexture()
{

}

void LoadingLevel::MouseTexture()
{

}

void LoadingLevel::DragonTexture()
{

}

void LoadingLevel::EndingTexture()
{

}
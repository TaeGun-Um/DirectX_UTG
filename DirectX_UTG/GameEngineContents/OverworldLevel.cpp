#include "PrecompileHeader.h"
#include "OverworldLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Overworld_Map.h"
#include "Player_Overworld.h"

#include "Screen_FX.h"
#include "Loading.h"

OverworldLevel::OverworldLevel() 
{
}

OverworldLevel::~OverworldLevel() 
{
}

void OverworldLevel::Start()
{

}
void OverworldLevel::Update(float _DeltaTime)
{
}

void OverworldLevel::LevelChangeStart()
{
	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });

	// CreateActor
	// Background, Map
	{
		std::shared_ptr<Overworld_Map> Object = CreateActor<Overworld_Map>();
	}
	// Character
	if (nullptr == PlayerObject)
	{
		PlayerObject = CreateActor<Player_Overworld>(1);
	}
	{
		//std::shared_ptr<Screen_FX> Object2 = CreateActor<Screen_FX>();
	}

	LoadingPtr = CreateActor<Loading>();
	LoadingPtr->SetLoadingPtrOff();
}
void OverworldLevel::LevelChangeEnd()
{
	LoadingPtr->SetLoadingPtrOn();
}
#include "PlayLevel.h"
#include "Player.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{
	GetMainCamera()->GetTransform().SetLocalPosition({ 0, 0, -100.0f });

	std::shared_ptr<Player> NewPlayer = CreateActor<Player>("Player");
}
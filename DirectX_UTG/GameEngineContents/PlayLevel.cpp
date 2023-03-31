#include "PlayLevel.h"

#include "Player.h"
#include <GameEngineCore/GameEngineCamera.h>

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}


void PlayLevel::Loading()
{
	GetMainCamera()->GetTransform().SetLocalPosition({ 0, 0, -1000.0f });

	std::shared_ptr<Player> NewPlayer = CreateActor<Player>("Player");
}
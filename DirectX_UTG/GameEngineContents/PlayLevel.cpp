#include "PrecompileHeader.h"
#include "PlayLevel.h"

#include <GameEngineCore/GameEngineCamera.h>
#include "Player.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}


void PlayLevel::Start()
{
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	std::shared_ptr<Player> NewPlayer = CreateActor<Player>("Player");
}
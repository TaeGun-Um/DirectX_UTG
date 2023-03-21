#include "PlayLevel.h"
#include "Player.h"

#include <GameEnginePlatform/GameEngineInput.h>

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{
	std::shared_ptr<Player> NewPlayer = CreateActor<Player>("Player");

	if (false == GameEngineInput::IsKey("Q"))
	{
		GameEngineInput::CreateKey("Q", 'Q');
		GameEngineInput::CreateKey("W", 'W');
		GameEngineInput::CreateKey("E", 'E');
		GameEngineInput::CreateKey("R", 'R');
	}
}
#include "PlayLevel.h"
#include "Player.h"

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{
	std::shared_ptr<Player> NewPlayer = CreateActor<Player>("Player");
}
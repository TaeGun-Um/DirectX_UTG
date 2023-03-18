#include "ContentsCore.h"
#include <GameEngineCore\GameEngineCore.h>
#include "PlayLevel.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::GameStart()
{
	new int();

	GameEngineCore::CreateLevel<PlayLevel>();
	GameEngineCore::ChangeLevel("PlayLevel");
}

void ContentsCore::GameEnd()
{

}
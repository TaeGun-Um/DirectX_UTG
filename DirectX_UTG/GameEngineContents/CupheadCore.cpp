#include "PrecompileHeader.h"
#include "CupheadCore.h"

#include <GameEngineCore\GameEngineCore.h>

#include "First_OpeningLevel.h"
#include "Second_OpeningLevel.h"
#include "TutorialLevel.h"
#include "WaitingRoomLevel.h"
#include "OverworldLevel.h"
#include "FrogLevel.h"
#include "DragonLevel.h"
#include "MouseLevel.h"
#include "EndingLevel.h"

CupheadCore::CupheadCore()
{
}

CupheadCore::~CupheadCore()
{
}

void CupheadCore::GameStart()
{
	new int(); // ½Å·ÚÀÇ ¸¯

	ContentsKeyBind();
	ContentsResourcesLoad();
	ContentsResourcesCreate();

	GameEngineCore::CreateLevel<First_OpeningLevel>();
	GameEngineCore::CreateLevel<Second_OpeningLevel>();
	GameEngineCore::CreateLevel<WaitingRoomLevel>();
	GameEngineCore::CreateLevel<TutorialLevel>();
	GameEngineCore::CreateLevel<OverworldLevel>();
	GameEngineCore::CreateLevel<FrogLevel>();
	GameEngineCore::CreateLevel<DragonLevel>();
	GameEngineCore::CreateLevel<MouseLevel>();
	GameEngineCore::CreateLevel<EndingLevel>();

	GameEngineCore::ChangeLevel("WaitingRoomLevel");
}

void CupheadCore::GameEnd()
{

}

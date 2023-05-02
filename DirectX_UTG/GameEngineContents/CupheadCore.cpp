#include "PrecompileHeader.h"
#include "CupheadCore.h"

#include <GameEngineCore\GameEngineCore.h>

#include "TestLevel.h"
#include "First_OpeningLevel.h"
#include "TutorialLevel.h"

#include "WaitingRoomLevel.h"
#include "TutorialLevel.h"
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
	new int(); // 신뢰의 릭

	ContentsResourcesCreate();

	GameEngineCore::CreateLevel<TestLevel>();
	//GameEngineCore::CreateLevel<First_OpeningLevel>();
	//GameEngineCore::CreateLevel<TutorialLevel>();

	GameEngineCore::ChangeLevel("TestLevel");
}

void CupheadCore::GameEnd()
{

}

void CupheadCore::ContentsResourcesCreate()
{
	// 텍스처 로드만 각 레벨별로 하고 정리하는 습관을 들이세요.
}
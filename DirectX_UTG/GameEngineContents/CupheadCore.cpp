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
	new int(); // �ŷ��� ��

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
	// �ؽ�ó �ε常 �� �������� �ϰ� �����ϴ� ������ ���̼���.
}
#include "PrecompileHeader.h"
#include "CupheadCore.h"

#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineCore/GameEngineGUI.h>

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

#include "TransformGUI.h"

CupheadCore::CupheadCore()
{
}

CupheadCore::~CupheadCore()
{
}

void CupheadCore::GameStart()
{
	new int(); // �ŷ��� ��

	GameEngineGUI::GUIWindowCreate<TransformGUI>("TransformGUI");

	ContentsResourcesCreate();

	GameEngineCore::CreateLevel<TestLevel>();
	//GameEngineCore::CreateLevel<First_OpeningLevel>();
	//GameEngineCore::CreateLevel<TutorialLevel>();
	//GameEngineCore::CreateLevel<OverworldLevel>();

	GameEngineCore::ChangeLevel("TestLevel");
}

void CupheadCore::GameEnd()
{

}

void CupheadCore::ContentsResourcesCreate()
{
	// �ؽ�ó �ε常 �� �������� �ϰ� �����ϴ� ������ ���̼���.
}
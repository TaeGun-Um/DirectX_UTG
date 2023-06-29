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

#include "LoadingLevel.h"

CupheadCore::CupheadCore()
{
}

CupheadCore::~CupheadCore()
{
}

void CupheadCore::GameStart()
{
	new int(); // �ŷ��� ��

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

	GameEngineCore::CreateLevel<LoadingLevel>();

	GameEngineCore::ChangeLevel("LoadingLevel");
}

void CupheadCore::GameEnd()
{
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");

		if (0 == RemoveFontResourceA(NewDir.GetPlusFileName("CupheadFelix-Regular-merged.ttf").GetFullPath().data()))
		{
			MsgAssert("��Ʈ ������ �����߽��ϴ�.");
			return;
		}

		SendMessage(GameEngineWindow::GetHWnd(), WM_FONTCHANGE, NULL, NULL);
	}
}

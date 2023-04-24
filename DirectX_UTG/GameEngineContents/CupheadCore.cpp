#include "PrecompileHeader.h"
#include "CupheadCore.h"

#include <GameEngineCore\GameEngineCore.h>

#include "PlayLevel.h"

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

	GameEngineCore::CreateLevel<PlayLevel>();
	GameEngineCore::ChangeLevel("PlayLevel");
}

void CupheadCore::GameEnd()
{

}

void CupheadCore::ContentsResourcesCreate()
{
	// 텍스처 로드만 각 레벨별로 하고 정리하는 습관을 들이세요.
}
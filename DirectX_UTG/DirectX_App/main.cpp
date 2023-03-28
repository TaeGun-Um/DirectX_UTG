#include <Windows.h>
#include <GameEngineBase\GameEngineFile.h>
#include <GameEngineBase\GameEngineDirectory.h>
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineContents\ContentsCore.h>

#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContents.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineCore::Start(hInstance, ContentsCore::GameStart, ContentsCore::GameEnd);
}

// 특정한 물체의 크기 이동 회전 관련 기하 속성을 관리해주는 클래스 GameEngineTransform 생성
// 
// 직관적인게 좋기 때문에, 기하학 함수 호출 시 바~로 update를 적용해버린다.
// 고정된 오브젝트 만들땐 이게 좋음
// 값을 바꾸면 모든행렬 재계산이 되는 구조.
// 
// 
// 
// 
// 
// 
// 
// 
// 
//
//
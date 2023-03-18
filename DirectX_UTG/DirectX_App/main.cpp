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
	// 시작할 때,          핸들       함수 인스턴스(Start)      함수 인스턴스(End)
	GameEngineCore::Start(hInstance, ContentsCore::GameStart, ContentsCore::GameEnd);
}

// 엔진은 각 게임마다 다를 예정
// 무슨 게임을 만들지 모름
// 

// 
// 엔진과 컨텐츠를 main에서 이어준다.
// GameEngineCore에 pragma contents를 참조추가 해준다. Core가 lib를 모른다고 하기 때문에.
// 
// 나중에 가면 얘가 먼저 정리되야 얘가 지워질 수 있어같은 경우가 생길 수 있다.
// 프로그래머가 삭제 순서에 대해서 제어해줘야 해야 한다.
// 프로그래머가 정리를 잘 못했다면 레벨을 Sharedptr로 들어 있다면 레벨이 지워지지 않게 된다.
// End에서는 모든 레벨이 사라져야한다. 그래서 호출.
// 

// 
// changelevel : sharedptr은 자체적으로 dynamic cast가 있음. 그걸로 casting 후 리턴해주는 방식
// 
// emplace_back 내부에서 자기가 기본 생성자 가지고 있으면 만들어주는 것
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

// 공전 행렬은 이미 이동되어 있는 물체를 회전시키면 공전하게 된다.
// 
// 뷰행렬에 대해 적용받는 액터들은 카메라 회전 행렬의 역행렬을 곱해야 한다.
// 회전행렬은 이 역행렬을 쉽게 구할 수 있다.
// 
// TarnsPose() .. 전치행렬
// 회전행렬에 전치행렬을 곱하면 반대로 회전하는 값 행렬을 구할 수 있다.
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
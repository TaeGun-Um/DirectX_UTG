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
	float4x4 Proj;
	Proj.PerspectiveFovLH(60.0f, 1280.0f / 720.0f);

	float4 Test = { -500.0f, 0, 5000.0f };

	Test *= Proj;

	Test.x /= Test.w;
	Test.y /= Test.w;
	Test.z /= Test.w;

	GameEngineCore::Start(hInstance, ContentsCore::GameStart, ContentsCore::GameEnd);
}



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
// 
// 
// 
// 
// 
// 
// 
// 
// 
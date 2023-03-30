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

// ���� ����� �̹� �̵��Ǿ� �ִ� ��ü�� ȸ����Ű�� �����ϰ� �ȴ�.
// 
// ����Ŀ� ���� ����޴� ���͵��� ī�޶� ȸ�� ����� ������� ���ؾ� �Ѵ�.
// ȸ������� �� ������� ���� ���� �� �ִ�.
// 
// TarnsPose() .. ��ġ���
// ȸ����Ŀ� ��ġ����� ���ϸ� �ݴ�� ȸ���ϴ� �� ����� ���� �� �ִ�.
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
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
	// ������ ��,          �ڵ�       �Լ� �ν��Ͻ�(Start)      �Լ� �ν��Ͻ�(End)
	GameEngineCore::Start(hInstance, ContentsCore::GameStart, ContentsCore::GameEnd);
}

// ������ �� ���Ӹ��� �ٸ� ����
// ���� ������ ������ ��
// 

// 
// ������ �������� main���� �̾��ش�.
// GameEngineCore�� pragma contents�� �����߰� ���ش�. Core�� lib�� �𸥴ٰ� �ϱ� ������.
// 
// ���߿� ���� �갡 ���� �����Ǿ� �갡 ������ �� �־�� ��찡 ���� �� �ִ�.
// ���α׷��Ӱ� ���� ������ ���ؼ� ��������� �ؾ� �Ѵ�.
// ���α׷��Ӱ� ������ �� ���ߴٸ� ������ Sharedptr�� ��� �ִٸ� ������ �������� �ʰ� �ȴ�.
// End������ ��� ������ ��������Ѵ�. �׷��� ȣ��.
// 

// 
// changelevel : sharedptr�� ��ü������ dynamic cast�� ����. �װɷ� casting �� �������ִ� ���
// 
// emplace_back ���ο��� �ڱⰡ �⺻ ������ ������ ������ ������ִ� ��
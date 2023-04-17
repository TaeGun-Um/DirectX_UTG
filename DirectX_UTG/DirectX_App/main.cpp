#include "PrecompileHeader.h"
#include <Windows.h>
#include <GameEngineBase\GameEngineFile.h>
#include <GameEngineBase\GameEngineDirectory.h>
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineContents\CupheadCore.h>

#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContents.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineCore::Start(hInstance, CupheadCore::GameStart, CupheadCore::GameEnd, { 0, 0 });
}

// 
// ������� �̸��� �ϳ��ε�, ���ؽ��� ���Ǳ⵵ �ϰ� ���̴��� ���Ǳ⵵ �Ѵٸ�, �ذ� ����� multimap�̴�.
// 
// ������۴� ���� ���������~ ���̴� ������ �ϸ鼭 �̷� ���̴��� ���±��� �ϰ�(64����Ʈ ¥�� ������۸� ����) ��� ���۰� ��������� ��
// ���ҽ��� �ؽ��ĸ� ����, ������۸� ���׸� ��� �ִ� ��  
// 
// ������۴� �޸𸮸� �Ƴ��� ���ؼ� ������ ������ ��ģ��.
// �ٸ� ���̴��� ���� ������µ�, �̸��� �Ȱ��� ũ�Ⱑ �ٸ� ���� ����
// 
// switch������ ���ƿͼ�
// ������� ���ٰ� �� ��Ȳ��, Create() �ǽ���.
// ������ ���̴��� ����� ������� ������۴� ��� �þ ���̴�.
// �̸��� �Ȱ��� ũ�Ⱑ �ٸ� �� ������, ������ �Ȱ��� �̸��� ũ���� ������۰� ������� ���� ����
// �⺻������ ������۴� �̸��� �߿��Ѱ� �ƴϰ� ũ�Ⱑ �߿��ϴ�.
// 
// ���� ������ ���ҽ��� �̸����� �����ϱ�� �ߴ�.
// ������۴� �̸��� �߿����� �ʾƼ� �̸����� ���� ���Ұ���
// GameEngineResources�� ��� ���� ���̴�.
// ������۴� ������ �� �ֱ� ����. �̸��� �ٸ��ٰ� ��� ���۸� �� �������� ���� ����
// ũ�Ⱑ ���� ������۴� �����ȴ�.
// 
// ������� CreateAndFind�� ���ǿ� �մ��� ���� ��������, ������ ���� ��������
// �Ű� ������ byte, Name���� �ϴ� ������
// ũ��� ������ ���԰� �̸��� �ٸ��� �ٸ� ��� ���۰� �Ǳ� ����.
// 
// CPU Ŭ���װ� write, ����� �����ؼ� ���ֱ� ����
// �׷��� ���̳������� ���������
// GetDevice->CreateBuffer���� 2��° ���ڰ� �ʿ����.
// 
// �ؽ��Ĵ� �����̰� ������ �����̶��
// ���ڰ� �����Ե� ���ҽ����� ���������� �ϳ��� ������ �ϴ� ��
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
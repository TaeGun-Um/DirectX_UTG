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
	GameEngineCore::Start(hInstance, ContentsCore::GameStart, ContentsCore::GameEnd, { 0, 0 });
}

// �����
// 
// ���Ҽ� ����� ��� �� = ���ʹϿ�
// ȸ������� 4x4�ε�
// �̰� x y z w�� ���ؼ� ���� �� ����. (1x4�� ����)
// �װ� ������ ����ϸ� ȸ������� �ȴٴ� ��
// 
// ���ʹϿ��� 4x4�� �ƴ� 1x4�� ���ϰ� �ֱ� ������ �޸������� �̵�
// �׸��� ������ ������ �Ȼ���� �ȴ�.
// 
// �ٵ� �� ������� ������ ������ڸ�
// ���� �����̽��� �����ϴ� ���𰡸� �ٲٷ��� �����غ���.
// ���⿡�� �̹� ũ���̰� ����Ǿ� �ִ�.
// �� ����� ������ �и��ϴ� �� ������ ¥������ �����.
// �ٵ� ���̷�Ʈ���� �̰� ��������
// XMMatrixDecompose(ũ, ��, ��)
// 
// �ϴ� �� ���� ���Ϸ���(���� �ɷ�) �̷��� ����� �̾Ƴ� �� ����.
// 
// ���߻��
// ���߻���� ���� �� ����ϴ� ���� �������̽��� �����ϴ� ���̴�.
// ��������� �׻� ������ ����Ű�� ������.
// ��� Ǯ�������� �����ϸ� �˾Ƴ� �� ����(��ȣ���� �������.)
// 
// �޽��� CreateLevel ���� ������� �־�� �Ѵ�.
// ���� �������� �ڽ��� ��, ��Ʈ ������ ��������� �Ѵ�.
// �̰͵��� Mesh�� ����.
// 
// ���� �ȳ����� ���� ���ϴ� Ÿ�ֿ̹� ���ŵȴ٤Ѥ� ���� ����ϱ� ���� CoreResourcesEnd���� ����
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
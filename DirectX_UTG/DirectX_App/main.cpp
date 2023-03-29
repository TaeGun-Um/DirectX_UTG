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

// �� ���
// 
// ���ϱ��� ���� Ŭ������ ������ �߿��� Ŭ�����̴�.
// ���� �ٲ� TransfomUpdata()�� ������.
// ����� ���� ���� �� ������, Ư�� ������Ʈ�� �ƴ� �� ����
// ��κ��� ������Ʈ�� �������� �ʱ� ������, TransformUpdate�� ������.
// 
// MainCamera�� ���������, Getmaincamera�� �������.
// ���Ϳ��� �ٷ� ��� ����.
// 
// �ڽ��� ���� ������ ������ class GameEngineLevel* Level ��� ���� ����
// ActorInit �������� Level->This�� ����
// 
// ��ũ���Լ��� �ζ����Լ��� ����
// ��ũ�� �Լ��� #define���� ����
// ������� �ɱ� �����
// ���� ġȯ���̱� ������ �ڷ����� üũ���ִ� �����Ϸ��� üũ�ص� �˾ƺ��� ���
// �������������ڵ� �ȵȴ�.
// �׷��� �ζ����� �������� �ڵ��� ����ϴ� ���� ����.
// 
// �Լ��� Local�� ���̴� ������ ���Ŀ� �˷���
// 
// �� ����� ����� ���ؼ� Z�� Y�� �ʿ��ϴ�.
// 
// LookAtLH �Լ� ���ο��� ������ ����.
// 
// ������ ���ؼ� ���ƾ��ϴ� ������ ���ϰ�, ������ ���ؼ� ��ŭ ���ƾ��ϴ��� ���� ���ϴ� ���̴�.
// 
// �ٽ� �� ���
// 
// �÷��̾ ������ ������ ����(ī�޶�) -100�� �ִ� ����
// ������� ���ؼ� ī�޶� �������� �̵���Ű�� �ٸ� ���͵��� ��� �׸�ŭ ������ �̵�
// �׷��� float D2Value�� ���� �׸�ŭ �̵��� ���� �Էµ�.
// 
// D0, D1�� X, Y���� ����
// 
// �̷��� ��ư�(?) ���ϴ� ������ ���� ȸ���� ���߱� ������.
// �׷��� ����� �� ���� ���翵 ������ ���;��ϱ� ������ ��ư�(?) ���ϴ���
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
// 
// 
// 
// 
// 
// 
// 
//
//
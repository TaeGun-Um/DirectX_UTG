#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"

// CreateActor�� �ǽ��ϸ鼭, shared_ptr�� Ȱ���ϸ� ���� ���� �� ���� �ȴ�.
GameEngineLevel::GameEngineLevel()
{
	MainCamera = CreateActor<GameEngineCamera>();
}

GameEngineLevel::~GameEngineLevel()
{
}

void GameEngineLevel::Loading()
{


}

void GameEngineLevel::Update(float _DeltaTime)
{
	// Actors(map)�� Update ȣ��
	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		// �ش� �κп��� TimeScale�� �����Ͽ� �������ų�, ��� ���߰ų� �ϴ� �������̽��� �߰��� ����
		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			Actor->Update(_DeltaTime);
		}
	}
}

void GameEngineLevel::Render(float _DeltaTime)
{
	// �������� ������ �� ������ ȣ��Ǵ� ������ (������ ����)
	// Actors(map)�� Render ȣ��
	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			Actor->Render(_DeltaTime);
		}
	}
}

// ������ �Լ�������, ������� ������ ��� Actor ����� �����ؾ��� �� �ִ�.
// �� ��� ��ȯ������ �߻� ����� �ֱ� ������ ���⼭ ����
void GameEngineLevel::ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Parent)
{
	_Actor->Level = this;        // ActorInit �������� ��� ���� ���� (GetLevel Ȱ�� ����)
	_Actor->SetParent(_Parent);
	_Actor->SetOrder(_Order);
	_Actor->Start();
}
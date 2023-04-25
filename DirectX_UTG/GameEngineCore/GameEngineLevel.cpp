#include "PrecompileHeader.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"

GameEngineLevel::GameEngineLevel()
{
	MainCamera = CreateActor<GameEngineCamera>(); // ������ ���� �� ��� ���� ī�޶� �ϳ� ������
}

GameEngineLevel::~GameEngineLevel()
{
}

void GameEngineLevel::Start()
{
}

// ������ ���� ����
void GameEngineLevel::ActorUpdate(float _DeltaTime)
{
	if (true == MainCamera->IsFreeCamera())
	{
		MainCamera->Update(_DeltaTime);
		return;
	}

	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		// TimeScale;
		// ���Ŀ� �����ϰڴ�.
		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			Actor->Update(_DeltaTime);
			Actor->ComponentsUpdate(_DeltaTime);
		}
	}
}
void GameEngineLevel::ActorRender(float _DeltaTime)
{
	// ���������������� ����Ʈ ������ ���� Setting ȣ��
	GetMainCamera()->Setting();

	// �̰� ���߿� ������� �������� ������ �� ������ ���Ǵ� ������ �̿��� ��
	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		// TimeScale;
		// ���Ŀ� �����ϰڴ�.
		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			Actor->Render(_DeltaTime);
			Actor->ComponentsRender(_DeltaTime);
		}
	}
}

void GameEngineLevel::Update(float _DeltaTime)
{
}

void GameEngineLevel::Render(float _DeltaTime)
{
}

void GameEngineLevel::ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Level)
{
	_Actor->Level = this;              // ������ ������ �ش� ������ �ȴ�.
	_Actor->SetOrder(_Order);          // CreateActor���� ������ Order�� ����ȴ�.
	_Actor->Start();                   // ������ ���� ������Ʈ

	Actors[_Order].push_back(_Actor);  // Level�� �����ϰ� �ִ� ���͸� �����ϴ� ����Ʈ�� ����.
}
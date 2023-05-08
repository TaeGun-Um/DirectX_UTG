#include "PrecompileHeader.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineVideo.h"
#include "GameEngineGUI.h"

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
	{
		std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<std::shared_ptr<GameEngineActor>>& ActorList = GroupStartIter->second;

			std::list<std::shared_ptr<GameEngineActor>>::iterator ActorStart = ActorList.begin();
			std::list<std::shared_ptr<GameEngineActor>>::iterator ActorEnd = ActorList.end();

			for (; ActorStart != ActorEnd; ++ActorStart)
			{
				std::shared_ptr<GameEngineActor> CheckActor = (*ActorStart);

				if (true == CheckActor->IsUpdate())
				{
					CheckActor->AccLiveTime(_DeltaTime);
				}

				// ActorStart = ActorList.erase(ActorStart);
			}
		}
	}

	if (true == MainCamera->IsFreeCamera())
	{
		MainCamera->Update(_DeltaTime);
		return;
	}

	{
		std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<std::shared_ptr<GameEngineActor>>& ActorList = GroupStartIter->second;

			std::list<std::shared_ptr<GameEngineActor>>::iterator ActorStart = ActorList.begin();
			std::list<std::shared_ptr<GameEngineActor>>::iterator ActorEnd = ActorList.end();

			for (; ActorStart != ActorEnd; ++ActorStart)
			{
				std::shared_ptr<GameEngineActor>& Actor = *ActorStart;

				if (false == Actor->IsUpdate())
				{
					continue;
				}
				Actor->Update(_DeltaTime);
				Actor->ComponentsUpdate(_DeltaTime);
			}
		}
	}
}
void GameEngineLevel::ActorRender(float _DeltaTime)
{
	// ���������������� ����Ʈ ������ ���� Setting ȣ��
	GetMainCamera()->Setting();

	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupStartIter = Actors.begin();
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupEndIter = Actors.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = GroupStartIter->second;

		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorStart = ActorList.begin();
		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorEnd = ActorList.end();

		for (; ActorStart != ActorEnd; ++ActorStart)
		{
			std::shared_ptr<GameEngineActor>& Actor = *ActorStart;

			if (false == Actor->IsUpdate())
			{
				continue;
			}

			Actor->Render(_DeltaTime);
			Actor->ComponentsRender(_DeltaTime);
		}
	}

	GameEngineGUI::Render(GetSharedThis(), _DeltaTime);
}

void GameEngineLevel::ActorRelease()
{
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupStartIter = Actors.begin();
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupEndIter = Actors.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		// ������ ���� ���۷����� �����Ͽ� ����
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = GroupStartIter->second;

		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorStart = ActorList.begin();
		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorEnd = ActorList.end();

		for (; ActorStart != ActorEnd; )
		{
			std::shared_ptr<GameEngineActor> RelaseActor = (*ActorStart);

			if (nullptr != RelaseActor && false == RelaseActor->IsDeath())
			{
				// ���Ͱ� Death��� �ش� ������ ������Ʈ�� ����������
				RelaseActor->ComponentsRelease();
				++ActorStart;
				continue;
			}

			RelaseActor->Release();
			ActorStart = ActorList.erase(ActorStart);
		}
	}
}

void GameEngineLevel::Update(float _DeltaTime) {}

void GameEngineLevel::Render(float _DeltaTime) {}

void GameEngineLevel::ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Level)
{
	_Actor->Level = this;              // ������ ������ �ش� ������ �ȴ�.
	_Actor->SetOrder(_Order);          // CreateActor���� ������ Order�� ����ȴ�.
	_Actor->Start();                   // ������ ���� ������Ʈ

	Actors[_Order].push_back(_Actor);  // Level�� �����ϰ� �ִ� ���͸� �����ϴ� ����Ʈ�� ����.
}

void GameEngineLevel::LevelChangeStart()
{

}
void GameEngineLevel::LevelChangeEnd()
{

}
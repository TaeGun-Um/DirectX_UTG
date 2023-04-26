#include "PrecompileHeader.h"
#include "PrecompileHeader.h"
#include "GameEngineActor.h"
#include "GameEngineComponent.h"

GameEngineActor::GameEngineActor()
{
}

GameEngineActor::~GameEngineActor()
{
}

// ���Ϳ� ������Ʈ ���� init
void GameEngineActor::ComponentInit(std::shared_ptr<class GameEngineComponent> _Component)
{
	_Component->Actor = this;                               // ������Ʈ�� ���ʹ� �ش� ���ͷ� ����
	_Component->GetTransform()->SetParent(GetTransform());  // ������Ʈ�� �θ� �ش� ���ͷ� ����
	_Component->Start();                                    // ������Ʈ ���� init

	ComponentsList.push_back(_Component);                   // ����Ʈ�� Ǫ����
}

// ������Ʈ ���� ����
void GameEngineActor::ComponentsUpdate(float _DeltaTime)
{
	for (std::shared_ptr<class GameEngineComponent>& Component : ComponentsList)
	{
		if (false == Component->IsUpdate())
		{
			continue;
		}

		Component->Update(_DeltaTime);
	}
}
void GameEngineActor::ComponentsRender(float _DeltaTime)
{
	for (std::shared_ptr<class GameEngineComponent>& Component : ComponentsList)
	{
		if (false == Component->IsUpdate())
		{
			continue;
		}

		Component->Render(_DeltaTime);
	}
}

void GameEngineActor::AccLiveTime(float _LiveTime)
{
	GameEngineUpdateObject::AccLiveTime(_LiveTime);

	for (std::shared_ptr<class GameEngineComponent>& Component : ComponentsList)
	{
		Component->AccLiveTime(_LiveTime);
	}
}
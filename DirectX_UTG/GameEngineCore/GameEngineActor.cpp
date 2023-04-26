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

// 액터에 컴포넌트 구조 init
void GameEngineActor::ComponentInit(std::shared_ptr<class GameEngineComponent> _Component)
{
	_Component->Actor = this;                               // 컴포넌트의 액터는 해당 액터로 설정
	_Component->GetTransform()->SetParent(GetTransform());  // 컴포넌트의 부모를 해당 액터로 설정
	_Component->Start();                                    // 컴포넌트 정보 init

	ComponentsList.push_back(_Component);                   // 리스트에 푸쉬백
}

// 컴포넌트 정보 갱신
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
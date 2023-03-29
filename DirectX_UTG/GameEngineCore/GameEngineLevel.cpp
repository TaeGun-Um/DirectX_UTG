#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"

// CreateActor를 실시하면서, shared_ptr을 활용하면 절대 지울 수 없게 된다.
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
	// Actors(map)의 Update 호출
	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		// 해당 부분에서 TimeScale을 적용하여 느려지거나, 잠시 멈추거나 하는 인터페이스를 추가할 예정
		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			Actor->Update(_DeltaTime);
		}
	}
}

void GameEngineLevel::Render(float _DeltaTime)
{
	// 랜더러의 랜더가 다 끝나고 호출되는 랜더들 (디버깅용 예정)
	// Actors(map)의 Render 호출
	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			Actor->Render(_DeltaTime);
		}
	}
}

// 간단한 함수이지만, 헤더에서 구현할 경우 Actor 헤더를 참조해야할 수 있다.
// 이 경우 순환참조의 발생 우려가 있기 때문에 여기서 구현
void GameEngineLevel::ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Parent)
{
	_Actor->Level = this;        // ActorInit 과정에서 즉시 레벨 지정 (GetLevel 활용 가능)
	_Actor->SetParent(_Parent);
	_Actor->SetOrder(_Order);
	_Actor->Start();
}
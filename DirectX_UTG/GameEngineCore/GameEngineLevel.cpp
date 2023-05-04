#include "PrecompileHeader.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineVideo.h"
#include "GameEngineGUI.h"

GameEngineLevel::GameEngineLevel()
{
	MainCamera = CreateActor<GameEngineCamera>(); // 레벨은 생성 시 즉시 메인 카메라를 하나 생성함
}

GameEngineLevel::~GameEngineLevel()
{
}

void GameEngineLevel::Start()
{
}

// 액터의 정보 갱신
void GameEngineLevel::ActorUpdate(float _DeltaTime)
{
	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			if (false == Actor->IsUpdate())
			{
				continue;
			}
			Actor->AccLiveTime(_DeltaTime);
		}
	}

	if (true == MainCamera->IsFreeCamera())
	{
		MainCamera->Update(_DeltaTime);
		return;
	}

	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		// TimeScale;
		// 추후에 적용하겠다.
		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			if (false == Actor->IsUpdate())
			{
				continue;
			}

			Actor->Update(_DeltaTime);
			Actor->ComponentsUpdate(_DeltaTime);
		}
	}
}
void GameEngineLevel::ActorRender(float _DeltaTime)
{
	// 랜더링파이프라인 뷰포트 설정을 위한 Setting 호출
	GetMainCamera()->Setting();

	// 이건 나중에 만들어질 랜더러의 랜더가 다 끝나고 사용되는 랜더가 이용할 것
	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		// TimeScale;
		// 추후에 적용하겠다.
		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			Actor->Render(_DeltaTime);
			Actor->ComponentsRender(_DeltaTime);
		}
	}

	GameEngineGUI::Render(GetSharedThis(), _DeltaTime);
}

void GameEngineLevel::ActorRelease()
{
	// 이건 나중에 만들어질 랜더러의 랜더가 다 끝나고 되는 랜더가 될겁니다.

	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		std::list<std::shared_ptr<GameEngineActor>>::iterator Start = ActorList.begin();
		std::list<std::shared_ptr<GameEngineActor>>::iterator End = ActorList.end();

		for (; Start != End; )
		{
			std::shared_ptr<GameEngineActor> RelaseActor = (*Start);

			if (nullptr != RelaseActor && false == RelaseActor->IsDeath())
			{
				++Start;
				continue;
			}

			RelaseActor->Release();
			Start = ActorList.erase(Start);
		}
	}

}

void GameEngineLevel::Update(float _DeltaTime) {}

void GameEngineLevel::Render(float _DeltaTime) {}

void GameEngineLevel::ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Level)
{
	_Actor->Level = this;              // 액터의 레벨은 해당 레벨이 된다.
	_Actor->SetOrder(_Order);          // CreateActor에서 지정한 Order가 복사된다.
	_Actor->Start();                   // 액터의 정보 업데이트

	Actors[_Order].push_back(_Actor);  // Level이 관리하고 있는 액터를 관리하는 리스트에 들어간다.
}

void GameEngineLevel::LevelChangeStart()
{

}
void GameEngineLevel::LevelChangeEnd()
{

}
#pragma once
#include <map>
#include <string_view>

#include <GameEngineBase\GameEngineTimeEvent.h>
#include "GameEngineObject.h"

// 설명 :
class GameEngineActor;
class GameEngineLevel : public GameEngineObject
{
	friend class GameEngineCore;

public:
	GameEngineTimeEvent TimeEvent;

	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	// 이름으로만 Create할 경우 랜더 오더가 0이 되도록 한 뒤, 아래 함수 호출
	template<typename ActorType>
	std::shared_ptr<ActorType> CreateActor(const std::string_view& _Name)
	{
		return CreateActor<ActorType>(0, _Name);
	}

	// 이번 Actor는 Create시, RenderOrder를 합쳐서 구현
	template<typename ActorType>
	std::shared_ptr<ActorType> CreateActor(int _Order = 0, const std::string_view& _Name = "")
	{
		std::shared_ptr<GameEngineActor> NewActor = std::make_shared<ActorType>();

		std::string Name = _Name.data();

		if (_Name == "")
		{
			const type_info& Info = typeid(ActorType);
			Name = Info.name();
			Name.replace(0, 6, "");
		}

		// Actor의 정보를 입력하고 Actors에 넣는다.
		ActorInit(NewActor, _Order, this);
		Actors[_Order].push_back(NewActor);

		return std::dynamic_pointer_cast<ActorType>(NewActor);
	}

protected:
	virtual void Loading() = 0;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>> Actors;

	void ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Level);

};


#pragma once
#include "GameEngineObject.h"

// 설명 :
class GameEngineActor : public GameEngineObject
{
	friend class GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	template<typename ActorType, typename EnumType>
	std::shared_ptr<ActorType> CreateComponent(EnumType _Order)
	{
		return CreateComponent<ActorType>(static_cast<int>(_Order));
	}

	// 액터의 컴포넌트(충돌체, 랜더러) 생성 후 ComponentsList에 Init
	template<typename ComponentType>
	std::shared_ptr<ComponentType> CreateComponent(int _Order = 0)
	{
		std::shared_ptr<class GameEngineComponent> NewComponent = std::make_shared<ComponentType>();

		ComponentInit(NewComponent, _Order);

		return std::dynamic_pointer_cast<ComponentType>(NewComponent);
	}

	void SetOrder(int _Order) override;

protected:
	virtual void Start() {}
	virtual void Update(float _DeltaTime) {}
	virtual void Render(float _DeltaTime) {}

private:
	void ComponentInit(std::shared_ptr<class GameEngineComponent> _Component, int _Order = 0); // 컴포넌트 정보 init

};


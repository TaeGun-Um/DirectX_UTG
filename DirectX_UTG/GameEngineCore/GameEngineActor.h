#pragma once
#include "GameEngineUpdateObject.h"

// 설명 :
class GameEngineActor : public GameEngineUpdateObject
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

	// 액터가 해당되는 레벨 리턴
	inline class GameEngineLevel* GetLevel() const
	{
		return Level;
	}

	// Component 생성
	template<typename ComponentType>
	std::shared_ptr<ComponentType> CreateComponent()
	{
		std::shared_ptr<class GameEngienComponent> NewComponent = std::make_shared<ComponentType>();

		ComponentInit(NewComponent);

		return std::dynamic_pointer_cast<ComponentType>(NewComponent);
	}

protected:
	virtual void Start() {}
	virtual void Update(float _DeltaTime) {}
	virtual void Render(float _DeltaTime) {}

private:
	class GameEngineLevel* Level;  // Actorinit 단계에서 Level을 this로 지정해주기 때문에, 액터의 레벨이 결정된다.

	std::list<std::shared_ptr<class GameEngineComponent>> ComponentList; // 이걸 컴포넌트 구조라고 합니다.

	// 컴포넌트의 부모 등록, 컴포넌트 init 실시
	void ComponentInit(std::shared_ptr<class GameEngineComponent> _Component);
};


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

	// Actor의 레벨은 액터 생성 시 자동으로 결정됨
	inline class GameEngineLevel* GetLevel() const
	{
		return Level;
	}

	// 액터의 컴포넌트(충돌체, 랜더러) 생성 후 ComponentsList에 Init
	template<typename ComponentType>
	std::shared_ptr<ComponentType> CreateComponent()
	{
		std::shared_ptr<class GameEngineComponent> NewComponent = std::make_shared<ComponentType>();

		ComponentInit(NewComponent);

		return std::dynamic_pointer_cast<ComponentType>(NewComponent);
	}

protected:
	virtual void Start() {}
	virtual void Update(float _DeltaTime) {}
	virtual void Render(float _DeltaTime) {}

	void AccLiveTime(float _LiveTime) override;

private:
	class GameEngineLevel* Level = nullptr;

	//// 이걸 컴포넌트 구조라고 합니다.
	std::list<std::shared_ptr<class GameEngineComponent>> ComponentsList;      // 생성한 컴포넌트들

	void ComponentInit(std::shared_ptr<class GameEngineComponent> _Component); // 컴포넌트 정보 init
	void ComponentsUpdate(float _DeltaTime);                                   // 컴포넌트 정보 갱신
	void ComponentsRender(float _DeltaTime);                                   // 컴포넌트 정보 갱신
	void ComponentsRelease();												   // 컴포넌트 릴리즈

};


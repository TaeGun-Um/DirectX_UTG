#pragma once
#include "GameEngineUpdateObject.h"

// ���� :
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

	// Actor�� ������ ���� ���� �� �ڵ����� ������
	inline class GameEngineLevel* GetLevel() const
	{
		return Level;
	}

	// ������ ������Ʈ(�浹ü, ������) ���� �� ComponentsList�� Init
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

	//// �̰� ������Ʈ ������� �մϴ�.
	std::list<std::shared_ptr<class GameEngineComponent>> ComponentsList;      // ������ ������Ʈ��

	void ComponentInit(std::shared_ptr<class GameEngineComponent> _Component); // ������Ʈ ���� init
	void ComponentsUpdate(float _DeltaTime);                                   // ������Ʈ ���� ����
	void ComponentsRender(float _DeltaTime);                                   // ������Ʈ ���� ����
	void ComponentsRelease();												   // ������Ʈ ������

};


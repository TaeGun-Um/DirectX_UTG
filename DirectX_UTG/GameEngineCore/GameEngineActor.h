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

	// 액터가 해당되는 레벨 리턴
	inline class GameEngineLevel* GetLevel() const
	{
		return Level;
	}

protected:
	virtual void Start() {}
	virtual void Update(float _DeltaTime) {}
	virtual void Render(float _DeltaTime) {}

private:
	class GameEngineLevel* Level;  // Actorinit 단계에서 Level을 this로 지정해주기 때문에, 액터의 레벨이 결정된다.
};


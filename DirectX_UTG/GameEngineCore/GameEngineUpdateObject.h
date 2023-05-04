#pragma once
#include "GameEngineObject.h"

// 설명 : 상속한 클래스에게 protected의 Start(), Updata(). Render()를 구현하도록 하는 클래스
class GameEngineUpdateObject : public GameEngineObject
{
	friend class GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineUpdateObject();
	~GameEngineUpdateObject();

	// delete Function
	GameEngineUpdateObject(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject(GameEngineUpdateObject&& _Other) noexcept = delete;
	GameEngineUpdateObject& operator=(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject& operator=(GameEngineUpdateObject&& _Other) noexcept = delete;

	virtual void AccLiveTime(float _LiveTime)
	{
		LiveTime += _LiveTime;
	}

	void ResetLiveTime()
	{
		LiveTime = 0.0f;
	}

	float GetLiveTime()
	{
		return LiveTime;
	}

protected:
	virtual void Start() {}
	virtual void Update(float _DeltaTime) {}
	virtual void Render(float _DeltaTime) {}
	virtual void Release() {}

private:
	float LiveTime = 0.0f;

};


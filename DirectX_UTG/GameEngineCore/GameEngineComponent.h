#pragma once
#include "GameEngineActor.h"

// 설명 : 액터의 컴포넌트들 (충돌체, 랜더러 등)
class GameEngineComponent : public GameEngineUpdateObject
{
	friend class GameEngineActor;

public:
	// constrcuter destructer
	GameEngineComponent();
	~GameEngineComponent();

	// delete Function
	GameEngineComponent(const GameEngineComponent& _Other) = delete;
	GameEngineComponent(GameEngineComponent&& _Other) noexcept = delete;
	GameEngineComponent& operator=(const GameEngineComponent& _Other) = delete;
	GameEngineComponent& operator=(GameEngineComponent&& _Other) noexcept = delete;

	// 컴포넌트의 액터는 Init 시 결정된다.
	class GameEngineActor* GetActor()
	{
		return Actor;
	}

	// 컴포넌트의 Parent(Actor)에게서 GetLevel()
	class GameEngineLevel* GetLevel()
	{
		return Actor->GetLevel();
	}

protected:

private:
	class GameEngineActor* Actor;                  // 액터(부모)는 Init 시 결정된다.

	void SetActor(class GameEngineActor* _Actor);  // 자신의 액터(부모)를 결정

};


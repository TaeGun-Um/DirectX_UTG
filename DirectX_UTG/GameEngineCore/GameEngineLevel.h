#pragma once

// pragma comment를 GameEngineCore.h에서 실시했기 때문에, GameEngineCore 프로젝트 내 다른 파일에서는 따로 참조 선언하지 않아도 된다.
#include <GameEngineBase\GameEngineTimeEvent.h>

// 설명 :
class GameEngineLevel
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

protected:
	virtual void Loading() = 0;

private:

};


#pragma once
#include <map>
#include <string>
#include <memory>
#include <Windows.h>
#include <functional>
#include <string_view>

#include <GameEngineBase\GameEngineString.h>

#include "GameEngineLevel.h"

// 설명 :
class GameEngineCore
{
public:
	// constrcuter destructer
	GameEngineCore();
	~GameEngineCore();

	// delete Function
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

	// 이번에는 함수 포인터가 아닌 functional을 활용할 예정
	static void Start(HINSTANCE _instance, std::function<void()> _Start, std::function<void()> _End);

	// LevelMap에 Level 데이터 입력
	template<typename LevelType>
	static void CreateLevel(const std::string_view& _Name = "")
	{
		LevelType* NewLevel = new LevelType();

		std::string Name;

		if (_Name == "")
		{

		}

		Name = GameEngineString::ToUpper(Name);
		LevelMap.insert(Name, NewLevel);
	}
	static void ChangeLevel(const std::string_view& _Name);

protected:

private:
	static void EngineStart();
	static void EngineUpdate();
	static void EngineEnd();

	static std::map<std::string, std::shared_ptr<GameEngineLevel>> LevelMap; // Core는 당연히 Level 자료형을 가지고 있어야 한다.
};


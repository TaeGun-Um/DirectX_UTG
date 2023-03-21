#pragma once
#include <map>
#include <string>
#include <memory>
#include <Windows.h>
#include <functional>
#include <string_view>
#include <typeinfo>

#pragma comment(lib, "GameEngineBase.lib")
#pragma comment(lib, "GameEnginePlatform.lib")

#include <GameEngineBase\GameEngineString.h>
#include <GameEngineBase\GameEngineDebug.h>

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

	static void Start(HINSTANCE _instance, std::function<void()> _Start, std::function<void()> _End, float4 _Pos = { 0, 0 }, float4 _Size = { 1280, 720 });

	template<typename LevelType>
	static std::shared_ptr<LevelType> CreateLevel(const std::string_view& _Name = "")
	{
		std::shared_ptr<GameEngineLevel> NewLevel = std::make_shared<LevelType>();

		std::string Name = _Name.data();

		// 클래스에 typeid를 활용하여 타입 정보체중 하나인 클래스명을 Name으로 설정
		if (_Name == "")
		{
			const type_info& Info = typeid(LevelType);
			Name = Info.name();
			// "Class Player" 에서 replace(0, 6, "") 시, 인덱스 0부터 6까지 텍스트를 제거하고 7부터 ""에 삽입
			Name.replace(0, 6, "");
		}

		Name = GameEngineString::ToUpper(Name);

		if (LevelMap.end() != LevelMap.find(Name))
		{
			MsgAssert("같은 이름의 레벨을 2개 만들수는 없습니다.");
		}

		// 상속받은 Level로 이동하여 Loading() 실행
		LevelInit(NewLevel);

		LevelMap.insert(std::make_pair(Name, NewLevel));

		return std::dynamic_pointer_cast<LevelType>(NewLevel);
	}
	static void ChangeLevel(const std::string_view& _Name);

protected:

private:
	static void LevelInit(std::shared_ptr<GameEngineLevel> _Level);

	static void EngineStart(std::function<void()> __ContentsStart);
	static void EngineUpdate();
	static void EngineEnd(std::function<void()> __ContentsEnd);

	static std::map<std::string, std::shared_ptr<GameEngineLevel>> LevelMap;
	static std::shared_ptr<GameEngineLevel> NextLevel; // 우선 ChangeLevel()에서 NextLevel에 find한 레벨 복사
	static std::shared_ptr<GameEngineLevel> MainLevel; // UpdateLoop에서 NextLevel을 MainLevel에 복수
};


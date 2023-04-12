#pragma once
#include <string>

// 설명 : GEObject의 부모 클래스, Name과 관련된 기능 담당
class GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineNameObject();
	~GameEngineNameObject();

	// delete Function
	GameEngineNameObject(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject(GameEngineNameObject&& _Other) noexcept = delete;
	GameEngineNameObject& operator=(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject& operator=(GameEngineNameObject&& _Other) noexcept = delete;

	// 상속한 클래스들의 Name을 지정
	void SetName(const std::string_view& _Name)
	{
		Name = _Name;
	}

	// 상속한 클래스들의 Name을 리턴
	std::string_view GetName()
	{
		return Name.c_str();
	}

protected:

private:
	std::string Name = "";  // 클래스들의 Name

};


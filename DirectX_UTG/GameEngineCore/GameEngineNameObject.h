#pragma once
#include <string>

// ���� : GEObject�� �θ� Ŭ����, Name�� ���õ� ��� ���
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

	// ����� Ŭ�������� Name�� ����
	void SetName(const std::string_view& _Name)
	{
		Name = _Name;
	}

	// ����� Ŭ�������� Name�� ����
	std::string_view GetName()
	{
		return Name.c_str();
	}

protected:

private:
	std::string Name = "";  // Ŭ�������� Name

};


#pragma once
#include "GameEnginePath.h"
#include "GameEngineSerializer.h"

enum class SAVEMODE
{
	Text,
	Bin,
};

// ���� : ���� ������� ���� Ŭ����
class GameEngineFile
{
public:
	// constrcuter destructer
	GameEngineFile();
	~GameEngineFile();
	GameEngineFile(std::filesystem::path _Path);

	// delete Function
	// GameEngineFile(const GameEngineFile& _Other) = delete;
	// GameEngineFile(GameEngineFile&& _Other) noexcept = delete;
	// GameEngineFile& operator=(const GameEngineFile& _Other) = delete;
	// GameEngineFile& operator=(GameEngineFile&& _Other) noexcept = delete;

	std::string GetFullPath()
	{
		return Path.Path.string();
	}

	void SaveBin(const GameEngineSerializer& _Data); // �����͸� ���̳ʸ� ���·� ����
	void SaveText(const std::string_view& _View);    // �����͸� �ؽ�Ʈ ���·� ����
	void LoadBin(GameEngineSerializer& _Data);       // �����͸� ���̳ʸ��� �ҷ�����

protected:

private:
	GameEnginePath Path; // == "D:\Project\AR45\WINAPI\APIApp\ContentsResources\Iamge\";
};


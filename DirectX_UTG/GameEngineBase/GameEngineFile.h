#pragma once
#include "GameEnginePath.h"
#include "GameEngineSerializer.h"

enum class SAVEMODE
{
	Text,
	Bin,
};

// 설명 : 파일 입출력을 위한 클래스
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

	void SaveBin(const GameEngineSerializer& _Data); // 데이터를 바이너리 형태로 저장
	void SaveText(const std::string_view& _View);    // 데이터를 텍스트 형태로 저장
	void LoadBin(GameEngineSerializer& _Data);       // 데이터를 바이너리로 불러오기

protected:

private:
	GameEnginePath Path; // == "D:\Project\AR45\WINAPI\APIApp\ContentsResources\Iamge\";
};


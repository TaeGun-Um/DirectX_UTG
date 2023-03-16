#pragma once
#include <string_view>
#include <vector>
#include "GameEnginePath.h"


// Ό³Έν :
class GameEngineFile;
class GameEngineDirectory
{
public:
	// constrcuter destructer
	GameEngineDirectory();
	~GameEngineDirectory();

	// delete Function
	GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory(GameEngineDirectory&& _Other) noexcept = delete;
	GameEngineDirectory& operator=(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory&& _Other) noexcept = delete;

	bool IsFile(const std::string_view& _FileName);

	bool MoveParent();

	void MoveParentToDirectory(const std::string_view& _String);

	bool Move(const std::string_view& _String);

	GameEnginePath GetPlusFileName(const std::string_view& _String);

	std::vector<GameEngineFile> GetAllFile(const std::string_view& _Ext = "");

protected:

private:
	GameEnginePath Path; // == "D:\Project\AR45\WINAPI\APIApp\ContentsResources\Iamge\";
};


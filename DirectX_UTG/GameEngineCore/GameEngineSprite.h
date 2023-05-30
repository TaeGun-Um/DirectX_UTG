#pragma once

#include "GameEngineTexture.h"

class SpriteInfo
{
public:
	std::shared_ptr<GameEngineTexture> Texture;
	float4 CutData;
};

// 설명 : 스프라이트는 무조건 1개 이상의 이미지 정보가 들어있음
// 이걸 만들때 그 텍스처가 로딩이 안되어있으면 텍스처의 로딩도 겸함
class GameEngineSprite : public GameEngineResource<GameEngineSprite>
{
public:
	// constrcuter destructer
	GameEngineSprite();
	~GameEngineSprite();

	// delete Function
	GameEngineSprite(const GameEngineSprite& _Other) = delete;
	GameEngineSprite(GameEngineSprite&& _Other) noexcept = delete;
	GameEngineSprite& operator=(const GameEngineSprite& _Other) = delete;
	GameEngineSprite& operator=(GameEngineSprite&& _Other) noexcept = delete;

	// 폴더 내 파일들을 프레임 애니메이션으로(Path만)
	static std::shared_ptr<GameEngineSprite> LoadFolder(const std::string_view& _Path)
	{
		GameEnginePath NewPath = std::string(_Path);
		return LoadFolder(NewPath.GetFileName(), _Path);
	}

	// 폴더 내 파일들을 프레임 애니메이션으로
	static std::shared_ptr<GameEngineSprite> LoadFolder(std::string _Spritename, const std::string_view& _Path)
	{
		std::shared_ptr<GameEngineSprite> NewTexture = GameEngineResource::Create(_Spritename);
		NewTexture->ResLoadFolder(_Path);
		return NewTexture;
	}

	// 스프라이트 시트를 프레임 애니메이션으로(기존)
	static std::shared_ptr<GameEngineSprite> LoadSheet(const std::string_view& _Path, size_t _X, size_t _Y)
	{
		GameEnginePath NewPath = std::string(_Path);

		std::shared_ptr<GameEngineSprite> NewTexture = GameEngineResource::Create(NewPath.GetFileName());
		NewTexture->ResLoadSheet(_Path, _X, _Y);
		return NewTexture;
	}

	size_t GetSpriteCount()
	{
		return Sprites.size();
	}

	const SpriteInfo& GetSpriteInfo(size_t _Index)
	{
		if (_Index < 0)
		{
			MsgAssert("0이하의 스프라이트 인덱스 입니다.");
		}

		if (_Index >= Sprites.size())
		{
			MsgAssert("스프라이트의 인덱스를 오버했습니다.");
		}

		return Sprites[_Index];
	}

	static void TargetSpriteRelease(const std::string_view& _Name)
	{
		GameEngineResource::TargetResourceRelase(_Name);
	}

protected:

private:
	void ResLoadFolder(const std::string_view& _Path);
	void ResLoadSheet(const std::string_view& _Path, size_t _X, size_t _Y);

	std::vector<SpriteInfo> Sprites;

};

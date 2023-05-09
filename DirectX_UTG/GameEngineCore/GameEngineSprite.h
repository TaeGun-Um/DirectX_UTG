#pragma once

#include "GameEngineTexture.h"

// ���� : ��������Ʈ�� ������ 1�� �̻��� �̹��� ������ �������
// �̰� ���鶧 �� �ؽ�ó�� �ε��� �ȵǾ������� �ؽ�ó�� �ε��� ����
class GameEngineSprite : public GameEngineResource<GameEngineSprite>
{
private:
	class SpriteInfo
	{
		std::shared_ptr<GameEngineTexture> Sprite;
		float4 CutData;
	};

public:
	// constrcuter destructer
	GameEngineSprite();
	~GameEngineSprite();

	// delete Function
	GameEngineSprite(const GameEngineSprite& _Other) = delete;
	GameEngineSprite(GameEngineSprite&& _Other) noexcept = delete;
	GameEngineSprite& operator=(const GameEngineSprite& _Other) = delete;
	GameEngineSprite& operator=(GameEngineSprite&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineSprite> LoadFolder(const std::string_view& _Path);

protected:

private:
	std::vector<SpriteInfo> Sprites;

};


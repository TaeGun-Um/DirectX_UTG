#pragma once

#include <GameEngineCore/GameEngineSpriteRenderer.h>

// ���� :
class ContentsSpriteRenderer : public GameEngineSpriteRenderer
{
public:
	void Start() override;

	float4 AColor;

public:
	// constrcuter destructer
	ContentsSpriteRenderer();
	~ContentsSpriteRenderer();

};


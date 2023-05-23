#pragma once

#include <GameEngineCore/GameEngineSpriteRenderer.h>

// Ό³Έν :
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


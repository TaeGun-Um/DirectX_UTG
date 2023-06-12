#pragma once

#include <GameEngineCore/GameEngineSpriteRenderer.h>

// Ό³Έν :
class HBSCSpriteRenderer : public GameEngineSpriteRenderer
{
public:
	// constrcuter destructer
	HBSCSpriteRenderer();
	~HBSCSpriteRenderer();

	// delete Function
	HBSCSpriteRenderer(const HBSCSpriteRenderer& _Other) = delete;
	HBSCSpriteRenderer(HBSCSpriteRenderer&& _Other) noexcept = delete;
	HBSCSpriteRenderer& operator=(const HBSCSpriteRenderer& _Other) = delete;
	HBSCSpriteRenderer& operator=(HBSCSpriteRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};


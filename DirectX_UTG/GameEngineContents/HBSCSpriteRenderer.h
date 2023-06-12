#pragma once

#include <GameEngineCore/GameEngineSpriteRenderer.h>

struct HBSCOption
{
	float4 MulColor;
	float4 PlusColor;
	float4 HBSCColor;
};

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

	HBSCOption HBSCColorValue;


protected:
	void Start() override;

private:
	void HBSCRenderInit();

};


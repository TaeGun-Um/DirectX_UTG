#include "PrecompileHeader.h"
#include "HBSCSpriteRenderer.h"

HBSCSpriteRenderer::HBSCSpriteRenderer() 
{
}

HBSCSpriteRenderer::~HBSCSpriteRenderer() 
{
}

void HBSCSpriteRenderer::Start()
{
	GameEngineRenderer::Start();
	HBSCRenderInit();
}

void HBSCSpriteRenderer::HBSCRenderInit()
{
	SetMesh("Rect");
	SetPipeLine("HBSCSprite");

	AtlasData.x = 0.0f;
	AtlasData.y = 0.0f;
	AtlasData.z = 1.0f;
	AtlasData.w = 1.0f;

	HBSCColorValue.MulColor = float4::One;
	HBSCColorValue.PlusColor = float4::Null;
	HBSCColorValue.HBSCColor = float4::Null;

	GetShaderResHelper().SetConstantBufferLink("AtlasData", AtlasData);
	GetShaderResHelper().SetConstantBufferLink("HBSCOption", HBSCColorValue);
}
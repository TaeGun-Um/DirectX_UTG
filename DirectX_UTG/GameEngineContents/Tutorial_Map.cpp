#include "PrecompileHeader.h"
#include "Tutorial_Map.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Tutorial_Map::Tutorial_Map() 
{
}

Tutorial_Map::~Tutorial_Map() 
{
}

void Tutorial_Map::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->SetTexture("Tutorial_Map.png");
		RenderPtr->GetTransform()->SetLocalScale({ 6188, 720, 1 });
		RenderPtr->GetTransform()->SetLocalPosition({ 0, 0, 1 });
	}

	if (nullptr == PlatformCollisionPtr)
	{
		PlatformCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Platform));
		PlatformCollisionPtr->GetTransform()->SetLocalScale({ 290, 26, 1 });
		PlatformCollisionPtr->GetTransform()->SetLocalPosition({ -970, 0, 1 });
	}

	if (nullptr == PlatformCollisionRenderPtr)
	{
		PlatformCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		PlatformCollisionRenderPtr->GetTransform()->SetLocalScale({ 290, 26, 1 });
		PlatformCollisionRenderPtr->GetTransform()->SetLocalPosition({ -970, 0, 1 });
		PlatformCollisionRenderPtr->SetTexture("GreenBox.png");
		PlatformCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.5f;
	}

	ParrySpotCollisionRenderPtr0 = CreateComponent<GameEngineSpriteRenderer>();
	ParrySpotCollisionRenderPtr0->GetTransform()->SetLocalScale({ 50, 50, 1 });
	ParrySpotCollisionRenderPtr0->GetTransform()->SetLocalPosition({ 705, -7, 1 });
	ParrySpotCollisionRenderPtr0->SetTexture("RedBox.png");
	ParrySpotCollisionRenderPtr0->ColorOptionValue.MulColor.a = 0.6f;

	ParrySpotCollisionRenderPtr1 = CreateComponent<GameEngineSpriteRenderer>();
	ParrySpotCollisionRenderPtr1->GetTransform()->SetLocalScale({ 50, 50, 1 });
	ParrySpotCollisionRenderPtr1->GetTransform()->SetLocalPosition({ 895, -7, 1 });
	ParrySpotCollisionRenderPtr1->SetTexture("RedBox.png");
	ParrySpotCollisionRenderPtr1->ColorOptionValue.MulColor.a = 0.6f;

	ParrySpotCollisionRenderPtr2 = CreateComponent<GameEngineSpriteRenderer>();
	ParrySpotCollisionRenderPtr2->GetTransform()->SetLocalScale({ 50, 50, 1 });
	ParrySpotCollisionRenderPtr2->GetTransform()->SetLocalPosition({ 1085, -7, 1 });
	ParrySpotCollisionRenderPtr2->SetTexture("RedBox.png");
	ParrySpotCollisionRenderPtr2->ColorOptionValue.MulColor.a = 0.6f;

	ParrySpotCollisionPtr0 = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::ParrySpot));
	ParrySpotCollisionPtr0->GetTransform()->SetLocalScale({ 50, 50, 1 });
	ParrySpotCollisionPtr0->GetTransform()->SetLocalPosition({ 705, -7, 1 });

	ParrySpotCollisionPtr1 = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::ParrySpot));
	ParrySpotCollisionPtr1->GetTransform()->SetLocalScale({ 50, 50, 1 });
	ParrySpotCollisionPtr1->GetTransform()->SetLocalPosition({ 895, -7, 1 });

	ParrySpotCollisionPtr2 = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::ParrySpot));
	ParrySpotCollisionPtr2->GetTransform()->SetLocalScale({ 50, 50, 1 });
	ParrySpotCollisionPtr2->GetTransform()->SetLocalPosition({ 1085, -7, 1 });
}
void Tutorial_Map::Update(float _DeltaTime)
{

}
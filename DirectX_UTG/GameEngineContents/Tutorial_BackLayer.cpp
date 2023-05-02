#include "PrecompileHeader.h"
#include "Tutorial_BackLayer.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"

Tutorial_BackLayer::Tutorial_BackLayer() 
{
}

Tutorial_BackLayer::~Tutorial_BackLayer() 
{
}

void Tutorial_BackLayer::Start()
{
	RenderPtr0 = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr0->SetTexture("Tutorial_BackLayer_002.png");
	RenderPtr0->GetTransform()->SetLocalScale({ 1280, 720, 1 });

	RenderPtr1 = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr1->SetTexture("Tutorial_BackLayer_001.png");
	RenderPtr1->GetTransform()->SetLocalScale({ 1280, 720, 100 });
}
void Tutorial_BackLayer::Update(float _DeltaTime)
{
	float4 MinusDist = Player::MainPlayer->GetCameraMoveDistance();
	GetTransform()->AddWorldPosition(MinusDist);
}
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
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetTexture("Tutorial_BackLayer_002.png");
	RenderPtr->GetTransform()->SetLocalScale({ 1280, 720, 1 });
	RenderPtr->GetTransform()->SetLocalPosition({ 0, 0, 1 });
}
void Tutorial_BackLayer::Update(float _DeltaTime)
{
	float4 MinusDist = Player::MainPlayer->GetCameraMoveDistance();
	GetTransform()->AddWorldPosition(MinusDist);
}
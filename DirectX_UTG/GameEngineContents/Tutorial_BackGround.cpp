#include "PrecompileHeader.h"
#include "Tutorial_BackGround.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"

Tutorial_BackGround::Tutorial_BackGround() 
{
}

Tutorial_BackGround::~Tutorial_BackGround() 
{
}

void Tutorial_BackGround::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetTexture("Tutorial_BackLayer_001.png");
	RenderPtr->GetTransform()->SetLocalScale({ 1280, 720, 1 });
	RenderPtr->GetTransform()->SetLocalPosition({ 0, 0, 1 });
}
void Tutorial_BackGround::Update(float _DeltaTime)
{
	float4 MinusDist = Player::MainPlayer->GetCameraMoveDistance();
	GetTransform()->AddWorldPosition(MinusDist);
}
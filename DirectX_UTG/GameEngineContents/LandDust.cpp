#include "PrecompileHeader.h"
#include "LandDust.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

LandDust::LandDust() 
{
}

LandDust::~LandDust() 
{
}

void LandDust::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetScaleToTexture("Ground_JumpDust_005.png");
}
void LandDust::Update(float _DeltaTime)
{

}
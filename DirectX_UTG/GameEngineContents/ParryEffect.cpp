#include "PrecompileHeader.h"
#include "ParryEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

ParryEffect::ParryEffect() 
{
}

ParryEffect::~ParryEffect() 
{
}

void ParryEffect::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetScaleToTexture("Ground_ParryEffect_002.png");
}
void ParryEffect::Update(float _DeltaTime)
{

}
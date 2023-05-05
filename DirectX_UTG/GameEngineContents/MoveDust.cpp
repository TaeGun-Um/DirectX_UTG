#include "PrecompileHeader.h"
#include "MoveDust.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

MoveDust::MoveDust() 
{
}

MoveDust::~MoveDust() 
{
}

void MoveDust::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetScaleToTexture("Temporary_MoveDust.png");
}
void MoveDust::Update(float _DeltaTime)
{

}
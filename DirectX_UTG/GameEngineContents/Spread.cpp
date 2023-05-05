#include "PrecompileHeader.h"
#include "Spread.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Spread::Spread() 
{
}

Spread::~Spread() 
{
}

void Spread::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetScaleToTexture("Temporary_Spread.png");
}
void Spread::Update(float _DeltaTime)
{

}
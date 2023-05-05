#include "PrecompileHeader.h"
#include "Peashooter.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Peashooter::Peashooter() 
{
}

Peashooter::~Peashooter() 
{
}

void Peashooter::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetScaleToTexture("Temporary_Peashooter.png");
}
void Peashooter::Update(float _DeltaTime)
{

}
#include "PrecompileHeader.h"
#include "Peashooter_EX.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Peashooter_EX::Peashooter_EX() 
{
}

Peashooter_EX::~Peashooter_EX() 
{
}

void Peashooter_EX::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetScaleToTexture("Temporary_PeashooterEX.png");
}
void Peashooter_EX::Update(float _DeltaTime)
{

}
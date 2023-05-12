#include "PrecompileHeader.h"
#include "Spread_EX.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Spread_EX::Spread_EX() 
{
}

Spread_EX::~Spread_EX() 
{
}

void Spread_EX::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetScaleToTexture("Temporary_SpreadEX.png");
}

void Spread_EX::Update(float _DeltaTime)
{
	MoveDirection(_DeltaTime);
	DeathCheck();
}

void Spread_EX::MoveDirection(float _DeltaTime)
{

}

void Spread_EX::DeathCheck()
{

}
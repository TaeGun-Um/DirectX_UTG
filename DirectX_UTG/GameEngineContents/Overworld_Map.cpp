#include "PrecompileHeader.h"
#include "Overworld_Map.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Overworld_Map::Overworld_Map() 
{
}

Overworld_Map::~Overworld_Map() 
{
}

void Overworld_Map::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetTexture("Overworld_Map.png");
	RenderPtr->GetTransform()->SetLocalScale({ 4000, 2300, 1 });
	RenderPtr->GetTransform()->SetLocalPosition({ 0, 0, 100 });
}
void Overworld_Map::Update(float _DeltaTime)
{

}
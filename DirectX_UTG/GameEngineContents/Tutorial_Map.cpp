#include "PrecompileHeader.h"
#include "Tutorial_Map.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Tutorial_Map::Tutorial_Map() 
{
}

Tutorial_Map::~Tutorial_Map() 
{
}

void Tutorial_Map::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetTexture("Tutorial_Map.png");
	RenderPtr->GetTransform()->SetLocalScale({ 5760, 720, 10 }); // 8192, 1024
}
void Tutorial_Map::Update(float _DeltaTime)
{

}
#include "PrecompileHeader.h"
#include "TestLevel_Map.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

TestLevel_Map::TestLevel_Map() 
{
}

TestLevel_Map::~TestLevel_Map() 
{
}

void TestLevel_Map::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetTexture("TestLevel_Map.png");
	RenderPtr->GetTransform()->SetLocalScale({ 2000, 720, 1 });
	RenderPtr->GetTransform()->SetLocalPosition({ 0, 0, 100 });

}
void TestLevel_Map::Update(float _DeltaTime)
{

}
#include "PrecompileHeader.h"
#include "Tutorial_ColMap.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Tutorial_ColMap::Tutorial_ColMap() 
{
}

Tutorial_ColMap::~Tutorial_ColMap() 
{
}

void Tutorial_ColMap::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetTexture("Tutorial_ColMap_d.png");
	RenderPtr->GetTransform()->SetLocalScale({ 5760, 720, 1 });
	RenderPtr->GetTransform()->SetLocalPosition({ 0, 0, 50 });
	RenderPtr->Off();
}
void Tutorial_ColMap::Update(float _DeltaTime)
{
	if (true == IsDebugRender)
	{
		RenderPtr->On();
	}
	else
	{
		RenderPtr->Off();
	}
}
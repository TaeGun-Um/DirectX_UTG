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
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->SetTexture("Tutorial_ColMap_d.png");
		RenderPtr->GetTransform()->SetLocalScale({ 6188, 720, 1 });
		RenderPtr->GetTransform()->SetLocalPosition({ 0, 0, 1 });
		RenderPtr->ColorOptionValue.MulColor.a = 0.7f;
		RenderPtr->Off();
	}
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
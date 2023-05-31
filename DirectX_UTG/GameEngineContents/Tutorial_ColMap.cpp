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
	if (nullptr == GameEngineTexture::Find("Tutorial_ColMap.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Tutorial_Normal");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Tutorial_ColMap.png").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->SetTexture("Tutorial_ColMap.png");
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
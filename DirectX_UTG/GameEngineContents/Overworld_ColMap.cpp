#include "PrecompileHeader.h"
#include "Overworld_ColMap.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Overworld_ColMap::Overworld_ColMap() 
{
}

Overworld_ColMap::~Overworld_ColMap() 
{
}

void Overworld_ColMap::Start()
{
	if (nullptr == GameEngineTexture::Find("Overworld_ColMap.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Overworld");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Overworld_ColMap.png").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->SetScaleToTexture("Overworld_ColMap.png");
		RenderPtr->ColorOptionValue.MulColor.a = 0.7f;
	}
}
void Overworld_ColMap::Update(float _DeltaTime)
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
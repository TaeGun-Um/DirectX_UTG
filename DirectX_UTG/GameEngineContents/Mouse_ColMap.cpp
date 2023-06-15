#include "PrecompileHeader.h"
#include "Mouse_ColMap.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Mouse_ColMap::Mouse_ColMap() 
{
}

Mouse_ColMap::~Mouse_ColMap() 
{
}

void Mouse_ColMap::Start()
{
	if (nullptr == GameEngineTexture::Find("Mouse_ColMap.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("3_Werner_Werman");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_ColMap.png").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->SetScaleToTexture("Mouse_ColMap.png");
		RenderPtr->ColorOptionValue.MulColor.a = 0.7f;
	}
}

void Mouse_ColMap::Update(float _DeltaTime)
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
#include "PrecompileHeader.h"
#include "Dragon_ColMap.h"

Dragon_ColMap::Dragon_ColMap() 
{
}

Dragon_ColMap::~Dragon_ColMap() 
{
}

void Dragon_ColMap::Start()
{
	if (nullptr == GameEngineTexture::Find("Dragon_ColMap.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("2_Grim_Matchstick");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Dragon_ColMap.png").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->SetScaleToTexture("Dragon_ColMap.png");
		RenderPtr->ColorOptionValue.MulColor.a = 0.7f;
	}
}

void Dragon_ColMap::Update(float _DeltaTime)
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
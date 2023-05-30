#include "PrecompileHeader.h"
#include "Frog_ColMap.h"

Frog_ColMap::Frog_ColMap() 
{
}

Frog_ColMap::~Frog_ColMap() 
{
}

void Frog_ColMap::Start()
{
	if (nullptr == GameEngineTexture::Find("Frog_ColMap.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("1_Ribby_and_Croaks");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Frog_ColMap.png").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->SetScaleToTexture("Frog_ColMap.png");
		RenderPtr->ColorOptionValue.MulColor.a = 0.7f;
	}
}

void Frog_ColMap::Update(float _DeltaTime)
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
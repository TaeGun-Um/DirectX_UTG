#include "PrecompileHeader.h"
#include "MDHR_Logo.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

MDHR_Logo* MDHR_Logo::LogoPtr = nullptr;
bool MDHR_Logo::IsEnd = false;

MDHR_Logo::MDHR_Logo() 
{
	LogoPtr = this;
}

MDHR_Logo::~MDHR_Logo() 
{
}

void MDHR_Logo::Start()
{
	if (nullptr == GameEngineSprite::Find("MDHR_Logo"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Opening1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MDHR_Logo").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "MDHR_Logo", .SpriteName = "MDHR_Logo", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("MDHR_Logo");
	}
}

void MDHR_Logo::Update(float _DeltaTime)
{
	if (99 == RenderPtr->GetCurrentFrame())
	{
		RenderPtr->ColorOptionValue.MulColor.a -= _DeltaTime * 1.5f;

		IsEnd = true;

		if (RenderPtr->ColorOptionValue.MulColor.a <= 0.0f)
		{
			Death();
		}
	}
}
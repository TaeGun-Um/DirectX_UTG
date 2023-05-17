#include "PrecompileHeader.h"
#include "HitSFX.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

HitSFX::HitSFX() 
{
}

HitSFX::~HitSFX() 
{
}

void HitSFX::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "HitSFX", .SpriteName = "HitSFX", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("HitSFX");
	}
}

void HitSFX::Update(float _DeltaTime)
{
	DeathCheck();
}

void HitSFX::DeathCheck()
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		Death();
	}
}
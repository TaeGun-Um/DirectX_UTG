#include "PrecompileHeader.h"
#include "EXDust.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

EXDust::EXDust() 
{
}

EXDust::~EXDust() 
{
}

void EXDust::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

	RenderPtr->CreateAnimation({ .AnimationName = "EXDust", .SpriteName = "EXDust", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

	RenderPtr->ChangeAnimation("EXDust");
}

void EXDust::Update(float _DeltaTime)
{
	DeathCheck();
}

void EXDust::DeathCheck()
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		Death();
	}
}
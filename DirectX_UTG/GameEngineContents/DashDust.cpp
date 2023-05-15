#include "PrecompileHeader.h"
#include "DashDust.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

DashDust::DashDust() 
{
}

DashDust::~DashDust() 
{
}

void DashDust::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "DashDust", .SpriteName = "DashDust", .FrameInter = 0.05f, .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("DashDust");
	}
}

void DashDust::Update(float _DeltaTime)
{
	DeathCheck();
}

void DashDust::DeathCheck()
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		Death();
	}
}
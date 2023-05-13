#include "PrecompileHeader.h"
#include "LandDust.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

LandDust::LandDust() 
{
}

LandDust::~LandDust() 
{
}

void LandDust::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

	RenderPtr->CreateAnimation({ .AnimationName = "JumpDust", .SpriteName = "JumpDust", .FrameInter = 0.05f, .ScaleToTexture = true });

	//RenderPtr->GetTransform()->SetLocalScale({100, 100});
	RenderPtr->ChangeAnimation("JumpDust");
}

void LandDust::Update(float _DeltaTime)
{
	DeathCheck();
}

void LandDust::DeathCheck()
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		IsDeath = true;
		Death();
	}
}
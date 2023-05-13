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
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

	RenderPtr->CreateAnimation({ .AnimationName = "DashDust", .SpriteName = "DashDust", .FrameInter = 0.05f, .ScaleToTexture = true });

	//RenderPtr->GetTransform()->SetLocalScale({100, 100});
	RenderPtr->ChangeAnimation("DashDust");
}

void DashDust::Update(float _DeltaTime)
{
	DeathCheck();
}

void DashDust::DeathCheck()
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		IsDeath = true;
		Death();
	}
}
#include "PrecompileHeader.h"
#include "ParryEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

ParryEffect::ParryEffect() 
{
}

ParryEffect::~ParryEffect() 
{
}

void ParryEffect::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

	RenderPtr->CreateAnimation({ .AnimationName = "ParryEffect", .SpriteName = "ParryEffect", .FrameInter = 0.05f, .ScaleToTexture = true });

	//RenderPtr->GetTransform()->SetLocalScale({100, 100});
	RenderPtr->ChangeAnimation("ParryEffect");
}

void ParryEffect::Update(float _DeltaTime)
{
	DeathCheck();
}

void ParryEffect::DeathCheck()
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		IsDeath = true;
		Death();
	}
}
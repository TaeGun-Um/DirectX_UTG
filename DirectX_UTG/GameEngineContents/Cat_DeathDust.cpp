#include "PrecompileHeader.h"
#include "Cat_DeathDust.h"
#include "CanExplosion_SFX.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Cat_DeathDust::Cat_DeathDust() 
{
}

Cat_DeathDust::~Cat_DeathDust() 
{
}

void Cat_DeathDust::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Cat_Death_SFX", .SpriteName = "Cat_Death_SFX", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Cat_Death_SFX");
	}
}

void Cat_DeathDust::Update(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		Death();
	}
}
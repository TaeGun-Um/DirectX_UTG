#include "PrecompileHeader.h"
#include "CanExplosion_SFX.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

CanExplosion_SFX::CanExplosion_SFX() 
{
}

CanExplosion_SFX::~CanExplosion_SFX() 
{
}

void CanExplosion_SFX::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Can_Explosion_SFX", .SpriteName = "Can_Explosion_SFX", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Can_Explosion_SFX");
	}
}

void CanExplosion_SFX::Update(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		Death();
	}
}
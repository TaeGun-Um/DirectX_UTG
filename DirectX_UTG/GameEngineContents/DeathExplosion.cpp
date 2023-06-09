#include "PrecompileHeader.h"
#include "DeathExplosion.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

DeathExplosion::DeathExplosion() 
{
}

DeathExplosion::~DeathExplosion() 
{
}

void DeathExplosion::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Explosion", .SpriteName = "Explosion", .FrameInter = 0.07f, .Loop = false });
		RenderPtr->GetTransform()->SetLocalScale({ 450, 450, 1 });

		RenderPtr->ChangeAnimation("Explosion");
	}
}

void DeathExplosion::Update(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		Death();
	}
}
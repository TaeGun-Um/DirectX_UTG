#include "PrecompileHeader.h"
#include "FistAttack_SFX.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

FistAttack_SFX::FistAttack_SFX() 
{
}

FistAttack_SFX::~FistAttack_SFX() 
{
}

void FistAttack_SFX::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "Spark", .SpriteName = "Spark", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("Spark");
	}
}

void FistAttack_SFX::Update(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		Death();
	}
}
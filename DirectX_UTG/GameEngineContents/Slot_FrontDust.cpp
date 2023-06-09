#include "PrecompileHeader.h"
#include "Slot_FrontDust.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Slot_FrontDust::Slot_FrontDust() 
{
}

Slot_FrontDust::~Slot_FrontDust() 
{
}

void Slot_FrontDust::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "Slot_Dust_Front", .SpriteName = "Slot_Dust_Front", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("Slot_Dust_Front");
	}
}

void Slot_FrontDust::Update(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		Death();
	}
}
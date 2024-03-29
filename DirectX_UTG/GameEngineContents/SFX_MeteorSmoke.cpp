#include "PrecompileHeader.h"
#include "SFX_MeteorSmoke.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "DragonLevel.h"
#include "You_Died.h"

SFX_MeteorSmoke::SFX_MeteorSmoke() 
{
}

SFX_MeteorSmoke::~SFX_MeteorSmoke() 
{
}

void SFX_MeteorSmoke::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "SFX_MeteorSmoke", .SpriteName = "SFX_MeteorSmoke", .FrameInter = 0.04f, .Loop = false , .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("SFX_MeteorSmoke");
	}
}

void SFX_MeteorSmoke::Update(float _DeltaTime)
{
	if (true == DragonLevel::DragonLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	if (true == RenderPtr->IsAnimationEnd())
	{
		Death();
	}
}
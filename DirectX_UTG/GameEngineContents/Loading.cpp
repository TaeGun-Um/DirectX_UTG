#include "PrecompileHeader.h"
#include "Loading.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Loading::Loading() 
{
}

Loading::~Loading() 
{
}

void Loading::SetLoadingPtrOn()
{
	RenderPtr->On();
}

void Loading::SetLoadingPtrOff()
{
	RenderPtr->Off();
}

void Loading::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->SetScaleToTexture("Loading.png");
		RenderPtr->Off();
	}
}

void Loading::Update(float _DeltaTime)
{

}

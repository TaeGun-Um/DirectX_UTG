#include "PrecompileHeader.h"
#include "Loading.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

Loading::Loading() 
{
}

Loading::~Loading() 
{
}

void Loading::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineUIRenderer>();
		RenderPtr->SetScaleToTexture("BlackBox.png");
	}

	if (nullptr == GlassRenderPtr)
	{
		GlassRenderPtr = CreateComponent<GameEngineUIRenderer>();
		GlassRenderPtr->CreateAnimation({ .AnimationName = "HOURGLASS", .SpriteName = "HOURGLASS", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		GlassRenderPtr->GetTransform()->AddLocalPosition({480, -150, -10});
		GlassRenderPtr->ChangeAnimation("HOURGLASS");
		
		GlassRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
		GlassRenderPtr->Off();
	}
}

void Loading::Update(float _DeltaTime)
{
	FadeIn(_DeltaTime);
	FadeOut(_DeltaTime);
}

void Loading::FadeIn(float _DeltaTime)
{
	if (false == IsStart || true == IsOutro)
	{
		return;
	}
	else
	{
		GlassRenderPtr->On();
	}

	if (1.0f > GlassRenderPtr->ColorOptionValue.MulColor.a)
	{
		GlassRenderPtr->ColorOptionValue.MulColor.a += _DeltaTime;
	}
	else if (1.0f <= GlassRenderPtr->ColorOptionValue.MulColor.a)
	{
		GlassRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
	}
}

void Loading::FadeOut(float _DeltaTime)
{
	if (false == IsOutro)
	{
		return;
	}

	if (0.0f < GlassRenderPtr->ColorOptionValue.MulColor.a)
	{
		GlassRenderPtr->ColorOptionValue.MulColor.a -= _DeltaTime;
	}
	else if (0.0f >= GlassRenderPtr->ColorOptionValue.MulColor.a)
	{
		GlassRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
		GlassRenderPtr->Off();

		IsEnd = true;
	}
}
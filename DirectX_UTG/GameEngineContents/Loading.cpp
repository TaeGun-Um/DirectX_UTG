#include "PrecompileHeader.h"
#include "Loading.h"

#include <GameEnginePlatform/GameEngineInput.h>       // Å×½ºÆ® ÀÎÇ²
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

Loading::Loading() 
{
}

Loading::~Loading() 
{
}

void Loading::SetLoadingPtrOn()
{
	RenderPtr->On();
	GlassRenderPtr->On();
}

void Loading::SetLoadingPtrOff()
{
	RenderPtr->Off();
	GlassRenderPtr->Off();
}

void Loading::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineUIRenderer>();
		RenderPtr->SetScaleToTexture("Loading.png");
		//RenderPtr->GetTransform()->AddLocalPosition({ 0, 0, -100 });
		RenderPtr->Off();
	}

	if (nullptr == GlassRenderPtr)
	{
		GlassRenderPtr = CreateComponent<GameEngineUIRenderer>();
		GlassRenderPtr->CreateAnimation({ .AnimationName = "HOURGLASS", .SpriteName = "HOURGLASS", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		GlassRenderPtr->GetTransform()->AddLocalPosition({470, -150, -10});
		GlassRenderPtr->ChangeAnimation("HOURGLASS");
		
		//GlassRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
		//GlassRenderPtr->Off();
	}
}

void Loading::Update(float _DeltaTime)
{
	// Å×½ºÆ® ÀÎÇ²
	if (true == GameEngineInput::IsDown("Test"))
	{
		IsStart = true;
	}

	if (true == GameEngineInput::IsDown("Attack"))
	{
		IsEnd = true;
	}
	//

	FadeIn(_DeltaTime);
	FadeOut(_DeltaTime);
}

void Loading::FadeIn(float _DeltaTime)
{
	if (false == IsStart || true == IsEnd)
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
	if (false == IsEnd)
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

		IsStart = false;
		IsEnd = false;
	}
}
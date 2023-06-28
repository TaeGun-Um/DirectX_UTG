#include "PrecompileHeader.h"
#include "HourGlass.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

HourGlass::HourGlass() 
{
}

HourGlass::~HourGlass() 
{
}

void HourGlass::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "HOURGLASS", .SpriteName = "HOURGLASS", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("HOURGLASS");
		RenderPtr->ColorOptionValue.MulColor.a = 0.0f;
		RenderPtr->Off();
	}
}

void HourGlass::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("Test"))
	{
		IsStart = true;
	}

	if (true == GameEngineInput::IsDown("Attack"))
	{
		IsEnd = true;
	}

	FadeIn(_DeltaTime);
	FadeOut(_DeltaTime);
}

void HourGlass::FadeIn(float _DeltaTime)
{
	if (false == IsStart || true == IsEnd)
	{
		return;
	}
	else
	{
		RenderPtr->On();
	}

	if (1.0f > RenderPtr->ColorOptionValue.MulColor.a)
	{
		RenderPtr->ColorOptionValue.MulColor.a += _DeltaTime;
	}
	else if (1.0f <= RenderPtr->ColorOptionValue.MulColor.a)
	{
		RenderPtr->ColorOptionValue.MulColor.a = 1.0f;
	}
}

void HourGlass::FadeOut(float _DeltaTime)
{
	if (false == IsEnd)
	{
		return;
	}

	if (0.0f < RenderPtr->ColorOptionValue.MulColor.a)
	{
		RenderPtr->ColorOptionValue.MulColor.a -= _DeltaTime;
	}
	else if (0.0f >= RenderPtr->ColorOptionValue.MulColor.a)
	{
		RenderPtr->ColorOptionValue.MulColor.a = 0.0f;
		RenderPtr->Off();

		IsStart = false;
		IsEnd = false;
	}
}
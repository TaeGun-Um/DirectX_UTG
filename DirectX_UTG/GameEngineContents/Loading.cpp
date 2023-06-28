#include "PrecompileHeader.h"
#include "Loading.h"

#include <GameEnginePlatform/GameEngineInput.h>       // �׽�Ʈ ��ǲ
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
}

void Loading::SetLoadingPtrOff()
{
	RenderPtr->Off();
}

void Loading::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineUIRenderer>();
		RenderPtr->SetScaleToTexture("Loading.png");
		RenderPtr->Off();
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "HOURGLASS", .SpriteName = "HOURGLASS", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("HOURGLASS");
		RenderPtr->ColorOptionValue.MulColor.a = 0.0f;
		RenderPtr->Off();
	}
}

void Loading::Update(float _DeltaTime)
{
	// �׽�Ʈ ��ǲ
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

void Loading::FadeOut(float _DeltaTime)
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
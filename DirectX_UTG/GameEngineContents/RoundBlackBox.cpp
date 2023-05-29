#include "PrecompileHeader.h"
#include "RoundBlackBox.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

RoundBlackBox::RoundBlackBox() 
{
}

RoundBlackBox::~RoundBlackBox() 
{
}

void RoundBlackBox::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineUIRenderer>();
		RenderPtr->GetTransform()->SetLocalScale({1300, 735});
		RenderPtr->CreateAnimation({ .AnimationName = "Enter", .SpriteName = "Enter", .FrameInter = 0.05f, .Loop = false});
		RenderPtr->CreateAnimation({ .AnimationName = "Exit", .SpriteName = "Exit", .FrameInter = 0.05f, .Loop = false });

		RenderPtr->ChangeAnimation("Enter");
		RenderPtr->Off();
	}
}

void RoundBlackBox::Update(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		IsEnd = true;
	}
}
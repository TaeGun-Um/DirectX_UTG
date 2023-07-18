#include "PrecompileHeader.h"
#include "BookEndRender.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

BookEndRender* BookEndRender::BookEndRenderPtr = nullptr;
bool BookEndRender::IsEnd = false;

BookEndRender::BookEndRender() 
{
}

BookEndRender::~BookEndRender() 
{
}

void BookEndRender::HBSCControl(std::shared_ptr<class GameEngineSpriteRenderer> _Object, float _saturation, float _brightness, float _contrast)
{
	float4 OriginColor = _Object->ColorOptionValue.MulColor;
	float4 ControlColor = float4::Zero;

	ControlColor.r = OriginColor.r;
	ControlColor.g = _saturation;
	ControlColor.b = _brightness;
	ControlColor.a = _contrast;

	_Object->ColorOptionValue.HBSCColor = ControlColor;
}

void BookEndRender::Start()
{
	if (false == GameEngineInput::IsKey("Next"))
	{
		GameEngineInput::CreateKey("Next", 'Z');
	}

	if (nullptr == GameEngineSprite::Find("Page_12-13"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Ending");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_12-13").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_13-14").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_14-15").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_15-16").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_16-17").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_17-18").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_18-End").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Arrow"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("TextBox");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Arrow").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "Page_12-13", .SpriteName = "Page_12-13", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Page_13-14", .SpriteName = "Page_13-14", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Page_14-15", .SpriteName = "Page_14-15", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Page_15-16", .SpriteName = "Page_15-16", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Page_16-17", .SpriteName = "Page_16-17", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Page_17-18", .SpriteName = "Page_17-18", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Page_18-End", .SpriteName = "Page_18-End", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("Page_12-13");
	}

	if (nullptr == ArrowRenderPtr)
	{
		ArrowRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ArrowRenderPtr->GetTransform()->SetLocalPosition({ 480, -310 });
		ArrowRenderPtr->CreateAnimation({ .AnimationName = "Arrow", .SpriteName = "Arrow", .FrameInter = 0.1f, .Loop = true, .ScaleToTexture = true });
		ArrowRenderPtr->ChangeAnimation("Arrow");
		ArrowRenderPtr->ColorOptionValue.MulColor.a = 0.8f;
		ArrowRenderPtr->Off();
	}

	HBSCControl(RenderPtr, 0.5f, 0.6f, 0.5f);
}
void BookEndRender::Update(float _DeltaTime)
{
	if (true == RenderPtr->FindAnimation("Page_12-13")->IsEnd() && 0 == Page)
	{
		ArrowRenderPtr->On();

		if (true == GameEngineInput::IsDown("Next"))
		{
			ArrowRenderPtr->Off();
			++Page;
			RenderPtr->ChangeAnimation("Page_13-14");
		}
	}

	if (true == RenderPtr->FindAnimation("Page_13-14")->IsEnd() && 1 == Page)
	{
		ArrowRenderPtr->On();

		if (true == GameEngineInput::IsDown("Next"))
		{
			ArrowRenderPtr->Off();
			++Page;
			RenderPtr->ChangeAnimation("Page_14-15");
		}
	}

	if (true == RenderPtr->FindAnimation("Page_14-15")->IsEnd() && 2 == Page)
	{
		ArrowRenderPtr->On();

		if (true == GameEngineInput::IsDown("Next"))
		{
			ArrowRenderPtr->Off();
			++Page;
			RenderPtr->ChangeAnimation("Page_15-16");
		}
	}

	if (true == RenderPtr->FindAnimation("Page_15-16")->IsEnd() && 3 == Page)
	{
		ArrowRenderPtr->On();

		if (true == GameEngineInput::IsDown("Next"))
		{
			ArrowRenderPtr->Off();
			++Page;
			RenderPtr->ChangeAnimation("Page_16-17");
		}
	}

	if (true == RenderPtr->FindAnimation("Page_16-17")->IsEnd() && 4 == Page)
	{
		ArrowRenderPtr->On();

		if (true == GameEngineInput::IsDown("Next"))
		{
			ArrowRenderPtr->Off();
			++Page;
			RenderPtr->ChangeAnimation("Page_17-18");
		}
	}

	if (true == RenderPtr->FindAnimation("Page_17-18")->IsEnd() && 5 == Page)
	{
		ArrowRenderPtr->On();

		if (true == GameEngineInput::IsDown("Next"))
		{
			ArrowRenderPtr->Off();
			++Page;
			RenderPtr->ChangeAnimation("Page_18-End");
		}
	}

	if (true == RenderPtr->FindAnimation("Page_18-End")->IsEnd() && 6 == Page)
	{
		IsEnd = true;
	}
}

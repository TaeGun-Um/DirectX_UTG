#include "PrecompileHeader.h"
#include "BookRender.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

BookRender* BookRender::BookRenderPtr = nullptr;
bool BookRender::IsEnd = false;

BookRender::BookRender() 
{
	BookRenderPtr = this;
}

BookRender::~BookRender() 
{
}

void BookRender::HBSCControl(std::shared_ptr<class GameEngineSpriteRenderer> _Object, float _saturation, float _brightness, float _contrast)
{
	float4 OriginColor = _Object->ColorOptionValue.MulColor;
	float4 ControlColor = float4::Zero;

	ControlColor.r = OriginColor.r;
	ControlColor.g = _saturation;
	ControlColor.b = _brightness;
	ControlColor.a = _contrast;

	_Object->ColorOptionValue.HBSCColor = ControlColor;
}

void BookRender::Start()
{
	if (false == GameEngineInput::IsKey("Next"))
	{
		GameEngineInput::CreateKey("Next", 'Z');
	}

	if (nullptr == GameEngineSprite::Find("Page_01"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Opening2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_01").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_01-02").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_02-03").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_03-04").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_04-05").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_05-06").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_06-07").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_07-08").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_08-09").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_09-10").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page_10-11").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "Page_01", .SpriteName = "Page_01", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Page_01-02", .SpriteName = "Page_01-02", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Page_02-03", .SpriteName = "Page_02-03", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Page_03-04", .SpriteName = "Page_03-04", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Page_04-05", .SpriteName = "Page_04-05", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Page_05-06", .SpriteName = "Page_05-06", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Page_06-07", .SpriteName = "Page_06-07", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Page_07-08", .SpriteName = "Page_07-08", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Page_08-09", .SpriteName = "Page_08-09", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Page_09-10", .SpriteName = "Page_09-10", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Page_10-11", .SpriteName = "Page_10-11", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("Page_01");
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

	if (nullptr == ArrowRenderPtr)
	{
		ArrowRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ArrowRenderPtr->GetTransform()->SetLocalPosition({480, -310});
		ArrowRenderPtr->CreateAnimation({ .AnimationName = "Arrow", .SpriteName = "Arrow", .FrameInter = 0.1f, .Loop = true, .ScaleToTexture = true });
		ArrowRenderPtr->ChangeAnimation("Arrow");
		ArrowRenderPtr->ColorOptionValue.MulColor.a = 0.8f;
		ArrowRenderPtr->Off();
	}

	HBSCControl(RenderPtr, 0.5f, 0.6f, 0.5f);
}
void BookRender::Update(float _DeltaTime)
{
	if (true == RenderPtr->FindAnimation("Page_01")->IsEnd() && 0 == Page)
	{
		ArrowRenderPtr->On();

		if (true == GameEngineInput::IsDown("Next"))
		{
			ArrowRenderPtr->Off();
			++Page;
			RenderPtr->ChangeAnimation("Page_01-02");
		}
	}

	if (true == RenderPtr->FindAnimation("Page_01-02")->IsEnd() && 1 == Page)
	{
		ArrowRenderPtr->On();

		if (true == GameEngineInput::IsDown("Next"))
		{
			ArrowRenderPtr->Off();
			++Page;
			RenderPtr->ChangeAnimation("Page_02-03");
		}
	}

	if (true == RenderPtr->FindAnimation("Page_02-03")->IsEnd() && 2 == Page)
	{
		ArrowRenderPtr->On();

		if (true == GameEngineInput::IsDown("Next"))
		{
			ArrowRenderPtr->Off();
			++Page;
			RenderPtr->ChangeAnimation("Page_03-04");
		}
	}

	if (true == RenderPtr->FindAnimation("Page_03-04")->IsEnd() && 3 == Page)
	{
		ArrowRenderPtr->On();

		if (true == GameEngineInput::IsDown("Next"))
		{
			ArrowRenderPtr->Off();
			++Page;
			RenderPtr->ChangeAnimation("Page_04-05");
		}
	}

	if (true == RenderPtr->FindAnimation("Page_04-05")->IsEnd() && 4 == Page)
	{
		ArrowRenderPtr->On();

		if (true == GameEngineInput::IsDown("Next"))
		{
			ArrowRenderPtr->Off();
			++Page;
			RenderPtr->ChangeAnimation("Page_05-06");
		}
	}

	if (true == RenderPtr->FindAnimation("Page_05-06")->IsEnd() && 5 == Page)
	{
		ArrowRenderPtr->On();

		if (true == GameEngineInput::IsDown("Next"))
		{
			ArrowRenderPtr->Off();
			++Page;
			RenderPtr->ChangeAnimation("Page_06-07");
		}
	}

	if (true == RenderPtr->FindAnimation("Page_06-07")->IsEnd() && 6 == Page)
	{
		ArrowRenderPtr->On();

		if (true == GameEngineInput::IsDown("Next"))
		{
			ArrowRenderPtr->Off();
			++Page;
			RenderPtr->ChangeAnimation("Page_07-08");
		}
	}

	if (true == RenderPtr->FindAnimation("Page_07-08")->IsEnd() && 7 == Page)
	{
		ArrowRenderPtr->On();

		if (true == GameEngineInput::IsDown("Next"))
		{
			ArrowRenderPtr->Off();
			++Page;
			RenderPtr->ChangeAnimation("Page_08-09");
		}
	}

	if (true == RenderPtr->FindAnimation("Page_08-09")->IsEnd() && 8 == Page)
	{
		ArrowRenderPtr->On();

		if (true == GameEngineInput::IsDown("Next"))
		{
			ArrowRenderPtr->Off();
			++Page;
			RenderPtr->ChangeAnimation("Page_09-10");
		}
	}

	if (true == RenderPtr->FindAnimation("Page_09-10")->IsEnd() && 9 == Page)
	{
		ArrowRenderPtr->On();

		if (true == GameEngineInput::IsDown("Next"))
		{
			ArrowRenderPtr->Off();
			++Page;
			RenderPtr->ChangeAnimation("Page_10-11");
		}
	}

	if (true == RenderPtr->FindAnimation("Page_10-11")->IsEnd() && 10 == Page)
	{
		ArrowRenderPtr->On();

		if (true == GameEngineInput::IsDown("Next"))
		{
			ArrowRenderPtr->Off();
			IsEnd = true;
		}
	}
}

#include "PrecompileHeader.h"
#include "NPC_TextBox.h"

#include <GameEngineCore/GameEngineFontRenderer.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

NPC_TextBox::NPC_TextBox() 
{
}

NPC_TextBox::~NPC_TextBox() 
{
}

void NPC_TextBox::Start()
{
	TextBoxInitSetting();
}

void NPC_TextBox::Update(float _DeltaTime)
{

}

void NPC_TextBox::BoxReset()
{
	IsDown = false;
	IsEnd = false;
}

bool NPC_TextBox::RenderAlphaSetting(std::shared_ptr<GameEngineFontRenderer> _FontRender, float _DeltaTime)
{
	if (false == IsDown)
	{
		BoxRenderPtr->ColorOptionValue.MulColor.a -= _DeltaTime * 15.0f;
		TailRenderPtr->ColorOptionValue.MulColor.a -= _DeltaTime * 15.0f;
		ArrowRenderPtr->ColorOptionValue.MulColor.a -= _DeltaTime * 15.0f;
		_FontRender->AddAlphaColor(-_DeltaTime * 15.0f);

		if (BoxRenderPtr->ColorOptionValue.MulColor.a <= 0.0f)
		{
			IsDown = true;
			BoxRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
			TailRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
			ArrowRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
			_FontRender->SetAlphaColor(0.0f);
		}
	}
	else
	{
		BoxRenderPtr->ColorOptionValue.MulColor.a += _DeltaTime * 15.0f;
		TailRenderPtr->ColorOptionValue.MulColor.a += _DeltaTime * 15.0f;
		ArrowRenderPtr->ColorOptionValue.MulColor.a += _DeltaTime * 15.0f;
		_FontRender->AddAlphaColor(_DeltaTime * 15.0f);

		if (BoxRenderPtr->ColorOptionValue.MulColor.a >= 1.0f)
		{
			IsEnd = true;
			BoxRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
			TailRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
			ArrowRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
			_FontRender->SetAlphaColor(1.0f);
		}
	}

	return IsEnd;
}

void NPC_TextBox::TextBoxInitSetting()
{
	if (nullptr == GameEngineTexture::Find("speech_bubble_box.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("TextBox");

		GameEngineTexture::Load(NewDir.GetPlusFileName("speech_bubble_box.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("speech_balloon_tail_0001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("speech_balloon_tail_0004.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("speech_balloon_tail_0009.png").GetFullPath());
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

	BoxRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	TailRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	ArrowRenderPtr = CreateComponent<GameEngineSpriteRenderer>();

	BoxRenderPtr->SetTexture("speech_bubble_box.png");
	BoxRenderPtr->GetTransform()->SetLocalScale({400, 130});

	TailRenderPtr->SetTexture("speech_balloon_tail_0004.png");
	TailRenderPtr->GetTransform()->SetLocalScale({ 50, 40 });

	ArrowRenderPtr->CreateAnimation({ .AnimationName = "Arrow", .SpriteName = "Arrow", .FrameInter = 0.1f, .Loop = true, .ScaleToTexture = true });
	ArrowRenderPtr->ChangeAnimation("Arrow");
}
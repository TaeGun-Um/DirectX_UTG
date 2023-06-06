#include "PrecompileHeader.h"
#include "NPC_TextBox.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

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

	BoxRenderPtr = CreateComponent<GameEngineUIRenderer>();
	TailRenderPtr = CreateComponent<GameEngineUIRenderer>();
	ArrowRenderPtr = CreateComponent<GameEngineUIRenderer>();

	BoxRenderPtr->SetTexture("speech_bubble_box.png");
	BoxRenderPtr->GetTransform()->SetLocalScale({400, 200});

	TailRenderPtr->SetScaleToTexture("speech_balloon_tail_0001.png");

	ArrowRenderPtr->CreateAnimation({ .AnimationName = "Arrow", .SpriteName = "Arrow", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
}
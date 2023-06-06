#include "PrecompileHeader.h"
#include "Stage_Title.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

Stage_Title::Stage_Title() 
{
}

Stage_Title::~Stage_Title() 
{
}

void Stage_Title::TitleWordSetting(CardValue _CV)
{
	CV = _CV;

	switch (CV)
	{
	case CardValue::Tutorial_Fly:
	{
		WordRenderPtr->ChangeAnimation("Frog");
	}
	break;
	case CardValue::Mouse:
	{
		WordRenderPtr->ChangeAnimation("Mouse");
	}
	break;
	case CardValue::Frog:
	{
		WordRenderPtr->ChangeAnimation("Frog");
	}
	break;
	case CardValue::Dragon:
	{
		WordRenderPtr->ChangeAnimation("Dragon");
	}
	break;
	case CardValue::Zeplin:
	{
		WordRenderPtr->ChangeAnimation("Zeplin");
	}
	break;
	case CardValue::Djimmi:
	{
		WordRenderPtr->ChangeAnimation("Djimmi");
	}
	break;
	case CardValue::Unknown:
	{
		MsgAssert("Card Value가 Unknown입니다. Value를 설정하세요.");
		return;
	}
	break;
	default:
		break;
	}
}

void Stage_Title::BoxPositionReset()
{
	BoxRender->GetTransform()->SetLocalPosition(YesPosition);
	SelectInt = 0;
}

void Stage_Title::Start()
{
	if (nullptr == GameEngineTexture::Find("TitleCard_Back.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Stage_Title");

		GameEngineTexture::Load(NewDir.GetPlusFileName("TitleCard_Back.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("TitleCard_Title.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("INS.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("AND.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Logo.png").GetFullPath());

		GameEngineTexture::Load(NewDir.GetPlusFileName("CONFIRM_BACK.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Wouldyou.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Yes.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("No.png").GetFullPath());

		GameEngineTexture::Load(NewDir.GetPlusFileName("SelectBox.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Title_Card.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Stage_Title");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Title_Card.png").GetFullPath(), 4, 5);
	}

	CardRenderPtr = CreateComponent<GameEngineUIRenderer>();
	BackRenderPtr = CreateComponent<GameEngineUIRenderer>();
	WordRenderPtr = CreateComponent<GameEngineUIRenderer>();
	INSRenderPtr = CreateComponent<GameEngineUIRenderer>();
	ANDRenderPtr = CreateComponent<GameEngineUIRenderer>();
	LOGORenderPtr = CreateComponent<GameEngineUIRenderer>();
	ConfirmRenderPtr = CreateComponent<GameEngineUIRenderer>();
	WouldRenderPtr = CreateComponent<GameEngineUIRenderer>();
	BoxRender = CreateComponent<GameEngineUIRenderer>();
	YesRenderPtr = CreateComponent<GameEngineUIRenderer>();
	NoRenderPtr = CreateComponent<GameEngineUIRenderer>();

	CardRenderPtr->SetScaleToTexture("TitleCard_Back.png");
	BackRenderPtr->SetScaleToTexture("TitleCard_Title.png");
	INSRenderPtr->SetScaleToTexture("INS.png");
	ANDRenderPtr->SetScaleToTexture("AND.png");
	LOGORenderPtr->SetScaleToTexture("Logo.png");
	ConfirmRenderPtr->SetScaleToTexture("CONFIRM_BACK.png");
	WouldRenderPtr->SetScaleToTexture("Wouldyou.png");
	BoxRender->SetScaleToTexture("SelectBox.png");
	YesRenderPtr->SetScaleToTexture("Yes.png");
	NoRenderPtr->SetScaleToTexture("No.png");

	INSRenderPtr->GetTransform()->SetLocalPosition({ 0, 160 });
	ANDRenderPtr->GetTransform()->SetLocalPosition({ 0, -115 });
	LOGORenderPtr->GetTransform()->SetLocalPosition({ 0, -190 });

	ConfirmRenderPtr->GetTransform()->SetLocalPosition({ 500, -330 });
	WouldRenderPtr->GetTransform()->SetLocalPosition({ 0, -75 });
	YesRenderPtr->GetTransform()->SetLocalPosition({ -50, -115 });
	NoRenderPtr->GetTransform()->SetLocalPosition({ 45, -115 });
	BoxRender->GetTransform()->SetLocalPosition({ -50, -115 });

	YesPosition = YesRenderPtr->GetTransform()->GetLocalPosition();
	NoPosition = NoRenderPtr->GetTransform()->GetLocalPosition();

	YesRenderPtr->ColorOptionValue.MulColor.a = 0.8f;
	NoRenderPtr->ColorOptionValue.MulColor.a = 0.8f;
	BoxRender->ColorOptionValue.MulColor.a = 0.8f;

	WordRenderPtr->GetTransform()->SetLocalScale({ 781, 572 });
	WordRenderPtr->CreateAnimation({ "Frog", "Title_Card.png", 8, 8, 1.f, false, false });
	WordRenderPtr->CreateAnimation({ "Dragon", "Title_Card.png", 6, 6, 1.f, false, false });
	WordRenderPtr->CreateAnimation({ "Mouse", "Title_Card.png", 12, 12, 1.f, false, false });
	WordRenderPtr->CreateAnimation({ "Djimmi", "Title_Card.png", 9, 9, 1.f, false, false });
	WordRenderPtr->CreateAnimation({ "Zeplin", "Title_Card.png", 3, 3, 1.f, false, false });

	WordRenderPtr->ChangeAnimation("Frog");
}

void Stage_Title::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("MoveRight") && 0 == SelectInt)
	{
		BoxRender->GetTransform()->SetLocalPosition(NoPosition);
		SelectInt = 1;
	}
	else if (true == GameEngineInput::IsDown("MoveLeft") && 0 == SelectInt)
	{
		BoxRender->GetTransform()->SetLocalPosition(NoPosition);
		SelectInt = 1;
	}
	else if (true == GameEngineInput::IsDown("MoveRight") && 1 == SelectInt)
	{
		BoxRender->GetTransform()->SetLocalPosition(YesPosition);
		SelectInt = 0;
	}
	else if (true == GameEngineInput::IsDown("MoveLeft") && 1 == SelectInt)
	{
		BoxRender->GetTransform()->SetLocalPosition(YesPosition);
		SelectInt = 0;
	}
}

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
		WordRenderPtr->Off();
		INSRenderPtr->Off();
		ANDRenderPtr->Off();
		LOGORenderPtr->Off();
		WouldRenderPtr->Off();
		YesRenderPtr->Off();
		NoRenderPtr->Off();

		CardRenderPtr->SetScaleToTexture("TitleCard_Title_Small.png");
		CardMaxScale = CardRenderPtr->GetTransform()->GetLocalScale();
		CardRenderPtr->GetTransform()->SetLocalScale(float4::Zero);

		BoxRender->SetScaleToTexture("EnterSelectBox.png");
		BoxMaxScale = BoxRender->GetTransform()->GetLocalScale();
		BoxRender->GetTransform()->SetLocalScale(float4::Zero);
		BoxRender->ColorOptionValue.MulColor.a = 0.8f;
		BoxEndPosition = float4{ 0, -65 };
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
	OnLogicEnd = false;

	ScaleMaxTime = 0.0f;

	CardRenderPtr->GetTransform()->SetLocalScale(float4::Zero);
	INSRenderPtr->GetTransform()->SetLocalScale(float4::Zero);
	ANDRenderPtr->GetTransform()->SetLocalScale(float4::Zero);
	LOGORenderPtr->GetTransform()->SetLocalScale(float4::Zero);
	WouldRenderPtr->GetTransform()->SetLocalScale(float4::Zero);
	BoxRender->GetTransform()->SetLocalScale(float4::Zero);
	YesRenderPtr->GetTransform()->SetLocalScale(float4::Zero);
	NoRenderPtr->GetTransform()->SetLocalScale(float4::Zero);

	Airplane_OneRenderPtr->GetTransform()->SetLocalScale(float4::Zero);
	Airplane_TwoRenderPtr->GetTransform()->SetLocalScale(float4::Zero);
	EnterRenderPtr->GetTransform()->SetLocalScale(float4::Zero);

	INSRenderPtr->GetTransform()->SetLocalPosition(float4::Zero);
	ANDRenderPtr->GetTransform()->SetLocalPosition(float4::Zero);
	LOGORenderPtr->GetTransform()->SetLocalPosition(float4::Zero);
	WouldRenderPtr->GetTransform()->SetLocalPosition(float4::Zero);
	YesRenderPtr->GetTransform()->SetLocalPosition(float4::Zero);
	NoRenderPtr->GetTransform()->SetLocalPosition(float4::Zero);
	BoxRender->GetTransform()->SetLocalPosition(float4::Zero);

	Airplane_OneRenderPtr->GetTransform()->SetLocalPosition(float4::Zero);
	Airplane_TwoRenderPtr->GetTransform()->SetLocalPosition(float4::Zero);
	EnterRenderPtr->GetTransform()->SetLocalPosition(float4::Zero);

	CardRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
	BackRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
	INSRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
	ANDRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
	LOGORenderPtr->ColorOptionValue.MulColor.a = 0.0f;
	ConfirmRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
	WouldRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
	BoxRender->ColorOptionValue.MulColor.a = 0.0f;
	YesRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
	NoRenderPtr->ColorOptionValue.MulColor.a = 0.0f;

	Airplane_OneRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
	Airplane_TwoRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
	EnterRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
}

void Stage_Title::Start()
{
	BoxInitSetting();
}

void Stage_Title::Update(float _DeltaTime)
{
	if (false == IsUpdate())
	{
		return;
	}

	if (true == IsSmall)
	{
		OnLogic_Small(_DeltaTime);

		if (false == OnLogicEnd)
		{
			return;
		}
	}
	else
	{
		Airplane_OneRenderPtr->Off();
		Airplane_TwoRenderPtr->Off();
		EnterRenderPtr->Off();

		OnLogic(_DeltaTime);

		if (false == OnLogicEnd)
		{
			return;
		}

		if (true == GameEngineInput::IsDown("MoveRight") && 0 == SelectInt)
		{
			BoxRender->GetTransform()->SetLocalPosition(NoEndPosition);
			SelectInt = 1;
		}
		else if (true == GameEngineInput::IsDown("MoveLeft") && 0 == SelectInt)
		{
			BoxRender->GetTransform()->SetLocalPosition(NoEndPosition);
			SelectInt = 1;
		}
		else if (true == GameEngineInput::IsDown("MoveRight") && 1 == SelectInt)
		{
			BoxRender->GetTransform()->SetLocalPosition(YesEndPosition);
			SelectInt = 0;
		}
		else if (true == GameEngineInput::IsDown("MoveLeft") && 1 == SelectInt)
		{
			BoxRender->GetTransform()->SetLocalPosition(YesEndPosition);
			SelectInt = 0;
		}
	}

}

void Stage_Title::OnLogic_Small(float _DeltaTime)
{
	if (true == OnLogicEnd)
	{
		return;
	}

	if (1.0f > CardRenderPtr->ColorOptionValue.MulColor.a)
	{
		CardRenderPtr->ColorOptionValue.MulColor.a += _DeltaTime * 4.f;
		BackRenderPtr->ColorOptionValue.MulColor.a += _DeltaTime * 4.f;
		ConfirmRenderPtr->ColorOptionValue.MulColor.a += _DeltaTime * 4.f;
		BoxRender->ColorOptionValue.MulColor.a += _DeltaTime * 4.f;
		Airplane_OneRenderPtr->ColorOptionValue.MulColor.a += _DeltaTime * 4.f;
		Airplane_TwoRenderPtr->ColorOptionValue.MulColor.a += _DeltaTime * 4.f;
		EnterRenderPtr->ColorOptionValue.MulColor.a += _DeltaTime * 4.f;
	}
	else if (1.0f <= CardRenderPtr->ColorOptionValue.MulColor.a)
	{
		CardRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		BackRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		ConfirmRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		BoxRender->ColorOptionValue.MulColor.a = 0.8f;
		Airplane_OneRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		Airplane_TwoRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		EnterRenderPtr->ColorOptionValue.MulColor.a = 0.8f;
	}

	ScaleMaxTime += _DeltaTime;

	float4 CardScale = float4::LerpClamp(MinScale, CardMaxScale, ScaleMaxTime * 3.f);
	float4 BoxScale = float4::LerpClamp(MinScale, BoxMaxScale, ScaleMaxTime * 3.f);
	float4 Airplane_OneScale = float4::LerpClamp(MinScale, Airplane_OneMaxScale, ScaleMaxTime * 3.f);
	float4 Airplane_TwoScale = float4::LerpClamp(MinScale, Airplane_TwoMaxScale, ScaleMaxTime * 3.f);
	float4 EnterScale = float4::LerpClamp(MinScale, EnterMaxScale, ScaleMaxTime * 3.f);

	CardRenderPtr->GetTransform()->SetLocalScale(CardScale);
	BoxRender->GetTransform()->SetLocalScale(BoxScale);
	Airplane_OneRenderPtr->GetTransform()->SetLocalScale(Airplane_OneScale);
	Airplane_TwoRenderPtr->GetTransform()->SetLocalScale(Airplane_TwoScale);
	EnterRenderPtr->GetTransform()->SetLocalScale(EnterScale);

	float4 BoxPosition = float4::LerpClamp(MinScale, BoxEndPosition, ScaleMaxTime * 3.f);
	float4 Airplane_OnePosition = float4::LerpClamp(MinScale, Airplane_OneEndPosition, ScaleMaxTime * 3.f);
	float4 Airplane_TwoPosition = float4::LerpClamp(MinScale, Airplane_TwoEndPosition, ScaleMaxTime * 3.f);
	float4 EnterPosition = float4::LerpClamp(MinScale, EnterEndPosition, ScaleMaxTime * 3.f);

	BoxRender->GetTransform()->SetLocalPosition(BoxPosition);
	Airplane_OneRenderPtr->GetTransform()->SetLocalPosition(Airplane_OnePosition);
	Airplane_TwoRenderPtr->GetTransform()->SetLocalPosition(Airplane_TwoPosition);
	EnterRenderPtr->GetTransform()->SetLocalPosition(EnterPosition);

	if (CardMaxScale == CardRenderPtr->GetTransform()->GetLocalScale())
	{
		OnLogicEnd = true;

		CardRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		BackRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		ConfirmRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		BoxRender->ColorOptionValue.MulColor.a = 0.8f;
		Airplane_OneRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		Airplane_TwoRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		EnterRenderPtr->ColorOptionValue.MulColor.a = 0.8f;
	}
}

void Stage_Title::OnLogic(float _DeltaTime)
{
	if (true == OnLogicEnd)
	{
		return;
	}

	if (1.0f > CardRenderPtr->ColorOptionValue.MulColor.a)
	{
		CardRenderPtr->ColorOptionValue.MulColor.a += _DeltaTime * 4.f;
		BackRenderPtr->ColorOptionValue.MulColor.a += _DeltaTime * 4.f;
		INSRenderPtr->ColorOptionValue.MulColor.a += _DeltaTime * 4.f;
		ANDRenderPtr->ColorOptionValue.MulColor.a += _DeltaTime * 4.f;
		LOGORenderPtr->ColorOptionValue.MulColor.a += _DeltaTime * 4.f;
		ConfirmRenderPtr->ColorOptionValue.MulColor.a += _DeltaTime * 4.f;
		WouldRenderPtr->ColorOptionValue.MulColor.a += _DeltaTime * 4.f;
		BoxRender->ColorOptionValue.MulColor.a += _DeltaTime * 4.f;
		YesRenderPtr->ColorOptionValue.MulColor.a += _DeltaTime * 4.f;
		NoRenderPtr->ColorOptionValue.MulColor.a += _DeltaTime * 4.f;
	}
	else if (1.0f <= CardRenderPtr->ColorOptionValue.MulColor.a)
	{
		CardRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		BackRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		INSRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		ANDRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		LOGORenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		ConfirmRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		BoxRender->ColorOptionValue.MulColor.a = 0.8f;
		YesRenderPtr->ColorOptionValue.MulColor.a = 0.8f;
		NoRenderPtr->ColorOptionValue.MulColor.a = 0.8f;
	}
	
	ScaleMaxTime += _DeltaTime;

	float4 CardScale = float4::LerpClamp(MinScale, CardMaxScale, ScaleMaxTime * 3.f);
	float4 INSScale = float4::LerpClamp(MinScale, INSMaxScale, ScaleMaxTime * 3.f);
	float4 ANDScale = float4::LerpClamp(MinScale, ANDMaxScale, ScaleMaxTime * 3.f);
	float4 WouldScale = float4::LerpClamp(MinScale, WouldMaxScale, ScaleMaxTime * 3.f);
	float4 BoxScale = float4::LerpClamp(MinScale, BoxMaxScale, ScaleMaxTime * 3.f);
	float4 YesScale = float4::LerpClamp(MinScale, YesMaxScale, ScaleMaxTime * 3.f);
	float4 NoScale = float4::LerpClamp(MinScale, NoMaxScale, ScaleMaxTime * 3.f);
	float4 LOGOScale = float4::LerpClamp(MinScale, LOGOMaxScale, ScaleMaxTime * 3.f);
	float4 WordScale = float4::LerpClamp(MinScale, WordMaxScale, ScaleMaxTime * 3.f);

	CardRenderPtr->GetTransform()->SetLocalScale(CardScale);
	INSRenderPtr->GetTransform()->SetLocalScale(INSScale);
	ANDRenderPtr->GetTransform()->SetLocalScale(ANDScale);
	WouldRenderPtr->GetTransform()->SetLocalScale(WouldScale);
	BoxRender->GetTransform()->SetLocalScale(BoxScale);
	YesRenderPtr->GetTransform()->SetLocalScale(YesScale);
	NoRenderPtr->GetTransform()->SetLocalScale(NoScale);
	LOGORenderPtr->GetTransform()->SetLocalScale(LOGOScale);
	WordRenderPtr->GetTransform()->SetLocalScale(WordScale);

	float4 INSPosition = float4::LerpClamp(MinScale, INSEndPosition, ScaleMaxTime * 3.f);
	float4 ANDPosition = float4::LerpClamp(MinScale, ANDEndPosition, ScaleMaxTime * 3.f);
	float4 WouldPosition = float4::LerpClamp(MinScale, WouldEndPosition, ScaleMaxTime * 3.f);
	float4 BoxPosition = float4::LerpClamp(MinScale, BoxEndPosition, ScaleMaxTime * 3.f);
	float4 YesPosition = float4::LerpClamp(MinScale, YesEndPosition, ScaleMaxTime * 3.f);
	float4 NoPosition = float4::LerpClamp(MinScale, NoEndPosition, ScaleMaxTime * 3.f);
	float4 LOGOPosition = float4::LerpClamp(MinScale, LOGOEndPosition, ScaleMaxTime * 3.f);

	INSRenderPtr->GetTransform()->SetLocalPosition(INSPosition);
	ANDRenderPtr->GetTransform()->SetLocalPosition(ANDPosition);
	WouldRenderPtr->GetTransform()->SetLocalPosition(WouldPosition);
	BoxRender->GetTransform()->SetLocalPosition(BoxPosition);
	YesRenderPtr->GetTransform()->SetLocalPosition(YesPosition);
	NoRenderPtr->GetTransform()->SetLocalPosition(NoPosition);
	LOGORenderPtr->GetTransform()->SetLocalPosition(LOGOPosition);

	if (CardMaxScale == CardRenderPtr->GetTransform()->GetLocalScale())
	{
		OnLogicEnd = true;

		CardRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		BackRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		INSRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		ANDRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		LOGORenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		ConfirmRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		WouldRenderPtr->ColorOptionValue.MulColor.a = 1.0f;
		BoxRender->ColorOptionValue.MulColor.a = 0.8f;
		YesRenderPtr->ColorOptionValue.MulColor.a = 0.8f;
		NoRenderPtr->ColorOptionValue.MulColor.a = 0.8f;
	}
}

void Stage_Title::BoxInitSetting()
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

		GameEngineTexture::Load(NewDir.GetPlusFileName("TitleCard_Title_Small.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Airplane_One.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Airplane_Two.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Enter.png").GetFullPath());

		GameEngineTexture::Load(NewDir.GetPlusFileName("SelectBox.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("EnterSelectBox.png").GetFullPath());
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

	BackRenderPtr = CreateComponent<GameEngineUIRenderer>();
	CardRenderPtr = CreateComponent<GameEngineUIRenderer>();
	WordRenderPtr = CreateComponent<GameEngineUIRenderer>();
	INSRenderPtr = CreateComponent<GameEngineUIRenderer>();
	ANDRenderPtr = CreateComponent<GameEngineUIRenderer>();
	LOGORenderPtr = CreateComponent<GameEngineUIRenderer>();
	ConfirmRenderPtr = CreateComponent<GameEngineUIRenderer>();
	WouldRenderPtr = CreateComponent<GameEngineUIRenderer>();
	BoxRender = CreateComponent<GameEngineUIRenderer>();
	YesRenderPtr = CreateComponent<GameEngineUIRenderer>();
	NoRenderPtr = CreateComponent<GameEngineUIRenderer>();

	Airplane_OneRenderPtr = CreateComponent<GameEngineUIRenderer>();
	Airplane_TwoRenderPtr = CreateComponent<GameEngineUIRenderer>();
	EnterRenderPtr = CreateComponent<GameEngineUIRenderer>();

	CardRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
	BackRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
	INSRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
	ANDRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
	LOGORenderPtr->ColorOptionValue.MulColor.a = 0.0f;
	ConfirmRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
	WouldRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
	BoxRender->ColorOptionValue.MulColor.a = 0.0f;
	YesRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
	NoRenderPtr->ColorOptionValue.MulColor.a = 0.0f;

	Airplane_OneRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
	Airplane_TwoRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
	EnterRenderPtr->ColorOptionValue.MulColor.a = 0.0f;

	CardRenderPtr->SetScaleToTexture("TitleCard_Title.png");
	BackRenderPtr->SetScaleToTexture("TitleCard_Back.png");
	INSRenderPtr->SetScaleToTexture("INS.png");
	ANDRenderPtr->SetScaleToTexture("AND.png");
	LOGORenderPtr->SetScaleToTexture("Logo.png");
	ConfirmRenderPtr->SetScaleToTexture("CONFIRM_BACK.png");
	WouldRenderPtr->SetScaleToTexture("Wouldyou.png");
	BoxRender->SetScaleToTexture("SelectBox.png");
	YesRenderPtr->SetScaleToTexture("Yes.png");
	NoRenderPtr->SetScaleToTexture("No.png");

	Airplane_OneRenderPtr->SetScaleToTexture("Airplane_One.png");
	Airplane_TwoRenderPtr->SetScaleToTexture("Airplane_Two.png");
	EnterRenderPtr->SetScaleToTexture("Enter.png");

	CardMaxScale = CardRenderPtr->GetTransform()->GetLocalScale();
	INSMaxScale = INSRenderPtr->GetTransform()->GetLocalScale();
	ANDMaxScale = ANDRenderPtr->GetTransform()->GetLocalScale();
	LOGOMaxScale = LOGORenderPtr->GetTransform()->GetLocalScale();
	WouldMaxScale = WouldRenderPtr->GetTransform()->GetLocalScale();
	BoxMaxScale = BoxRender->GetTransform()->GetLocalScale();
	YesMaxScale = YesRenderPtr->GetTransform()->GetLocalScale();
	NoMaxScale = NoRenderPtr->GetTransform()->GetLocalScale();

	Airplane_OneMaxScale = Airplane_OneRenderPtr->GetTransform()->GetLocalScale();
	Airplane_TwoMaxScale = Airplane_TwoRenderPtr->GetTransform()->GetLocalScale();
	EnterMaxScale = EnterRenderPtr->GetTransform()->GetLocalScale();

	CardRenderPtr->GetTransform()->SetLocalScale(float4::Zero);
	INSRenderPtr->GetTransform()->SetLocalScale(float4::Zero);
	ANDRenderPtr->GetTransform()->SetLocalScale(float4::Zero);
	LOGORenderPtr->GetTransform()->SetLocalScale(float4::Zero);
	WouldRenderPtr->GetTransform()->SetLocalScale(float4::Zero);
	BoxRender->GetTransform()->SetLocalScale(float4::Zero);
	YesRenderPtr->GetTransform()->SetLocalScale(float4::Zero);
	NoRenderPtr->GetTransform()->SetLocalScale(float4::Zero);

	Airplane_OneRenderPtr->GetTransform()->SetLocalScale(float4::Zero);
	Airplane_TwoRenderPtr->GetTransform()->SetLocalScale(float4::Zero);
	EnterRenderPtr->GetTransform()->SetLocalScale(float4::Zero);

	ConfirmRenderPtr->GetTransform()->SetLocalPosition({ 500, -330 });

	INSEndPosition = float4{ 0, 160 };
	ANDEndPosition = float4{ 0, -115 };
	LOGOEndPosition = float4{ 0, -190 };
	WouldEndPosition = float4{ 0, -75 };
	YesEndPosition = float4{ -50, -115 };
	NoEndPosition = float4{ 45, -115 };
	BoxEndPosition = float4{ -50, -115 };

	Airplane_OneEndPosition = float4{ 0, 70 };
	Airplane_TwoEndPosition = float4{ 0, 0 };
	EnterEndPosition = float4{ 0, -65 };

	YesPosition = YesRenderPtr->GetTransform()->GetLocalPosition();
	NoPosition = NoRenderPtr->GetTransform()->GetLocalPosition();
	EnterPosition = EnterRenderPtr->GetTransform()->GetLocalPosition();

	YesRenderPtr->ColorOptionValue.MulColor.a = 0.8f;
	NoRenderPtr->ColorOptionValue.MulColor.a = 0.8f;
	BoxRender->ColorOptionValue.MulColor.a = 0.8f;
	EnterRenderPtr->ColorOptionValue.MulColor.a = 0.8f;

	WordRenderPtr->GetTransform()->SetLocalScale({ 781, 572 });
	WordRenderPtr->CreateAnimation({ "Frog", "Title_Card.png", 8, 8, 1.f, false, false });
	WordRenderPtr->CreateAnimation({ "Dragon", "Title_Card.png", 6, 6, 1.f, false, false });
	WordRenderPtr->CreateAnimation({ "Mouse", "Title_Card.png", 12, 12, 1.f, false, false });
	WordRenderPtr->CreateAnimation({ "Djimmi", "Title_Card.png", 9, 9, 1.f, false, false });
	WordRenderPtr->CreateAnimation({ "Zeplin", "Title_Card.png", 3, 3, 1.f, false, false });

	WordRenderPtr->ChangeAnimation("Frog");

	WordMaxScale = WordRenderPtr->GetTransform()->GetLocalScale();

	WordRenderPtr->GetTransform()->SetLocalScale(float4::Zero);
}
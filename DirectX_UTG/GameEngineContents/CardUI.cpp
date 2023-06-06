#include "PrecompileHeader.h"
#include "CardUI.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "CardUIRenderer.h"

#include "Player.h"

CardUI::CardUI() 
{
}

CardUI::~CardUI() 
{
}

void CardUI::SetMainPalyer(std::shared_ptr<class Player> _MainPlayer)
{
	MainPlayer = _MainPlayer;
}

void CardUI::CartUIReset()
{
	Stack0 = 0.0f;
	Stack1 = 0.0f;
	Stack2 = 0.0f;
	Stack3 = 0.0f;
	Stack4 = 0.0f;

	CardBackRenderPtr0->On();
	CardBackRenderPtr1->On();
	CardBackRenderPtr2->On();
	CardBackRenderPtr3->On();
	CardBackRenderPtr4->On();

	CardBackRenderPtr0->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.0f);
	CardBackRenderPtr1->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.0f);
	CardBackRenderPtr2->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.0f);
	CardBackRenderPtr3->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.0f);
	CardBackRenderPtr4->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.0f);

	CardFrontRenderPtr0->Off();
	CardFrontRenderPtr1->Off();
	CardFrontRenderPtr2->Off();
	CardFrontRenderPtr3->Off();
	CardFrontRenderPtr4->Off();
}

void CardUI::Start()
{
	if (nullptr == GameEngineSprite::Find("CardUI"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CardUI").GetFullPath());
	}

	CardHeight = static_cast<float>(GameEngineTexture::Find("Card_001.png")->GetHeight());

	CardBackRenderPtr0 = CreateComponent<CardUIRenderer>();
	CardBackRenderPtr1 = CreateComponent<CardUIRenderer>();
	CardBackRenderPtr2 = CreateComponent<CardUIRenderer>();
	CardBackRenderPtr3 = CreateComponent<CardUIRenderer>();
	CardBackRenderPtr4 = CreateComponent<CardUIRenderer>();

	CardFrontRenderPtr0 = CreateComponent<CardUIRenderer>();
	CardFrontRenderPtr1 = CreateComponent<CardUIRenderer>();
	CardFrontRenderPtr2 = CreateComponent<CardUIRenderer>();
	CardFrontRenderPtr3 = CreateComponent<CardUIRenderer>();
	CardFrontRenderPtr4 = CreateComponent<CardUIRenderer>();

	CardFrontRenderPtr0->CreateAnimation({ .AnimationName = "Rotate", .SpriteName = "CardUI", .Start = 0, .End = 5, .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
	CardFrontRenderPtr1->CreateAnimation({ .AnimationName = "Rotate", .SpriteName = "CardUI", .Start = 0, .End = 5, .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
	CardFrontRenderPtr2->CreateAnimation({ .AnimationName = "Rotate", .SpriteName = "CardUI", .Start = 0, .End = 5, .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
	CardFrontRenderPtr3->CreateAnimation({ .AnimationName = "Rotate", .SpriteName = "CardUI", .Start = 0, .End = 5, .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
	CardFrontRenderPtr4->CreateAnimation({ .AnimationName = "Rotate", .SpriteName = "CardUI", .Start = 0, .End = 5, .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });

	CardFrontRenderPtr0->CreateAnimation({ .AnimationName = "Off", .SpriteName = "CardUI", .Start = 0, .End = 0, .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
	CardFrontRenderPtr1->CreateAnimation({ .AnimationName = "Off", .SpriteName = "CardUI", .Start = 0, .End = 0, .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
	CardFrontRenderPtr2->CreateAnimation({ .AnimationName = "Off", .SpriteName = "CardUI", .Start = 0, .End = 0, .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
	CardFrontRenderPtr3->CreateAnimation({ .AnimationName = "Off", .SpriteName = "CardUI", .Start = 0, .End = 0, .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
	CardFrontRenderPtr4->CreateAnimation({ .AnimationName = "Off", .SpriteName = "CardUI", .Start = 0, .End = 0, .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });

	SizeY = 1.0f / (Player::MainPlayer->MaxEXGauge - 1);

	CardBackRenderPtr0->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.0f);
	CardBackRenderPtr1->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.0f);
	CardBackRenderPtr2->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.0f);
	CardBackRenderPtr3->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.0f);
	CardBackRenderPtr4->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.0f);

	CardBackRenderPtr1->GetTransform()->SetLocalPosition({ 20, 0 });
	CardBackRenderPtr2->GetTransform()->SetLocalPosition({ 40, 0 });
	CardBackRenderPtr3->GetTransform()->SetLocalPosition({ 60, 0 });
	CardBackRenderPtr4->GetTransform()->SetLocalPosition({ 80, 0 });

	CardFrontRenderPtr1->GetTransform()->SetLocalPosition({ 20, 0 });
	CardFrontRenderPtr2->GetTransform()->SetLocalPosition({ 40, 0 });
	CardFrontRenderPtr3->GetTransform()->SetLocalPosition({ 60, 0 });
	CardFrontRenderPtr4->GetTransform()->SetLocalPosition({ 80, 0 });

	CardFrontRenderPtr0->Off();
	CardFrontRenderPtr1->Off();
	CardFrontRenderPtr2->Off();
	CardFrontRenderPtr3->Off();
	CardFrontRenderPtr4->Off();
}

void CardUI::Update(float _DeltaTime)
{
	if (true == MainPlayer->IsEXMax)
	{
		float MaxEXGauge = MainPlayer->MaxEXGauge;
		float CurHeight = CardHeight / MaxEXGauge;

		Stack0 = 49;
		Stack1 = 49;
		Stack2 = 49;
		Stack3 = 49;
		Stack4 = 49;

		CardBackRenderPtr0->Off();
		CardBackRenderPtr1->Off();
		CardBackRenderPtr2->Off();
		CardBackRenderPtr3->Off();
		CardBackRenderPtr4->Off();

		CardFrontRenderPtr0->On();
		CardFrontRenderPtr1->On();
		CardFrontRenderPtr2->On();
		CardFrontRenderPtr3->On();
		CardFrontRenderPtr4->On();

		CardFrontRenderPtr0->ChangeAnimation("Rotate", false);
		CardFrontRenderPtr1->ChangeAnimation("Rotate", false);
		CardFrontRenderPtr2->ChangeAnimation("Rotate", false);
		CardFrontRenderPtr3->ChangeAnimation("Rotate", false);
		CardFrontRenderPtr4->ChangeAnimation("Rotate", false);
	}

	int StackCount = MainPlayer->PlayerEXStack;
	float CurGauege = MainPlayer->PlayerEXGauge;

	// ¾ÈµÊ
	if (true == MainPlayer->IsEXUse)
	{
		MainPlayer->IsEXUse = false;

		if (4 == StackCount)
		{
			Stack4 = 0;
			CardFrontRenderPtr4->ChangeAnimation("Off", false);
			CardFrontRenderPtr4->Off();
			CardBackRenderPtr4->On();
			CardBackRenderPtr4->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.0f);
		}
		else if (3 == StackCount)
		{
			CardBackRenderPtr4->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.0f);
			Stack3 = Stack4;
			Stack4 = 0;
			CardFrontRenderPtr3->ChangeAnimation("Off", false);
			CardFrontRenderPtr3->Off();
			CardBackRenderPtr3->On();
			CardBackRenderPtr3->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, SizeY * Stack3);
		}
		else if (2 == StackCount)
		{
			CardBackRenderPtr3->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.0f);
			Stack2 = Stack3;
			Stack3 = 0;
			CardFrontRenderPtr2->ChangeAnimation("Off", false);
			CardFrontRenderPtr2->Off();
			CardBackRenderPtr2->On();
			CardBackRenderPtr2->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, SizeY * Stack2);
		}
		else if (1 == StackCount)
		{
			CardBackRenderPtr2->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.0f);
			Stack1 = Stack2;
			Stack2 = 0;
			CardFrontRenderPtr1->ChangeAnimation("Off", false);
			CardFrontRenderPtr1->Off();
			CardBackRenderPtr1->On();
			CardBackRenderPtr1->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, SizeY * Stack1);
		}
		else if (0 == StackCount)
		{
			CardBackRenderPtr1->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.0f);
			Stack0 = Stack1;
			Stack1 = 0;
			CardFrontRenderPtr0->ChangeAnimation("Off", false);
			CardFrontRenderPtr0->Off();
			CardBackRenderPtr0->On();
			CardBackRenderPtr0->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, SizeY * Stack0);
		}

		return;
	}

	if (0 == StackCount)
	{
		if (49.0f > Stack0)
		{
			Stack0 = CurGauege;
			CardBackRenderPtr0->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, SizeY * Stack0);
		}
	}

	if (1 == StackCount)
	{
		Stack0 = 49;
		CardBackRenderPtr0->Off();
		CardFrontRenderPtr0->On();
		CardFrontRenderPtr0->ChangeAnimation("Rotate", false);

		if (49.0f > Stack1)
		{
			Stack1 = CurGauege;
			CardBackRenderPtr1->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, SizeY * Stack1);
		}
	}

	if (2 == StackCount)
	{
		Stack1 = 49;
		CardBackRenderPtr1->Off();
		CardFrontRenderPtr1->On();
		CardFrontRenderPtr1->ChangeAnimation("Rotate", false);

		if (49.0f > Stack2)
		{
			Stack2 = CurGauege;
			CardBackRenderPtr2->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, SizeY * Stack2);
		}
	}

	if (3 == StackCount)
	{
		Stack2 = 49;
		CardBackRenderPtr2->Off();
		CardFrontRenderPtr2->On();
		CardFrontRenderPtr2->ChangeAnimation("Rotate", false);

		if (49.0f > Stack3)
		{
			Stack3 = CurGauege;
			CardBackRenderPtr3->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, SizeY * Stack3);
		}
	}

	if (4 == StackCount)
	{
		Stack3 = 49;
		CardBackRenderPtr3->Off();
		CardFrontRenderPtr3->On();
		CardFrontRenderPtr3->ChangeAnimation("Rotate", false);

		if (49.0f > Stack4)
		{
			Stack4 = CurGauege;
			CardBackRenderPtr4->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, SizeY * Stack4);
		}
	}

	if (5 == StackCount)
	{
		Stack4 = 49;
		CardBackRenderPtr4->Off();
		CardFrontRenderPtr4->On();
		CardFrontRenderPtr4->ChangeAnimation("Rotate", false);
	}

	float MaxEXGauge = MainPlayer->MaxEXGauge;
	float CurHeight = CardHeight / MaxEXGauge;

	CardBackRenderPtr0->GetTransform()->SetLocalPosition({ 0 , (Stack0 * CurHeight) / 2 });
	CardFrontRenderPtr0->GetTransform()->SetLocalPosition({ 0 , (Stack0 * CurHeight) / 2 });

	CardBackRenderPtr1->GetTransform()->SetLocalPosition({ 20 , (Stack1 * CurHeight) / 2 });
	CardFrontRenderPtr1->GetTransform()->SetLocalPosition({ 20 , (Stack1 * CurHeight) / 2 });

	CardBackRenderPtr2->GetTransform()->SetLocalPosition({ 40 , (Stack2 * CurHeight) / 2 });
	CardFrontRenderPtr2->GetTransform()->SetLocalPosition({ 40 , (Stack2 * CurHeight) / 2 });

	CardBackRenderPtr3->GetTransform()->SetLocalPosition({ 60 , (Stack3 * CurHeight) / 2 });
	CardFrontRenderPtr3->GetTransform()->SetLocalPosition({ 60 , (Stack3 * CurHeight) / 2 });

	CardBackRenderPtr4->GetTransform()->SetLocalPosition({ 80 , (Stack4 * CurHeight) / 2 });
	CardFrontRenderPtr4->GetTransform()->SetLocalPosition({ 80 , (Stack4 * CurHeight) / 2 });
}

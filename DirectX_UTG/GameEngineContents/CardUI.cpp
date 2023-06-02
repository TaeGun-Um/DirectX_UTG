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

		NewDir.Move("CardUI");

		//GameEngineTexture::Load(NewDir.GetPlusFileName("Card_001.png").GetFullPath());
	}

	CardRenderPtr0 = CreateComponent<CardUIRenderer>();
	CardRenderPtr1 = CreateComponent<CardUIRenderer>();
	CardRenderPtr2 = CreateComponent<CardUIRenderer>();
	CardRenderPtr3 = CreateComponent<CardUIRenderer>();
	CardRenderPtr4 = CreateComponent<CardUIRenderer>();

	CardRenderPtr0->SetScaleToTexture("Card_001.png");
	CardRenderPtr1->SetScaleToTexture("Card_001.png");
	CardRenderPtr2->SetScaleToTexture("Card_001.png");
	CardRenderPtr3->SetScaleToTexture("Card_001.png");
	CardRenderPtr4->SetScaleToTexture("Card_001.png");

	CardRenderPtr0->CreateAnimation({ .AnimationName = "Rotate", .SpriteName = "CardUI", .Start = 0, .End = 5, .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
	CardRenderPtr1->CreateAnimation({ .AnimationName = "Rotate", .SpriteName = "CardUI", .Start = 0, .End = 5, .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
	CardRenderPtr2->CreateAnimation({ .AnimationName = "Rotate", .SpriteName = "CardUI", .Start = 0, .End = 5, .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
	CardRenderPtr3->CreateAnimation({ .AnimationName = "Rotate", .SpriteName = "CardUI", .Start = 0, .End = 5, .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
	CardRenderPtr4->CreateAnimation({ .AnimationName = "Rotate", .SpriteName = "CardUI", .Start = 0, .End = 5, .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });

	SizeY = 1.0f / (Player::MainPlayer->MaxEXGauge - 1);

	CardRenderPtr0->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.0f);
	CardRenderPtr1->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.0f);
	CardRenderPtr2->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.0f);
	CardRenderPtr3->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.0f);
	CardRenderPtr4->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.0f);

	CardRenderPtr1->GetTransform()->SetLocalPosition({ 20, 0 });
	CardRenderPtr2->GetTransform()->SetLocalPosition({ 40, 0 });
	CardRenderPtr3->GetTransform()->SetLocalPosition({ 60, 0 });
	CardRenderPtr4->GetTransform()->SetLocalPosition({ 80, 0 });
}

void CardUI::Update(float _DeltaTime)
{
	int StackCount = MainPlayer->PlayerEXStack;

	// ¾ÈµÊ
	if (true == GameEngineInput::IsDown("EX") && 1 == StackCount)
	{
		int a = 0;
	}

	if (0 == StackCount)
	{
		if (49 > Stack0)
		{
			Stack0Full = false;
			float CurGauege = MainPlayer->PlayerEXGauge;
			Stack0 = CurGauege;

			CardRenderPtr0->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, SizeY * Stack0);
		}
		else if (49 == Stack0)
		{
			Stack0Full = true;
			CardRenderPtr0->ChangeAnimation("Rotate", false);
		}
	}

	if (true == Stack0Full && 1 == StackCount)
	{
		if (49 > Stack1)
		{
			Stack1Full = false;
			float CurGauege = MainPlayer->PlayerEXGauge;
			Stack1 = CurGauege;

			CardRenderPtr1->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, SizeY * Stack1);
		}
		else if (49 == Stack1)
		{
			Stack1Full = true;
			CardRenderPtr1->ChangeAnimation("Rotate", false);
		}
	}

	if (true == Stack1Full && 2 == StackCount)
	{
		if (49 > Stack2)
		{
			Stack2Full = false;
			float CurGauege = MainPlayer->PlayerEXGauge;
			Stack2 = CurGauege;

			CardRenderPtr2->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, SizeY * Stack2);
		}
		else if (49 == Stack2)
		{
			Stack2Full = true;
			CardRenderPtr2->ChangeAnimation("Rotate", false);
		}
	}

	if (true == Stack2Full && 3 == StackCount)
	{
		if (49 > Stack3)
		{
			Stack3Full = false;
			float CurGauege = MainPlayer->PlayerEXGauge;
			Stack3 = CurGauege;

			CardRenderPtr3->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, SizeY * Stack3);
		}
		else if (49 == Stack3)
		{
			Stack3Full = true;
			CardRenderPtr3->ChangeAnimation("Rotate", false);
		}
	}

	if (true == Stack3Full && 4 == StackCount)
	{
		if (49 > Stack4)
		{
			Stack4Full = false;
			float CurGauege = MainPlayer->PlayerEXGauge;
			Stack4 = CurGauege;

			CardRenderPtr4->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, SizeY * Stack4);
		}
		else if (49 == Stack4)
		{
			Stack4Full = true;
			CardRenderPtr4->ChangeAnimation("Rotate", false);
		}
	}
}

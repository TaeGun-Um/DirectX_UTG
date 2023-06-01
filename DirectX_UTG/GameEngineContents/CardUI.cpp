#include "PrecompileHeader.h"
#include "CardUI.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

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

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Card_001.png").GetFullPath(), 1, 50);
	}

	RenderPtr = CreateComponent<GameEngineUIRenderer>();

	RenderPtr->CreateAnimation({ .AnimationName = "Back_001", .SpriteName = "Card_001.png", .Start = 0, .End = 0, .FrameInter = 1.f, .Loop = false });
	RenderPtr->CreateAnimation({ .AnimationName = "Back_002", .SpriteName = "Card_001.png", .Start = 1, .End = 1, .FrameInter = 1.f, .Loop = false });
	RenderPtr->CreateAnimation({ .AnimationName = "Back_003", .SpriteName = "Card_001.png", .Start = 2, .End = 2, .FrameInter = 1.f, .Loop = false });
	RenderPtr->CreateAnimation({ .AnimationName = "Back_004", .SpriteName = "Card_001.png", .Start = 3, .End = 3, .FrameInter = 1.f, .Loop = false });
	RenderPtr->CreateAnimation({ .AnimationName = "Back_005", .SpriteName = "Card_001.png", .Start = 4, .End = 4, .FrameInter = 1.f, .Loop = false });
	RenderPtr->CreateAnimation({ .AnimationName = "Back_006", .SpriteName = "Card_001.png", .Start = 5, .End = 5, .FrameInter = 1.f, .Loop = false });
	RenderPtr->CreateAnimation({ .AnimationName = "Back_007", .SpriteName = "Card_001.png", .Start = 6, .End = 6, .FrameInter = 1.f, .Loop = false });
	RenderPtr->CreateAnimation({ .AnimationName = "Back_008", .SpriteName = "Card_001.png", .Start = 7, .End = 7, .FrameInter = 1.f, .Loop = false });
	RenderPtr->CreateAnimation({ .AnimationName = "Back_009", .SpriteName = "Card_001.png", .Start = 8, .End = 8, .FrameInter = 1.f, .Loop = false });
	RenderPtr->CreateAnimation({ .AnimationName = "Back_010", .SpriteName = "Card_001.png", .Start = 9, .End = 9, .FrameInter = 1.f, .Loop = false });

	RenderPtr->CreateAnimation({ .AnimationName = "Rotate", .SpriteName = "CardUI", .Start = 0, .End = 5, .FrameInter = 0.06f, .Loop = false });
	RenderPtr->CreateAnimation({ .AnimationName = "Front", .SpriteName = "CardUI", .Start = 5, .End = 5, .FrameInter = 0.06f, .Loop = false });

	RenderPtr->ChangeAnimation("Back_001");
}

void CardUI::Update(float _DeltaTime)
{
	if (0 == MainPlayer->PlayerEXGauge)
	{
		RenderPtr->Off();
	}
	else
	{
		RenderPtr->On();
	}
	
	Stack = MainPlayer->PlayerEXGauge;

	switch (Stack)
	{
	case 0:
	{
		RenderPtr->ChangeAnimation("Back_001");
	}
	break;
	case 1:
	{
		RenderPtr->ChangeAnimation("Back_002");
	}
	break;
	case 2:
	{
		RenderPtr->ChangeAnimation("Back_003");
	}
	break;
	case 3:
	{
		RenderPtr->ChangeAnimation("Back_004");
	}
	break;
	case 4:
	{
		RenderPtr->ChangeAnimation("Back_005");
	}
	break;
	case 5:
	{
		RenderPtr->ChangeAnimation("Back_006");
	}
	break;
	case 6:
	{
		RenderPtr->ChangeAnimation("Back_007");
	}
	break;
	case 7:
	{
		RenderPtr->ChangeAnimation("Back_008");
	}
	break;
	case 8:
	{
		RenderPtr->ChangeAnimation("Back_009");
	}
	break;
	case 9:
	{
		RenderPtr->ChangeAnimation("Back_010");
	}
	break;
	default:
		break;
	}
	
}
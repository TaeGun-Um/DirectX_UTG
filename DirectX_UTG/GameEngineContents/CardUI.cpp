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

void CardUI::SetMainPalyer(std::shared_ptr<class Player> _MainPalyer)
{
	MainPalyer = _MainPalyer;
}

void CardUI::Start()
{
	if (nullptr == GameEngineSprite::Find("Health.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Health");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Health.png").GetFullPath(), 6, 2);
	}

	RenderPtr = CreateComponent<GameEngineUIRenderer>();
	RenderPtr->GetTransform()->SetLocalScale({80, 34});
	RenderPtr->CreateAnimation({ "DEAD", "Health.png", 0, 0, 1.f, false, false });
	RenderPtr->CreateAnimation({ "HP1", "Health.png", 3, 3, 1.f, false, false });
	RenderPtr->CreateAnimation({ "HP2", "Health.png", 4, 4, 1.f, false, false });
	RenderPtr->CreateAnimation({ "HP3", "Health.png", 5, 5, 1.f, false, false });
	RenderPtr->CreateAnimation({ "MAX", "Health.png", 2, 2, 1.f, false, false });
	RenderPtr->ChangeAnimation("HP3");
}

void CardUI::Update(float _DeltaTime)
{
	if (true == MainPalyer->GetPlayerIsHPMax())
	{
		RenderPtr->ChangeAnimation("MAX");
		return;
	}

	int HP = MainPalyer->GetPlayerHP();

	switch (HP)
	{
	case 0:
	{
		RenderPtr->ChangeAnimation("DEAD");
	}
	break;
	case 1:
	{
		RenderPtr->ChangeAnimation("HP1");
	}
	break;
	case 2:
	{
		RenderPtr->ChangeAnimation("HP2");
	}
	break;
	case 3:
	{
		RenderPtr->ChangeAnimation("HP3");
	}
	break;
	default:
	{
		MsgAssert("HP 설정에 문제가 있습니다.");
	}
	break;
	}
}
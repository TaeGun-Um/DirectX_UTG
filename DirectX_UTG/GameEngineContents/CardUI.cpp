#include "PrecompileHeader.h"
#include "CardUI.h"

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

	}

	RenderPtr = CreateComponent<GameEngineUIRenderer>();

	RenderPtr->CreateAnimation({ .AnimationName = "Back", .SpriteName = "CardUI", .Start = 0, .End = 0, .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "Rotate", .SpriteName = "CardUI", .Start = 0, .End = 5, .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "Front", .SpriteName = "CardUI", .Start = 5, .End = 5, .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });

	RenderPtr->ChangeAnimation("Back");
}

void CardUI::Update(float _DeltaTime)
{
	if (49 == RenderPtr->GetCurrentFrame())
	{
		RenderPtr->ChangeAnimation("Rotate");
	}

}
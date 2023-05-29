#include "PrecompileHeader.h"
#include "TitleMenu.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "First_OpeningLevel.h"

TitleMenu::TitleMenu() 
{
	if (false == GameEngineInput::IsKey("TitleSelect"))
	{
		GameEngineInput::CreateKey("TitleSelect", 'Z');
		GameEngineInput::CreateKey("TitleUp", VK_UP);
		GameEngineInput::CreateKey("TitleDown", VK_DOWN);
	}
}

TitleMenu::~TitleMenu() 
{
}

void TitleMenu::Start()
{
	if (nullptr == GameEngineTexture::Find("cuphead_startscreen.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("MainMenu");

		GameEngineTexture::Load(NewDir.GetPlusFileName("cuphead_startscreen.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("START.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("EXIT.png").GetFullPath());
	}

	if (nullptr == BGRenderPtr)
	{
		BGRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BGRenderPtr->SetScaleToTexture("cuphead_startscreen.png");
	}

	if (nullptr == StartRenderPtr)
	{
		StartRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		StartRenderPtr->SetScaleToTexture("START.png");
		StartRenderPtr->GetTransform()->SetLocalPosition({ 0, 20 });
	}

	if (nullptr == EndRenderPtr)
	{
		EndRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		EndRenderPtr->SetScaleToTexture("EXIT.png");
		EndRenderPtr->GetTransform()->SetLocalPosition({ 0, -20 });
		EndRenderPtr->ColorOptionValue.MulColor.a = NoneColor;
	}
}

void TitleMenu::Update(float _DeltaTime)
{
	if (false == First_OpeningLevel::First_OpeningLevelPtr->GetIsTitleMove())
	{
		return;
	}

	if (true == GameEngineInput::IsDown("TitleUp") && 0 == SelectCount)
	{
		Delaytiem = 0.0f;
		SelectCount = 1;
		EndRenderPtr->ColorOptionValue.MulColor.a = SelectColor;
		StartRenderPtr->ColorOptionValue.MulColor.a = NoneColor;
	}
	else if (true == GameEngineInput::IsDown("TitleDown") && 0 == SelectCount)
	{
		Delaytiem = 0.0f;
		SelectCount = 1;
		EndRenderPtr->ColorOptionValue.MulColor.a = SelectColor;
		StartRenderPtr->ColorOptionValue.MulColor.a = NoneColor;
	}
	else if (true == GameEngineInput::IsDown("TitleUp") && 1 == SelectCount)
	{
		Delaytiem = 0.0f;
		SelectCount = 0;
		EndRenderPtr->ColorOptionValue.MulColor.a = NoneColor;
		StartRenderPtr->ColorOptionValue.MulColor.a = SelectColor;
	}
	else if (true == GameEngineInput::IsDown("TitleDown") && 1 == SelectCount)
	{
		Delaytiem = 0.0f;
		SelectCount = 0;
		EndRenderPtr->ColorOptionValue.MulColor.a = NoneColor;
		StartRenderPtr->ColorOptionValue.MulColor.a = SelectColor;
	}

	if (true == GameEngineInput::IsDown("TitleSelect") && 0 == SelectCount)
	{
		IsStart = true;
	}

	if (true == GameEngineInput::IsDown("TitleSelect") && 1 == SelectCount)
	{
		IsEnd = true;
	}
}
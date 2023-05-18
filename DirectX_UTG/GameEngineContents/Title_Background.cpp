#include "PrecompileHeader.h"
#include "Title_Background.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "MDHR_Logo.h"
#include "Player.h"

Title_Background::Title_Background() 
{
}

Title_Background::~Title_Background() 
{
}

void Title_Background::Start()
{
	if (nullptr == GameEngineSprite::Find("Cuphead_and_Mugman"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Opening1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cuphead_and_Mugman").GetFullPath());

		if (nullptr == GameEngineSprite::Find("PressAnyButton"))
		{
			NewDir.Move("Title");

			GameEngineTexture::Load(NewDir.GetPlusFileName("Title_Background.png").GetFullPath());
			GameEngineTexture::Load(NewDir.GetPlusFileName("PressAnyButton.png").GetFullPath());
		}
	}

	if (nullptr == RenderPtr0)
	{
		RenderPtr0 = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr0->SetTexture("Title_Background.png");
		RenderPtr0->GetTransform()->SetLocalScale({ 1280, 720, 4 });
		RenderPtr0->Off();
	}

	if (nullptr == RenderPtr1)
	{
		RenderPtr1 = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr1->CreateAnimation({ .AnimationName = "Cuphead_and_Mugman", .SpriteName = "Cuphead_and_Mugman", .FrameInter = 0.05f, .ScaleToTexture = true });
		RenderPtr1->ChangeAnimation("Cuphead_and_Mugman");
		RenderPtr1->GetTransform()->AddWorldPosition({ 50, -60 });
		RenderPtr1->Off();
	}

	if (nullptr == RenderPtr2)
	{
		RenderPtr2 = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr2->SetTexture("PressAnyButton.png");
		RenderPtr2->GetTransform()->SetLocalScale({ 355, 51, 2 });
		RenderPtr2->GetTransform()->AddWorldPosition({ 25, -280 });
		RenderPtr2->Off();
	}
}
void Title_Background::Update(float _DeltaTime)
{
	if (false == MDHR_Logo::LogoPtr->GetLogoAnimationIsEnd())
	{
		return;
	}
	
	RenderPtr0->On();
	RenderPtr1->On();
	RenderPtr2->On();

	KeyRenderTime += _DeltaTime;

	if (1.0f <= KeyRenderTime)
	{
		RenderPtr2->Off();
	}
	
	if (2.0f <= KeyRenderTime)
	{
		RenderPtr2->On();
		KeyRenderTime = 0.0f;
	}
}
#include "PrecompileHeader.h"
#include "Title_Background.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Title_Background::Title_Background() 
{
}

Title_Background::~Title_Background() 
{
}

void Title_Background::Start()
{
	RenderPtr0 = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr0->SetTexture("Title_Background.png");
	RenderPtr0->GetTransform()->SetLocalScale({ 1280, 720, 4 });

	RenderPtr1 = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr1->SetTexture("Title_Animation_001.png");
	RenderPtr1->GetTransform()->SetLocalScale({ 1093, 614, 3 });
	RenderPtr1->GetTransform()->AddWorldPosition({ 50, -60 });

	RenderPtr2 = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr2->SetTexture("PressAnyButton.png");
	RenderPtr2->GetTransform()->SetLocalScale({ 355, 51, 2 });
	RenderPtr2->GetTransform()->AddWorldPosition({ 25, -300 });
}
void Title_Background::Update(float _DeltaTime)
{
	KeyRenderTime += _DeltaTime;

	if (2.0f <= KeyRenderTime)
	{
		RenderPtr2->Off();
	}
	
	if (4.0f <= KeyRenderTime)
	{
		RenderPtr2->On();
		KeyRenderTime = 0.0f;
	}

}
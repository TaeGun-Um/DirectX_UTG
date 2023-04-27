#include "PrecompileHeader.h"
#include "BookRender.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

BookRender::BookRender() 
{
}

BookRender::~BookRender() 
{
}

void BookRender::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetTexture("book_intro_0000.png");
	RenderPtr->GetTransform()->SetLocalScale({ 1280, 720, 1 });
}
void BookRender::Update(float _DeltaTime)
{

}
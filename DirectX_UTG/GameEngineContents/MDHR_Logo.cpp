#include "PrecompileHeader.h"
#include "MDHR_Logo.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

MDHR_Logo::MDHR_Logo() 
{
}

MDHR_Logo::~MDHR_Logo() 
{
}

void MDHR_Logo::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetTexture("tile000.png");
	RenderPtr->GetTransform()->SetLocalScale({1280, 720, 1});
}
void MDHR_Logo::Update(float _DeltaTime)
{

}
#include "PrecompileHeader.h"
#include "EXDust.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

EXDust::EXDust() 
{
}

EXDust::~EXDust() 
{
}

void EXDust::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetScaleToTexture("Ground_Ex_SFX_008.png");
}
void EXDust::Update(float _DeltaTime)
{

}
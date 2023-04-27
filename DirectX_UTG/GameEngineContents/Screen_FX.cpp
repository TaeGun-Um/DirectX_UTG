#include "PrecompileHeader.h"
#include "Screen_FX.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Screen_FX::Screen_FX() 
{
}

Screen_FX::~Screen_FX() 
{
}

void Screen_FX::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetTexture("Screen_Fx_001.png");
	RenderPtr->GetTransform()->SetLocalScale({ 1024, 512, 1 });
}
void Screen_FX::Update(float _DeltaTime)
{

}
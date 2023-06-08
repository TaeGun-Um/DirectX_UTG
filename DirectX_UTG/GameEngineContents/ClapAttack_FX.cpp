#include "PrecompileHeader.h"
#include "ClapAttack_FX.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>


ClapAttack_FX::ClapAttack_FX() 
{
}

ClapAttack_FX::~ClapAttack_FX() 
{
}

void ClapAttack_FX::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "Clap_FX", .SpriteName = "Clap_FX", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("Clap_FX");
	}
}

void ClapAttack_FX::Update(float _DeltaTime)
{
	if (false == Directbool)
	{
		Directbool = true;
		GetTransform()->SetLocalRotation({ 0, 0, 180 });
	}

	if (true == RenderPtr->IsAnimationEnd())
	{
		Death();
	}
}
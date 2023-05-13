#include "PrecompileHeader.h"
#include "MoveDust.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

MoveDust::MoveDust() 
{
}

MoveDust::~MoveDust() 
{
}

void MoveDust::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

	RenderPtr->CreateAnimation({ "Dust_A", "Dust_A.png", 0, 18, 0.05f, true, false });
	RenderPtr->CreateAnimation({ "Dust_B", "Dust_B.png", 0, 19, 0.05f, true, false });
	RenderPtr->CreateAnimation({ "Dust_C", "Dust_C.png", 0, 18, 0.05f, true, false });

	//RenderPtr->GetTransform()->SetLocalScale({100, 100});
	RenderPtr->ChangeAnimation("EXDust");
}

void MoveDust::Update(float _DeltaTime)
{
	DeathCheck();
}

void MoveDust::DeathCheck()
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		IsDeath = true;
		Death();
	}
}
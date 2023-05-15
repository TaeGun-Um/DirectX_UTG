#include "PrecompileHeader.h"
#include "MoveDust.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

MoveDust::MoveDust() 
{
}

MoveDust::~MoveDust() 
{
}

void MoveDust::SetDustType(DustType _Type)
{
	switch (Type)
	{
	case DustType::A:
		RenderPtr->ChangeAnimation("Dust_A");
		break;
	case DustType::B:
		RenderPtr->ChangeAnimation("Dust_B");
		break;
	case DustType::C:
		RenderPtr->ChangeAnimation("Dust_C");
		break;
	default:
		break;
	}
}

void MoveDust::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ "Dust_A", "Dust_A.png", 0, 18, 0.05f, true, true });
		RenderPtr->CreateAnimation({ "Dust_B", "Dust_B.png", 0, 19, 0.05f, true, true });
		RenderPtr->CreateAnimation({ "Dust_C", "Dust_C.png", 0, 18, 0.05f, true, true });

		RenderPtr->ChangeAnimation("Dust_A");
	}
}

void MoveDust::Update(float _DeltaTime)
{
	DeathCheck();
}

void MoveDust::DeathCheck()
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		Death();
	}
}
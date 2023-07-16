#include "PrecompileHeader.h"
#include "Dragon_FallPoint.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "DragonLevel.h"
#include "You_Died.h"

Dragon_FallPoint::Dragon_FallPoint() 
{
}

Dragon_FallPoint::~Dragon_FallPoint() 
{
}

void Dragon_FallPoint::Start()
{
	if (nullptr == CollisionPtr)
	{
		CollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::FallPoint));
		CollisionPtr->GetTransform()->SetLocalPosition({ -400, -10 });
		CollisionPtr->GetTransform()->SetLocalScale({ 1400, 50, -2 });
	}

	if (nullptr == CollisionRenderPtr)
	{
		CollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		CollisionRenderPtr->GetTransform()->SetLocalScale(CollisionPtr->GetTransform()->GetLocalScale());
		CollisionRenderPtr->GetTransform()->SetLocalPosition(CollisionPtr->GetTransform()->GetLocalPosition());
		CollisionRenderPtr->SetTexture("RedBox.png");
		CollisionRenderPtr->ColorOptionValue.MulColor.a = 0.6f;
		CollisionRenderPtr->Off();
	}
}

void Dragon_FallPoint::Update(float _DeltaTime)
{
	if (true == IsDebugRender)
	{
		CollisionRenderPtr->On();
	}
	else
	{
		CollisionRenderPtr->Off();
	}
}
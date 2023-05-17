#include "PrecompileHeader.h"
#include "PortalDoor.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"

PortalDoor::PortalDoor() 
{
}

PortalDoor::~PortalDoor() 
{
}

void PortalDoor::Start()
{
	if (nullptr == RenderPtrCollisionPtr)
	{
		RenderPtrCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Portal));
		RenderPtrCollisionPtr->GetTransform()->SetLocalScale({ 170, 150, 1 });
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->GetTransform()->SetLocalScale(RenderPtrCollisionPtr->GetTransform()->GetLocalScale());
		RenderPtr->GetTransform()->SetLocalPosition(RenderPtrCollisionPtr->GetTransform()->GetLocalPosition());
		RenderPtr->SetTexture("GreenBox.png");
		RenderPtr->ColorOptionValue.MulColor.a = 0.6f;
	}
}

void PortalDoor::Update(float _DeltaTime)
{
	//RenderPtr->GetTransform()->SetLocalScale(RenderPtr->GetTransform()->GetLocalScale());
	//RenderPtr->GetTransform()->SetLocalPosition(RenderPtr->GetTransform()->GetLocalPosition());
}
#include "PrecompileHeader.h"
#include "Axeman.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Axeman::Axeman() 
{
}

Axeman::~Axeman() 
{
}

void Axeman::Start()
{
	NPCLoad(NPCValue::Axeman);
	InitRenderSetting();
	InitCollisionSetting();
}
void Axeman::Update(float _DeltaTime)
{
	CollisionCheck(CollisionPtr);
}

void Axeman::InitRenderSetting()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr != RenderPtr)
	{
		RenderPtr->CreateAnimation({ .AnimationName = "Axeman_Idle", .SpriteName = "Axeman_Idle", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Axeman_Idle");
	}
}

void Axeman::InitCollisionSetting()
{
	if (nullptr == CollisionRenderPtr)
	{
		CollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr == CollisionPtr)
	{
		CollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::NPC));
	}

	if (nullptr != CollisionPtr)
	{
		CollisionPtr->GetTransform()->SetLocalScale({ 50, 50, 1 });
		CollisionPtr->GetTransform()->SetLocalPosition({ 0, 0, -17 });
	}

	if (nullptr != CollisionRenderPtr)
	{
		CollisionRenderPtr->SetTexture("GreenLine.png");
		CollisionRenderPtr->GetTransform()->SetLocalScale(CollisionPtr->GetTransform()->GetLocalScale());
		CollisionRenderPtr->GetTransform()->SetLocalPosition(CollisionPtr->GetTransform()->GetLocalPosition());
	}
}
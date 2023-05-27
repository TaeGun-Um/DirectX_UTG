#include "PrecompileHeader.h"
#include "Canteen.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Canteen* Canteen::CanteenPtr = nullptr;

Canteen::Canteen() 
{
}

Canteen::~Canteen() 
{
}

void Canteen::Start()
{
	CanteenPtr = this;
	NPCLoad(NPCValue::Canteen);
	InitRenderSetting();
	InitCollisionSetting();
}
void Canteen::Update(float _DeltaTime)
{
	CollisionCheck(CollisionPtr);
}

void Canteen::InitRenderSetting()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr != RenderPtr)
	{
		RenderPtr->CreateAnimation({ .AnimationName = "Canteen_Idle", .SpriteName = "Canteen_Idle", .FrameInter = 0.09f, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Canteen_Idle");
		RenderPtr->CameraCullingOn();
	}
}

void Canteen::InitCollisionSetting()
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
		CollisionPtr->GetTransform()->SetLocalScale({ 60, 60, 1 });
		CollisionPtr->GetTransform()->SetLocalPosition({ 0, 0, -17 });
	}

	if (nullptr != CollisionRenderPtr)
	{
		CollisionRenderPtr->SetTexture("GreenLine.png");
		CollisionRenderPtr->GetTransform()->SetLocalScale(CollisionPtr->GetTransform()->GetLocalScale());
		CollisionRenderPtr->GetTransform()->SetLocalPosition(CollisionPtr->GetTransform()->GetLocalPosition());
	}
}
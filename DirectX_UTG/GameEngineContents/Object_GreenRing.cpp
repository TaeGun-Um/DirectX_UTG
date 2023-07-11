#include "PrecompileHeader.h"
#include "Object_GreenRing.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Object_GreenRing::Object_GreenRing() 
{
}

Object_GreenRing::~Object_GreenRing() 
{
}

void Object_GreenRing::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Object_GreenRing", .SpriteName = "Object_GreenRing", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Object_PinkRing", .SpriteName = "Object_PinkRing", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Object_GreenRing");
	}

	if (nullptr == BodyCollisionPtr)
	{
		BodyCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Monster));
		BodyCollisionPtr->SetColType(ColType::AABBBOX2D);
		BodyCollisionPtr->GetTransform()->SetLocalScale({ 50, 50, -50 });
		BodyCollisionPtr->GetTransform()->SetLocalPosition({ 0, 0 });
	}

	if (nullptr == BodyCollisionRenderPtr)
	{
		BodyCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BodyCollisionRenderPtr->GetTransform()->SetLocalScale(BodyCollisionPtr->GetTransform()->GetLocalScale());
		BodyCollisionRenderPtr->GetTransform()->SetLocalPosition(BodyCollisionPtr->GetTransform()->GetLocalPosition());
		BodyCollisionRenderPtr->SetTexture("GreenLine.png");
		BodyCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
		//BodyCollisionRenderPtr->Off();
	}
}

void Object_GreenRing::Update(float _DeltaTime)
{

}
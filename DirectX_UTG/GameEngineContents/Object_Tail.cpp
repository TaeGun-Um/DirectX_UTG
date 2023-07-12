#include "PrecompileHeader.h"
#include "Object_Tail.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Object_Tail::Object_Tail() 
{
}

Object_Tail::~Object_Tail() 
{
}

void Object_Tail::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Object_Tail", .SpriteName = "Object_Tail", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Object_Tail");
	}

	if (nullptr == BodyCollisionPtr)
	{
		BodyCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Monster));
		BodyCollisionPtr->SetColType(ColType::AABBBOX2D);
		BodyCollisionPtr->GetTransform()->SetLocalScale({ 70, 500, -50 });
		BodyCollisionPtr->GetTransform()->SetLocalPosition({ -50, 100 });
	}

	if (nullptr == BodyCollisionRenderPtr)
	{
		BodyCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BodyCollisionRenderPtr->GetTransform()->SetLocalScale(BodyCollisionPtr->GetTransform()->GetLocalScale());
		BodyCollisionRenderPtr->GetTransform()->SetLocalPosition(BodyCollisionPtr->GetTransform()->GetLocalPosition());
		BodyCollisionRenderPtr->SetTexture("RedBox.png");
		BodyCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
		//BodyCollisionRenderPtr->Off();
	}
}

void Object_Tail::Update(float _DeltaTime)
{
	MoveCalculation(_DeltaTime);
	DeathCheck();
}

void Object_Tail::MoveCalculation(float _DeltaTime)
{
	float4 CurPos = GetTransform()->GetLocalPosition();

	if (OneStepPosition.y >= CurPos.y && false == OneStep)
	{
		float MoveDis = 300.0f * _DeltaTime;
		GetTransform()->AddLocalPosition({ 0, MoveDis });
	}
	else
	{
		OneStep = true;
	}

	if (true == OneStep)
	{
		MoveTime += _DeltaTime;
	}

	if (2.0f <= MoveTime)
	{
		if (TwoStepPosition.y >= CurPos.y && false == TwoStep)
		{
			float MoveDis = 1200.0f * _DeltaTime;
			GetTransform()->AddLocalPosition({ 0, MoveDis });
		}
		else
		{
			TwoStep = true;
		}
	}

	if (true == TwoStep)
	{
		BackTime += _DeltaTime;
	}

	if (1.f <= BackTime)
	{
		float MoveDis = 5.0f * _DeltaTime;

		if (2.5f >= abs(MoveAccel.y))
		{
			MoveAccel += float4{ 0, -MoveDis };
		}

		GetTransform()->AddLocalPosition(MoveAccel);
	}
}

void Object_Tail::DeathCheck()
{
	float4 CurPos = GetTransform()->GetLocalPosition();

	if (InitPosition.y - 100.0f >= CurPos.y)
	{
		Death();
	}
}
#include "PrecompileHeader.h"
#include "Object_Meteor.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "SFX_MeteorSmoke.h"
#include "DragonLevel.h"
#include "You_Died.h"

Object_Meteor::Object_Meteor() 
{
}

Object_Meteor::~Object_Meteor() 
{
}

void Object_Meteor::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Object_Meteor", .SpriteName = "Object_Meteor", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Object_Meteor");
	}

	if (nullptr == BodyCollisionPtr)
	{
		BodyCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
		BodyCollisionPtr->SetColType(ColType::AABBBOX2D);
		BodyCollisionPtr->GetTransform()->SetLocalScale({ 80, 80, -50 });
		BodyCollisionPtr->GetTransform()->SetLocalPosition({ -30, 0 });
	}

	if (nullptr == BodyCollisionRenderPtr)
	{
		BodyCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BodyCollisionRenderPtr->GetTransform()->SetLocalScale(BodyCollisionPtr->GetTransform()->GetLocalScale());
		BodyCollisionRenderPtr->GetTransform()->SetLocalPosition(BodyCollisionPtr->GetTransform()->GetLocalPosition());
		BodyCollisionRenderPtr->SetTexture("GreenBox.png");
		BodyCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
		BodyCollisionRenderPtr->Off();
	}
}

void Object_Meteor::Update(float _DeltaTime)
{
	if (true == DragonLevel::DragonLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	MoveCalculation(_DeltaTime);
	DeathCheck();
	CreateSmoke(_DeltaTime);
}

void Object_Meteor::MoveCalculation(float _DeltaTime)
{
	if (true == IsReverse)
	{
		MoveTime += _DeltaTime;

		float CosTime = MoveTime * 2.5f;

		float SinY = (sinf(CosTime + GameEngineMath::PIE) * 230.0f);

		GetTransform()->SetLocalPosition({ InitPosition.x - (CosTime * 150.0f), SinY + InitPosition.y, -5 });
	}
	else
	{
		MoveTime += _DeltaTime;

		float CosTime = MoveTime * 2.5f;

		float SinY = (sinf(CosTime) * 230.0f);

		GetTransform()->SetLocalPosition({ InitPosition.x - (CosTime * 150.0f), SinY + InitPosition.y, -5 });
	}
}

void Object_Meteor::DeathCheck()
{
	float4 CurPos = GetTransform()->GetLocalPosition();

	if (InitPosition.x - 1100.0f >= CurPos.x)
	{
		Death();
	}
}

void Object_Meteor::CreateSmoke(float _DeltaTime)
{
	SmokeCreateDelayTime += _DeltaTime;

	if (SmokeCreateDelayTime <= 0.2f)
	{
		return;
	}

	std::shared_ptr<SFX_MeteorSmoke> SmokeSFX = GetLevel()->CreateActor<SFX_MeteorSmoke>();

	float4 StartPosition = GetTransform()->GetWorldPosition();
	float4 ProjectilePosition = StartPosition + float4{ 0, 0, 1 };

	SmokeSFX->SetStartPosition(ProjectilePosition);

	SmokeCreateDelayTime = 0.0f;
}


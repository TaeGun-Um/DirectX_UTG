#include "PrecompileHeader.h"
#include "Object_GreenRing.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"

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
		BodyCollisionPtr->GetTransform()->SetLocalScale({ 50, 60, -50 });
		BodyCollisionPtr->GetTransform()->SetLocalPosition({ 0, 0 });
	}

	if (nullptr == BodyCollisionRenderPtr)
	{
		BodyCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BodyCollisionRenderPtr->GetTransform()->SetLocalScale(BodyCollisionPtr->GetTransform()->GetLocalScale());
		BodyCollisionRenderPtr->GetTransform()->SetLocalPosition(BodyCollisionPtr->GetTransform()->GetLocalPosition());
		BodyCollisionRenderPtr->SetTexture("RedBox.png");
		BodyCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
		BodyCollisionRenderPtr->Off();
	}

	if (nullptr == ParryCollisionPtr)
	{
		ParryCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::ParrySpot));
		ParryCollisionPtr->SetColType(ColType::SPHERE2D);
		ParryCollisionPtr->GetTransform()->SetLocalScale({ 90, 100, -50 });
		ParryCollisionPtr->GetTransform()->SetLocalPosition({ 0, 0 });
		ParryCollisionPtr->Off();
	}

	if (nullptr == ParryCollisionRenderPtr)
	{
		ParryCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ParryCollisionRenderPtr->SetTexture("GreenLine.png");
		ParryCollisionRenderPtr->GetTransform()->SetLocalScale(ParryCollisionPtr->GetTransform()->GetLocalScale());
		ParryCollisionRenderPtr->GetTransform()->SetLocalPosition(ParryCollisionPtr->GetTransform()->GetLocalPosition());
		ParryCollisionRenderPtr->Off();
	}
}

void Object_GreenRing::Update(float _DeltaTime)
{
	if (true == IsParryProjectile)
	{
		IsParryProjectile = false;
		ParryCollisionPtr->On();
		RenderPtr->ChangeAnimation("Object_PinkRing");
	}

	CollisionCheck();
	MoveCalculation(_DeltaTime);
	DeathCheck();
}

void Object_GreenRing::CollisionCheck()
{
	if (nullptr != ParryCollisionPtr->Collision(static_cast<int>(CollisionOrder::PlayerParry), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		Player::MainPlayer->SetParryOn();
		Death();
	}
}

void Object_GreenRing::MoveCalculation(float _DeltaTime)
{
	float MoveDist = MoveSpeed * _DeltaTime;

	float4 MoveDist4 = float4::Zero;
	float4 Correction = float4::Zero;

	Correction = GetTransform()->GetWorldRightVector().NormalizeReturn();
	GetTransform()->AddLocalPosition(-(Correction * MoveSpeed * _DeltaTime));
}

void Object_GreenRing::DeathCheck()
{
	float4 CurPos = GetTransform()->GetLocalPosition();

	if (InitPosition.x - 1200.0f >= CurPos.x)
	{
		Death();
	}
}
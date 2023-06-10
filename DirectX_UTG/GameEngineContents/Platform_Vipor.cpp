#include "PrecompileHeader.h"
#include "Platform_Vipor.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "FrogLevel.h"
#include "You_Died.h"

Platform_Vipor::Platform_Vipor() 
{
}

Platform_Vipor::~Platform_Vipor() 
{
}

void Platform_Vipor::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Snake_Platform", .SpriteName = "Snake_Platform", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Snake_Platform");
	}

	if (nullptr == PlatformCollisionPtr)
	{
		PlatformCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Platform));
		PlatformCollisionPtr->GetTransform()->SetLocalScale({ 200, 25, 1 });
		PlatformCollisionPtr->GetTransform()->SetLocalPosition({ 0, 20 });
	}

	if (nullptr == PlatformCollisionRenderPtr)
	{
		PlatformCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		PlatformCollisionRenderPtr->GetTransform()->SetLocalScale(PlatformCollisionPtr->GetTransform()->GetLocalScale());
		PlatformCollisionRenderPtr->GetTransform()->SetLocalPosition(PlatformCollisionPtr->GetTransform()->GetLocalPosition());
		PlatformCollisionRenderPtr->SetTexture("RedBox.png");
		PlatformCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.6f;
	}

	if (nullptr == DebugRenderPtr)
	{
		DebugRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr->GetTransform()->AddLocalPosition({0, -5});
		DebugRenderPtr->SetTexture("BlueDot.png");
	}

	//if (nullptr == HitCollisionPtr)
	//{
	//	HitCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
	//	HitCollisionPtr->GetTransform()->SetLocalScale({ 50, 50, 1 });
	//	HitCollisionPtr->GetTransform()->SetLocalPosition({ 50, 0 });
	//}

	//if (nullptr == HitCollisionRenderPtr)
	//{
	//	HitCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	//	HitCollisionRenderPtr->GetTransform()->SetLocalScale({ 50, 50, 1 });
	//	HitCollisionRenderPtr->GetTransform()->SetLocalPosition({ 50, 0 });
	//	HitCollisionRenderPtr->SetTexture("RedLine.png");
	//}
}

void Platform_Vipor::Update(float _DeltaTime)
{
	if (true == FrogLevel::FrogLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	PixelCheck(_DeltaTime);
	MoveDirection(_DeltaTime);
	DeathCheck();
}

void Platform_Vipor::MoveDirection(float _DeltaTime)
{
	if (false == IsBoundEnd)
	{
		if (MoveDirect.y >= -500.0f)
		{
			MoveDirect.y += -1000.0f * _DeltaTime;
		}

		GetTransform()->AddLocalPosition(MoveDirect * _DeltaTime);
	}
	else
	{
		MoveDirect.y = 0;
	}

	float MoveDis = 100.0f * _DeltaTime;

	GetTransform()->AddLocalPosition({ -MoveDis, 0 });
	GetTransform()->AddLocalPosition(MoveDirect * _DeltaTime);
}

void Platform_Vipor::DeathCheck()
{
	float4 CurPos = GetTransform()->GetLocalPosition();

	if (StartPosition.x - 1100.0f >= CurPos.x)
	{
		Death();
	}
}

void Platform_Vipor::PixelCheck(float _DeltaTime)
{
	if (2 == BoundCount)
	{
		return;
	}

	float4 PlatformPos = GetTransform()->GetLocalPosition();
	float4 BoundPos = PlatformPos + float4{ 0, -5 };

	GameEnginePixelColor BoundPixel = PixelCollisionCheck.PixelCheck(BoundPos);

	if (true == PixelCollisionCheck.IsBlack(BoundPixel) && 0 == BoundCount)
	{
		MoveDirect.y = 0;
		MoveDirect.y += 100.0f;
		++BoundCount;
	}
	if (true == PixelCollisionCheck.IsBlack(BoundPixel) && 1 == BoundCount)
	{
		MoveDirect.y = 0;
		IsBoundEnd = true;
		++BoundCount;
	}
}
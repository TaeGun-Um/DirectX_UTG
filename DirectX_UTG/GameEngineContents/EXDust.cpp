#include "PrecompileHeader.h"
#include "EXDust.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

EXDust::EXDust() 
{
}

EXDust::~EXDust() 
{
}

void EXDust::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

	RenderPtr->CreateAnimation({ .AnimationName = "Ex_SFX", .SpriteName = "Ex_SFX", .FrameInter = 0.05f });

	RenderPtr->GetTransform()->SetLocalScale({100, 100});
	RenderPtr->ChangeAnimation("Ex_SFX");
}

void EXDust::Update(float _DeltaTime)
{
	MoveDirection(_DeltaTime);
	DeathCheck();
}

void EXDust::MoveDirection(float _DeltaTime)
{
	if (true == IsDeath)
	{
		return;
	}

	float MoveDist = MoveSpeed * _DeltaTime;

	float4 MoveDist4 = float4::Zero;
	float4 Correction = float4::Zero;

	Correction = GetTransform()->GetWorldRightVector().NormalizeReturn();
	GetTransform()->AddLocalPosition(Correction * MoveSpeed * _DeltaTime);
}

void EXDust::DeathCheck()
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		IsDeath = true;
		Death();
	}
}
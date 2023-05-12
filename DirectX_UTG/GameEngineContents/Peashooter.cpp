#include "PrecompileHeader.h"
#include "Peashooter.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Peashooter::Peashooter() 
{
}

Peashooter::~Peashooter() 
{
}

void Peashooter::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

	RenderPtr->CreateAnimation({ "Loop", "Peashooter_Loop.png", 0, 7, 0.1f, true, false });
	RenderPtr->CreateAnimation({ "Death", "Peashooter_Death.png", 0, 6, 0.1f, false, false });

	RenderPtr->GetTransform()->SetLocalScale(float4{ 400, 400 });
	RenderPtr->ChangeAnimation("Loop");
}
void Peashooter::Update(float _DeltaTime)
{
	//if (true == RenderPtr->FindAnimation("Spawn")->IsEnd())
	//{
	//	RenderPtr->ChangeAnimation("Loop", true);
	//}

	MoveDirection(_DeltaTime);
	DeathCheck();
}

void Peashooter::MoveDirection(float _DeltaTime)
{
	float MoveDist = MoveSpeed * _DeltaTime;

	float4 MoveDist4 = float4::Zero;
	float4 Correction = float4::Zero;

	Correction = GetTransform()->GetWorldRightVector().NormalizeReturn();
	GetTransform()->AddLocalPosition(Correction * MoveSpeed * _DeltaTime);
}

void Peashooter::DeathCheck()
{
	if (1.0f <= GetLiveTime())
	{
		Death();
	}
}
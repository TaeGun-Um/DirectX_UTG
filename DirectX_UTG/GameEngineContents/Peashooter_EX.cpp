#include "PrecompileHeader.h"
#include "Peashooter_EX.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Peashooter_EX::Peashooter_EX() 
{
}

Peashooter_EX::~Peashooter_EX() 
{
}

void Peashooter_EX::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

	RenderPtr->CreateAnimation({ "Loop", "Peashooter_EX_Loop.png", 0, 7, 0.07f, true, false });
	RenderPtr->CreateAnimation({ "Death", "Peashooter_EX_Death.png", 0, 8, 0.05f, true, false });

	RenderPtr->GetTransform()->SetLocalScale(float4{ 700, 700 });
	RenderPtr->ChangeAnimation("Loop");
}
void Peashooter_EX::Update(float _DeltaTime)
{
	MoveDirection(_DeltaTime);
	DeathCheck();
}

void Peashooter_EX::MoveDirection(float _DeltaTime)
{
	if (true == IsDeath || true == Check)
	{
		return;
	}

	float MoveDist = MoveSpeed * _DeltaTime;

	float4 MoveDist4 = float4::Zero;
	float4 Correction = float4::Zero;

	Correction = GetTransform()->GetWorldRightVector().NormalizeReturn();
	GetTransform()->AddLocalPosition(Correction * MoveSpeed * _DeltaTime);
}

void Peashooter_EX::DeathCheck()
{
	if (1.0f <= GetLiveTime())
	{
		if (false == Check)
		{
			Check = true;
			RenderPtr->ChangeAnimation("Death", false);
		}
	}

	if (true == RenderPtr->FindAnimation("Death")->IsEnd())
	{
		IsDeath = true;
	}

	if (true == IsDeath)
	{
		Death();
	}
}
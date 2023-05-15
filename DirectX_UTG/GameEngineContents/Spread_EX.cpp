#include "PrecompileHeader.h"
#include "Spread_EX.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Spread_EX::Spread_EX() 
{
}

Spread_EX::~Spread_EX() 
{
}

void Spread_EX::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ "Spawn", "Spread_EX_Spawn.png", 0, 4, 0.04f, true, true });
		RenderPtr->CreateAnimation({ "Loop", "Spread_EX_Loop.png", 0, 3, 0.07f, true, true });
		RenderPtr->CreateAnimation({ "Death", "Spread_EX_Death.png", 0, 5, 0.05f, true, true });

		RenderPtr->ChangeAnimation("Spawn");
	}

	if (nullptr == FalmeRenderPtr)
	{
		FalmeRenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		FalmeRenderPtr->GetTransform()->SetLocalPosition({ -100, 0 });

		FalmeRenderPtr->CreateAnimation({ "FlameStart", "Spread_EX_Flame.png", 0, 4, 0.07f, true, true });
		FalmeRenderPtr->CreateAnimation({ "FlameLoop", "Spread_EX_Flame.png", 5, 9, 0.07f, true, true });
		FalmeRenderPtr->CreateAnimation({ "FlameEnd", "Spread_EX_Flame.png", 10, 16, 0.07f, true, true });

		FalmeRenderPtr->ChangeAnimation("FlameStart");
	}
}

void Spread_EX::Update(float _DeltaTime)
{
	UpdateState(_DeltaTime);
}

void Spread_EX::ChangeState(Spread_EXState _StateValue)
{
	Spread_EXState NextState = _StateValue;
	Spread_EXState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case Spread_EXState::Spawn:
		SpawnStart();
		break;
	case Spread_EXState::Loop:
		LoopStart();
		break;
	case Spread_EXState::Death:
		DeathStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case Spread_EXState::Spawn:
		SpawnEnd();
		break;
	case Spread_EXState::Loop:
		LoopEnd();
		break;
	case Spread_EXState::Death:
		DeathEnd();
		break;
	default:
		break;
	}

}
void Spread_EX::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case Spread_EXState::Spawn:
		SpawnUpdate(_DeltaTime);
		break;
	case Spread_EXState::Loop:
		LoopUpdate(_DeltaTime);
		break;
	case Spread_EXState::Death:
		DeathUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Spread_EX::SpawnStart()
{

}
void Spread_EX::SpawnUpdate(float _DeltaTime)
{
	float MoveDist = MoveSpeed * _DeltaTime;

	float4 MoveDist4 = float4::Zero;
	float4 Correction = float4::Zero;

	Correction = GetTransform()->GetWorldRightVector().NormalizeReturn();
	GetTransform()->AddLocalPosition(Correction * MoveSpeed * _DeltaTime);

	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(Spread_EXState::Loop);
		return;
	}
}
void Spread_EX::SpawnEnd()
{

}

void Spread_EX::LoopStart()
{
	RenderPtr->ChangeAnimation("Loop");
	FalmeRenderPtr->ChangeAnimation("FlameLoop");
}
void Spread_EX::LoopUpdate(float _DeltaTime)
{
	float MoveDist = MoveSpeed * _DeltaTime;

	float4 MoveDist4 = float4::Zero;
	float4 Correction = float4::Zero;

	Correction = GetTransform()->GetWorldRightVector().NormalizeReturn();
	GetTransform()->AddLocalPosition(Correction * MoveSpeed * _DeltaTime);

	if (3.0f <= GetLiveTime())
	{
		IsDeath = true;
	}

	if (true == IsDeath)
	{
		ChangeState(Spread_EXState::Death);
		return;
	}
}
void Spread_EX::LoopEnd()
{

}

void Spread_EX::DeathStart()
{
	RenderPtr->ChangeAnimation("Death");
	FalmeRenderPtr->ChangeAnimation("FlameEnd");
}
void Spread_EX::DeathUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		Death();
	}
}
void Spread_EX::DeathEnd()
{

}
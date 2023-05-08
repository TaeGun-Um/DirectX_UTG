#include "PrecompileHeader.h"
#include "Spread.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Spread::Spread() 
{
}

Spread::~Spread() 
{
}

void Spread::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetScaleToTexture("Temporary_Spread.png");
}
void Spread::Update(float _DeltaTime)
{
	MoveDirection(_DeltaTime);
	DeathCheck();
}

void Spread::MoveDirection(float _DeltaTime)
{
	float MoveDist = MoveSpeed * _DeltaTime;

	float4 MoveDist4 = float4::Zero;
	float4 Correction = float4::Zero;

	Correction = GetTransform()->GetWorldRightVector().NormalizeReturn();
	GetTransform()->AddLocalPosition(Correction * MoveSpeed * _DeltaTime);
}

void Spread::DeathCheck()
{
	if (0.2f <= GetLiveTime())
	{
		Death();
	}
}
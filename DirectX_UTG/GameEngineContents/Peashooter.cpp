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
	RenderPtr->SetScaleToTexture("Temporary_Peashooter.png");
}
void Peashooter::Update(float _DeltaTime)
{
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
	if (0.2f <= GetLiveTime())
	{
		Death();
	}
}
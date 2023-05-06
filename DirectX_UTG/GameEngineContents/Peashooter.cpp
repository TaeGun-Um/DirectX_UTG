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
	float MoveDist = MoveSpeed * _DeltaTime;

	if (true == Direction) // Right
	{
		GetTransform()->AddLocalPosition({ MoveDist, 0 });
	}
	else				   // Left
	{
		GetTransform()->AddLocalPosition({ -MoveDist, 0 });
	}

	float4 BulletPos = GetTransform()->GetLocalPosition();

	if (abs(InitPlayerXPosition + 1000.0f) <= abs(BulletPos.x))
	{
		Death();
	}
}
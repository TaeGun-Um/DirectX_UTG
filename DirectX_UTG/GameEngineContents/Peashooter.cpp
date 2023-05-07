#include "PrecompileHeader.h"
#include "Peashooter.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"

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

	switch (ADValue)
	{
	case AttackDirection::Right_Up:
	{
		GetTransform()->AddLocalPosition({ 0, MoveDist });
	}
	break;
	case AttackDirection::Right_DiagonalUp:
	{
		MoveDist4 = { MoveDist, MoveDist };
		Correction = MoveDist4.NormalizeReturn();

		GetTransform()->AddLocalPosition(Correction * MoveSpeed * _DeltaTime);
	}
	break;
	case AttackDirection::Right_Front:
	{
		GetTransform()->AddLocalPosition({ MoveDist, 0 });
	}
	break;
	case AttackDirection::Right_DiagonalDown:
	{
		MoveDist4 = { MoveDist , -MoveDist };
		Correction = MoveDist4.NormalizeReturn();

		GetTransform()->AddLocalPosition(Correction * MoveSpeed * _DeltaTime);
	}
	break;
	case AttackDirection::Right_Down:
	{
		GetTransform()->AddLocalPosition({ 0, -MoveDist });
	}
	break;
	case AttackDirection::Left_Up:
	{
		GetTransform()->AddLocalPosition({ 0, MoveDist });
	}
	break;
	case AttackDirection::Left_DiagonalUp:
	{
		MoveDist4 = { -MoveDist, MoveDist };
		Correction = MoveDist4.NormalizeReturn();

		GetTransform()->AddLocalPosition(Correction * MoveSpeed * _DeltaTime);
	}
	break;
	case AttackDirection::Left_Front:
	{
		GetTransform()->AddLocalPosition({ -MoveDist, 0 });
	}
	break;
	case AttackDirection::Left_DiagonalDown:
	{
		MoveDist4 = { -MoveDist, -MoveDist };
		Correction = MoveDist4.NormalizeReturn();

		GetTransform()->AddLocalPosition(Correction * MoveSpeed * _DeltaTime);
	}
	break;
	case AttackDirection::Left_Down:
	{
		GetTransform()->AddLocalPosition({ 0, -MoveDist });
	}
	break;
	default:
		break;
	}
}

void Peashooter::DeathCheck()
{
	//float4 BulletPos = GetTransform()->GetLocalPosition();

	//if (abs(InitPlayerXPosition + 1000.0f) <= abs(BulletPos.x))
	//{
	//	Death();
	//}

	if (0.2f <= GetLiveTime())
	{
		Off();
	}
}
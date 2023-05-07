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

	switch (ADValue)
	{
	case AttackDirection::Right_Up:
	{
		GetTransform()->AddLocalPosition({ 0, MoveDist });
	}
	break;
	case AttackDirection::Right_DiagonalUp:
	{
		GetTransform()->AddLocalPosition({ MoveDist / 2, MoveDist / 2 });
	}
	break;
	case AttackDirection::Right_Front:
	{
		GetTransform()->AddLocalPosition({ MoveDist, 0 });
	}
	break;
	case AttackDirection::Right_DiagonalDown:
	{
		GetTransform()->AddLocalPosition({ (MoveDist / 2), -(MoveDist / 2) });
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
		GetTransform()->AddLocalPosition({ -(MoveDist / 2), (MoveDist / 2) });
	}
	break;
	case AttackDirection::Left_Front:
	{
		GetTransform()->AddLocalPosition({ -MoveDist, 0 });
	}
	break;
	case AttackDirection::Left_DiagonalDown:
	{
		GetTransform()->AddLocalPosition({ -(MoveDist / 2), -(MoveDist / 2) });
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
	float4 BulletPos = GetTransform()->GetLocalPosition();

	if (abs(InitPlayerXPosition + 1000.0f) <= abs(BulletPos.x))
	{
		Death();
	}
}
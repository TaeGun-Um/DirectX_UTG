#include "PrecompileHeader.h"
#include "Werner_Werman.h"

#include <GameEngineBase/GameEngineRandom.h>

void Werner_Werman::ChangeState_Cannon(CannonState _StateValue)
{
	CannonState NextState = _StateValue;
	CannonState PrevState = CannonStateValue;

	CannonStateValue = NextState;

	switch (NextState)
	{
	case CannonState::Out:
		Cannon_OutStart();
		break;
	case CannonState::Idle:
		Cannon_IdleStart();
		break;
	case CannonState::Fire:
		Cannon_FireStart();
		break;
	case CannonState::In:
		Cannon_InStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case CannonState::Out:
		Cannon_OutEnd();
		break;
	case CannonState::Idle:
		Cannon_IdleEnd();
		break;
	case CannonState::Fire:
		Cannon_FireEnd();
		break;
	case CannonState::In:
		Cannon_InEnd();
		break;
	default:
		break;
	}
}

void Werner_Werman::UpdateState_Cannon(float _DeltaTime)
{
	switch (CannonStateValue)
	{
	case CannonState::Out:
		Cannon_OutUpdate(_DeltaTime);
		break;
	case CannonState::Idle:
		Cannon_IdleUpdate(_DeltaTime);
		break;
	case CannonState::Fire:
		Cannon_FireUpdate(_DeltaTime);
		break;
	case CannonState::In:
		Cannon_InUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Werner_Werman::Cannon_OutStart()
{
	WeaponRender->GetTransform()->SetLocalPosition({ -70, 250 });
	WeaponRender->On();
	WeaponRender->ChangeAnimation("Cannon_Out");
}
void Werner_Werman::Cannon_OutUpdate(float _DeltaTime)
{
	if (true == WeaponRender->IsAnimationEnd())
	{
		ChangeState_Cannon(CannonState::Idle);
	}
}
void Werner_Werman::Cannon_OutEnd()
{

}

void Werner_Werman::Cannon_InStart()
{
	IsFire = false;
	CannonFireCount = 0;
	WeaponRender->ChangeAnimation("Cannon_In");
}
void Werner_Werman::Cannon_InUpdate(float _DeltaTime)
{
	if (true == WeaponRender->IsAnimationEnd())
	{
		CannonAble = false;
		WeaponType = false;
		WeaponRender->Off();
	}
}
void Werner_Werman::Cannon_InEnd()
{

}

void Werner_Werman::Cannon_IdleStart()
{
	CannonFireRand = 1;
	CannonFireMaxCount = 6;
	WeaponRender->ChangeAnimation("Cannon_Idle");
}
void Werner_Werman::Cannon_IdleUpdate(float _DeltaTime)
{
	if ((CannonFireMaxCount - 2) == CannonFireCount && 1 == CannonFireRand)
	{
		CannonFireRand = 0;
		int RandC = GameEngineRandom::MainRandom.RandomInt(0, 1);

		if (0 == RandC)
		{
			++CannonFireCount;
		}
	}

	if (CannonFireMaxCount > CannonFireCount)
	{
		FireTime += _DeltaTime;
	}
	
	if (0.7f <= FireTime)
	{
		CannonFireTime += _DeltaTime;
	}

	if (0.5f <= CannonFireTime)
	{
		if (2 <= CannonLoopCount)
		{
			FireTime = 0.0f;
			CannonFireTime = 0.0f;
			CannonLoopCount = 0;
			return;
		}

		CannonFireTime = 0.0f;
		++CannonLoopCount;
		IsFire = true;
	}

	if (true == IsFire)
	{
		IsFire = false;
		ChangeState_Cannon(CannonState::Fire);
	}

	if (CannonFireMaxCount <= CannonFireCount)
	{
		CannonFireTime = 0.0f;
		FireTime = 0.0f;
		CannonLoopCount = 0;
		ChangeState_Cannon(CannonState::In);
	}
}
void Werner_Werman::Cannon_IdleEnd()
{

}

void Werner_Werman::Cannon_FireStart()
{
	WeaponRender->ChangeAnimation("Cannon_Fire");
	IsCreateCherryBomb = true;
}
void Werner_Werman::Cannon_FireUpdate(float _DeltaTime)
{
	if (1 == WeaponRender->GetCurrentFrame() && true == IsCreateCherryBomb)
	{
		IsCreateCherryBomb = false;
		CreateCherryBomb();
		++CannonFireCount;
	}

	if (true == WeaponRender->IsAnimationEnd())
	{
		ChangeState_Cannon(CannonState::Idle);
	}
}
void Werner_Werman::Cannon_FireEnd()
{

}
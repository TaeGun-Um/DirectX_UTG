#include "PrecompileHeader.h"
#include "Werner_Werman.h"

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
	CannonfireCount = 0;
	WeaponRender->ChangeAnimation("Cannon_In");
}
void Werner_Werman::Cannon_InUpdate(float _DeltaTime)
{
	if (true == WeaponRender->IsAnimationEnd())
	{
		CannonAble = false;
		WeaponRender->Off();
	}
}
void Werner_Werman::Cannon_InEnd()
{

}

void Werner_Werman::Cannon_IdleStart()
{
	WeaponRender->ChangeAnimation("Cannon_Idle");
}
void Werner_Werman::Cannon_IdleUpdate(float _DeltaTime)
{
	if (5 >= CannonfireCount)
	{
		FireTime += _DeltaTime;
	}
	
	if (1.0f <= FireTime)
	{
		FireTime = 0.0f;
		IsFire = true;
	}

	if (true == IsFire)
	{
		IsFire = false;
		++CannonfireCount;
		ChangeState_Cannon(CannonState::Fire);
	}

	if (5 < CannonfireCount)
	{
		ChangeState_Cannon(CannonState::In);
	}
}
void Werner_Werman::Cannon_IdleEnd()
{
	FireTime = 0.0f;
}

void Werner_Werman::Cannon_FireStart()
{
	WeaponRender->ChangeAnimation("Cannon_Fire");
}
void Werner_Werman::Cannon_FireUpdate(float _DeltaTime)
{
	if (true == WeaponRender->IsAnimationEnd())
	{
		ChangeState_Cannon(CannonState::Idle);
	}
}
void Werner_Werman::Cannon_FireEnd()
{

}
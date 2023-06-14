#include "PrecompileHeader.h"
#include "Werner_Werman.h"

void Werner_Werman::ChangeState_Catapult(CatapultState _StateValue)
{
	CatapultState NextState = _StateValue;
	CatapultState PrevState = CatapultStateValue;

	CatapultStateValue = NextState;

	switch (NextState)
	{
	case CatapultState::Out:
		Catapult_OutStart();
		break;
	case CatapultState::Loop:
		Catapult_LoopStart();
		break;
	case CatapultState::Reload:
		Catapult_ReloadStart();
		break;
	case CatapultState::Reload_Loop:
		Catapult_Reload_LoopStart();
		break;
	case CatapultState::Fire:
		Catapult_FireStart();
		break;
	case CatapultState::In:
		Catapult_InStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case CatapultState::Out:
		Catapult_OutEnd();
		break;
	case CatapultState::Loop:
		Catapult_LoopEnd();
		break;
	case CatapultState::Reload:
		Catapult_ReloadEnd();
		break;
	case CatapultState::Reload_Loop:
		Catapult_Reload_LoopEnd();
		break;
	case CatapultState::Fire:
		Catapult_FireEnd();
		break;
	case CatapultState::In:
		Catapult_InEnd();
		break;
	default:
		break;
	}
}

void Werner_Werman::UpdateState_Catapult(float _DeltaTime)
{
	switch (CatapultStateValue)
	{
	case CatapultState::Out:
		Catapult_OutUpdate(_DeltaTime);
		break;
	case CatapultState::Loop:
		Catapult_LoopUpdate(_DeltaTime);
		break;
	case CatapultState::Reload:
		Catapult_ReloadUpdate(_DeltaTime);
		break;
	case CatapultState::Reload_Loop:
		Catapult_Reload_LoopUpdate(_DeltaTime);
		break;
	case CatapultState::Fire:
		Catapult_FireUpdate(_DeltaTime);
		break;
	case CatapultState::In:
		Catapult_InUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Werner_Werman::Catapult_OutStart()
{
	CatapultFireCount = 0;

	CatapultStartPosition = float4{ -30, 10 };
	CatapultEndPosition = float4{ -30, 260 };

	WeaponRender->GetTransform()->SetLocalPosition(CatapultStartPosition);
	WeaponRender->On();

	WeaponRender->ChangeAnimation("Catapult_Loop");
}
void Werner_Werman::Catapult_OutUpdate(float _DeltaTime)
{
	CatapultLoopTime += _DeltaTime;

	float4 NewPos = float4::Lerp(CatapultStartPosition, CatapultEndPosition, CatapultLoopTime * 1.2f);
	WeaponRender->GetTransform()->SetLocalPosition(NewPos);

	float4 CurPos = WeaponRender->GetTransform()->GetLocalPosition();

	if (CatapultEndPosition.y <= CurPos.y)
	{
		WeaponRender->GetTransform()->SetLocalPosition(CatapultEndPosition);
		ChangeState_Catapult(CatapultState::Loop);
	}
}
void Werner_Werman::Catapult_OutEnd()
{
	CatapultLoopTime = 0.0f;
}

void Werner_Werman::Catapult_InStart()
{
	WeaponRender->ChangeAnimation("Catapult_Loop");
}
void Werner_Werman::Catapult_InUpdate(float _DeltaTime)
{
	CatapultLoopTime += _DeltaTime;

	float4 NewPos = float4::Lerp(CatapultEndPosition, CatapultStartPosition, CatapultLoopTime * 1.2f);
	WeaponRender->GetTransform()->SetLocalPosition(NewPos);

	float4 CurPos = WeaponRender->GetTransform()->GetLocalPosition();

	if (CatapultStartPosition.y >= CurPos.y)
	{
		WeaponRender->GetTransform()->SetLocalPosition(CatapultStartPosition);
		CatapultLoopTime = 0.0f;
		CatapultAble = false;
		WeaponType = true;
		WeaponRender->Off();
	}
}
void Werner_Werman::Catapult_InEnd()
{
	
}

void Werner_Werman::Catapult_LoopStart()
{
	WeaponRender->ChangeAnimation("Catapult_Loop");
}
void Werner_Werman::Catapult_LoopUpdate(float _DeltaTime)
{
	CatapultLoopTime += _DeltaTime;

	if (CatapultFireCount < 2)
	{
		if (0.9f <= CatapultLoopTime)
		{
			ChangeState_Catapult(CatapultState::Reload);
		}
	}
	else
	{
		if (0.9f <= CatapultLoopTime)
		{
			ChangeState_Catapult(CatapultState::In);
		}
	}
}
void Werner_Werman::Catapult_LoopEnd()
{
	CatapultLoopTime = 0.0f;
}

void Werner_Werman::Catapult_ReloadStart()
{
	WeaponRender->ChangeAnimation("Catapult_Reload");
}
void Werner_Werman::Catapult_ReloadUpdate(float _DeltaTime)
{
	if (true == WeaponRender->IsAnimationEnd())
	{
		ChangeState_Catapult(CatapultState::Reload_Loop);
	}
}
void Werner_Werman::Catapult_ReloadEnd()
{

}

void Werner_Werman::Catapult_Reload_LoopStart()
{
	WeaponRender->ChangeAnimation("Catapult_Reload_Loop");
}
void Werner_Werman::Catapult_Reload_LoopUpdate(float _DeltaTime)
{
	CatapultReLoadLoopTime += _DeltaTime;

	if (1.0f <= CatapultReLoadLoopTime)
	{
		ChangeState_Catapult(CatapultState::Fire);
	}
}
void Werner_Werman::Catapult_Reload_LoopEnd()
{
	CatapultReLoadLoopTime = 0.0f;
}

void Werner_Werman::Catapult_FireStart()
{
	WeaponRender->ChangeAnimation("Catapult_Fire");
}
void Werner_Werman::Catapult_FireUpdate(float _DeltaTime)
{
	if (true == WeaponRender->IsAnimationEnd())
	{
		++CatapultFireCount;
		ChangeState_Catapult(CatapultState::Loop);
	}
}
void Werner_Werman::Catapult_FireEnd()
{

}
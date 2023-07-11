#include "PrecompileHeader.h"
#include "GrimMatchstick.h"

#include <GameEngineBase/GameEngineRandom.h>

void GrimMatchstick::ChangeState(DragonState _StateValue)
{
	DragonState NextState = _StateValue;
	DragonState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case DragonState::Intro:
		IntroStart();
		break;
	case DragonState::Idle:
		IdleStart();
		break;
	case DragonState::Meteor_Intro:
		Meteor_IntroStart();
		break;
	case DragonState::Meteor_Intro_Loop:
		Meteor_Intro_LoopStart();
		break;
	case DragonState::Meteor_Shoot:
		Meteor_ShootStart();
		break;
	case DragonState::Meteor_Shoot_LollBack:
		Meteor_Shoot_LollBackStart();
		break;
	case DragonState::Meteor_Outro:
		Meteor_OutroStart();
		break;
	case DragonState::Peashoot_Intro:
		Peashoot_IntroStart();
		break;
	case DragonState::Peashoot_Shoot:
		Peashoot_ShootStart();
		break;
	case DragonState::Peashoot_Shoot_Plus:
		Peashoot_Shoot_PlusStart();
		break;
	case DragonState::Peashoot_Outro:
		Peashoot_OutroStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case DragonState::Intro:
		IntroEnd();
		break;
	case DragonState::Idle:
		IdleEnd();
		break;
	case DragonState::Meteor_Intro:
		Meteor_IntroEnd();
		break;
	case DragonState::Meteor_Intro_Loop:
		Meteor_Intro_LoopEnd();
		break;
	case DragonState::Meteor_Shoot:
		Meteor_ShootEnd();
		break;
	case DragonState::Meteor_Shoot_LollBack:
		Meteor_Shoot_LollBackEnd();
		break;
	case DragonState::Meteor_Outro:
		Meteor_OutroEnd();
		break;
	case DragonState::Peashoot_Intro:
		Peashoot_IntroEnd();
		break;
	case DragonState::Peashoot_Shoot:
		Peashoot_ShootEnd();
		break;
	case DragonState::Peashoot_Shoot_Plus:
		Peashoot_Shoot_PlusEnd();
		break;
	case DragonState::Peashoot_Outro:
		Peashoot_OutroEnd();
		break;
	default:
		break;
	}
}

void GrimMatchstick::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case DragonState::Intro:
		IntroUpdate(_DeltaTime);
		break;
	case DragonState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	case DragonState::Meteor_Intro:
		Meteor_IntroUpdate(_DeltaTime);
		break;
	case DragonState::Meteor_Intro_Loop:
		Meteor_Intro_LoopUpdate(_DeltaTime);
		break;
	case DragonState::Meteor_Shoot:
		Meteor_ShootUpdate(_DeltaTime);
		break;
	case DragonState::Meteor_Shoot_LollBack:
		Meteor_Shoot_LollBackUpdate(_DeltaTime);
		break;
	case DragonState::Meteor_Outro:
		Meteor_OutroUpdate(_DeltaTime);
		break;
	case DragonState::Peashoot_Intro:
		Peashoot_IntroUpdate(_DeltaTime);
		break;
	case DragonState::Peashoot_Shoot:
		Peashoot_ShootUpdate(_DeltaTime);
		break;
	case DragonState::Peashoot_Shoot_Plus:
		Peashoot_Shoot_PlusUpdate(_DeltaTime);
		break;
	case DragonState::Peashoot_Outro:
		Peashoot_OutroUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void GrimMatchstick::Phase1_ChangeStateCountFunction()
{
	ChangeStateCount += 1;
}

void GrimMatchstick::Phase1_MeteorCountFunction()
{
	MeteorCount += 1;
}

void GrimMatchstick::Phase1_PeashootCountFunction()
{
	PeashootCount += 1;
}

void GrimMatchstick::Phase1_MeteorMaxCountFunction()
{
	MeteorMax += 1;
	CreateMeteor();
}

void GrimMatchstick::Phase1_PeashootMaxCountFunction()
{
	PeashootMax += 1;

	if (1 == PeashootMax || 3 == PeashootMax || 6 == PeashootMax)
	{
		GetRingAngleWithDotProduct3D();
		RingCreate = true;
	}
}

void GrimMatchstick::IntroStart()
{
	RenderPtr->ChangeAnimation("Dragon_Intro");

	ChangeStateCount = 0;
	MeteorCount = 0;
	PeashootCount = 0;

	RenderPtr->SetAnimationStartEvent("Dragon_Idle", 15, std::bind(&GrimMatchstick::Phase1_ChangeStateCountFunction, this));
	RenderPtr->SetAnimationStartEvent("Dragon_MeteorAttack_Intro_Loop", 6, std::bind(&GrimMatchstick::Phase1_MeteorCountFunction, this));
	RenderPtr->SetAnimationStartEvent("Dragon_PeashotAttack_Shoot", 15, std::bind(&GrimMatchstick::Phase1_PeashootCountFunction, this));
	RenderPtr->SetAnimationStartEvent("Dragon_MeteorAttack_Shoot_Front", 7, std::bind(&GrimMatchstick::Phase1_MeteorMaxCountFunction, this));
	RenderPtr->SetAnimationStartEvent("Dragon_PeashotAttack_Shoot", 15, std::bind(&GrimMatchstick::Phase1_PeashootMaxCountFunction, this));
}
void GrimMatchstick::IntroUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(DragonState::Idle);
		return;
	}
}
void GrimMatchstick::IntroEnd()
{

}

void GrimMatchstick::IdleStart()
{
	RenderPtr->ChangeAnimation("Dragon_Idle");
}
void GrimMatchstick::IdleUpdate(float _DeltaTime)
{
	if (3 == ChangeStateCount)
	{
		ChangeStateCount = 0;
		//int RandC = GameEngineRandom::MainRandom.RandomInt(0, 1);

		//if (0 == RandC)
		//{
		//	ChangeState(DragonState::Meteor_Intro);
		//	return;
		//}
		//else
		//{
		//	ChangeState(DragonState::Peashoot_Intro);
		//	return;
		//}

		ChangeState(DragonState::Peashoot_Intro);
		return;
	}
}
void GrimMatchstick::IdleEnd()
{

}

void GrimMatchstick::Meteor_IntroStart()
{
	RenderPtr->ChangeAnimation("Dragon_MeteorAttack_Intro");
}
void GrimMatchstick::Meteor_IntroUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(DragonState::Meteor_Intro_Loop);
		return;
	}
}
void GrimMatchstick::Meteor_IntroEnd()
{

}

void GrimMatchstick::Meteor_Intro_LoopStart()
{
	RenderPtr->ChangeAnimation("Dragon_MeteorAttack_Intro_Loop");
}
void GrimMatchstick::Meteor_Intro_LoopUpdate(float _DeltaTime)
{
	if (4 == MeteorCount)
	{
		MeteorCount = 0;
		ChangeState(DragonState::Meteor_Shoot);
		return;
	}
}
void GrimMatchstick::Meteor_Intro_LoopEnd()
{

}

void GrimMatchstick::Meteor_ShootStart()
{
	RenderPtr->ChangeAnimation("Dragon_MeteorAttack_Shoot_Front");
}
void GrimMatchstick::Meteor_ShootUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		if (1 >= MeteorMax)
		{
			int RandC = GameEngineRandom::MainRandom.RandomInt(0, 1);

			if (0 == RandC)
			{
				ChangeState(DragonState::Meteor_Shoot_LollBack);
				return;
			}
			else
			{
				ChangeState(DragonState::Meteor_Outro);
				return;
			}
		}
		else
		{
			ChangeState(DragonState::Meteor_Outro);
			return;
		}
	}
}
void GrimMatchstick::Meteor_ShootEnd()
{

}

void GrimMatchstick::Meteor_Shoot_LollBackStart()
{
	RenderPtr->ChangeAnimation("Dragon_MeteorAttack_Shoot_LollBack");
}
void GrimMatchstick::Meteor_Shoot_LollBackUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(DragonState::Meteor_Intro_Loop);
		return;
	}
}
void GrimMatchstick::Meteor_Shoot_LollBackEnd()
{

}

void GrimMatchstick::Meteor_OutroStart()
{
	RenderPtr->ChangeAnimation("Dragon_MeteorAttack_Outro");
}
void GrimMatchstick::Meteor_OutroUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(DragonState::Idle);
		return;
	}
}
void GrimMatchstick::Meteor_OutroEnd()
{
	MeteorMax = 0;
}

void GrimMatchstick::Peashoot_IntroStart()
{
	RenderPtr->ChangeAnimation("Dragon_PeashotAttack_Intro");
}
void GrimMatchstick::Peashoot_IntroUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(DragonState::Peashoot_Shoot);
		return;
	}
}
void GrimMatchstick::Peashoot_IntroEnd()
{

}

void GrimMatchstick::Peashoot_ShootStart()
{
	EyeRenderPtr->On();
	RenderPtr->ChangeAnimation("Dragon_PeashotAttack_Shoot");
}
void GrimMatchstick::Peashoot_ShootUpdate(float _DeltaTime)
{
	if (5 <= PeashootMax)
	{
		int RandC = GameEngineRandom::MainRandom.RandomInt(0, 1);

		if (0 == RandC)
		{
			ChangeState(DragonState::Peashoot_Shoot_Plus);
			return;
		}
		else
		{
			ChangeState(DragonState::Peashoot_Outro);
			return;
		}
	}
}
void GrimMatchstick::Peashoot_ShootEnd()
{

}

void GrimMatchstick::Peashoot_Shoot_PlusStart()
{
	RenderPtr->ChangeAnimation("Dragon_PeashotAttack_Shoot");
}
void GrimMatchstick::Peashoot_Shoot_PlusUpdate(float _DeltaTime)
{
	if (8 <= PeashootMax)
	{
		ChangeState(DragonState::Peashoot_Outro);
		return;
	}
}
void GrimMatchstick::Peashoot_Shoot_PlusEnd()
{

}

void GrimMatchstick::Peashoot_OutroStart()
{
	EyeRenderPtr->Off();
	EyeRenderPtr->ChangeAnimation("SFX_EyesAttack");
	RenderPtr->ChangeAnimation("Dragon_PeashotAttack_Outro");
}
void GrimMatchstick::Peashoot_OutroUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(DragonState::Idle);
		return;
	}
}
void GrimMatchstick::Peashoot_OutroEnd()
{
	PeashootMax = 0;
}
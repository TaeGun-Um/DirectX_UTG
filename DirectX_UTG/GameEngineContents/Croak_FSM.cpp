#include "PrecompileHeader.h"
#include "Croak.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "Player.h"
#include "Ribby.h"

void Croak::ChangeState(CroakState _StateValue)
{
	CroakState NextState = _StateValue;
	CroakState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case CroakState::Intro:
		IntroStart();
		break;
	case CroakState::Idle:
		IdleStart();
		break;
	case CroakState::CreateMob_Start:
		CreateMob_StartStart();
		break;
	case CroakState::CreateMob_Start_Loop:
		CreateMob_Start_LoopStart();
		break;
	case CroakState::CreateMob_Start_Out:
		CreateMob_Start_OutStart();
		break;
	case CroakState::CreateMob:
		CreateMobStart();
		break;
	case CroakState::CreateMob_End:
		CreateMob_EndStart();
		break;
	case CroakState::Fan_Intro:
		Fan_IntroStart();
		break;
	case CroakState::Fan_Loop_A:
		Fan_Loop_AStart();
		break;
	case CroakState::Fan_Loop_B:
		Fan_Loop_BStart();
		break;
	case CroakState::Fan_End:
		Fan_EndStart();
		break;
	case CroakState::Slot_Morph_Intro:
		Slot_Morph_IntroStart();
		break;
	case CroakState::Slot_Morph_Intro_Loop:
		Slot_Morph_Intro_LoopStart();
		break;
	case CroakState::Slot_Morph_Outro:
		Slot_Morph_OutroStart();
		break;
	case CroakState::Slot_InitialOpen:
		Slot_InitialOpenStart();
		break;
	case CroakState::Slot_Idle:
		Slot_IdleStart();
		break;
	case CroakState::Slot_Death:
		Slot_DeathStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case CroakState::Intro:
		IntroEnd();
		break;
	case CroakState::Idle:
		IdleEnd();
		break;
	case CroakState::CreateMob_Start:
		CreateMob_StartEnd();
		break;
	case CroakState::CreateMob_Start_Loop:
		CreateMob_Start_LoopEnd();
		break;
	case CroakState::CreateMob_Start_Out:
		CreateMob_Start_OutEnd();
		break;
	case CroakState::CreateMob:
		CreateMobEnd();
		break;
	case CroakState::CreateMob_End:
		CreateMob_EndEnd();
		break;
	case CroakState::Fan_Intro:
		Fan_IntroEnd();
		break;
	case CroakState::Fan_Loop_A:
		Fan_Loop_AEnd();
		break;
	case CroakState::Fan_Loop_B:
		Fan_Loop_BEnd();
		break;
	case CroakState::Fan_End:
		Fan_EndEnd();
		break;
	case CroakState::Slot_Morph_Intro:
		Slot_Morph_IntroEnd();
		break;
	case CroakState::Slot_Morph_Intro_Loop:
		Slot_Morph_Intro_LoopEnd();
		break;
	case CroakState::Slot_Morph_Outro:
		Slot_Morph_OutroEnd();
		break;
	case CroakState::Slot_InitialOpen:
		Slot_InitialOpenEnd();
		break;
	case CroakState::Slot_Idle:
		Slot_IdleEnd();
		break;
	case CroakState::Slot_Death:
		Slot_DeathEnd();
		break;
	default:
		break;
	}
}

void Croak::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case CroakState::Intro:
		IntroUpdate(_DeltaTime);
		break;
	case CroakState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	case CroakState::CreateMob_Start:
		CreateMob_StartUpdate(_DeltaTime);
		break;
	case CroakState::CreateMob_Start_Loop:
		CreateMob_Start_LoopUpdate(_DeltaTime);
		break;
	case CroakState::CreateMob_Start_Out:
		CreateMob_Start_OutUpdate(_DeltaTime);
		break;
	case CroakState::CreateMob:
		CreateMobUpdate(_DeltaTime);
		break;
	case CroakState::CreateMob_End:
		CreateMob_EndUpdate(_DeltaTime);
		break;
	case CroakState::Fan_Intro:
		Fan_IntroUpdate(_DeltaTime);
		break;
	case CroakState::Fan_Loop_A:
		Fan_Loop_AUpdate(_DeltaTime);
		break;
	case CroakState::Fan_Loop_B:
		Fan_Loop_BUpdate(_DeltaTime);
		break;
	case CroakState::Fan_End:
		Fan_EndUpdate(_DeltaTime);
		break;
	case CroakState::Slot_Morph_Intro:
		Slot_Morph_IntroUpdate(_DeltaTime);
		break;
	case CroakState::Slot_Morph_Intro_Loop:
		Slot_Morph_Intro_LoopUpdate(_DeltaTime);
		break;
	case CroakState::Slot_Morph_Outro:
		Slot_Morph_OutroUpdate(_DeltaTime);
		break;
	case CroakState::Slot_InitialOpen:
		Slot_InitialOpenUpdate(_DeltaTime);
		break;
	case CroakState::Slot_Idle:
		Slot_IdleUpdate(_DeltaTime);
		break;
	case CroakState::Slot_Death:
		Slot_DeathUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Croak::IntroStart()
{
	RenderPtr->ChangeAnimation("Croaks_Intro");
}
void Croak::IntroUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(CroakState::Idle);
		return;
	}
}
void Croak::IntroEnd()
{
	IsIntro = false;
}
	 
void Croak::IdleStart()
{
	PlusBodyCollisionPtr->GetTransform()->SetLocalScale({ 200, 200, 1 });
	PlusBodyCollisionPtr->GetTransform()->SetLocalPosition({ -8, -220 });

	PlusEXCollisionPtr->GetTransform()->SetLocalScale({ 200, 200, 1 });
	PlusEXCollisionPtr->GetTransform()->SetLocalPosition({ -8, -220 });

	RenderPtr->ChangeAnimation("Croaks_Idle");

	// 지울것
	float4 CurPos = Ribby::RibbyPtr->GetTransform()->GetLocalPosition();

	Ribby::RibbyPtr->GetTransform()->SetLocalPosition({ CurPos.x - 860.0f, CurPos.y });

	Ribby::RibbyPtr->Directbool = true;
	Ribby::RibbyPtr->BodyCollisionPtr->Off();
	Ribby::RibbyPtr->EXCollisionPtr->Off();

	RollPatter = 1;
	//
}
void Croak::IdleUpdate(float _DeltaTime)
{
	if (true == IsIntro)
	{
		ChangeState(CroakState::Intro);
		return;
	}

	// 지울것
	IdleDelayTime += _DeltaTime;

	if (IdleDelayTime >= 0.25f && 1 == RollPatter)
	{
		ChangeState(CroakState::Slot_Morph_Intro);
		++RollPatter;
		IdleDelayTime = 0.0f;
		Ribby::RibbyPtr->IsRoll = true;
		return;
	}
	// 지울것

	//if (400.0f >= HP)
	//{
	//	Ribby::RibbyPtr->IsClap = false;
	//	return;
	//}

	//if (false == Ribby::RibbyPtr->IsFistAttak && false == Ribby::RibbyPtr->IsRoll)
	//{
	//	IdleDelayTime += _DeltaTime;
	//}

	//if (IdleDelayTime >= 0.25f && 0 == RollPatter && 750.0f >= HP)
	//{
	//	++RollPatter;
	//	IdleDelayTime = 0.0f;
	//	Ribby::RibbyPtr->IsRoll = true;
	//	return;
	//}

	//if (IdleDelayTime >= 1.5f && false == Ribby::RibbyPtr->IsRoll && 1 == RollPatter)
	//{
	//	Ribby::RibbyPtr->IsClap = true;
	//	ChangeState(CroakState::Fan_Intro);
	//	return;
	//}

	//if (750.0f >= HP)
	//{
	//	return;
	//}
	//
	//if (IdleDelayTime >= 2.f)
	//{
	//	IdleDelayTime = 0.0f;
	//	int RandC = GameEngineRandom::MainRandom.RandomInt(0, 1);

	//	if (0 == RandC)
	//	{
	//		if (RibbyFistCount == MaxPatternCount)
	//		{
	//			RibbyFistCount = 0;
	//			ChangeState(CroakState::CreateMob_Start);
	//			return;
	//		}
	//		else
	//		{
	//			++RibbyFistCount;
	//			Ribby::RibbyPtr->IsFistAttak = true;
	//			return;
	//		}
	//	}
	//	else
	//	{
	//		if (CroakCrateMobCount == MaxPatternCount)
	//		{
	//			CroakCrateMobCount = 0;
	//			Ribby::RibbyPtr->IsFistAttak = true;
	//			return;
	//		}
	//		else
	//		{
	//			++CroakCrateMobCount;
	//			ChangeState(CroakState::CreateMob_Start);
	//			return;
	//		}
	//	}
	//}
}
void Croak::IdleEnd()
{
	IdleDelayTime = 0.0f;
}
	 
void Croak::CreateMob_StartStart()
{
	IsCreatefly = true;
	RenderPtr->ChangeAnimation("Croaks_CreateMob_Start");
}
void Croak::CreateMob_StartUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(CroakState::CreateMob_Start_Loop);
		return;
	}
}
void Croak::CreateMob_StartEnd()
{

}
	 
void Croak::CreateMob_Start_LoopStart()
{
	RenderPtr->ChangeAnimation("Croaks_CreateMob_Start_Loop");
}
void Croak::CreateMob_Start_LoopUpdate(float _DeltaTime)
{
	CreateMob_LoopTime += _DeltaTime;

	if (CreateMob_LoopTime >= 0.8f)
	{
		ChangeState(CroakState::CreateMob_Start_Out);
		return;
	}
}
void Croak::CreateMob_Start_LoopEnd()
{
	CreateMob_LoopTime = 0.0f;
}

void Croak::CreateMob_Start_OutStart()
{
	RenderPtr->ChangeAnimation("Croaks_CreateMob_Start_Out");
}
void Croak::CreateMob_Start_OutUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd() && true == CreateLoop)
	{
		LoopCreateAction = true;
		ChangeState(CroakState::CreateMob);
		return;
	}
	else if (true == RenderPtr->IsAnimationEnd() && false == CreateLoop)
	{
		CreatePlus = 1;
		ChangeState(CroakState::CreateMob);
		return;
	}
}
void Croak::CreateMob_Start_OutEnd()
{

}

void Croak::CreateMobStart() 
{
	RenderPtr->ChangeAnimation("Croaks_CreateMob");
}
void Croak::CreateMobUpdate(float _DeltaTime) 
{
	if (2 == RenderPtr->GetCurrentFrame() && false == CreateAction)
	{
		CreateAction = true;
		++CreateMobCount;
		CreateFirefly();
	}

	if (true == RenderPtr->IsAnimationEnd() && true == LoopCreateAction)
	{
		LoopCreateAction = false;

		int RandC = GameEngineRandom::MainRandom.RandomInt(0, 1);

		if (0 == RandC)
		{
			ChangeState(CroakState::CreateMob);
			return;
		}
		else
		{
			LoopCreateEnd = true;
			ChangeState(CroakState::CreateMob_End);
			return;
		}
	}

	if (true == RenderPtr->IsAnimationEnd() && 1 == CreatePlus && false == CreateLoop)
	{
		CreatePlus = 0;
		ChangeState(CroakState::CreateMob);
		return;
	}

	if (true == RenderPtr->IsAnimationEnd() && 0 == CreatePlus && false == CreateLoop)
	{
		CreateLoop = true;
		ChangeState(CroakState::CreateMob_Start);
		return;
	}

	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(CroakState::CreateMob_End);
		return;
	}
}
void Croak::CreateMobEnd()
{
	CreateAction = false;
}
	 
void Croak::CreateMob_EndStart()
{
	CreateLoop = false;
	LoopCreateAction = false;
	CreateMobCount = 0;
	RenderPtr->ChangeAnimation("Croaks_CreateMob_End");
}
void Croak::CreateMob_EndUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(CroakState::Idle);
		return;
	}
}
void Croak::CreateMob_EndEnd()
{
	IsCreatefly = false;
}
	 
void Croak::Fan_IntroStart()
{
	PlusBodyCollisionPtr->Off();
	PlusEXCollisionPtr->Off();

	RenderPtr->ChangeAnimation("Croaks_Fan_Intro");
}
void Croak::Fan_IntroUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(CroakState::Fan_Loop_A);
		return;
	}

	if (400.0f >= HP)
	{
		Ribby::RibbyPtr->IsClap = false;
	}
}
void Croak::Fan_IntroEnd()
{

}
	 
void Croak::Fan_Loop_AStart()
{
	RenderPtr->ChangeAnimation("Croaks_Fan_LoopA");
	WindRenderPtr->ChangeAnimation("Croaks_Fan_Wind_Intro");

	PlusBodyCollisionPtr->On();
	PlusEXCollisionPtr->On();

	PlusBodyCollisionPtr->GetTransform()->SetLocalScale({ 200, 350, 1 });
	PlusBodyCollisionPtr->GetTransform()->SetLocalPosition({ -80, 50 });

	PlusEXCollisionPtr->GetTransform()->SetLocalScale({ 200, 350, 1 });
	PlusEXCollisionPtr->GetTransform()->SetLocalPosition({ -80, 50 });

	WindRenderPtr->On();
}
void Croak::Fan_Loop_AUpdate(float _DeltaTime)
{
	AFanLoopTime += _DeltaTime;

	float WindPower = 250.0f * _DeltaTime;

	Player::MainPlayer->PlayerMoveDisturbance(-WindPower);

	if (true == WindRenderPtr->FindAnimation("Croaks_Fan_Wind_Intro")->IsEnd())
	{
		WindRenderPtr->ChangeAnimation("Croaks_Fan_Wind_Loop", false);
	}

	if (0.4f <= AFanLoopTime)
	{
		WindRenderPtr->ChangeAnimation("Croaks_Fan_Wind_Loop", false);
		ChangeState(CroakState::Fan_Loop_B);
		return;
	}

	if (400.0f >= HP)
	{
		Ribby::RibbyPtr->IsClap = false;
	}
}
void Croak::Fan_Loop_AEnd()
{
	AFanLoopTime = 0.0f;
}
	 
void Croak::Fan_Loop_BStart()
{
	RenderPtr->ChangeAnimation("Croaks_Fan_LoopB");
}
void Croak::Fan_Loop_BUpdate(float _DeltaTime)
{
	BFanLoopTime += _DeltaTime;

	float WindPower = 250.0f * _DeltaTime;

	Player::MainPlayer->PlayerMoveDisturbance(-WindPower);

	if (8.5f <= BFanLoopTime)
	{
		ChangeState(CroakState::Fan_End);
		return;
	}

	if (400.0f >= HP)
	{
		Ribby::RibbyPtr->IsClap = false;
		Ribby::RibbyPtr->ClapCount = 0;
		ChangeState(CroakState::Fan_End);
		return;
	}
}
void Croak::Fan_Loop_BEnd()
{
	BFanLoopTime = 0.0f;
}
	 
void Croak::Fan_EndStart()
{
	RenderPtr->ChangeAnimation("Croaks_Fan_Outro");

	PlusBodyCollisionPtr->Off();
	PlusEXCollisionPtr->Off();

	WindRenderPtr->Off();
}
void Croak::Fan_EndUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(CroakState::Idle);
		return;
	}
}
void Croak::Fan_EndEnd()
{
	PlusBodyCollisionPtr->On();
	PlusEXCollisionPtr->On();
	IdleDelayTime += 1.0f;
}

void Croak::Slot_Morph_IntroStart()
{
	PlusBodyCollisionPtr->Off();
	PlusEXCollisionPtr->Off();

	BodyCollisionPtr->GetTransform()->SetLocalScale({ 250, 250 });
	EXCollisionPtr->GetTransform()->SetLocalScale({ 250, 250 });

	BodyCollisionPtr->GetTransform()->SetLocalPosition({ -90, -180 });
	EXCollisionPtr->GetTransform()->SetLocalPosition({ -90, -180 });

	RenderPtr->ChangeAnimation("Slot_Morph_Intro");
}
void Croak::Slot_Morph_IntroUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(CroakState::Slot_Morph_Intro_Loop);
		return;
	}
}
void Croak::Slot_Morph_IntroEnd()
{

}

void Croak::Slot_Morph_Intro_LoopStart()
{
	RenderPtr->ChangeAnimation("Slot_Morph_Intro_Loop");
}
void Croak::Slot_Morph_Intro_LoopUpdate(float _DeltaTime)
{
	if (true == IsMorph)
	{
		ChangeState(CroakState::Slot_Morph_Outro);
		return;
	}
}
void Croak::Slot_Morph_Intro_LoopEnd()
{

}

void Croak::Slot_Morph_OutroStart()
{
	SlotInvincibility = true;

	GetTransform()->AddLocalPosition({-240, 0});

	BodyCollisionPtr->Off();
	EXCollisionPtr->Off();

	RenderPtr->ChangeAnimation("Slot_Morph_Outro");
}
void Croak::Slot_Morph_OutroUpdate(float _DeltaTime)
{
	if (15 == RenderPtr->GetCurrentFrame() && 1 == SlotPositionFix)
	{
		SlotPositionFix = 0;
		GetTransform()->AddLocalPosition({ 180, -30 });
	}
	
	if (true == RenderPtr->IsAnimationEnd())
	{
		MorphDealyTime += _DeltaTime;

		BodyCollisionPtr->On();
		EXCollisionPtr->On();

		BodyCollisionPtr->GetTransform()->SetLocalScale({ 400, 500 });
		EXCollisionPtr->GetTransform()->SetLocalScale({ 400, 500 });

		BodyCollisionPtr->GetTransform()->SetLocalPosition({ 30, -50 });
		EXCollisionPtr->GetTransform()->SetLocalPosition({ 30, -50 });
	}

	if (0.7f <= MorphDealyTime)
	{
		ChangeState(CroakState::Slot_InitialOpen);
		return;
	}
}
void Croak::Slot_Morph_OutroEnd()
{
	MorphDealyTime = 0.0f;
}

void Croak::Slot_InitialOpenStart()
{
	RenderPtr->ChangeAnimation("Slot_InitialOpen");
}
void Croak::Slot_InitialOpenUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(CroakState::Slot_Idle);
		return;
	}
}
void Croak::Slot_InitialOpenEnd()
{

}

void Croak::Slot_IdleStart()
{
	SlotInvincibility = true;

	RenderPtr->ChangeAnimation("Slot_Idle");
}
void Croak::Slot_IdleUpdate(float _DeltaTime)
{
	CoinAttackTime += _DeltaTime;

	if (2.0f <= CoinAttackTime)
	{
		CoinAttackTime = 0.0f;
		SlotMouthRenderPtr->On();
	}

	if (5 == SlotMouthRenderPtr->GetCurrentFrame())
	{
		CreateCoinProjectile();
		SlotMouthRenderPtr->FindAnimation("Slot_CoinMouth")->CurFrame = 0;
		SlotMouthRenderPtr->Off();
	}
}
void Croak::Slot_IdleEnd()
{

}

void Croak::Slot_DeathStart()
{
	RenderPtr->ChangeAnimation("Slot_Death_Intro");
}
void Croak::Slot_DeathUpdate(float _DeltaTime)
{

}
void Croak::Slot_DeathEnd()
{

}
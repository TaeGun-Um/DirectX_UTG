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
	case CroakState::Slot_ArmMove_Intro:
		Slot_ArmMove_IntroStart();
		break;
	case CroakState::Slot_ArmMove_Loop:
		Slot_ArmMove_LoopStart();
		break;
	case CroakState::Slot_ArmMove_Outro:
		Slot_ArmMove_OutroStart();
		break;
	case CroakState::Slot_Idle:
		Slot_IdleStart();
		break;
	case CroakState::Slot_Attack_Intro:
		Slot_Attack_IntroStart();
		break;
	case CroakState::Slot_Attack_Loop:
		Slot_Attack_LoopStart();
		break;
	case CroakState::Slot_Attack_Outro:
		Slot_Attack_OutroStart();
		break;
	case CroakState::Slot_Death_Intro:
		Slot_Death_IntroStart();
		break;
	case CroakState::Slot_Death_Loop:
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
	case CroakState::Slot_ArmMove_Intro:
		Slot_ArmMove_IntroEnd();
		break;
	case CroakState::Slot_ArmMove_Loop:
		Slot_ArmMove_LoopEnd();
		break;
	case CroakState::Slot_ArmMove_Outro:
		Slot_ArmMove_OutroEnd();
		break;
	case CroakState::Slot_Idle:
		Slot_IdleEnd();
		break;
	case CroakState::Slot_Attack_Intro:
		Slot_Attack_IntroEnd();
		break;
	case CroakState::Slot_Attack_Loop:
		Slot_Attack_LoopEnd();
		break;
	case CroakState::Slot_Attack_Outro:
		Slot_Attack_OutroEnd();
		break;
	case CroakState::Slot_Death_Intro:
		Slot_Death_IntroEnd();
		break;
	case CroakState::Slot_Death_Loop:
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
	case CroakState::Slot_ArmMove_Intro:
		Slot_ArmMove_IntroUpdate(_DeltaTime);
		break;
	case CroakState::Slot_ArmMove_Loop:
		Slot_ArmMove_LoopUpdate(_DeltaTime);
		break;
	case CroakState::Slot_ArmMove_Outro:
		Slot_ArmMove_OutroUpdate(_DeltaTime);
		break;
	case CroakState::Slot_Idle:
		Slot_IdleUpdate(_DeltaTime);
		break;
	case CroakState::Slot_Attack_Intro:
		Slot_Attack_IntroUpdate(_DeltaTime);
		break;
	case CroakState::Slot_Attack_Loop:
		Slot_Attack_LoopUpdate(_DeltaTime);
		break;
	case CroakState::Slot_Attack_Outro:
		Slot_Attack_OutroUpdate(_DeltaTime);
		break;
	case CroakState::Slot_Death_Intro:
		Slot_Death_IntroUpdate(_DeltaTime);
		break;
	case CroakState::Slot_Death_Loop:
		Slot_DeathUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Croak::IntroStart()
{
	EXCollisionPtr->GetTransform()->SetLocalScale({ 150, 480, 1 });
	EXCollisionPtr->GetTransform()->SetLocalPosition({ 20, -80 });

	BodyCollisionPtr->GetTransform()->SetLocalScale({ 150, 480, 1 });
	BodyCollisionPtr->GetTransform()->SetLocalPosition({ 20, -80 });

	PlusBodyCollisionPtr->GetTransform()->SetLocalScale({ 200, 200, 1 });
	PlusBodyCollisionPtr->GetTransform()->SetLocalPosition({ -8, -220 });

	PlusEXCollisionPtr->GetTransform()->SetLocalScale({ 200, 200, 1 });
	PlusEXCollisionPtr->GetTransform()->SetLocalPosition({ -8, -220 });

	PlusEXCollisionPtr->On();
	PlusBodyCollisionPtr->On();

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
	//float4 CurPos = Ribby::RibbyPtr->GetTransform()->GetLocalPosition();

	//Ribby::RibbyPtr->GetTransform()->SetLocalPosition({ CurPos.x - 860.0f, CurPos.y });

	//Ribby::RibbyPtr->Directbool = true;
	//Ribby::RibbyPtr->BodyCollisionPtr->Off();
	//Ribby::RibbyPtr->EXCollisionPtr->Off();

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

	// 지울것 // 룰렛 테스트
	IdleDelayTime += _DeltaTime;
	Ribby::RibbyPtr->Off();

	if (IdleDelayTime >= 1.f)
	{
		CreateCoinCount = 3;
		ChangeState(CroakState::Slot_Morph_Outro);
		return;
	}
	//

	// 합체 테스트
	//if (IdleDelayTime >= 0.25f && 1 == RollPatter)
	//{
	//	ChangeState(CroakState::Slot_Morph_Intro);
	//	++RollPatter;
	//	IdleDelayTime = 0.0f;
	//	Ribby::RibbyPtr->IsRoll = true;
	//	return;
	//}
	// 지울것

	/*if (400.0f >= HP)
	{
		Ribby::RibbyPtr->IsClap = false;
		Ribby::RibbyPtr->ClapCount = 0;
		ChangeState(CroakState::Slot_Morph_Intro);
		return;
	}

	if (false == Ribby::RibbyPtr->IsFistAttak && false == Ribby::RibbyPtr->IsRoll)
	{
		IdleDelayTime += _DeltaTime;
	}

	if (IdleDelayTime >= 0.25f && 0 == RollPatter && 750.0f >= HP)
	{
		++RollPatter;
		IdleDelayTime = 0.0f;
		Ribby::RibbyPtr->IsRoll = true;
		return;
	}

	if (IdleDelayTime >= 1.5f && false == Ribby::RibbyPtr->IsRoll && 1 == RollPatter)
	{
		Ribby::RibbyPtr->IsClap = true;
		ChangeState(CroakState::Fan_Intro);
		return;
	}

	if (750.0f >= HP)
	{
		return;
	}
	
	if (IdleDelayTime >= 2.f)
	{
		IdleDelayTime = 0.0f;
		int RandC = GameEngineRandom::MainRandom.RandomInt(0, 1);

		if (0 == RandC)
		{
			if (RibbyFistCount == MaxPatternCount)
			{
				RibbyFistCount = 0;
				ChangeState(CroakState::CreateMob_Start);
				return;
			}
			else
			{
				++RibbyFistCount;
				Ribby::RibbyPtr->IsFistAttak = true;
				return;
			}
		}
		else
		{
			if (CroakCrateMobCount == MaxPatternCount)
			{
				CroakCrateMobCount = 0;
				Ribby::RibbyPtr->IsFistAttak = true;
				return;
			}
			else
			{
				++CroakCrateMobCount;
				ChangeState(CroakState::CreateMob_Start);
				return;
			}
		}
	}*/
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
		Ribby::RibbyPtr->ClapCount = 0;
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
	IdleDelayTime += _DeltaTime;

	if (1.0f <= IdleDelayTime)
	{
		IdleDelayTime = 0.0f;
		Ribby::RibbyPtr->IsRoll = true;
	}

	if (true == IsMorph)
	{
		ChangeState(CroakState::Slot_Morph_Outro);
		return;
	}
}
void Croak::Slot_Morph_Intro_LoopEnd()
{
	IdleDelayTime = 0.0f;
}

void Croak::Slot_Morph_OutroStart()
{
	SlotInvincibility = true;

	GetTransform()->AddLocalPosition({ -240, 0 });

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

	if (20 == RenderPtr->GetCurrentFrame() && 0 == SlotPositionFix)
	{
		SlotPositionFix = -1;
		CreateFrontDust();
		SlotImageBackRenderPtr->On();
		SlotImageRenderPtr0->On();
		SlotImageRenderPtr1->On();
		SlotImageRenderPtr2->On();
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

	SlotImageRenderPtr0->SetScaleToTexture("Slot_TEMP.png");
	SlotImageRenderPtr0->GetTransform()->SetLocalScale({ 60, 150 });

	SlotImageRenderPtr1->SetScaleToTexture("Slot_TEMP.png");
	SlotImageRenderPtr1->GetTransform()->SetLocalScale({ 60, 150 });

	SlotImageRenderPtr2->SetScaleToTexture("Slot_TEMP.png");
	SlotImageRenderPtr2->GetTransform()->SetLocalScale({ 60, 150 });

	SlotImageRenderPtr0->GetTransform()->SetLocalPosition(SlotViporPosition0);
	SlotImageRenderPtr1->GetTransform()->SetLocalPosition(SlotViporPosition1);
	SlotImageRenderPtr2->GetTransform()->SetLocalPosition(SlotViporPosition2);

	LowerLimit = SlotViporPosition0 + float4{ 0, -45 };
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
	if (false == IsRullet)
	{
		SlotInvincibility = true;
	}

	RulletSelectCount = 1;
	
	RenderPtr->ChangeAnimation("Slot_Idle");
}
void Croak::Slot_IdleUpdate(float _DeltaTime)
{
	if (false == IsRullet)
	{
		 // CoinAttack(_DeltaTime); mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

		if (3 == CreateCoinCount)
		{
			ChangeState(CroakState::Slot_ArmMove_Intro);
			return;
		}
	}
	else if (true == IsRullet)
	{
		RulletTime += _DeltaTime; // 임시

		if (3.5f <= RulletTime && 1 == RulletSelectCount)
		{
			RulletSelectCount = 0;

			int RandC = GameEngineRandom::MainRandom.RandomInt(0, 2);

			if (0 == RandC)
			{
				IsVipor = true;
			}
			else if (1 == RandC)
			{
				IsBison = true;
			}
			else
			{
				IsTiger = true;
			}
		}

		if (true == RulletActivateEnd)
		{
			RulletSelectDelayTime += _DeltaTime;
			RulletImageBlink(_DeltaTime);
		}

		if (3.0f <= RulletSelectDelayTime)
		{
			ChangeState(CroakState::Slot_Attack_Intro);
			return;
		}
	}
}
void Croak::Slot_IdleEnd()
{
	CoinAttackTime = 0.0f;
	RulletSelectDelayTime = 0.0f;
	ImageBlinkTime = 0.0f;
	RulletTime = 0.0f;
}

void Croak::Slot_ArmMove_IntroStart()
{
	WaveTime0 = 0.0f;
	WaveTime1 = 0.0f;
	WaveTime2 = 0.0f;
	RulletDelayTime = 0.0f;

	RulletWave0 = false;
	RulletWave1 = false;
	RulletWave2 = false;
	IsRulletActivate = false;
	RulletActivateEnd = false;

	RenderPtr->ChangeAnimation("Slot_ArmMove_Intro");
}
void Croak::Slot_ArmMove_IntroUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(CroakState::Slot_ArmMove_Loop);
		return;
	}
}
void Croak::Slot_ArmMove_IntroEnd()
{

}

void Croak::Slot_ArmMove_LoopStart()
{
	ParryCollisionPtr->On();
	RenderPtr->ChangeAnimation("Slot_ArmMove_Loop");
}
void Croak::Slot_ArmMove_LoopUpdate(float _DeltaTime)
{
	//CoinAttack(_DeltaTime);                                   MMMMMMMMMMMmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

	if (true == IsArmParry)
	{
		IsRullet = true;
		IsRulletActivate = true;
		ChangeState(CroakState::Slot_ArmMove_Outro);
		return;
	}
}
void Croak::Slot_ArmMove_LoopEnd()
{
	SlotMouthRenderPtr->Off();
	CreateCoinCount = 0;
	CoinAttackTime = 0.0f;
}

void Croak::Slot_ArmMove_OutroStart()
{
	RenderPtr->ChangeAnimation("Slot_ArmMove_Outro");
}
void Croak::Slot_ArmMove_OutroUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(CroakState::Slot_Idle);
		return;
	}
}
void Croak::Slot_ArmMove_OutroEnd()
{

}

void Croak::Slot_Attack_IntroStart()
{
	SlotInvincibility = false;

	RenderPtr->ChangeAnimation("Slot_Attack_Intro");
}
void Croak::Slot_Attack_IntroUpdate(float _DeltaTime)
{
	if (true == IsStageEnd)
	{
		ChangeState(CroakState::Slot_Death_Intro);
		return;
	}

	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(CroakState::Slot_Attack_Loop);
		return;
	}
}
void Croak::Slot_Attack_IntroEnd()
{

}

int Creta = 1;

void Croak::Slot_Attack_LoopStart()
{
	SlotFrontRenderPtr->On();

	CreateVipor = 20;
	RulletLoopTime = 0.7f;

	RenderPtr->ChangeAnimation("Slot_Attack_Loop");
}
void Croak::Slot_Attack_LoopUpdate(float _DeltaTime)
{
	if (true == IsStageEnd)
	{
		ChangeState(CroakState::Slot_Death_Intro);
		return;
	}

	if (5 == RenderPtr->GetCurrentFrame())
	{
		SlotFrontRenderPtr->SetScaleToTexture("SlotMachine_Attack_Front_006.png");
	}
	else if (4 == RenderPtr->GetCurrentFrame())
	{
		SlotFrontRenderPtr->SetScaleToTexture("SlotMachine_Attack_Front_005.png");
	}
	else if (3 == RenderPtr->GetCurrentFrame())
	{
		SlotFrontRenderPtr->SetScaleToTexture("SlotMachine_Attack_Front_004.png");
	}
	else if (2 == RenderPtr->GetCurrentFrame())
	{
		SlotFrontRenderPtr->SetScaleToTexture("SlotMachine_Attack_Front_003.png");
	}
	else if (1 == RenderPtr->GetCurrentFrame())
	{
		SlotFrontRenderPtr->SetScaleToTexture("SlotMachine_Attack_Front_002.png");
	}
	else if (0 == RenderPtr->GetCurrentFrame())
	{
		SlotFrontRenderPtr->SetScaleToTexture("SlotMachine_Attack_Front_001.png");
	}

	RulletLoopTime += _DeltaTime;

	if (true == IsVipor && 0 < CreateVipor && 0.8f <= RulletLoopTime)
	{
		RulletLoopTime = 0.0f;
		--CreateVipor;
		CreatePlatform_Vipor(); // 22개 바닥으로 소환
	}
	else if (true == IsBison && 0 < CreateVipor && 0.8f <= RulletLoopTime)
	{
		RulletLoopTime = 0.0f;
		--CreateVipor;
		CreatePlatform_Vipor(); // 22개 바닥으로 소환
		//CreatePlatform_Bison(_DeltaTime); // 11개 중간으로 소환
	}
	else if (true == IsTiger && 0 < CreateVipor && 0.8f <= RulletLoopTime)
	{
		RulletLoopTime = 0.0f;
		--CreateVipor;
		CreatePlatform_Vipor(); // 22개 바닥으로 소환
		//CreatePlatform_Tiger(_DeltaTime); // 10개 바닥
	}

	if (0 == CreateVipor && 0.5f <= RulletLoopTime)
	{
		ChangeState(CroakState::Slot_Attack_Outro);
		return;
	}
}
void Croak::Slot_Attack_LoopEnd()
{
	SlotFrontRenderPtr->Off();
	RulletLoopTime = 0.0f;
}

void Croak::Slot_Attack_OutroStart()
{
	RenderPtr->ChangeAnimation("Slot_Attack_Outro");
}
void Croak::Slot_Attack_OutroUpdate(float _DeltaTime)
{
	if (true == IsStageEnd)
	{
		ChangeState(CroakState::Slot_Death_Intro);
		return;
	}

	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(CroakState::Slot_InitialOpen);
		return;
	}
}
void Croak::Slot_Attack_OutroEnd()
{
	IsVipor = false;
	IsBison = false;
	IsTiger = false;
	IsRullet = false;
}

void Croak::Slot_Death_IntroStart()
{
	RenderPtr->ChangeAnimation("Slot_Death_Intro");
}
void Croak::Slot_Death_IntroUpdate(float _DeltaTime)
{
	if (RenderPtr->IsAnimationEnd())
	{
		ChangeState(CroakState::Slot_Death_Loop);
		return;
	}
}
void Croak::Slot_Death_IntroEnd()
{

}

void Croak::Slot_DeathStart()
{
	RenderPtr->ChangeAnimation("Slot_Death_Loop");
	ExplosionTime = 0.4f;
}
void Croak::Slot_DeathUpdate(float _DeltaTime)
{
	ExplosionTime += _DeltaTime;

	if (0.4f <= ExplosionTime)
	{
		ExplosionTime = 0.0f;
		CreateDeathExplosion(_DeltaTime);
	}
}
void Croak::Slot_DeathEnd()
{

}
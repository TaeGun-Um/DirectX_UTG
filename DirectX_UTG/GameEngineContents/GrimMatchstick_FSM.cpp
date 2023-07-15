#include "PrecompileHeader.h"
#include "GrimMatchstick.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Dragon_BackGround.h"
#include "Player.h"

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
	case DragonState::Ph2_Intro_Loop:
		Ph2_Intro_LoopStart();
		break;
	case DragonState::Ph2_Intro:
		Ph2_IntroStart();
		break;
	case DragonState::Ph2_Idle:
		Ph2_IdleStart();
		break;
	case DragonState::Ph2_Death:
		Ph2_DeathStart();
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
	case DragonState::Ph2_Intro_Loop:
		Ph2_Intro_LoopEnd();
		break;
	case DragonState::Ph2_Intro:
		Ph2_IntroEnd();
		break;
	case DragonState::Ph2_Idle:
		Ph2_IdleEnd();
		break;
	case DragonState::Ph2_Death:
		Ph2_DeathEnd();
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
	case DragonState::Ph2_Intro_Loop:
		Ph2_Intro_LoopUpdate(_DeltaTime);
		break;
	case DragonState::Ph2_Intro:
		Ph2_IntroUpdate(_DeltaTime);
		break;
	case DragonState::Ph2_Idle:
		Ph2_IdleUpdate(_DeltaTime);
		break;
	case DragonState::Ph2_Death:
		Ph2_DeathUpdate(_DeltaTime);
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

	InitPosition = GetTransform()->GetWorldPosition();

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
	//if (700.0f >= HP)
	{
		IsTailSpawn = true;
		BodyCollisionPtr->Off();
		EXCollisionPtr->Off();

		float4 CurPos = GetTransform()->GetLocalPosition();

		if (2300.0f <= CurPos.x)
		{
			if (false == Dragon_BackGround::BackGroundPtr->GetIsDragonDashEnd())
			{
				Dragon_BackGround::BackGroundPtr->SetIsDragonDash();
			}
			else
			{
				ChangeState(DragonState::Ph2_Intro_Loop);
				return;
			}

			return;
		}

		float MoveDis = 300.0f;

		MoveAccel.x += MoveDis * _DeltaTime;

		GetTransform()->AddLocalPosition(MoveAccel * _DeltaTime);

		return;
	}

	if (3 == ChangeStateCount)
	{
		ChangeStateCount = 0;
		int RandC = GameEngineRandom::MainRandom.RandomInt(0, 1);

		if (0 == RandC)
		{
			ChangeState(DragonState::Meteor_Intro);
			return;
		}
		else
		{
			ChangeState(DragonState::Peashoot_Intro);
			return;
		}
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

void GrimMatchstick::Ph2_Intro_LoopStart()
{
	BodyCollisionPtr->On();
	EXCollisionPtr->On();

	BodyCollisionPtr->GetTransform()->SetLocalScale({ 150, 450 });
	BodyCollisionPtr->GetTransform()->SetLocalPosition({ -100, 0, -50 });
	EXCollisionPtr->GetTransform()->SetLocalScale({ 150, 450 });
	EXCollisionPtr->GetTransform()->SetLocalPosition({ -100, 0, -50 });

	BodyCollisionRenderPtr->GetTransform()->SetLocalScale(BodyCollisionPtr->GetTransform()->GetLocalScale());
	BodyCollisionRenderPtr->GetTransform()->SetLocalPosition(BodyCollisionPtr->GetTransform()->GetLocalPosition());
	EXCollisionRenderPtr->GetTransform()->SetLocalScale(EXCollisionPtr->GetTransform()->GetLocalScale());
	EXCollisionRenderPtr->GetTransform()->SetLocalPosition(EXCollisionPtr->GetTransform()->GetLocalPosition());

	Plus_BodyCollisionPtr->On();
	Plus_EXCollisionPtr->On();

	Plus_BodyCollisionPtr->GetTransform()->SetLocalScale({ 300, 120 });
	Plus_BodyCollisionPtr->GetTransform()->SetLocalPosition({ 0, -200, -50 });
	Plus_EXCollisionPtr->GetTransform()->SetLocalScale({ 300, 120 });
	Plus_EXCollisionPtr->GetTransform()->SetLocalPosition({ 0, -200, -50 });

	Plus_BodyCollisionRenderPtr->On();
	Plus_EXCollisionRenderPtr->On();

	Plus_BodyCollisionRenderPtr->GetTransform()->SetLocalScale(Plus_BodyCollisionPtr->GetTransform()->GetLocalScale());
	Plus_BodyCollisionRenderPtr->GetTransform()->SetLocalPosition(Plus_BodyCollisionPtr->GetTransform()->GetLocalPosition());
	Plus_EXCollisionRenderPtr->GetTransform()->SetLocalScale(Plus_EXCollisionPtr->GetTransform()->GetLocalScale());
	Plus_EXCollisionRenderPtr->GetTransform()->SetLocalPosition(Plus_EXCollisionPtr->GetTransform()->GetLocalPosition());

	float4 CurPos = GetTransform()->GetWorldPosition();

	GetTransform()->SetWorldPosition({ -400, CurPos.y, CurPos.z });

	RenderPtr->ChangeAnimation("Dragon_Ph2_Intro_Loop");
}
void GrimMatchstick::Ph2_Intro_LoopUpdate(float _DeltaTime)
{
	float4 CurPos = GetTransform()->GetWorldPosition();

	if (130.0f >= CurPos.x)
	{
		float MoveDis = 600.0f * _DeltaTime;

		GetTransform()->AddWorldPosition({ MoveDis , 0 });
	}
	else
	{
		ChangeState(DragonState::Ph2_Intro);
		return;
	}
}
void GrimMatchstick::Ph2_Intro_LoopEnd()
{

}

void GrimMatchstick::Ph2_IntroStart()
{
	RenderPtr->ChangeAnimation("Dragon_Ph2_Intro");
}
void GrimMatchstick::Ph2_IntroUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(DragonState::Ph2_Idle);
		return;
	}
}
void GrimMatchstick::Ph2_IntroEnd()
{

}

void GrimMatchstick::Ph2_IdleStart()
{
	RenderPtr->ChangeAnimation("Dragon_Ph2_Idle");

	EyeRenderPtr->GetTransform()->SetLocalPosition({ 650, -180 });
	EyeRenderPtr->ChangeAnimation("Dragon_Ph2_Tounge_Intro");
	EyeRenderPtr->On();

	UpRenderPtr->GetTransform()->AddLocalPosition({ 0, 0, -1 });

	UpRenderPtr->On();

	ChangeState_FireRender(FireRenderState::Object_Fire_Waiting);
}
void GrimMatchstick::Ph2_IdleUpdate(float _DeltaTime)
{
	if (400.0f >= HP)
	{
		ChangeState(DragonState::Ph2_Death);
		return;
	}

	if (true == EyeRenderPtr->FindAnimation("Dragon_Ph2_Tounge_Intro")->IsEnd())
	{
		EyeRenderPtr->ChangeAnimation("Dragon_Ph2_Tounge_Intro_Loop", false);
	}

	UpRenderSetting();

	UpdateState_FireRender(_DeltaTime);

	FireWorkSpawnDelayTime += _DeltaTime;

	if (0.8f <= FireWorkSpawnDelayTime)
	{
		FireWorkSpawnDelayTime = 0.0f;
		CreateFireWork();
	}
}
void GrimMatchstick::Ph2_IdleEnd()
{

}

void GrimMatchstick::Ph2_DeathStart()
{
	FireRenderPtr->Off();
	BodyCollisionPtr->Off();
	EXCollisionPtr->Off();

	Plus_BodyCollisionPtr->Off();
	Plus_EXCollisionPtr->Off();

	RenderPtr->ChangeAnimation("Dragon_Ph2_Death");
}
void GrimMatchstick::Ph2_DeathUpdate(float _DeltaTime)
{
	UpRenderSetting_Death();

	ExplosionTime += _DeltaTime;
	Ph2DeathDelayTime += _DeltaTime;

	if (0.4f <= ExplosionTime)
	{
		ExplosionTime = 0.0f;
		Player::MainPlayer->StartCameraShaking(6);
		CreateDeathExplosion(_DeltaTime);
	}

	if (3.0f <= Ph2DeathDelayTime)
	{
		EyeRenderPtr->ChangeAnimation("Dragon_Ph2_Tounge_Outro", false);
	}
}
void GrimMatchstick::Ph2_DeathEnd()
{
	Ph2DeathDelayTime = 0.0f;
	ExplosionTime = 0.0f;
}

void GrimMatchstick::UpRenderSetting_Death()
{
	if (7 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_DeathUp_007.png");
	}
	else if (6 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_DeathUp_006.png");
	}
	else if (5 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_DeathUp_005.png");
	}
	else if (4 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_DeathUp_004.png");
	}
	else if (3 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_DeathUp_003.png");
	}
	else if (2 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_DeathUp_002.png");
	}
	else if (1 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_DeathUp_001.png");
	}
	else if (0 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_DeathUp_000.png");
	}
}

void GrimMatchstick::UpRenderSetting()
{
	if (13 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_IdleUp_013.png");
	}
	else if (12 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_IdleUp_012.png");
	}
	else if (11 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_IdleUp_011.png");
	}
	else if (10 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_IdleUp_010.png");
	}
	else if (9 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_IdleUp_009.png");
	}
	else if (8 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_IdleUp_008.png");
	}
	else if (7 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_IdleUp_007.png");
	}
	else if (6 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_IdleUp_006.png");
	}
	else if (5 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_IdleUp_005.png");
	}
	else if (4 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_IdleUp_004.png");
	}
	else if (3 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_IdleUp_003.png");
	}
	else if (2 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_IdleUp_002.png");
	}
	else if (1 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_IdleUp_001.png");
	}
	else if (0 == RenderPtr->GetCurrentFrame())
	{
		UpRenderPtr->SetScaleToTexture("Ph2_IdleUp_000.png");
	}
}
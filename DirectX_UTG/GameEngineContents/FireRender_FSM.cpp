#include "PrecompileHeader.h"
#include "GrimMatchstick.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>

void GrimMatchstick::ChangeState_FireRender(FireRenderState _StateValue)
{
	FireRenderState NextState = _StateValue;
	FireRenderState PrevState = FireStateValue;

	FireStateValue = NextState;

	switch (NextState)
	{
	case FireRenderState::Object_Fire_Waiting:
		Object_Fire_WaitingStart();
		break;
	case FireRenderState::Object_Fire_Intro:
		Object_Fire_IntroStart();
		break;
	case FireRenderState::Object_Fire_Loop:
		Object_Fire_LoopStart();
		break;
	case FireRenderState::Object_Fire_Outro:
		Object_Fire_OutroStart();
		break;
	case FireRenderState::Object_FireSmoke_Intro:
		Object_FireSmoke_IntroStart();
		break;
	case FireRenderState::Object_FireSmoke_Loop:
		Object_FireSmoke_LoopStart();
		break;
	case FireRenderState::Object_FireSmoke_Outro:
		Object_FireSmoke_OutroStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case FireRenderState::Object_Fire_Waiting:
		Object_Fire_WaitingEnd();
		break;
	case FireRenderState::Object_Fire_Intro:
		Object_Fire_IntroEnd();
		break;
	case FireRenderState::Object_Fire_Loop:
		Object_Fire_LoopEnd();
		break;
	case FireRenderState::Object_Fire_Outro:
		Object_Fire_OutroEnd();
		break;
	case FireRenderState::Object_FireSmoke_Intro:
		Object_FireSmoke_IntroEnd();
		break;
	case FireRenderState::Object_FireSmoke_Loop:
		Object_FireSmoke_LoopEnd();
		break;
	case FireRenderState::Object_FireSmoke_Outro:
		Object_FireSmoke_OutroEnd();
		break;
	default:
		break;
	}
}
void GrimMatchstick::UpdateState_FireRender(float _DeltaTime)
{
	switch (FireStateValue)
	{
	case FireRenderState::Object_Fire_Waiting:
		Object_Fire_WaitingUpdate(_DeltaTime);
		break;
	case FireRenderState::Object_Fire_Intro:
		Object_Fire_IntroUpdate(_DeltaTime);
		break;
	case FireRenderState::Object_Fire_Loop:
		Object_Fire_LoopUpdate(_DeltaTime);
		break;
	case FireRenderState::Object_Fire_Outro:
		Object_Fire_OutroUpdate(_DeltaTime);
		break;
	case FireRenderState::Object_FireSmoke_Intro:
		Object_FireSmoke_IntroUpdate(_DeltaTime);
		break;
	case FireRenderState::Object_FireSmoke_Loop:
		Object_FireSmoke_LoopUpdate(_DeltaTime);
		break;
	case FireRenderState::Object_FireSmoke_Outro:
		Object_FireSmoke_OutroUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void GrimMatchstick::Object_Fire_WaitingStart()
{
	if (false == Ph2FireSetting)
	{
		Ph2FireSetting = true;

		FireRenderPtr->GetTransform()->SetLocalPosition({ 127, 265 });

		FireCollisionPtr->GetTransform()->SetLocalScale({ 60, 400 });
		FireCollisionPtr->GetTransform()->SetLocalPosition({ 120, 200, -50 });

		FireCollisionRenderPtr->GetTransform()->SetLocalScale(FireCollisionPtr->GetTransform()->GetLocalScale());
		FireCollisionRenderPtr->GetTransform()->SetLocalPosition(FireCollisionPtr->GetTransform()->GetLocalPosition());
	}
	
	FireRenderPtr->Off();
}
void GrimMatchstick::Object_Fire_WaitingUpdate(float _DeltaTime)
{
	FireWaitingTime += _DeltaTime;

	if (1.5f <= FireWaitingTime)
	{
		FireWaitingTime = 0.0f;

		int RandC = GameEngineRandom::MainRandom.RandomInt(0, 1);

		if (0 == RandC)
		{
			ChangeState_FireRender(FireRenderState::Object_Fire_Intro);
			return;
		}
		else
		{
			ChangeState_FireRender(FireRenderState::Object_FireSmoke_Intro);
			return;
		}
	}
}
void GrimMatchstick::Object_Fire_WaitingEnd()
{
	FireRenderPtr->On();
}

void GrimMatchstick::Object_Fire_IntroStart()
{
	FireCollisionPtr->On();

	FireRenderPtr->ChangeAnimation("Object_Fire_Intro");

	EffectPlayer = GameEngineSound::Play("dragon_left_dragon_fire_start.wav");
}
void GrimMatchstick::Object_Fire_IntroUpdate(float _DeltaTime)
{
	if (true == FireRenderPtr->IsAnimationEnd())
	{
		ChangeState_FireRender(FireRenderState::Object_Fire_Loop);
		return;
	}
}
void GrimMatchstick::Object_Fire_IntroEnd()
{

}

void GrimMatchstick::Object_Fire_LoopStart()
{
	FireRenderPtr->ChangeAnimation("Object_Fire_Loop");

	EffectPlayer = GameEngineSound::Play("dragon_left_dragon_fire_loop.wav");
}
void GrimMatchstick::Object_Fire_LoopUpdate(float _DeltaTime)
{
	FireWaitingTime += _DeltaTime;

	if (3.0f <= FireWaitingTime)
	{
		FireWaitingTime = 0.0f;
		ChangeState_FireRender(FireRenderState::Object_Fire_Outro);
		return;
	}
}
void GrimMatchstick::Object_Fire_LoopEnd()
{
	FireCollisionPtr->Off();
}

void GrimMatchstick::Object_Fire_OutroStart()
{
	FireRenderPtr->ChangeAnimation("Object_Fire_Outro");

	EffectPlayer = GameEngineSound::Play("dragon_left_dragon_fire_end.wav");
}
void GrimMatchstick::Object_Fire_OutroUpdate(float _DeltaTime)
{
	if (true == FireRenderPtr->IsAnimationEnd())
	{
		ChangeState_FireRender(FireRenderState::Object_Fire_Waiting);
		return;
	}
}
void GrimMatchstick::Object_Fire_OutroEnd()
{

}

void GrimMatchstick::Object_FireSmoke_IntroStart()
{
	FireRenderPtr->ChangeAnimation("Object_FireSmoke_Intro");

	EffectPlayer = GameEngineSound::Play("dragon_left_dragon_smoke_start.wav");
}
void GrimMatchstick::Object_FireSmoke_IntroUpdate(float _DeltaTime)
{
	if (true == FireRenderPtr->IsAnimationEnd())
	{
		ChangeState_FireRender(FireRenderState::Object_FireSmoke_Loop);
		return;
	}
}
void GrimMatchstick::Object_FireSmoke_IntroEnd()
{

}

void GrimMatchstick::Object_FireSmoke_LoopStart()
{
	FireRenderPtr->ChangeAnimation("Object_FireSmoke_Loop");

	EffectPlayer = GameEngineSound::Play("dragon_left_dragon_smoke_loop.wav");
}
void GrimMatchstick::Object_FireSmoke_LoopUpdate(float _DeltaTime)
{
	FireWaitingTime += _DeltaTime;

	if (1.7f <= FireWaitingTime)
	{
		FireWaitingTime = 0.0f;
		ChangeState_FireRender(FireRenderState::Object_FireSmoke_Outro);
		return;
	}
}
void GrimMatchstick::Object_FireSmoke_LoopEnd()
{

}

void GrimMatchstick::Object_FireSmoke_OutroStart()
{
	FireRenderPtr->ChangeAnimation("Object_FireSmoke_Outro");

	EffectPlayer = GameEngineSound::Play("dragon_left_dragon_smoke_end.wav");
}
void GrimMatchstick::Object_FireSmoke_OutroUpdate(float _DeltaTime)
{
	if (true == FireRenderPtr->IsAnimationEnd())
	{
		ChangeState_FireRender(FireRenderState::Object_Fire_Waiting);
		return;
	}
}
void GrimMatchstick::Object_FireSmoke_OutroEnd()
{

}
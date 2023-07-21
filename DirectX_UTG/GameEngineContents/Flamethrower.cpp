#include "PrecompileHeader.h"
#include "Flamethrower.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "MouseLevel.h"
#include "You_Died.h"
#include "Werner_Werman.h"

Flamethrower::Flamethrower() 
{
}

Flamethrower::~Flamethrower() 
{
}

void Flamethrower::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "Flamethrower_Intro_Loop", .SpriteName = "Flamethrower_Intro_Loop", .FrameInter = 0.045f, .Loop = true, .ScaleToTexture = false });
		RenderPtr->CreateAnimation({ .AnimationName = "Flamethrower_Fire", .SpriteName = "Flamethrower_Fire", .FrameInter = 0.045f, .Loop = false, .ScaleToTexture = false });
		RenderPtr->CreateAnimation({ .AnimationName = "Flamethrower_Fire_Loop", .SpriteName = "Flamethrower_Fire_Loop", .FrameInter = 0.045f, .Loop = true, .ScaleToTexture = false });
		RenderPtr->CreateAnimation({ .AnimationName = "Flamethrower_Fire_Outro", .SpriteName = "Flamethrower_Fire_Outro", .FrameInter = 0.045f, .Loop = false, .ScaleToTexture = false });
		RenderPtr->GetTransform()->SetLocalScale({411, 360});
		RenderPtr->ChangeAnimation("Flamethrower_Intro_Loop");
		ChangeState(FireState::Intro);

		MaxAlpha = RenderPtr->ColorOptionValue.MulColor.a;
		RenderPtr->ColorOptionValue.MulColor.a = 0.0f;
		MinAlpha = RenderPtr->ColorOptionValue.MulColor.a;
	}

	if (nullptr == ProjectileCollisionPtr)
	{
		ProjectileCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
		ProjectileCollisionPtr->SetColType(ColType::SPHERE2D);
		ProjectileCollisionPtr->GetTransform()->SetLocalScale({ 400, 200, 1 });
		ProjectileCollisionPtr->GetTransform()->SetLocalPosition({ 0, -70 });
		ProjectileCollisionPtr->Off();
	}

	if (nullptr == ProjectileCollisionRenderPtr)
	{
		ProjectileCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ProjectileCollisionRenderPtr->SetTexture("GreenLine.png");
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalScale(ProjectileCollisionPtr->GetTransform()->GetLocalScale());
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalPosition(ProjectileCollisionPtr->GetTransform()->GetLocalPosition());
		ProjectileCollisionRenderPtr->Off();
	}
}

void Flamethrower::Update(float _DeltaTime)
{
	if (true == MouseLevel::MouseLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	if (true == IsDebugRender && true == ProjectileCollisionPtr->IsUpdate())
	{
		ProjectileCollisionRenderPtr->On();
	}
	else
	{
		ProjectileCollisionRenderPtr->Off();
	}

	UpdateState(_DeltaTime);

	float Movedis = Werner_Werman::WernerWermanPtr->GetPhase2MoveDistance();

	GetTransform()->AddLocalPosition({ -Movedis , 0 });
}

void Flamethrower::ChangeState(FireState _StateValue)
{
	FireState NextState = _StateValue;
	FireState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case FireState::Intro:
		IntroStart();
		break;
	case FireState::Fire:
		FireStart();
		break;
	case FireState::FireLoop:
		FireLoopStart();
		break;
	case FireState::Outro:
		OutroStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case FireState::Intro:
		IntroEnd();
		break;
	case FireState::Fire:
		FireEnd();
		break;
	case FireState::FireLoop:
		FireLoopEnd();
		break;
	case FireState::Outro:
		OutroEnd();
		break;
	default:
		break;
	}
}
void Flamethrower::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case FireState::Intro:
		IntroUpdate(_DeltaTime);
		break;
	case FireState::Fire:
		FireUpdate(_DeltaTime);
		break;
	case FireState::FireLoop:
		FireLoopUpdate(_DeltaTime);
		break;
	case FireState::Outro:
		OutroUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Flamethrower::IntroStart()
{
	RenderPtr->ChangeAnimation("Flamethrower_Intro_Loop");
}
void Flamethrower::IntroUpdate(float _DeltaTime)
{
	if (true == Werner_Werman::WernerWermanPtr->GetPhase2End())
	{
		IsEnd = true;
	}

	DelayTime += _DeltaTime;

	if (1.0f >= DelayTime)
	{
		return;
	}

	if (false == IsEnd)
	{
		if (MaxAlpha <= RenderPtr->ColorOptionValue.MulColor.a)
		{
			RenderPtr->ColorOptionValue.MulColor.a = MaxAlpha;
			IntroLoopTime += _DeltaTime;
		}
		else
		{
			RenderPtr->ColorOptionValue.MulColor.a += _DeltaTime * 2.5f;
		}

		if (0.8f <= IntroLoopTime)
		{
			ChangeState(FireState::Fire);
			return;
		}
	}
	else
	{
		if (MinAlpha <= RenderPtr->ColorOptionValue.MulColor.a)
		{
			RenderPtr->ColorOptionValue.MulColor.a -= _DeltaTime * 1.5f;
			Werner_Werman::WernerWermanPtr->SetIsFlameEnd();
		}
		else
		{
			RenderPtr->ColorOptionValue.MulColor.a = MinAlpha;
			Death();
			IntroLoopTime += _DeltaTime;
		}
	}
}
void Flamethrower::IntroEnd()
{
	IntroLoopTime = 0.0f;
}

void Flamethrower::FireStart()
{
	RenderPtr->ChangeAnimation("Flamethrower_Fire");

	int RandC = GameEngineRandom::MainRandom.RandomInt(0, 1);

	if (0 == RandC)
	{
		EffectPlayer = GameEngineSound::Play("mouse_flamethrower_01.wav");
	}
	else
	{
		EffectPlayer = GameEngineSound::Play("mouse_flamethrower_02.wav");
	}
}
void Flamethrower::FireUpdate(float _DeltaTime)
{
	if (true == Werner_Werman::WernerWermanPtr->GetPhase2End())
	{
		IsEnd = true;
		ChangeState(FireState::Outro);
		return;
	}

	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(FireState::FireLoop);
		return;
	}
}
void Flamethrower::FireEnd()
{

}

void Flamethrower::FireLoopStart()
{
	ProjectileCollisionPtr->On();
	RenderPtr->ChangeAnimation("Flamethrower_Fire_Loop");
}
void Flamethrower::FireLoopUpdate(float _DeltaTime)
{
	if (true == Werner_Werman::WernerWermanPtr->GetPhase2End())
	{
		IsEnd = true;
		ChangeState(FireState::Outro);
		return;
	}

	FireLoopTime += _DeltaTime;

	if (1.0f <= FireLoopTime)
	{
		ChangeState(FireState::Outro);
		return;
	}
}
void Flamethrower::FireLoopEnd()
{
	ProjectileCollisionPtr->Off();
}

void Flamethrower::OutroStart()
{
	RenderPtr->ChangeAnimation("Flamethrower_Fire_Outro");
}
void Flamethrower::OutroUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		IsEnd = true;
		ChangeState(FireState::Intro);
		return;
	}
}
void Flamethrower::OutroEnd()
{

}
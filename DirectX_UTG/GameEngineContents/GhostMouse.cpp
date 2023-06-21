#include "PrecompileHeader.h"
#include "GhostMouse.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Peashooter.h"
#include "Peashooter_EX.h"
#include "Spread.h"
#include "Spread_EX.h"

#include "Player.h"
#include "MouseLevel.h"
#include "You_Died.h"

GhostMouse::GhostMouse() 
{
}

GhostMouse::~GhostMouse() 
{
}

void GhostMouse::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "Ghost_Intro", .SpriteName = "Ghost_Intro", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ghost_Idle", .SpriteName = "Ghost_Idle", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ghost_Attack_Pink", .SpriteName = "Ghost_Attack_Pink", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ghost_Attack_Blue", .SpriteName = "Ghost_Attack_Blue", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ghost_Attack_Outro", .SpriteName = "Ghost_Attack_Outro", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ghost_Death", .SpriteName = "Ghost_Death", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });

		ChangeState(GhostState::Intro);
	}

	if (nullptr == BodyCollisionPtr)
	{
		BodyCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterHitBox));
		BodyCollisionPtr->SetColType(ColType::AABBBOX2D);
		BodyCollisionPtr->GetTransform()->SetLocalScale({ 180, 310, -50 });
		BodyCollisionPtr->GetTransform()->SetLocalPosition({ 0, 0 });
		BodyCollisionPtr->Off();
	}

	if (nullptr == BodyCollisionRenderPtr)
	{
		BodyCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BodyCollisionRenderPtr->GetTransform()->SetLocalScale(BodyCollisionPtr->GetTransform()->GetLocalScale());
		BodyCollisionRenderPtr->GetTransform()->SetLocalPosition(BodyCollisionPtr->GetTransform()->GetLocalPosition());
		BodyCollisionRenderPtr->SetTexture("GreenLine.png");
		BodyCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
		BodyCollisionRenderPtr->Off();
	}

	if (nullptr == EXCollisionPtr)
	{
		EXCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterHitBox));
		EXCollisionPtr->SetColType(ColType::AABBBOX2D);
		EXCollisionPtr->GetTransform()->SetLocalScale({ 180, 310, -50 });
		EXCollisionPtr->GetTransform()->SetLocalPosition({ 0, 0 });
		EXCollisionPtr->Off();
	}

	if (nullptr == EXCollisionRenderPtr)
	{
		EXCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		EXCollisionRenderPtr->GetTransform()->SetLocalScale(EXCollisionPtr->GetTransform()->GetLocalScale());
		EXCollisionRenderPtr->GetTransform()->SetLocalPosition(EXCollisionPtr->GetTransform()->GetLocalPosition());
		EXCollisionRenderPtr->SetTexture("RedLine.png");
		EXCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
		EXCollisionRenderPtr->Off();
	}
}

void GhostMouse::Update(float _DeltaTime)
{
	if (true == IsDebugRender)
	{
		if (true == BodyCollisionPtr->IsUpdate())
		{
			BodyCollisionRenderPtr->On();
			EXCollisionRenderPtr->On();
		}
		else
		{
			BodyCollisionRenderPtr->Off();
			EXCollisionRenderPtr->Off();
		}
	}
	else
	{
		BodyCollisionRenderPtr->Off();
		EXCollisionRenderPtr->Off();
	}

	CollisionCheck();
	HitBlink(_DeltaTime);
	UpdateState(_DeltaTime);
}

void GhostMouse::HitBlink(float _DeltaTime)
{
	if (false == IsBlink)
	{
		return;
	}

	BlinkTime += _DeltaTime;

	if (BlinkCount == 1)
	{
		BlinkCount = 0;

		OriginMulColor = RenderPtr->ColorOptionValue.MulColor;
		BlinkMulColor.r = 0.2f;
		BlinkMulColor.g = 0.2f;
		BlinkMulColor.b = 0.35f;
		RenderPtr->ColorOptionValue.MulColor += BlinkMulColor;
	}

	if (BlinkTime >= 0.1f)
	{
		BlinkCount = 1;
		BlinkTime = 0.0f;
		IsBlink = false;

		RenderPtr->ColorOptionValue.MulColor = OriginMulColor;
	}
}

void GhostMouse::CollisionCheck()
{
	/////////////// Normal
	if (nullptr != BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Peashooter), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& HP > 0.0f)
	{
		GameEngineActor* Projectile = BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Peashooter), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Peashooter*>(Projectile)->SetPeashooterDeath();
		dynamic_cast<Peashooter*>(Projectile)->SetHitture();
		HP -= 1.0f;

		if (0 >= HP)
		{
			HP = 0.0f;
			IsDeath = true;
		}

		IsBlink = true;
	}

	if (nullptr != BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Spread), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& HP > 0.0f)
	{
		GameEngineActor* Projectile = BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Spread), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Spread*>(Projectile)->SetSpreadDeath();
		dynamic_cast<Spread*>(Projectile)->SetHitture();
		HP -= 0.4f;

		if (0 >= HP)
		{
			HP = 0.0f;
			IsDeath = true;
		}

		IsBlink = true;
	}

	/////////////// EX
	if (nullptr != EXCollisionPtr->Collision(static_cast<int>(CollisionOrder::PeashooterEX), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& HP > 0.0f)
	{
		GameEngineActor* Projectile = EXCollisionPtr->Collision(static_cast<int>(CollisionOrder::PeashooterEX), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Peashooter_EX*>(Projectile)->SetHitture();
		HP -= 5.0f;

		if (0 >= HP)
		{
			HP = 0.0f;
			IsDeath = true;
		}

		IsBlink = true;
	}

	if (nullptr != EXCollisionPtr->Collision(static_cast<int>(CollisionOrder::SpreadEX), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& HP > 0.0f)
	{
		GameEngineActor* Projectile = EXCollisionPtr->Collision(static_cast<int>(CollisionOrder::SpreadEX), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Spread_EX*>(Projectile)->SetSpread_EXDeath();
		HP -= 10.0f;

		if (0 >= HP)
		{
			HP = 0.0f;
			IsDeath = true;
		}

		IsBlink = true;
	}
}

void GhostMouse::ChangeState(GhostState _StateValue)
{
	GhostState NextState = _StateValue;
	GhostState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case GhostState::Intro:
		IntroStart();
		break;
	case GhostState::Idle:
		IdleStart();
		break;
	case GhostState::BlueBallAttack:
		BlueBallAttackStart();
		break;
	case GhostState::PinkBallAttack:
		PinkBallAttackStart();
		break;
	case GhostState::AttackOutro:
		AttackOutroStart();
		break;
	case GhostState::Death:
		DeathStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case GhostState::Intro:
		IntroEnd();
		break;
	case GhostState::Idle:
		IdleEnd();
		break;
	case GhostState::BlueBallAttack:
		BlueBallAttackEnd();
		break;
	case GhostState::PinkBallAttack:
		PinkBallAttackEnd();
		break;
	case GhostState::AttackOutro:
		AttackOutroEnd();
		break;
	case GhostState::Death:
		DeathEnd();
		break;
	default:
		break;
	}
}
void GhostMouse::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case GhostState::Intro:
		IntroUpdate(_DeltaTime);
		break;
	case GhostState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	case GhostState::BlueBallAttack:
		BlueBallAttackUpdate(_DeltaTime);
		break;
	case GhostState::PinkBallAttack:
		PinkBallAttackUpdate(_DeltaTime);
		break;
	case GhostState::AttackOutro:
		AttackOutroUpdate(_DeltaTime);
		break;
	case GhostState::Death:
		DeathUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void GhostMouse::IntroStart()
{
	RenderPtr->ChangeAnimation("Ghost_Intro");
}
void GhostMouse::IntroUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(GhostState::Idle);
		return;
	}
}
void GhostMouse::IntroEnd()
{
	BodyCollisionPtr->On();
	EXCollisionPtr->On();
}

void GhostMouse::IdleStart()
{
	RenderPtr->ChangeAnimation("Ghost_Idle");
}
void GhostMouse::IdleUpdate(float _DeltaTime)
{
	if (true == IsDeath)
	{
		ChangeState(GhostState::Death);
		return;
	}

	AttackDelayTime += _DeltaTime;

	if (1.0f <= AttackDelayTime)
	{
		ChangeState(GhostState::BlueBallAttack);
		return;
	}
}
void GhostMouse::IdleEnd()
{
	AttackDelayTime = 0.0f;
}

void GhostMouse::BlueBallAttackStart()
{
	RenderPtr->ChangeAnimation("Ghost_Attack_Blue");
}
void GhostMouse::BlueBallAttackUpdate(float _DeltaTime)
{
	if (true == IsDeath)
	{
		ChangeState(GhostState::Death);
		return;
	}

	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(GhostState::AttackOutro);
		return;
	}
}
void GhostMouse::BlueBallAttackEnd()
{

}

void GhostMouse::PinkBallAttackStart()
{
	RenderPtr->ChangeAnimation("Ghost_Attack_Pink");
}
void GhostMouse::PinkBallAttackUpdate(float _DeltaTime)
{
	if (true == IsDeath)
	{
		ChangeState(GhostState::Death);
		return;
	}

	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(GhostState::AttackOutro);
		return;
	}
}
void GhostMouse::PinkBallAttackEnd()
{

}

void GhostMouse::AttackOutroStart()
{
	RenderPtr->ChangeAnimation("Ghost_Attack_Outro");
}
void GhostMouse::AttackOutroUpdate(float _DeltaTime)
{
	if (true == IsDeath)
	{
		ChangeState(GhostState::Death);
		return;
	}

	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(GhostState::Idle);
		return;
	}
}
void GhostMouse::AttackOutroEnd()
{

}

void GhostMouse::DeathStart()
{
	BodyCollisionPtr->Off();
	EXCollisionPtr->Off();

	RenderPtr->ChangeAnimation("Ghost_Death");
}
void GhostMouse::DeathUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		Death();
	}
}
void GhostMouse::DeathEnd()
{

}
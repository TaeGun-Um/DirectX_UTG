#include "PrecompileHeader.h"
#include "GhostMouse_Projectile.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"
#include "MouseLevel.h"
#include "You_Died.h"
#include "SmallBall.h"

GhostMouse_Projectile::GhostMouse_Projectile() 
{
}

GhostMouse_Projectile::~GhostMouse_Projectile() 
{
}

void GhostMouse_Projectile::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "GhostBullet_Blue_Intro", .SpriteName = "GhostBullet_Blue_Intro", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "GhostBullet_Pink_Intro", .SpriteName = "GhostBullet_Pink_Intro", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "GhostBullet_Blue_Loop", .SpriteName = "GhostBullet_Blue_Loop", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "GhostBullet_Pink_Loop", .SpriteName = "GhostBullet_Pink_Loop", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "GhostBullet_Blue_Death", .SpriteName = "GhostBullet_Blue_Death", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "GhostBullet_Pink_Death", .SpriteName = "GhostBullet_Pink_Death", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
	}

	if (nullptr == ProjectileCollisionPtr)
	{
		ProjectileCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
		ProjectileCollisionPtr->SetColType(ColType::SPHERE2D);
		ProjectileCollisionPtr->GetTransform()->SetLocalScale({ 30, 30, -40 });
		ProjectileCollisionPtr->GetTransform()->SetLocalPosition({ 0, 0 });
	}

	if (nullptr == ProjectileCollisionRenderPtr)
	{
		ProjectileCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ProjectileCollisionRenderPtr->SetTexture("GreenBox.png");
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalScale(ProjectileCollisionPtr->GetTransform()->GetLocalScale());
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalPosition(ProjectileCollisionPtr->GetTransform()->GetLocalPosition());
		ProjectileCollisionRenderPtr->Off();
	}

	if (nullptr == ParryCollisionPtr)
	{
		ParryCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::ParrySpot));
		ParryCollisionPtr->SetColType(ColType::SPHERE2D);
		ParryCollisionPtr->GetTransform()->SetLocalScale({ 80, 80, -40 });
		ParryCollisionPtr->GetTransform()->SetLocalPosition({ 0, 0 });
		ParryCollisionPtr->Off();
	}

	if (nullptr == ParryCollisionRenderPtr)
	{
		ParryCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ParryCollisionRenderPtr->SetTexture("GreenLine.png");
		ParryCollisionRenderPtr->GetTransform()->SetLocalScale(ParryCollisionPtr->GetTransform()->GetLocalScale());
		ParryCollisionRenderPtr->GetTransform()->SetLocalPosition(ParryCollisionPtr->GetTransform()->GetLocalPosition());
		ParryCollisionRenderPtr->Off();
	}

	ChangeState(BallState::Intro);
}

void GhostMouse_Projectile::Update(float _DeltaTime)
{
	if (true == MouseLevel::MouseLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	CollisionCheck();
	MoveDirection(_DeltaTime);
	PixelCheck(_DeltaTime);
	UpdateState(_DeltaTime);
	CreateSmallBall();
}

void GhostMouse_Projectile::CollisionCheck()
{
	if (nullptr != ParryCollisionPtr->Collision(static_cast<int>(CollisionOrder::PlayerParry), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		Player::MainPlayer->SetParryOn();
		Death();
	}
}

void GhostMouse_Projectile::MoveDirection(float _DeltaTime)
{
	if (1 == MoveSet)
	{
		MoveSet = 0;

		float4 PlayerPosition = Player::MainPlayer->GetTransform()->GetLocalPosition() + float4{ 0, 40, 0 };
		float4 Direct = PlayerPosition - StartPosition;
		DirectNormal = Direct.NormalizeReturn();
	}

	float MoveDist = 30.0f * _DeltaTime;

	float4 MoveDist4 = float4::Zero;
	float4 Correction = float4::Zero;

	Correction = GetTransform()->GetWorldRightVector().NormalizeReturn();
	GetTransform()->AddLocalPosition(DirectNormal * MoveSpeed * _DeltaTime);
}

void GhostMouse_Projectile::CreateSmallBall()
{
	if (true == IsCreateSmall)
	{
		IsCreateSmall = false;

		std::shared_ptr<SmallBall> Object = GetLevel()->CreateActor<SmallBall>();
		std::shared_ptr<SmallBall> Object2 = GetLevel()->CreateActor<SmallBall>();

		float4 StartPosition = GetTransform()->GetWorldPosition();
		float4 LeftObjectPosition = StartPosition + float4{ 0, -5, 3 };
		float4 RightObjectPosition = StartPosition + float4{ 0, -5, 3 };

		Object->SetStartPosition(LeftObjectPosition);
		Object->SetIsPink(IsPink);

		Object2->SetStartPosition(RightObjectPosition);
		Object2->SetDirectionNegative();
		Object2->SetIsPink(IsPink);
	}
}

void GhostMouse_Projectile::PixelCheck(float _DeltaTime)
{
	if (true == IsDeath)
	{
		return;
	}

	float4 ProjectilePos = GetTransform()->GetWorldPosition();
	float4 LandPos = ProjectilePos + float4{ 0, -15 };

	GameEnginePixelColor LandPixel = PixelCollisionCheck.PixelCheck(LandPos);

	if (true == PixelCollisionCheck.IsBlack(LandPixel))
	{
		DirectNormal = float4::Zero;
		IsDeath = true;
		IsCreateSmall = true;
	}

	float4 RightPos = ProjectilePos + float4{ -15, 0 };
	float4 LeftPos = ProjectilePos + float4{ 15, 0 };

	GameEnginePixelColor RightPixel = PixelCollisionCheck.PixelCheck(RightPos);
	GameEnginePixelColor LeftPixel = PixelCollisionCheck.PixelCheck(LeftPos);

	if (true == PixelCollisionCheck.IsBlack(RightPixel))
	{
		DirectNormal = float4::Zero;
		IsDeath = true;
	}
	else if (true == PixelCollisionCheck.IsBlack(LeftPixel))
	{
		DirectNormal = float4::Zero;
		IsDeath = true;
	}
}

void GhostMouse_Projectile::ChangeState(BallState _StateValue)
{
	BallState NextState = _StateValue;
	BallState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case BallState::Intro:
		IntroStart();
		break;
	case BallState::Loop:
		LoopStart();
		break;
	case BallState::Death:
		DeathStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case BallState::Intro:
		IntroEnd();
		break;
	case BallState::Loop:
		LoopEnd();
		break;
	case BallState::Death:
		DeathEnd();
		break;
	default:
		break;
	}
}
void GhostMouse_Projectile::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case BallState::Intro:
		IntroUpdate(_DeltaTime);
		break;
	case BallState::Loop:
		LoopUpdate(_DeltaTime);
		break;
	case BallState::Death:
		DeathUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void GhostMouse_Projectile::IntroStart()
{
	RenderPtr->ChangeAnimation("GhostBullet_Blue_Intro");
}
void GhostMouse_Projectile::IntroUpdate(float _DeltaTime)
{
	if (true == IsParryProjectile)
	{
		IsParryProjectile = false;
		IsPink = true;
		ParryCollisionPtr->On();
		RenderPtr->ChangeAnimation("GhostBullet_Pink_Intro");
	}

	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(BallState::Loop);
		return;
	}
}
void GhostMouse_Projectile::IntroEnd()
{

}

void GhostMouse_Projectile::LoopStart()
{
	if (true == IsPink)
	{
		RenderPtr->ChangeAnimation("GhostBullet_Pink_Loop");
	}
	else
	{
		RenderPtr->ChangeAnimation("GhostBullet_Blue_Loop");
	}
}
void GhostMouse_Projectile::LoopUpdate(float _DeltaTime)
{
	if (true == IsDeath)
	{
		ChangeState(BallState::Death);
		return;
	}
}
void GhostMouse_Projectile::LoopEnd()
{

}

void GhostMouse_Projectile::DeathStart()
{
	ProjectileCollisionPtr->Off();
	ParryCollisionPtr->Off();
	ParryCollisionRenderPtr->Off();
	ProjectileCollisionRenderPtr->Off();

	if (true == IsPink)
	{
		RenderPtr->ChangeAnimation("GhostBullet_Pink_Death");
	}
	else
	{
		RenderPtr->ChangeAnimation("GhostBullet_Blue_Death");
	}
}
void GhostMouse_Projectile::DeathUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		Death();
	}
}
void GhostMouse_Projectile::DeathEnd()
{

}
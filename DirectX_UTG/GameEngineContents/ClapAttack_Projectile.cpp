#include "PrecompileHeader.h"
#include "ClapAttack_Projectile.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "FrogLevel.h"
#include "ClapAttack_FX.h"

#include "You_Died.h"

ClapAttack_Projectile::ClapAttack_Projectile() 
{
}

ClapAttack_Projectile::~ClapAttack_Projectile() 
{
}

void ClapAttack_Projectile::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "Clap_Ball", .SpriteName = "Clap_Ball", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("Clap_Ball");
	}

	if (nullptr == DebugRenderPtr)
	{
		DebugRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		DebugRenderPtr->SetScaleToTexture("BlueDot.png");
		DebugRenderPtr->GetTransform()->SetLocalPosition({ 10, 0, -3 });
	}

	if (nullptr == ProjectileCollisionPtr)
	{
		ProjectileCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
		ProjectileCollisionPtr->SetColType(ColType::SPHERE2D);
		ProjectileCollisionPtr->GetTransform()->SetLocalScale({ 80, 80, 1 });
		ProjectileCollisionPtr->GetTransform()->SetLocalPosition({ 0, 0 });
	}

	if (nullptr == ProjectileCollisionRenderPtr)
	{
		ProjectileCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ProjectileCollisionRenderPtr->SetTexture("RedBox.png");
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalScale(ProjectileCollisionPtr->GetTransform()->GetLocalScale());
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalPosition(ProjectileCollisionPtr->GetTransform()->GetLocalPosition());
		ProjectileCollisionRenderPtr->Off();
	}
}

void ClapAttack_Projectile::Update(float _DeltaTime)
{
	if (true == FrogLevel::FrogLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	PixelCheck(_DeltaTime);
	MoveDirection(_DeltaTime);
	DeathCheck();
}

void ClapAttack_Projectile::MoveDirection(float _DeltaTime)
{
	if (true == IsDeath)
	{
		return;
	}

	float MoveDist = 30.0f * _DeltaTime;

	float4 MoveDist4 = float4::Zero;
	float4 Correction = float4::Zero;

	Correction = GetTransform()->GetWorldRightVector().NormalizeReturn();
	GetTransform()->AddLocalPosition(Correction * MoveSpeed * _DeltaTime);
}

void ClapAttack_Projectile::CreateClapAttackSFX()
{
	std::shared_ptr<ClapAttack_FX> SFX = GetLevel()->CreateActor<ClapAttack_FX>();
	float4 StartPosition = GetTransform()->GetLocalPosition();
	float4 SFXPosition = StartPosition;

	SFX->SetStartPosition(SFXPosition);
}

void ClapAttack_Projectile::PixelCheck(float _DeltaTime)
{
	if (3 <= BoundCount)
	{
		return;
	}

	// ³«ÇÏ Ã¼Å©
	float4 ProjectilePos = GetTransform()->GetLocalPosition();
	float4 BoundPos = ProjectilePos + float4{ 10, 0 };

	GameEnginePixelColor BoundPixel = PixelCollisionCheck.PixelCheck(BoundPos);

	if (true == PixelCollisionCheck.IsBlack(BoundPixel) && true == Directbool)
	{
		GetTransform()->SetLocalRotation({ 0, 0, 300 });
		Directbool = false;
		++BoundCount;
	}
	else if (true == PixelCollisionCheck.IsBlack(BoundPixel) && false == Directbool)
	{
		GetTransform()->SetLocalRotation({ 0, 0, 60 });
		Directbool = true;
		++BoundCount;
	}

}

void ClapAttack_Projectile::DeathCheck()
{
	float4 CurPos = GetTransform()->GetLocalPosition();

	if ((StartPosition.x + 1200.0f) <= CurPos.x)
	{
		IsDeath = true;
	}

	if (true == IsDeath)
	{
		Death();
	}
}
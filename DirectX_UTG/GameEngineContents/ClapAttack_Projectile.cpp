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

	// PixelCheck(_DeltaTime);
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
	// ³«ÇÏ Ã¼Å©
	float4 ProjectilePos = GetTransform()->GetLocalPosition();
	float4 UpPos = ProjectilePos + float4{ 0, 10 };
	float4 DownPos = ProjectilePos + float4{ 0, -10 };

	GameEnginePixelColor UpPixel = PixelCollisionCheck.PixelCheck(UpPos);
	GameEnginePixelColor DownPixel = PixelCollisionCheck.PixelCheck(DownPos);

	if (true == PixelCollisionCheck.IsBlack(UpPixel))
	{
	}

	if (true == PixelCollisionCheck.IsBlack(DownPixel))
	{
	}
}
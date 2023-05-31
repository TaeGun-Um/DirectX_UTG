#include "PrecompileHeader.h"
#include "Ribby.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"
#include "Peashooter.h"
#include "Peashooter_EX.h"
#include "Spread.h"
#include "Spread_EX.h"

Ribby::Ribby() 
{
}

Ribby::~Ribby() 
{
}

void Ribby::Start()
{
	if (nullptr == GameEngineSprite::Find("Ribby_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Ribby");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_Idle").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_Idle", .SpriteName = "Ribby_Idle", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Ribby_Idle");
	}

	if (nullptr == BodyCollisionPtr)
	{
		BodyCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Monster));
		BodyCollisionPtr->GetTransform()->SetLocalScale({ 150, 250, 1 });
		BodyCollisionPtr->GetTransform()->SetLocalPosition({ 60, -30 });
	}

	if (nullptr == BodyCollisionRenderPtr)
	{
		BodyCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BodyCollisionRenderPtr->GetTransform()->SetLocalScale(BodyCollisionPtr->GetTransform()->GetLocalScale());
		BodyCollisionRenderPtr->GetTransform()->SetLocalPosition(BodyCollisionPtr->GetTransform()->GetLocalPosition());
		BodyCollisionRenderPtr->SetTexture("GreenLine.png");
		BodyCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
	}
}

void Ribby::Update(float _DeltaTime)
{
	if (true == IsDebugRender)
	{
		BodyCollisionRenderPtr->On();
	}
	else
	{
		BodyCollisionRenderPtr->Off();
	}

	CollisionCheck();
	HitBlink(_DeltaTime);
}

void Ribby::CollisionCheck()
{
	if (nullptr != BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Peashooter), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& HP > 0)
	{
		GameEngineActor* Projectile = BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Peashooter), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Peashooter*>(Projectile)->SetPeashooterDeath();
		dynamic_cast<Peashooter*>(Projectile)->SetHitture();
		--HP;

		if (0 == HP)
		{
			IsStageEnd = true;
		}

		IsBlink = true;
	}

	if (nullptr != BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Spread), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& HP > 0)
	{
		GameEngineActor* Projectile = BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Spread), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Spread*>(Projectile)->SetSpreadDeath();
		dynamic_cast<Spread*>(Projectile)->SetHitture();
		--HP;

		if (0 == HP)
		{
			IsStageEnd = true;
		}

		IsBlink = true;
	}
}

void Ribby::HitBlink(float _DeltaTime)
{
	if (false == IsBlink)
	{
		return;
	}

	BlinkTime += _DeltaTime;

	if (BlinkCount == 1)
	{
		BlinkCount = 0;

		OriginMulColor = RenderPtr->ColorOptionValue.MulColor.a;
		BlinkMulColor = 0.8f;
		RenderPtr->ColorOptionValue.MulColor.a = BlinkMulColor;
	}

	if (BlinkTime >= 0.1f)
	{
		BlinkCount = 1;
		BlinkTime = 0.0f;
		IsBlink = false;

		RenderPtr->ColorOptionValue.MulColor.a = OriginMulColor;
	}
}
#include "PrecompileHeader.h"
#include "Tutorial_Target.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Peashooter.h"
#include "Spread.h"

Tutorial_Target::Tutorial_Target() 
{
}

Tutorial_Target::~Tutorial_Target() 
{
}

void Tutorial_Target::Start()
{
	if (nullptr == GameEngineTexture::Find("tutorial_pyramid_topper.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Tutorial_Normal");
		NewDir.Move("Shapes_and_Exit_Door");

		GameEngineTexture::Load(NewDir.GetPlusFileName("tutorial_pyramid_topper.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Target"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Tutorial_Normal");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Target").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Explosion"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Tutorial_Normal");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Explosion").GetFullPath());
	}

	if (nullptr == BoxCollisionPtr)
	{
		BoxCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Wall));
		BoxCollisionPtr->GetTransform()->SetLocalScale({ 190, 400, 1 });
		BoxCollisionPtr->GetTransform()->SetLocalPosition({ -6, -70 });
	}

	if (nullptr == TargetCollisionPtr)
	{
		TargetCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Monster));
		TargetCollisionPtr->GetTransform()->SetLocalScale({ 60, 70, 1 });
		TargetCollisionPtr->GetTransform()->SetLocalPosition({ -3, 110 });
	}

	if (nullptr == BoxRenderPtr)
	{
		BoxRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BoxRenderPtr->SetTexture("tutorial_pyramid_topper.png");
		BoxRenderPtr->GetTransform()->SetLocalScale({ 195, 170, 1 });
		BoxRenderPtr->GetTransform()->SetLocalPosition({ 0, 0 });
		BoxRenderPtr->CameraCullingOn();
	}

	if (nullptr == TargetRenderPtr)
	{
		TargetRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		TargetRenderPtr->CreateAnimation({ .AnimationName = "Target", .SpriteName = "Target", .FrameInter = 0.08f });
		TargetRenderPtr->CreateAnimation({ .AnimationName = "Explosion", .SpriteName = "Explosion", .FrameInter = 0.07f, .Loop = false });
		TargetRenderPtr->GetTransform()->SetLocalScale({ 76, 87, 1 });
		TargetRenderPtr->GetTransform()->SetLocalPosition(TargetCollisionPtr->GetTransform()->GetLocalPosition());
		TargetRenderPtr->CameraCullingOn();

		TargetRenderPtr->ChangeAnimation("Target");
	}

	if (nullptr == TargetCollisionRenderPtr)
	{
		TargetCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		TargetCollisionRenderPtr->SetTexture("GreenLine.png");
		TargetCollisionRenderPtr->GetTransform()->SetLocalScale(TargetCollisionPtr->GetTransform()->GetLocalScale());
		TargetCollisionRenderPtr->GetTransform()->SetLocalPosition(TargetCollisionPtr->GetTransform()->GetLocalPosition());
	}

	if (nullptr == BoxCollisionRenderPtr)
	{
		BoxCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BoxCollisionRenderPtr->SetTexture("GreenLine.png");
		BoxCollisionRenderPtr->GetTransform()->SetLocalScale(BoxCollisionPtr->GetTransform()->GetLocalScale());
		BoxCollisionRenderPtr->GetTransform()->SetLocalPosition(BoxCollisionPtr->GetTransform()->GetLocalPosition());
	}
}

void Tutorial_Target::Update(float _DeltaTime)
{
	if (true == IsDebugRender)
	{
		BoxCollisionRenderPtr->On();
		TargetCollisionRenderPtr->On();
	}
	else
	{
		BoxCollisionRenderPtr->Off();
		TargetCollisionRenderPtr->Off();
	}

	SetDeath();
	CollisionCheck();
}

void Tutorial_Target::CollisionCheck()
{
	if (nullptr != TargetCollisionPtr->Collision(static_cast<int>(CollisionOrder::Peashooter), ColType::SPHERE2D, ColType::SPHERE2D)
		&& 1 <= HP)
	{
		GameEngineActor* Projectile = TargetCollisionPtr->Collision(static_cast<int>(CollisionOrder::Peashooter), ColType::SPHERE2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Peashooter*>(Projectile)->SetPeashooterDeath();
		dynamic_cast<Peashooter*>(Projectile)->SetHitture();
		--HP;

		if (0 >= HP)
		{
			IsDeath = true;
		}
	}

	if (nullptr != TargetCollisionPtr->Collision(static_cast<int>(CollisionOrder::Spread), ColType::SPHERE2D, ColType::SPHERE2D)
		&& 1 <= HP)
	{
		GameEngineActor* Projectile = TargetCollisionPtr->Collision(static_cast<int>(CollisionOrder::Spread), ColType::SPHERE2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Spread*>(Projectile)->SetSpreadDeath();
		dynamic_cast<Spread*>(Projectile)->SetHitture();
		--HP;

		if (0 >= HP)
		{
			IsDeath = true;
		}
	}
}

void Tutorial_Target::SetDeath()
{
	if (false == IsDeath)
	{
		return;
	}

	BoxCollisionRenderPtr->Death();
	BoxCollisionPtr->Death();
	BoxRenderPtr->Death();
	TargetCollisionRenderPtr->Death();
	TargetCollisionPtr->Death();

	TargetRenderPtr->GetTransform()->SetLocalScale({ 350, 350, 1 });
	TargetRenderPtr->GetTransform()->SetLocalPosition({ -3, 50 });

	TargetRenderPtr->ChangeAnimation("Explosion", false);

	if (true == TargetRenderPtr->FindAnimation("Explosion")->IsEnd())
	{
		Death();
	}
}

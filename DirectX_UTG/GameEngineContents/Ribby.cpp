#include "PrecompileHeader.h"
#include "Ribby.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Croak.h"
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
	ActorInitSetting();
}

void Ribby::Update(float _DeltaTime)
{
	MoveAbleTime += _DeltaTime;

	if (MoveAbleTime <= 1.8f)
	{
		return;
	}

	if (true == IsDebugRender)
	{
		BodyCollisionRenderPtr->On();
		EXCollisionRenderPtr->On();
	}
	else
	{
		BodyCollisionRenderPtr->Off();
		EXCollisionRenderPtr->Off();
	}

	DirectCheck();
	UpdateState(_DeltaTime);
	CollisionCheck();
	HitBlink(_DeltaTime);
}

void Ribby::DirectCheck()
{
	if (false == Directbool)
	{
		GetTransform()->SetLocalPositiveScaleX();
	}
	else
	{
		GetTransform()->SetLocalNegativeScaleX();
	}
}

void Ribby::CollisionCheck()
{
	/////////////// Normal
	if (nullptr != BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Peashooter), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& Croak::CroakPtr->HP > 0.0f)
	{
		GameEngineActor* Projectile = BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Peashooter), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Peashooter*>(Projectile)->SetPeashooterDeath();
		dynamic_cast<Peashooter*>(Projectile)->SetHitture();
		Croak::CroakPtr->HP -= 1.0f;

		if (0 >= Croak::CroakPtr->HP)
		{
			Croak::CroakPtr->HP = 0.0f;
			IsStageEnd = true;
		}

		IsBlink = true;
	}

	if (nullptr != BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Spread), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& Croak::CroakPtr->HP > 0.0f)
	{
		GameEngineActor* Projectile = BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Spread), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Spread*>(Projectile)->SetSpreadDeath();
		dynamic_cast<Spread*>(Projectile)->SetHitture();
		Croak::CroakPtr->HP -= 0.4f;

		if (0 >= Croak::CroakPtr->HP)
		{
			Croak::CroakPtr->HP = 0.0f;
			IsStageEnd = true;
		}

		IsBlink = true;
	}

	/////////////// EX
	if (nullptr != EXCollisionPtr->Collision(static_cast<int>(CollisionOrder::PeashooterEX), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& Croak::CroakPtr->HP > 0.0f)
	{
		GameEngineActor* Projectile = EXCollisionPtr->Collision(static_cast<int>(CollisionOrder::PeashooterEX), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Peashooter_EX*>(Projectile)->SetHitture();
		Croak::CroakPtr->HP -= 5.0f;

		if (0 >= Croak::CroakPtr->HP)
		{
			Croak::CroakPtr->HP = 0.0f;
			IsStageEnd = true;
		}

		IsBlink = true;
	}

	if (nullptr != EXCollisionPtr->Collision(static_cast<int>(CollisionOrder::SpreadEX), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& Croak::CroakPtr->HP > 0.0f)
	{
		GameEngineActor* Projectile = EXCollisionPtr->Collision(static_cast<int>(CollisionOrder::SpreadEX), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Spread_EX*>(Projectile)->SetSpread_EXDeath();
		Croak::CroakPtr->HP -= 10.0f;

		if (0 >= Croak::CroakPtr->HP)
		{
			Croak::CroakPtr->HP = 0.0f;
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

void Ribby::ActorInitSetting()
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

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_Intro_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_Intro_End").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_Idle").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_Intro", .SpriteName = "Ribby_Intro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_Intro_Loop", .SpriteName = "Ribby_Intro_Loop", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_Intro_End", .SpriteName = "Ribby_Intro_End", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_Idle", .SpriteName = "Ribby_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("Ribby_Idle");
	}

	if (nullptr == BodyCollisionPtr)
	{
		BodyCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Monster));
		BodyCollisionPtr->SetColType(ColType::AABBBOX2D);
		BodyCollisionPtr->GetTransform()->SetLocalScale({ 150, 270, 1 });
		BodyCollisionPtr->GetTransform()->SetLocalPosition({ 60, -40 });
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
		EXCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Monster));
		EXCollisionPtr->SetColType(ColType::AABBBOX2D);
		EXCollisionPtr->GetTransform()->SetLocalScale({ 150, 270, 1 });
		EXCollisionPtr->GetTransform()->SetLocalPosition({ 60, -40 });
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
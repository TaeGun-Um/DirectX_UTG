#include "PrecompileHeader.h"
#include "Ribby.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Croak.h"
#include "Player.h"
#include "Peashooter.h"
#include "Peashooter_EX.h"
#include "Spread.h"
#include "Spread_EX.h"

#include "Croak.h"
#include "FistAttack_Projectile.h"
#include "FistAttack_SFX.h"
#include "ClapAttack_Projectile.h"

Ribby* Ribby::RibbyPtr = nullptr;

Ribby::Ribby() 
{
}

Ribby::~Ribby() 
{
}

void Ribby::Start()
{
	RibbyPtr = this;
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

	DirectCheck();
	UpdateState(_DeltaTime);
	CollisionCheck();
	CollisionSetting();
	HitBlink(_DeltaTime);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     AssistFunction                     ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                    CollisionCheck                    /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Ribby::SetInitReset()
{
	On();
	MoveAbleTime = 0.0f;
	StateValue = RibbyState::Idle;
	ChangeState(RibbyState::Idle);
	GetTransform()->SetLocalPositiveScaleX();

	RollStartPosition = float4::Zero;
	RollEndPosition = float4::Zero;
	MoveDistance = float4::Zero;
	DirectNormal = float4::Zero;

	RollMoveTime = 0.0f;
	IntroLoopTime = 0.0f;
	IdleDelayTime = 0.0f;
	ClapDelayTime = 0.0f;
	FistLoopDelayTime = 0.0f;
	FistAttackDelayTime = 0.0f;
	LoopInterDelayTime = 0.0f;
	RollDelayTime = 0.0f;
	ClapLoopTime = 0.0f;

	Directbool = false;
	IsIntro = true;
	IsRoll = false;
	IsClap = false;
	IsFistAttak = false;
	ParryFistCreate = false;

	FistCreateCount = 0;
	ParryFistCount = 1;
	ClapCount = 4;
	CreateBallCount = 1;

	BodyCollisionRenderPtr->Off();
	EXCollisionRenderPtr->Off();
}

void Ribby::CollisionSetting()
{
	BodyCollisionRenderPtr->GetTransform()->SetLocalScale(BodyCollisionPtr->GetTransform()->GetLocalScale());
	BodyCollisionRenderPtr->GetTransform()->SetLocalPosition(BodyCollisionPtr->GetTransform()->GetLocalPosition());

	EXCollisionRenderPtr->GetTransform()->SetLocalScale(EXCollisionPtr->GetTransform()->GetLocalScale());
	EXCollisionRenderPtr->GetTransform()->SetLocalPosition(EXCollisionPtr->GetTransform()->GetLocalPosition());
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     CreateActor                      ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Ribby::CreateFistProjectile()
{
	std::shared_ptr<FistAttack_Projectile> Projectile = GetLevel()->CreateActor<FistAttack_Projectile>();
	float4 StartPosition = GetTransform()->GetLocalPosition();
	float4 ProjectilePosition = StartPosition;

	if (0 == FistCreateCount || 4 == FistCreateCount || 8 == FistCreateCount)
	{
		ProjectilePosition += float4{ -140, -120, -1 };
	}
	else if (1 == FistCreateCount || 3 == FistCreateCount || 5 == FistCreateCount || 7 == FistCreateCount)
	{
		ProjectilePosition += float4{ -140, -30, -1 };
	}
	else if (2 == FistCreateCount || 6 == FistCreateCount)
	{
		ProjectilePosition += float4{ -140, 60, -1 };
	}

	int RandC = GameEngineRandom::MainRandom.RandomInt(0, (8 - FistCreateCount));
	
	if (0 == RandC && false == ParryFistCreate)
	{
		ParryFistCreate = true;
	}

	if (true == ParryFistCreate && 1 == ParryFistCount)
	{
		ParryFistCount = 0;
		Projectile->SetParryFistCreate();
	}

	Projectile->SetStartPosition(ProjectilePosition);
	Projectile->SetDirection(Directbool);

	if (true == IsDebugRender)
	{
		Projectile->SetCollisionRenderOn();
	}
	else
	{
		Projectile->SetCollisionRenderOff();
	}

	CreateFistSFX(ProjectilePosition);
}

void Ribby::CreateFistSFX(float4 _Position)
{
	std::shared_ptr<FistAttack_SFX> FistSFX = GetLevel()->CreateActor<FistAttack_SFX>();
	
	FistSFX->SetStartPosition(_Position);
	FistSFX->SetDirection(Directbool);
}

void Ribby::CreateBallProjectile()
{
	std::shared_ptr<ClapAttack_Projectile> Projectile = GetLevel()->CreateActor<ClapAttack_Projectile>();
	float4 StartPosition = GetTransform()->GetLocalPosition();

	float4 ProjectilePosition = StartPosition + float4{115, -5, 1};
	float4 ProjectileRotation = float4::Zero;

	int RandC = GameEngineRandom::MainRandom.RandomInt(0, 1);
	bool UpDirect = true;

	if (0 == RandC)
	{
		ProjectileRotation = float4{ 0, 0, 63 };
		UpDirect = true;
	}
	else
	{
		ProjectileRotation = float4{ 0, 0, 298 };
		UpDirect = false;
	}

	if (true == IsDebugRender)
	{
		Projectile->SetCollisionRenderOn();
	}
	else
	{
		Projectile->SetCollisionRenderOff();
	}

	Projectile->SetColMap(Player::MainPlayer->GetColMap(), PixelCollision::Coordinate::Custom);
	Projectile->SetStartPosition(ProjectilePosition);
	Projectile->SetProjectileRotation(ProjectileRotation, UpDirect);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                         FSM                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     InitSetting                     ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_FistAttack_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_FistAttack_Intro_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_FistAttack_Intro_out").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_FistAttack_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_FistAttack_End").GetFullPath());
		
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_Roll_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_Roll_Intro_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_Roll_Intro_Out").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_Roll_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_Roll_End").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_ClapAttack_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_ClapAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_ClapAttack_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_ClapAttack_LoopBack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ribby_ClapAttack_End").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Normal_Loop"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Ribby");
		NewDir.Move("Fist_Projectile");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Normal_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Normal_Spawn").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Pink_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Pink_Spawn").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Spark").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Death_FX").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Clap_Ball"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Ribby");
		NewDir.Move("Clap_Projectile");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Clap_Ball").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Clap_FX").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_Intro", .SpriteName = "Ribby_Intro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_Intro_Loop", .SpriteName = "Ribby_Intro_Loop", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_Intro_End", .SpriteName = "Ribby_Intro_End", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_Idle", .SpriteName = "Ribby_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });

		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_FistAttack_Intro", .SpriteName = "Ribby_FistAttack_Intro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_FistAttack_Intro_Loop", .SpriteName = "Ribby_FistAttack_Intro_Loop", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_FistAttack_Intro_out", .SpriteName = "Ribby_FistAttack_Intro_out", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_FistAttack_Loop", .SpriteName = "Ribby_FistAttack_Loop", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_FistAttack_End", .SpriteName = "Ribby_FistAttack_End", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_Roll_Intro", .SpriteName = "Ribby_Roll_Intro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_Roll_Intro_Loop", .SpriteName = "Ribby_Roll_Intro_Loop", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_Roll_Intro_Out", .SpriteName = "Ribby_Roll_Intro_Out", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_Roll_Loop", .SpriteName = "Ribby_Roll_Loop", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_Roll_End", .SpriteName = "Ribby_Roll_End", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });

		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_ClapAttack_Intro", .SpriteName = "Ribby_ClapAttack_Intro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_ClapAttack", .SpriteName = "Ribby_ClapAttack", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_ClapAttack_Loop", .SpriteName = "Ribby_ClapAttack_Loop", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_ClapAttack_LoopBack", .SpriteName = "Ribby_ClapAttack_LoopBack", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Ribby_ClapAttack_End", .SpriteName = "Ribby_ClapAttack_End", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

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
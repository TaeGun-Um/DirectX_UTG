#include "PrecompileHeader.h"
#include "Katzenwagen.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"
#include "Peashooter.h"
#include "Peashooter_EX.h"
#include "Spread.h"
#include "Spread_EX.h"

#include "Werner_Werman.h"
#include "Mouse_Map.h"

Katzenwagen* Katzenwagen::KatzenwagenPtr = nullptr;

Katzenwagen::Katzenwagen() 
{
}

Katzenwagen::~Katzenwagen() 
{
}

void Katzenwagen::Start()
{
	KatzenwagenPtr = this;

	ActorInitSetting();
}

void Katzenwagen::Update(float _DeltaTime)
{
	if (false == IsIntro)
	{
		return;
	}
	
	if (true == IsIntro && 1 == InitSetting)
	{
		InitSetting = 0;
		ChangeState(KatzenwagenState::Intro);
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

void Katzenwagen::HitBlink(float _DeltaTime)
{
	if (false == IsBlink)
	{
		return;
	}

	BlinkTime += _DeltaTime;

	if (BlinkCount == 1)
	{
		BlinkCount = 0;

		OriginMulColor = HeadRenderPtr->ColorOptionValue.MulColor;
		BlinkMulColor.r = 0.2f;
		BlinkMulColor.g = 0.2f;
		BlinkMulColor.b = 0.35f;
		HeadRenderPtr->ColorOptionValue.MulColor += BlinkMulColor;
	}

	if (BlinkTime >= 0.1f)
	{
		BlinkCount = 1;
		BlinkTime = 0.0f;
		IsBlink = false;

		HeadRenderPtr->ColorOptionValue.MulColor = OriginMulColor;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                    CollisionCheck                    /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Katzenwagen::CollisionSetting()
{
	if (true == BodyCollisionPtr->IsUpdate())
	{
		BodyCollisionRenderPtr->GetTransform()->SetLocalScale(BodyCollisionPtr->GetTransform()->GetLocalScale());
		EXCollisionRenderPtr->GetTransform()->SetLocalScale(EXCollisionPtr->GetTransform()->GetLocalScale());
	}
}

void Katzenwagen::CollisionCheck()
{
	/////////////// Normal
	if (nullptr != BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Peashooter), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& Werner_Werman::WernerWermanPtr->HP > 0.0f)
	{
		GameEngineActor* Projectile = BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Peashooter), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Peashooter*>(Projectile)->SetPeashooterDeath();
		dynamic_cast<Peashooter*>(Projectile)->SetHitture();
		Werner_Werman::WernerWermanPtr->HP -= 1.0f;

		if (0 >= Werner_Werman::WernerWermanPtr->HP)
		{
			Werner_Werman::WernerWermanPtr->HP = 0.0f;
			Werner_Werman::WernerWermanPtr->IsStageEnd = true;
		}

		IsBlink = true;
	}

	if (nullptr != BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Spread), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& Werner_Werman::WernerWermanPtr->HP > 0.0f)
	{
		GameEngineActor* Projectile = BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Spread), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Spread*>(Projectile)->SetSpreadDeath();
		dynamic_cast<Spread*>(Projectile)->SetHitture();
		Werner_Werman::WernerWermanPtr->HP -= 0.4f;

		if (0 >= Werner_Werman::WernerWermanPtr->HP)
		{
			Werner_Werman::WernerWermanPtr->HP = 0.0f;
			Werner_Werman::WernerWermanPtr->IsStageEnd = true;
		}

		IsBlink = true;
	}

	/////////////// EX
	if (nullptr != EXCollisionPtr->Collision(static_cast<int>(CollisionOrder::PeashooterEX), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& Werner_Werman::WernerWermanPtr->HP > 0.0f)
	{
		GameEngineActor* Projectile = EXCollisionPtr->Collision(static_cast<int>(CollisionOrder::PeashooterEX), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Peashooter_EX*>(Projectile)->SetHitture();
		Werner_Werman::WernerWermanPtr->HP -= 5.0f;

		if (0 >= Werner_Werman::WernerWermanPtr->HP)
		{
			Werner_Werman::WernerWermanPtr->HP = 0.0f;
			Werner_Werman::WernerWermanPtr->IsStageEnd = true;
		}

		IsBlink = true;
	}

	if (nullptr != EXCollisionPtr->Collision(static_cast<int>(CollisionOrder::SpreadEX), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& Werner_Werman::WernerWermanPtr->HP > 0.0f)
	{
		GameEngineActor* Projectile = EXCollisionPtr->Collision(static_cast<int>(CollisionOrder::SpreadEX), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Spread_EX*>(Projectile)->SetSpread_EXDeath();
		Werner_Werman::WernerWermanPtr->HP -= 10.0f;

		if (0 >= Werner_Werman::WernerWermanPtr->HP)
		{
			Werner_Werman::WernerWermanPtr->HP = 0.0f;
			Werner_Werman::WernerWermanPtr->IsStageEnd = true;
		}

		IsBlink = true;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                         FSM                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Katzenwagen::DirectCheck()
{
	//if (false == Directbool)
	//{
	//	HeadRenderPtr->GetTransform()->SetLocalPositiveScaleX();
	//}
	//else
	//{
	//	HeadRenderPtr->GetTransform()->SetLocalNegativeScaleX();
	//}
}

void Katzenwagen::IntroAnimationSetting()
{
	RightHandRenderPtr->On();
	LeftHandRenderPtr->On();
	HeadRenderPtr->On();

	HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -105, -10 });

	RightHandRenderPtr->ChangeAnimation("Cat_Idle_RightHand");
	LeftHandRenderPtr->ChangeAnimation("Cat_Idle_LeftHand");
	HeadRenderPtr->ChangeAnimation("Cat_Intro_Head");
	BodyRenderPtr->ChangeAnimation("Cat_Idle_Body");

	HeadRenderPtr->SetAnimationStartEvent("Cat_Intro_Head", 5, std::bind(&Katzenwagen::IntroMouseOff, this));
	HeadRenderPtr->SetAnimationStartEvent("Cat_Intro_Head", 37, std::bind(&Katzenwagen::IntroWallBrake, this));
}

void Katzenwagen::IntroMouseOff()
{
	HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -105, -15 });

	Werner_Werman::WernerWermanPtr->CanRenderPtr->Off();
	Werner_Werman::WernerWermanPtr->CanBackRenderPtr->Off();
	Werner_Werman::WernerWermanPtr->CanUpRenderPtr->Off();
	Werner_Werman::WernerWermanPtr->MouseRenderPtr->Off();
	Werner_Werman::WernerWermanPtr->WeaponRender->Off();
	Werner_Werman::WernerWermanPtr->MouseUpRenderPtr->Off();
	Werner_Werman::WernerWermanPtr->WheelRenderPtr->Off();
	Werner_Werman::WernerWermanPtr->FlamecannonRenderPtr_Right->Off();
	Werner_Werman::WernerWermanPtr->FlamecannonRenderPtr_Left->Off();
	//Werner_Werman::WernerWermanPtr->Phase2Parent->Off();

	Werner_Werman::WernerWermanPtr->BodyCollisionPtr->Off();
	Werner_Werman::WernerWermanPtr->EXCollisionPtr->Off();
	Werner_Werman::WernerWermanPtr->PlatformCollisionPtr->Off();
}

void Katzenwagen::IntroWallBrake()
{
	Mouse_Map::MouseMapPtr->IsPhase3 = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     InitSetting                     ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Katzenwagen::ActorInitSetting()
{
	if (nullptr == GameEngineSprite::Find("Cat_Intro_Body"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase3");

		// Body
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Intro_Body").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Idle_Body").GetFullPath());

		// Head
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Intro_Head").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Idle_Head").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Claw_Head_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Claw_Head_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Claw_Head_Outro").GetFullPath());

		// Arm
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Idle_LeftHand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Idle_RightHand").GetFullPath());
		
		// AttackArm
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Claw_Hand_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Claw_Hand_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Claw_Hand_Outro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cat_Claw_Hand_Hit").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("UpTexture.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase3");

		GameEngineTexture::Load(NewDir.GetPlusFileName("UpTexture.png").GetFullPath());
	}

	if (nullptr == TailHandRenderPtr)
	{
		//TailHandRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		//TailHandRenderPtr->CreateAnimation({ .AnimationName = "Object_Flamecannon", .SpriteName = "Object_Flamecannon", .FrameInter = 0.065f, .Loop = true, .ScaleToTexture = true });
		//TailHandRenderPtr->ChangeAnimation("Object_Flamecannon");
	}

	if (nullptr == BodyRenderPtr)
	{
		BodyRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BodyRenderPtr->CreateAnimation({ .AnimationName = "Cat_Intro_Body", .SpriteName = "Cat_Intro_Body", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
		BodyRenderPtr->CreateAnimation({ .AnimationName = "Cat_Idle_Body", .SpriteName = "Cat_Idle_Body", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		BodyRenderPtr->GetTransform()->SetLocalPosition({ 0, 0, 5 });
		BodyRenderPtr->ChangeAnimation("Cat_Intro_Body");
		BodyRenderPtr->Off();
	}

	if (nullptr == RightHandRenderPtr)
	{
		RightHandRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RightHandRenderPtr->CreateAnimation({ .AnimationName = "Cat_Idle_RightHand", .SpriteName = "Cat_Idle_RightHand", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		RightHandRenderPtr->GetTransform()->SetLocalPosition({ 120, -100, 5 });
		RightHandRenderPtr->ChangeAnimation("Cat_Idle_RightHand");
		RightHandRenderPtr->Off();
	}

	if (nullptr == LeftHandRenderPtr)
	{
		LeftHandRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		LeftHandRenderPtr->CreateAnimation({ .AnimationName = "Cat_Idle_LeftHand", .SpriteName = "Cat_Idle_LeftHand", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		LeftHandRenderPtr->GetTransform()->SetLocalPosition({ -120, -100, 5 });
		LeftHandRenderPtr->ChangeAnimation("Cat_Idle_LeftHand");
		LeftHandRenderPtr->Off();
	}

	if (nullptr == BodyUpRenderPtr)
	{
		BodyUpRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BodyUpRenderPtr->SetTexture("UpTexture.png");
		BodyUpRenderPtr->GetTransform()->SetLocalScale({ 350, 30, 1 });
		BodyUpRenderPtr->GetTransform()->SetLocalPosition({ 10, 100, 5 });
		BodyUpRenderPtr->Off();
	}

	if (nullptr == HeadRenderPtr)
	{
		HeadRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		HeadRenderPtr->CreateAnimation({ .AnimationName = "Cat_Intro_Head", .SpriteName = "Cat_Intro_Head", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		HeadRenderPtr->CreateAnimation({ .AnimationName = "Cat_Idle_Head_Left", .SpriteName = "Cat_Idle_Head", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		HeadRenderPtr->CreateAnimation({ .AnimationName = "Cat_Idle_Head_Right", .SpriteName = "Cat_Idle_Head", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		HeadRenderPtr->CreateAnimation({ .AnimationName = "Cat_Claw_Head_Intro", .SpriteName = "Cat_Claw_Head_Intro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		HeadRenderPtr->CreateAnimation({ .AnimationName = "Cat_Claw_Head_Loop", .SpriteName = "Cat_Claw_Head_Loop", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		HeadRenderPtr->CreateAnimation({ .AnimationName = "Cat_Claw_Head_Outro", .SpriteName = "Cat_Claw_Head_Outro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, 0 });
		HeadRenderPtr->ChangeAnimation("Cat_Intro_Head");
		HeadRenderPtr->Off();
	}

	if (nullptr == BodyCollisionPtr)
	{
		BodyCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterHitBox));
		BodyCollisionPtr->SetColType(ColType::AABBBOX2D);
		BodyCollisionPtr->GetTransform()->SetLocalScale({ 350, 200, 1 });
		BodyCollisionPtr->GetTransform()->SetLocalPosition({ 0, 10, -50 });
		BodyCollisionPtr->Off();
	}

	if (nullptr == AttackHandRenderPtr)
	{
		AttackHandRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		AttackHandRenderPtr->CreateAnimation({ .AnimationName = "Cat_Claw_Hand_Intro", .SpriteName = "Cat_Claw_Hand_Intro", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = false });
		AttackHandRenderPtr->CreateAnimation({ .AnimationName = "Cat_Claw_Hand_Loop", .SpriteName = "Cat_Claw_Hand_Loop", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = false });
		AttackHandRenderPtr->CreateAnimation({ .AnimationName = "Cat_Claw_Hand_Hit", .SpriteName = "Cat_Claw_Hand_Hit", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = false });
		AttackHandRenderPtr->CreateAnimation({ .AnimationName = "Cat_Claw_Hand_Outro", .SpriteName = "Cat_Claw_Hand_Outro", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = false });
		AttackHandRenderPtr->GetTransform()->SetLocalScale({ 1000, 710, 1 });
		AttackHandRenderPtr->ChangeAnimation("Cat_Claw_Hand_Intro");
		AttackHandRenderPtr->Off();
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
		EXCollisionPtr->GetTransform()->SetLocalScale({ 350, 200, 1 });
		EXCollisionPtr->GetTransform()->SetLocalPosition({ 0, 10, -50 });
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

	if (nullptr == AttackCollisionPtr)
	{
		AttackCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Monster));
		AttackCollisionPtr->SetColType(ColType::AABBBOX2D);
		AttackCollisionPtr->GetTransform()->SetLocalScale({ 180, 310, 1 });
		AttackCollisionPtr->GetTransform()->SetLocalPosition({ 0, 0, -50 });
		AttackCollisionPtr->Off();
	}

	if (nullptr == AttackCollisionRenderPtr)
	{
		AttackCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		AttackCollisionRenderPtr->GetTransform()->SetLocalScale(AttackCollisionPtr->GetTransform()->GetLocalScale());
		AttackCollisionRenderPtr->GetTransform()->SetLocalPosition(AttackCollisionPtr->GetTransform()->GetLocalPosition());
		AttackCollisionRenderPtr->SetTexture("RedLine.png");
		AttackCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
		AttackCollisionRenderPtr->Off();
	}
}
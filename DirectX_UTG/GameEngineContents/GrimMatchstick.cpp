#include "PrecompileHeader.h"
#include "GrimMatchstick.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "Peashooter.h"
#include "Peashooter_EX.h"
#include "Spread.h"
#include "Spread_EX.h"

#include "Object_GreenRing.h"
#include "Object_Meteor.h"
#include "Object_Tail.h"

GrimMatchstick* GrimMatchstick::GrimMatchstickPtr = nullptr;

GrimMatchstick::GrimMatchstick() 
{
}

GrimMatchstick::~GrimMatchstick() 
{
}

void GrimMatchstick::Start()
{
	GrimMatchstickPtr = this;

	ActorInitSetting();
}

void GrimMatchstick::Update(float _DeltaTime)
{
	//if (true == IsDebugRender)
	//{
	//	if (true == BodyCollisionPtr->IsUpdate())
	//	{
	//		BodyCollisionRenderPtr->On();
	//		EXCollisionRenderPtr->On();
	//	}
	//	else
	//	{
	//		BodyCollisionRenderPtr->Off();
	//		EXCollisionRenderPtr->Off();
	//	}
	//}
	//else
	//{
	//	BodyCollisionRenderPtr->Off();
	//	EXCollisionRenderPtr->Off();
	//}

	if (false == IsSpawn)
	{
		SpawnDelayTime += _DeltaTime;

		if (SpawnDelayTime < 0.9f)
		{
			return;
		}
		else
		{
			IsSpawn = true;
			RenderPtr->On();
		}
	}

	DirectCheck();
	UpdateState(_DeltaTime);
	CollisionCheck();
	CollisionSetting();
	HitBlink(_DeltaTime);

	CreateRing(_DeltaTime);
	CreateTail(_DeltaTime);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     AssistFunction                     ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GrimMatchstick::HitBlink(float _DeltaTime)
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
		UpRenderPtr->ColorOptionValue.MulColor += BlinkMulColor;
	}

	if (BlinkTime >= 0.1f)
	{
		BlinkCount = 1;
		BlinkTime = 0.0f;
		IsBlink = false;

		RenderPtr->ColorOptionValue.MulColor = OriginMulColor;
		UpRenderPtr->ColorOptionValue.MulColor = OriginMulColor;
	}
}

void GrimMatchstick::GetRingAngleWithDotProduct3D()
{
	float4 StartPosition = GetTransform()->GetWorldPosition();
	RingProjectilePostion = StartPosition + float4{ -55, 300, -5 };

	float4 ForwardVector = float4{ -1, 0, 0 };
	float4 ForwardDirectNormal = ForwardVector.NormalizeReturn();

	float4 PlayerPosition = Player::MainPlayer->GetTransform()->GetLocalPosition() + float4{ 0, 40, 0 };
	float4 Direct = PlayerPosition - RingProjectilePostion;
	float4 RotationDirectNormal = Direct.NormalizeReturn();

	if (0.0f <= RotationDirectNormal.y)
	{
		RingReverse = true;
	}
	else
	{
		RingReverse = false;
	}

	RingRotationZ = float4::GetAngleVectorToVectorDeg(ForwardDirectNormal, RotationDirectNormal);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                    CollisionCheck                    /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GrimMatchstick::CollisionCheck()
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
			IsStageEnd = true;
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
			IsStageEnd = true;
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
			IsStageEnd = true;
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
			IsStageEnd = true;
		}

		IsBlink = true;
	}

	/////////////// Normal
	if (nullptr != Plus_BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Peashooter), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& HP > 0.0f)
	{
		GameEngineActor* Projectile = Plus_BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Peashooter), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Peashooter*>(Projectile)->SetPeashooterDeath();
		dynamic_cast<Peashooter*>(Projectile)->SetHitture();
		HP -= 1.0f;

		if (0 >= HP)
		{
			HP = 0.0f;
			IsStageEnd = true;
		}

		IsBlink = true;
	}

	if (nullptr != Plus_BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Spread), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& HP > 0.0f)
	{
		GameEngineActor* Projectile = Plus_BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Spread), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Spread*>(Projectile)->SetSpreadDeath();
		dynamic_cast<Spread*>(Projectile)->SetHitture();
		HP -= 0.4f;

		if (0 >= HP)
		{
			HP = 0.0f;
			IsStageEnd = true;
		}

		IsBlink = true;
	}

	/////////////// EX
	if (nullptr != Plus_EXCollisionPtr->Collision(static_cast<int>(CollisionOrder::PeashooterEX), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& HP > 0.0f)
	{
		GameEngineActor* Projectile = Plus_EXCollisionPtr->Collision(static_cast<int>(CollisionOrder::PeashooterEX), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Peashooter_EX*>(Projectile)->SetHitture();
		HP -= 5.0f;

		if (0 >= HP)
		{
			HP = 0.0f;
			IsStageEnd = true;
		}

		IsBlink = true;
	}

	if (nullptr != Plus_EXCollisionPtr->Collision(static_cast<int>(CollisionOrder::SpreadEX), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& HP > 0.0f)
	{
		GameEngineActor* Projectile = Plus_EXCollisionPtr->Collision(static_cast<int>(CollisionOrder::SpreadEX), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Spread_EX*>(Projectile)->SetSpread_EXDeath();
		HP -= 10.0f;

		if (0 >= HP)
		{
			HP = 0.0f;
			IsStageEnd = true;
		}

		IsBlink = true;
	}
}

void GrimMatchstick::CollisionSetting()
{
	BodyCollisionRenderPtr->GetTransform()->SetLocalScale(BodyCollisionPtr->GetTransform()->GetLocalScale());
	EXCollisionRenderPtr->GetTransform()->SetLocalScale(EXCollisionPtr->GetTransform()->GetLocalScale());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     CreateActor                      ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GrimMatchstick::CreateTail(float _DeltaTime)
{
	if (true == IsTailSpawn)
	{
		return;
	}

	TailSpawnTime += _DeltaTime;

	if (20.0f >= TailSpawnTime)
	{
		return;
	}

	std::shared_ptr<Object_Tail> TailObject = GetLevel()->CreateActor<Object_Tail>();

	float4 PlayerPosition = Player::MainPlayer->GetTransform()->GetLocalPosition();
	float4 ProjectilePosition = float4{ PlayerPosition.x, -450, -5 };

	if (true == IsDebugRender)
	{
		TailObject->SetCollisionRenderOn();
	}
	else
	{
		TailObject->SetCollisionRenderOff();
	}

	TailObject->SetStartPosition(ProjectilePosition);

	TailSpawnTime = 0.0f;
}

void GrimMatchstick::CreateRing(float _DeltaTime)
{
	if (false == RingCreate)
	{
		return;
	}

	if (RingMaxCreateCount == RingCreateCount)
	{
		RingSpawnDelayTime = 0.0f;
		RingCreate = false;
		RingCreateCount = 0;
		return;
	}

	RingSpawnDelayTime += _DeltaTime;

	if (0.25f >= RingSpawnDelayTime)
	{
		return;
	}

	++RingCreateCount;

	std::shared_ptr<Object_GreenRing> RingObject = GetLevel()->CreateActor<Object_GreenRing>();

	RingObject->SetStartPosition(RingProjectilePostion);

	if (true == IsDebugRender)
	{
		RingObject->SetCollisionRenderOn();
	}
	else
	{
		RingObject->SetCollisionRenderOff();
	}

	if (false == RingReverse)
	{
		RingObject->SetProjectileRotation({ 0, 0, RingRotationZ });
	}
	else
	{
		RingObject->SetProjectileRotation({ 0, 0, -RingRotationZ });
	}

	if (3 == RingCreateCount)
	{
		RingObject->SetParryRingCreate();
	}

	RingSpawnDelayTime = 0.0f;
}

void GrimMatchstick::CreateMeteor()
{
	std::shared_ptr<Object_Meteor> Meteor0 = GetLevel()->CreateActor<Object_Meteor>();
	std::shared_ptr<Object_Meteor> Meteor1 = GetLevel()->CreateActor<Object_Meteor>();

	float4 StartPosition = GetTransform()->GetWorldPosition();
	float4 ProjectilePosition = StartPosition + float4{ -250, 70, -5 };

	if (true == IsDebugRender)
	{
		Meteor0->SetCollisionRenderOn();
		Meteor1->SetCollisionRenderOn();
	}
	else
	{
		Meteor0->SetCollisionRenderOff();
		Meteor1->SetCollisionRenderOff();
	}

	Meteor0->SetStartPosition(ProjectilePosition);
	Meteor1->SetStartPosition(ProjectilePosition);

	Meteor1->SetReverse();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                         FSM                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GrimMatchstick::DirectCheck()
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

void GrimMatchstick::ActorInitSetting()
{
	if (nullptr == GameEngineSprite::Find("Dragon_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Phase1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_Idle").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_MeteorAttack_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_MeteorAttack_Intro_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_MeteorAttack_Shoot_Front").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_MeteorAttack_Shoot_LollBack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_MeteorAttack_Outro").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_PeashotAttack_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_PeashotAttack_Shoot").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_PeashotAttack_Outro").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Dragon_Ph2_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_Ph2_Intro_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_Ph2_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_Ph2_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_Ph2_Death").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Ph2_IdleUp_000.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Phase2");
		NewDir.Move("Dragon_Ph2_Idle_T");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_000.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_002.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_003.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_004.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_005.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_006.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_007.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_008.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_009.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_010.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_011.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_012.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Ph2_IdleUp_013.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Dragon_Ph2_Tounge"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_Ph2_Tounge_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_Ph2_Tounge_Intro_Loop").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Fire_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Fire_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Fire_Outro").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_FireSmoke_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_FireSmoke_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_FireSmoke_Outro").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SFX_AttackSmoke_A").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SFX_AttackSmoke_B").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Object_Firework_A_Move"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Firework_A_Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Firework_B_Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Firework_C_Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Firework_C_Jump_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Firework_C_Jump_Loop").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Object_GreenRing"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Phase1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_GreenRing").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_PinkRing").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SFX_EyesAttack").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Meteor").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SFX_MeteorSmoke").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Tail").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "Dragon_Intro", .SpriteName = "Dragon_Intro", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Dragon_Idle", .SpriteName = "Dragon_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });

		RenderPtr->CreateAnimation({ .AnimationName = "Dragon_MeteorAttack_Intro", .SpriteName = "Dragon_MeteorAttack_Intro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Dragon_MeteorAttack_Intro_Loop", .SpriteName = "Dragon_MeteorAttack_Intro_Loop", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Dragon_MeteorAttack_Shoot_Front", .SpriteName = "Dragon_MeteorAttack_Shoot_Front", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Dragon_MeteorAttack_Shoot_LollBack", .SpriteName = "Dragon_MeteorAttack_Shoot_LollBack", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Dragon_MeteorAttack_Outro", .SpriteName = "Dragon_MeteorAttack_Outro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

		RenderPtr->CreateAnimation({ .AnimationName = "Dragon_PeashotAttack_Intro", .SpriteName = "Dragon_PeashotAttack_Intro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Dragon_PeashotAttack_Shoot", .SpriteName = "Dragon_PeashotAttack_Shoot", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Dragon_PeashotAttack_Outro", .SpriteName = "Dragon_PeashotAttack_Outro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

		RenderPtr->CreateAnimation({ .AnimationName = "Dragon_Ph2_Intro_Loop", .SpriteName = "Dragon_Ph2_Intro_Loop", .FrameInter = 0.04f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Dragon_Ph2_Intro", .SpriteName = "Dragon_Ph2_Intro", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Dragon_Ph2_Idle", .SpriteName = "Dragon_Ph2_Idle", .FrameInter = 0.04f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Dragon_Ph2_Death", .SpriteName = "Dragon_Ph2_Death", .FrameInter = 0.04f, .Loop = true, .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("Dragon_Intro");
	}

	if (nullptr == EyeRenderPtr)
	{
		EyeRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		EyeRenderPtr->CreateAnimation({ .AnimationName = "SFX_EyesAttack", .SpriteName = "SFX_EyesAttack", .FrameInter = 0.03f, .Loop = true , .ScaleToTexture = true });
		EyeRenderPtr->CreateAnimation({ .AnimationName = "Dragon_Ph2_Tounge_Intro", .SpriteName = "Dragon_Ph2_Tounge_Intro", .FrameInter = 0.03f, .Loop = false , .ScaleToTexture = true });
		EyeRenderPtr->CreateAnimation({ .AnimationName = "Dragon_Ph2_Tounge_Intro_Loop", .SpriteName = "Dragon_Ph2_Tounge_Intro_Loop", .FrameInter = 0.1f, .Loop = true , .ScaleToTexture = true });
		EyeRenderPtr->GetTransform()->SetLocalPosition({ -55, 300 });
		EyeRenderPtr->ChangeAnimation("SFX_EyesAttack");
		EyeRenderPtr->Off();
	}

	if (nullptr == UpRenderPtr)
	{
		UpRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		UpRenderPtr->SetScaleToTexture("Ph2_IdleUp_000.png");
		UpRenderPtr->Off();
	}

	if (nullptr == FireRenderPtr)
	{
		FireRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		FireRenderPtr->CreateAnimation({ .AnimationName = "Object_Fire_Intro", .SpriteName = "Object_Fire_Intro", .FrameInter = 0.07f, .Loop = false , .ScaleToTexture = true });
		FireRenderPtr->CreateAnimation({ .AnimationName = "Object_Fire_Loop", .SpriteName = "Object_Fire_Loop", .FrameInter = 0.07f, .Loop = true , .ScaleToTexture = true });
		FireRenderPtr->CreateAnimation({ .AnimationName = "Object_Fire_Outro", .SpriteName = "Object_Fire_Outro", .FrameInter = 0.07f, .Loop = false , .ScaleToTexture = true });
		FireRenderPtr->CreateAnimation({ .AnimationName = "Object_FireSmoke_Intro", .SpriteName = "Object_FireSmoke_Intro", .FrameInter = 0.07f, .Loop = false , .ScaleToTexture = true });
		FireRenderPtr->CreateAnimation({ .AnimationName = "Object_FireSmoke_Loop", .SpriteName = "Object_FireSmoke_Loop", .FrameInter = 0.07f, .Loop = true , .ScaleToTexture = true });
		FireRenderPtr->CreateAnimation({ .AnimationName = "Object_FireSmoke_Outro", .SpriteName = "Object_FireSmoke_Outro", .FrameInter = 0.07f, .Loop = false , .ScaleToTexture = true });
		FireRenderPtr->GetTransform()->SetLocalPosition({ -55, 300 });
		FireRenderPtr->ChangeAnimation("Object_Fire_Intro");
		FireRenderPtr->Off();
	}

	if (nullptr == BodyCollisionPtr)
	{
		BodyCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Monster));
		BodyCollisionPtr->SetColType(ColType::AABBBOX2D);
		BodyCollisionPtr->GetTransform()->SetLocalScale({ 180, 570, -50 });
		BodyCollisionPtr->GetTransform()->SetLocalPosition({ 0, 45 });
	}

	if (nullptr == BodyCollisionRenderPtr)
	{
		BodyCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BodyCollisionRenderPtr->GetTransform()->SetLocalScale(BodyCollisionPtr->GetTransform()->GetLocalScale());
		BodyCollisionRenderPtr->GetTransform()->SetLocalPosition(BodyCollisionPtr->GetTransform()->GetLocalPosition());
		BodyCollisionRenderPtr->SetTexture("GreenLine.png");
		BodyCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
		//BodyCollisionRenderPtr->Off();
	}

	if (nullptr == EXCollisionPtr)
	{
		EXCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Monster));
		EXCollisionPtr->SetColType(ColType::AABBBOX2D);
		EXCollisionPtr->GetTransform()->SetLocalScale({ 180, 570, -50 });
		EXCollisionPtr->GetTransform()->SetLocalPosition({ 0, 45 });
	}

	if (nullptr == EXCollisionRenderPtr)
	{
		EXCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		EXCollisionRenderPtr->GetTransform()->SetLocalScale(EXCollisionPtr->GetTransform()->GetLocalScale());
		EXCollisionRenderPtr->GetTransform()->SetLocalPosition(EXCollisionPtr->GetTransform()->GetLocalPosition());
		EXCollisionRenderPtr->SetTexture("RedLine.png");
		EXCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
		//EXCollisionRenderPtr->Off();
	}

	if (nullptr == Plus_BodyCollisionPtr)
	{
		Plus_BodyCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Monster));
		Plus_BodyCollisionPtr->SetColType(ColType::AABBBOX2D);
		Plus_BodyCollisionPtr->GetTransform()->SetLocalScale({ 180, 570, -50 });
		Plus_BodyCollisionPtr->GetTransform()->SetLocalPosition({ 0, 45 });
		Plus_BodyCollisionPtr->Off();
	}

	if (nullptr == Plus_BodyCollisionRenderPtr)
	{
		Plus_BodyCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		Plus_BodyCollisionRenderPtr->GetTransform()->SetLocalScale(Plus_BodyCollisionPtr->GetTransform()->GetLocalScale());
		Plus_BodyCollisionRenderPtr->GetTransform()->SetLocalPosition(Plus_BodyCollisionPtr->GetTransform()->GetLocalPosition());
		Plus_BodyCollisionRenderPtr->SetTexture("GreenLine.png");
		Plus_BodyCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
		Plus_BodyCollisionRenderPtr->Off();
	}

	if (nullptr == Plus_EXCollisionPtr)
	{
		Plus_EXCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Monster));
		Plus_EXCollisionPtr->SetColType(ColType::AABBBOX2D);
		Plus_EXCollisionPtr->GetTransform()->SetLocalScale({ 180, 570, -50 });
		Plus_EXCollisionPtr->GetTransform()->SetLocalPosition({ 0, 45 });
		Plus_EXCollisionPtr->Off();
	}

	if (nullptr == Plus_EXCollisionRenderPtr)
	{
		Plus_EXCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		Plus_EXCollisionRenderPtr->GetTransform()->SetLocalScale(Plus_EXCollisionPtr->GetTransform()->GetLocalScale());
		Plus_EXCollisionRenderPtr->GetTransform()->SetLocalPosition(Plus_EXCollisionPtr->GetTransform()->GetLocalPosition());
		Plus_EXCollisionRenderPtr->SetTexture("RedLine.png");
		Plus_EXCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
		Plus_EXCollisionRenderPtr->Off();
	}

	if (nullptr == FireCollisionPtr)
	{
		FireCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
		FireCollisionPtr->SetColType(ColType::AABBBOX2D);
		FireCollisionPtr->GetTransform()->SetLocalScale({ 50, 200, -50 });
		FireCollisionPtr->GetTransform()->SetLocalPosition({ 0, 45 });
		FireCollisionPtr->Off();
	}

	if (nullptr == FireCollisionRenderPtr)
	{
		FireCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		FireCollisionRenderPtr->GetTransform()->SetLocalScale(Plus_EXCollisionPtr->GetTransform()->GetLocalScale());
		FireCollisionRenderPtr->GetTransform()->SetLocalPosition(Plus_EXCollisionPtr->GetTransform()->GetLocalPosition());
		FireCollisionRenderPtr->SetTexture("GreenBox.png");
		FireCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
		FireCollisionRenderPtr->Off();
	}

	ChangeState(DragonState::Intro);
	RenderPtr->Off();
}
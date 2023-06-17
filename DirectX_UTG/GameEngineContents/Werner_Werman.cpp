#include "PrecompileHeader.h"
#include "Werner_Werman.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"
#include "Peashooter.h"
#include "Peashooter_EX.h"
#include "Spread.h"
#include "Spread_EX.h"

#include "CherryBomb.h"
#include "CatapultProjectile.h"
#include "SpringObject.h"
#include "CanExplosion_SFX.h"

Werner_Werman::Werner_Werman() 
{
}

Werner_Werman::~Werner_Werman() 
{
}

void Werner_Werman::Start()
{
	ActorInitSetting();
}

void Werner_Werman::Update(float _DeltaTime)
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

		if (PlatformCollisionPtr->IsUpdate())
		{
			PlatformCollisionRenderPtr->On();
		}
		else
		{
			PlatformCollisionRenderPtr->Off();
		}
	}
	else
	{
		BodyCollisionRenderPtr->Off();
		EXCollisionRenderPtr->Off();
		PlatformCollisionRenderPtr->Off();
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

void Werner_Werman::HitBlink(float _DeltaTime)
{
	if (false == IsBlink)
	{
		return;
	}

	BlinkTime += _DeltaTime;

	if (BlinkCount == 1)
	{
		BlinkCount = 0;

		OriginMulColor = CanRenderPtr->ColorOptionValue.MulColor;
		BlinkMulColor.r = 0.2f;
		BlinkMulColor.g = 0.2f;
		BlinkMulColor.b = 0.35f;
		CanRenderPtr->ColorOptionValue.MulColor += BlinkMulColor;
		CanBackRenderPtr->ColorOptionValue.MulColor += BlinkMulColor;
		MouseRenderPtr->ColorOptionValue.MulColor += BlinkMulColor;
		WeaponRender->ColorOptionValue.MulColor += BlinkMulColor;
	}

	if (BlinkTime >= 0.1f)
	{
		BlinkCount = 1;
		BlinkTime = 0.0f;
		IsBlink = false;

		CanRenderPtr->ColorOptionValue.MulColor = OriginMulColor;
		CanBackRenderPtr->ColorOptionValue.MulColor = OriginMulColor;
		MouseRenderPtr->ColorOptionValue.MulColor = OriginMulColor;
		WeaponRender->ColorOptionValue.MulColor = OriginMulColor;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                    CollisionCheck                    /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Werner_Werman::PlatformCollisionCheck(float _Value)
{
	/////////////// Platform
	if (nullptr != PlatformCollisionPtr->Collision(static_cast<int>(CollisionOrder::PlayerFrontSensor), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		Player::MainPlayer->PlayerBlockDisturbance(_Value);
	}

	if (nullptr != PlatformCollisionPtr->Collision(static_cast<int>(CollisionOrder::PlayerBottomSensor), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		if (true == Player::MainPlayer->GetPlatformCheckAble())
		{
			Player::MainPlayer->PlayerMoveDisturbance(_Value);
		}
	}
}

void Werner_Werman::CollisionCheck()
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
}

void Werner_Werman::CollisionSetting()
{
	BodyCollisionRenderPtr->GetTransform()->SetLocalScale(BodyCollisionPtr->GetTransform()->GetLocalScale());
	EXCollisionRenderPtr->GetTransform()->SetLocalScale(EXCollisionPtr->GetTransform()->GetLocalScale());
	
	if (false == IsPhase2)
	{
		BodyCollisionRenderPtr->GetTransform()->SetLocalPosition(BodyCollisionPtr->GetTransform()->GetLocalPosition());
		EXCollisionRenderPtr->GetTransform()->SetLocalPosition(EXCollisionPtr->GetTransform()->GetLocalPosition());
	}
	else
	{
		BodyCollisionRenderPtr->GetTransform()->SetLocalPosition(Phase2Parent->GetTransform()->GetLocalPosition() + BodyCollisionPtr->GetTransform()->GetLocalPosition());
		EXCollisionRenderPtr->GetTransform()->SetLocalPosition(Phase2Parent->GetTransform()->GetLocalPosition() + EXCollisionPtr->GetTransform()->GetLocalPosition());
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     CreateActor                      ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Werner_Werman::CreateCherryBomb()
{
	std::shared_ptr<CherryBomb> Projectile = GetLevel()->CreateActor<CherryBomb>();
	float4 StartPosition = WeaponRender->GetTransform()->GetWorldPosition();
	float4 ProjectilePosition = float4::Zero;

	if (false == Directbool)
	{
		ProjectilePosition = StartPosition + float4{ -25, 10, -1 };
	}
	else
	{
		ProjectilePosition = StartPosition + float4{ 25, 10, -1 };
	}

	int RandC = GameEngineRandom::MainRandom.RandomInt(0, (6 - CannonFireCount));

	if (0 == RandC && false == ParryBombCreate)
	{
		ParryBombCreate = true;
		Projectile->SetParryBombCreate();
	}

	if (true == IsDebugRender)
	{
		Projectile->SetCollisionRenderOn();
	}
	else
	{
		Projectile->SetCollisionRenderOff();
	}

	int RandC2 = GameEngineRandom::MainRandom.RandomInt(0, 2);

	if (0 == RandC2)
	{
		Projectile->SetJumpPower(550.0f);
	}
	else if (1 == RandC2)
	{
		Projectile->SetJumpPower(600.0f);
	}
	else if (2 == RandC2)
	{
		Projectile->SetJumpPower(700.0f);
	}

	Projectile->SetColMap(Player::MainPlayer->GetColMap(), PixelCollision::Coordinate::Custom);
	Projectile->SetStartPosition(ProjectilePosition);
	Projectile->SetDirection(Directbool);
}

void Werner_Werman::CreateCatapultProjectile()
{
	std::shared_ptr<CatapultProjectile> Projectile0 = GetLevel()->CreateActor<CatapultProjectile>();
	std::shared_ptr<CatapultProjectile> Projectile1 = GetLevel()->CreateActor<CatapultProjectile>();
	std::shared_ptr<CatapultProjectile> Projectile2 = GetLevel()->CreateActor<CatapultProjectile>();
	std::shared_ptr<CatapultProjectile> Projectile3 = GetLevel()->CreateActor<CatapultProjectile>();
	std::shared_ptr<CatapultProjectile> Projectile4 = GetLevel()->CreateActor<CatapultProjectile>();

	float4 StartPosition = WeaponRender->GetTransform()->GetWorldPosition();

	float4 ProjectilePosition = float4::Zero;

	float4 ProjectileRotation0 = float4::Zero;
	float4 ProjectileRotation1 = float4::Zero;
	float4 ProjectileRotation2 = float4::Zero;
	float4 ProjectileRotation3 = float4::Zero;
	float4 ProjectileRotation4 = float4::Zero;

	if (false == Directbool)
	{
		ProjectilePosition = StartPosition + float4{ -50, 100, -1 };

		ProjectileRotation0 += float4{ 0, 0, 350 };
		ProjectileRotation1 += float4{ 0, 0, 5 };
		ProjectileRotation2 += float4{ 0, 0, 20 };
		ProjectileRotation3 += float4{ 0, 0, 35 };
		ProjectileRotation4 += float4{ 0, 0, 50 };
	}
	else
	{
		ProjectilePosition = StartPosition + float4{ 45, 100, -1 };

		ProjectileRotation0 += float4{ 0, 0, 10 };
		ProjectileRotation1 += float4{ 0, 0, 355 };
		ProjectileRotation2 += float4{ 0, 0, 340 };
		ProjectileRotation3 += float4{ 0, 0, 325 };
		ProjectileRotation4 += float4{ 0, 0, 310 };
	}

	if (true == IsDebugRender)
	{
		Projectile0->SetCollisionRenderOn();
		Projectile1->SetCollisionRenderOn();
		Projectile2->SetCollisionRenderOn();
		Projectile3->SetCollisionRenderOn();
		Projectile4->SetCollisionRenderOn();
	}
	else
	{
		Projectile0->SetCollisionRenderOff();
		Projectile1->SetCollisionRenderOff();
		Projectile2->SetCollisionRenderOff();
		Projectile3->SetCollisionRenderOff();
		Projectile4->SetCollisionRenderOff();
	}

	Projectile0->SetStartPosition(ProjectilePosition);
	Projectile1->SetStartPosition(ProjectilePosition);
	Projectile2->SetStartPosition(ProjectilePosition);
	Projectile3->SetStartPosition(ProjectilePosition);
	Projectile4->SetStartPosition(ProjectilePosition);

	Projectile0->SetProjectileRotation(ProjectileRotation0);
	Projectile1->SetProjectileRotation(ProjectileRotation1);
	Projectile2->SetProjectileRotation(ProjectileRotation2);
	Projectile3->SetProjectileRotation(ProjectileRotation3);
	Projectile4->SetProjectileRotation(ProjectileRotation4);

	Projectile0->SetDirection(Directbool);
	Projectile1->SetDirection(Directbool);
	Projectile2->SetDirection(Directbool);
	Projectile3->SetDirection(Directbool);
	Projectile4->SetDirection(Directbool);

	Projectile1->SetParryProjectileCreate();
	Projectile2->SetParryProjectileCreate();
	Projectile0->SetProjectileRandomAnimation();
	Projectile3->SetProjectileRandomAnimation();
	Projectile4->SetProjectileRandomAnimation();
}

void Werner_Werman::CreateSpringObject()
{
	std::shared_ptr<SpringObject> Spring0 = GetLevel()->CreateActor<SpringObject>();
	std::shared_ptr<SpringObject> Spring1 = GetLevel()->CreateActor<SpringObject>();

	float4 StartPosition = GetTransform()->GetWorldPosition();
	float4 ProjectilePosition = StartPosition + float4{0, 250};

	if (true == IsDebugRender)
	{
		Spring0->SetCollisionRenderOn();
		Spring1->SetCollisionRenderOn();
	}
	else
	{
		Spring0->SetCollisionRenderOff();
		Spring1->SetCollisionRenderOff();
	}

	Spring0->SetStartPosition(ProjectilePosition);
	Spring1->SetStartPosition(ProjectilePosition);

	Spring0->SetMoveSpeed(300.0f);
	Spring1->SetMoveSpeed(500.0f);

	Spring0->SetColMap(Player::MainPlayer->GetColMap(), PixelCollision::Coordinate::Custom);
	Spring1->SetColMap(Player::MainPlayer->GetColMap(), PixelCollision::Coordinate::Custom);
}

void Werner_Werman::CreateExplosionSFX()
{
	std::shared_ptr<CanExplosion_SFX> CanExplosion = GetLevel()->CreateActor<CanExplosion_SFX>();

	float4 StartPosition = GetTransform()->GetWorldPosition();
	float4 CanExplosionPosition = StartPosition + float4{ 0, 0, -5 };

	CanExplosion->SetStartPosition(CanExplosionPosition);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                         FSM                       /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Werner_Werman::DirectCheck()
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

void Werner_Werman::ActorInitSetting()
{
	if (nullptr == GameEngineSprite::Find("Mouse_Intro"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_Intro_Front").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_Intro_Smoke").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_PopOut").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_ShakeFist").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_Dash_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_Dash_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_Dash_Outro").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Cannon_In"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");
		NewDir.Move("Object_Cannon");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cannon_In").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cannon_Out").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cannon_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cannon_Shoot").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Catapult_Loop"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");
		NewDir.Move("Object_Catapult");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Catapult_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Catapult_Reload").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Catapult_Reload_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Catapult_Fire").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Can_Part_Body_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Part_Body_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Part_Body_Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Part_Body_In").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Part_Body_Out").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Part_Wheels").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("CherryBomb_Normal"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");
		NewDir.Move("Object_CherryBomb");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CherryBomb_Normal").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CherryBomb_Pink").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CherryBomb_Explode").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CherryBomb_Fire_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CherryBomb_Fire_Loop").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("CatapultProjectile_Bolt"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");
		NewDir.Move("Object_CatapultProjectile");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CatapultProjectile_Bolt").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CatapultProjectile_Coin").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CatapultProjectile_Gum").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CatapultProjectile_Nut").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CatapultProjectile_Popcap").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CatapultProjectile_Tooth").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Spring_Intro"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");
		NewDir.Move("Object_Spring");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Spring_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Spring_Land").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Spring_Idle_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Spring_Launch").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Spring_Death").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Can_Explosion_Intro"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Explosion_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Explosion_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Explosion_Outro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Explosion_SFX").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_IntroBomb").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Can_Explosion_SFX"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Explosion_SFX").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Plat_Loop"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Plat_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Plat_MoveLeft").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Plat_MoveRight").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Mouse_TransitionA"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_TransitionA").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_TransitionA_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_TransitionB").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_TransitionB_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_TransitionC").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_TransitionC_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_TransitionD").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_TransitionD_Loop").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Can_Tin_Up"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Can_Tin_Up").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Object_Flamecannon"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_Flamecannon").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Scissor_Intro"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase2");
		NewDir.Move("Object_Scissor");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Scissor_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Scissor_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Scissor_Down_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Scissor_Up").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Scissor_Up_Loop").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Can_Idle_Up_001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");
		NewDir.Move("Can_Part_Body_IdleUp");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Idle_Up_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Idle_Up_002.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Idle_Up_003.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Can_Idle_Back_001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");
		NewDir.Move("Can_Part_Back_Idle");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Idle_Back_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Idle_Back_002.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Idle_Back_003.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Can_Part_Back_InOut_001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");
		NewDir.Move("Can_Part_Back_InOut");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Part_Back_InOut_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Part_Back_InOut_002.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Part_Back_InOut_003.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Can_Move_Back_001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");
		NewDir.Move("Can_Part_Back_Move");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_002.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_003.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_004.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_005.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_006.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_007.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_008.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_009.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_010.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_011.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_012.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_013.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_014.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_015.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_016.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_017.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_018.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_019.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_020.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_021.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_022.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_023.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Can_Move_Back_024.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Mouse_Intro_Top_007.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase1");
		NewDir.Move("Mouse_Intro_Front");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_007.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_008.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_009.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_010.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_011.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_012.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_013.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_014.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_015.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_016.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_017.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_018.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_019.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_020.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_021.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_022.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_023.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_024.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_025.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_026.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_027.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_028.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_029.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_030.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_031.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_032.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_046.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_047.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_048.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Mouse_Intro_Top_049.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Tin_Boil_Back_001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Phase2");
		NewDir.Move("Can_Tin_Back");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Tin_Boil_Back_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Tin_Boil_Back_002.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Tin_Boil_Back_003.png").GetFullPath());
	}

	if (nullptr == CanBackRenderPtr)
	{
		CanBackRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		CanBackRenderPtr->GetTransform()->SetLocalPosition({ 0, 144 });
		CanBackRenderPtr->SetScaleToTexture("Can_Idle_Back_001.png");
	}

	if (nullptr == WeaponRender)
	{
		WeaponRender = CreateComponent<GameEngineSpriteRenderer>();
		WeaponRender->CreateAnimation({ .AnimationName = "Cannon_In", .SpriteName = "Cannon_In", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		WeaponRender->CreateAnimation({ .AnimationName = "Cannon_Out", .SpriteName = "Cannon_Out", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		WeaponRender->CreateAnimation({ .AnimationName = "Cannon_Idle", .SpriteName = "Cannon_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		WeaponRender->CreateAnimation({ .AnimationName = "Cannon_Fire", .SpriteName = "Cannon_Shoot", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

		WeaponRender->CreateAnimation({ .AnimationName = "Catapult_Loop", .SpriteName = "Catapult_Loop", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		WeaponRender->CreateAnimation({ .AnimationName = "Catapult_Reload", .SpriteName = "Catapult_Reload", .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true });
		WeaponRender->CreateAnimation({ .AnimationName = "Catapult_Reload_Loop", .SpriteName = "Catapult_Reload_Loop", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		WeaponRender->CreateAnimation({ .AnimationName = "Catapult_Fire", .SpriteName = "Catapult_Fire", .FrameInter = 0.055f, .Loop = false, .ScaleToTexture = true });

		WeaponRender->CreateAnimation({ .AnimationName = "Object_IntroBomb", .SpriteName = "Object_IntroBomb", .FrameInter = 0.065f, .Loop = false, .ScaleToTexture = true });

		WeaponRender->CreateAnimation({ .AnimationName = "Scissor_Intro", .SpriteName = "Scissor_Intro", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
		WeaponRender->CreateAnimation({ .AnimationName = "Scissor_Down", .SpriteName = "Scissor_Down", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
		WeaponRender->CreateAnimation({ .AnimationName = "Scissor_Down_Loop", .SpriteName = "Scissor_Down_Loop", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
		WeaponRender->CreateAnimation({ .AnimationName = "Scissor_Up", .SpriteName = "Scissor_Up", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
		WeaponRender->CreateAnimation({ .AnimationName = "Scissor_Up_Loop", .SpriteName = "Scissor_Up_Loop", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });

		WeaponRender->GetTransform()->AddLocalPosition({ -70, 250 });
		WeaponRender->ChangeAnimation("Cannon_Out");
		WeaponRender->Off();
	}

	if (nullptr == FlamecannonRenderPtr_Left)
	{
		FlamecannonRenderPtr_Left = CreateComponent<GameEngineSpriteRenderer>();
		FlamecannonRenderPtr_Left->CreateAnimation({ .AnimationName = "Object_Flamecannon", .SpriteName = "Object_Flamecannon", .FrameInter = 0.065f, .Loop = true, .ScaleToTexture = true });
		FlamecannonRenderPtr_Left->ChangeAnimation("Object_Flamecannon");
		FlamecannonRenderPtr_Left->Off();
	}

	if (nullptr == FlamecannonRenderPtr_Right)
	{
		FlamecannonRenderPtr_Right = CreateComponent<GameEngineSpriteRenderer>();
		FlamecannonRenderPtr_Right->CreateAnimation({ .AnimationName = "Object_Flamecannon", .SpriteName = "Object_Flamecannon", .FrameInter = 0.065f, .Loop = true, .ScaleToTexture = true });
		FlamecannonRenderPtr_Right->ChangeAnimation("Object_Flamecannon");
		FlamecannonRenderPtr_Right->Off();
	}

	if (nullptr == CanRenderPtr)
	{
		CanRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		CanRenderPtr->CreateAnimation({ .AnimationName = "Can_Idle", .SpriteName = "Can_Part_Body_Idle", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		CanRenderPtr->CreateAnimation({ .AnimationName = "Can_Move", .SpriteName = "Can_Part_Body_Move", .FrameInter = 0.055f, .Loop = true, .ScaleToTexture = true });
		CanRenderPtr->CreateAnimation({ .AnimationName = "Can_MouseIn", .SpriteName = "Can_Part_Body_In", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		CanRenderPtr->CreateAnimation({ .AnimationName = "Can_MouseOut", .SpriteName = "Can_Part_Body_Out", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		CanRenderPtr->CreateAnimation({ .AnimationName = "Can_Explosion_Intro", .SpriteName = "Can_Explosion_Intro", .FrameInter = 0.045f, .Loop = false, .ScaleToTexture = true });
		CanRenderPtr->CreateAnimation({ .AnimationName = "Can_Explosion_Loop", .SpriteName = "Can_Explosion_Loop", .FrameInter = 0.045f, .Loop = true, .ScaleToTexture = true });
		CanRenderPtr->CreateAnimation({ .AnimationName = "Can_Explosion_Outro", .SpriteName = "Can_Explosion_Outro", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });

		CanRenderPtr->ChangeAnimation("Can_Idle");
	}

	if (nullptr == MouseRenderPtr)
	{
		MouseRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		MouseRenderPtr->CreateAnimation({ .AnimationName = "Mouse_Intro", .SpriteName = "Mouse_Intro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		MouseRenderPtr->CreateAnimation({ .AnimationName = "Mouse_PopOut", .SpriteName = "Mouse_PopOut", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		MouseRenderPtr->CreateAnimation({ .AnimationName = "Mouse_ShakeFist", .SpriteName = "Mouse_ShakeFist", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		MouseRenderPtr->CreateAnimation({ .AnimationName = "Mouse_Dash_Intro", .SpriteName = "Mouse_Dash_Intro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		MouseRenderPtr->CreateAnimation({ .AnimationName = "Mouse_Dash_Loop", .SpriteName = "Mouse_Dash_Loop", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		MouseRenderPtr->CreateAnimation({ .AnimationName = "Mouse_Dash_Outro", .SpriteName = "Mouse_Dash_Outro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

		MouseRenderPtr->CreateAnimation({ .AnimationName = "Mouse_TransitionA", .SpriteName = "Mouse_TransitionA", .FrameInter = 0.035f, .Loop = false, .ScaleToTexture = true });
		MouseRenderPtr->CreateAnimation({ .AnimationName = "Mouse_TransitionA_Loop", .SpriteName = "Mouse_TransitionA_Loop", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		MouseRenderPtr->CreateAnimation({ .AnimationName = "Mouse_TransitionB", .SpriteName = "Mouse_TransitionB", .FrameInter = 0.035f, .Loop = false, .ScaleToTexture = true });
		MouseRenderPtr->CreateAnimation({ .AnimationName = "Mouse_TransitionB_Loop", .SpriteName = "Mouse_TransitionB_Loop", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		MouseRenderPtr->CreateAnimation({ .AnimationName = "Mouse_TransitionC", .SpriteName = "Mouse_TransitionC", .FrameInter = 0.035f, .Loop = false, .ScaleToTexture = true });
		MouseRenderPtr->CreateAnimation({ .AnimationName = "Mouse_TransitionC_Loop", .SpriteName = "Mouse_TransitionC_Loop", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		MouseRenderPtr->CreateAnimation({ .AnimationName = "Mouse_TransitionD", .SpriteName = "Mouse_TransitionD", .FrameInter = 0.035f, .Loop = false, .ScaleToTexture = true });
		MouseRenderPtr->CreateAnimation({ .AnimationName = "Mouse_TransitionD_Loop", .SpriteName = "Mouse_TransitionD_Loop", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		MouseRenderPtr->GetTransform()->AddLocalPosition({ 0, 250 });
		MouseRenderPtr->ChangeAnimation("Mouse_Intro");
	}

	if (nullptr == CanUpRenderPtr)
	{
		CanUpRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		CanUpRenderPtr->SetScaleToTexture("Can_Idle_Up_001.png");
	}

	if (nullptr == MouseUpRenderPtr)
	{
		MouseUpRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		MouseUpRenderPtr->SetScaleToTexture("Mouse_Intro_Top_007.png");
		MouseUpRenderPtr->GetTransform()->AddLocalPosition({ 0, 250 });
		MouseUpRenderPtr->Off();
	}

	if (nullptr == WheelRenderPtr)
	{
		WheelRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		WheelRenderPtr->CreateAnimation({ .AnimationName = "Wheel_Move", .SpriteName = "Can_Part_Wheels", .FrameInter = 0.055f, .Loop = true, .ScaleToTexture = true });
		WheelRenderPtr->CreateAnimation({ .AnimationName = "Plat_Loop", .SpriteName = "Plat_Loop", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		WheelRenderPtr->CreateAnimation({ .AnimationName = "Plat_MoveLeft", .SpriteName = "Plat_MoveLeft", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		WheelRenderPtr->CreateAnimation({ .AnimationName = "Plat_MoveRight", .SpriteName = "Plat_MoveRight", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		WheelRenderPtr->GetTransform()->SetLocalPosition({ 20, -130 });
		WheelRenderPtr->ChangeAnimation("Wheel_Move");
		WheelRenderPtr->Off();
	}

	if (nullptr == BodyCollisionPtr)
	{
		BodyCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Monster));
		BodyCollisionPtr->SetColType(ColType::AABBBOX2D);
		BodyCollisionPtr->GetTransform()->SetLocalScale({ 180, 310, -2 });
		BodyCollisionPtr->GetTransform()->SetLocalPosition({ 0, 0 });
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
		EXCollisionPtr->GetTransform()->SetLocalScale({ 180, 310, -2 });
		EXCollisionPtr->GetTransform()->SetLocalPosition({ 0, 0 });
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

	if (nullptr == PlatformCollisionPtr)
	{
		PlatformCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Platform));
		PlatformCollisionPtr->GetTransform()->SetLocalScale({ 280, 40, -2 });
		PlatformCollisionPtr->GetTransform()->SetLocalPosition({ 0, -100 });
		PlatformCollisionPtr->Off();
	}

	if (nullptr == PlatformCollisionRenderPtr)
	{
		PlatformCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		PlatformCollisionRenderPtr->GetTransform()->SetLocalScale(PlatformCollisionPtr->GetTransform()->GetLocalScale());
		PlatformCollisionRenderPtr->GetTransform()->SetLocalPosition(PlatformCollisionPtr->GetTransform()->GetLocalPosition());
		PlatformCollisionRenderPtr->SetTexture("GreenBox.png");
		PlatformCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.6f;
		PlatformCollisionRenderPtr->Off();
	}

	ChangeState(MouseState::Idle);
}
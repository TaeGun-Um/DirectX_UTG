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
}

void GrimMatchstick::CollisionSetting()
{
	BodyCollisionRenderPtr->GetTransform()->SetLocalScale(BodyCollisionPtr->GetTransform()->GetLocalScale());
	EXCollisionRenderPtr->GetTransform()->SetLocalScale(EXCollisionPtr->GetTransform()->GetLocalScale());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     CreateActor                      ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GrimMatchstick::CreateRing()
{

}

void GrimMatchstick::CreateMeteor()
{
	std::shared_ptr<Object_Meteor> Meteor0 = GetLevel()->CreateActor<Object_Meteor>();
	std::shared_ptr<Object_Meteor> Meteor1 = GetLevel()->CreateActor<Object_Meteor>();

	float4 StartPosition = GetTransform()->GetWorldPosition();
	float4 ProjectilePosition = StartPosition + float4{ -220, 50, -5 };

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

void GrimMatchstick::CreateTail()
{

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

		RenderPtr->ChangeAnimation("Dragon_Intro");
	}

	//if (nullptr == UpRenderPtr)
	//{
	//	UpRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	//	UpRenderPtr->CreateAnimation({ .AnimationName = "Dragon_Idle", .SpriteName = "Dragon_Idle", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
	//	UpRenderPtr->ChangeAnimation("Dragon_Idle");
	//}

	if (nullptr == EyeRenderPtr)
	{
		EyeRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		EyeRenderPtr->CreateAnimation({ .AnimationName = "SFX_EyesAttack", .SpriteName = "SFX_EyesAttack", .FrameInter = 0.03f, .Loop = true , .ScaleToTexture = true });
		EyeRenderPtr->GetTransform()->SetLocalPosition({ -55, 300 });
		EyeRenderPtr->ChangeAnimation("SFX_EyesAttack");
		EyeRenderPtr->Off();
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

	ChangeState(DragonState::Intro);
	RenderPtr->Off();
}
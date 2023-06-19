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
	//BodyCollisionRenderPtr->GetTransform()->SetLocalScale(BodyCollisionPtr->GetTransform()->GetLocalScale());
	//EXCollisionRenderPtr->GetTransform()->SetLocalScale(EXCollisionPtr->GetTransform()->GetLocalScale());

	//if (false == IsPhase2)
	//{
	//	BodyCollisionRenderPtr->GetTransform()->SetLocalPosition(BodyCollisionPtr->GetTransform()->GetLocalPosition());
	//	EXCollisionRenderPtr->GetTransform()->SetLocalPosition(EXCollisionPtr->GetTransform()->GetLocalPosition());
	//}
	//else
	//{
	//	BodyCollisionRenderPtr->GetTransform()->SetLocalPosition(Phase2Parent->GetTransform()->GetLocalPosition() + BodyCollisionPtr->GetTransform()->GetLocalPosition());
	//	EXCollisionRenderPtr->GetTransform()->SetLocalPosition(Phase2Parent->GetTransform()->GetLocalPosition() + EXCollisionPtr->GetTransform()->GetLocalPosition());
	//}
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

void Katzenwagen::ActorInitSetting()
{
	//if (nullptr == GameEngineSprite::Find("Bottlecap_A"))
	//{
	//	GameEngineDirectory NewDir;
	//	NewDir.MoveParentToDirectory("CupHead_Resource");
	//	NewDir.Move("CupHead_Resource");
	//	NewDir.Move("Image");
	//	NewDir.Move("Character");
	//	NewDir.Move("3_Werner_Werman");
	//	NewDir.Move("Phase2");
	//	NewDir.Move("Sidsticks_Bottlecap");

	//	GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottlecap_A").GetFullPath());
	//	GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottlecap_B").GetFullPath());
	//	GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottlecap_C").GetFullPath());
	//	GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottlecap_D").GetFullPath());
	//	GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottlecap_E").GetFullPath());
	//	GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottlecap_F").GetFullPath());
	//}

	//if (nullptr == GameEngineTexture::Find("Tin_Boil_Back_001.png"))
	//{
	//	GameEngineDirectory NewDir;
	//	NewDir.MoveParentToDirectory("CupHead_Resource");
	//	NewDir.Move("CupHead_Resource");
	//	NewDir.Move("Image");
	//	NewDir.Move("Character");
	//	NewDir.Move("3_Werner_Werman");
	//	NewDir.Move("Phase2");
	//	NewDir.Move("Can_Tin_Back");

	//	GameEngineTexture::Load(NewDir.GetPlusFileName("Tin_Boil_Back_001.png").GetFullPath());
	//	GameEngineTexture::Load(NewDir.GetPlusFileName("Tin_Boil_Back_002.png").GetFullPath());
	//	GameEngineTexture::Load(NewDir.GetPlusFileName("Tin_Boil_Back_003.png").GetFullPath());
	//}

	//if (nullptr == CanUpRenderPtr)
	//{
	//	CanUpRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	//	CanUpRenderPtr->SetScaleToTexture("Can_Idle_Up_001.png");
	//}

	if (nullptr == TailHandRenderPtr)
	{
		TailHandRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		//TailHandRenderPtr->CreateAnimation({ .AnimationName = "Object_Flamecannon", .SpriteName = "Object_Flamecannon", .FrameInter = 0.065f, .Loop = true, .ScaleToTexture = true });
		//TailHandRenderPtr->ChangeAnimation("Object_Flamecannon");
	}

	if (nullptr == RightHandRenderPtr)
	{
		RightHandRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		//RightHandRenderPtr->CreateAnimation({ .AnimationName = "Object_Flamecannon", .SpriteName = "Object_Flamecannon", .FrameInter = 0.065f, .Loop = true, .ScaleToTexture = true });
		//RightHandRenderPtr->ChangeAnimation("Object_Flamecannon");
	}

	if (nullptr == LeftHandRenderPtr)
	{
		LeftHandRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		//LeftHandRenderPtr->CreateAnimation({ .AnimationName = "Object_Flamecannon", .SpriteName = "Object_Flamecannon", .FrameInter = 0.065f, .Loop = true, .ScaleToTexture = true });
		//LeftHandRenderPtr->ChangeAnimation("Object_Flamecannon");
	}

	if (nullptr == BodyRenderPtr)
	{
		BodyRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		//BodyRenderPtr->CreateAnimation({ .AnimationName = "Object_Flamecannon", .SpriteName = "Object_Flamecannon", .FrameInter = 0.065f, .Loop = true, .ScaleToTexture = true });
		//BodyRenderPtr->ChangeAnimation("Object_Flamecannon");
	}

	if (nullptr == HeadRenderPtr)
	{
		HeadRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		//HeadRenderPtr->CreateAnimation({ .AnimationName = "Object_Flamecannon", .SpriteName = "Object_Flamecannon", .FrameInter = 0.065f, .Loop = true, .ScaleToTexture = true });
		//HeadRenderPtr->ChangeAnimation("Object_Flamecannon");
	}

	if (nullptr == BodyCollisionPtr)
	{
		BodyCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterHitBox));
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
		EXCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterHitBox));
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

	if (nullptr == AttackCollisionPtr)
	{
		AttackCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Monster));
		AttackCollisionPtr->SetColType(ColType::AABBBOX2D);
		AttackCollisionPtr->GetTransform()->SetLocalScale({ 180, 310, -2 });
		AttackCollisionPtr->GetTransform()->SetLocalPosition({ 0, 0 });
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
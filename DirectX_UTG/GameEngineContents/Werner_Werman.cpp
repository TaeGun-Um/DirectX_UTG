#include "PrecompileHeader.h"
#include "Werner_Werman.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"
#include "Peashooter.h"
#include "Peashooter_EX.h"
#include "Spread.h"
#include "Spread_EX.h"

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
	}

	if (BlinkTime >= 0.1f)
	{
		BlinkCount = 1;
		BlinkTime = 0.0f;
		IsBlink = false;

		CanRenderPtr->ColorOptionValue.MulColor = OriginMulColor;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                    CollisionCheck                    /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
	BodyCollisionRenderPtr->GetTransform()->SetLocalPosition(BodyCollisionPtr->GetTransform()->GetLocalPosition());

	EXCollisionRenderPtr->GetTransform()->SetLocalScale(EXCollisionPtr->GetTransform()->GetLocalScale());
	EXCollisionRenderPtr->GetTransform()->SetLocalPosition(EXCollisionPtr->GetTransform()->GetLocalPosition());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     CreateActor                      ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mouse_Dash").GetFullPath());
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
		WeaponRender->GetTransform()->AddLocalPosition({ -70, 250 });
		WeaponRender->ChangeAnimation("Cannon_Out");
		WeaponRender->Off();
	}

	if (nullptr == CanRenderPtr)
	{
		CanRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		CanRenderPtr->CreateAnimation({ .AnimationName = "Can_Idle", .SpriteName = "Can_Part_Body_Idle", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		CanRenderPtr->CreateAnimation({ .AnimationName = "Can_Move", .SpriteName = "Can_Part_Body_Move", .FrameInter = 0.055f, .Loop = true, .ScaleToTexture = true });
		CanRenderPtr->CreateAnimation({ .AnimationName = "Can_MouseIn", .SpriteName = "Can_Part_Body_In", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		CanRenderPtr->CreateAnimation({ .AnimationName = "Can_MouseOut", .SpriteName = "Can_Part_Body_Out", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
		CanRenderPtr->ChangeAnimation("Can_Idle");
	}

	if (nullptr == MouseRenderPtr)
	{
		MouseRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		MouseRenderPtr->CreateAnimation({ .AnimationName = "Mouse_Intro", .SpriteName = "Mouse_Intro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		MouseRenderPtr->GetTransform()->AddLocalPosition({ 0, 250 });
		MouseRenderPtr->ChangeAnimation("Mouse_Intro");
	}

	if (nullptr == CanUpRenderPtr)
	{
		CanUpRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		//CanUpRenderPtr->GetTransform()->SetLocalPosition({ 0, 250 });
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
		WheelRenderPtr->GetTransform()->SetLocalPosition({ 20, -130 });
		WheelRenderPtr->ChangeAnimation("Wheel_Move");
		WheelRenderPtr->Off();
	}

	if (nullptr == BodyCollisionPtr)
	{
		BodyCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Monster));
		BodyCollisionPtr->SetColType(ColType::AABBBOX2D);
		BodyCollisionPtr->GetTransform()->SetLocalScale({ 180, 310, 1 });
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
		EXCollisionPtr->GetTransform()->SetLocalScale({ 180, 310, 1 });
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

	ChangeState(MouseState::Idle);
}
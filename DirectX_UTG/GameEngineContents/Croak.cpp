#include "PrecompileHeader.h"
#include "Croak.h"

#include <cmath>

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"
#include "Peashooter.h"
#include "Peashooter_EX.h"
#include "Spread.h"
#include "Spread_EX.h"

#include "Ribby.h"
#include "Croak_Firefly.h"
#include "Slot_FrontDust.h"
#include "CoinAttack_Projectile.h"
#include "DeathExplosion.h"

#include "Platform_Vipor.h"
#include "Platform_Bison.h"
#include "Platform_Tiger.h"

Croak* Croak::CroakPtr = nullptr;

Croak::Croak() 
{
}

Croak::~Croak() 
{
}

void Croak::Start()
{
	CroakPtr = this;
	ActorInitSetting();
}

void Croak::Update(float _DeltaTime)
{
	MoveAbleTime += _DeltaTime;

	if (MoveAbleTime <= 0.5f)
	{
		return;
	}

	if (true == IsDebugRender)
	{
		BodyCollisionRenderPtr->On();
		EXCollisionRenderPtr->On();
		
		if (true == PlusEXCollisionPtr->IsUpdate())
		{
			PlusBodyCollisionRenderPtr->On();
			PlusEXCollisionRenderPtr->On();
		}
		else
		{
			PlusBodyCollisionRenderPtr->Off();
			PlusEXCollisionRenderPtr->Off();
		}

		if (true == ParryCollisionPtr->IsUpdate())
		{
			ParryCollisionRenderPtr->On();
		}
		else
		{
			ParryCollisionRenderPtr->Off();
		}
	}
	else
	{
		BodyCollisionRenderPtr->Off();
		EXCollisionRenderPtr->Off();
		PlusBodyCollisionRenderPtr->Off();
		PlusEXCollisionRenderPtr->Off();
		ParryCollisionRenderPtr->Off();
	}

	UpdateState(_DeltaTime);
	CollisionCheck();
	CollisionSetting();
	HitBlink(_DeltaTime);
	RulletActivate(_DeltaTime);

	RulletActivate(_DeltaTime); // 룰렛
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     AssistFunction                     ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Croak::SetInitReset()
{
	MoveAbleTime = 0.0f;
	StateValue = CroakState::Idle;
	ChangeState(CroakState::Idle);
	HP = 1000;

	IsRulletActivate = false;
	IsVipor = false;
	IsBison = false;
	IsTiger = false;
	RulletWave0 = false;
	RulletWave1 = false;
	RulletWave2 = false;

	WaveTime0 = 0.0f;
	WaveTime1 = 0.0f;
	WaveTime2 = 0.0f;
	RulletSelectDelayTime = 0.0f;
	RulletDelayTime = 0.0f;
	IntroLoopTime = 0.0f;
	IdleDelayTime = 0.0f;
	CreateMob_LoopTime = 0.0f;
	AFanLoopTime = 0.0f;
	BFanLoopTime = 0.0f;
	MorphDealyTime = 0.0f;
	CoinAttackTime = 0.0f;
	ImageBlinkTime = 0.0f;

	RulletTime = 0.0f; // 임시
	RulletLoopTime = 0.0f; // 임시

	IsIntro = true;
	IsCreatefly = false;
	CreateAction = false;
	CreateLoop = false;
	LoopCreateAction = false;
	LoopCreateEnd = false;
	IsMorph = false;
	SlotInvincibility = false;
	IsRullet = false;
	IsArmParry = false;
	IsRulletActivate = false;
	IsVipor = false;
	IsBison = false;
	IsTiger = false;
	RulletWave0 = false;
	RulletWave1 = false;
	RulletWave2 = false;

	CreatePlus = 0;
	CreateMobCount = 0;
	CreateCoinCount = 0;
	RibbyFistCount = 0;
	CroakCrateMobCount = 0;
	MaxPatternCount = 2;
	RollPatter = 0;
	SlotPositionFix = 1;
	ImageBlinkCount = 0;

	WindRenderPtr->Off();
	SlotMouthRenderPtr->Off();
	SlotFrontRenderPtr->Off();

	SlotImageBackRenderPtr->Off();
	SlotImageRenderPtr0->Off();
	SlotImageRenderPtr1->Off();
	SlotImageRenderPtr2->Off();

	ParryCollisionPtr->Off();
}

void Croak::RulletImageBlink(float _DeltaTime)
{
	ImageBlinkTime += _DeltaTime;

	if (0.3f <= ImageBlinkTime)
	{
		ImageBlinkTime = 0.0f;

		if (0 == ImageBlinkCount)
		{
			++ImageBlinkCount;

			SlotImageRenderPtr0->SetScaleToTexture("Slot_flash_TEMP.png");
			SlotImageRenderPtr0->GetTransform()->SetLocalScale({ 60, 150 });

			SlotImageRenderPtr2->SetScaleToTexture("Slot_TEMP.png");
			SlotImageRenderPtr2->GetTransform()->SetLocalScale({ 60, 150 });

			if (true == IsVipor)
			{
				SlotImageRenderPtr0->GetTransform()->SetLocalPosition(SlotViporPosition0);
				SlotImageRenderPtr2->GetTransform()->SetLocalPosition(SlotViporPosition2);
			}
			else if (true == IsBison)
			{
				SlotImageRenderPtr0->GetTransform()->SetLocalPosition(SlotBisonPosition0);
				SlotImageRenderPtr2->GetTransform()->SetLocalPosition(SlotBisonPosition2);
			}
			else if (true == IsTiger)
			{
				SlotImageRenderPtr0->GetTransform()->SetLocalPosition(SlotTigerPosition0);
				SlotImageRenderPtr2->GetTransform()->SetLocalPosition(SlotTigerPosition2);
			}
		}
		else if (1 == ImageBlinkCount)
		{
			++ImageBlinkCount;

			SlotImageRenderPtr0->SetScaleToTexture("Slot_TEMP.png");
			SlotImageRenderPtr0->GetTransform()->SetLocalScale({ 60, 150 });

			SlotImageRenderPtr1->SetScaleToTexture("Slot_flash_TEMP.png");
			SlotImageRenderPtr1->GetTransform()->SetLocalScale({ 60, 150 });

			if (true == IsVipor)
			{
				SlotImageRenderPtr0->GetTransform()->SetLocalPosition(SlotViporPosition0);
				SlotImageRenderPtr1->GetTransform()->SetLocalPosition(SlotViporPosition1);
			}
			else if (true == IsBison)
			{
				SlotImageRenderPtr0->GetTransform()->SetLocalPosition(SlotBisonPosition0);
				SlotImageRenderPtr1->GetTransform()->SetLocalPosition(SlotBisonPosition1);
			}
			else if (true == IsTiger)
			{
				SlotImageRenderPtr0->GetTransform()->SetLocalPosition(SlotTigerPosition0);
				SlotImageRenderPtr1->GetTransform()->SetLocalPosition(SlotTigerPosition1);
			}
		}
		else if (2 == ImageBlinkCount)
		{
			ImageBlinkCount = 0;

			SlotImageRenderPtr1->SetScaleToTexture("Slot_TEMP.png");
			SlotImageRenderPtr1->GetTransform()->SetLocalScale({ 60, 150 });

			SlotImageRenderPtr2->SetScaleToTexture("Slot_flash_TEMP.png");
			SlotImageRenderPtr2->GetTransform()->SetLocalScale({ 60, 150 });

			if (true == IsVipor)
			{
				SlotImageRenderPtr1->GetTransform()->SetLocalPosition(SlotViporPosition1);
				SlotImageRenderPtr2->GetTransform()->SetLocalPosition(SlotViporPosition2);
			}
			else if (true == IsBison)
			{
				SlotImageRenderPtr1->GetTransform()->SetLocalPosition(SlotBisonPosition1);
				SlotImageRenderPtr2->GetTransform()->SetLocalPosition(SlotBisonPosition2);
			}
			else if (true == IsTiger)
			{
				SlotImageRenderPtr1->GetTransform()->SetLocalPosition(SlotTigerPosition1);
				SlotImageRenderPtr2->GetTransform()->SetLocalPosition(SlotTigerPosition2);
			}
		}
	}
}

void Croak::RulletActivate(float _DeltaTime)
{
	if (false == IsRulletActivate)
	{
		return;
	}

	RulletDelayTime += _DeltaTime;

	float MoveDis = 400.0f * _DeltaTime;

	float4 CurPos0 = SlotImageRenderPtr0->GetTransform()->GetLocalPosition();
	float4 CurPos1 = SlotImageRenderPtr1->GetTransform()->GetLocalPosition();
	float4 CurPos2 = SlotImageRenderPtr2->GetTransform()->GetLocalPosition();

	if (0.1f <= RulletDelayTime && false == RulletWave0)
	{
		if (true == IsVipor)
		{
			if (SlotViporPosition0.y >= CurPos0.y)
			{
				RulletWave0 = true;
				SlotImageRenderPtr0->GetTransform()->SetLocalPosition(SlotViporPosition0);
			}
			else
			{
				SlotImageRenderPtr0->GetTransform()->AddLocalPosition({ 0, -MoveDis });
			}
		}
		else if (true == IsBison)
		{
			if (SlotBisonPosition0.y >= CurPos0.y)
			{
				RulletWave0 = true;
				SlotImageRenderPtr0->GetTransform()->SetLocalPosition(SlotBisonPosition0);
			}
			else
			{
				SlotImageRenderPtr0->GetTransform()->AddLocalPosition({ 0, -MoveDis });
			}
		}
		else if (true == IsTiger)
		{
			if (SlotTigerPosition0.y >= CurPos0.y)
			{
				RulletWave0 = true;
				SlotImageRenderPtr0->GetTransform()->SetLocalPosition(SlotTigerPosition0);
			}
			else
			{
				SlotImageRenderPtr0->GetTransform()->AddLocalPosition({ 0, -MoveDis });
			}
		}
		else
		{
			SlotImageRenderPtr0->GetTransform()->AddLocalPosition({ 0, -MoveDis });

			if (LowerLimit.y >= CurPos0.y)
			{
				SlotImageRenderPtr0->GetTransform()->SetLocalPosition(SlotViporPosition0 + float4{ 0, 137 });
			}
		}
	}

	if (0.5f <= RulletDelayTime && false == RulletWave1)
	{
		if (true == IsVipor)
		{
			if (SlotViporPosition1.y >= CurPos1.y)
			{
				RulletWave1 = true;
				SlotImageRenderPtr1->GetTransform()->SetLocalPosition(SlotViporPosition1);
			}
			else
			{
				SlotImageRenderPtr1->GetTransform()->AddLocalPosition({ 0, -MoveDis });
			}
		}
		else if (true == IsBison)
		{
			if (SlotBisonPosition1.y >= CurPos0.y)
			{
				RulletWave1 = true;
				SlotImageRenderPtr1->GetTransform()->SetLocalPosition(SlotBisonPosition1);
			}
			else
			{
				SlotImageRenderPtr1->GetTransform()->AddLocalPosition({ 0, -MoveDis });
			}
		}
		else if (true == IsTiger)
		{
			if (SlotTigerPosition1.y >= CurPos0.y)
			{
				RulletWave1 = true;
				SlotImageRenderPtr1->GetTransform()->SetLocalPosition(SlotTigerPosition1);
			}
			else
			{
				SlotImageRenderPtr1->GetTransform()->AddLocalPosition({ 0, -MoveDis });
			}
		}
		else
		{
			SlotImageRenderPtr1->GetTransform()->AddLocalPosition({ 0, -MoveDis });

			if (LowerLimit.y >= CurPos1.y)
			{
				SlotImageRenderPtr1->GetTransform()->SetLocalPosition(SlotViporPosition1 + float4{ 0, 137 });
			}
		}
	}

	if (1.0f <= RulletDelayTime && false == RulletWave2)
	{
		if (true == IsVipor)
		{
			if (SlotViporPosition2.y >= CurPos2.y)
			{
				RulletWave2 = true;
				SlotImageRenderPtr2->GetTransform()->SetLocalPosition(SlotViporPosition2);
			}
			else
			{
				SlotImageRenderPtr2->GetTransform()->AddLocalPosition({ 0, -MoveDis });
			}
		}
		else if (true == IsBison)
		{
			if (SlotBisonPosition2.y >= CurPos0.y)
			{
				RulletWave2 = true;
				SlotImageRenderPtr2->GetTransform()->SetLocalPosition(SlotBisonPosition2);
			}
			else
			{
				SlotImageRenderPtr2->GetTransform()->AddLocalPosition({ 0, -MoveDis });
			}
		}
		else if (true == IsTiger)
		{
			if (SlotTigerPosition2.y >= CurPos0.y)
			{
				RulletWave2 = true;
				SlotImageRenderPtr2->GetTransform()->SetLocalPosition(SlotTigerPosition2);
			}
			else
			{
				SlotImageRenderPtr2->GetTransform()->AddLocalPosition({ 0, -MoveDis });
			}
		}
		else
		{
			SlotImageRenderPtr2->GetTransform()->AddLocalPosition({ 0, -MoveDis });

			if (LowerLimit.y >= CurPos2.y)
			{
				SlotImageRenderPtr2->GetTransform()->SetLocalPosition(SlotViporPosition2 + float4{ 0, 137 });
			}
		}
	}

	if (true == RulletWave0)
	{
		WaveTime0 += _DeltaTime;
		
		float4 LimitPos = float4::Zero;

		if (true == IsVipor)
		{
			LimitPos = SlotViporPosition0;
		}
		else if (true == IsBison)
		{
			LimitPos = SlotBisonPosition0;
		}
		else if (true == IsTiger)
		{
			LimitPos = SlotTigerPosition0;
		}
		
		LimitPos.y -= sinf(WaveTime0 * 12.f) * (30.0f - (WaveTime0 * 24.0f));

		if (0.0f >= (WaveTime0 * 12.f) * (30.0f - (WaveTime0 * 24.0f)))
		{
			if (true == IsVipor)
			{
				SlotImageRenderPtr0->GetTransform()->SetLocalPosition(SlotViporPosition0);
			}
			else if (true == IsBison)
			{
				SlotImageRenderPtr0->GetTransform()->SetLocalPosition(SlotBisonPosition0);
			}
			else if (true == IsTiger)
			{
				SlotImageRenderPtr0->GetTransform()->SetLocalPosition(SlotTigerPosition0);
			}
		}
		else
		{
			RulletActivateEnd = true;
			SlotImageRenderPtr0->GetTransform()->SetLocalPosition(LimitPos);
		}
	}

	if (true == RulletWave1)
	{
		WaveTime1 += _DeltaTime;

		float4 LimitPos = float4::Zero;

		if (true == IsVipor)
		{
			LimitPos = SlotViporPosition1;
		}
		else if (true == IsBison)
		{
			LimitPos = SlotBisonPosition1;
		}
		else if (true == IsTiger)
		{
			LimitPos = SlotTigerPosition1;
		}

		LimitPos.y -= sinf(WaveTime1 * 12.f) * (30.0f - (WaveTime1 * 24.0f));

		if (0.0f >= (WaveTime1 * 12.f) * (30.0f - (WaveTime1 * 24.0f)))
		{
			if (true == IsVipor)
			{
				SlotImageRenderPtr1->GetTransform()->SetLocalPosition(SlotViporPosition1);
			}
			else if (true == IsBison)
			{
				SlotImageRenderPtr1->GetTransform()->SetLocalPosition(SlotBisonPosition1);
			}
			else if (true == IsTiger)
			{
				SlotImageRenderPtr1->GetTransform()->SetLocalPosition(SlotTigerPosition1);
			}
		}
		else
		{
			SlotImageRenderPtr1->GetTransform()->SetLocalPosition(LimitPos);
		}
	}

	if (true == RulletWave2)
	{
		WaveTime2 += _DeltaTime;

		float4 LimitPos = float4::Zero;

		if (true == IsVipor)
		{
			LimitPos = SlotViporPosition2;
		}
		else if (true == IsBison)
		{
			LimitPos = SlotBisonPosition2;
		}
		else if (true == IsTiger)
		{
			LimitPos = SlotTigerPosition2;
		}

		LimitPos.y -= sinf(WaveTime2 * 12.f) * (30.0f - (WaveTime2 * 24.0f));

		if (0.0f >= (WaveTime2 * 12.f) * (30.0f - (WaveTime2 * 24.0f)))
		{
			if (true == IsVipor)
			{
				SlotImageRenderPtr2->GetTransform()->SetLocalPosition(SlotViporPosition2);
			}
			else if (true == IsBison)
			{
				SlotImageRenderPtr2->GetTransform()->SetLocalPosition(SlotBisonPosition2);
			}
			else if (true == IsTiger)
			{
				SlotImageRenderPtr2->GetTransform()->SetLocalPosition(SlotTigerPosition2);
			}
		}
		else
		{
			SlotImageRenderPtr2->GetTransform()->SetLocalPosition(LimitPos);
		}
	}
}

void Croak::CoinAttack(float _DeltaTime)
{
	if (true == IsRullet)
	{
		return;
	}

	CoinAttackTime += _DeltaTime;

	if (1.2f <= CoinAttackTime && 3 > CreateCoinCount)
	{
		CoinAttackTime = 0.0f;
		SlotMouthRenderPtr->On();
	}

	if (2.7f <= CoinAttackTime)
	{
		CreateCoinCount = 0;
	}

	if (5 == SlotMouthRenderPtr->GetCurrentFrame())
	{
		++CreateCoinCount;
		CreateCoinProjectile();
		SlotMouthRenderPtr->FindAnimation("Slot_CoinMouth")->CurFrame = 0;
		SlotMouthRenderPtr->Off();
	}
}

void Croak::CollisionSetting()
{
	BodyCollisionRenderPtr->GetTransform()->SetLocalScale(BodyCollisionPtr->GetTransform()->GetLocalScale());
	BodyCollisionRenderPtr->GetTransform()->SetLocalPosition(BodyCollisionPtr->GetTransform()->GetLocalPosition());

	EXCollisionRenderPtr->GetTransform()->SetLocalScale(EXCollisionPtr->GetTransform()->GetLocalScale());
	EXCollisionRenderPtr->GetTransform()->SetLocalPosition(EXCollisionPtr->GetTransform()->GetLocalPosition());

	PlusBodyCollisionRenderPtr->GetTransform()->SetLocalScale(PlusBodyCollisionPtr->GetTransform()->GetLocalScale());
	PlusBodyCollisionRenderPtr->GetTransform()->SetLocalPosition(PlusBodyCollisionPtr->GetTransform()->GetLocalPosition());

	PlusEXCollisionRenderPtr->GetTransform()->SetLocalScale(PlusEXCollisionPtr->GetTransform()->GetLocalScale());
	PlusEXCollisionRenderPtr->GetTransform()->SetLocalPosition(PlusEXCollisionPtr->GetTransform()->GetLocalPosition());
}

void Croak::HitBlink(float _DeltaTime)
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
		SlotFrontRenderPtr->ColorOptionValue.MulColor += BlinkMulColor;
	}

	if (BlinkTime >= 0.1f)
	{
		BlinkCount = 1;
		BlinkTime = 0.0f;
		IsBlink = false;

		RenderPtr->ColorOptionValue.MulColor = OriginMulColor;
		SlotFrontRenderPtr->ColorOptionValue.MulColor = OriginMulColor;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                    CollisionCheck                    /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Croak::CollisionCheck()
{
	if (nullptr != ParryCollisionPtr->Collision(static_cast<int>(CollisionOrder::PlayerParry), ColType::AABBBOX2D, ColType::SPHERE2D))
	{
		ParryCollisionPtr->Off();
		IsArmParry = true;
	}
	else
	{
		IsArmParry = false;
	}

	/////////////// Normal
	if (nullptr != BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Peashooter), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& HP > 0.0f)
	{
		GameEngineActor* Projectile = BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Peashooter), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Peashooter*>(Projectile)->SetPeashooterDeath();

		if (false == SlotInvincibility)
		{
			dynamic_cast<Peashooter*>(Projectile)->SetHitture();

			HP -= 1.0f;

			if (0 >= HP)
			{
				HP = 0.0f;
				IsStageEnd = true;
			}

			IsBlink = true;
		}
	}

	if (nullptr != BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Spread), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& HP > 0.0f)
	{
		GameEngineActor* Projectile = BodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Spread), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Spread*>(Projectile)->SetSpreadDeath();

		if (false == SlotInvincibility)
		{
			dynamic_cast<Spread*>(Projectile)->SetHitture();

			HP -= 0.4f;

			if (0 >= HP)
			{
				HP = 0.0f;
				IsStageEnd = true;
			}

			IsBlink = true;
		}
	}

	if (nullptr != PlusBodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Peashooter), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& HP > 0.0f)
	{
		GameEngineActor* Projectile = PlusBodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Peashooter), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Peashooter*>(Projectile)->SetPeashooterDeath();

		if (false == SlotInvincibility)
		{
			dynamic_cast<Peashooter*>(Projectile)->SetHitture();

			HP -= 1.0f;

			if (0 >= HP)
			{
				HP = 0.0f;
				IsStageEnd = true;
			}

			IsBlink = true;
		}
	}

	if (nullptr != PlusBodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Spread), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& HP > 0.0f)
	{
		GameEngineActor* Projectile = PlusBodyCollisionPtr->Collision(static_cast<int>(CollisionOrder::Spread), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Spread*>(Projectile)->SetSpreadDeath();
		
		if (false == SlotInvincibility)
		{
			dynamic_cast<Spread*>(Projectile)->SetHitture();

			HP -= 0.4f;

			if (0 >= HP)
			{
				HP = 0.0f;
				IsStageEnd = true;
			}

			IsBlink = true;
		}
	}

	if (true == SlotInvincibility)
	{
		return;
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

	if (nullptr != PlusEXCollisionPtr->Collision(static_cast<int>(CollisionOrder::PeashooterEX), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& HP > 0.0f)
	{
		GameEngineActor* Projectile = PlusEXCollisionPtr->Collision(static_cast<int>(CollisionOrder::PeashooterEX), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
		dynamic_cast<Peashooter_EX*>(Projectile)->SetHitture();
		HP -= 5.0f;

		if (0 >= HP)
		{
			HP = 0.0f;
			IsStageEnd = true;
		}

		IsBlink = true;
	}

	if (nullptr != PlusEXCollisionPtr->Collision(static_cast<int>(CollisionOrder::SpreadEX), ColType::AABBBOX2D, ColType::SPHERE2D)
		&& HP > 0.0f)
	{
		GameEngineActor* Projectile = PlusEXCollisionPtr->Collision(static_cast<int>(CollisionOrder::SpreadEX), ColType::AABBBOX2D, ColType::SPHERE2D)->GetActor();
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     CreateActor                      ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Croak::CreateFirefly()
{
	std::shared_ptr<Croak_Firefly> Mob = GetLevel()->CreateActor<Croak_Firefly>();
	float4 StartPosition = GetTransform()->GetLocalPosition();
	float4 MobPosition = StartPosition + float4{-250, 70, 1};

	if (true == IsDebugRender)
	{
		Mob->SetCollisionRenderOn();
	}
	else
	{
		Mob->SetCollisionRenderOff();
	}

	Mob->SetStartPosition(MobPosition);

	if (1 == CreateMobCount)
	{
		Mob->SetIsFirstSpawn();
	}
	else if (2 == CreateMobCount)
	{
		Mob->SetIsSecondSpawn();
	}
	else if (3 == CreateMobCount)
	{
		Mob->SetIsThirdSpawn();
	}
	else if (4 == CreateMobCount)
	{
		Mob->SetIsFourthSpawn();
	}
	else
	{
		MsgAssert("FireFly 스폰이 뭔가 잘못됨");
		return;
	}
}

void Croak::CreateFrontDust()
{
	std::shared_ptr<Slot_FrontDust> Dust = GetLevel()->CreateActor<Slot_FrontDust>();
	float4 StartPosition = GetTransform()->GetLocalPosition();
	float4 DustPosition = StartPosition + float4{ 0, -250, 1 };

	Dust->SetStartPosition(DustPosition);
}

void Croak::CreateCoinProjectile()
{
	std::shared_ptr<CoinAttack_Projectile> Projectile = GetLevel()->CreateActor<CoinAttack_Projectile>();
	float4 StartPosition = SlotMouthRenderPtr->GetTransform()->GetWorldPosition();
	float4 ProjectilePosition = StartPosition + float4{ 0, 0, -1 };

	if (true == IsDebugRender)
	{
		Projectile->SetCollisionRenderOn();
	}
	else
	{
		Projectile->SetCollisionRenderOff();
	}

	Projectile->SetStartPosition(ProjectilePosition);
}

void Croak::CreatePlatform_Vipor()
{
	std::shared_ptr<Platform_Vipor> Platform = GetLevel()->CreateActor<Platform_Vipor>();
	float4 StartPosition = GetTransform()->GetLocalPosition();
	float4 PlatformPosition = StartPosition + float4{ 0, -180 };

	if (true == IsDebugRender)
	{
		Platform->SetCollisionRenderOn();
	}
	else
	{
		Platform->SetCollisionRenderOff();
	}

	Platform->SetColMap(Player::MainPlayer->GetColMap(), PixelCollision::Coordinate::Custom);
	Platform->SetStartPosition(PlatformPosition);
}

void Croak::CreatePlatform_Bison()
{

}

void Croak::CreatePlatform_Tiger()
{

}

void Croak::CreateDeathExplosion(float _DeltaTime)
{
	std::shared_ptr<DeathExplosion> Explosion = GetLevel()->CreateActor<DeathExplosion>();
	float4 StartPosition = SlotMouthRenderPtr->GetTransform()->GetWorldPosition();

	int RandX = GameEngineRandom::MainRandom.RandomInt(-230, 230); // -200 ~ 200
	int RandY = GameEngineRandom::MainRandom.RandomInt(-350, 130); // -350 ~ 100

	float4 ExplosionPosition = StartPosition + float4{ static_cast<float>(RandX), static_cast<float>(RandY), -1 };

	Explosion->SetStartPosition(ExplosionPosition);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                     InitSetting                     ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Croak::ActorInitSetting()
{
	if (nullptr == GameEngineSprite::Find("Croaks_Intro"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Croaks");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_Idle").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_CreateMob_Start").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_CreateMob_Start_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_CreateMob_Start_Out").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_CreateMob").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_CreateMob_End").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_Fan_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_Fan_LoopA").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_Fan_LoopB").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_Fan_Outro").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_Fan_Wind_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croaks_Fan_Wind_Loop").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Slot_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Croaks");
		NewDir.Move("Croaks_SlotMachine");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_Morph_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_Morph_Intro_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_Morph_Outro").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_InitialOpen").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_ArmMove_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_ArmMove_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_ArmMove_Outro").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_Attack_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_Attack_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_Attack_Outro").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_Death_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_Death_Loop").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Firefly_Death"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Croaks");
		NewDir.Move("Croaks_Firefly");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Firefly_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Firefly_Down").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Firefly_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Firefly_Left").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Firefly_Up").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Slot_CoinMouth"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Croaks");
		NewDir.Move("Croaks_SlotMachine");
		NewDir.Move("Slot_Coin");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_CoinMouth").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Projectile").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Slot_Dust_Front"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Croaks");
		NewDir.Move("Croaks_SlotMachine");
		NewDir.Move("Slot_Dust");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Slot_Dust_Front").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("Slot_TEMP.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Croaks");
		NewDir.Move("Croaks_SlotMachine");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Slot_TEMP.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Slot_flash_TEMP.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Slot_ImageBack.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("SlotMachine_Attack_Front_001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Croaks");
		NewDir.Move("Croaks_SlotMachine");
		NewDir.Move("Attack_Front");

		GameEngineTexture::Load(NewDir.GetPlusFileName("SlotMachine_Attack_Front_001.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("SlotMachine_Attack_Front_002.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("SlotMachine_Attack_Front_003.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("SlotMachine_Attack_Front_004.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("SlotMachine_Attack_Front_005.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("SlotMachine_Attack_Front_006.png").GetFullPath());
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

	if (nullptr == GameEngineSprite::Find("Snake_Platform"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Croaks");
		NewDir.Move("Croaks_SlotMachine");
		NewDir.Move("Attack_Platforms");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Snake_Platform").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Tiger_Ball").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Tiger_Front").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Tiger_Platform").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bison_Flame_Large_Intro").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bison_Flame_Large_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bison_Flame_Small_Loop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bison_Front").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bison_Platform").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "Croaks_Intro", .SpriteName = "Croaks_Intro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Croaks_Idle", .SpriteName = "Croaks_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });

		RenderPtr->CreateAnimation({ .AnimationName = "Croaks_CreateMob_Start", .SpriteName = "Croaks_CreateMob_Start", .FrameInter = 0.065f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Croaks_CreateMob_Start_Loop", .SpriteName = "Croaks_CreateMob_Start_Loop", .FrameInter = 0.065f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Croaks_CreateMob_Start_Out", .SpriteName = "Croaks_CreateMob_Start_Out", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Croaks_CreateMob", .SpriteName = "Croaks_CreateMob", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Croaks_CreateMob_End", .SpriteName = "Croaks_CreateMob_End", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

		RenderPtr->CreateAnimation({ .AnimationName = "Croaks_Fan_Intro", .SpriteName = "Croaks_Fan_Intro", .FrameInter = 0.04f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Croaks_Fan_LoopA", .SpriteName = "Croaks_Fan_LoopA", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Croaks_Fan_LoopB", .SpriteName = "Croaks_Fan_LoopB", .FrameInter = 0.04f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Croaks_Fan_Outro", .SpriteName = "Croaks_Fan_Outro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

		RenderPtr->CreateAnimation({ .AnimationName = "Slot_Morph_Intro", .SpriteName = "Slot_Morph_Intro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Slot_Morph_Intro_Loop", .SpriteName = "Slot_Morph_Intro_Loop", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Slot_Morph_Outro", .SpriteName = "Slot_Morph_Outro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Slot_InitialOpen", .SpriteName = "Slot_InitialOpen", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Slot_Idle", .SpriteName = "Slot_Idle", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Slot_Death_Intro", .SpriteName = "Slot_Death_Intro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Slot_Death_Loop", .SpriteName = "Slot_Death_Loop", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Slot_ArmMove_Intro", .SpriteName = "Slot_ArmMove_Intro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Slot_ArmMove_Loop", .SpriteName = "Slot_ArmMove_Loop", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Slot_ArmMove_Outro", .SpriteName = "Slot_ArmMove_Outro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Slot_Attack_Intro", .SpriteName = "Slot_Attack_Intro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Slot_Attack_Loop", .SpriteName = "Slot_Attack_Loop", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Slot_Attack_Outro", .SpriteName = "Slot_Attack_Outro", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("Croaks_Idle");
	}

	if (nullptr == BodyCollisionPtr)
	{
		BodyCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Monster));
		BodyCollisionPtr->SetColType(ColType::AABBBOX2D);
		BodyCollisionPtr->GetTransform()->SetLocalScale({ 150, 480, 1 });
		BodyCollisionPtr->GetTransform()->SetLocalPosition({ 20, -80 });
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
		EXCollisionPtr->GetTransform()->SetLocalScale({ 150, 480, 1 });
		EXCollisionPtr->GetTransform()->SetLocalPosition({ 20, -80 });
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

	if (nullptr == PlusBodyCollisionPtr)
	{
		PlusBodyCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Monster));
		PlusBodyCollisionPtr->SetColType(ColType::AABBBOX2D);
		PlusBodyCollisionPtr->GetTransform()->SetLocalScale({ 200, 200, 1 });
		PlusBodyCollisionPtr->GetTransform()->SetLocalPosition({ -8, -220 });
	}

	if (nullptr == PlusBodyCollisionRenderPtr)
	{
		PlusBodyCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		PlusBodyCollisionRenderPtr->GetTransform()->SetLocalScale(PlusBodyCollisionPtr->GetTransform()->GetLocalScale());
		PlusBodyCollisionRenderPtr->GetTransform()->SetLocalPosition(PlusBodyCollisionPtr->GetTransform()->GetLocalPosition());
		PlusBodyCollisionRenderPtr->SetTexture("GreenLine.png");
		PlusBodyCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
		PlusBodyCollisionRenderPtr->Off();
	}

	if (nullptr == PlusEXCollisionPtr)
	{
		PlusEXCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Monster));
		PlusEXCollisionPtr->SetColType(ColType::AABBBOX2D);
		PlusEXCollisionPtr->GetTransform()->SetLocalScale({ 200, 200, 1 });
		PlusEXCollisionPtr->GetTransform()->SetLocalPosition({ -8, -220 });
	}

	if (nullptr == PlusEXCollisionRenderPtr)
	{
		PlusEXCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		PlusEXCollisionRenderPtr->GetTransform()->SetLocalScale(PlusEXCollisionPtr->GetTransform()->GetLocalScale());
		PlusEXCollisionRenderPtr->GetTransform()->SetLocalPosition(PlusEXCollisionPtr->GetTransform()->GetLocalPosition());
		PlusEXCollisionRenderPtr->SetTexture("RedLine.png");
		PlusEXCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
		PlusEXCollisionRenderPtr->Off();
	}

	if (nullptr == WindRenderPtr)
	{
		WindRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		WindRenderPtr->CreateAnimation({ .AnimationName = "Croaks_Fan_Wind_Intro", .SpriteName = "Croaks_Fan_Wind_Intro", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
		WindRenderPtr->CreateAnimation({ .AnimationName = "Croaks_Fan_Wind_Loop", .SpriteName = "Croaks_Fan_Wind_Loop", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		WindRenderPtr->ChangeAnimation("Croaks_Fan_Wind_Intro");
		WindRenderPtr->GetTransform()->AddLocalPosition({-400, -10});
		WindRenderPtr->Off();
	}

	if (nullptr == SlotMouthRenderPtr)
	{
		SlotMouthRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		SlotMouthRenderPtr->CreateAnimation({ .AnimationName = "Slot_CoinMouth", .SpriteName = "Slot_CoinMouth", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		SlotMouthRenderPtr->ChangeAnimation("Slot_CoinMouth");
		SlotMouthRenderPtr->GetTransform()->AddLocalPosition({ -5, 65 });
		SlotMouthRenderPtr->Off();
	}

	// basic = 66, 301 // idle = 66, 200

	if (nullptr == SlotImageRenderPtr0)
	{
		SlotImageRenderPtr0 = CreateComponent<GameEngineSpriteRenderer>();
		SlotImageRenderPtr0->SetScaleToTexture("Slot_TEMP.png");
		SlotImageRenderPtr0->GetTransform()->SetLocalScale({ 60, 150 });
		SlotImageRenderPtr0->GetTransform()->AddLocalPosition({ -65, -80, 1 });

		SlotViporPosition0 = SlotImageRenderPtr0->GetTransform()->GetLocalPosition();
		SlotBisonPosition0 = SlotViporPosition0 + float4{ 0, 51 };
		SlotTigerPosition0 = SlotViporPosition0 + float4{ 0, 102 };

		SlotImageRenderPtr0->Off();
	}

	if (nullptr == SlotImageRenderPtr1)
	{
		SlotImageRenderPtr1 = CreateComponent<GameEngineSpriteRenderer>();
		SlotImageRenderPtr1->SetScaleToTexture("Slot_TEMP.png");
		SlotImageRenderPtr1->GetTransform()->SetLocalScale({ 60, 150 });
		SlotImageRenderPtr1->GetTransform()->AddLocalPosition({ -12, -80, 1 });

		SlotViporPosition1 = SlotImageRenderPtr1->GetTransform()->GetLocalPosition();
		SlotBisonPosition1 = SlotViporPosition1 + float4{ 0, 51 };
		SlotTigerPosition1 = SlotViporPosition1 + float4{ 0, 102 };

		SlotImageRenderPtr1->Off();
	}

	if (nullptr == SlotImageRenderPtr2)
	{
		SlotImageRenderPtr2 = CreateComponent<GameEngineSpriteRenderer>();
		SlotImageRenderPtr2->SetScaleToTexture("Slot_TEMP.png");
		SlotImageRenderPtr2->GetTransform()->SetLocalScale({ 60, 150 });
		SlotImageRenderPtr2->GetTransform()->AddLocalPosition({ 43, -80, 1 });

		SlotViporPosition2 = SlotImageRenderPtr2->GetTransform()->GetLocalPosition();
		SlotBisonPosition2 = SlotViporPosition2 + float4{ 0, 51 };
		SlotTigerPosition2 = SlotViporPosition2 + float4{ 0, 102 };

		SlotImageRenderPtr2->Off();
	}

	if (nullptr == SlotImageBackRenderPtr)
	{
		SlotImageBackRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		SlotImageBackRenderPtr->SetTexture("Slot_ImageBack.png");
		SlotImageBackRenderPtr->GetTransform()->SetLocalScale({ 200, 100 });
		SlotImageBackRenderPtr->GetTransform()->AddLocalPosition({ 0, -20, 2 });
		SlotImageBackRenderPtr->Off();
	}

	if (nullptr == ParryCollisionPtr)
	{
		ParryCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::ParrySpot));
		ParryCollisionPtr->SetColType(ColType::SPHERE2D);
		ParryCollisionPtr->GetTransform()->SetLocalScale({ 130, 130, 1 });
		ParryCollisionPtr->GetTransform()->SetLocalPosition({ -350, -50 });
		ParryCollisionPtr->Off();
	}

	if (nullptr == ParryCollisionRenderPtr)
	{
		ParryCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ParryCollisionRenderPtr->SetTexture("GreenLine.png");
		ParryCollisionRenderPtr->GetTransform()->SetLocalScale(ParryCollisionPtr->GetTransform()->GetLocalScale());
		ParryCollisionRenderPtr->GetTransform()->SetLocalPosition(ParryCollisionPtr->GetTransform()->GetLocalPosition());
		ParryCollisionRenderPtr->Off();
	}

	if (nullptr == SlotFrontRenderPtr)
	{
		SlotFrontRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		SlotFrontRenderPtr->SetScaleToTexture("SlotMachine_Attack_Front_001.png");
		SlotFrontRenderPtr->GetTransform()->AddLocalPosition({ 0, 0, -3 });
		SlotFrontRenderPtr->Off();
	}
}

// 투명 블링크 // mulcolor 자료형 float
//void Croak::HitBlink(float _DeltaTime)
//{
//	if (false == IsBlink)
//	{
//		return;
//	}
//
//	BlinkTime += _DeltaTime;
//
//	if (BlinkCount == 1)
//	{
//		BlinkCount = 0;
//
//		OriginMulColor = RenderPtr->ColorOptionValue.MulColor.a;
//		BlinkMulColor = 0.8f;
//		RenderPtr->ColorOptionValue.MulColor.a = BlinkMulColor;
//		SlotFrontRenderPtr->ColorOptionValue.MulColor.a = 0.0f;
//	}
//
//	if (BlinkTime >= 0.1f)
//	{
//		BlinkCount = 1;
//		BlinkTime = 0.0f;
//		IsBlink = false;
//
//		RenderPtr->ColorOptionValue.MulColor.a = OriginMulColor;
//		SlotFrontRenderPtr->ColorOptionValue.MulColor.a = OriginMulColor;
//	}
//}
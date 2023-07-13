#include "PrecompileHeader.h"
#include "Object_FireWork.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"

Object_FireWork::Object_FireWork() 
{
}

Object_FireWork::~Object_FireWork() 
{
}

void Object_FireWork::SelectFireWork(FireWorkType _Type)
{
	TypeValue = _Type;

	switch (_Type)
	{
	case FireWorkType::Leader:
		RenderPtr->ChangeAnimation("Object_Firework_Leader");

		BodyCollisionPtr->GetTransform()->SetLocalScale({ 80, 120, -50 });
		BodyCollisionPtr->GetTransform()->SetLocalPosition({ -10, -20 });
		break;
	case FireWorkType::Work_A:
		RenderPtr->ChangeAnimation("Object_Firework_A_Move");

		BodyCollisionPtr->GetTransform()->SetLocalScale({ 80, 80, -50 });
		BodyCollisionPtr->GetTransform()->SetLocalPosition({ 0, -20 });
		break;
	case FireWorkType::Work_B:
		RenderPtr->ChangeAnimation("Object_Firework_B_Move");

		BodyCollisionPtr->GetTransform()->SetLocalScale({ 80, 80, -50 });
		BodyCollisionPtr->GetTransform()->SetLocalPosition({ 0, -20 });
		break;
	case FireWorkType::Work_C:
		RenderPtr->ChangeAnimation("Object_Firework_C_Move");

		BodyCollisionPtr->GetTransform()->SetLocalScale({ 80, 80, -50 });
		BodyCollisionPtr->GetTransform()->SetLocalPosition({ 0, -20 });
		break;
	default:
		break;
	}

	BodyCollisionRenderPtr->GetTransform()->SetLocalScale(BodyCollisionPtr->GetTransform()->GetLocalScale());
	BodyCollisionRenderPtr->GetTransform()->SetLocalPosition(BodyCollisionPtr->GetTransform()->GetLocalPosition());
}

void Object_FireWork::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Object_Firework_Leader", .SpriteName = "Object_Firework_Leader", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Object_Firework_A_Move", .SpriteName = "Object_Firework_A_Move", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Object_Firework_B_Move", .SpriteName = "Object_Firework_B_Move", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Object_Firework_C_Move", .SpriteName = "Object_Firework_C_Move", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Object_Firework_C_Jump_Intro", .SpriteName = "Object_Firework_C_Jump_Intro", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Object_Firework_C_Jump_Inter", .SpriteName = "Object_Firework_C_Jump_Inter", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Object_Firework_C_Jump_Loop", .SpriteName = "Object_Firework_C_Jump_Loop", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("Object_Firework_Leader");
	}

	if (nullptr == BodyCollisionPtr)
	{
		BodyCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
		BodyCollisionPtr->SetColType(ColType::AABBBOX2D);
		BodyCollisionPtr->GetTransform()->SetLocalScale({ 80, 120, -50 });
		BodyCollisionPtr->GetTransform()->SetLocalPosition({ -10, -20 });
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

	ChangeState(FireWorkState::Move);
}

void Object_FireWork::Update(float _DeltaTime)
{
	UpdateState(_DeltaTime);
	DeathCheck();
}

void Object_FireWork::DeathCheck()
{
	float4 CurPos = GetTransform()->GetLocalPosition();

	if (InitPosition.x + 1200.0f <= CurPos.x)
	{
		Death();
	}

	if (InitPosition.y - 300.0f >= CurPos.y)
	{
		Death();
	}
}

void Object_FireWork::ChangeState(FireWorkState _StateValue)
{
	FireWorkState NextState = _StateValue;
	FireWorkState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case FireWorkState::Move:
		MoveStart();
		break;
	case FireWorkState::Jump_Intro:
		Jump_IntroStart();
		break;
	case FireWorkState::Jump_Inter:
		Jump_InterStart();
		break;
	case FireWorkState::Jump:
		JumpStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case FireWorkState::Move:
		MoveEnd();
		break;
	case FireWorkState::Jump_Intro:
		Jump_IntroEnd();
		break;
	case FireWorkState::Jump_Inter:
		Jump_InterEnd();
		break;
	case FireWorkState::Jump:
		JumpEnd();
		break;
	default:
		break;
	}
}
void Object_FireWork::UpdateState(float _DeltaTime) 
{
	switch (StateValue)
	{
	case FireWorkState::Move:
		MoveUpdate(_DeltaTime);
		break;
	case FireWorkState::Jump_Intro:
		Jump_IntroUpdate(_DeltaTime);
		break;
	case FireWorkState::Jump_Inter:
		Jump_InterUpdate(_DeltaTime);
		break;
	case FireWorkState::Jump:
		JumpUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Object_FireWork::MoveStart()
{

}
void Object_FireWork::MoveUpdate(float _DeltaTime)
{
	float MoveDis = MoveSpeed * _DeltaTime;

	GetTransform()->AddLocalPosition({ MoveDis , 0 });

	if (FireWorkType::Work_C == TypeValue)
	{
		float4 CurPos = GetTransform()->GetWorldPosition();

		if (700.0f <= CurPos.x)
		{
			ChangeState(FireWorkState::Jump_Intro);
			return;
		}
	}
}
void Object_FireWork::MoveEnd()
{

}

void Object_FireWork::Jump_IntroStart() 
{
	float PlayerPosition = Player::MainPlayer->GetTransform()->GetWorldPosition().x;
	float FireWorkPosition = GetTransform()->GetWorldPosition().x;

	float DirectValue = FireWorkPosition - PlayerPosition;

	if (0.0f >= DirectValue)
	{
		Directbool = true;  // ¿À
	}
	else
	{
		Directbool = false; // ¿Þ
	}

	if (false == Directbool)
	{
		GetTransform()->SetLocalNegativeScaleX();
	}
	else
	{
		GetTransform()->SetLocalPositiveScaleX();
	}

	RenderPtr->ChangeAnimation("Object_Firework_C_Jump_Intro");
}
void Object_FireWork::Jump_IntroUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(FireWorkState::Jump_Inter);
		return;
	}
}
void Object_FireWork::Jump_IntroEnd()
{

}

void Object_FireWork::Jump_InterStart()
{
	int RandC = GameEngineRandom::MainRandom.RandomInt(0, 2);
	int RandC2 = GameEngineRandom::MainRandom.RandomInt(0, 2);

	if (0 == RandC)
	{
		MoveDirect.y += 1400.0f;
	}
	else if (1 == RandC)
	{
		MoveDirect.y += 1320.0f;
	}
	else if (2 == RandC)
	{
		MoveDirect.y += 1240.0f;
	}

	if (0 == RandC2)
	{
		MoveSpeed = 500.0f;
	}
	else if (1 == RandC2)
	{
		MoveSpeed = 450.0f;
	}
	else if (2 == RandC2)
	{
		MoveSpeed = 400.0f;
	}
}
void Object_FireWork::Jump_InterUpdate(float _DeltaTime)
{
	float MoveDis = MoveSpeed * _DeltaTime;

	if (false == Directbool)
	{
		GetTransform()->AddLocalPosition({ -MoveDis , 0 });
	}
	else
	{
		GetTransform()->AddLocalPosition({ MoveDis , 0 });
	}

	if (MoveDirect.y >= -1600.0f)
	{
		MoveDirect.y += -2500.0f * _DeltaTime;
	}

	GetTransform()->AddLocalPosition(MoveDirect * _DeltaTime);

	if (true == RenderPtr->IsAnimationEnd())
	{
		ChangeState(FireWorkState::Jump);
		return;
	}
}
void Object_FireWork::Jump_InterEnd()
{

}

void Object_FireWork::JumpStart()
{
	RenderPtr->ChangeAnimation("Object_Firework_C_Jump_Loop");
}
void Object_FireWork::JumpUpdate(float _DeltaTime)
{
	float MoveDis = MoveSpeed * _DeltaTime;

	if (false == Directbool)
	{
		GetTransform()->AddLocalPosition({ -MoveDis , 0 });
	}
	else
	{
		GetTransform()->AddLocalPosition({ MoveDis , 0 });
	}

	if (MoveDirect.y >= -1600.0f)
	{
		MoveDirect.y += -2500.0f * _DeltaTime;
	}

	GetTransform()->AddLocalPosition(MoveDirect * _DeltaTime);
}
void Object_FireWork::JumpEnd()
{

}
#include "PrecompileHeader.h"
#include "ElderKettle.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"

ElderKettle::ElderKettle() 
{
}

ElderKettle::~ElderKettle() 
{
}

void ElderKettle::Start()
{
	if (nullptr == GameEngineTexture::Find("Kettle_Idle.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("ElderKettle");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Kettle_Idle.png").GetFullPath(), 7, 1);
	}

	if (RenderPtr == nullptr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ "Kettle_Idle", "Kettle_Idle.png", 0, 6, 0.1f, true, true });
		RenderPtr->ChangeAnimation("Kettle_Idle");
	}

	if (nullptr == CollisionRenderPtr)
	{
		CollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr == CollisionPtr)
	{
		CollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::ElderKettle));
	}

	if (nullptr != CollisionPtr)
	{
		CollisionPtr->GetTransform()->SetLocalScale({ 120, 200, 1 });
		CollisionPtr->GetTransform()->SetLocalPosition({ -20, 100, -17 });
	}

	if (nullptr != CollisionRenderPtr)
	{
		CollisionRenderPtr->SetTexture("GreenLine.png");
		CollisionRenderPtr->GetTransform()->SetLocalScale(CollisionPtr->GetTransform()->GetLocalScale());
		CollisionRenderPtr->GetTransform()->SetLocalPosition(CollisionPtr->GetTransform()->GetLocalPosition());
	}

	if (nullptr == EnterMessageRenderPtr)
	{
		EnterMessageRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		EnterMessageRenderPtr->SetScaleToTexture("EnterMessage.png");
		EnterMessageRenderMaxScale = EnterMessageRenderPtr->GetTransform()->GetLocalScale();
		EnterMessageRenderPtr->GetTransform()->SetLocalScale(float4{ 1, 1, 1 });
		EnterMessageRenderMinScale = EnterMessageRenderPtr->GetTransform()->GetLocalScale();
		EnterMessageRenderPtr->GetTransform()->SetLocalPosition(RenderPtr->GetTransform()->GetLocalPosition() + float4{ 0, 300, -20 });
		EnterMessageRenderPtr->Off();
	}
}

void ElderKettle::Update(float _DeltaTime)
{
	CollisionCheck(_DeltaTime);
	UpdateState(_DeltaTime);
}

void ElderKettle::CollisionCheck(float _DeltaTime)
{
	if (nullptr != CollisionPtr->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		EnterMessageScaleUp(_DeltaTime);
	}
	else
	{
		EnterMessageScaleDown(_DeltaTime);
	}
}

void ElderKettle::EnterMessageScaleUp(float _DeltaTime)
{
	ScaleCheckStart = true;
	ScaleMinTime = 0.0f;
	EnterMessageRenderPtr->On();
	ScaleCount = 1;

	ScaleMaxTime += _DeltaTime;

	float4 Scale = float4::LerpClamp(EnterMessageRenderMinScale, EnterMessageRenderMaxScale, ScaleMaxTime * 5.5f);

	EnterMessageRenderPtr->GetTransform()->SetLocalScale(Scale);
}

void ElderKettle::EnterMessageScaleDown(float _DeltaTime)
{
	if (false == ScaleCheckStart)
	{
		return;
	}

	ScaleMaxTime = 0.0f;
	EnterMessageRenderPtr->On();

	ScaleMinTime += _DeltaTime;

	if (1 == ScaleCount)
	{
		ScaleCount = 0;
		EnterMessageRenderDelayScale = EnterMessageRenderMaxScale * 1.35f;
	}

	float4 Scale = float4::LerpClamp(EnterMessageRenderDelayScale, EnterMessageRenderMinScale, ScaleMinTime * 5.f);

	EnterMessageRenderPtr->GetTransform()->SetLocalScale(Scale);

	if (EnterMessageRenderMinScale == EnterMessageRenderPtr->GetTransform()->GetLocalScale())
	{
		EnterMessageRenderPtr->Off();
	}
}

void ElderKettle::ChangeState(KettleState _StateValue)
{
	KettleState NextState = _StateValue;
	KettleState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case KettleState::Idle:
		IdleStart();
		break;
	}
}

void ElderKettle::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case KettleState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	}
}

void ElderKettle::IdleStart()
{

}
void ElderKettle::IdleUpdate(float _DeltaTime)
{

}
void ElderKettle::IdleEnd()
{

}
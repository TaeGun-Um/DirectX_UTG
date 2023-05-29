#include "PrecompileHeader.h"
#include "PortalDoor.h"

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "WaitingRoomLevel.h"
#include "TutorialLevel.h"
#include "OverworldLevel.h"
#include "FrogLevel.h"
#include "DragonLevel.h"
#include "MouseLevel.h"

#include "Player.h"

PortalDoor::PortalDoor() 
{
}

PortalDoor::~PortalDoor() 
{
}

void PortalDoor::Start()
{
	if (nullptr == RenderCollisionPtr)
	{
		RenderCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Portal));
		RenderCollisionPtr->GetTransform()->SetLocalScale({ 170, 150, 1 });
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->GetTransform()->SetLocalScale(RenderCollisionPtr->GetTransform()->GetLocalScale());
		RenderPtr->GetTransform()->SetLocalPosition(RenderCollisionPtr->GetTransform()->GetLocalPosition());
		RenderPtr->SetTexture("GreenBox.png");
		RenderPtr->ColorOptionValue.MulColor.a = 0.6f;
	}

	if (nullptr == EnterMessageRenderPtr)
	{
		EnterMessageRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		EnterMessageRenderPtr->SetScaleToTexture("EnterMessage.png");
		EnterMessageRenderMaxScale = EnterMessageRenderPtr->GetTransform()->GetLocalScale();
		EnterMessageRenderPtr->GetTransform()->SetLocalScale(float4{1, 1, 1});
		EnterMessageRenderMinScale = EnterMessageRenderPtr->GetTransform()->GetLocalScale();
		EnterMessageRenderPtr->GetTransform()->SetLocalPosition(RenderCollisionPtr->GetTransform()->GetLocalPosition() + float4{0, 250, 0});
		EnterMessageRenderPtr->Off();
	}
}

void PortalDoor::Update(float _DeltaTime)
{
	if (true == IsDebugRender)
	{
		RenderPtr->On();
	}
	else
	{
		RenderPtr->Off();
	}

	CollisionCheck(_DeltaTime);

	if (false == Player::MainPlayer->GetPlayerPortalAble())
	{
		return;
	}

	if (true == Player::MainPlayer->GetPlayerPortaling()
		&& Player::MainPlayer->GetPlayerMainRenderPtr()->FindAnimation("Portal")->IsEnd())
	{
		LevelChange();
	}
}

void PortalDoor::CollisionCheck(float _DeltaTime)
{
	if (nullptr != RenderCollisionPtr->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		EnterMessageScaleUp(_DeltaTime);
	}
	else
	{
		EnterMessageScaleDown(_DeltaTime);
	}
}

void PortalDoor::LevelChange()
{
	TutorialLevel::TutorialLevelPtr->LoadingOn();
	GameEngineCore::ChangeLevel("OverworldLevel");
}

void PortalDoor::EnterMessageScaleUp(float _DeltaTime)
{
	ScaleCheckStart = true;
	ScaleMinTime = 0.0f;
	EnterMessageRenderPtr->On();
	ScaleCount = 1;

	ScaleMaxTime += _DeltaTime;

	float4 Scale = float4::LerpClamp(EnterMessageRenderMinScale, EnterMessageRenderMaxScale, ScaleMaxTime * 5.5f);

	EnterMessageRenderPtr->GetTransform()->SetLocalScale(Scale);
}

void PortalDoor::EnterMessageScaleDown(float _DeltaTime)
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
		EnterMessageRenderDelayScale = EnterMessageRenderMaxScale * 1.2f;
	}

	float4 Scale = float4::LerpClamp(EnterMessageRenderDelayScale, EnterMessageRenderMinScale, ScaleMinTime * 5.f);

	EnterMessageRenderPtr->GetTransform()->SetLocalScale(Scale);

	if (EnterMessageRenderMinScale == EnterMessageRenderPtr->GetTransform()->GetLocalScale())
	{
		EnterMessageRenderPtr->Off();
	}
}
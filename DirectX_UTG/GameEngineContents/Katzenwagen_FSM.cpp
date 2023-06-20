#include "PrecompileHeader.h"
#include "Katzenwagen.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "Mouse_Map.h"

void Katzenwagen::ChangeState(KatzenwagenState _StateValue)
{
	KatzenwagenState NextState = _StateValue;
	KatzenwagenState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case KatzenwagenState::Intro:
		IntroStart();
		break;
	case KatzenwagenState::Idle:
		IdleStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case KatzenwagenState::Intro:
		IntroEnd();
		break;
	case KatzenwagenState::Idle:
		IdleEnd();
		break;
	default:
		break;
	}
}

void Katzenwagen::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case KatzenwagenState::Intro:
		IntroUpdate(_DeltaTime);
		break;
	case KatzenwagenState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Katzenwagen::IntroStart()
{
	BodyRenderPtr->On();

	BodyRenderPtr->ChangeAnimation("Cat_Intro_Body");

	BodyRenderPtr->SetAnimationStartEvent("Cat_Intro_Body", 8, std::bind(&Katzenwagen::IntroAnimationSetting, this));
}
void Katzenwagen::IntroUpdate(float _DeltaTime)
{
	if (true == HeadRenderPtr->IsUpdate())
	{
		IntroHeadPositionSetting();

		if (true == HeadRenderPtr->IsAnimationEnd())
		{
			ChangeState(KatzenwagenState::Idle);
			return;
		}
	}
}
void Katzenwagen::IntroEnd()
{

}

void Katzenwagen::IdleStart()
{
	if (nullptr == HeadParent)
	{
		HeadParent = CreateComponent<GameEngineSpriteRenderer>();
		HeadParent->SetScaleToTexture("RedBox.png");
		HeadParent->GetTransform()->SetLocalScale({ 1, 1, 1 });
	}

	HeadRenderPtr->ChangeAnimation("Cat_Idle_Head_Left");
	HeadRenderPtr->GetTransform()->SetParent(HeadParent->GetTransform());

	EXCollisionPtr->On();
	BodyCollisionPtr->On();
	BodyUpRenderPtr->On();
}
void Katzenwagen::IdleUpdate(float _DeltaTime)
{
	if (true == HeadRenderPtr->FindAnimation("Cat_Idle_Head_Left")->IsEnd())
	{
		Directbool = true;
		HeadRenderPtr->ChangeAnimation("Cat_Idle_Head_Right", false);
	}

	if (true == HeadRenderPtr->FindAnimation("Cat_Idle_Head_Right")->IsEnd())
	{
		Directbool = false;
		HeadRenderPtr->ChangeAnimation("Cat_Idle_Head_Left", false);
	}

	if (false == Directbool)
	{
		HeadParent->GetTransform()->SetLocalPositiveScaleX();
	}
	else
	{
		HeadParent->GetTransform()->SetLocalNegativeScaleX();
	}
}
void Katzenwagen::IdleEnd()
{

}

void Katzenwagen::IntroHeadPositionSetting()
{
	if (54 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -20, -10 });
	}
	else if (53 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -20, -10 });
	}
	else if (52 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -20, -10 });
	}
	else if (51 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -20, -10 });
	}
	else if (50 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -40, -10 });
	}
	else if (49 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -60, -10 });
	}
	else if (48 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -80, -10 });
	}
	else if (37 == HeadRenderPtr->GetCurrentFrame())
	{
		HeadRenderPtr->GetTransform()->SetLocalPosition({ 0, -105, -10 });
	}
}
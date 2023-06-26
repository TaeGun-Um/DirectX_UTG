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
	if (nullptr == GameEngineSprite::Find("Kettle_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("ElderKettle");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Kettle_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottle_Pop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottle_Pop_Boil").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bottle_Pop_Trans_Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Talk_A").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Talk_AToB").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Talk_B").GetFullPath());
	}

	if (RenderPtr == nullptr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Kettle_Idle", .SpriteName = "Kettle_Idle", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Bottle_Pop", .SpriteName = "Bottle_Pop", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Bottle_Pop_Boil", .SpriteName = "Bottle_Pop_Boil", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Bottle_Pop_Trans_Idle", .SpriteName = "Bottle_Pop_Trans_Idle", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Talk_A", .SpriteName = "Talk_A", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Talk_AToB", .SpriteName = "Talk_AToB", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Talk_B", .SpriteName = "Talk_B", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });
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
		CollisionPtr->GetTransform()->SetLocalPosition({ 10, -20, -17 });
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
		EnterMessageRenderPtr->GetTransform()->SetLocalPosition(RenderPtr->GetTransform()->GetLocalPosition() + float4{ 15, 150, -20 });
		EnterMessageRenderPtr->Off();
	}
}

void ElderKettle::Update(float _DeltaTime)
{
	if (true == IsDebugRender)
	{
		CollisionRenderPtr->On();
	}
	else
	{
		CollisionRenderPtr->Off();
	}

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

//< ¿¤´õÄ³Æ²>
//1. what a fine pickle you boys have gotten yourselves into!
//2. i know you don't want to be pawns of the devil!
//3. but if you refuse... i can't bear to imagine your fates!
//4. you must Play along for now.collect those contracts!
//5. and you'd best be ready for some nasty business...!
//6. your debtor 'friends' won't be very frindly once you confront them!
//7. in fact, i expect they'll transform into trrible beasts!
//8. take this potion so they won't hang you out to dry.
//9. it will give you the most remarkable magical abilities!
//10. now go to my writing desk and use the mystical inkwell there.
//11. you need to prepare yourselves for a scrap!!
//
//1. well.what are you rascals waiting for ? off you go!
//2. meanwhile, i shall try to figure some way out of this mess!
//3. good luck.you troublesome little mugs!!
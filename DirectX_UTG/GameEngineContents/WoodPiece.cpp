#include "PrecompileHeader.h"
#include "WoodPiece.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "MouseLevel.h"
#include "You_Died.h"

WoodPiece::WoodPiece() 
{
}

WoodPiece::~WoodPiece() 
{
}

void WoodPiece::Start()
{
	//if (nullptr == StickRenderPtr)
	//{
	//	StickRenderPtr = CreateComponent<GameEngineSpriteRenderer>();

	//	StickRenderPtr->CreateAnimation({ .AnimationName = "Stick_A", .SpriteName = "Stick_A", .FrameInter = 0.09f, .Loop = true, .ScaleToTexture = true });
	//	StickRenderPtr->CreateAnimation({ .AnimationName = "Stick_B", .SpriteName = "Stick_B", .FrameInter = 0.09f, .Loop = true, .ScaleToTexture = true });
	//	StickRenderPtr->CreateAnimation({ .AnimationName = "Stick_C", .SpriteName = "Stick_C", .FrameInter = 0.09f, .Loop = true, .ScaleToTexture = true });

	//	StickRenderPtr->ChangeAnimation("Stick_A");
	//}

	//if (nullptr == BottleRenderPtr)
	//{
	//	BottleRenderPtr = CreateComponent<GameEngineSpriteRenderer>();

	//	BottleRenderPtr->CreateAnimation({ .AnimationName = "A_Loop", .SpriteName = "Bottlecap_A", .FrameInter = 0.09f, .Loop = true, .ScaleToTexture = true });
	//	BottleRenderPtr->CreateAnimation({ .AnimationName = "B_Loop", .SpriteName = "Bottlecap_B", .FrameInter = 0.09f, .Loop = true, .ScaleToTexture = true });
	//	BottleRenderPtr->CreateAnimation({ .AnimationName = "C_Loop", .SpriteName = "Bottlecap_C", .FrameInter = 0.09f, .Loop = true, .ScaleToTexture = true });
	//	BottleRenderPtr->CreateAnimation({ .AnimationName = "D_Loop", .SpriteName = "Bottlecap_D", .FrameInter = 0.09f, .Loop = true, .ScaleToTexture = true });
	//	BottleRenderPtr->CreateAnimation({ .AnimationName = "E_Loop", .SpriteName = "Bottlecap_E", .FrameInter = 0.09f, .Loop = true, .ScaleToTexture = true });
	//	BottleRenderPtr->CreateAnimation({ .AnimationName = "F_Loop", .SpriteName = "Bottlecap_F", .FrameInter = 0.09f, .Loop = true, .ScaleToTexture = true });

	//	BottleRenderPtr->ChangeAnimation("A_Loop");
	//	ChangeState(SitckState::Intro);
	//}

	//if (nullptr == AttackCollisionPtr)
	//{
	//	AttackCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
	//	AttackCollisionPtr->SetColType(ColType::SPHERE2D);
	//	AttackCollisionPtr->Off();
	//}

	//if (nullptr == AttackCollisionRenderPtr)
	//{
	//	AttackCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	//	AttackCollisionRenderPtr->SetTexture("GreenLine.png");
	//	AttackCollisionRenderPtr->Off();
	//}
}

void WoodPiece::Update(float _DeltaTime)
{
	//if (true == MouseLevel::MouseLevelPtr->GetYouDiedPtr()->GetIsEnd())
	//{
	//	Death();
	//}

	//UpdateState(_DeltaTime);
}
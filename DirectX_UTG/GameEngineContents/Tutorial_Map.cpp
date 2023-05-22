#include "PrecompileHeader.h"
#include "Tutorial_Map.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"

Tutorial_Map::Tutorial_Map() 
{
}

Tutorial_Map::~Tutorial_Map() 
{
}

void Tutorial_Map::Start()
{
	if (nullptr == GameEngineTexture::Find("Tutorial_Map.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Tutorial_Normal");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Tutorial_Map.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("tutorial_pink_sphere_1.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Tutorial_Normal");
		NewDir.Move("Sphere");

		GameEngineTexture::Load(NewDir.GetPlusFileName("tutorial_pink_sphere_1.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("tutorial_pink_sphere_2.png").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->SetTexture("Tutorial_Map.png");
		RenderPtr->GetTransform()->SetLocalScale({ 6188, 720, 1 });
		RenderPtr->GetTransform()->SetLocalPosition({ 0, 0, 1 });
	}

	if (nullptr == PlatformCollisionPtr)
	{
		PlatformCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Platform));
		PlatformCollisionPtr->GetTransform()->SetLocalScale({ 290, 26, 1 });
		PlatformCollisionPtr->GetTransform()->SetLocalPosition({ -970, 0, 1 });
	}

	if (nullptr == PlatformCollisionRenderPtr)
	{
		PlatformCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		PlatformCollisionRenderPtr->GetTransform()->SetLocalScale({ 290, 26, 1 });
		PlatformCollisionRenderPtr->GetTransform()->SetLocalPosition({ -970, 0, 1 });
		PlatformCollisionRenderPtr->SetTexture("GreenBox.png");
		PlatformCollisionRenderPtr->ColorOptionValue.MulColor.a = 0.5f;
	}

	if (nullptr == ParrySpotCollisionPtr0)
	{
		ParrySpotCollisionPtr0 = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::ParrySpot));
		ParrySpotCollisionPtr0->GetTransform()->SetLocalScale({ 40, 40, 1 });
		ParrySpotCollisionPtr0->GetTransform()->SetLocalPosition({ 704, -9, 1 });
	}

	if (nullptr == ParrySpotCollisionPtr1)
	{
		ParrySpotCollisionPtr1 = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::ParrySpot));
		ParrySpotCollisionPtr1->GetTransform()->SetLocalScale({ 40, 40, 1 });
		ParrySpotCollisionPtr1->GetTransform()->SetLocalPosition({ 894, -9, 1 });
		ParrySpotCollisionPtr1->Off();
	}

	if (nullptr == ParrySpotCollisionPtr2)
	{
		ParrySpotCollisionPtr2 = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::ParrySpot));
		ParrySpotCollisionPtr2->GetTransform()->SetLocalScale({ 40, 40, 1 });
		ParrySpotCollisionPtr2->GetTransform()->SetLocalPosition({ 1088, -9, 1 });
		ParrySpotCollisionPtr2->Off();
	}

	if (nullptr == ParrySpotCollisionRenderPtr0)
	{
		ParrySpotCollisionRenderPtr0 = CreateComponent<GameEngineSpriteRenderer>();
		ParrySpotCollisionRenderPtr0->SetTexture("tutorial_pink_sphere_1.png");
		ParrySpotCollisionRenderPtr0->GetTransform()->SetLocalScale({ 100, 100, 1 });
		ParrySpotCollisionRenderPtr0->GetTransform()->SetLocalPosition(ParrySpotCollisionPtr0->GetTransform()->GetLocalPosition());
		ParrySpotCollisionRenderPtr0->ColorOptionValue.MulColor.a = 0.7f;
	}

	if (nullptr == ParrySpotCollisionRenderPtr1)
	{
		ParrySpotCollisionRenderPtr1 = CreateComponent<GameEngineSpriteRenderer>();
		ParrySpotCollisionRenderPtr1->SetTexture("tutorial_pink_sphere_2.png");
		ParrySpotCollisionRenderPtr1->GetTransform()->SetLocalScale({ 100, 100, 1 });
		ParrySpotCollisionRenderPtr1->GetTransform()->SetLocalPosition(ParrySpotCollisionPtr1->GetTransform()->GetLocalPosition());
		ParrySpotCollisionRenderPtr1->ColorOptionValue.MulColor.a = 0.7f;
		ParrySpotCollisionRenderPtr1->Off();
	}

	if (nullptr == ParrySpotCollisionRenderPtr2)
	{
		ParrySpotCollisionRenderPtr2 = CreateComponent<GameEngineSpriteRenderer>();
		ParrySpotCollisionRenderPtr2->SetTexture("tutorial_pink_sphere_1.png");
		ParrySpotCollisionRenderPtr2->GetTransform()->SetLocalScale({ 100, 100, 1 });
		ParrySpotCollisionRenderPtr2->GetTransform()->SetLocalPosition(ParrySpotCollisionPtr2->GetTransform()->GetLocalPosition());
		ParrySpotCollisionRenderPtr2->ColorOptionValue.MulColor.a = 0.7f;
		ParrySpotCollisionRenderPtr2->Off();
	}
}
void Tutorial_Map::Update(float _DeltaTime)
{
	if (true == IsDebugRender)
	{
		PlatformCollisionRenderPtr->On();
	}
	else
	{
		PlatformCollisionRenderPtr->Off();
	}

	if (nullptr != ParrySpotCollisionPtr0->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D)
		&& Player::MainPlayer->GetParryCheck())
	{
		Step_1();
	}

	if (nullptr != ParrySpotCollisionPtr1->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D)
		&& Player::MainPlayer->GetParryCheck())
	{
		Step_2();
	}

	if (nullptr != ParrySpotCollisionPtr2->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D)
		&& Player::MainPlayer->GetParryCheck())
	{
		Step_3();
	}
}

void Tutorial_Map::Step_1()
{
	ParrySpotCollisionPtr0->Off();
	ParrySpotCollisionRenderPtr0->Off();

	ParrySpotCollisionPtr1->On();
	ParrySpotCollisionRenderPtr1->On();
}

void Tutorial_Map::Step_2()
{
	ParrySpotCollisionPtr1->Off();
	ParrySpotCollisionRenderPtr1->Off();

	ParrySpotCollisionPtr2->On();
	ParrySpotCollisionRenderPtr2->On();
}

void Tutorial_Map::Step_3()
{
	ParrySpotCollisionPtr2->Off();
	ParrySpotCollisionRenderPtr2->Off();

	ParrySpotCollisionPtr0->On();
	ParrySpotCollisionRenderPtr0->On();
}
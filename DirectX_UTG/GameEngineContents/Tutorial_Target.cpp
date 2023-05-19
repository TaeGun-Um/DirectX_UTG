#include "PrecompileHeader.h"
#include "Tutorial_Target.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Tutorial_Target::Tutorial_Target() 
{
}

Tutorial_Target::~Tutorial_Target() 
{
}

void Tutorial_Target::Start()
{
	if (nullptr == GameEngineTexture::Find("tutorial_target_0001"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Tutorial_Normal");
		NewDir.Move("Target");

		GameEngineTexture::Load(NewDir.GetPlusFileName("tutorial_target_0001.png").GetFullPath());
	}

	if (nullptr == GameEngineTexture::Find("tutorial_pyramid_topper.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Tutorial_Normal");
		NewDir.Move("Shapes_and_Exit_Door");

		GameEngineTexture::Load(NewDir.GetPlusFileName("tutorial_pyramid_topper.png").GetFullPath());
	}

	if (nullptr == BoxCollisionPtr)
	{
		BoxCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Wall));
		BoxCollisionPtr->GetTransform()->SetLocalScale({ 190, 400, 1 });
		BoxCollisionPtr->GetTransform()->SetLocalPosition({ -6, -70 });
		
	}

	if (nullptr == TargetCollisionPtr)
	{
		TargetCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Monster));
		TargetCollisionPtr->GetTransform()->SetLocalScale({ 70, 80, 1 });
		TargetCollisionPtr->GetTransform()->SetLocalPosition({ -3, 110 });
	}

	if (nullptr == BoxRenderPtr)
	{
		BoxRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BoxRenderPtr->SetTexture("tutorial_pyramid_topper.png");
		BoxRenderPtr->GetTransform()->SetLocalScale({ 195, 170, 1 });
		BoxRenderPtr->GetTransform()->SetLocalPosition({ 0, 0 });
	}

	if (nullptr == TargetRenderPtr)
	{
		TargetRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		TargetRenderPtr->SetTexture("tutorial_target_0001.png");
		TargetRenderPtr->GetTransform()->SetLocalScale({ 76, 87, 1 });
		TargetRenderPtr->GetTransform()->SetLocalPosition(TargetCollisionPtr->GetTransform()->GetLocalPosition());
	}

	if (nullptr == TargetCollisionRenderPtr)
	{
		TargetCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		TargetCollisionRenderPtr->SetTexture("GreenLine.png");
		TargetCollisionRenderPtr->GetTransform()->SetLocalScale(TargetCollisionPtr->GetTransform()->GetLocalScale());
		TargetCollisionRenderPtr->GetTransform()->SetLocalPosition(TargetCollisionPtr->GetTransform()->GetLocalPosition());
	}

	if (nullptr == BoxCollisionRenderPtr)
	{
		BoxCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BoxCollisionRenderPtr->SetTexture("GreenLine.png");
		BoxCollisionRenderPtr->GetTransform()->SetLocalScale(BoxCollisionPtr->GetTransform()->GetLocalScale());
		BoxCollisionRenderPtr->GetTransform()->SetLocalPosition(BoxCollisionPtr->GetTransform()->GetLocalPosition());
	}
}

void Tutorial_Target::Update(float _DeltaTime)
{

}

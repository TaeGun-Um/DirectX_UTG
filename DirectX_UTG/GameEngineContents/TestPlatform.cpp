#include "PrecompileHeader.h"
#include "TestPlatform.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

TestPlatform::TestPlatform() 
{
}

TestPlatform::~TestPlatform() 
{
}

void TestPlatform::Start()
{
	if (nullptr == GameEngineSprite::Find("Platform"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("1_Ribby_and_Croaks");
		NewDir.Move("Croaks_SlotMachine");
		NewDir.Move("SlotMachine");
		NewDir.Move("Attack");
		NewDir.Move("Platforms");
		NewDir.Move("Bison");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Platform").GetFullPath());
	}

	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	CollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();

	RenderPtr->CreateAnimation({ .AnimationName = "Platform", .SpriteName = "Platform", .FrameInter = 0.05f, .ScaleToTexture = true });
	RenderPtr->ChangeAnimation("Platform");

	CollisionRenderPtr->SetTexture("GreenLine.png");
	//CollisionRenderPtr->GetTransform()->SetParent(RenderPtr->GetTransform());
	CollisionRenderPtr->GetTransform()->SetLocalScale({200, 100, 1});
}

void TestPlatform::Update(float _DeltaTime)
{

}
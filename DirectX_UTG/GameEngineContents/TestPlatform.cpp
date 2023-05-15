#include "PrecompileHeader.h"
#include "TestPlatform.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

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

	CollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Platform));
	CollisionPtr->GetTransform()->SetLocalScale({ 200, 26, 1 });
	CollisionPtr->GetTransform()->SetLocalPosition({ 0, 20 });

	CollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	CollisionRenderPtr->GetTransform()->SetLocalScale({ 200, 26 });
	CollisionRenderPtr->GetTransform()->SetLocalPosition({ 0, 20 });
	CollisionRenderPtr->SetTexture("GreenLine.png");
}

void TestPlatform::Update(float _DeltaTime)
{

}
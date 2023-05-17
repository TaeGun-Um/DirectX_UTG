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
	CollisionPtr->GetTransform()->SetLocalScale({ 200, 25, 1 });
	CollisionPtr->GetTransform()->SetLocalPosition({ 0, 20 });

	CollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	CollisionRenderPtr->GetTransform()->SetLocalScale(CollisionPtr->GetTransform()->GetLocalScale());
	CollisionRenderPtr->GetTransform()->SetLocalPosition(CollisionPtr->GetTransform()->GetLocalPosition());
	CollisionRenderPtr->SetTexture("GreenBox.png");
	CollisionRenderPtr->ColorOptionValue.MulColor.a = 0.6f;

	AttackCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
	AttackCollisionPtr->GetTransform()->SetLocalScale({ 50, 50, 1 });
	AttackCollisionPtr->GetTransform()->SetLocalPosition({ 50, 0 });

	AttackCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	AttackCollisionRenderPtr->GetTransform()->SetLocalScale({ 50, 50, 1 });
	AttackCollisionRenderPtr->GetTransform()->SetLocalPosition({ 50, 0 });
	AttackCollisionRenderPtr->SetTexture("RedLine.png");
}

void TestPlatform::Update(float _DeltaTime)
{

}

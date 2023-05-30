#include "PrecompileHeader.h"
#include "TestActor.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

TestActor::TestActor() 
{
}

TestActor::~TestActor() 
{
}

void TestActor::Start()
{
	if (nullptr == GameEngineTexture::Find("dragon_idle_0001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Phase1");
		NewDir.Move("Dragon_Idle");

		GameEngineTexture::Load(NewDir.GetPlusFileName("dragon_idle_0001.png").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->SetScaleToTexture("dragon_idle_0001.png");
	}
}

void TestActor::Update(float _DeltaTime)
{

}
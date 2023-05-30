#include "PrecompileHeader.h"
#include "GrimMatchstick.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

GrimMatchstick::GrimMatchstick() 
{
}

GrimMatchstick::~GrimMatchstick() 
{
}

void GrimMatchstick::Start()
{
	if (nullptr == GameEngineSprite::Find("Dragon_Idle"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("2_Grim_Matchstick");
		NewDir.Move("Phase1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dragon_Idle").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Dragon_Idle", .SpriteName = "Dragon_Idle", .FrameInter = 0.06f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Dragon_Idle");
	}
}

void GrimMatchstick::Update(float _DeltaTime)
{

}
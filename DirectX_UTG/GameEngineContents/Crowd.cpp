#include "PrecompileHeader.h"
#include "Crowd.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Crowd::Crowd() 
{
}

Crowd::~Crowd() 
{
}

void Crowd::Start()
{
	if (nullptr == GameEngineSprite::Find("Crowd"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("1_Ribby_and_Croaks");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Crowd").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Crowd", .SpriteName = "Crowd", .FrameInter = 0.11f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Crowd");
	}
}

void Crowd::Update(float _DeltaTime)
{

}
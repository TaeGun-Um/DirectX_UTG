#include "PrecompileHeader.h"
#include "Craber.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Craber::Craber() 
{
}

Craber::~Craber() 
{
}

void Craber::Start()
{
	if (nullptr == GameEngineSprite::Find("Craber"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("1_Ribby_and_Croaks");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Craber").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Craber", .SpriteName = "Craber", .FrameInter = 0.11f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Craber");
	}
}

void Craber::Update(float _DeltaTime)
{

}
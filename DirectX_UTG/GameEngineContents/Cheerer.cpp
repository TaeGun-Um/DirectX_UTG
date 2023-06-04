#include "PrecompileHeader.h"
#include "Cheerer.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>


Cheerer::Cheerer() 
{
}

Cheerer::~Cheerer() 
{
}

void Cheerer::Start()
{
	if (nullptr == GameEngineSprite::Find("Cheerer"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("1_Ribby_and_Croaks");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Cheerer").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Cheerer", .SpriteName = "Cheerer", .FrameInter = 0.11f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Cheerer");
	}
}

void Cheerer::Update(float _DeltaTime)
{

}
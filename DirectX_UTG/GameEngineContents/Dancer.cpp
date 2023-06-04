#include "PrecompileHeader.h"
#include "Dancer.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Dancer::Dancer() 
{
}

Dancer::~Dancer() 
{
}

void Dancer::Start()
{
	if (nullptr == GameEngineSprite::Find("Dancer"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("1_Ribby_and_Croaks");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Dancer").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Dancer", .SpriteName = "Dancer", .FrameInter = 0.11f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Dancer");
	}
}

void Dancer::Update(float _DeltaTime)
{

}
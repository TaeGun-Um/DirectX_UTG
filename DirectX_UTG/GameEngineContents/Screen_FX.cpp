#include "PrecompileHeader.h"
#include "Screen_FX.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Screen_FX::Screen_FX() 
{
}

Screen_FX::~Screen_FX() 
{
}

void Screen_FX::Start()
{
	if (nullptr == GameEngineSprite::Find("Screen_FX"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Opening1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Screen_FX").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Screen_FX", .SpriteName = "Screen_FX", .FrameInter = 0.1f });
		RenderPtr->GetTransform()->SetLocalScale({1280, 720});
		RenderPtr->ChangeAnimation("Screen_FX");
		RenderPtr->ColorOptionValue.MulColor.r = 0.8f;
		RenderPtr->ColorOptionValue.MulColor.g = 0.8f;
		RenderPtr->ColorOptionValue.MulColor.b = 0.8f;
		RenderPtr->ColorOptionValue.MulColor.a = 0.2f;
	}
}
void Screen_FX::Update(float _DeltaTime)
{

}
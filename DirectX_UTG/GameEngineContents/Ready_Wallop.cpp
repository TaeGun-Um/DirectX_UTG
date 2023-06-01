#include "PrecompileHeader.h"
#include "Ready_Wallop.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

Ready_Wallop::Ready_Wallop() 
{
}

Ready_Wallop::~Ready_Wallop() 
{
}

void Ready_Wallop::Start()
{
	if (nullptr == GameEngineSprite::Find("Ready_WALLOP"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Font");
		NewDir.Move("Message");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ready_WALLOP").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineUIRenderer>();
		RenderPtr->GetTransform()->SetLocalScale({ 1280, 720 });
		RenderPtr->CreateAnimation({ .AnimationName = "Ready_Wallop", .SpriteName = "Ready_Wallop", .FrameInter = 0.05f, .Loop = false });

		RenderPtr->ChangeAnimation("Ready_Wallop");
		RenderPtr->Off();
	}
}

void Ready_Wallop::Update(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		IsEnd = true;
		RenderPtr->Off();
	}
}
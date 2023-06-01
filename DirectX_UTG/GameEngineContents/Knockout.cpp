#include "PrecompileHeader.h"
#include "Knockout.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

Knockout::Knockout() 
{
}

Knockout::~Knockout() 
{
}

void Knockout::Start()
{
	if (nullptr == GameEngineSprite::Find("KNOCKOUT"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Font");
		NewDir.Move("Message");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("KNOCKOUT").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineUIRenderer>();
		RenderPtr->GetTransform()->SetLocalScale({ 1280, 720 });
		RenderPtr->CreateAnimation({ .AnimationName = "KNOCKOUT", .SpriteName = "KNOCKOUT", .FrameInter = 0.05f, .Loop = false });

		RenderPtr->ChangeAnimation("KNOCKOUT");
		RenderPtr->Off();
	}
}

void Knockout::Update(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		IsEnd = true;
		RenderPtr->Off();
	}
}
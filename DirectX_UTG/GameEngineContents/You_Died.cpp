#include "PrecompileHeader.h"
#include "You_Died.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

You_Died::You_Died() 
{
}

You_Died::~You_Died() 
{
}

void You_Died::Start()
{
	if (nullptr == GameEngineSprite::Find("YOU_DIED.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Font");
		NewDir.Move("Message");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("YOU_DIED.png").GetFullPath(), 3, 7);
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineUIRenderer>();
		RenderPtr->GetTransform()->SetLocalScale({ 1079, 235 });
		RenderPtr->CreateAnimation({ "YOU_DIED", "YOU_DIED.png", 0, 19, 0.05f, true });

		RenderPtr->ChangeAnimation("YOU_DIED");
		RenderPtr->Off();
	}
}

void You_Died::Update(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		IsEnd = true;
		RenderPtr->Off();
	}
}
#include "PrecompileHeader.h"
#include "Tutorial_BackLayer.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

#include "Player.h"

Tutorial_BackLayer::Tutorial_BackLayer() 
{
}

Tutorial_BackLayer::~Tutorial_BackLayer() 
{
}

void Tutorial_BackLayer::Start()
{
	if (nullptr == GameEngineTexture::Find("Tutorial_BackLayer_002.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Tutorial_Normal");
		NewDir.Move("Drawing");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Tutorial_BackLayer_002.png").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineUIRenderer>();
		RenderPtr->SetTexture("Tutorial_BackLayer_002.png");
		RenderPtr->GetTransform()->SetLocalScale({ 1280, 720, 1 });
		RenderPtr->GetTransform()->SetLocalPosition({ -640, -260, 1 });
	}
}
void Tutorial_BackLayer::Update(float _DeltaTime)
{
}
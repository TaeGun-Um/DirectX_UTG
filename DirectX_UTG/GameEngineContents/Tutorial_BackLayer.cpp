#include "PrecompileHeader.h"
#include "Tutorial_BackLayer.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

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
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->SetTexture("Tutorial_BackLayer_002.png");
		RenderPtr->GetTransform()->SetLocalScale({ 1280, 720, 1 });
		RenderPtr->GetTransform()->SetLocalPosition({ 0, 0, 1 });
	}
}
void Tutorial_BackLayer::Update(float _DeltaTime)
{
	float4 MinusDist = Player::MainPlayer->GetCameraMoveDistance();
	GetTransform()->AddWorldPosition(MinusDist);
}
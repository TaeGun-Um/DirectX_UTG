#include "PrecompileHeader.h"
#include "Tutorial_BackGround.h"

#include <GameEngineCore/GameEngineLevel.h>
//#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"

Tutorial_BackGround::Tutorial_BackGround() 
{
}

Tutorial_BackGround::~Tutorial_BackGround() 
{
}

void Tutorial_BackGround::Start()
{
	if (nullptr == GameEngineTexture::Find("Tutorial_BackLayer_001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Tutorial_Normal");
		NewDir.Move("Drawing");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Tutorial_BackLayer_001.png").GetFullPath());
	}

	if (RenderPtr == nullptr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->SetTexture("Tutorial_BackLayer_001.png");
		RenderPtr->GetTransform()->SetLocalScale({ 1350, 759, 1 });
		RenderPtr->GetTransform()->SetLocalPosition({ 0, 0, 1 });
	}
}
void Tutorial_BackGround::Update(float _DeltaTime)
{
	float XPos =  GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition().x;
	float YPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition().y;
	float ZPos = GetTransform()->GetLocalPosition().z;

	GetTransform()->SetLocalPosition({ XPos , YPos , ZPos });
}
#include "PrecompileHeader.h"
#include "Mouse_FrontObject.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Mouse_FrontObject::Mouse_FrontObject() 
{
}

Mouse_FrontObject::~Mouse_FrontObject() 
{
}

void Mouse_FrontObject::Start()
{
	//if (nullptr == GameEngineTexture::Find("Backstage_1.png"))
	//{
	//	GameEngineDirectory NewDir;
	//	NewDir.MoveParentToDirectory("CupHead_Resource");
	//	NewDir.Move("CupHead_Resource");
	//	NewDir.Move("Image");
	//	NewDir.Move("Level");
	//	NewDir.Move("1_Ribby_and_Croaks");

	//	GameEngineTexture::Load(NewDir.GetPlusFileName("Backstage_1.png").GetFullPath());
	//}

	//if (nullptr == RenderPtr)
	//{
	//	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	//	RenderPtr->SetTexture("Backstage_1.png");
	//	RenderPtr->GetTransform()->SetLocalScale({ 1941, 480 });
	//	RenderPtr->GetTransform()->SetLocalPosition({ 40, 130 });
	//}
}

void Mouse_FrontObject::Update(float _DeltaTime)
{

}
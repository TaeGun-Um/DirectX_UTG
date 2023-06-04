#include "PrecompileHeader.h"
#include "Frog_FrontObject.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Frog_FrontObject::Frog_FrontObject() 
{
}

Frog_FrontObject::~Frog_FrontObject() 
{
}

void Frog_FrontObject::Start()
{
	if (nullptr == GameEngineTexture::Find("Plant_1.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("1_Ribby_and_Croaks");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Table_1.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Table_2.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Plant_1.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Plant_2.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Plant_3.png").GetFullPath());
	}

	if (nullptr == FrontRenderPtr_1)
	{
		FrontRenderPtr_1 = CreateComponent<GameEngineSpriteRenderer>();
		FrontRenderPtr_1->SetTexture("Table_1.png");
		FrontRenderPtr_1->GetTransform()->SetLocalScale({ 469, 250 });
		FrontRenderPtr_1->GetTransform()->SetLocalPosition({ 550, -290 });
	}

	if (nullptr == FrontRenderPtr_2)
	{
		FrontRenderPtr_2 = CreateComponent<GameEngineSpriteRenderer>();
		FrontRenderPtr_2->SetTexture("Table_2.png");
		FrontRenderPtr_2->GetTransform()->SetLocalScale({ 470, 250 });
		FrontRenderPtr_2->GetTransform()->SetLocalPosition({ -550, -295 });

	}

	if (nullptr == FrontRenderPtr_3)
	{
		FrontRenderPtr_3 = CreateComponent<GameEngineSpriteRenderer>();
		FrontRenderPtr_3->SetTexture("Plant_3.png");
		FrontRenderPtr_3->GetTransform()->SetLocalScale({ 324, 300 });
		FrontRenderPtr_3->GetTransform()->SetLocalPosition({ -640, -310 });
	}

	if (nullptr == FrontRenderPtr_4)
	{
		FrontRenderPtr_4 = CreateComponent<GameEngineSpriteRenderer>();
		FrontRenderPtr_4->SetTexture("Plant_2.png");
		FrontRenderPtr_4->GetTransform()->SetLocalScale({ 371, 250 });
		FrontRenderPtr_4->GetTransform()->SetLocalPosition({ -30, -340 });
	}

	if (nullptr == FrontRenderPtr_5)
	{
		FrontRenderPtr_5 = CreateComponent<GameEngineSpriteRenderer>();
		FrontRenderPtr_5->SetTexture("Plant_1.png");
		FrontRenderPtr_5->GetTransform()->SetLocalScale({ 314, 300 });
		FrontRenderPtr_5->GetTransform()->SetLocalPosition({ 560, -305 });
	}
}

void Frog_FrontObject::Update(float _DeltaTime)
{

}
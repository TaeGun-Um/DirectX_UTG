#include "PrecompileHeader.h"
#include "Frog_Map.h"

Frog_Map::Frog_Map() 
{
}

Frog_Map::~Frog_Map() 
{
}

void Frog_Map::Start()
{
	if (nullptr == GameEngineTexture::Find("Backstage_1.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("1_Ribby_and_Croaks");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Backstage_1.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Backstage_2.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Backstage_3.png").GetFullPath());
	}

	if (nullptr == BGRenderPtr_1)
	{
		BGRenderPtr_1 = CreateComponent<GameEngineSpriteRenderer>();
		BGRenderPtr_1->SetTexture("Backstage_1.png");
		BGRenderPtr_1->GetTransform()->SetLocalScale({ 1941, 480 });
		BGRenderPtr_1->GetTransform()->SetLocalPosition({ 40, 130 });
	}

	if (nullptr == BGRenderPtr_2)
	{
		BGRenderPtr_2 = CreateComponent<GameEngineSpriteRenderer>();
		BGRenderPtr_2->SetTexture("Backstage_2.png");
		BGRenderPtr_2->GetTransform()->SetLocalScale({ 1707, 650 });
		BGRenderPtr_2->GetTransform()->SetLocalPosition({ 0, 150 });

	}

	if (nullptr == BGRenderPtr_3)
	{
		BGRenderPtr_3 = CreateComponent<GameEngineSpriteRenderer>();
		BGRenderPtr_3->SetTexture("Backstage_3.png");
		BGRenderPtr_3->GetTransform()->SetLocalScale({ 1793, 950 });
		BGRenderPtr_3->GetTransform()->SetLocalPosition({ 0, 65, -2 });
	}
}

void Frog_Map::Update(float _DeltaTime)
{

}
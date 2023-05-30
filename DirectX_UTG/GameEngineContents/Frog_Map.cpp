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

		GameEngineTexture::Load(NewDir.GetPlusFileName("Backstage_1_1.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Backstage_2_2.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("Backstage_3_3.png").GetFullPath());
	}

	if (nullptr == BGRenderPtr_1)
	{
		BGRenderPtr_1 = CreateComponent<GameEngineSpriteRenderer>();
		BGRenderPtr_1->SetScaleToTexture("Backstage_1_1.png");
	}

	if (nullptr == BGRenderPtr_2)
	{
		BGRenderPtr_2 = CreateComponent<GameEngineSpriteRenderer>();
		BGRenderPtr_2->SetScaleToTexture("Backstage_2_2.png");
	}

	if (nullptr == BGRenderPtr_3)
	{
		BGRenderPtr_3 = CreateComponent<GameEngineSpriteRenderer>();
		BGRenderPtr_3->SetScaleToTexture("Backstage_3_3.png");
	}
}

void Frog_Map::Update(float _DeltaTime)
{

}
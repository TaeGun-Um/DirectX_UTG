#include "PrecompileHeader.h"
#include "BuildingDataBase.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

BuildingDataBase::BuildingDataBase() 
{
}

BuildingDataBase::~BuildingDataBase() 
{
}

void BuildingDataBase::Start()
{
	if (nullptr == GameEngineTexture::Find("Overworld_Map.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Overworld");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Overworld_Map.png").GetFullPath());
	}
}

void BuildingDataBase::Update(float _DeltaTime)
{

}

void BuildingDataBase::BuildingSetting()
{

}

void BuildingDataBase::CreateFlag()
{

}
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

void BuildingDataBase::BuildingSetting(Building _BuildingValue)
{
	BuildingValue = _BuildingValue;

	switch (BuildingValue)
	{
	case Building::Home:
	{

	}
		break;
	case Building::Tutorial_Fly:
	{

	}
		break;
	case Building::Mouse:
	{

	}
		break;
	case Building::Frog:
	{

	}
		break;
	case Building::Dragon:
	{

	}
		break;
	case Building::Zeplin:
	{

	}
		break;
	case Building::Djimmi:
	{

	}
		break;
	case Building::Unknown:
	{
		MsgAssert("BuildingSetting()를 실시하지 않았습니다. BuildingValue가 Unknown입니다.");
		return;
	}
		break;
	default:
		break;
	}
}

void BuildingDataBase::CreateFlag()
{

}
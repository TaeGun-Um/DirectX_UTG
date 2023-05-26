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

void BuildingDataBase::BuildingSetting(BuildingValue _BValue)
{
	BValue = _BValue;

	switch (BValue)
	{
	case BuildingValue::Home:
	{

	}
		break;
	case BuildingValue::Tutorial_Fly:
	{

	}
		break;
	case BuildingValue::Mouse:
	{

	}
		break;
	case BuildingValue::Frog:
	{

	}
		break;
	case BuildingValue::Dragon:
	{

	}
		break;
	case BuildingValue::Zeplin:
	{

	}
		break;
	case BuildingValue::Djimmi:
	{

	}
		break;
	case BuildingValue::Unknown:
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
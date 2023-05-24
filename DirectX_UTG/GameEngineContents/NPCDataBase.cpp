#include "PrecompileHeader.h"
#include "NPCDataBase.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

NPCDataBase::NPCDataBase() 
{
}

NPCDataBase::~NPCDataBase() 
{
}

void NPCDataBase::Start()
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

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->SetScaleToTexture("Overworld_Map.png");
	}
}

void NPCDataBase::Update(float _DeltaTime)
{

}

void NPCDataBase::NPCSetting() 
{

}
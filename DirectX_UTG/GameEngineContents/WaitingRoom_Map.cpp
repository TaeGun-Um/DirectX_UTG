#include "PrecompileHeader.h"
#include "WaitingRoom_Map.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

WaitingRoom_Map::WaitingRoom_Map() 
{
}

WaitingRoom_Map::~WaitingRoom_Map() 
{
}

void WaitingRoom_Map::Start()
{

}

void WaitingRoom_Map::Update(float _DeltaTime)
{
	if (nullptr == GameEngineTexture::Find("WaitingRoom_Background.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("WaitingRoom");

		GameEngineTexture::Load(NewDir.GetPlusFileName("WaitingRoom_Background.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("WaitingRoom_Chair.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("WaitingRoom_Couch.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("WaitingRoom_Vignette.png").GetFullPath());
	}

	if (BGRenderPtr == nullptr)
	{
		BGRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BGRenderPtr->SetScaleToTexture("WaitingRoom_Background.png");
	}
	if (CouchRenderPtr == nullptr)
	{
		CouchRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		CouchRenderPtr->SetScaleToTexture("WaitingRoom_Couch.png");
		CouchRenderPtr->GetTransform()->SetLocalPosition({ 460, -230, -20 });
	}
	if (ChairRenderPtr == nullptr)
	{
		ChairRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ChairRenderPtr->SetScaleToTexture("WaitingRoom_Chair.png");
		ChairRenderPtr->GetTransform()->SetLocalPosition({ -320, -270, -20 });
	}
	if (VignetteRenderPtr == nullptr)
	{
		VignetteRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		VignetteRenderPtr->SetScaleToTexture("WaitingRoom_Vignette.png");
		VignetteRenderPtr->GetTransform()->SetLocalPosition({ 0, 0, -20 });
	}
}

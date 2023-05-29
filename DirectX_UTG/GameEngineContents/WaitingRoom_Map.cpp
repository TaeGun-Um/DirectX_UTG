#include "PrecompileHeader.h"
#include "WaitingRoom_Map.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"

WaitingRoom_Map::WaitingRoom_Map() 
{
}

WaitingRoom_Map::~WaitingRoom_Map() 
{
}

void WaitingRoom_Map::Start()
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

	if (nullptr == GameEngineSprite::Find("Note_One"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("WaitingRoom");
		NewDir.Move("Note");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Note_One").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Note_Two").GetFullPath());
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
		CouchOriginPos = CouchRenderPtr->GetTransform()->GetLocalPosition();
	}
	if (ChairRenderPtr == nullptr)
	{
		ChairRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ChairRenderPtr->SetScaleToTexture("WaitingRoom_Chair.png");
		ChairRenderPtr->GetTransform()->SetLocalPosition({ -320, -270, -20 });
		ChairOriginPos = ChairRenderPtr->GetTransform()->GetLocalPosition();
	}
	if (VignetteRenderPtr == nullptr)
	{
		VignetteRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		VignetteRenderPtr->SetScaleToTexture("WaitingRoom_Vignette.png");
		VignetteRenderPtr->GetTransform()->SetLocalPosition({ 0, 0, -20 });
	}

	if (NoteRenderPtr == nullptr)
	{
		NoteRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		NoteRenderPtr->GetTransform()->SetLocalPosition({-55, 120});
		NoteRenderPtr->CreateAnimation({ .AnimationName = "Note_One", .SpriteName = "Note_One", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		NoteRenderPtr->CreateAnimation({ .AnimationName = "Note_Two", .SpriteName = "Note_Two", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
		NoteRenderPtr->ChangeAnimation("Note_One");
	}
}

void WaitingRoom_Map::Update(float _DeltaTime)
{
	if (1 == PlayerDistCount)
	{
		PlayerDistCount = 0;
		PlayerDist = Player::MainPlayer->GetTransform()->GetLocalPosition().x;
	}
	
	if (0 == NoteCount)
	{
		NoteCount = 1;
		NoteRenderPtr->ChangeAnimation("Note_One");
	}

	if (NoteRenderPtr->IsAnimationEnd() && 1 == NoteCount)
	{
		NoteCount = 2;
		NoteRenderPtr->ChangeAnimation("Note_Two");
	}

	if (NoteRenderPtr->IsAnimationEnd() && 2 == NoteCount)
	{
		NoteCount = 0;
	}

	float PlusDist = Player::MainPlayer->GetTransform()->GetLocalPosition().x;
	float Mount = PlayerDist - PlusDist;

	CouchRenderPtr->GetTransform()->SetLocalPosition(CouchOriginPos + float4{ Mount / 50 , 0 });
	ChairRenderPtr->GetTransform()->SetLocalPosition(ChairOriginPos + float4{ Mount / 50 , 0 });
}

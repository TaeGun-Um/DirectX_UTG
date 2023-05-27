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
	if (nullptr == GameEngineTexture::Find("Flag.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Overworld");

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Flag.png").GetFullPath(), 5, 6);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("FlagShadow.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Djimmi_The_Great.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Grim_Matchstick.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Hilda_Berg.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Ribby_and_Croaks.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Ribby_and_Croaks_Wave.png").GetFullPath(), 7, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Tutorial_Fly.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_WaittingRoom.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("To_Werner_Werman.png").GetFullPath(), 3, 1);
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CameraCullingOn();
	}
	if (nullptr == FlagRenderPtr)
	{
		FlagRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		FlagRenderPtr->CreateAnimation({ .AnimationName = "FlagUp", .SpriteName = "Flag.png", .Start = 0, .End = 27, .FrameInter = 0.1f, .ScaleToTexture = true });
		FlagRenderPtr->CreateAnimation({ .AnimationName = "FlagOn", .SpriteName = "Flag.png", .Start = 15, .End = 27, .FrameInter = 0.1f, .ScaleToTexture = true });
		FlagRenderPtr->ChangeAnimation("FlagUp");
		FlagRenderPtr->CameraCullingOn();
		FlagRenderPtr->Off();
	}

	if (nullptr == CollisionPtr)
	{
		CollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::Building));
		CollisionPtr->GetTransform()->SetLocalScale({ 80, 80, 1 });
		// CollisionPtr->GetTransform()->SetLocalPosition({ 0, 0 });
	}

	if (nullptr == CollisionRenderPtr)
	{
		CollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		CollisionRenderPtr->GetTransform()->SetLocalScale(CollisionPtr->GetTransform()->GetLocalScale());
		CollisionRenderPtr->GetTransform()->SetLocalPosition(CollisionPtr->GetTransform()->GetLocalPosition());
		CollisionRenderPtr->SetTexture("GreenLine.png");
		CollisionRenderPtr->ColorOptionValue.MulColor.a = 0.7f;
		CollisionRenderPtr->CameraCullingOn();
	}
	//RenderPtr->CreateAnimation({ "Spread_Spawn", "Spread_Spawn.png", 0, 3, 0.05f, true, false });
	//RenderPtr->CreateAnimation({ .AnimationName = "AirHit", .SpriteName = "AirHit", .FrameInter = 0.04f, .Loop = false });
}

void BuildingDataBase::Update(float _DeltaTime)
{
	CollisionCheck();
}

void BuildingDataBase::BuildingSetting(BuildingValue _BValue)
{
	BValue = _BValue;

	switch (BValue)
	{
	case BuildingValue::Home:
	{
		RenderPtr->CreateAnimation({ .AnimationName = "To_WaittingRoom", .SpriteName = "To_WaittingRoom.png", .Start = 0, .End = 2, .FrameInter = 0.1f, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("To_WaittingRoom");
	}
		break;
	case BuildingValue::Tutorial_Fly:
	{
		RenderPtr->CreateAnimation({ .AnimationName = "To_Tutorial_Fly", .SpriteName = "To_Tutorial_Fly.png", .Start = 0, .End = 2, .FrameInter = 0.1f, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("To_Tutorial_Fly");
	}
		break;
	case BuildingValue::Mouse:
	{
		RenderPtr->CreateAnimation({ .AnimationName = "To_Werner_Werman", .SpriteName = "To_Werner_Werman.png", .Start = 0, .End = 2, .FrameInter = 0.1f, .ScaleToTexture = false });
		RenderPtr->GetTransform()->SetLocalScale({400, 400, 1});
		RenderPtr->ChangeAnimation("To_Werner_Werman");
	}
		break;
	case BuildingValue::Frog:
	{
		RenderPtr->CreateAnimation({ .AnimationName = "To_Ribby_and_Croaks", .SpriteName = "To_Ribby_and_Croaks.png", .Start = 0, .End = 2, .FrameInter = 0.1f, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("To_Ribby_and_Croaks");

		if (nullptr == AssitantRenderPtr)
		{
			AssitantRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
			AssitantRenderPtr->CreateAnimation({ .AnimationName = "To_Ribby_and_Croaks_Wave", .SpriteName = "To_Ribby_and_Croaks_Wave.png", .Start = 0, .End = 6, .FrameInter = 0.1f, .ScaleToTexture = true });
			AssitantRenderPtr->ChangeAnimation("To_Ribby_and_Croaks_Wave");
			AssitantRenderPtr->GetTransform()->SetLocalPosition({-25, -110});
		}
	}
		break;
	case BuildingValue::Dragon:
	{
		RenderPtr->CreateAnimation({ .AnimationName = "To_Grim_Matchstick", .SpriteName = "To_Grim_Matchstick.png", .Start = 0, .End = 2, .FrameInter = 0.1f, .ScaleToTexture = false });
		RenderPtr->GetTransform()->SetLocalScale({ 400, 400, 1 });
		RenderPtr->ChangeAnimation("To_Grim_Matchstick");
	}
		break;
	case BuildingValue::Zeplin:
	{
		RenderPtr->CreateAnimation({ .AnimationName = "To_Hilda_Berg", .SpriteName = "To_Hilda_Berg.png", .Start = 0, .End = 2, .FrameInter = 0.1f, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("To_Hilda_Berg");
	}
		break;
	case BuildingValue::Djimmi:
	{
		RenderPtr->CreateAnimation({ .AnimationName = "To_Djimmi_The_Great", .SpriteName = "To_Djimmi_The_Great.png", .Start = 0, .End = 2, .FrameInter = 0.1f, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("To_Djimmi_The_Great");
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

void BuildingDataBase::CollisionCheck()
{
	if (nullptr != CollisionPtr->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		int a = 0;
	}
}

void BuildingDataBase::CreateFlag()
{

}
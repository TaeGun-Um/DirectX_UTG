#include "PrecompileHeader.h"
#include "CardUI.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
#include "CardUIRenderer.h"

#include "Player.h"

CardUI::CardUI() 
{
}

CardUI::~CardUI() 
{
}

void CardUI::SetMainPalyer(std::shared_ptr<class Player> _MainPlayer)
{
	MainPlayer = _MainPlayer;
}

void CardUI::Start()
{
	if (nullptr == GameEngineSprite::Find("CardUI"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CardUI").GetFullPath());

		NewDir.Move("CardUI");

		//GameEngineTexture::Load(NewDir.GetPlusFileName("Card_001.png").GetFullPath());
	}

	RenderPtr = CreateComponent<CardUIRenderer>();

	RenderPtr->SetScaleToTexture("Card_001.png");

	RenderPtr->CreateAnimation({ .AnimationName = "Rotate", .SpriteName = "CardUI", .Start = 0, .End = 5, .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
	RenderPtr->CreateAnimation({ .AnimationName = "Front", .SpriteName = "CardUI", .Start = 5, .End = 5, .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });

	//RenderPtr->ChangeAnimation("Back");
}

void CardUI::Update(float _DeltaTime)
{
	RenderPtr->SetScaleToCutTexture("Card_001.png", 0.0f, 0.0f, 1.0f, 0.5f);
}

//void GameEngineSprite::ResLoadCard(const std::string_view& _Path, size_t _X, size_t _Y)
//{
//	GameEnginePath NewPath(_Path);
//
//	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(NewPath.GetFileName());
//
//	if (nullptr == Texture)
//	{
//		Texture = GameEngineTexture::Load(_Path);
//	}
//
//	Sprites.resize(_Y * _X);
//
//	float4 UVScale = { 1.0f / static_cast<float>(_X), 1.0f / static_cast<float>(_Y) };
//
//	float4 Start = float4::Zero;
//
//	for (size_t y = 0; y < _Y; y++)
//	{
//		for (size_t x = 0; x < _X; x++)
//		{
//			size_t Index = (_X * y) + x;
//
//			Sprites[Index].Texture = Texture;
//			Sprites[Index].CutData.PosX = Start.x;
//			Sprites[Index].CutData.PosY = Start.y;
//			Sprites[Index].CutData.SizeX = UVScale.x;
//			Sprites[Index].CutData.SizeY = UVScale.y * (y + 1);
//			Start.x += UVScale.x;
//		}
//
//		Start.x = 0.0f;
//	}
//}
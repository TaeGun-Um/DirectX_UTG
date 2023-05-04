#include "PrecompileHeader.h"
#include "PixelCollision.h"

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineTexture.h>

PixelCollision::PixelCollision() 
{
}

PixelCollision::~PixelCollision() 
{
}

void PixelCollision::SetColMap(const std::shared_ptr<GameEngineTexture>& _ColMap, Coordinate _Pivot)
{
	GameEnginePixelColor DC(static_cast<char>(123), static_cast<char>(123), static_cast<char>(123), static_cast<char>(123));
	GameEnginePixelColor BC(static_cast<char>(0), static_cast<char>(0), static_cast<char>(0), static_cast<char>(255));
	
	DebugColor = DC;
	BlackColor = BC;

	ColMap = _ColMap;
	Pivot = _Pivot;

	Height = _ColMap->GetHeight();
	Width = _ColMap->GetWidth();

	Height_Half = static_cast<float>(Height / 2);
	Width_Half = static_cast<float>(Width / 2);
}

GameEnginePixelColor PixelCollision::PixelCheck(float4 _Value)
{
	if (nullptr == ColMap)
	{
		MsgAssert("SetColMap() �Լ��� ColMap�� �������� �ʰ� �ȼ� üũ�� �ǽ��Ϸ��� �߽��ϴ�.");
	}

	GameEnginePixelColor ColMapPixel;

	switch (Pivot)
	{
	case PixelCollision::Coordinate::Origin:
	{
		int ColCheckX = static_cast<int>(_Value.x + Width_Half);
		int ColCheckY = static_cast<int>(_Value.y - Height_Half);

		ColMapPixel = ColMap->GetPixel(ColCheckX, -ColCheckY, DebugColor);
	}
		break;
	case PixelCollision::Coordinate::Custom:
	{
		int ColCheckX = static_cast<int>(_Value.x + Width_Half);
		int ColCheckY = static_cast<int>(_Value.y - Height);

		ColMapPixel = ColMap->GetPixel(ColCheckX, -ColCheckY, DebugColor);
	}
		break;
	default:
		break;
	}

	return ColMapPixel;
}
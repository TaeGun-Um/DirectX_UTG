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

	Half_Height = static_cast<float>(Height / 2);
	Half_Width = static_cast<float>(Width / 2);
}

GameEnginePixelColor PixelCollision::PixelCheck(float4 _Value)
{
	if (nullptr == ColMap)
	{
		MsgAssert("SetColMap() 함수로 ColMap을 설정하지 않고 픽셀 체크를 실시하려고 했습니다.");
	}

	GameEnginePixelColor ColMapPixel;

	switch (Pivot)
	{
	case PixelCollision::Coordinate::Origin:
	{
		int ColCheckX = static_cast<int>(_Value.x + Half_Width);
		int ColCheckY = static_cast<int>(_Value.y - Half_Height);

		ColMapPixel = ColMap->GetPixel(ColCheckX, -ColCheckY, DebugColor);
	}
		break;
	case PixelCollision::Coordinate::Custom:
	{
		int ColCheckX = static_cast<int>(_Value.x + Half_Width);
		int ColCheckY = static_cast<int>(_Value.y - Height);

		ColMapPixel = ColMap->GetPixel(ColCheckX, -ColCheckY, DebugColor);
	}
		break;
	default:
		break;
	}

	return ColMapPixel;
}
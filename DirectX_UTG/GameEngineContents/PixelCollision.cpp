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
	GameEnginePixelColor BLC(static_cast<char>(0), static_cast<char>(0), static_cast<char>(255), static_cast<char>(255));
	
	DebugColor = DC;
	BlackColor = BC;
	BlueColor = BLC;

	ColMap = _ColMap;
	Pivot = _Pivot;

	Height = _ColMap->GetHeight();
	Width = _ColMap->GetWidth();

	Height_Half = static_cast<float>(Height / 2);
	Width_Half = static_cast<float>(Width / 2);
}

GameEnginePixelColor PixelCollision::PixelCheck(const float4& _Value)
{
	if (nullptr == ColMap)
	{
		MsgAssert("SetColMap() 함수로 ColMap을 설정하지 않고 픽셀 체크를 실시하려고 했습니다.");
	}

	GameEnginePixelColor ColMapPixel;

	switch (Pivot)
	{
	case PixelCollision::Coordinate::WindowOrigin:
	{
		int ColCheckX = static_cast<int>(_Value.x + Width_Half);
		int ColCheckY = static_cast<int>(_Value.y - Height_Half);

		ColMapPixel = ColMap->GetPixel(ColCheckX, -ColCheckY, DebugColor);
	}
		break;
	case PixelCollision::Coordinate::DirectOrigin:
	{
		// 중앙, Y만 0
		int ColCheckX = static_cast<int>(_Value.x + Width_Half);
		int ColCheckY = static_cast<int>(_Value.y - Height);

		ColMapPixel = ColMap->GetPixel(ColCheckX, -ColCheckY, DebugColor);
	}
	case PixelCollision::Coordinate::Custom:
	{
		// 왼쪽하단이 0, 0
		int ColCheckX = static_cast<int>(_Value.x);
		int ColCheckY = static_cast<int>(_Value.y - Height);

		ColMapPixel = ColMap->GetPixel(ColCheckX, -ColCheckY, DebugColor);
	}
		break;
	default:
		break;
	}

	return ColMapPixel;
}
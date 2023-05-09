#pragma once

#include <GameEngineCore/GameEngineTexture.h>

// Ό³Έν :
class PixelCollision
{
public:
	// constrcuter destructer
	PixelCollision();
	~PixelCollision();

	// delete Function
	PixelCollision(const PixelCollision& _Other) = delete;
	PixelCollision(PixelCollision&& _Other) noexcept = delete;
	PixelCollision& operator=(const PixelCollision& _Other) = delete;
	PixelCollision& operator=(PixelCollision&& _Other) noexcept = delete;

	enum class Coordinate
	{
		WindowOrigin,
		DirectOrigin,
		Custom
	};

	void SetColMap(const std::shared_ptr<GameEngineTexture>& _ColMap, Coordinate _Pivot);

	GameEnginePixelColor PixelCheck(const float4& _Value);

	bool IsBlack(GameEnginePixelColor _Pixel)
	{
		return BlackColor == _Pixel;
	}

	bool IsBlue(GameEnginePixelColor _Pixel)
	{
		return BlueColor == _Pixel;
	}

	float GetColMapHeight_Half()
	{
		return Height_Half;
	}

	float GetColMapWidth_Half()
	{
		return Width_Half;
	}

protected:

private:
	Coordinate Pivot = Coordinate::WindowOrigin;
	GameEnginePixelColor DebugColor;
	GameEnginePixelColor BlackColor;
	GameEnginePixelColor BlueColor;
	std::shared_ptr<class GameEngineTexture> ColMap = nullptr;
	int Height = 0;
	int Width = 0;

	float Height_Half = 0.0f;
	float Width_Half = 0.0f;

};


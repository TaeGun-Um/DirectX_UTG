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
		Origin,
		Custom
	};

	void SetColMap(const std::shared_ptr<GameEngineTexture>& _ColMap, Coordinate _Pivot);

	GameEnginePixelColor PixelCheck(float4 _Value);

	bool IsBlack(GameEnginePixelColor _Pixel)
	{
		return BlackColor == _Pixel;
	}

protected:

private:
	Coordinate Pivot = Coordinate::Origin;
	GameEnginePixelColor DebugColor;
	GameEnginePixelColor BlackColor;
	std::shared_ptr<class GameEngineTexture> ColMap = nullptr;
	int Height = 0;
	int Width = 0;

	float Half_Height = 0.0f;
	float Half_Width = 0.0f;

};


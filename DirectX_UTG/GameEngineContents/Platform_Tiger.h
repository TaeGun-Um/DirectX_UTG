#pragma once

// Ό³Έν :
class Platform_Tiger : public GameEngineActor
{
public:
	// constrcuter destructer
	Platform_Tiger();
	~Platform_Tiger();

	// delete Function
	Platform_Tiger(const Platform_Tiger& _Other) = delete;
	Platform_Tiger(Platform_Tiger&& _Other) noexcept = delete;
	Platform_Tiger& operator=(const Platform_Tiger& _Other) = delete;
	Platform_Tiger& operator=(Platform_Tiger&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
		StartPosition = GetTransform()->GetLocalPosition();
	}

	void SetColMap(const std::shared_ptr<GameEngineTexture>& _ColMap, PixelCollision::Coordinate _Pivot)
	{
		PixelCollisionCheck.SetColMap(_ColMap, _Pivot);
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> PlatformCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> HitCollisionRenderPtr = nullptr;

	std::shared_ptr<class GameEngineCollision> PlatformCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> HitCollisionPtr = nullptr;

	void PixelCheck(float _DeltaTime);
	void MoveDirection(float _DeltaTime);
	void DeathCheck();

	float4 StartPosition = float4::Zero;

	PixelCollision PixelCollisionCheck;
};


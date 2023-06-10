#pragma once

// Ό³Έν :
class Platform_Vipor : public GameEngineActor
{
public:
	// constrcuter destructer
	Platform_Vipor();
	~Platform_Vipor();

	// delete Function
	Platform_Vipor(const Platform_Vipor& _Other) = delete;
	Platform_Vipor(Platform_Vipor&& _Other) noexcept = delete;
	Platform_Vipor& operator=(const Platform_Vipor& _Other) = delete;
	Platform_Vipor& operator=(Platform_Vipor&& _Other) noexcept = delete;

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

	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr = nullptr;

	void PixelCheck(float _DeltaTime);
	void MoveDirection(float _DeltaTime);
	void DeathCheck();

	float4 StartPosition = float4::Zero;
	float4 MoveDirect = float4::Zero;

	PixelCollision PixelCollisionCheck;

	bool IsBoundEnd = false;

	int BoundCount = 0;
};


#pragma once

enum class WoodPieceState
{
	Loop,
	Death,
};

// Ό³Έν :
class WoodPiece : public GameEngineActor
{
public:
	// constrcuter destructer
	WoodPiece();
	~WoodPiece();

	// delete Function
	WoodPiece(const WoodPiece& _Other) = delete;
	WoodPiece(WoodPiece&& _Other) noexcept = delete;
	WoodPiece& operator=(const WoodPiece& _Other) = delete;
	WoodPiece& operator=(WoodPiece&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
	}

	void SetCollisionRenderOn()
	{
		ProjectileCollisionRenderPtr->On();
	}

	void SetCollisionRenderOff()
	{
		ProjectileCollisionRenderPtr->Off();
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
	std::shared_ptr<class GameEngineSpriteRenderer> ProjectileCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> ProjectileCollisionPtr = nullptr;
	
	void MoveDirection(float _DeltaTime);
	void PixelCheck(float _DeltaTime);

	PixelCollision PixelCollisionCheck;

	WoodPieceState StateValue = WoodPieceState::Loop;
	
	float4 MoveDirect = float4::Zero;

	bool IsDeath = false;

	void ChangeState(WoodPieceState _StateValue);
	void UpdateState(float _DeltaTime);

	void LoopStart();
	void LoopUpdate(float _DeltaTime);
	void LoopEnd();

	void DeathStart();
	void DeathUpdate(float _DeltaTime);
	void DeathEnd();
};


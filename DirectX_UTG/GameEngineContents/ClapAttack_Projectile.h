#pragma once

// Ό³Έν :
class ClapAttack_Projectile : public GameEngineActor
{
public:
	// constrcuter destructer
	ClapAttack_Projectile();
	~ClapAttack_Projectile();

	// delete Function
	ClapAttack_Projectile(const ClapAttack_Projectile& _Other) = delete;
	ClapAttack_Projectile(ClapAttack_Projectile&& _Other) noexcept = delete;
	ClapAttack_Projectile& operator=(const ClapAttack_Projectile& _Other) = delete;
	ClapAttack_Projectile& operator=(ClapAttack_Projectile&& _Other) noexcept = delete;

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

private:
	void CreateClapAttackSFX();
	void PixelCheck(float _DeltaTime);

	std::shared_ptr<GameEngineTexture> ColMap = nullptr;
	PixelCollision::Coordinate Pivot = PixelCollision::Coordinate::WindowOrigin;
	PixelCollision PixelCollisionCheck;

};


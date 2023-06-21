#pragma once

// Ό³Έν :
class GhostMouse_Projectile : public GameEngineActor
{
public:
	// constrcuter destructer
	GhostMouse_Projectile();
	~GhostMouse_Projectile();

	// delete Function
	GhostMouse_Projectile(const GhostMouse_Projectile& _Other) = delete;
	GhostMouse_Projectile(GhostMouse_Projectile&& _Other) noexcept = delete;
	GhostMouse_Projectile& operator=(const GhostMouse_Projectile& _Other) = delete;
	GhostMouse_Projectile& operator=(GhostMouse_Projectile&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
	}

	void SetCollisionRenderOn()
	{
		ProjectileCollisionRenderPtr->On();
		ParryCollisionRenderPtr->On();

		if (false == IsParryProjectile)
		{
			ParryCollisionRenderPtr->Off();
		}
	}

	void SetCollisionRenderOff()
	{
		ProjectileCollisionRenderPtr->Off();
		ParryCollisionRenderPtr->Off();
	}

	void SetParryBombCreate()
	{
		IsParryProjectile = true;
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
	std::shared_ptr<class GameEngineSpriteRenderer> ParryCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> ParryCollisionPtr = nullptr;

	float4 MoveDirect = float4::Zero;
	float MoveSpeed = 330.0f;

	bool IsDeath = false;
	bool IsParryProjectile = false;

	PixelCollision PixelCollisionCheck;

};


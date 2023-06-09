#pragma once

// Ό³Έν :
class DeathExplosion : public GameEngineActor
{
public:
	// constrcuter destructer
	DeathExplosion();
	~DeathExplosion();

	// delete Function
	DeathExplosion(const DeathExplosion& _Other) = delete;
	DeathExplosion(DeathExplosion&& _Other) noexcept = delete;
	DeathExplosion& operator=(const DeathExplosion& _Other) = delete;
	DeathExplosion& operator=(DeathExplosion&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;


};


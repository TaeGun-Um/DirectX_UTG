#pragma once

// Ό³Έν :
class CanExplosion_SFX : public GameEngineActor
{
public:
	// constrcuter destructer
	CanExplosion_SFX();
	~CanExplosion_SFX();

	// delete Function
	CanExplosion_SFX(const CanExplosion_SFX& _Other) = delete;
	CanExplosion_SFX(CanExplosion_SFX&& _Other) noexcept = delete;
	CanExplosion_SFX& operator=(const CanExplosion_SFX& _Other) = delete;
	CanExplosion_SFX& operator=(CanExplosion_SFX&& _Other) noexcept = delete;

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


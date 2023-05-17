#pragma once

// Ό³Έν :
class HitSFX : public GameEngineActor
{
public:
	// constrcuter destructer
	HitSFX();
	~HitSFX();

	// delete Function
	HitSFX(const HitSFX& _Other) = delete;
	HitSFX(HitSFX&& _Other) noexcept = delete;
	HitSFX& operator=(const HitSFX& _Other) = delete;
	HitSFX& operator=(HitSFX&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
	}

	void SetDirection(bool _Direction)
	{
		if (false == _Direction)
		{
			GetTransform()->SetLocalNegativeScaleX();
		}
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {};

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	void DeathCheck();

};


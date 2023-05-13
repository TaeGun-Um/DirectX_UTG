#pragma once

// Ό³Έν :
class LandDust : public GameEngineActor
{
public:
	// constrcuter destructer
	LandDust();
	~LandDust();

	// delete Function
	LandDust(const LandDust& _Other) = delete;
	LandDust(LandDust&& _Other) noexcept = delete;
	LandDust& operator=(const LandDust& _Other) = delete;
	LandDust& operator=(LandDust&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {};

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

	bool IsDeath = false;

	void DeathCheck();
};


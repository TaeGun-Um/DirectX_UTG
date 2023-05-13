#pragma once

// Ό³Έν :
class DashDust : public GameEngineActor
{
public:
	// constrcuter destructer
	DashDust();
	~DashDust();

	// delete Function
	DashDust(const DashDust& _Other) = delete;
	DashDust(DashDust&& _Other) noexcept = delete;
	DashDust& operator=(const DashDust& _Other) = delete;
	DashDust& operator=(DashDust&& _Other) noexcept = delete;

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


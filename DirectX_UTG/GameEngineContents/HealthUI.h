#pragma once

// Ό³Έν :
class HealthUI : public GameEngineActor
{
public:
	// constrcuter destructer
	HealthUI();
	~HealthUI();

	// delete Function
	HealthUI(const HealthUI& _Other) = delete;
	HealthUI(HealthUI&& _Other) noexcept = delete;
	HealthUI& operator=(const HealthUI& _Other) = delete;
	HealthUI& operator=(HealthUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

};


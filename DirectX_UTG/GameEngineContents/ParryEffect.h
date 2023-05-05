#pragma once

// Ό³Έν :
class ParryEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	ParryEffect();
	~ParryEffect();

	// delete Function
	ParryEffect(const ParryEffect& _Other) = delete;
	ParryEffect(ParryEffect&& _Other) noexcept = delete;
	ParryEffect& operator=(const ParryEffect& _Other) = delete;
	ParryEffect& operator=(ParryEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {};

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

};


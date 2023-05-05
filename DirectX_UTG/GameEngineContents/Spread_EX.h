#pragma once

// Ό³Έν :
class Spread_EX : public GameEngineActor
{
public:
	// constrcuter destructer
	Spread_EX();
	~Spread_EX();

	// delete Function
	Spread_EX(const Spread_EX& _Other) = delete;
	Spread_EX(Spread_EX&& _Other) noexcept = delete;
	Spread_EX& operator=(const Spread_EX& _Other) = delete;
	Spread_EX& operator=(Spread_EX&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {};

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

};


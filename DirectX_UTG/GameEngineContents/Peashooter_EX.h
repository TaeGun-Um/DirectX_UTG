#pragma once

// Ό³Έν :
class Peashooter_EX : public GameEngineActor
{
public:
	// constrcuter destructer
	Peashooter_EX();
	~Peashooter_EX();

	// delete Function
	Peashooter_EX(const Peashooter_EX& _Other) = delete;
	Peashooter_EX(Peashooter_EX&& _Other) noexcept = delete;
	Peashooter_EX& operator=(const Peashooter_EX& _Other) = delete;
	Peashooter_EX& operator=(Peashooter_EX&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {};

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

};


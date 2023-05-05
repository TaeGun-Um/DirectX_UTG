#pragma once

// Ό³Έν :
class Peashooter : public GameEngineActor
{
public:
	// constrcuter destructer
	Peashooter();
	~Peashooter();

	// delete Function
	Peashooter(const Peashooter& _Other) = delete;
	Peashooter(Peashooter&& _Other) noexcept = delete;
	Peashooter& operator=(const Peashooter& _Other) = delete;
	Peashooter& operator=(Peashooter&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {};

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

};


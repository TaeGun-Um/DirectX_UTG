#pragma once

// Ό³Έν :
class Frog_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Frog_Map();
	~Frog_Map();

	// delete Function
	Frog_Map(const Frog_Map& _Other) = delete;
	Frog_Map(Frog_Map&& _Other) noexcept = delete;
	Frog_Map& operator=(const Frog_Map& _Other) = delete;
	Frog_Map& operator=(Frog_Map&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BGRenderPtr_1 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BGRenderPtr_2 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BGRenderPtr_3 = nullptr;

};


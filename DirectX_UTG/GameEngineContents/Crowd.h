#pragma once

// Ό³Έν :
class Crowd : public GameEngineActor
{
public:
	// constrcuter destructer
	Crowd();
	~Crowd();

	// delete Function
	Crowd(const Crowd& _Other) = delete;
	Crowd(Crowd&& _Other) noexcept = delete;
	Crowd& operator=(const Crowd& _Other) = delete;
	Crowd& operator=(Crowd&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

};


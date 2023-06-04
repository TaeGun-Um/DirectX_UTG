#pragma once

// Ό³Έν :
class Dancer : public GameEngineActor
{
public:
	// constrcuter destructer
	Dancer();
	~Dancer();

	// delete Function
	Dancer(const Dancer& _Other) = delete;
	Dancer(Dancer&& _Other) noexcept = delete;
	Dancer& operator=(const Dancer& _Other) = delete;
	Dancer& operator=(Dancer&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

};


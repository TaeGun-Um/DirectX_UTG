#pragma once

// Ό³Έν :
class Cheerer : public GameEngineActor
{
public:
	// constrcuter destructer
	Cheerer();
	~Cheerer();

	// delete Function
	Cheerer(const Cheerer& _Other) = delete;
	Cheerer(Cheerer&& _Other) noexcept = delete;
	Cheerer& operator=(const Cheerer& _Other) = delete;
	Cheerer& operator=(Cheerer&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

};


#pragma once

// Ό³Έν :
class Craber : public GameEngineActor
{
public:
	// constrcuter destructer
	Craber();
	~Craber();

	// delete Function
	Craber(const Craber& _Other) = delete;
	Craber(Craber&& _Other) noexcept = delete;
	Craber& operator=(const Craber& _Other) = delete;
	Craber& operator=(Craber&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

};


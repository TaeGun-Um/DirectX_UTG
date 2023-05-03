#pragma once

// Ό³Έν :
class Overworld_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Overworld_Map();
	~Overworld_Map();

	// delete Function
	Overworld_Map(const Overworld_Map& _Other) = delete;
	Overworld_Map(Overworld_Map&& _Other) noexcept = delete;
	Overworld_Map& operator=(const Overworld_Map& _Other) = delete;
	Overworld_Map& operator=(Overworld_Map&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr;

};

#pragma once

// Ό³Έν :
class Tutorial_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Tutorial_Map();
	~Tutorial_Map();

	// delete Function
	Tutorial_Map(const Tutorial_Map& _Other) = delete;
	Tutorial_Map(Tutorial_Map&& _Other) noexcept = delete;
	Tutorial_Map& operator=(const Tutorial_Map& _Other) = delete;
	Tutorial_Map& operator=(Tutorial_Map&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr;

};


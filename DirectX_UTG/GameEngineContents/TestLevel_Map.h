#pragma once

// Ό³Έν :
class TestLevel_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	TestLevel_Map();
	~TestLevel_Map();

	// delete Function
	TestLevel_Map(const TestLevel_Map& _Other) = delete;
	TestLevel_Map(TestLevel_Map&& _Other) noexcept = delete;
	TestLevel_Map& operator=(const TestLevel_Map& _Other) = delete;
	TestLevel_Map& operator=(TestLevel_Map&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr;

};


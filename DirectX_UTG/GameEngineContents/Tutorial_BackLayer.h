#pragma once

// Ό³Έν :
class Tutorial_BackLayer : public GameEngineActor
{
public:
	// constrcuter destructer
	Tutorial_BackLayer();
	~Tutorial_BackLayer();

	// delete Function
	Tutorial_BackLayer(const Tutorial_BackLayer& _Other) = delete;
	Tutorial_BackLayer(Tutorial_BackLayer&& _Other) noexcept = delete;
	Tutorial_BackLayer& operator=(const Tutorial_BackLayer& _Other) = delete;
	Tutorial_BackLayer& operator=(Tutorial_BackLayer&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr;

};


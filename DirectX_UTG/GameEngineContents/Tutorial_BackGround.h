#pragma once

// Ό³Έν :
class Tutorial_BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	Tutorial_BackGround();
	~Tutorial_BackGround();

	// delete Function
	Tutorial_BackGround(const Tutorial_BackGround& _Other) = delete;
	Tutorial_BackGround(Tutorial_BackGround&& _Other) noexcept = delete;
	Tutorial_BackGround& operator=(const Tutorial_BackGround& _Other) = delete;
	Tutorial_BackGround& operator=(Tutorial_BackGround&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr;

};


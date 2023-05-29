#pragma once

// Ό³Έν :
class Title_Background : public GameEngineActor
{
public:
	// constrcuter destructer
	Title_Background();
	~Title_Background();

	// delete Function
	Title_Background(const Title_Background& _Other) = delete;
	Title_Background(Title_Background&& _Other) noexcept = delete;
	Title_Background& operator=(const Title_Background& _Other) = delete;
	Title_Background& operator=(Title_Background&& _Other) noexcept = delete;

	void SetRenderOff()
	{
		RenderPtr0->Off();
		RenderPtr1->Off();
		RenderPtr2->Off();
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr0 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr1 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr2 = nullptr;

	float KeyRenderTime = 0.0f;
};

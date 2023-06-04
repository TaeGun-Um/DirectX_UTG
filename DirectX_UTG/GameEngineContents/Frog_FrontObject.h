#pragma once

// Ό³Έν :
class Frog_FrontObject : public GameEngineActor
{
public:
	// constrcuter destructer
	Frog_FrontObject();
	~Frog_FrontObject();

	// delete Function
	Frog_FrontObject(const Frog_FrontObject& _Other) = delete;
	Frog_FrontObject(Frog_FrontObject&& _Other) noexcept = delete;
	Frog_FrontObject& operator=(const Frog_FrontObject& _Other) = delete;
	Frog_FrontObject& operator=(Frog_FrontObject&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> FrontRenderPtr_1 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> FrontRenderPtr_2 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> FrontRenderPtr_3 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> FrontRenderPtr_4 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> FrontRenderPtr_5 = nullptr;

};


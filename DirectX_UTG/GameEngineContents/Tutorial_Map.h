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
	std::shared_ptr<class GameEngineSpriteRenderer> PlatformCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> PlatformCollisionPtr = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> ParrySpotCollisionRenderPtr0 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ParrySpotCollisionRenderPtr1 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ParrySpotCollisionRenderPtr2 = nullptr;
	std::shared_ptr<class GameEngineCollision> ParrySpotCollisionPtr0 = nullptr;
	std::shared_ptr<class GameEngineCollision> ParrySpotCollisionPtr1 = nullptr;
	std::shared_ptr<class GameEngineCollision> ParrySpotCollisionPtr2 = nullptr;

	void Step_1();
	void Step_2();
	void Step_3();
};


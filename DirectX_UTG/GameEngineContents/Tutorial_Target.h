#pragma once

// Ό³Έν :
class Tutorial_Target : public GameEngineActor
{
public:
	// constrcuter destructer
	Tutorial_Target();
	~Tutorial_Target();

	// delete Function
	Tutorial_Target(const Tutorial_Target& _Other) = delete;
	Tutorial_Target(Tutorial_Target&& _Other) noexcept = delete;
	Tutorial_Target& operator=(const Tutorial_Target& _Other) = delete;
	Tutorial_Target& operator=(Tutorial_Target&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BoxRenderPtr;
	std::shared_ptr<class GameEngineSpriteRenderer> TargetRenderPtr;
	std::shared_ptr<class GameEngineCollision> TargetCollisionPtr;
	std::shared_ptr<class GameEngineCollision> BoxCollisionPtr;
	std::shared_ptr<class GameEngineSpriteRenderer> TargetCollisionRenderPtr;
	std::shared_ptr<class GameEngineSpriteRenderer> BoxCollisionRenderPtr;

};


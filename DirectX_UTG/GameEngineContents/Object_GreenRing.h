#pragma once

// Ό³Έν :
class Object_GreenRing : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_GreenRing();
	~Object_GreenRing();

	// delete Function
	Object_GreenRing(const Object_GreenRing& _Other) = delete;
	Object_GreenRing(Object_GreenRing&& _Other) noexcept = delete;
	Object_GreenRing& operator=(const Object_GreenRing& _Other) = delete;
	Object_GreenRing& operator=(Object_GreenRing&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BodyCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> BodyCollisionPtr = nullptr;

};


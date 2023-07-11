#pragma once

// Ό³Έν :
class Object_Tail : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_Tail();
	~Object_Tail();

	// delete Function
	Object_Tail(const Object_Tail& _Other) = delete;
	Object_Tail(Object_Tail&& _Other) noexcept = delete;
	Object_Tail& operator=(const Object_Tail& _Other) = delete;
	Object_Tail& operator=(Object_Tail&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BodyCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> BodyCollisionPtr = nullptr;

};


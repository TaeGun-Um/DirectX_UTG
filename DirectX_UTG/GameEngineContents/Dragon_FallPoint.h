#pragma once

// Ό³Έν :
class Dragon_FallPoint : public GameEngineActor
{
public:
	// constrcuter destructer
	Dragon_FallPoint();
	~Dragon_FallPoint();

	// delete Function
	Dragon_FallPoint(const Dragon_FallPoint& _Other) = delete;
	Dragon_FallPoint(Dragon_FallPoint&& _Other) noexcept = delete;
	Dragon_FallPoint& operator=(const Dragon_FallPoint& _Other) = delete;
	Dragon_FallPoint& operator=(Dragon_FallPoint&& _Other) noexcept = delete;

	void DebugRenderOn()
	{
		IsDebugRender = true;
	}

	void DebugRenderOff()
	{
		IsDebugRender = false;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> CollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> CollisionPtr = nullptr;

	bool IsDebugRender = false;

};


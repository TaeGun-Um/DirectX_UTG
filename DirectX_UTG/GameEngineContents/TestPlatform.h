#pragma once

// 설명 :
class TestPlatform : public GameEngineActor
{
public:
	// constrcuter destructer
	TestPlatform();
	~TestPlatform();

	// delete Function
	TestPlatform(const TestPlatform& _Other) = delete;
	TestPlatform(TestPlatform&& _Other) noexcept = delete;
	TestPlatform& operator=(const TestPlatform& _Other) = delete;
	TestPlatform& operator=(TestPlatform&& _Other) noexcept = delete;

	// 지울것
	std::shared_ptr<class GameEngineSpriteRenderer> GetCollisionRenderPtr()
	{
		return CollisionRenderPtr;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr;
	std::shared_ptr<class GameEngineCollision> CollisionPtr;
	std::shared_ptr<class GameEngineSpriteRenderer> CollisionRenderPtr;

};


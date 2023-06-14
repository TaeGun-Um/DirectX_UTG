#pragma once

// Ό³Έν :
class CatapultProjectile : public GameEngineActor
{
public:
	// constrcuter destructer
	CatapultProjectile();
	~CatapultProjectile();

	// delete Function
	CatapultProjectile(const CatapultProjectile& _Other) = delete;
	CatapultProjectile(CatapultProjectile&& _Other) noexcept = delete;
	CatapultProjectile& operator=(const CatapultProjectile& _Other) = delete;
	CatapultProjectile& operator=(CatapultProjectile&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

};


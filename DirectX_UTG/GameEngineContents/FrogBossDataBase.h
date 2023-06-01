#pragma once

// Ό³Έν :
class FrogBossDataBase : public GameEngineActor
{
public:
	// constrcuter destructer
	FrogBossDataBase();
	~FrogBossDataBase();

	// delete Function
	FrogBossDataBase(const FrogBossDataBase& _Other) = delete;
	FrogBossDataBase(FrogBossDataBase&& _Other) noexcept = delete;
	FrogBossDataBase& operator=(const FrogBossDataBase& _Other) = delete;
	FrogBossDataBase& operator=(FrogBossDataBase&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

};


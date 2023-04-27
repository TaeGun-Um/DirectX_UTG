#pragma once

// Ό³Έν :
class FrogLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	FrogLevel();
	~FrogLevel();

	// delete Function
	FrogLevel(const FrogLevel& _Other) = delete;
	FrogLevel(FrogLevel&& _Other) noexcept = delete;
	FrogLevel& operator=(const FrogLevel& _Other) = delete;
	FrogLevel& operator=(FrogLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:

};


#pragma once

// Ό³Έν :
class Second_OpeningLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	Second_OpeningLevel();
	~Second_OpeningLevel();

	// delete Function
	Second_OpeningLevel(const Second_OpeningLevel& _Other) = delete;
	Second_OpeningLevel(Second_OpeningLevel&& _Other) noexcept = delete;
	Second_OpeningLevel& operator=(const Second_OpeningLevel& _Other) = delete;
	Second_OpeningLevel& operator=(Second_OpeningLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:

};


#pragma once

// Ό³Έν :
class First_OpeningLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	First_OpeningLevel();
	~First_OpeningLevel();

	// delete Function
	First_OpeningLevel(const First_OpeningLevel& _Other) = delete;
	First_OpeningLevel(First_OpeningLevel&& _Other) noexcept = delete;
	First_OpeningLevel& operator=(const First_OpeningLevel& _Other) = delete;
	First_OpeningLevel& operator=(First_OpeningLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:

};


#pragma once

enum class LevelValue
{
	First_OpeningLevel,
	Second_OpeningLevel,
	WaitingRoomLevel,
	TutorialLevel,
	OverworldLevel,
	FrogLevel,
	DragonLevel,
	MouseLevel,
	EndingLevel,
};

// 설명 :
class LoadingLevel : public GameEngineLevel
{
public:
	static LoadingLevel* LoadingLevelPtr;

	// constrcuter destructer
	LoadingLevel();
	~LoadingLevel();

	// delete Function
	LoadingLevel(const LoadingLevel& _Other) = delete;
	LoadingLevel(LoadingLevel&& _Other) noexcept = delete;
	LoadingLevel& operator=(const LoadingLevel& _Other) = delete;
	LoadingLevel& operator=(LoadingLevel&& _Other) noexcept = delete;

	void SetLevelState(LevelValue _Value)
	{
		LevelState = _Value;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class Loading> LoadingObject = nullptr;

	LevelValue LevelState = LevelValue::First_OpeningLevel;

	float EndTime = 0.0f; // 테스트

	void LevelChange();

	void OpeningTexture();
	void WaitingTexture();
	void TutorialTexture();
	void OverworldTexture();
	void FrogTexture();
	void MouseTexture();
	void DragonTexture();
	void EndingTexture();
};


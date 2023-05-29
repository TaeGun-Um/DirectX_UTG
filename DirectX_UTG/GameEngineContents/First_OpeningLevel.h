#pragma once

// Ό³Έν :
class First_OpeningLevel : public GameEngineLevel
{
public:
	static First_OpeningLevel* First_OpeningLevelPtr;

	// constrcuter destructer
	First_OpeningLevel();
	~First_OpeningLevel();

	// delete Function
	First_OpeningLevel(const First_OpeningLevel& _Other) = delete;
	First_OpeningLevel(First_OpeningLevel&& _Other) noexcept = delete;
	First_OpeningLevel& operator=(const First_OpeningLevel& _Other) = delete;
	First_OpeningLevel& operator=(First_OpeningLevel&& _Other) noexcept = delete;

	bool GetIsTitleMove()
	{
		return TitleMove;
	}

	std::shared_ptr<class RoundBlackBox> GetBlackBoxPtr()
	{
		return BlackBoxPtr;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class Loading> LoadingPtr = nullptr;
	std::shared_ptr<class RoundBlackBox> BlackBoxPtr = nullptr;
	std::shared_ptr<class Title_Background> BackgroundObject = nullptr;
	std::shared_ptr<class TitleMenu> TitleMenuObject = nullptr;

	bool NextStep1 = false;
	int NextStep1Count = 1;
	bool NextStep2 = false;
	int NextStep2Count = 1;

	bool TitleMove = false;
	bool EndStep = false;
	bool StartStep = false;
	float AccessTime = 0.0f;

};


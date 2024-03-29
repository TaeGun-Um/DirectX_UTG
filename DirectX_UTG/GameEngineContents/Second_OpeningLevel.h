#pragma once

// ���� :
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

	void ReLoadSetting();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	GameEngineSoundPlayer BGMPlayer;
	GameEngineSoundPlayer EffectPlayer;

	bool IsBGMOn = false;

	std::shared_ptr<class RoundBlackBox> BlackBoxPtr = nullptr;
	std::shared_ptr<class BookRender> BookRenderObject = nullptr;

	bool IsEnd = false;
};


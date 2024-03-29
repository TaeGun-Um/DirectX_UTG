#pragma once

// ���� :
class EndingLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	EndingLevel();
	~EndingLevel();

	// delete Function
	EndingLevel(const EndingLevel& _Other) = delete;
	EndingLevel(EndingLevel&& _Other) noexcept = delete;
	EndingLevel& operator=(const EndingLevel& _Other) = delete;
	EndingLevel& operator=(EndingLevel&& _Other) noexcept = delete;

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
	std::shared_ptr<class BookEndRender> BookRenderObject = nullptr;

	bool IsEnd = false;

};


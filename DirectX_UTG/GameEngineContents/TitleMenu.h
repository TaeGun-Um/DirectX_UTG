#pragma once

// Ό³Έν :
class TitleMenu : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleMenu();
	~TitleMenu();

	// delete Function
	TitleMenu(const TitleMenu& _Other) = delete;
	TitleMenu(TitleMenu&& _Other) noexcept = delete;
	TitleMenu& operator=(const TitleMenu& _Other) = delete;
	TitleMenu& operator=(TitleMenu&& _Other) noexcept = delete;

	bool GetIsStart()
	{
		return IsStart;
	}

	bool GetIsEnd()
	{
		return IsEnd;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BGRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> StartRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> EndRenderPtr = nullptr;

	GameEngineSoundPlayer EffectPlayer;
	bool IsSound = false;

	int SelectCount = 0;
	float SelectColor = 1.0f;
	float NoneColor = 0.3f;
	float Delaytiem = 0.0f;

	bool IsStart = false;
	bool IsEnd = false;
};


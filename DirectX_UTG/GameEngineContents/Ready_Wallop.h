#pragma once

// Ό³Έν :
class Ready_Wallop : public GameEngineActor
{
public:
	// constrcuter destructer
	Ready_Wallop();
	~Ready_Wallop();

	// delete Function
	Ready_Wallop(const Ready_Wallop& _Other) = delete;
	Ready_Wallop(Ready_Wallop&& _Other) noexcept = delete;
	Ready_Wallop& operator=(const Ready_Wallop& _Other) = delete;
	Ready_Wallop& operator=(Ready_Wallop&& _Other) noexcept = delete;

	void StartMessage()
	{
		RenderPtr->ChangeAnimation("Ready_Wallop");
		RenderPtr->On();
	}

	bool GetIsEnd()
	{
		return IsEnd;
	}

	void MessageReset()
	{
		RenderPtr->ChangeAnimation("Ready_Wallop");
		RenderPtr->Off();
		IsEnd = false;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	GameEngineSoundPlayer VoicePlayer;

	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	bool IsEnd = false;

	void StartVoiceSound();
	void EndVoiceSound();
};


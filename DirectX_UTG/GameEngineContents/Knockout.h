#pragma once

// Ό³Έν :
class Knockout : public GameEngineActor
{
public:
	// constrcuter destructer
	Knockout();
	~Knockout();

	// delete Function
	Knockout(const Knockout& _Other) = delete;
	Knockout(Knockout&& _Other) noexcept = delete;
	Knockout& operator=(const Knockout& _Other) = delete;
	Knockout& operator=(Knockout&& _Other) noexcept = delete;

	void StartMessage()
	{
		RenderPtr->ChangeAnimation("KNOCKOUT");
		RenderPtr->On();
	}

	bool GetIsEnd()
	{
		return IsEnd;
	}

	void MessageReset()
	{
		RenderPtr->ChangeAnimation("KNOCKOUT");
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

	void KnockSound();
	void KnockBellSound();
};


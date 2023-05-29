#pragma once

// Ό³Έν :
class RoundBlackBox : public GameEngineActor
{
public:
	// constrcuter destructer
	RoundBlackBox();
	~RoundBlackBox();

	// delete Function
	RoundBlackBox(const RoundBlackBox& _Other) = delete;
	RoundBlackBox(RoundBlackBox&& _Other) noexcept = delete;
	RoundBlackBox& operator=(const RoundBlackBox& _Other) = delete;
	RoundBlackBox& operator=(RoundBlackBox&& _Other) noexcept = delete;

	void SetEnter()
	{
		RenderPtr->ChangeAnimation("Enter");
		RenderPtr->On();
	}

	void SetExit()
	{
		RenderPtr->ChangeAnimation("Exit");
		RenderPtr->On();
	}

	bool GetIsEnd()
	{
		return IsEnd;
	}

	void BoxSettingReset()
	{
		RenderPtr->ChangeAnimation("Enter");
		RenderPtr->Off();
		IsEnd = false;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr;
	bool IsEnd = false;
};


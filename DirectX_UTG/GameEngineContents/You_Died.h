#pragma once

// Ό³Έν :
class You_Died : public GameEngineActor
{
public:
	// constrcuter destructer
	You_Died();
	~You_Died();

	// delete Function
	You_Died(const You_Died& _Other) = delete;
	You_Died(You_Died&& _Other) noexcept = delete;
	You_Died& operator=(const You_Died& _Other) = delete;
	You_Died& operator=(You_Died&& _Other) noexcept = delete;

	void StartMessage()
	{
		RenderPtr->ChangeAnimation("YOU_DIED");
		RenderPtr->On();
	}

	bool GetIsEnd()
	{
		return IsEnd;
	}

	void MessageReset()
	{
		RenderPtr->ChangeAnimation("YOU_DIED");
		RenderPtr->Off();
		IsEnd = false;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	bool IsEnd = false;

};


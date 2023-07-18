#pragma once

// Ό³Έν :
class Opening_BlackBox : public GameEngineActor
{
public:
	// constrcuter destructer
	Opening_BlackBox();
	~Opening_BlackBox();

	// delete Function
	Opening_BlackBox(const Opening_BlackBox& _Other) = delete;
	Opening_BlackBox(Opening_BlackBox&& _Other) noexcept = delete;
	Opening_BlackBox& operator=(const Opening_BlackBox& _Other) = delete;
	Opening_BlackBox& operator=(Opening_BlackBox&& _Other) noexcept = delete;

	bool GetIsEnd()
	{
		return IsEnd;
	}

	void SetDelayTimeZero()
	{
		DelayTime = 0.0f;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	GameEngineSoundPlayer BGMPlayer;

	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

	float DelayTime = 0.0f;

	bool IsEnd = false;
	bool IsBGMOn = false;
	bool IsLogoBGM = false;

};


#pragma once

// Ό³Έν :
class HourGlass : public GameEngineActor
{
public:
	// constrcuter destructer
	HourGlass();
	~HourGlass();

	// delete Function
	HourGlass(const HourGlass& _Other) = delete;
	HourGlass(HourGlass&& _Other) noexcept = delete;
	HourGlass& operator=(const HourGlass& _Other) = delete;
	HourGlass& operator=(HourGlass&& _Other) noexcept = delete;

	void SetStart()
	{
		IsStart = true;
	}

	void SetEnd()
	{
		IsEnd = true;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

	float FadeTime = 0.0f;
	bool IsStart = false;
	bool IsEnd = false;

	void FadeIn(float _DeltaTime);
	void FadeOut(float _DeltaTime);
};


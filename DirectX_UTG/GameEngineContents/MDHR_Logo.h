#pragma once

// Ό³Έν :
class MDHR_Logo : public GameEngineActor
{
public:
	static MDHR_Logo* LogoPtr;

	// constrcuter destructer
	MDHR_Logo();
	~MDHR_Logo();

	// delete Function
	MDHR_Logo(const MDHR_Logo& _Other) = delete;
	MDHR_Logo(MDHR_Logo&& _Other) noexcept = delete;
	MDHR_Logo& operator=(const MDHR_Logo& _Other) = delete;
	MDHR_Logo& operator=(MDHR_Logo&& _Other) noexcept = delete;

	static bool GetLogoAnimationIsEnd()
	{
		return IsEnd;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	static bool IsEnd;
};


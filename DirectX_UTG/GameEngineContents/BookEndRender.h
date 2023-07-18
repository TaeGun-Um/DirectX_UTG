#pragma once

// Ό³Έν :
class BookEndRender : public GameEngineActor
{
public:
	static BookEndRender* BookEndRenderPtr;

	// constrcuter destructer
	BookEndRender();
	~BookEndRender();

	// delete Function
	BookEndRender(const BookEndRender& _Other) = delete;
	BookEndRender(BookEndRender&& _Other) noexcept = delete;
	BookEndRender& operator=(const BookEndRender& _Other) = delete;
	BookEndRender& operator=(BookEndRender&& _Other) noexcept = delete;

	static bool GetBookAnimationIsEnd()
	{
		return IsEnd;
	}

	void BookRenderEndReset()
	{
		IsEnd = false;
		Page = 0;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	GameEngineSoundPlayer EffectPlayer;

	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ArrowRenderPtr = nullptr;

	int Page = 0;
	static bool IsEnd;
	
	void EndingCherringSound();
	void RandPageturnSound();
	void HBSCControl(std::shared_ptr<class GameEngineSpriteRenderer> _Object, float _saturation, float _brightness, float _contrast);

};


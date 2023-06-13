#pragma once

// Ό³Έν :
class BookRender : public GameEngineActor
{
public:
	static BookRender* BookRenderPtr;
	
	// constrcuter destructer
	BookRender();
	~BookRender();

	// delete Function
	BookRender(const BookRender& _Other) = delete;
	BookRender(BookRender&& _Other) noexcept = delete;
	BookRender& operator=(const BookRender& _Other) = delete;
	BookRender& operator=(BookRender&& _Other) noexcept = delete;

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
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ArrowRenderPtr = nullptr;
	
	int Page = 0;
	static bool IsEnd;

	void HBSCControl(std::shared_ptr<class GameEngineSpriteRenderer> _Object, float _saturation, float _brightness, float _contrast);
};


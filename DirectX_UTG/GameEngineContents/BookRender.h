#pragma once

// Ό³Έν :
class BookRender : public GameEngineActor
{
public:
	// constrcuter destructer
	BookRender();
	~BookRender();

	// delete Function
	BookRender(const BookRender& _Other) = delete;
	BookRender(BookRender&& _Other) noexcept = delete;
	BookRender& operator=(const BookRender& _Other) = delete;
	BookRender& operator=(BookRender&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr;

};


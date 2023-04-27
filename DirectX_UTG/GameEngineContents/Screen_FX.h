#pragma once

// Ό³Έν :
class Screen_FX : public GameEngineActor
{
public:
	// constrcuter destructer
	Screen_FX();
	~Screen_FX();

	// delete Function
	Screen_FX(const Screen_FX& _Other) = delete;
	Screen_FX(Screen_FX&& _Other) noexcept = delete;
	Screen_FX& operator=(const Screen_FX& _Other) = delete;
	Screen_FX& operator=(Screen_FX&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr;

};


#pragma once

// Ό³Έν :
class GrimMatchstick : public GameEngineActor
{
public:
	// constrcuter destructer
	GrimMatchstick();
	~GrimMatchstick();

	// delete Function
	GrimMatchstick(const GrimMatchstick& _Other) = delete;
	GrimMatchstick(GrimMatchstick&& _Other) noexcept = delete;
	GrimMatchstick& operator=(const GrimMatchstick& _Other) = delete;
	GrimMatchstick& operator=(GrimMatchstick&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

};


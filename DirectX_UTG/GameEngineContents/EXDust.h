#pragma once

// Ό³Έν :
class EXDust : public GameEngineActor
{
public:
	// constrcuter destructer
	EXDust();
	~EXDust();

	// delete Function
	EXDust(const EXDust& _Other) = delete;
	EXDust(EXDust&& _Other) noexcept = delete;
	EXDust& operator=(const EXDust& _Other) = delete;
	EXDust& operator=(EXDust&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {};

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

};


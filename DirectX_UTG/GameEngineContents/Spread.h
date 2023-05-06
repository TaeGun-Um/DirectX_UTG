#pragma once

// Ό³Έν :
class Spread : public GameEngineActor
{
public:
	// constrcuter destructer
	Spread();
	~Spread();

	// delete Function
	Spread(const Spread& _Other) = delete;
	Spread(Spread&& _Other) noexcept = delete;
	Spread& operator=(const Spread& _Other) = delete;
	Spread& operator=(Spread&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {};

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

	float4 InitPlayerPosition = float4::Zero;
	float InitPlayerXPosition = 0.0f;
	float MoveSpeed = 450.0f;
	bool Direction = true;   // true == Right // false == Left

};


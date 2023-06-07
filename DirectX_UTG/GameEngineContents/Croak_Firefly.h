#pragma once

// Ό³Έν :
class Croak_Firefly : public GameEngineActor
{
public:
	// constrcuter destructer
	Croak_Firefly();
	~Croak_Firefly();

	// delete Function
	Croak_Firefly(const Croak_Firefly& _Other) = delete;
	Croak_Firefly(Croak_Firefly&& _Other) noexcept = delete;
	Croak_Firefly& operator=(const Croak_Firefly& _Other) = delete;
	Croak_Firefly& operator=(Croak_Firefly&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

};


#pragma once

// Ό³Έν :
class Cat_DeathDust : public GameEngineActor
{
public:
	// constrcuter destructer
	Cat_DeathDust();
	~Cat_DeathDust();

	// delete Function
	Cat_DeathDust(const Cat_DeathDust& _Other) = delete;
	Cat_DeathDust(Cat_DeathDust&& _Other) noexcept = delete;
	Cat_DeathDust& operator=(const Cat_DeathDust& _Other) = delete;
	Cat_DeathDust& operator=(Cat_DeathDust&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetWorldPosition(_PlayerPosition);
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

};


#pragma once

// Ό³Έν :
class MoveDust : public GameEngineActor
{
public:
	// constrcuter destructer
	MoveDust();
	~MoveDust();

	// delete Function
	MoveDust(const MoveDust& _Other) = delete;
	MoveDust(MoveDust&& _Other) noexcept = delete;
	MoveDust& operator=(const MoveDust& _Other) = delete;
	MoveDust& operator=(MoveDust&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {};

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

	bool IsDeath = false;

	void DeathCheck();

};


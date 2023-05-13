#pragma once

enum class DustType
{
	A,
	B,
	C
};

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

	void SetDirection(bool _Direction)
	{
		if (false == _Direction)
		{
			GetTransform()->SetLocalNegativeScaleX();
		}
	}

	void SetDustType(DustType _Type);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {};

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	DustType Type = DustType::A;
	void DeathCheck();

};


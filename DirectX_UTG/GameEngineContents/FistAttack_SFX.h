#pragma once

// Ό³Έν :
class FistAttack_SFX : public GameEngineActor
{
public:
	// constrcuter destructer
	FistAttack_SFX();
	~FistAttack_SFX();

	// delete Function
	FistAttack_SFX(const FistAttack_SFX& _Other) = delete;
	FistAttack_SFX(FistAttack_SFX&& _Other) noexcept = delete;
	FistAttack_SFX& operator=(const FistAttack_SFX& _Other) = delete;
	FistAttack_SFX& operator=(FistAttack_SFX&& _Other) noexcept = delete;

	void SetDirection(bool _Direction)
	{
		if (false == _Direction)
		{
			GetTransform()->SetLocalNegativeScaleX();
		}
	}

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

};


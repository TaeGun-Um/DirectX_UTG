#pragma once

// ���� :
class ParryEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	ParryEffect();
	~ParryEffect();

	// delete Function
	ParryEffect(const ParryEffect& _Other) = delete;
	ParryEffect(ParryEffect&& _Other) noexcept = delete;
	ParryEffect& operator=(const ParryEffect& _Other) = delete;
	ParryEffect& operator=(ParryEffect&& _Other) noexcept = delete;

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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {};

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

	bool IsDeath = false;

	void DeathCheck();

};


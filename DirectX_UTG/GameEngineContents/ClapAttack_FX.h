#pragma once

// Ό³Έν :
class ClapAttack_FX : public GameEngineActor
{
public:
	// constrcuter destructer
	ClapAttack_FX();
	~ClapAttack_FX();

	// delete Function
	ClapAttack_FX(const ClapAttack_FX& _Other) = delete;
	ClapAttack_FX(ClapAttack_FX&& _Other) noexcept = delete;
	ClapAttack_FX& operator=(const ClapAttack_FX& _Other) = delete;
	ClapAttack_FX& operator=(ClapAttack_FX&& _Other) noexcept = delete;

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


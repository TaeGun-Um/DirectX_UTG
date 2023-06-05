#pragma once

// Ό³Έν :
class WeaponUI : public GameEngineActor
{
public:
	// constrcuter destructer
	WeaponUI();
	~WeaponUI();

	// delete Function
	WeaponUI(const WeaponUI& _Other) = delete;
	WeaponUI(WeaponUI&& _Other) noexcept = delete;
	WeaponUI& operator=(const WeaponUI& _Other) = delete;
	WeaponUI& operator=(WeaponUI&& _Other) noexcept = delete;

	void SetMainPalyer(std::shared_ptr<class Player> _MainPlayer);

	void StartPositionSetting(float4 _Value)
	{
		StartPosition = _Value;
		EndPosition = StartPosition + float4{ 0, 55 };
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> PeashooterRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> SpreadRenderPtr = nullptr;
	std::shared_ptr<class Player> MainPlayer = nullptr;

	float4 StartPosition = float4::Zero;
	float4 EndPosition = float4::Zero;
	float4 CurPosition = float4::Zero;
	float4 MoveDistance = float4::Zero;

	float DelayTime = 0.0f;

	bool PeashooterAnimation = false;
	bool SpreadAnimation = false;
	bool RenderOut = false;
};


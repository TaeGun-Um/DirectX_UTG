#pragma once

enum class KettleState
{
	Idle,

};

// Ό³Έν :
class ElderKettle : public GameEngineActor
{
public:
	// constrcuter destructer
	ElderKettle();
	~ElderKettle();

	// delete Function
	ElderKettle(const ElderKettle& _Other) = delete;
	ElderKettle(ElderKettle&& _Other) noexcept = delete;
	ElderKettle& operator=(const ElderKettle& _Other) = delete;
	ElderKettle& operator=(ElderKettle&& _Other) noexcept = delete;

	void DebugRenderOn()
	{
		IsDebugRender = true;
	}

	void DebugRenderOff()
	{
		IsDebugRender = false;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> EnterMessageRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> CollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> CollisionPtr = nullptr;

	bool IsDebugRender = false;

	void CollisionCheck(float _DeltaTime);
	void EnterMessageScaleUp(float _DeltaTime);
	void EnterMessageScaleDown(float _DeltaTime);

	float4 EnterMessageRenderMaxScale = float4::Zero;
	float4 EnterMessageRenderMinScale = float4::Zero;
	float4 EnterMessageRenderDelayScale = float4::Zero;
	float ScaleMaxTime = 0.0f;
	float ScaleMinTime = 0.0f;
	int ScaleCount = 1;
	bool ScaleCheckStart = false;

	void ChangeState(KettleState _StateValue);
	void UpdateState(float _DeltaTime);
	KettleState StateValue = KettleState::Idle;

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

};


#pragma once

// Ό³Έν :
class Deliver : public GameEngineActor
{
public:
	// constrcuter destructer
	Deliver();
	~Deliver();

	// delete Function
	Deliver(const Deliver& _Other) = delete;
	Deliver(Deliver&& _Other) noexcept = delete;
	Deliver& operator=(const Deliver& _Other) = delete;
	Deliver& operator=(Deliver&& _Other) noexcept = delete;

	void SetStartPosition(float4 _StartPostion)
	{
		StartPostion = _StartPostion;
		EndPostion = StartPostion + float4{ 1500 , 0 };
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

	float4 StartPostion = float4::Zero;
	float4 EndPostion = float4::Zero;
	float MoveTime = 0.0f;
	float DelayTime = 0.0f;
	bool Directbool = true;

	void DirectCheck();
	void MoveCalculation(float _DeltaTime);
};


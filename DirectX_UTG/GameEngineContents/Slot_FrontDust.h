#pragma once

// Ό³Έν :
class Slot_FrontDust : public GameEngineActor
{
public:
	// constrcuter destructer
	Slot_FrontDust();
	~Slot_FrontDust();

	// delete Function
	Slot_FrontDust(const Slot_FrontDust& _Other) = delete;
	Slot_FrontDust(Slot_FrontDust&& _Other) noexcept = delete;
	Slot_FrontDust& operator=(const Slot_FrontDust& _Other) = delete;
	Slot_FrontDust& operator=(Slot_FrontDust&& _Other) noexcept = delete;

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


#pragma once

// Ό³Έν :
class SFX_MeteorSmoke : public GameEngineActor
{
public:
	// constrcuter destructer
	SFX_MeteorSmoke();
	~SFX_MeteorSmoke();

	// delete Function
	SFX_MeteorSmoke(const SFX_MeteorSmoke& _Other) = delete;
	SFX_MeteorSmoke(SFX_MeteorSmoke&& _Other) noexcept = delete;
	SFX_MeteorSmoke& operator=(const SFX_MeteorSmoke& _Other) = delete;
	SFX_MeteorSmoke& operator=(SFX_MeteorSmoke&& _Other) noexcept = delete;

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


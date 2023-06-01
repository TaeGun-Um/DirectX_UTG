#pragma once

// Ό³Έν :
class PlayerGhost : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerGhost();
	~PlayerGhost();

	// delete Function
	PlayerGhost(const PlayerGhost& _Other) = delete;
	PlayerGhost(PlayerGhost&& _Other) noexcept = delete;
	PlayerGhost& operator=(const PlayerGhost& _Other) = delete;
	PlayerGhost& operator=(PlayerGhost&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
		StartPosition = GetTransform()->GetLocalPosition();
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {};

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	float4 StartPosition = float4::Zero;
	float MoveSpeed = 200.0f;
	void DeathCheck();
};


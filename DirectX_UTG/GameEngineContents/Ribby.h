#pragma once

// Ό³Έν :
class Ribby : public GameEngineActor
{
public:
	// constrcuter destructer
	Ribby();
	~Ribby();

	// delete Function
	Ribby(const Ribby& _Other) = delete;
	Ribby(Ribby&& _Other) noexcept = delete;
	Ribby& operator=(const Ribby& _Other) = delete;
	Ribby& operator=(Ribby&& _Other) noexcept = delete;

	bool GetIsStageEnd()
	{
		return IsStageEnd;
	}

	void SetInitReset()
	{
		IsStageEnd = false;
		HP = 10;
	}

	int GetRibbyHP()
	{
		return HP;
	}

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
	std::shared_ptr<class GameEngineSpriteRenderer> BodyCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> BodyCollisionPtr = nullptr;

	int HP = 10;
	bool IsStageEnd = false;

	void CollisionCheck();
	void HitBlink(float _DeltaTime);

	bool IsDebugRender = false;
	bool IsBlink = false;
	
	float BlinkTime = 0.0f;
	float OriginMulColor = 0.0f;
	float BlinkMulColor = 0.0f;
	int BlinkCount = 1;
};


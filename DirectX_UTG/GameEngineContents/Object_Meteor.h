#pragma once

// Ό³Έν :
class Object_Meteor : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_Meteor();
	~Object_Meteor();

	// delete Function
	Object_Meteor(const Object_Meteor& _Other) = delete;
	Object_Meteor(Object_Meteor&& _Other) noexcept = delete;
	Object_Meteor& operator=(const Object_Meteor& _Other) = delete;
	Object_Meteor& operator=(Object_Meteor&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
		InitPosition = GetTransform()->GetLocalPosition();
	}

	void SetCollisionRenderOn()
	{
		BodyCollisionRenderPtr->On();
	}

	void SetCollisionRenderOff()
	{
		BodyCollisionRenderPtr->Off();
	}

	void SetReverse()
	{
		IsReverse = true;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BodyCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> BodyCollisionPtr = nullptr;

	void MoveCalculation(float _DeltaTime);
	void DeathCheck();
	void CreateSmoke(float _DeltaTime);

	float4 InitPosition = float4::Zero;
	float MoveTime = 0.0f;
	float SmokeCreateDelayTime = 0.0f;
	
	bool IsReverse = false;
};


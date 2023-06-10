#pragma once

#include <GameEngineCore/GameEngineCollision.h>

// Ό³Έν :
class Platform_Bison : public GameEngineActor
{
public:
	// constrcuter destructer
	Platform_Bison();
	~Platform_Bison();

	// delete Function
	Platform_Bison(const Platform_Bison& _Other) = delete;
	Platform_Bison(Platform_Bison&& _Other) noexcept = delete;
	Platform_Bison& operator=(const Platform_Bison& _Other) = delete;
	Platform_Bison& operator=(Platform_Bison&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
		StartPosition = GetTransform()->GetLocalPosition();
	}

	void SetFireRotation(const float4& _Rotation, bool _Direct)
	{
		FireRenderPtr->GetTransform()->SetLocalRotation(_Rotation);
		Directbool = _Direct;

		if (false == Directbool)
		{
			FireRenderPtr->GetTransform()->AddLocalPosition({ 0, -150 });
			FireCollisionPtr->GetTransform()->AddLocalPosition({ 0, -550 });
		}
	}

	void SetCollisionRenderOn()
	{
		PlatformCollisionRenderPtr->On();
		HitCollisionRenderPtr->On();
		DebugRenderPtr->On();

		if (true == FireCollisionPtr->IsUpdate())
		{
			FireCollisionRenderPtr->On();
		}
		else
		{
			FireCollisionRenderPtr->Off();
		}
	}

	void SetCollisionRenderOff()
	{
		PlatformCollisionRenderPtr->Off();
		HitCollisionRenderPtr->Off();
		DebugRenderPtr->Off();
		FireCollisionRenderPtr->Off();
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> FrontRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> FireRenderPtr = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> PlatformCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> HitCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> FireCollisionRenderPtr = nullptr;

	std::shared_ptr<class GameEngineCollision> PlatformCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> HitCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> FireCollisionPtr = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr = nullptr;

	void FrontSet();
	void FireChage(float _DeltaTime);
	void MoveDirection(float _DeltaTime);
	void CollisionCheck(float _Value);
	void DeathCheck();

	float4 StartPosition = float4::Zero;
	float4 MoveDirect = float4::Zero;
	
	float FireChangeTime = 0.0f;
	float WaveTime = 0.0f;
	bool IsWaveEnd = false;
	bool Directbool = true;

	bool FireEnd1 = false;
	bool FireEnd2 = false;
};


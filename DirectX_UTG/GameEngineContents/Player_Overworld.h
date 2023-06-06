#pragma once

#include "PlayerDataBase.h"

enum class OverworldState
{
	Idle,
	Move,
	Portal,
	Win,
};

// 설명 :
class Player_Overworld : public PlayerDataBase
{
	friend class OverworldGUI;

public:
	static Player_Overworld* MainPlayer;

	// constrcuter destructer
	Player_Overworld();
	~Player_Overworld();

	// delete Function
	Player_Overworld(const Player_Overworld& _Other) = delete;
	Player_Overworld(Player_Overworld&& _Other) noexcept = delete;
	Player_Overworld& operator=(const Player_Overworld& _Other) = delete;
	Player_Overworld& operator=(Player_Overworld&& _Other) noexcept = delete;

	void InitReset();

	void WinFSMSetting();

	bool GetIsIdle()
	{
		return IsIdle;
	}

	void PlayerCollisionPtrOn()
	{
		IsCollisionOn = true;
	}

	void PlayerCollisionPtrOff()
	{
		IsCollisionOn = false;
	}

	void SetIsPortalingTrue()
	{
		IsPortaling = true;
	}

	// 임시 디버깅용 (빌딩에서 사용중)
	void SetIsPortalingfalse()
	{
		IsPortaling = false;
	}

	void PlayerDebugRenderOn()
	{
		IsDebugRender = true;
	}

	void PlayerDebugRenderOff()
	{
		IsDebugRender = false;
	}

	// 픽셀 충돌 설정
	void SetColMap(const std::shared_ptr<GameEngineTexture>& _ColMap, PixelCollision::Coordinate _Pivot)
	{
		PixelCollisionCheck.SetColMap(_ColMap, _Pivot);
		ColMap = _ColMap;
		Pivot = _Pivot;

		ColMapHegiht_Half = PixelCollisionCheck.GetColMapHeight_Half();
		ColMapWidth_Half = PixelCollisionCheck.GetColMapWidth_Half();
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr;
	std::shared_ptr<class GameEngineSpriteRenderer> EnterMessageRenderPtr;

	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr0 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr1 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr2 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr3 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr4 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr5 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr6 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr7 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr8 = nullptr;

	std::shared_ptr<class GameEngineCollision> CollisionPtr;
	std::shared_ptr<class GameEngineSpriteRenderer> CollisionRenderPtr;

	bool IsDebugRender = false;
	bool Directbool = true;

	// Assistant Function
	void CheatKey();
	void DebugRendererSetting();
	void EnterMessageScaleUp(float _DeltaTime);
	void EnterMessageScaleDown(float _DeltaTime);

	// 픽셀체크
	void PixelCheck(float _DeltaTime);

	std::shared_ptr<GameEngineTexture> ColMap = nullptr;
	PixelCollision::Coordinate Pivot = PixelCollision::Coordinate::WindowOrigin;
	PixelCollision PixelCollisionCheck;

	AttackDirection ADValue = AttackDirection::Right_Down;

	void PlayerInitialSetting();
	void PlayerCollisionSetting();
	void PlayerDebugRenderer();
	void DirectCheck();
	void MoveDirectCheck();
	void CreateMoveDust();
	void CollisionCheck(float _DeltaTime);

	float4 EnterMessageRenderMaxScale = float4::Zero;
	float4 EnterMessageRenderMinScale = float4::Zero;
	float4 EnterMessageRenderDelayScale = float4::Zero;
	float MoveAbleTime = 0.0f;
	float ScaleMaxTime = 0.0f;
	float ScaleMinTime = 0.0f;
	float MoveTime = 0.0f;
	float WinTime = 0.0f;
	int ScaleCount = 1;
	bool ScaleCheckStart = false;
	bool IsCollisionOn = true;
	bool IsSpeedUp = false;
	bool IsPortaling = false;

	void UpdateState(float _DeltaTime);
	void ChangeState(OverworldState _StateValue);
	OverworldState StateValue = OverworldState::Idle;

	float4 LUD = float4::Zero;
	float4 RUD = float4::Zero;
	float4 RDD = float4::Zero;
	float4 LDD = float4::Zero;
	float4 LD = float4::Zero;
	float4 RD = float4::Zero;
	float4 UD = float4::Zero;
	float4 DD = float4::Zero;

	bool IsIdle = false;
	bool IsWin = false;
	bool WinSetting = false;

	void IdleStart() override;
	void IdleUpdate(float _DeltaTime) override;
	void IdleEnd() override;

	void MoveStart() override;
	void MoveUpdate(float _DeltaTime) override;
	void MoveEnd() override;

	void PortalStart();
	void PortalUpdate(float _DeltaTime);
	void PortalEnd();

	void WinStart();
	void WinUpdate(float _DeltaTime);
	void WinEnd();
};


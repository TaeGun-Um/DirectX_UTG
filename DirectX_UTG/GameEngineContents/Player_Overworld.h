#pragma once

#include "PlayerDataBase.h"

enum class OverworldState
{
	Idle,
	Move,
	Win,
};

// 설명 :
class Player_Overworld : public PlayerDataBase
{
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
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr0 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr1 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr2 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr3 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr4 = nullptr;

	bool IsDebugRender = false;
	bool Directbool = true;

	// 픽셀체크
	void PixelCheck(float _DeltaTime);

	std::shared_ptr<GameEngineTexture> ColMap = nullptr;
	PixelCollision::Coordinate Pivot = PixelCollision::Coordinate::WindowOrigin;
	PixelCollision PixelCollisionCheck;

	AttackDirection ADValue = AttackDirection::Right_Down;

	void PlayerInitialSetting();
	void DebugRendererSetting();
	void DirectCheck();
	void MoveDirectCheck();

	void UpdateState(float _DeltaTime);
	void ChangeState(OverworldState _StateValue);
	OverworldState StateValue = OverworldState::Idle;

	void IdleStart() override;
	void IdleUpdate(float _DeltaTime) override;
	void IdleEnd() override;

	void MoveStart() override;
	void MoveUpdate(float _DeltaTime) override;
	void MoveEnd() override;

	void WinStart();
	void WinUpdate(float _DeltaTime);
	void WinEnd();
};


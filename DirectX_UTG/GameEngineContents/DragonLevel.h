#pragma once

#include "Loading.h"

// ���� :
class DragonLevel : public GameEngineLevel
{
public:
	static DragonLevel* DragonLevelPtr;

	// constrcuter destructer
	DragonLevel();
	~DragonLevel();

	// delete Function
	DragonLevel(const DragonLevel& _Other) = delete;
	DragonLevel(DragonLevel&& _Other) noexcept = delete;
	DragonLevel& operator=(const DragonLevel& _Other) = delete;
	DragonLevel& operator=(DragonLevel&& _Other) noexcept = delete;

	std::shared_ptr<class Knockout> GetKnockoutPtr()
	{
		return KnockoutPtr;
	}

	std::shared_ptr<class You_Died> GetYouDiedPtr()
	{
		return YouDiedPtr;
	}

	std::shared_ptr<class Ready_Wallop> GetReadyWallopPtr()
	{
		return ReadyWallopPtr;
	}

	bool GetIsDragonLevelEnd()
	{
		return IsDragonLevelEnd;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	//std::shared_ptr<class Frog_Map> MapObject = nullptr;
	std::shared_ptr<class Dragon_ColMap> ThisColMap = nullptr;
	std::shared_ptr<class WeaponUI> WeaponObject = nullptr;
	std::shared_ptr<class HealthUI> HealthObject = nullptr;
	std::shared_ptr<class CardUI> CardObject = nullptr;
	std::shared_ptr<class Player> PlayerObject = nullptr;
	std::shared_ptr<class GrimMatchstick> DragonObject = nullptr;

	std::shared_ptr<class TransformGUI> GUI = nullptr;
	std::shared_ptr<class RoundBlackBox> BlackBoxPtr = nullptr;
	std::shared_ptr<class Knockout> KnockoutPtr = nullptr;
	std::shared_ptr<class You_Died> YouDiedPtr = nullptr;
	std::shared_ptr<class Ready_Wallop> ReadyWallopPtr = nullptr;

	void ReLoadSetting();
	void PlayerDebugRenderOn();
	void PlayerDebugRenderOff();
	void LevelDebugOn();
	void LevelDebugOff();

	float ReadyWallopTime = 0.0f;
	float EndTime = 0.0f;

	bool IsBossEnd = false;
	bool IsPlayerEnd = false;
	bool IsDragonLevelEnd = false;

	int DebugBoxCount = 1;
	int ReadyWallopCount = 1;
	int EndSetCount = 1;
	int EndSetCount2 = 1;

};


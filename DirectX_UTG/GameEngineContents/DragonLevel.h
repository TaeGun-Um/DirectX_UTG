#pragma once

#include "Loading.h"

// Ό³Έν :
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
	GameEngineSoundPlayer BGMPlayer;
	GameEngineSoundPlayer VoicePlayer;

	bool IsBGMOn = false;
	bool IsVoiceOn = false;

	std::shared_ptr<class Dragon_BackGround> BackGroundObject = nullptr;
	std::shared_ptr<class Dragon_FrontGround> FrontGroundObject = nullptr;
	std::shared_ptr<class Dragon_FallPoint> FallPointObject = nullptr;

	std::shared_ptr<class Dragon_CloudPlatform> CloudPlatformObject0 = nullptr;
	std::shared_ptr<class Dragon_CloudPlatform> CloudPlatformObject1 = nullptr;
	std::shared_ptr<class Dragon_CloudPlatform> CloudPlatformObject2 = nullptr;
	std::shared_ptr<class Dragon_CloudPlatform> CloudPlatformObject3 = nullptr;
	std::shared_ptr<class Dragon_CloudPlatform> CloudPlatformObject4 = nullptr;
	std::shared_ptr<class Dragon_CloudPlatform> CloudPlatformObject5 = nullptr;
	std::shared_ptr<class Dragon_CloudPlatform> CloudPlatformObject6 = nullptr;
	std::shared_ptr<class Dragon_CloudPlatform> CloudPlatformObject7 = nullptr;
	std::shared_ptr<class Dragon_CloudPlatform> CloudPlatformObject8 = nullptr;
	
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

	void KnockSound();
	void StartVoiceSound();
	void ReLoadSetting();
	void PlayerDebugRenderOn();
	void PlayerDebugRenderOff();
	void LevelDebugOn();
	void LevelDebugOff();

	float BGMDelayTime = 0.0f;
	float ReadyWallopTime = 0.0f;
	float EndTime = 0.0f;

	bool IsEndSound = false;
	bool IsEndSound2 = false;
	bool IsBossEnd = false;
	bool IsPlayerEnd = false;
	bool IsDragonLevelEnd = false;

	int DebugBoxCount = 1;
	int ReadyWallopCount = 1;
	int EndSetCount = 1;
	int EndSetCount2 = 1;
	int CloudMoveCount = 1;
};


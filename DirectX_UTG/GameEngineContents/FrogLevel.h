#pragma once

#include "Loading.h"

// Ό³Έν :
class FrogLevel : public GameEngineLevel
{
public:
	static FrogLevel* FrogLevelPtr;

	// constrcuter destructer
	FrogLevel();
	~FrogLevel();

	// delete Function
	FrogLevel(const FrogLevel& _Other) = delete;
	FrogLevel(FrogLevel&& _Other) noexcept = delete;
	FrogLevel& operator=(const FrogLevel& _Other) = delete;
	FrogLevel& operator=(FrogLevel&& _Other) noexcept = delete;

	void LoadingOn()
	{
		LoadingPtr->SetLoadingPtrOn();
	}

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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class Loading> LoadingPtr = nullptr;
	std::shared_ptr<class Frog_Map> MapObject = nullptr;
	std::shared_ptr<class Frog_ColMap> ThisColMap = nullptr;
	std::shared_ptr<class HealthUI> HealthObject = nullptr;
	std::shared_ptr<class CardUI> CardObject = nullptr;
	std::shared_ptr<class Player> PlayerObject = nullptr;
	std::shared_ptr<class Ribby> RibbyObject = nullptr;

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
	bool IsFrogLevelEnd = false;

	int ReadyWallopCount = 1;
	int EndSetCount = 1;
	int EndSetCount2 = 1;
};


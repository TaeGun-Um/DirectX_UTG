#pragma once

#include "Loading.h"

// ���� :
class MouseLevel : public GameEngineLevel
{
public:
	static MouseLevel* MouseLevelPtr;

	// constrcuter destructer
	MouseLevel();
	~MouseLevel();

	// delete Function
	MouseLevel(const MouseLevel& _Other) = delete;
	MouseLevel(MouseLevel&& _Other) noexcept = delete;
	MouseLevel& operator=(const MouseLevel& _Other) = delete;
	MouseLevel& operator=(MouseLevel&& _Other) noexcept = delete;

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

	bool GetIsMouseLevelEnd()
	{
		return IsMouseLevelEnd;
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

	std::shared_ptr<class Mouse_Map> MapObject = nullptr;
	std::shared_ptr<class Mouse_ColMap> ThisColMap = nullptr;
	std::shared_ptr<class Mouse_FrontObject> FrontMapObject = nullptr;
	std::shared_ptr<class Mouse_BackObject> BackMapObject = nullptr;
	std::shared_ptr<class WeaponUI> WeaponObject = nullptr;
	std::shared_ptr<class HealthUI> HealthObject = nullptr;
	std::shared_ptr<class CardUI> CardObject = nullptr;
	std::shared_ptr<class Player> PlayerObject = nullptr;
	std::shared_ptr<class Werner_Werman> MouseObject = nullptr;
	std::shared_ptr<class Katzenwagen> CatObject = nullptr;

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

	float ReadyWallopTime = 0.0f;
	float EndTime = 0.0f;

	bool IsEndSound = false;
	bool IsEndSound2 = false;
	bool IsBossEnd = false;
	bool IsPlayerEnd = false;
	bool IsMouseLevelEnd = false;

	int ReadyWallopCount = 1;
	int EndSetCount = 1;
	int EndSetCount2 = 1;

};


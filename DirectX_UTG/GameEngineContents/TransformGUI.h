#pragma once

#include <GameEngineCore/GameEngineGUI.h>

// ���� :
class TransformGUI : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	TransformGUI();
	~TransformGUI();

	// delete Function
	TransformGUI(const TransformGUI& _Other) = delete;
	TransformGUI(TransformGUI&& _Other) noexcept = delete;
	TransformGUI& operator=(const TransformGUI& _Other) = delete;
	TransformGUI& operator=(TransformGUI&& _Other) noexcept = delete;
	
	void OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime) override;

	void SetTarget(GameEngineTransform* _Target);

	void SetMainPalyer(std::shared_ptr<class Player> _MainPalyer);
	void SetFrogBoss(std::shared_ptr<class Croak> _FrogBoss);
	void SetDragonBoss(std::shared_ptr<class GrimMatchstick> _FrogBoss);
	void SetMouseBoss(std::shared_ptr<class Werner_Werman> _FrogBoss);

	std::function<void()> PlayerDebugRenderOn;
	std::function<void()> PlayerDebugRenderOff;

	std::function<void()> ColMapRenderOn;
	std::function<void()> ColMapRenderOff;

protected:

private:
	std::shared_ptr<class Player> MainPlayer = nullptr;
	std::shared_ptr<class Croak> FrogBoss = nullptr;
	std::shared_ptr<class GrimMatchstick> DragonBoss = nullptr;
	std::shared_ptr<class Werner_Werman> MouseBoss = nullptr;
	GameEngineTransform* TargetTransform = nullptr;

	bool IsWorldPostion = false;
	bool IsWorldRotation = false;
	bool IsWorldScale = false;

	bool IsPlayerDebugDot = false;
	bool IsColMapRender = false;

	float Postion[4] = { 0, 0, 0, 1 };
	float Rotation[4] = { 0, 0, 0, 1 };
	float Scale[4] = { 1, 1, 1, 1 };

	int PlayerHP = 0;
	int PlayerEXGauge = 0;
	int PlayerEXStack = 0;

	std::vector<std::function<void()>> CustomGuiFunctions;

	void HelpMarker(const std::string_view& _Text);

	static float4 ConvertFloat4(float _FloatArr[4]);

};


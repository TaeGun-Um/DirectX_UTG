#pragma once

#include <GameEngineCore/GameEngineGUI.h>

// Ό³Έν :
class OverworldGUI : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	OverworldGUI();
	~OverworldGUI();

	// delete Function
	OverworldGUI(const OverworldGUI& _Other) = delete;
	OverworldGUI(OverworldGUI&& _Other) noexcept = delete;
	OverworldGUI& operator=(const OverworldGUI& _Other) = delete;
	OverworldGUI& operator=(OverworldGUI&& _Other) noexcept = delete;

	void OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime) override;

	void SetTarget(GameEngineTransform* _Target);

	void SetOverworldPalyer(std::shared_ptr<class Player_Overworld> _OverworldPalyer);

	std::function<void()> PlayerDebugRenderOn;
	std::function<void()> PlayerDebugRenderOff;

	std::function<void()> ColMapRenderOn;
	std::function<void()> ColMapRenderOff;

protected:

private:
	std::shared_ptr<class Player_Overworld> OverworldPalyer = nullptr;
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


#pragma once

#include <GameEngineCore/GameEngineGUI.h>

// Ό³Έν :
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

	std::function<void()> PlayerDebugRenderOn;
	std::function<void()> PlayerDebugRenderOff;

protected:

private:
	GameEngineTransform* TargetTransform = nullptr;

	bool IsWorldPostion = false;
	bool IsWorldRotation = false;
	bool IsWorldScale = false;

	bool IsPlayerDebugDot = false;

	float Postion[4] = { 0, 0, 0, 1 };
	float Rotation[4] = { 0, 0, 0, 1 };
	float Scale[4] = { 1, 1, 1, 1 };

	std::vector<std::function<void()>> CustomGuiFunctions;

	void HelpMarker(const std::string_view& _Text);

	static float4 ConvertFloat4(float _FloatArr[4]);

};


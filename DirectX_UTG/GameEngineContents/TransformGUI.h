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

	void SetTargetTransform(GameEngineTransform* _Target)
	{
		TargetTransform = _Target;
	}

protected:

private:
	GameEngineTransform* TargetTransform = nullptr;

};


#pragma once
#include <functional>
#include <GameEngineCore/GameEngineGUI.h>

// Ό³Έν :
class ImguiWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	ImguiWindow();
	~ImguiWindow();

	// delete Function
	ImguiWindow(const ImguiWindow& _Other) = delete;
	ImguiWindow(ImguiWindow&& _Other) noexcept = delete;
	ImguiWindow& operator=(const ImguiWindow& _Other) = delete;
	ImguiWindow& operator=(ImguiWindow&& _Other) noexcept = delete;

	std::function<void()> Test2;

	void OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime) override;

protected:

private:

};


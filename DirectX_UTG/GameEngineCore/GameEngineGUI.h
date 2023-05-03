#pragma once
#include <memory>
#include <map>

#include <GameEngineBase/GameEngineString.h>
#include "GameEngineNameObject.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

class GameEngineGUIWindow : public GameEngineNameObject, public std::enable_shared_from_this<GameEngineGUIWindow>
{
	friend class GameEngineGUI;

private:
	void Begin()
	{
		std::string_view View = GetName();
		ImGui::Begin(View.data());
	}
	void End()
	{
		ImGui::End();
	}

public:
	virtual void Start() {}
	virtual void OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime) = 0;
};

// 설명 : IMGUI를 수월하게 사용할 수 있도록 도와주는 클래스
class GameEngineGUI
{
public:
	// constrcuter destructer
	GameEngineGUI();
	~GameEngineGUI();

	// delete Function
	GameEngineGUI(const GameEngineGUI& _Other) = delete;
	GameEngineGUI(GameEngineGUI&& _Other) noexcept = delete;
	GameEngineGUI& operator=(const GameEngineGUI& _Other) = delete;
	GameEngineGUI& operator=(GameEngineGUI&& _Other) noexcept = delete;

	// IMGUI 이니셜라이즈
	static void Initialize();

	// 생성된 IMGUI Render
	static void Render(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime);

	// IMGUI 릴리즈
	static void Release();

	// IMGUI 생성
	template<typename WindowType>
	static std::shared_ptr<GameEngineGUIWindow> GUIWindowCreate(const std::string_view& _Name)
	{
		std::string UpperString = GameEngineString::ToUpper(_Name);

		if (AllWindow.end() != AllWindow.find(UpperString))
		{
			MsgAssert("이런 이름을 가진 GUI윈도우는 이미 존재합니다." + std::string(_Name));
			return nullptr;
		}

		std::shared_ptr<GameEngineGUIWindow> WindowPtr;
		AllWindow[UpperString] = WindowPtr = std::make_shared<WindowType>();
		WindowPtr->SetName(UpperString);
		WindowPtr->Start();

		return WindowPtr;
	}

	// IMGUI 찾기(템플릿)
	template<typename ConvertType>
	static std::shared_ptr<ConvertType> FindGUIWindowConvert(const std::string_view& _Name)
	{
		std::shared_ptr<GameEngineGUIWindow> Window = FindGUIWindow(_Name);

		return std::dynamic_pointer_cast<ConvertType>(Window);
	}

	// IMGUI 찾기
	static std::shared_ptr<GameEngineGUIWindow> FindGUIWindow(const std::string_view& _Name)
	{
		std::string UpperString = GameEngineString::ToUpper(_Name);

		std::map<std::string, std::shared_ptr<GameEngineGUIWindow>>::iterator FindIter = AllWindow.find(UpperString);

		if (AllWindow.end() == FindIter)
		{
			return nullptr;
		}

		return FindIter->second;
	}

protected:

private:
	static std::map<std::string, std::shared_ptr<GameEngineGUIWindow>> AllWindow; // 생성된 모든 IMGUI 저장
};


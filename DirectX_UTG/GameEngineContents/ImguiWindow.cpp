#include "PrecompileHeader.h"
#include "ImguiWindow.h"

ImguiWindow::ImguiWindow() 
{
}

ImguiWindow::~ImguiWindow() 
{
}

void ImguiWindow::OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime)
{
	if (ImGui::Button("sdfsdfsdf"))
	{
		if (nullptr != Test2)
		{
			Test2();
		}
	}
}
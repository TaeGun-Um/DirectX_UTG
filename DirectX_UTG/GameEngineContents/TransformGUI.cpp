#include "PrecompileHeader.h"
#include "TransformGUI.h"

TransformGUI::TransformGUI() 
{
}

TransformGUI::~TransformGUI() 
{
}
bool IS = false;
bool ISa = false;
char a = 'a';
char b = 'b';
void TransformGUI::OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime)
{
	//if (ImGui::Button("sdfsdfsdf"))
	//{
	//	if (nullptr != Test2)
	//	{
	//		Test2();
	//	}
	//}
	TargetTransform->GetLocalPosition().x;

	//ImGui::GetCursorPosX();

	ImGui::Checkbox(&a, &IS);
	
	ImGui::SameLine();

	ImGui::Checkbox(&b, &ISa);
}
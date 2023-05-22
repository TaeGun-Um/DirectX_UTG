#include "PrecompileHeader.h"
#include "TransformGUI.h"

#include <GameEngineBase/GameEngineString.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"

TransformGUI::TransformGUI() 
{
}

TransformGUI::~TransformGUI() 
{
}

void TransformGUI::OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime)
{
	if (nullptr == TargetTransform)
	{
		return;
	}

	if (true == TargetTransform->IsDeath())
	{
		TargetTransform = nullptr;
		return;
	}

	ImGui::Checkbox("W", &IsWorldPostion);
	ImGui::SameLine();
	HelpMarker("Setting World Postion");
	ImGui::SameLine();

	float4 GetPostion = float4::Zero;

	if (true == IsWorldPostion)
	{
		TargetTransform->SetWorldPosition(TargetTransform->GetWorldPosition());
		GetPostion = TargetTransform->GetWorldPosition();
	}
	else
	{
		TargetTransform->SetLocalPosition(TargetTransform->GetLocalPosition());
		GetPostion = TargetTransform->GetLocalPosition();
	}

	Postion[0] = GetPostion.x;
	Postion[1] = GetPostion.y;
	Postion[2] = GetPostion.z;
	Postion[3] = GetPostion.w;

	ImGui::DragFloat4(" - Postion", Postion);

	if (true == IsWorldPostion)
	{
		TargetTransform->SetWorldPosition(ConvertFloat4(Postion));
	}
	else
	{
		TargetTransform->SetLocalPosition(ConvertFloat4(Postion));
	}

	ImGui::Checkbox("W", &IsWorldRotation);
	ImGui::SameLine();
	HelpMarker("Setting World Rotation");
	ImGui::SameLine();

	float4 GetRoation = float4::Zero;

	if (true == IsWorldPostion)
	{
		TargetTransform->SetWorldRotation(TargetTransform->GetWorldRotation());
		GetRoation = TargetTransform->GetWorldRotation();
	}
	else
	{
		TargetTransform->SetLocalRotation(TargetTransform->GetLocalRotation());
		GetRoation = TargetTransform->GetLocalRotation();
	}

	Rotation[0] = GetRoation.x;
	Rotation[1] = GetRoation.y;
	Rotation[2] = GetRoation.z;
	Rotation[3] = GetRoation.w;

	ImGui::DragFloat4(" - Rotation", Rotation);

	if (true == IsWorldRotation)
	{
		TargetTransform->SetWorldRotation(ConvertFloat4(Rotation));
	}
	else
	{
		TargetTransform->SetLocalRotation(ConvertFloat4(Rotation));
	}

	ImGui::Checkbox("W", &IsWorldScale);
	ImGui::SameLine();
	HelpMarker("Setting World Scale");
	ImGui::SameLine();

	float4 GetScale = float4::Zero;

	if (true == IsWorldScale)
	{
		TargetTransform->SetWorldScale(TargetTransform->GetWorldRotation());
		GetScale = TargetTransform->GetWorldScale();
	}
	else
	{
		TargetTransform->SetLocalScale(TargetTransform->GetLocalScale());
		GetScale = TargetTransform->GetLocalScale();
	}

	Scale[0] = GetScale.x;
	Scale[1] = GetScale.y;
	Scale[2] = GetScale.z;
	Scale[3] = GetScale.w;

	ImGui::DragFloat4(" - Scale", Scale);

	if (true == IsWorldScale)
	{
		TargetTransform->SetWorldScale(ConvertFloat4(Scale));
	}
	else
	{
		TargetTransform->SetLocalScale(ConvertFloat4(Scale));
	}

	ImGui::Checkbox("PlayerDebugDot", &IsPlayerDebugDot);

	if (nullptr != PlayerDebugRenderOn && true == IsPlayerDebugDot)
	{
		PlayerDebugRenderOn();
	}

	if (nullptr != PlayerDebugRenderOff && false == IsPlayerDebugDot)
	{
		PlayerDebugRenderOff();
	}

	ImGui::Checkbox("ColMapRender", &IsColMapRender);

	if (nullptr != ColMapRenderOn && true == IsColMapRender)
	{
		ColMapRenderOn();
	}

	if (nullptr != ColMapRenderOff && false == IsColMapRender)
	{
		ColMapRenderOff();
	}

	if (nullptr != Player::MainPlayer)
	{
		ImGui::Text("PlayerHP : %d", MainPalyer->GetPlayerHP());
		ImGui::Text("EXGauge : %f", MainPalyer->GetPlayerEXGauge());
		ImGui::Text("EXStack : %d", MainPalyer->GetPlayerEXStack());

		//ImGui::Text("IsBottomJump : %s", IsBottomJump);
		//const char* CollisionPtr = "NULL";

		//if (nullptr == MainPalyer->BottomSensorCollisionPtr->Collision(static_cast<int>(CollisionOrder::Platform), ColType::AABBBOX2D, ColType::AABBBOX2D))
		//{
		//	CollisionPtr = "NULL";
		//}
		//else
		//{
		//	CollisionPtr = "Collision";
		//}
		//
		//ImGui::Text("CollisionPtr : %s", CollisionPtr);
	}
}

void TransformGUI::SetTarget(GameEngineTransform* _Target)
{
	TargetTransform = _Target;

	if (nullptr != TargetTransform)
	{
		IsWorldPostion = false;
		IsWorldRotation = false;
		IsWorldScale = false;

		float4 LocalPos = TargetTransform->GetLocalPosition();
		float4 LocalRotation = TargetTransform->GetLocalRotation();
		float4 LocalScale = TargetTransform->GetLocalScale();

		Postion[0] = LocalPos.x;
		Postion[1] = LocalPos.y;
		Postion[2] = LocalPos.z;
		Postion[3] = LocalPos.w;

		Rotation[0] = LocalRotation.x;
		Rotation[1] = LocalRotation.y;
		Rotation[2] = LocalRotation.z;
		Rotation[3] = LocalRotation.w;

		Scale[0] = LocalScale.x;
		Scale[1] = LocalScale.y;
		Scale[2] = LocalScale.z;
		Scale[3] = LocalScale.w;
	}
}

void TransformGUI::SetMainPalyer(std::shared_ptr<class Player> _MainPalyer)
{
	MainPalyer = _MainPalyer;
}

void TransformGUI::HelpMarker(const std::string_view& _Text)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort) && ImGui::BeginTooltip())
	{
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(_Text.data());
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

float4 TransformGUI::ConvertFloat4(float _FloatArr[4])
{
	return float4(_FloatArr[0], _FloatArr[1], _FloatArr[2], _FloatArr[3]);
}
#include "PrecompileHeader.h"
#include "Mouse_FrontObject.h"

#include "HBSCSpriteRenderer.h"

Mouse_FrontObject::Mouse_FrontObject() 
{
}

Mouse_FrontObject::~Mouse_FrontObject() 
{
}

// saturation ä�� // brightness ��� // contrast ���
void Mouse_FrontObject::BrightnessControl(std::shared_ptr<class HBSCSpriteRenderer> _Object, float _saturation, float _brightness, float _contrast)
{
	float4 OriginColor = _Object->ColorOptionValue.MulColor;
	float4 ControlColor = float4::Zero;

	ControlColor.r = OriginColor.r;
	ControlColor.g = _saturation;
	ControlColor.b = _brightness;
	ControlColor.a = _contrast;

	_Object->HBSCColorValue.HBSCColor = ControlColor;
}

void Mouse_FrontObject::Start()
{
	if (nullptr == GameEngineTexture::Find("mouse_bg_foreground_a.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Mouse_FrontMapObject");

		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_foreground_a.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_foreground_b1.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_foreground_b2.png").GetFullPath());
	}

	if (nullptr == FrontRenderPtr_1)
	{
		FrontRenderPtr_1 = CreateComponent<HBSCSpriteRenderer>();
		FrontRenderPtr_1->SetScaleToTexture("mouse_bg_foreground_b2.png");
		FrontRenderPtr_1->GetTransform()->SetWorldPosition({ 630, 380, -4 });
	}
	if (nullptr == FrontRenderPtr_2)
	{
		FrontRenderPtr_2 = CreateComponent<HBSCSpriteRenderer>();
		FrontRenderPtr_2->SetScaleToTexture("mouse_bg_foreground_a.png");
		FrontRenderPtr_2->GetTransform()->SetWorldPosition({ 600, 650, -4 });
	}
	if (nullptr == FrontRenderPtr_3)
	{
		FrontRenderPtr_3 = CreateComponent<HBSCSpriteRenderer>();
		FrontRenderPtr_3->SetScaleToTexture("mouse_bg_foreground_b1.png");
		FrontRenderPtr_3->GetTransform()->SetWorldPosition({ 635, 100, -4 });
	}

	BrightnessControl(FrontRenderPtr_1, 0.6f, 0.6f, 0.6f);
	BrightnessControl(FrontRenderPtr_2, 0.6f, 0.6f, 0.6f);
	BrightnessControl(FrontRenderPtr_3, 0.6f, 0.6f, 0.6f);
}

void Mouse_FrontObject::Update(float _DeltaTime)
{

}
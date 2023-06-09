#include "PrecompileHeader.h"
#include "Mouse_BackObject.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Mouse_BackObject* Mouse_BackObject::MouseBackObjectPtr = nullptr;

Mouse_BackObject::Mouse_BackObject() 
{
}

Mouse_BackObject::~Mouse_BackObject() 
{
}

// saturation ä�� // brightness ��� // contrast ���
void Mouse_BackObject::HBSCControl(std::shared_ptr<class GameEngineSpriteRenderer> _Object, float _saturation, float _brightness, float _contrast)
{
	float4 OriginColor = _Object->ColorOptionValue.MulColor;
	float4 ControlColor = float4::Zero;

	ControlColor.r = OriginColor.r;
	ControlColor.g = _saturation;
	ControlColor.b = _brightness;
	ControlColor.a = _contrast;

	_Object->ColorOptionValue.HBSCColor = ControlColor;
}

void Mouse_BackObject::Start()
{
	MouseBackObjectPtr = this;

	if (nullptr == GameEngineTexture::Find("mouse_bg_bullet_a.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("3_Werner_Werman");
		NewDir.Move("Mouse_BackMapObject");

		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_bullet_a.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_bullet_b.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_bullet_c.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_bullet_d.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_blue_stool.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_red_stool.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_thimble_a.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_thimble_b.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_die.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("mouse_bg_table.png").GetFullPath());
	}

	if (nullptr == BackRenderPtr_Bullet1)
	{
		BackRenderPtr_Bullet1 = CreateComponent<GameEngineSpriteRenderer>();
		BackRenderPtr_Bullet1->SetScaleToTexture("mouse_bg_bullet_a.png");
		BackRenderPtr_Bullet1->GetTransform()->SetWorldPosition({ 270, 280, 2 });
	}
	if (nullptr == BackRenderPtr_Bullet2)
	{
		BackRenderPtr_Bullet2 = CreateComponent<GameEngineSpriteRenderer>();
		BackRenderPtr_Bullet2->SetScaleToTexture("mouse_bg_bullet_b.png");
		BackRenderPtr_Bullet2->GetTransform()->SetWorldPosition({ 310, 285, 2 });
	}
	if (nullptr == BackRenderPtr_Bullet3)
	{
		BackRenderPtr_Bullet3 = CreateComponent<GameEngineSpriteRenderer>();
		BackRenderPtr_Bullet3->SetScaleToTexture("mouse_bg_bullet_c.png");
		BackRenderPtr_Bullet3->GetTransform()->SetWorldPosition({ 345, 295, 2 });
	}
	if (nullptr == BackRenderPtr_Bullet4)
	{
		BackRenderPtr_Bullet4 = CreateComponent<GameEngineSpriteRenderer>();
		BackRenderPtr_Bullet4->SetScaleToTexture("mouse_bg_bullet_d.png");
		BackRenderPtr_Bullet4->GetTransform()->SetWorldPosition({ 385, 280, 2 });
	}
	if (nullptr == BackRenderPtr_Dice)
	{
		BackRenderPtr_Dice = CreateComponent<GameEngineSpriteRenderer>();
		BackRenderPtr_Dice->SetScaleToTexture("mouse_bg_die.png");
		BackRenderPtr_Dice->GetTransform()->SetWorldPosition({ 450, 260, 2 });
	}
	if (nullptr == BackRenderPtr_Stool1)
	{
		BackRenderPtr_Stool1 = CreateComponent<GameEngineSpriteRenderer>();
		BackRenderPtr_Stool1->SetScaleToTexture("mouse_bg_blue_stool.png");
		BackRenderPtr_Stool1->GetTransform()->SetWorldPosition({ 875, 200, 2 });
	}
	if (nullptr == BackRenderPtr_Table)
	{
		BackRenderPtr_Table = CreateComponent<GameEngineSpriteRenderer>();
		BackRenderPtr_Table->SetScaleToTexture("mouse_bg_table.png");
		BackRenderPtr_Table->GetTransform()->SetWorldPosition({ 970, 200, 2 });
	}
	if (nullptr == BackRenderPtr_Stool2)
	{
		BackRenderPtr_Stool2 = CreateComponent<GameEngineSpriteRenderer>();
		BackRenderPtr_Stool2->SetScaleToTexture("mouse_bg_red_stool.png");
		BackRenderPtr_Stool2->GetTransform()->SetWorldPosition({ 1065, 200, 2 });
	}
	if (nullptr == BackRenderPtr_Thimble1)
	{
		BackRenderPtr_Thimble1 = CreateComponent<GameEngineSpriteRenderer>();
		BackRenderPtr_Thimble1->SetScaleToTexture("mouse_bg_thimble_a.png");
		BackRenderPtr_Thimble1->GetTransform()->SetWorldPosition({ 945, 245, 2 });
	}
	if (nullptr == BackRenderPtr_Thimble2)
	{
		BackRenderPtr_Thimble2 = CreateComponent<GameEngineSpriteRenderer>();
		BackRenderPtr_Thimble2->SetScaleToTexture("mouse_bg_thimble_b.png");
		BackRenderPtr_Thimble2->GetTransform()->SetWorldPosition({ 990, 243, 2 });
	}

	HBSCControl(BackRenderPtr_Bullet1, 0.45f, 0.6f, 0.49f);
	HBSCControl(BackRenderPtr_Bullet2, 0.45f, 0.6f, 0.49f);
	HBSCControl(BackRenderPtr_Bullet3, 0.45f, 0.6f, 0.49f);
	HBSCControl(BackRenderPtr_Bullet4, 0.45f, 0.6f, 0.49f);
	HBSCControl(BackRenderPtr_Dice, 0.45f, 0.6f, 0.49f);
	HBSCControl(BackRenderPtr_Stool1, 0.45f, 0.6f, 0.49f);
	HBSCControl(BackRenderPtr_Table, 0.45f, 0.6f, 0.49f);
	HBSCControl(BackRenderPtr_Stool2, 0.45f, 0.6f, 0.49f);
	HBSCControl(BackRenderPtr_Thimble1, 0.45f, 0.6f, 0.49f);
	HBSCControl(BackRenderPtr_Thimble2, 0.45f, 0.6f, 0.49f);
}

void Mouse_BackObject::Update(float _DeltaTime)
{

}
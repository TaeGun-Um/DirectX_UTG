#include "PrecompileHeader.h"
#include "Overworld_Upper.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Overworld_Upper::Overworld_Upper() 
{
}

Overworld_Upper::~Overworld_Upper() 
{
}

void Overworld_Upper::Start()
{
	if (nullptr == GameEngineTexture::Find("Overworld_Bush_Left.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Overworld");

		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\Bush\\Overworld_Bush_Left.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\Bush\\Overworld_Bush_Right.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\2.Right\\Mausoleum_Bush.png").GetFullPath());

		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\0.Small_Island\\Dock&Boat\\Boat.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\0.Small_Island\\Dock&Boat\\Dock.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\0.Small_Island\\Lighthouse&Bouy\\Lighthouse.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\0.Small_Island\\Lighthouse&Bouy\\Lighthouse_Buoy.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Tree_Island.png").GetFullPath());

		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\0.Small_Island\\MainBridge\\MainBridge_FrontTopper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Bridges\\ClipBridge\\ClipBridge_FrontTopper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Bridges\\ForestBridge\\ForestBridge_FrontTopper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\2.Right\\Bridge\\PlaneBridge\\PlaneBridge_FrontTopper.png").GetFullPath());


		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Stairs\\BotanicStair\\BotanicStair_FrontTopper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Stairs\\RuseStair\\RuseStair_Topper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Stairs\\TreetopStair\\TreetopStair_FrontTopper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\2.Right\\Stairs\\HouseStair\\HouseStair_FrontTopper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\2.Right\\Stairs\\ZeppelinStair\\ZeppelinStair_Topper.png").GetFullPath());
	}

	if (nullptr == Overworld_Bush_LeftRenderPtr) // ���� �� ��Ǯ��
	{
		Overworld_Bush_LeftRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		Overworld_Bush_LeftRenderPtr->SetScaleToTexture("Overworld_Bush_Left.png");
		Overworld_Bush_LeftRenderPtr->GetTransform()->SetLocalPosition({ -600, 0, -5 });
		Overworld_Bush_LeftRenderPtr->CameraCullingOn();
	}
	if (nullptr == Overworld_Bush_RightRenderPtr) // ������ �� ��Ǯ��
	{
		//Overworld_Bush_RightRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		//Overworld_Bush_RightRenderPtr->SetScaleToTexture("Mausoleum_Bush.png");
		//Overworld_Bush_RightRenderPtr->CameraCullingOn();
	}
	if (nullptr == Mausoleum_BushRenderPtr) // �ڹ��� ��ġ ��Ǯ
	{
		//Mausoleum_BushRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		//Mausoleum_BushRenderPtr->SetScaleToTexture("Overworld_Map.png");
		//Mausoleum_BushRenderPtr->CameraCullingOn();
	}

	if (nullptr == DockRenderPtr) // ���� �� ��ũ
	{
		DockRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == BoatRenderPtr) // ���� �� ��
	{
		BoatRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == LighthouseRenderPtr)	// ���� �� ���
	{
		LighthouseRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == BuoyRenderPtr) // ���� �� ��ǥ
	{
		BuoyRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == Tree_IslandRenderPtr) // �� �Ʒ� ��
	{
		Tree_IslandRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr == MainBridge_FrontTopperRenderPtr) // �ٸ� ����
	{
		MainBridge_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == ClipBridge_FrontTopperRenderPtr) // �ٸ� ����
	{
		ClipBridge_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == ForestBridge_FrontTopperRenderPtr) // �ٸ� ����
	{
		ForestBridge_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == PlaneBridge_FrontTopperRenderPtr) // �ٸ� ����
	{
		PlaneBridge_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr == BotanicStair_FrontTopperRenderPtr) // ��� ����
	{
		BotanicStair_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == RuseStair_TopperRenderPtr) // ��� ����
	{
		RuseStair_TopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == TreetopStair_FrontTopperRenderPtr) // ��� ����
	{
		TreetopStair_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == HouseStair_FrontTopperRenderPtr) // ��� ����
	{
		HouseStair_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == ZeppelinStair_TopperRenderPtr) // ��� ����
	{
		ZeppelinStair_TopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
}
void Overworld_Upper::Update(float _DeltaTime)
{

}
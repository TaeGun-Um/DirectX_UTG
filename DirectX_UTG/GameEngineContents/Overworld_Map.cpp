#include "PrecompileHeader.h"
#include "Overworld_Map.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player_Overworld.h"

Overworld_Map::Overworld_Map() 
{
}

Overworld_Map::~Overworld_Map() 
{
}

void Overworld_Map::Start()
{
	if (nullptr == GameEngineTexture::Find("Overworld_Map.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Overworld");

		GameEngineTexture::Load(NewDir.GetPlusFileName("Overworld_Map.png").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->SetScaleToTexture("Overworld_Map.png");
	}

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

		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\0.Small_Island\\Dock&Boat\\Dock.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\0.Small_Island\\Dock&Boat\\Boat.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\0.Small_Island\\Lighthouse&Bouy\\Lighthouse.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\0.Small_Island\\Lighthouse&Bouy\\Lighthouse_Buoy.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Tree_Island.png").GetFullPath());

		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\0.Small_Island\\MainBridge\\MainBridge_FrontTopper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Bridges\\ClipBridge\\ClipBridge_FrontTopper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Bridges\\ForestBridge\\ForestBridge_FrontTopper.png").GetFullPath());

		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Stairs\\BotanicStair\\BotanicStair_FrontTopper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Stairs\\RuseStair\\RuseStair_Topper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Stairs\\TreetopStair\\TreetopStair_FrontTopper.png").GetFullPath());
	}

	if (nullptr == Overworld_Bush_LeftRenderPtr) // ���� �� ��Ǯ��
	{
		Overworld_Bush_LeftRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		Overworld_Bush_LeftRenderPtr->SetScaleToTexture("Overworld_Bush_Left.png");
		Overworld_Bush_LeftRenderPtr->GetTransform()->SetLocalPosition({-652, 65, -10});
		Overworld_Bush_LeftRenderPtr->CameraCullingOn();
	}
	if (nullptr == Overworld_Bush_RightRenderPtr) // ������ �� ��Ǯ��
	{
		Overworld_Bush_RightRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		Overworld_Bush_RightRenderPtr->SetScaleToTexture("Overworld_Bush_Right.png");
		Overworld_Bush_RightRenderPtr->GetTransform()->SetLocalPosition({ 930, 45, -10 });
		Overworld_Bush_RightRenderPtr->CameraCullingOn();
	}
	if (nullptr == Mausoleum_BushRenderPtr) // �ڹ��� ��ġ ��Ǯ
	{
		//Mausoleum_BushRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		//Mausoleum_BushRenderPtr->SetScaleToTexture("Mausoleum_Bush.png");
		//Mausoleum_BushRenderPtr->GetTransform()->SetLocalPosition({ 1050, -600, -10 });
		//Mausoleum_BushRenderPtr->CameraCullingOn();
	}

	if (nullptr == DockRenderPtr) // ���� �� ��ũ
	{
		DockRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		DockRenderPtr->SetScaleToTexture("Dock.png");
		DockRenderPtr->GetTransform()->SetLocalPosition({ -1445, -190, -10 });
		DockRenderPtr->CameraCullingOn();
	}
	if (nullptr == BoatRenderPtr) // ���� �� ��
	{
		BoatRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BoatRenderPtr->SetScaleToTexture("Boat.png");
		BoatRenderPtr->GetTransform()->SetLocalPosition({ -1355, -295, -10 });
		BoatRenderPtr->CameraCullingOn();
	}

	if (nullptr == LighthouseRenderPtr)	// ���� �� ���
	{
		LighthouseRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		LighthouseRenderPtr->SetScaleToTexture("Lighthouse.png");
		LighthouseRenderPtr->GetTransform()->SetLocalPosition({ -1790, 550, -10 });
		LighthouseRenderPtr->CameraCullingOn();
	}
	if (nullptr == BuoyRenderPtr) // ���� �� ��ǥ
	{
		BuoyRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BuoyRenderPtr->SetScaleToTexture("Lighthouse_Buoy.png");
		BuoyRenderPtr->GetTransform()->SetLocalPosition({ -1660, 365, -10 });
		BuoyRenderPtr->CameraCullingOn();
	}
	if (nullptr == Tree_IslandRenderPtr) // �� �Ʒ� ��
	{
		Tree_IslandRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		Tree_IslandRenderPtr->SetScaleToTexture("Tree_Island.png");
		Tree_IslandRenderPtr->GetTransform()->SetLocalPosition({ 430, -850, -10 });
		Tree_IslandRenderPtr->CameraCullingOn();
	}

	if (nullptr == MainBridge_FrontTopperRenderPtr) // �ٸ� ����
	{
		MainBridge_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		MainBridge_FrontTopperRenderPtr->SetScaleToTexture("MainBridge_FrontTopper.png");
		MainBridge_FrontTopperRenderPtr->GetTransform()->SetLocalPosition({ -395, 25, -10 });
		MainBridge_FrontTopperRenderPtr->CameraCullingOn();
	}
	if (nullptr == ClipBridge_FrontTopperRenderPtr) // �ٸ� ����
	{
		ClipBridge_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ClipBridge_FrontTopperRenderPtr->SetScaleToTexture("ClipBridge_FrontTopper.png");
		ClipBridge_FrontTopperRenderPtr->GetTransform()->SetLocalPosition({ 763, -303, -10 });
		ClipBridge_FrontTopperRenderPtr->CameraCullingOn();
	}
	if (nullptr == ForestBridge_FrontTopperRenderPtr) // �ٸ� ����
	{
		ForestBridge_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ForestBridge_FrontTopperRenderPtr->SetScaleToTexture("ForestBridge_FrontTopper.png");
		ForestBridge_FrontTopperRenderPtr->GetTransform()->SetLocalPosition({ 375, 172, -10 });
		ForestBridge_FrontTopperRenderPtr->CameraCullingOn();
	}
	if (nullptr == PlaneBridge_FrontTopperRenderPtr) // �ٸ� ����
	{
		PlaneBridge_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		PlaneBridge_FrontTopperRenderPtr->SetScaleToTexture("ForestBridge_FrontTopper.png");
		PlaneBridge_FrontTopperRenderPtr->GetTransform()->SetLocalPosition({ 997, 747, -10 });
		PlaneBridge_FrontTopperRenderPtr->CameraCullingOn();
	}

	if (nullptr == BotanicStair_FrontTopperRenderPtr) // ��� ����
	{
		BotanicStair_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		BotanicStair_FrontTopperRenderPtr->SetScaleToTexture("BotanicStair_FrontTopper.png");
		BotanicStair_FrontTopperRenderPtr->GetTransform()->SetLocalPosition({ 123, -475, -10 });
		BotanicStair_FrontTopperRenderPtr->CameraCullingOn();
	}
	if (nullptr == RuseStair_TopperRenderPtr) // ��� ����
	{
		RuseStair_TopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RuseStair_TopperRenderPtr->SetScaleToTexture("RuseStair_Topper.png");
		RuseStair_TopperRenderPtr->GetTransform()->SetLocalPosition({ 47, 617, -10 });
		RuseStair_TopperRenderPtr->CameraCullingOn();
	}
	if (nullptr == TreetopStair_FrontTopperRenderPtr) // ��� ����
	{
		TreetopStair_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		TreetopStair_FrontTopperRenderPtr->SetScaleToTexture("TreetopStair_FrontTopper.png");
		TreetopStair_FrontTopperRenderPtr->GetTransform()->SetLocalPosition({ 772, 278, -10 });
		TreetopStair_FrontTopperRenderPtr->CameraCullingOn();
	}
	if (nullptr == HouseStair_FrontTopperRenderPtr) // ��� ����
	{
		HouseStair_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		HouseStair_FrontTopperRenderPtr->SetScaleToTexture("BotanicStair_FrontTopper.png");
		HouseStair_FrontTopperRenderPtr->GetTransform()->SetLocalPosition({ 1432, 35, -10 });
		HouseStair_FrontTopperRenderPtr->CameraCullingOn();
	}
	if (nullptr == ZeppelinStair_TopperRenderPtr) // ��� ����
	{
		ZeppelinStair_TopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ZeppelinStair_TopperRenderPtr->SetScaleToTexture("RuseStair_Topper.png");
		ZeppelinStair_TopperRenderPtr->GetTransform()->SetLocalPosition({ 1320, 642, -10 });
		ZeppelinStair_TopperRenderPtr->CameraCullingOn();
	}
}
void Overworld_Map::Update(float _DeltaTime)
{
}
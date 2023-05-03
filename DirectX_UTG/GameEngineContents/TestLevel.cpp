#include "PrecompileHeader.h"
#include "TestLevel.h"

#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineVideo.h>

#include "TestObject.h"
#include "Obj.h"
#include "TestLevel_Map.h"
#include "Player.h"

//#include "ImguiWindow.h"
#include "TransformGUI.h"

TestLevel::TestLevel()
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::PlayerCreate()
{
	std::shared_ptr<Player> Object = CreateActor<Player>(1);
	Object->GetTransform()->AddLocalPosition({ 240, -450 });
}

void TestLevel::Start()
{
	////////////////////////////////////////// ������ //////////////////////////////////////////////
	
	// Ű �ε� (�ӽ�)

	//{
	//	GameEngineDirectory NewDir;
	//	NewDir.MoveParentToDirectory("ContentResources");
	//	NewDir.Move("ContentResources");

	//	std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".avi", });

	//	for (size_t i = 0; i < File.size(); i++)
	//	{
	//		GameEngineVideo::Load(File[i].GetFullPath());
	//	}

	//	Video = GameEngineVideo::Find("TestVideo.avi");
	//	Video->Play();
	//}

	//{
	//	GameEngineDirectory NewDir;
	//	NewDir.MoveParentToDirectory("CupHead_Resource");
	//	NewDir.Move("CupHead_Resource");
	//	NewDir.Move("Image");
	//	NewDir.Move("Character");
	//	NewDir.Move("Overworld_NPCs");
	//	NewDir.Move("Axeman");
	//	NewDir.Move("Axeman_Idle");

	//	std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

	//	for (size_t i = 0; i < File.size(); i++)
	//	{
	//		GameEngineTexture::Load(File[i].GetFullPath());
	//	}
	//}

	//GetMainCamera()->SetProjectionType(CameraType::Perspective);
	//GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	//{
	//	std::shared_ptr<TestObject> Object = CreateActor<TestObject>();
	//}

	//{
	//	std::shared_ptr<Obj> Object = CreateActor<Obj>();
	//	Object->GetTransform()->SetLocalScale({ 1000, 1000, 1000 });
	//	Object->GetTransform()->SetLocalPosition({ 0, 0, 100.0f });
	//}

	////////////////////////////////////////// ������ //////////////////////////////////////////////
	
	// ���ҽ� �ε�
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("TestLevel");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}
	// �ӽ� �÷��̾� �̹��� �ε�
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("CH_Action");
		NewDir.Move("CHAc_Ground");
		NewDir.Move("CHAc_Ground_Idle");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	// ī�޶� ����
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });
	GetMainCamera()->GetTransform()->AddLocalPosition({ 240, -450 });

	// CreateActor
	// Background, Map
	{
		std::shared_ptr<TestLevel_Map> Object = CreateActor<TestLevel_Map>(-100);
		Object->GetTransform()->AddLocalPosition({2000/2, -720/2});
		
	}
	// Character

	//GameEngineGUI::GUIWindowCreate<ImguiWindow>("ImguiWindow");
	GameEngineGUI::GUIWindowCreate<TransformGUI>("TransformGUI");

	{
		PlayerObject = CreateActor<Player>(1);
		PlayerObject->GetTransform()->AddLocalPosition({ 240, -450 });

		GUI = GameEngineGUI::FindGUIWindowConvert<TransformGUI>("TransformGUI");
		GUI->SetTargetTransform(PlayerObject->GetTransform());
	}

	/*std::shared_ptr<ImguiWindow> Window = GameEngineGUI::FindGUIWindowConvert<ImguiWindow>("ImguiWindow");

	{
		if (nullptr == Window)
		{
			MsgAssert("������ �׽�Ʈ �ڵ� ���۵�");
		}

		Window->Test2 = std::bind(&TestLevel::PlayerCreate, this);
	}*/

	{
		/*std::shared_ptr<Player> Object = CreateActor<Player>(1);
		Object->GetTransform()->AddLocalPosition({ 240, -450 });*/
	}

}

void TestLevel::Update(float _DeltaTime)
{
	//if (true == GameEngineInput::IsPress("Action"))
	//{
	//	GameEngineCore::ChangeLevel("First_OpeningLevel");
	//}

	GUI->SetTargetTransform(PlayerObject->GetTransform());
}

void TestLevel::LevelChangeStart()
{
	GameEngineLevel::LevelChangeStart();
	int a = 0;
}

void TestLevel::LevelChangeEnd()
{
	GameEngineLevel::LevelChangeEnd();
	int a = 0;
}
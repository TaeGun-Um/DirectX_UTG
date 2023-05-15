#include "PrecompileHeader.h"
#include "GameEngineCore.h"
#include <GameEngineBase\GameEngineDebug.h>
#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEnginePlatform\GameEngineWindow.h>
#include <GameEnginePlatform\GameEngineSound.h>
#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEngineBase\GameEngineTime.h>
#include "GameEngineDevice.h"
#include "GameEngineVideo.h"
#include "GameEngineGUI.h"

std::map<std::string, std::shared_ptr<GameEngineLevel>> GameEngineCore::LevelMap;
std::shared_ptr<GameEngineLevel> GameEngineCore::MainLevel = nullptr;
std::shared_ptr<GameEngineLevel> GameEngineCore::NextLevel = nullptr;

GameEngineCore::GameEngineCore()
{
}

GameEngineCore::~GameEngineCore()
{
}

// Core�� ���� ���� (���ҽ�, ����, ���� Start)
void GameEngineCore::EngineStart(std::function<void()> _ContentsStart)
{
	GameEngineDevice::Initialize();

	// �޽��� CreateLevel ���� ������� �־�� �Ѵ�.
	// ���� �������� �ڽ��� ��, ��Ʈ ������ ��������� �Ѵ�.
	// ���� �ȳ����� ���� ���ϴ� Ÿ�ֿ̹� ���Ž�Ű�� ���� CoreResourcesEnd���� ����

	CoreResourcesInit();

	GameEngineGUI::Initialize();

	if (nullptr == _ContentsStart)
	{
		MsgAssert("���� �������� �������� �ʽ��ϴ�.");
	}
	_ContentsStart();
}

// Core�� ���� ����
void GameEngineCore::EngineUpdate()
{
	if (nullptr != NextLevel)
	{
		if (nullptr != MainLevel)
		{
			MainLevel->LevelChangeEnd();
		}

		MainLevel = NextLevel;

		if (nullptr != MainLevel)
		{
			MainLevel->LevelChangeStart();
		}

		NextLevel = nullptr;
		GameEngineTime::GlobalTime.Reset();
	}

	if (nullptr == MainLevel)
	{
		MsgAssert("�ƹ��� ������ �������� �ʰ� �ֽ��ϴ�.");
		return;
	}

	// ��ŸŸ�� üũ
	float TimeDeltaTime = GameEngineTime::GlobalTime.TimeCheck();

	if (TimeDeltaTime > 1 / 30.0f)
	{
		TimeDeltaTime = 1 / 30.0f;
	}

	GameEngineInput::Update(TimeDeltaTime);       // �Ҵ� �� ������ Key �� ������Ʈ
	GameEngineSound::SoundUpdate();               // FMOD Sound ������Ʈ

	MainLevel->TimeEvent.Update(TimeDeltaTime);   // Level�� TimeEvent ���� �� ������Ʈ
	MainLevel->AccLiveTime(TimeDeltaTime);
	MainLevel->Update(TimeDeltaTime);             
	MainLevel->ActorUpdate(TimeDeltaTime);        // Level�� Actor ���� �� ������Ʈ
	GameEngineDevice::RenderStart();              // ����� Ŭ����

	GameEngineVideo::VideoState State = GameEngineVideo::GetCurState();

	if (State != GameEngineVideo::VideoState::Running)
	{
		MainLevel->Render(TimeDeltaTime);
		MainLevel->ActorRender(TimeDeltaTime);    // Render�� �ǽø� HDC�� Ȱ���Ͽ� �̹��� ����
		GameEngineDevice::RenderEnd();            // ����ۿ� �̹��� ����
	}

	MainLevel->ActorRelease(); // �������
}

// Core�� ���� ���� (Level(map) clear, �Ҵ�� shared_ptr ����� ����, DirectX ����� ����(Release))
void GameEngineCore::EngineEnd(std::function<void()> _ContentsEnd)
{
	if (nullptr == _ContentsEnd)
	{
		MsgAssert("�� �������� �������� �ʽ��ϴ�.");
	}

	_ContentsEnd();

	GameEngineGUI::Release();
	LevelMap.clear();
	CoreResourcesEnd();
	GameEngineDevice::Release();
	GameEngineWindow::Release();
}

void GameEngineCore::Start(HINSTANCE _instance, std::function<void()> _Start, std::function<void()> _End, float4 _Pos, float4 _Size)
{
	GameEngineDebug::LeakCheck();

	if (false == GameEngineInput::IsKey("EngineMouseLeft"))
	{
		GameEngineInput::CreateKey("EngineMouseLeft", VK_LBUTTON);
		GameEngineInput::CreateKey("EngineMouseRight", VK_RBUTTON);
	}

	GameEngineWindow::WindowCreate(_instance, "MainWindow", _Size, _Pos);
	GameEngineWindow::WindowLoop(std::bind(GameEngineCore::EngineStart, _Start), GameEngineCore::EngineUpdate, std::bind(GameEngineCore::EngineEnd, _End));
}

void GameEngineCore::ChangeLevel(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (LevelMap.end() == LevelMap.find(UpperName))
	{
		MsgAssert("�������� �ʴ� ������ ü���� �Ϸ��� �߽��ϴ�.");
		return;
	}

	NextLevel = LevelMap[UpperName];
}

void GameEngineCore::LevelInit(std::shared_ptr<GameEngineLevel> _Level)
{
	_Level->Start();
}
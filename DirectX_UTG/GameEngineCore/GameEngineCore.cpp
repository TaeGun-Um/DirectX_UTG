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
GameEngineLevel* GameEngineCore::CurLoadLevel = nullptr;

GameEngineCore::GameEngineCore()
{
}

GameEngineCore::~GameEngineCore()
{
}

// Core의 시작 구간 (리소스, 액터, 레벨 Start)
void GameEngineCore::EngineStart(std::function<void()> _ContentsStart)
{
	GameEngineDevice::Initialize();

	// 메쉬는 CreateLevel 전에 만들어져 있어야 한다.
	// 보통 엔진에서 박스나 구, 렉트 정도는 지원해줘야 한다.
	// 릭은 안남지만 내가 원하는 타이밍에 제거시키기 위해 CoreResourcesEnd에서 삭제

	CoreResourcesInit();

	GameEngineGUI::Initialize();

	if (nullptr == _ContentsStart)
	{
		MsgAssert("시작 컨텐츠가 존재하지 않습니다.");
	}
	_ContentsStart();
}

// Core의 루프 구간
void GameEngineCore::EngineUpdate()
{
	if (nullptr != NextLevel)
	{
		std::shared_ptr<GameEngineLevel> PrevLevel = MainLevel;

		if (nullptr != MainLevel)
		{
			MainLevel->LevelChangeEnd();
			MainLevel->ActorLevelChangeEnd();
		}

		MainLevel = NextLevel;

		if (nullptr != MainLevel)
		{
			MainLevel->LevelChangeStart();
			MainLevel->ActorLevelChangeStart();
		}

		// PrevLevel
		// 레벨체인지가 완료된 시점에서 Texture의 상태를 한번 생각해봅시다.

		// 1은 가지고 있다.
		// GameEngineResources<GameEngineTexture>가 1개의 레퍼런스 카운트를 가지고 있을 것이다.

		// 이전레벨에 존재하는 TextureSetter내부에 보관되고 있는 애들은 2이상의 가지고 있을 것이다.

		// 3이상인 애들은 => 이전레벨과 지금레벨에서 모두 사용하는 
		// 애들 TextureResources에서도 들고 있을것이기 때문에 레퍼런스 카운트가 3이상이다.
		// 2인애들은 이전레벨에서만 사용하거나 지금레벨에서만 사용애들입니다.
		// 레퍼런스 카운트 관리해볼것이다.

		// Prev레벨에서 사용한 텍스처들

		PrevLevel;
		MainLevel;
		NextLevel = nullptr;
		GameEngineTime::GlobalTime.Reset();
	}

	if (nullptr == MainLevel)
	{
		MsgAssert("아무런 레벨도 동작하지 않고 있습니다.");
		return;
	}

	// 델타타임 체크
	float TimeDeltaTime = GameEngineTime::GlobalTime.TimeCheck();

	if (TimeDeltaTime > 1 / 30.0f)
	{
		TimeDeltaTime = 1 / 30.0f;
	}

	GameEngineInput::Update(TimeDeltaTime);       // 할당 후 변동된 Key 값 업데이트
	GameEngineSound::SoundUpdate();               // FMOD Sound 업데이트

	MainLevel->TimeEvent.Update(TimeDeltaTime);   // Level의 TimeEvent 변동 값 업데이트
	MainLevel->AccLiveTime(TimeDeltaTime);
	MainLevel->Update(TimeDeltaTime);             
	MainLevel->ActorUpdate(TimeDeltaTime);        // Level의 Actor 변동 값 업데이트
	GameEngineDevice::RenderStart();              // 백버퍼 클리어

	GameEngineVideo::VideoState State = GameEngineVideo::GetCurState();

	if (State != GameEngineVideo::VideoState::Running)
	{
		MainLevel->Render(TimeDeltaTime);
		MainLevel->ActorRender(TimeDeltaTime);    // Render를 실시며 HDC를 활용하여 이미지 수정
		GameEngineDevice::RenderEnd();            // 백버퍼에 이미지 랜더
	}

	MainLevel->ActorRelease(); // 릴리즈구조
}

// Core의 종료 구간 (Level(map) clear, 할당된 shared_ptr 명시적 해제, DirectX 명시적 해제(Release))
void GameEngineCore::EngineEnd(std::function<void()> _ContentsEnd)
{
	if (nullptr == _ContentsEnd)
	{
		MsgAssert("끝 컨텐츠가 존재하지 않습니다.");
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
		MsgAssert("존재하지 않는 레벨로 체인지 하려고 했습니다.");
		return;
	}

	NextLevel = LevelMap[UpperName];
}

void GameEngineCore::LevelInit(std::shared_ptr<GameEngineLevel> _Level)
{
	CurLoadLevel = _Level.get();
	_Level->Start();
	CurLoadLevel = nullptr;
}
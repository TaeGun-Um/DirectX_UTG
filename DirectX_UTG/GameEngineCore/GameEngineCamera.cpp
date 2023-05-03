#include "PrecompileHeader.h"
#include "PrecompileHeader.h"
#include "GameEngineCamera.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineDevice.h"

GameEngineCamera::GameEngineCamera()
{
}

GameEngineCamera::~GameEngineCamera()
{
}

void GameEngineCamera::Start()
{
	if (false == GameEngineInput::IsKey("CamMoveLeft"))
	{
		GameEngineInput::CreateKey("CamMoveLeft", 'A');
		GameEngineInput::CreateKey("CamMoveRight", 'D');
		GameEngineInput::CreateKey("CamMoveUp", 'Q');
		GameEngineInput::CreateKey("CamMoveDown", 'E');
		GameEngineInput::CreateKey("CamMoveForward", 'W');
		GameEngineInput::CreateKey("CamMoveBack", 'S');

		GameEngineInput::CreateKey("RotY+", VK_NUMPAD1);
		GameEngineInput::CreateKey("RotY-", VK_NUMPAD2);
		GameEngineInput::CreateKey("RotZ+", VK_NUMPAD4);
		GameEngineInput::CreateKey("RotZ-", VK_NUMPAD5);
		GameEngineInput::CreateKey("RotX+", VK_NUMPAD7);
		GameEngineInput::CreateKey("RotX-", VK_NUMPAD8);

		GameEngineInput::CreateKey("CamRot", VK_RBUTTON);
		GameEngineInput::CreateKey("SpeedBoost", VK_LSHIFT);
		GameEngineInput::CreateKey("FreeCameraSwitch", 'P');
		GameEngineInput::CreateKey("ProjectionModeChange", 'O');
	}

	// 뷰포트 구조체 설정
	// GameEngineMath의 ViewPort 인자와 동일한 인자 구성을 전달하면 된다.
	ViewPortData.TopLeftX = 0;                                   // 1. 화면 x축 시작 부분을 윈도우의 어디로 잡을 것인지. 0 이상 올리면 왼쪽에 빈 칸 생기고 출력됨
	ViewPortData.TopLeftY = 0;                                   // 2. 화면 y축 시작 부분을 윈도우의 어디로 잡을 것인지. 0 이상 올리면 위쪽에 빈 칸 생기고 출력됨
	ViewPortData.Width = GameEngineWindow::GetScreenSize().x;    // 3. 윈도우 너비 float
	ViewPortData.Height = GameEngineWindow::GetScreenSize().y;   // 4. 윈도우 높이 float
	ViewPortData.MinDepth = 0.0f;                                // 5. mindepth
	ViewPortData.MaxDepth = 1.0f;                                // 6. maxdepth, min과 max 설정 시 프로젝션 0.0f ~ 1.0f 내에서 또 특정 부분을 자른다. 안씀

	Width = ViewPortData.Width;
	Height = ViewPortData.Height;
}

void GameEngineCamera::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("ProjectionModeChange"))
	{
		switch (ProjectionType)
		{
		case CameraType::None:
			break;
		case CameraType::Perspective:
			ProjectionType = CameraType::Orthogonal;
			break;
		case CameraType::Orthogonal:
			ProjectionType = CameraType::Perspective;
			break;
		default:
			break;
		}
	}

	if (true == GameEngineInput::IsDown("FreeCameraSwitch"))
	{
		FreeCamera = !FreeCamera;

		if (true == FreeCamera)
		{
			OldData = GetTransform()->GetTransDataRef();
		}
		else {
			GetTransform()->SetTransformData(OldData);
		}
	}

	if (true == FreeCamera)
	{
		float RotSpeed = 180.0f;

		float Speed = 200.0f;

		if (true == GameEngineInput::IsPress("SpeedBoost"))
		{
			Speed = 1000.0f;
		}

		if (true == GameEngineInput::IsPress("CamMoveLeft"))
		{
			GetTransform()->AddLocalPosition(GetTransform()->GetWorldLeftVector() * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("CamMoveRight"))
		{
			GetTransform()->AddLocalPosition(GetTransform()->GetWorldRightVector() * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("CamMoveUp"))
		{
			GetTransform()->AddLocalPosition(GetTransform()->GetWorldUpVector() * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("CamMoveDown"))
		{
			GetTransform()->AddLocalPosition(GetTransform()->GetWorldDownVector() * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("CamMoveForward"))
		{
			GetTransform()->AddLocalPosition(GetTransform()->GetWorldForwardVector() * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("CamMoveBack"))
		{
			GetTransform()->AddLocalPosition(GetTransform()->GetWorldBackVector() * Speed * _DeltaTime);
		}

		if (true == GameEngineInput::IsPress("CamRot"))
		{
			float4 Dir = GameEngineInput::GetMouseDirectionNormal();

			float4 RotMouseDir;
			RotMouseDir.x = Dir.y;
			RotMouseDir.y = Dir.x;

			GetTransform()->AddWorldRotation(RotMouseDir);
		}

	}
}

void GameEngineCamera::Render(float _DeltaTime)
{
	// 뷰행렬을 만들기 위해서는 이 2개의 행렬이 필요하다.
	float4 EyeDir = GetTransform()->GetLocalForwardVector();
	float4 EyeUp = GetTransform()->GetLocalUpVector();
	float4 EyePos = GetTransform()->GetLocalPosition();

	View.LookToLH(EyePos, EyeDir, EyeUp);

	switch (ProjectionType)
	{
	case CameraType::None:
	{
		MsgAssert("카메라 투영이 설정되지 않았습니다.");
		break;
	}
	case CameraType::Perspective:
		Projection.PerspectiveFovLH(FOV, Width / Height, Near, Far);
		break;
	case CameraType::Orthogonal:
		Projection.OrthographicLH(Width, Height, Near, Far);
		break;
	default:
		break;
	}

	ViewPort.ViewPort(GameEngineWindow::GetScreenSize().x, GameEngineWindow::GetScreenSize().y, 0.0f, 0.0f);
}

// 뷰포트 세팅은 Camera가 세팅할 것이기 때문에 여기서 하는 것이다. GetCurrentCamera같은걸 만들어서 현재 카메라의 뷰포트 해주는 방식으로 해줘도 되지만
// 우리 뷰포트는 하나만 있을 예정이라 여기서 실시 후 GameEngineCore에서 실시
void GameEngineCamera::Setting()
{
	GameEngineDevice::GetContext()->RSSetViewports(1, &ViewPortData);
	// 1. 뷰포트도 여러 개 세팅이 가능하지만, 우리는 하나만 할 것
	// 2. 뷰포트 구조체. Camera의 Start에서 셋업
}
#include "PrecompileHeader.h"
#include <Windows.h>
#include <GameEngineBase\GameEngineFile.h>
#include <GameEngineBase\GameEngineDirectory.h>
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineContents\CupheadCore.h>

#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContents.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineCore::Start(hInstance, CupheadCore::GameStart, CupheadCore::GameEnd, { 0, 0 });
}

// 다이렉트 함수는 출력을 잘 봐야함.
// 상식적인 수준으로 오류를 전달해줌
// 
// 레스터라이저
// 레스터라이저도 우리 구조에서는 리소스
// 
// 프로그램가능단계 고정단계
// 인덱스버퍼나 다른 것들은 그냥 고정되어 있는 값만 넘기고 세팅을 어떻게 할 수 없음
// 
// Direct11의 랜더링파이프라인 단계는 고정기능 단계, 프로그래밍 가능 단계
// 쉐이더는 다 프로그래밍 가능 단계
// 나머지는 고정기능 단계
// 
// 쉽게 설명하면 내가 옵션 정도만 넘겨서 만드는 것.
// 이미 세팅은 다 되있는데, 이때 옵션만 이거로 해라 넘기는 것
// 프로그래밍 가능 단계는 특정 규칙만 지키면 맘대로 짤 수 있는 단계이다.
// 보통 쉐이더 단계는 코드를 넘기는 거니까 프로그래밍 가능 단계
// 래스터라이저나 아웃풋머저같은 단계는 고정 단계라고 함
// 
// 래스터라이저는 고정단계라는 것을 정확하게 알고 있어야 한다.
// 
// D3D11_RASTERIZEF_DESC Desc;
// ID3D11RasterizerState* << 보통 고정단계는 State를 넘기라고 한다.
// 
// 엔진에서 지원해주는 기본 세팅들은 전부다 EngineBase라고 지을 예정(약속)
// 
// 
// ResCreate에서 Desc 설정
// 
// 1. FilMode = 솔리드와 와이어 프레임이 있음/ 와이어 프레임 : 선으로 표헌 / 솔리드 : 면으로 표현
//           FilMode는 전환이 안된다. 순식간에 전환이 안됨. 그래서 언제나 와이어랑 솔리드 두개 다만들예정
//           랜파 클래스에서 SetFilemode() 함수를 통해 둘 다 만들것
// 
// ResCreate에서 Fillmode 와이어프레임
// GetDevice()->CreateResterizer(&Desc, 와이어프레임) 하고 하나 더 만듬 
// Filemode 솔리드
// GetDevice()->CreateResterizer(&Desc, 솔리드)
// 
// 2. CullMOde = 앞면 뒷면 상관없음(None)이 있는데, 사실 다 만들어야함
// 지금 당장은 Front로 하믄 댐
// 
// 사실 Recreate같은 걸 활용해서 다시 만들어도 빠르기 때문에, 하나만 정해놓고 해도 되지만,
// 
// SetCULLmode 한 뒤 ReCreate() 실시
// 그리고 Release 만듬
// 이러면 ReCreate하는 순간 Release를 넣으면 만들어진거 싹 지우고 다시 만드는 구조
// 게임 도중에 FileMode를 바꾸거나 cull을 바꾸거나 하는 일은 있을 수 없어서 괜찮음(여긴 엔진임)
// 
// 3. Cull Back = 삼각형이 앞면인지 뒷면인지 그걸 반전한다
// 
// 4. 픽셀에 깊이값 추가
// 
// 5. 픽셀의 최대 깊이 편향
// 
// 6. 거리에 따라 클리핑 활성화, 왼쪽 오른쪽 삐져나온거 잘라~ Depthclipenable이면 z도 짜름
// z 짜르기는 게임하다가 갑자기 생성되는 물체 생각하면 댐 그거임
// 
// 7 가위 사각형 컬링, 특정 렉트 구조체를 넣어서 함 그러면 그 바깥을 자르는건데 안할거임
//   모니터 안에서도 다시 네모를 넣어서 그거만 그릴래 할 때 쓰는 것
// 
// 8. 솔리드 방식일때의 안티얼라이어싱
// 
// 9 다중 샘플 안티얼라이어싱 대상에 ~ << 주변 흐릿하게 만드는거 켤래 안켤래~ true면 키는 것
// 그릴 때 라인으로 그리는거 있음 와이어프레임같은것. 그것도 안티얼라이어싱 할건지 물어보는 것
// 
// >> 지금 아무것도 넣을 필요가 ㅇㅄ음. FILL이랑 CULL만 넣으면 되기 때문. 나머지 000000 널널너런ㄹ
// 
// 일단 Front~ 까지만 true로
// 
// 여기까지하면 시계반대방향으로 항햐는 삼각형들을 면으로 출력해라~
// 
// 
// 다음은 픽셀쉐이더
// 
// 구조가 버텍스쉐이더랑 동일하고
// PsSetPixelshader() 하면 댐
// 
// 여기의 엔트리포인트는 PS
// 
// 픽셀쉐이더 이후는 아웃풋머저 단계에 들어감
// 아웃풋머저는 도화지를 깔고 여기다 그려라고 하는 것
// 근데 이 도화지를 동시에 5장그리기 할 수 있음 
// 그에 맞는 옵션이 있음, 이게 쉐이더 hlsl에 있음
// OutColor 구조체 선언 후
// SV_Target0
// SV_Target1
// SV_Target2
// SV_Target3
// SV_Target4
// 하면 RenderTarget 5개에 동시에 가능
// 근데 그럴 필요 없으니 0 하나만 만든다. 0번째 도화지에 출력하라가 된다.
// 
// 그리고 쉐이더는 지금과 같이 할 것임
// Texture_PS에는 Output 값이 들어옴
// Color.Color = _Value.Color << 지금은 버텍스 안에 RED 넣어놨음.
// 
// 이 쉐이더는
// 먼저 버텍스로 정점정보가 들어옴
// 그다음 레스터라이저 넘기기 용으로 Output 함
// 그러면 레스터라이저에서 w나누기 하고 정보가 PS로 OutPut으로 들어옴
// 그러면 그 안에 있던 컬러는? (레드레드레드) 그냥나옴
// 
// 픽셀들 건진 횟수 만큼 (일반적으로는 말도 안되는 수만큼) 포문이 돈다.
// 보통 글카는 1024를 동시에 출력할 수 있음
// 물론 좋으면 더 높아짐
// 
// 하고 SetPixelShader 생성
// 
// 
// 아웃풋머저는 여기서 세팅 안함
// 여러개의 랜더 타겟을 쓴다는 생각 안하고있고
// 디바이스가 랜더타겟 가지고 있음
// 그리고 랜더타겟 클래스를 리소스로 생성함
// 거기가서 Setting 클래스 생성
// OMSetRenderTargets()
// 1. svtarget0~123이 여러개 포인터로 셋팅하면 개조되게 만들 예정
//    지금 당장은 1
// 2. ID3D11RenderTargetView
// 3. 뭐가 앞에 나오고 뒤에나올지 결정하는건데, 지금 당장은 z값을 쓰지 않을 예정. 널포인터
// 
// 여기까지 한 뒤, OMSetRenderTargets은 RenderStart에서 Clear() 하고 실시
// 
// 랜파 착각하는게 하나 있음
// 세팅을 순서대로 해야한다는 착각을 함
// RenderStart에서 아웃풋머저 처음 실시하는 인터페이스인데, 사실 상관없어서 해도 됨
// 착각 ㄴ
// 
// 랜더파이프라인의 Render() 내의 랜파 순서가 뒤섞여도 상관없다는 뜻
// 아직 그린다는 행위는 하지 않았음 (REndering, Draw 같은 인터페이스로 그리지 않았음)
// 현재는 세팅 단계이다.
// 드로우 전 세팅하는걸 완성해놓는 중임
// 
// 세팅을 하는 순간 그리는게 아니라, 세팅된 걸 Draw 하는 것이다.
// Draw 하는 순간에 안채워져있는게 문제일뿐.
// 
// 전단계를 안채운다고 해서 다음 단계가 안채워지는게 아니다. 걱정 ㄴㄴ
// 
// 아웃풋머저까지 했으면 Draw 하면 되지만, 아직 안됨
// 랜파 jpg에서 왼쪽 보면 아직 덜 만든게 있기 때문.
// 
// 랜파클래스 REnder로 이동
// 다 끝났음.
// Device::GetCOntext->DrawIndexed() 실시
// 인덱스 버퍼가 세팅됐을 때만 이걸 사용해서 그릴 것
// 근데 우리 인터페이스는 인덱스버퍼를 세팅 안할 생각이 없어서 이걸로만 그릴 것임
// Auto는 버텍스에 있는 정보에 0 1 2 3 4 5로 그리겠다가 됨 (6개 필요, 4개면 못그림) 이런 식인데,
// DrawIndexed는 내가 번호까지 지정해서 그려주는 느낌이라 직관적임. 그래서 이걸로만 할것임
// 사실 나머지는 까먹어서 안쓴다고 함
// 
// 이미지 띄울거면 만들면 됨
// 외부 인터페이스를 하나도 안바꿀 것
// 
// 1. GetIndexCount()로 인덱스 갯수 가져옴 인덱스 버퍼에 넣어준 갯수 만큼 인덱스 카운트 넣었따
// 2. 인덱스 몇번쨰부터? 0
// 3. 버텍스 몇번쨰부터? 0
// 
// 까지 하면 오류가 막 뜰거임
// 
// 먼저 Primitive Topology 세팅해줘야 한다.
// 그리기 전에 인풋 어셈블러2 단계에서 IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY)
// D3D11_PRIMITIVE_TOPOLOGY : 트라이앵글리스트 삼각형으로 읽어라.
// 애초에 우리 랜파는 그렇게 디자인 되어 있으니.
// 
// 다음 에러들
// 뷰포트 세팅 안해줬다.
// 
// 뷰포트 세팅은 Camera가 세팅해줄 것이기 때문에, 
// 뭐 GetCurrentCamera같은걸 만들어서 현재 카메라의 뷰포트 해주는 방식으로 해주긴 한데,
// 우리 뷰포트는 하나만 있을 것임. 그래서 Camera에 Setting() 하나 만들고
// GameEngineDevice::GetContext()->RSSetViewport()
// 
// 1. 뷰포트도 여러개 세팅 가능, 우리는 1
// 2. D3D~ 이건 뷰포트 구조체, 헤더에 추가하고 언제 세팅되냐면 Start에서 하면 댐
//    애초에 우리의 math의 매개변수를 가져와서 그대로 Start에서 세팅해주면 된다.

//    1. 0, 화면 시작 부분을 윈도우 어디로 잡을 것인지.
//    2. 0, 화면의 레프트 시작 부분 윈도우 어디로?
//    3. 윈도우 너비 알려줘
//    4. 윈도우 높이 알려줘
//    5. 민댑스 0.0
//    6. 맥스댑스 1.0
//       >>민과 맥스댑스는 뭔가. 프로젝션하면 0 ~ 1까지 짤림. 근데 이거 하면 그 내부에서 또 잘라낼 수 있음. 근데 그럴 생각 없다.
// 3. RSViewport도 랜더타겟 하나마다 뷰포트 세팅에 차이를 둘 수 있음 (여러개 만들 수 있다는 뜼)
// 
// Core에 GetMainCarmara()->Setting 실시
// 
// 다음 오류
// 
// 버텍스 쉐이더에서 인풋데이터가 없다.
// 인풋레이아웃 낫셋~
// 이 에러는 
// 
// 앞서 버텍스쉐이더 만들때 인풋어셈블러1로 돌아와야한다고 얘기한적있음
// 시멘틱<<
// 첫번째가 포지션이고 두번째가 컬러인걸 표시한다 가 사실은 아님
// 뭔가 직접 만들어서 알려줘야함
// 참고로 GameEngineVertex에 변수의 순서가 바껴도 알려줄 수 있음
// 
// 내 Vertex의 구성이 어떻게 되어있는지 다 알려줘야 함 << 인풋 레이아웃을 만들어야 한다
// 만드는게 골때리긴함. 3D 끝날때까지 하나밖에 안만들것임. 여러개 만들 수 있긴 한데 안할거임.
// 버텍스쉐이더에 이 구조를 가진 것이 있나?
// 
// 버텍스버퍼로 이동
// GEDevice::CreateInputLayout() 실시
// 
// 3. 쉐이더바이트코드인풋시그니처 : 쉐이더의 바이너리코드를 달라. ID3D11Blob 넣어줌
// 
// 1. InputElementDesc.
//    GEVertex가 가지는게 맞다. 그쪽으로 이동
//    버텍스의 정보 순서를 누가 제일 잘 아나? << GEVertex임
// 
//    1. 배열을 달라. 시멘틱 POS의 name을 string으로 넣어줘야함
//    2. 포지션 몇번이냐 . 0번임 << 원래 2번째인데, 뒤로 미룸
//       포지션을 여러개 넣을 수 있긴 한데, 그러면 POSITION1 POSITION2 이렇게 할 수 있다는 것. 이거 일단 0으로
//    3. 포멧. float2? 3? 4? 어떤거냐~ 우리는 float4. DXGI_FORMAT_R32G32B32A32_FLOAT
//    4. Inputslot. 한 번에 버텍스 버퍼를 여러개 설정했을 때, 이건 몇 번째 버퍼냐고 물어보는 것.
//       근데 버텍스버퍼 여러개 세팅 안함(IASetBurttexBuffer의 ppVertexBuffer's')
//       첫 번째 네모, 두 번째 동그라미 셋팅 했다 하면, 첫 번째 인풋 따로, 두 번째 메쉬에 따로 인 데, 지금 우리는 버텍스 버퍼를 두 개 이상 세팅하지 않아서(헷갈리는 미친짓) 빵
//       n개의 버텍스 버퍼를 세팅할 때 n번째 버텍스 버퍼의 레이아웃이다!
//    5. 0번째 바이트부터 포멧크기만큼 위치해있다는 뜻. 포지션이면 0에서부터 16, 컬러면 16부터 32. 이걸 넣어줘야함. 그런데 이것도 뺌 (-1로 함)
//       우리한테 계산하라고 안함. 실수가 가장 많이 나오는 곳이 여기다.
//    6. 어떤 용도의 인풋레이아웃인지. VERTEX_DATA 용 인풋 레이아웃이다라는 뜻
//    7. 나~중에 인스턴싱이라는 구조를 만들 때 쓸 것이다. 인스턴싱을 한다면. 지금당장은 말해도 알려줄 수가 없다.
// 
// 그래서 지금은~ 첫번쨰 포지션 16바이트, 두번째 컬러 16바이트다 끝
//
// AddInputLayout() 후 푸쉬백할 예정
//
// CoreResourcesInit()에서 순서대로~ 넣어~
//
//
//
//
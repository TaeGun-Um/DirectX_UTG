#include "PrecompileHeader.h"
#include "GameEngineVertex.h"

// 1. LPCSTR SemanticName == 배열을 달라는 뜻. 시멘틱의 POSITION, COLOR 이런 것을 string으로 넣어줘야함 
// 2. DXGI_FORMAT Format == 자료형(Format)을 달라는 뜻. float4니까 DXGI_FORMAT_R32G32B32A32_FLOAT
// 3. D3D11_INPUT_CLASSIFICATION InputSlotClass == D3D11_INPUT_PER_VERTEX_DATA, 버텍스 데이터가 인스턴싱 데이터다 라는걸 표현
// 4. UINT InstanceDataStepRate == 0, 나중에 나중에 인스턴싱이라는 구조를 배울때 쓸때가 있을것이다.
// 5. UINT AlignedByteOffset == -1, 0번째 바이트부터 
// 6. UINT InputSlot == 0, 한 번에 버텍스 버퍼를 여러 개 생성n개의 버텍스 버퍼를 세팅할때 n번째 버텍스 버퍼의 인풋 레이아웃이다 라는걸 표현하는것
// 7. UINT SemanticIndex == 0.



// 2. 포지션 몇번이냐 . 0번임 << 원래 2번째인데, 뒤로 미룸
//    포지션을 여러개 넣을 수 있긴 한데, 그러면 POSITION1 POSITION2 이렇게 할 수 있다는 것. 이거 일단 0으로
// 4. Inputslot. 한 번에 버텍스 버퍼를 여러개 설정했을 때, 이건 몇 번째 버퍼냐고 물어보는 것.
//    근데 버텍스버퍼 여러개 세팅 안함(IASetBurttexBuffer의 ppVertexBuffer's')
//    첫 번째 네모, 두 번째 동그라미 셋팅 했다 하면, 첫 번째 인풋 따로, 두 번째 메쉬에 따로 인 데, 지금 우리는 버텍스 버퍼를 두 개 이상 세팅하지 않아서(헷갈리는 미친짓) 빵
//    n개의 버텍스 버퍼를 세팅할 때 n번째 버텍스 버퍼의 레이아웃이다!
// 5. 0번째 바이트부터 포멧크기만큼 위치해있다는 뜻. 포지션이면 0에서부터 16, 컬러면 16부터 32. 이걸 넣어줘야함. 그런데 이것도 뺌 (-1로 함)
//    우리한테 계산하라고 안함. 실수가 가장 많이 나오는 곳이 여기다.
// 6. 어떤 용도의 인풋레이아웃인지. VERTEX_DATA 용 인풋 레이아웃이다라는 뜻
// 7. 나~중에 인스턴싱이라는 구조를 만들 때 쓸 것이다. 인스턴싱을 한다면. 지금당장은 말해도 알려줄 수가 없다.

void GameEngineInputLayOut::AddInputLayOut(
	LPCSTR SemanticName,                         
	DXGI_FORMAT Format,                          
	D3D11_INPUT_CLASSIFICATION InputSlotClass,   
	UINT InstanceDataStepRate,                   
	UINT AlignedByteOffset,                      
	UINT InputSlot,                              
	UINT SemanticIndex                           
)
{
	D3D11_INPUT_ELEMENT_DESC Data;    // LayOut 구조체
	Data.SemanticName = SemanticName; // SemanticName은 변수 옆에 선언한 POSITION, COLOR 이런 것을 string으로 넣어달라는 뜻
	Descs.push_back(Data);            // 생성한 레이아웃 푸쉬백
}

GameEngineInputLayOut GameEngineVertex::LayOut;
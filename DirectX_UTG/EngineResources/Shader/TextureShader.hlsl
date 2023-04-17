
// 사실 쉐이더에서 월드프로젝션을 하려면, 외부에서 WorldMatrix를 알려줘야 한다.
// 이걸 가능하게 해주는 것이 바로 상수버퍼

// 콘스턴스 버퍼, 우리가 만든 행렬
// 텍스쳐, 그림 넣어야 나오지
// 바이트어드레스버퍼, 무시
// 스트럭쳐드버퍼, 무시

// 상수버퍼
// cbuffer TransformData : register(b0)
// {
//     int intValue0;
// }
// 다이렉트는 0번부터 16번까지 있다.
// b0 ~ b16까지 가능
// 이런 식으로 쓰면 내가 쓰겠다고 명시하는 것이다.
cbuffer TransformData : register(b0)
{
    float4x4 WorldMatrix;
}

// 셰이더는 빌드에 포함되지 않는다.

// 셰이더 규칙
// 어떤 정보가 들어올지에 대한 구조체를 만든다.
struct Input
{
    // 시멘틱 == 앞 : 뒤
    // 앞 == 뒤에 있는게 어떤 역할을 가졌는지에 대한 변수
    // 뒤 == 역할
    float4 Pos : POSITION;
    float4 Color : COLOR;
};

// void GameEngineVertexBuffer::Setting() 에서
// GameEngineDevice::GetContext()->IASetVertexBuffers(0, 1, &Buffer, &VertexSize, &Offset); 를 통해
// 공간 크기, 점 갯수, 배열 갯수에 대한 정보만 void 포인터를 통해 덩어리로 전달받게 된다.
// 이 데이터 덩어리에는 Position이나 Color와 같은 정보가 없기 때문에 내부가 어떻게 이뤄져야하는지 모르는 상태
// 내가 어떤 식으로 해당 데이터 덩어리를 해석할 것인지 구조체에서 시멘틱으로 해석하게 함

struct OutPut
{
    // SV_Position == 레스터라이져한테 w로 나눈 후 뷰포트를 곱하고 픽셀 건져낼 때 쓸 position 정보를 본인이 보낸 것이라고 알려주는 것(누굴 가지고 픽셀 건지기 할지 모르니 알려주는 것)
    // COLOR == 최초로 COLOR를 입력하면 COLOR[n]이 생성된다. 이건 구조체 내부의 COLOR가 COLOR0, COLOR1, COLOR2, ... 로 여러 개 선언될 수 있기 때문
    float4 Pos : SV_Position;
    float4 Color : COLOR;
};

// 외부에서 쉐이더를 컴파일할 때, EntryPount를 원하는 경우가 있다.
// 함수의 이름, "Texture_VS"를 입력하는 것이 EntryPoint 이다.

// 상수버퍼를 추가하면 b0 -> b1 -> b2 이런 식
// 기본적인 *(곱하기)는 같은 자료형만 가능하게 해뒀기 때문에
// 다른 형태의 자료형을 곱하려면 mul(뮬)을 이용해야 한다.
OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    OutPutValue.Pos = mul(_Value.Pos, WorldMatrix);
    // OutPutValue.Pos = _Value.Pos;
    OutPutValue.Color = _Value.Color;

    // OutPutValue.Pos *= 월드뷰프로젝션;
    
    return OutPutValue;
}

// 픽셀쉐이더 이후는 아웃풋머저 단계에 들어간다. 아웃풋머저는 도화지를 깔고(RenderTarget) 여기에 그리라고 하는 단계
// 여기서 동시에 5장 그리기 같은 것을 할 수 있다.
// 아래에서 
// float4 Color : SV_Target0;
// float4 Color : SV_Target1;
// float4 Color : SV_Target2;
// float4 Color : SV_Target3;
// float4 Color : SV_Target4;
// 이런 식으로 하면 동시에 RenderTarget 5개에 그릴 수 있음. 근데 그럴 필요 없으니 SV_Target0 하나만 만든다.

//struct OutColor
//{
//    float4 Color : SV_Target0; // 0번째 도화지에 출력하라
//};

// 픽셀쉐이더의 엔트리포인트는 PS, 여기에 OutPut 값이 들어온다.
// 이 쉐이더는 먼저 정점 정보가 들어온다. 그 다음 레스터라이저 넘기기용으로 Output 실시
// 그러면 레스터라이저에서 w나누기를 하고 PS에 OutPut으로 전달 된다.
// 이때, 디폴트 값은 Red이기 때문에 레드, 레드, 레드, 레드 이런 식으로 나올 것이다.
//OutColor Texture_PS(OutPut _Value)
//{
//    OutColor ReturnColor = (OutColor) 0;
//    ReturnColor.Color = _Value.Color;     // 지금은 디폴트 컬러를 Red로 넣어놨음, 아마 설정을 바꾸지 않으면 Red 도형이 출력될 예정
    
//    return ReturnColor;
//}

// 아웃풋머저에 0번 타겟에 출력된 float4를 레드로 출력하라는 뜻
float4 Texture_PS(OutPut _Value) : SV_Target0
{
    return float4(1.0f, 0.0f, 0.0f, 1.0f);
}
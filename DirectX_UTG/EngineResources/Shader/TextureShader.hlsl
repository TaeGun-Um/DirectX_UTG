
// 셰이더는 빌드에 포함되지 않는다.

// 셰이더 규칙
// 어떤 정보가 들어올지에 대한 구조체를 만든다.
struct Input 
{
    // 시멘틱 == 앞 : 뒤
    // 앞 == 뒤에 있는게 어떤 역할을 가졌는지에 대한 변수
    // 뒤 == 역할
	float4 Pos   : POSITION0;
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
OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut)0;
	
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.Color = _Value.Color;

    return OutPutValue;
}
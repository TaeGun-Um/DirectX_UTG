#include "PrecompileHeader.h"
#include "GameEngineVertex.h"

// 1. LPCSTR SemanticName                       == 배열을 달라는 뜻. 시멘틱의 POSITION, COLOR 이런 것을 string으로 넣어줘야함

// 2. DXGI_FORMAT Format                        == 자료형(Format)을 달라는 뜻. float4니까 DXGI_FORMAT_R32G32B32A32_FLOAT

// 3. D3D11_INPUT_CLASSIFICATION InputSlotClass == D3D11_INPUT_PER_VERTEX_DATA, 어떤 용도의 인풋레이아웃인지 전해줌. 버텍스 데이터가 인스턴싱 데이터다 라는걸 표현

// 4. UINT InstanceDataStepRate                 == 0, 나중에 나중에 인스턴싱이라는 구조를 배울때 쓸때가 있을것이다. 지금당장은 말해도 알려줄 수가 없다.

// 5. UINT AlignedByteOffset                    == -1, 0번째 바이트부터 포멧크기만큼 위치해있다는 뜻. 포지션이면 0에서부터 16, 컬러면 16부터 32. 이걸 넣어줘야함.
//                                                 그런데 이것도 뺄 것이다(-1로 함). 우리한테 계산하라고 안함. 실수가 가장 많이 나오는 곳이 여기다.

// 6. UINT InputSlot                            == 0, 한 번에 버텍스 버퍼를 여러 개 생성, n개의 버텍스 버퍼를 세팅할때 n번째 버텍스 버퍼의 인풋 레이아웃이다라는 것을 표현
//                                                 근데 버텍스버퍼 여러개 세팅 안함(IASetBurttexBuffer의 ppVertexBuffer's')
//                                                 첫 번째 네모, 두 번째 동그라미 셋팅 했다 하면 첫 번째 인풋 따로, 두 번째 메쉬에 따로 인데
//                                                 지금 우리는 버텍스 버퍼를 두 개 이상 세팅하지 않아서(헷갈리는 행위X) 0

// 7. UINT SemanticIndex                        == 0번이라는 뜻. 포지션을 여러개 넣을 수 있긴 한데, 그러면 POSITION1 POSITION2 이렇게 할 수 있다는 것. 일단 0으로 함.

void GameEngineInputLayOutInfo::AddInputLayOut(
	LPCSTR _SemanticName,                         
	DXGI_FORMAT _Format,                          
	D3D11_INPUT_CLASSIFICATION _InputSlotClass,   
	UINT _InstanceDataStepRate,                   
	UINT _AlignedByteOffset,                      
	UINT _InputSlot,                              
	UINT _SemanticIndex                           
)
{
	D3D11_INPUT_ELEMENT_DESC Data;                       // LayOut 구조체
	Data.SemanticName = _SemanticName;                   // SemanticName은 변수 옆에 선언한 POSITION, COLOR 이런 것을 string으로 넣어달라는 뜻
	Data.SemanticIndex = _SemanticIndex;                 // 시멘틱의 동일한 정보를 두 개 이상 넣으면 바꿔줘야 하지만 일단 0
	Data.Format = _Format;                               // 자료형
	Data.AlignedByteOffset = Offset;                     // 버텍스 포지션 몇번쨰부터 시작? 아래에 FormatSize()로 계산하게 한다.
	Data.InputSlotClass = _InputSlotClass;               // 인스턴싱 하면 보자
	Data.InputSlot = _InputSlot;                         // 인스턴싱에서 사용하는건데, 버텍스 버퍼를 중첩시키는 것. 인스턴싱 하면 보자
	Data.InstanceDataStepRate = _InstanceDataStepRate;   // 인스턴싱 하면 보자
	
	Offset += FormatSize(Data.Format);                   // Offset 자동 계산

	Descs.push_back(Data);                               // 생성한 레이아웃 푸쉬백
}

// 기존의 코드 복사해서 가져옴. AlignedByteOffset를 자료형에 따라 계산하여 Offset에 복사해준다.
UINT GameEngineInputLayOutInfo::FormatSize(DXGI_FORMAT _Format)
{
	switch (_Format)
	{
	case DXGI_FORMAT_UNKNOWN:
	{
		MsgAssert("몬가 잘못됐음");
		return -1;
	}
	case DXGI_FORMAT_R32G32B32A32_TYPELESS:
	case DXGI_FORMAT_R32G32B32A32_FLOAT:
	case DXGI_FORMAT_R32G32B32A32_UINT:
	case DXGI_FORMAT_R32G32B32A32_SINT:
		return 16;
	case DXGI_FORMAT_R32G32B32_TYPELESS:
	case DXGI_FORMAT_R32G32B32_FLOAT:
	case DXGI_FORMAT_R32G32B32_UINT:
	case DXGI_FORMAT_R32G32B32_SINT:
	case DXGI_FORMAT_R16G16B16A16_TYPELESS:
	case DXGI_FORMAT_R16G16B16A16_FLOAT:
	case DXGI_FORMAT_R16G16B16A16_UNORM:
	case DXGI_FORMAT_R16G16B16A16_UINT:
	case DXGI_FORMAT_R16G16B16A16_SNORM:
	case DXGI_FORMAT_R16G16B16A16_SINT:
	case DXGI_FORMAT_R32G32_TYPELESS:
	case DXGI_FORMAT_R32G32_FLOAT:
	case DXGI_FORMAT_R32G32_UINT:
	case DXGI_FORMAT_R32G32_SINT:
	case DXGI_FORMAT_R32G8X24_TYPELESS:
	case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
	case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
	case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
	case DXGI_FORMAT_R10G10B10A2_TYPELESS:
	case DXGI_FORMAT_R10G10B10A2_UNORM:
	case DXGI_FORMAT_R10G10B10A2_UINT:
	case DXGI_FORMAT_R11G11B10_FLOAT:
	case DXGI_FORMAT_R8G8B8A8_TYPELESS:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UINT:
	case DXGI_FORMAT_R8G8B8A8_SNORM:
	case DXGI_FORMAT_R8G8B8A8_SINT:
	case DXGI_FORMAT_R16G16_TYPELESS:
	case DXGI_FORMAT_R16G16_FLOAT:
	case DXGI_FORMAT_R16G16_UNORM:
	case DXGI_FORMAT_R16G16_UINT:
	case DXGI_FORMAT_R16G16_SNORM:
	case DXGI_FORMAT_R16G16_SINT:
	case DXGI_FORMAT_R32_TYPELESS:
	case DXGI_FORMAT_D32_FLOAT:
	case DXGI_FORMAT_R32_FLOAT:
	case DXGI_FORMAT_R32_UINT:
	case DXGI_FORMAT_R32_SINT:
		return 4;
	case DXGI_FORMAT_R24G8_TYPELESS:
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
	case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
	case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
	case DXGI_FORMAT_R8G8_TYPELESS:
	case DXGI_FORMAT_R8G8_UNORM:
	case DXGI_FORMAT_R8G8_UINT:
	case DXGI_FORMAT_R8G8_SNORM:
	case DXGI_FORMAT_R8G8_SINT:
	case DXGI_FORMAT_R16_TYPELESS:
	case DXGI_FORMAT_R16_FLOAT:
	case DXGI_FORMAT_D16_UNORM:
	case DXGI_FORMAT_R16_UNORM:
	case DXGI_FORMAT_R16_UINT:
	case DXGI_FORMAT_R16_SNORM:
	case DXGI_FORMAT_R16_SINT:
	case DXGI_FORMAT_R8_TYPELESS:
	case DXGI_FORMAT_R8_UNORM:
	case DXGI_FORMAT_R8_UINT:
	case DXGI_FORMAT_R8_SNORM:
	case DXGI_FORMAT_R8_SINT:
	case DXGI_FORMAT_A8_UNORM:
	case DXGI_FORMAT_R1_UNORM:
	case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
	case DXGI_FORMAT_R8G8_B8G8_UNORM:
	case DXGI_FORMAT_G8R8_G8B8_UNORM:
	case DXGI_FORMAT_BC1_TYPELESS:
	case DXGI_FORMAT_BC1_UNORM:
	case DXGI_FORMAT_BC1_UNORM_SRGB:
	case DXGI_FORMAT_BC2_TYPELESS:
	case DXGI_FORMAT_BC2_UNORM:
	case DXGI_FORMAT_BC2_UNORM_SRGB:
	case DXGI_FORMAT_BC3_TYPELESS:
	case DXGI_FORMAT_BC3_UNORM:
	case DXGI_FORMAT_BC3_UNORM_SRGB:
	case DXGI_FORMAT_BC4_TYPELESS:
	case DXGI_FORMAT_BC4_UNORM:
	case DXGI_FORMAT_BC4_SNORM:
	case DXGI_FORMAT_BC5_TYPELESS:
	case DXGI_FORMAT_BC5_UNORM:
	case DXGI_FORMAT_BC5_SNORM:
	case DXGI_FORMAT_B5G6R5_UNORM:
	case DXGI_FORMAT_B5G5R5A1_UNORM:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
	case DXGI_FORMAT_B8G8R8X8_UNORM:
	case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
	case DXGI_FORMAT_B8G8R8A8_TYPELESS:
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8X8_TYPELESS:
	case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
	case DXGI_FORMAT_BC6H_TYPELESS:
	case DXGI_FORMAT_BC6H_UF16:
	case DXGI_FORMAT_BC6H_SF16:
	case DXGI_FORMAT_BC7_TYPELESS:
	case DXGI_FORMAT_BC7_UNORM:
	case DXGI_FORMAT_BC7_UNORM_SRGB:
	case DXGI_FORMAT_AYUV:
	case DXGI_FORMAT_Y410:
	case DXGI_FORMAT_Y416:
	case DXGI_FORMAT_NV12:
	case DXGI_FORMAT_P010:
	case DXGI_FORMAT_P016:
	case DXGI_FORMAT_420_OPAQUE:
	case DXGI_FORMAT_YUY2:
	case DXGI_FORMAT_Y210:
	case DXGI_FORMAT_Y216:
	case DXGI_FORMAT_NV11:
	case DXGI_FORMAT_AI44:
	case DXGI_FORMAT_IA44:
	case DXGI_FORMAT_P8:
	case DXGI_FORMAT_A8P8:
	case DXGI_FORMAT_B4G4R4A4_UNORM:
	case DXGI_FORMAT_P208:
	case DXGI_FORMAT_V208:
	case DXGI_FORMAT_V408:
	case DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE:
	case DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE:
	case DXGI_FORMAT_FORCE_UINT:
	{
		MsgAssert("크기를 아직 책정하지 않은 포맷을 받았습니다.");
		return -1;
	}
	default:
		break;
	}

	MsgAssert("뭘한거냐????");
	return -1;
	// ???????
}

GameEngineInputLayOutInfo GameEngineVertex::LayOut;
#include "PrecompileHeader.h"
#include "GameEngineVertex.h"

// 1. LPCSTR SemanticName                       == �迭�� �޶�� ��. �ø�ƽ�� POSITION, COLOR �̷� ���� string���� �־������

// 2. DXGI_FORMAT Format                        == �ڷ���(Format)�� �޶�� ��. float4�ϱ� DXGI_FORMAT_R32G32B32A32_FLOAT

// 3. D3D11_INPUT_CLASSIFICATION InputSlotClass == D3D11_INPUT_PER_VERTEX_DATA, � �뵵�� ��ǲ���̾ƿ����� ������. ���ؽ� �����Ͱ� �ν��Ͻ� �����ʹ� ��°� ǥ��

// 4. UINT InstanceDataStepRate                 == 0, ���߿� ���߿� �ν��Ͻ��̶�� ������ ��ﶧ ������ �������̴�. ���ݴ����� ���ص� �˷��� ���� ����.

// 5. UINT AlignedByteOffset                    == -1, 0��° ����Ʈ���� ����ũ�⸸ŭ ��ġ���ִٴ� ��. �������̸� 0�������� 16, �÷��� 16���� 32. �̰� �־������.
//                                                 �׷��� �̰͵� �� ���̴�(-1�� ��). �츮���� ����϶�� ����. �Ǽ��� ���� ���� ������ ���� �����.

// 6. UINT InputSlot                            == 0, �� ���� ���ؽ� ���۸� ���� �� ����, n���� ���ؽ� ���۸� �����Ҷ� n��° ���ؽ� ������ ��ǲ ���̾ƿ��̴ٶ�� ���� ǥ��
//                                                 �ٵ� ���ؽ����� ������ ���� ����(IASetBurttexBuffer�� ppVertexBuffer's')
//                                                 ù ��° �׸�, �� ��° ���׶�� ���� �ߴ� �ϸ� ù ��° ��ǲ ����, �� ��° �޽��� ���� �ε�
//                                                 ���� �츮�� ���ؽ� ���۸� �� �� �̻� �������� �ʾƼ�(�򰥸��� ����X) 0

// 7. UINT SemanticIndex                        == 0���̶�� ��. �������� ������ ���� �� �ֱ� �ѵ�, �׷��� POSITION1 POSITION2 �̷��� �� �� �ִٴ� ��. �ϴ� 0���� ��.

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
	D3D11_INPUT_ELEMENT_DESC Data;    // LayOut ����ü
	Data.SemanticName = SemanticName; // SemanticName�� ���� ���� ������ POSITION, COLOR �̷� ���� string���� �־�޶�� ��
	Descs.push_back(Data);            // ������ ���̾ƿ� Ǫ����
}

GameEngineInputLayOut GameEngineVertex::LayOut;
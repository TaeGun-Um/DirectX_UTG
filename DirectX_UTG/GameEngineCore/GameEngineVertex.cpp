#include "PrecompileHeader.h"
#include "GameEngineVertex.h"

// 1. LPCSTR SemanticName == �迭�� �޶�� ��. �ø�ƽ�� POSITION, COLOR �̷� ���� string���� �־������ 
// 2. DXGI_FORMAT Format == �ڷ���(Format)�� �޶�� ��. float4�ϱ� DXGI_FORMAT_R32G32B32A32_FLOAT
// 3. D3D11_INPUT_CLASSIFICATION InputSlotClass == D3D11_INPUT_PER_VERTEX_DATA, ���ؽ� �����Ͱ� �ν��Ͻ� �����ʹ� ��°� ǥ��
// 4. UINT InstanceDataStepRate == 0, ���߿� ���߿� �ν��Ͻ��̶�� ������ ��ﶧ ������ �������̴�.
// 5. UINT AlignedByteOffset == -1, 0��° ����Ʈ���� 
// 6. UINT InputSlot == 0, �� ���� ���ؽ� ���۸� ���� �� ����n���� ���ؽ� ���۸� �����Ҷ� n��° ���ؽ� ������ ��ǲ ���̾ƿ��̴� ��°� ǥ���ϴ°�
// 7. UINT SemanticIndex == 0.



// 2. ������ ����̳� . 0���� << ���� 2��°�ε�, �ڷ� �̷�
//    �������� ������ ���� �� �ֱ� �ѵ�, �׷��� POSITION1 POSITION2 �̷��� �� �� �ִٴ� ��. �̰� �ϴ� 0����
// 4. Inputslot. �� ���� ���ؽ� ���۸� ������ �������� ��, �̰� �� ��° ���۳İ� ����� ��.
//    �ٵ� ���ؽ����� ������ ���� ����(IASetBurttexBuffer�� ppVertexBuffer's')
//    ù ��° �׸�, �� ��° ���׶�� ���� �ߴ� �ϸ�, ù ��° ��ǲ ����, �� ��° �޽��� ���� �� ��, ���� �츮�� ���ؽ� ���۸� �� �� �̻� �������� �ʾƼ�(�򰥸��� ��ģ��) ��
//    n���� ���ؽ� ���۸� ������ �� n��° ���ؽ� ������ ���̾ƿ��̴�!
// 5. 0��° ����Ʈ���� ����ũ�⸸ŭ ��ġ���ִٴ� ��. �������̸� 0�������� 16, �÷��� 16���� 32. �̰� �־������. �׷��� �̰͵� �� (-1�� ��)
//    �츮���� ����϶�� ����. �Ǽ��� ���� ���� ������ ���� �����.
// 6. � �뵵�� ��ǲ���̾ƿ�����. VERTEX_DATA �� ��ǲ ���̾ƿ��̴ٶ�� ��
// 7. ��~�߿� �ν��Ͻ��̶�� ������ ���� �� �� ���̴�. �ν��Ͻ��� �Ѵٸ�. ���ݴ����� ���ص� �˷��� ���� ����.

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
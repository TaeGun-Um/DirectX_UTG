#include <Windows.h>
#include <GameEngineBase\GameEngineFile.h>
#include <GameEngineBase\GameEngineDirectory.h>
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineContents\ContentsCore.h>

#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContents.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineCore::Start(hInstance, ContentsCore::GameStart, ContentsCore::GameEnd, { 0, 0 });
}

// 
// D3D11CreateDevice() ���ڰ� �� ����.
// 1. �� ��ġ�� ���ؼ� ������� �����
// 2. ���� �־ �������. �̷��� �ؼ� ����͸� ������� ���� ��, ��͸� �ȳ־��ָ� (�η� �־��ָ�) �˾Ƽ� ã�Ƽ� ������ֱ� ��.
//	  ����ͷ� �� �� SOFTWARE(CPU�� �׷���)�� HARDWARE(�׷���ī��� �׷���)�� ����.
// 3. ����͸� ���Ա� ������ 0�� �ְų� ���� ���� �� �ִµ�, �Լ� �ȿ��� �˾Ƽ� ���డ �ȴ�.
// 4. iFlag�� ����׸� ����׷� ������డ �ȴ�.
// 5. FeatureLevel�� �������°ǵ�, ���� ������ �� �����ʹ޶�� �ϴ� ��
// 6. 0�� ������ �˾Ƽ� ���ش�.
// 7. ���̷�Ʈ�� SDK ������ �ִµ�, D3D11_SDK_VERSION�� ������ �׳� �ش� �����쿡�� �����ϴ� SDK ������ define ��
//    SDK == ����Ʈ���� �𺧷Ӹ�Ʈ ŰƮ, ����Ʈ���� �����ڿ� ŰƮ (lib, header �� ������)
// 8. ����̽�
// 9. ����, ���ʿ� 11�̱� ������ �ȳ־ 11��
// 
// ���������� ������ ���̷�Ʈ ������ �Ѿ�´�.
// 
// 7, 8, 9�� �����Ҵ� �ѰͰ� �ٸ� ����. ������ ������ ���� ��������� ȣ���ϴ� �������̽� ����->coreend���� ȣ��
// 
// ������� �ϸ� ����̽��� ���������.
// ���� ������ (â)�� �����ϴ� �۾��� ������Ѵ�.
// ��, ����� ����� �۾��� ����� �Ѵ�.
// ������ ��, �׸�(2���� �迭)�� GPU�� ����ǰ� �װ��� ������ ���� ���� swapchain�� ������ �Ѵ�.
// 
// CreateSwapChain�� �Ϸ���
// 1. â ũ�� == ������â ũ�⸦ �˾ƾ���. ����� �ٲ�� ����̽� �����ٰ� �ٽ� ������ �Ѵ�.
//              ���ӿ��� â ũ�� �����ϸ� ��� ���߰� �ε��. �̰� ����̽� �� �� �����, ���ҽ� �� �� ����� �ٽ� ���� �ε��ϴ� ������ ���ľ��Ѵ�.
// 	            �̰� ���Ұ���
// 
// 2. DXGI_SWAP_CHAIN_DESC == ��κ� 0 ������ �⺻ �������� ������ ���̴�.
//    BufferCount = 2; WinApi�� ���� ���۸� ��İ� ����. ������ �ٸ� �� ������ �ٷ��� ��ī�� ����� ���°͸� �����ְ� �ٸ���.
//    BufferDexc.Width = unsigned int
//    BufferDesc.Height = unsigned
//    OutputWindow = � ������(â)�� ��� ���ΰ� == �ڵ�
//    BufferDesc.Refreshrate.Denominator = �ּ� ȭ�� ���ŷ�
//    BufferDesc.Refreshrate. == �ִ� ȭ�� ���ŷ�
//    BufferDesc.Format = DXGU_FORMAT_R8G8B8A8_UNORM (1byte, 1byte, 1byte, 1byte �������� �����޶�.)  // DXGI_FORMAT_420_OPAQUE(float�ε�, 32bit, 32bit, 32bit 4k���̴�.)
//    BufferDesc.Scanline = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED == �̹����� �ϳ� �׷��� ��, ����Ե� ����� ��ü�� ������ ���� �Ʒ��� ��ĵ�������� �׸�. �װ� ����
//    BufferDesc.Sacling = ��� �ȳ�
//    BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE+SHADER_INPUT   == �� ����ü���� �ܼ��� Ư�� ����Ϳ��� �׸��� �뵵�� ����°� �ƴ϶�, ���� ������ �ɼ��� ���ؼ� ���� �� �ִ�.
//                                                                    �����찡 �ϳ��ϱ� �ϳ���? �ƴϴ�. �� ���¿����� �������� ���� �� �ִ�. ���� �뵵�� Ư�� �����쿡 ������ 
//                                                                    ���� �ɼ��� ������ ���̷�Ʈ�� �����ϴ� ���̴�. ���̴������� �̰� ����� �� �ֵ��� �ϰڴٴ� ��.
//    SampleDesc.Quality = 0 // �ڵ����� �ش޶�� ��
//    SampleDesc.Count = 1   // ����Ƽ 1¥�� �����޶�� ���� �ƴ�.
// 
// ���ø�
// 
// ȭ�鿡 ���� �׸� ��, 
//
// ��Ƽ����̾��
// �ε巴�� ���̵��� �����ִ� ��. MSAA�� ��Ƽ����̾�� �˰����̴�.
// ����ʹ� �̹� �ȼ��� 2���� �迭�� ���̴�.
// �ȼ��� ������ ����.
// ������ �̷��� ���� ������ �׸��� �ʹ�.
// �ȼ��� ���ڸ��� ������ ��
// ������ ���� ������ ���� = ����
// ���� = ����
// �̷��� �ȼ� �ϳ��� ���� ��ġ�Ѵ�. ���� ���� ���� ���� ���� �� ǥ���� ��������, ��� �κ� üũ�� ������.
// 1�ʿ� for���� 1280x720�� ��Ƽ����̾�� ���ϱ� ��ŭ ����. (1280 x 720 x 8 = 720��)
//
// ���귮�� ���ϱ� ������ �ļ��� ���� �θ�
// ������ FXAA �˰���
//
//
//
//
//
//
//
//
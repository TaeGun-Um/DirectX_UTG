#include "PrecompileHeader.h"
#include "GameEngineVertexShader.h"

GameEngineVertexShader::GameEngineVertexShader()
{
	Type = ShaderType::Vertex;
}

GameEngineVertexShader::~GameEngineVertexShader()
{
	if (nullptr != ShaderPtr)
	{
		ShaderPtr->Release();
		ShaderPtr = nullptr;
	}
}

// ���̴� ������ �ǽ�
void GameEngineVertexShader::ShaderLoad(const std::string_view& _Path ,const std::string_view& _EntryPoint ,UINT _VersionHigh /*= 5*/ ,UINT _VersionLow /*= 0*/)
{
	CreateVersion("vs", _VersionHigh, _VersionLow);
	SetEntryPoint(_EntryPoint);

	unsigned int Flag = 0;

#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;

#endif
	// ������� �Ҷ� �̿ɼ��� ������ �ִ�. ���߿� ��� ������ �� �˷��޶�� ���
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	// ID3DBlob ���� �ʿ�, �����߻� �� �ش� �����Ϳ� ���� �޼����� ���޵�(�ϴ��� if ������ Ȯ��)
	ID3DBlob* Error;

	// ��δ� �����ڵ�ȭ �Ͽ� ���޹޾ƾ� �Ѵ�.
	std::wstring UniCodePath = GameEngineString::AnsiToUniCode(_Path);

	if (S_OK != D3DCompileFromFile          // ���̴��� ��θ� �˷��ָ� �������� ���ִ� �Լ��̴�.
	(
		UniCodePath.c_str(),                // �����ڵ�ȭ�� ��� wstring�� ��� ����
		nullptr,                            // ��������, #defined�� Ȱ������ ����, ���� ���̴��� 4���� �̻� �ڵ��ϰ� #defined�� ���� ��쿡 ���� �� �����, �� ����η� �ٲ㰡�� ���̴� �Լ��� ȣ��������, ���� �Ⱦ� ����(�Ƹ� ��� �Ⱦ� ���� ����, �׷��� ��������)
		D3D_COMPILE_STANDARD_FILE_INCLUDE,  // �ش� ���̴� ���� #include�� ������� ��, ��¿ �� include �ϰ� ��¿ �� ���ϴ� ��찡 �ֱ� �ѵ�, �׳� ���̴� �ڵ� �ȿ��� #include�ϰ� ����� �����̴�.
		EntryPoint.c_str(),                 // EntryPoint ����
		Version.c_str(),                    // Version ����
		Flag,                               // ����� ����� �� Flag(D3D10_SHADER_DEBUG)�� �ش޶�� ��, D11�� ���� D10�� �ִ�. ���̷�Ʈ�� D11�� �ȹٲ���
		0,                                  // �˾Ƽ� �϶�� ��
		&BinaryCode,                        // ���� �����ʹ� ������ ���� ����ȴ�. ���̴� �ڵ带 �׷���ī�忡�� �������� ��, �Ѱܹ޴� ���̳ʸ��ڵ带 ����
		&Error                              // �������� ���⿡ �� ����
	)
		)
	{
		// S_OK�� �ƴ� ���, reinterpret_cast<char*>(Error->GetBufferPointer())�� string���� ������
		// � ������ �߻��ߴ��� �� �� �ִ�. �̰��� �츮�� MsgAssert�� ���ڷ� ���� �� Assert �ǽ�
		std::string ErrorString = reinterpret_cast<char*>(Error->GetBufferPointer());
		MsgAssert(ErrorString);
		return;
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreateVertexShader
	(
		BinaryCode->GetBufferPointer(),  // ���̳ʸ��ڵ��� ���������� ��������
		BinaryCode->GetBufferSize(),     // ���̳ʸ��ڵ��� ���ۻ����� ��������
		nullptr,                         // ������� ���� �־��� ��� �����޶�� ��
		&ShaderPtr                       // ShaderPtr�� �� ����
	)
		)
	{
		MsgAssert("���ؽ� ���̴� �ڵ� ������ �����߽��ϴ�");
		return;
	}

	// GameEngineConstantBuffer�� ShaderResCheck ����
	ShaderResCheck();
}

// VertexShader Setting �ܰ�, Load �� ���� ������ ShaderPtr�� Ȱ��
void GameEngineVertexShader::Setting()
{
	if (nullptr == ShaderPtr)
	{
		MsgAssert("���ؽ� ���̴��� �������� �ʽ��ϴ� ���ÿ� �����߽��ϴ�.");
		return;
	}

	GameEngineDevice::GetContext()->VSSetShader(ShaderPtr, nullptr, 0);
	// 1�� : Load�� �� ����� ���ؽ�������
	// 2�� : �ʿ���� ������ ��������
	// 3�� : �ʿ���� ������ 0
}
#include "PrecompileHeader.h"
#include "GameEngineShaderResHelper.h"
#include "GameEngineShader.h"
#include "GameEngineConstantBuffer.h"

// ConstantBuffer를 순회하며 필요로 하는 GameEngineShaderResHelper를 복사
void GameEngineShaderResHelper::Copy(const GameEngineShaderResHelper& _ResHelper)
{
	for (const std::pair<std::string, GameEngineConstantBufferSetter>& Setter : _ResHelper.ConstantBuffer)
	{
		ConstantBuffer.insert(Setter);
	}
}

// 상수 버퍼 세팅을 ParentShader로 구분하고, Type에 맞는 쉐이더 세팅 실시
void GameEngineConstantBufferSetter::Setting()
{
	// 여기서 세팅 처음에 이걸 실시(GPU에게 Map하고 값 복사하고 Umap하는 행동)하고 Type에 맞춰 쉐이더 세팅한다.
	Res->ChangeData(CPUData, CPUDataSize);

	ShaderType Type = ParentShader->GetType();  // 어떤 쉐이더인지 구분하기 위해 GetType

	switch (Type)
	{
	case ShaderType::None:   // 부모(쉐이더)가 아무것도 아닐 경우 (오류)
	{
		MsgAssert("어떤 쉐이더에 세팅될지 알수없는 상수버퍼 입니다.");
		break;
	}
	case ShaderType::Vertex: // 부모(쉐이더)가 버텍스일 경우
	{
		Res->VSSetting(BindPoint);
		break;
	}
	case ShaderType::Pixel:  // 부모(쉐이더)가 픽셀일 경우
	{
		Res->PSSetting(BindPoint);
		break;
	}
	default:
		break;
	}

}

// ~Setter는 세팅된 리소스(상수 버퍼, 텍스쳐 등)를 가지고 있다.
// 여기서 상수 버퍼는 문제가 조금 있는데, 모든 쉐이더에서 사용하기 때문이다.
// 이를 구분하기 위해, 멀티맵에서 어떤 쉐이더인지 구분하고, 그에 따라 Setting이 되도록 switch문 실시
void GameEngineShaderResHelper::Setting()
{
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator StartIter = ConstantBuffer.begin();
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator EndIter = ConstantBuffer.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		GameEngineConstantBufferSetter& Setter = StartIter->second;
		Setter.Setting();
	}
}

// 이름이 링크인 이유는, 복사된 랜더러의 ResHelper 내에 초기값이 적용(빨간색에 배경!)됐다고 해도, 이후에 값을 변경하면 변경되기 때문에 링크라고 지었습니다.
void GameEngineShaderResHelper::SetConstantBufferLink(const std::string_view& _Name, const void* _Data, UINT _Size)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator FindIter = ConstantBuffer.find(UpperName);

	if (ConstantBuffer.end() == FindIter)
	{
		MsgAssert("존재하지 않는 상수버퍼를 세팅하려고 했습니다." + UpperName);
		return;
	}

	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator NameStartIter = ConstantBuffer.lower_bound(UpperName); // 같은 이름 중(Key 중) 가장 앞에 있는 것
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator NameEndIter = ConstantBuffer.upper_bound(UpperName);   // 같은 이름 중(Key 중) 가장 뒤에 있는 것

	for (; NameStartIter != NameEndIter; ++NameStartIter)
	{
		GameEngineConstantBufferSetter& Setter = NameStartIter->second;

		if (Setter.Res->GetBufferSize() != _Size)
		{
			MsgAssert("상수버퍼와 세팅하려는 데이터의 크기가 다릅니다.\n 상수버퍼 : " + std::to_string(Setter.Res->GetBufferSize()) + "\n유저가 세팅한 데이터 : " + std::to_string(_Size) + UpperName);
			return;
		}

		Setter.CPUData = _Data;      // 링크로 함수 호출하면 CPUData에 자료형 입력
		Setter.CPUDataSize = _Size;  // 이러면 저장된 자료형 데이터 크기와 상수 버퍼 데이터 크기가 다르면 오류날 것임
	}

}
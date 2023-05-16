#include "PrecompileHeader.h"
#include "GameEngineShaderResHelper.h"
#include "GameEngineShader.h"
#include "GameEngineConstantBuffer.h"

// 쉐이더의 리소스 정보를 랜더러에 카피
void GameEngineShaderResHelper::Copy(const GameEngineShaderResHelper& _ResHelper)
{
	// 상수 버퍼 리소스 카피
	for (const std::pair<std::string, GameEngineConstantBufferSetter>& Setter : _ResHelper.ConstantBufferSetters)
	{
		ConstantBufferSetters.insert(Setter);
	}
	// 텍스쳐 리소스 카피
	for (const std::pair<std::string, GameEngineTextureSetter>& Setter : _ResHelper.TextureSetters)
	{
		TextureSetters.insert(Setter);
	}
	// 샘플러 리소스 카피
	for (const std::pair<std::string, GameEngineSamplerSetter>& Setter : _ResHelper.SamplerSetters)
	{
		SamplerSetters.insert(Setter);
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

// 텍스쳐 세팅을 ParentShader로 구분하고, Type에 맞는 쉐이더 세팅 실시
// 텍스쳐는 이미 있는 것을 사용하기 때문에, ChangeData를 실시하지 않는다.
void GameEngineTextureSetter::Setting()
{
	ShaderType Type = ParentShader->GetType();

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

// 샘플러 세팅을 ParentShader로 구분하고, Type에 맞는 쉐이더 세팅 실시
// 샘플러는 이미 있는 것을 사용하기 때문에, ChangeData를 실시하지 않는다.
void GameEngineSamplerSetter::Setting()
{
	ShaderType Type = ParentShader->GetType();

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
	// 쉐이더 상수 버퍼 세팅
	{
		std::multimap<std::string, GameEngineConstantBufferSetter>::iterator StartIter = ConstantBufferSetters.begin();
		std::multimap<std::string, GameEngineConstantBufferSetter>::iterator EndIter = ConstantBufferSetters.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			GameEngineConstantBufferSetter& Setter = StartIter->second;
			Setter.Setting();
		}
	}
	// 쉐이더 텍스쳐 세팅
	{
		std::multimap<std::string, GameEngineTextureSetter>::iterator StartIter = TextureSetters.begin();
		std::multimap<std::string, GameEngineTextureSetter>::iterator EndIter = TextureSetters.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			GameEngineTextureSetter& Setter = StartIter->second;
			Setter.Setting();
		}
	}
	// 쉐이더 샘플러 세팅
	{
		std::multimap<std::string, GameEngineSamplerSetter>::iterator StartIter = SamplerSetters.begin();
		std::multimap<std::string, GameEngineSamplerSetter>::iterator EndIter = SamplerSetters.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			GameEngineSamplerSetter& Setter = StartIter->second;
			Setter.Setting();
		}
	}
}

// 이름이 링크인 이유는, 복사된 랜더러의 ResHelper 내에 초기값이 적용(빨간색에 배경!)됐다고 해도, 이후에 값을 변경하면 변경되기 때문에 링크라고 지었습니다.
void GameEngineShaderResHelper::SetConstantBufferLink(const std::string_view& _Name, const void* _Data, UINT _Size)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator FindIter = ConstantBufferSetters.find(UpperName);

	if (ConstantBufferSetters.end() == FindIter)
	{
		MsgAssert("존재하지 않는 상수버퍼를 세팅하려고 했습니다." + UpperName);
		return;
	}

	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator NameStartIter = ConstantBufferSetters.lower_bound(UpperName); // 같은 이름 중(Key 중) 가장 앞에 있는 것
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator NameEndIter = ConstantBufferSetters.upper_bound(UpperName);   // 같은 이름 중(Key 중) 가장 뒤에 있는 것

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

// 텍스쳐를 이름으로 지정하는 함수
void GameEngineShaderResHelper::SetTexture(const std::string_view& _SettingName, const std::string_view& _ImageName)
{
	std::string UpperName = GameEngineString::ToUpper(_SettingName);

	std::multimap<std::string, GameEngineTextureSetter>::iterator FindIter = TextureSetters.find(UpperName);

	if (TextureSetters.end() == FindIter)
	{
		MsgAssert("쉐이더에서 이런 이름의 텍스처 세팅를 사용하지 않았습니다." + UpperName);
		return;
	}

	std::multimap<std::string, GameEngineTextureSetter>::iterator NameStartIter = TextureSetters.lower_bound(UpperName);
	std::multimap<std::string, GameEngineTextureSetter>::iterator NameEndIter = TextureSetters.upper_bound(UpperName);

	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(_ImageName);

	if (nullptr == FindTex)
	{
		MsgAssert("이런 이름의 텍스처는 로드한 적이 없습니다." + std::string(_ImageName));
		return;
	}

	for (; NameStartIter != NameEndIter; ++NameStartIter)
	{
		GameEngineTextureSetter& Setter = NameStartIter->second;
		Setter.Res = FindTex;
	}

}

// 텍스쳐를 이름없이 지정하는 함수
void GameEngineShaderResHelper::SetTexture(const std::string_view& _SettingName, std::shared_ptr<GameEngineTexture> _Texture)
{
	if (nullptr == _Texture)
	{
		MsgAssert("nullptr인 텍스처를 세팅하려고 했습니다." + std::string(_SettingName));
		return;
	}

	std::string UpperName = GameEngineString::ToUpper(_SettingName);

	std::multimap<std::string, GameEngineTextureSetter>::iterator FindIter = TextureSetters.find(UpperName);

	if (TextureSetters.end() == FindIter)
	{
		MsgAssert("쉐이더에서 이런 이름의 텍스처 세팅를 사용하지 않았습니다." + UpperName);
		return;
	}

	std::multimap<std::string, GameEngineTextureSetter>::iterator NameStartIter = TextureSetters.lower_bound(UpperName);
	std::multimap<std::string, GameEngineTextureSetter>::iterator NameEndIter = TextureSetters.upper_bound(UpperName);

	for (; NameStartIter != NameEndIter; ++NameStartIter)
	{
		GameEngineTextureSetter& Setter = NameStartIter->second;
		Setter.Res = _Texture;
	}
}

GameEngineTextureSetter* GameEngineShaderResHelper::GetTextureSetter(const std::string_view& _View)
{
	std::string UpperName = GameEngineString::ToUpper(_View);

	std::multimap<std::string, GameEngineTextureSetter>::iterator FindIter = TextureSetters.find(UpperName);

	if (FindIter == TextureSetters.end())
	{
		return nullptr;
	}

	return &(FindIter->second);
}

std::vector<GameEngineTextureSetter*> GameEngineShaderResHelper::GetTextureSetters(const std::string_view& _View)
{
	std::string UpperName = GameEngineString::ToUpper(_View);

	std::multimap<std::string, GameEngineTextureSetter>::iterator FindIter = TextureSetters.find(UpperName);

	std::vector<GameEngineTextureSetter*> Result;

	if (FindIter == TextureSetters.end())
	{
		return Result;
	}

	std::multimap<std::string, GameEngineTextureSetter>::iterator NameStartIter = TextureSetters.lower_bound(UpperName);
	std::multimap<std::string, GameEngineTextureSetter>::iterator NameEndIter = TextureSetters.upper_bound(UpperName);

	for (; NameStartIter != NameEndIter; ++NameStartIter)
	{
		Result.push_back(&NameStartIter->second);
	}

	return Result;
}
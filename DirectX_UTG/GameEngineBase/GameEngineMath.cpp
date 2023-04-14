#include "PrecompileHeader.h"
#include "PrecompileHeader.h"
#include "GameEngineMath.h"
#include "GameEngineString.h"

const float GameEngineMath::PIE = 3.141592653589793238462643383279502884197169399375105820974944f;
const float GameEngineMath::PIE2 = PIE * 2.0f;
const float GameEngineMath::DegToRad = GameEngineMath::PIE / 180;
const float GameEngineMath::RadToDeg = 180 / GameEngineMath::PIE;

const float4 float4::Left = { -1.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::Right = { 1.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::Up = { 0.0f, 1.0f, 0.0f, 1.0f };
const float4 float4::Down = { 0.0f, -1.0f, 0.0f, 1.0f };
const float4 float4::Forward = { 0.0f, 0.0f, 1.0f, 1.0f };
const float4 float4::Back = { 0.0f, 0.0f, -1.0f, 1.0f };

const float4 float4::One = { 1.0f, 1.0f, 1.0f, 1.0f };
const float4 float4::Zero = { 0.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::Null = { 0.0f, 0.0f, 0.0f, 0.0f };

const float4 float4::Red = { 1.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
const float4 float4::Green = { 0.0f, 1.0f, 0.0f, 1.0f };
const float4 float4::White = { 1.0f, 1.0f, 1.0f, 1.0f };
const float4 float4::Black = { 0.0f, 0.0f, 0.0f, 1.0f };


// Radian을 통한 X축 회전
void float4::RotaitonXRad(float _Rad)
{
	float4x4 Rot;
	Rot.RotationXRad(_Rad); // 회전 행렬 (X축)
	*this *= Rot;
}

// Radian을 통한 Y축 회전
void float4::RotaitonYRad(float _Rad)
{
	float4x4 Rot;
	Rot.RotationYRad(_Rad); // 회전 행렬 (Y축)
	*this *= Rot;
}

// Radian을 통한 Z축 회전
void float4::RotaitonZRad(float _Rad)
{
	float4x4 Rot;
	Rot.RotationZRad(_Rad); // 회전 행렬 (Z축)
	*this *= Rot;
}

// 오일러 각도를 쿼터니온으로 변환하여 리턴
float4 float4::EulerDegToQuaternion()
{
	float4 Return = DirectVector;
	Return *= GameEngineMath::DegToRad;
	Return = DirectX::XMQuaternionRotationRollPitchYawFromVector(Return.DirectVector); // 전달한 벡터로부터 롤(X축 회전), 피치(Y축 회전), 야(Z축 회전) 정보를 리턴
	return Return;
}

// 쿼터니온을 오일러 각도로 변환하여 리턴(Degree)
float4 float4::QuaternionToEulerDeg()
{
	return QuaternionToEulerRad() * GameEngineMath::RadToDeg;
}

// 쿼터니온을 오일러 각도로 변환하여 리턴(Radian)
float4 float4::QuaternionToEulerRad()
{
	float sqw = w * w;
	float sqx = x * x;
	float sqy = y * y;
	float sqz = z * z;

	// 인터넷에 있던 어떤 식을 가져왔습니다.
	float AngleX = asinf(2.0f * (w * x - y * z));
	float AngleY = atan2f(2.0f * (x * z - w * y), (-sqx - sqy + sqz + sqw));
	float AngleZ = atan2f(2.0f * (x * y - w * z), (-sqx + sqy - sqz + sqw));

	return float4(AngleX, AngleY, AngleZ);
}

// 쿼터니온을 행렬로 변환하여 리턴
float4x4 float4::QuaternionToRotationMatrix()
{
	// 다이렉트 XMMatrixRotationQuaternion == 쿼터니온을 행렬로 변환
	return DirectX::XMMatrixRotationQuaternion(DirectVector);
}

// flaot4와 행렬의 곱 (1x4 * 4x4), DirectX : XMVector4Transform(float4, float4x4)
float4 float4::operator*(const class float4x4& _Other)
{
	float4 ReturnValue = DirectX::XMVector4Transform(*this, _Other);

	return ReturnValue;
}

// flaot4와 행렬의 곱 (1x4 * 4x4) 래퍼런스형, DirectX : XMVector4Transform(float4, float4x4)
float4& float4::operator*=(const class float4x4& _Other)
{
	DirectVector = DirectX::XMVector4Transform(*this, _Other);;
	return *this;
}

// 제로행렬
const float4x4 float4x4::Zero = float4x4(float4::Null, float4::Null, float4::Null, float4::Null);

std::vector<unsigned int> GameEngineMath::GetDigits(int _Value)
{
	std::vector<unsigned int> ResultValue = std::vector<unsigned int>();

	std::string StringValue = GameEngineString::ToString(_Value);

	int StartIndex = 0;

	if (0 != StringValue.size() && StringValue[0] == '-')
	{
		StartIndex = 1;
	}

	ResultValue.reserve(StringValue.size());

	for (size_t i = StartIndex; i < StringValue.size(); i++)
	{
		ResultValue.push_back(StringValue[i] - '0');
	}

	return ResultValue;
}

unsigned int GameEngineMath::GetLenth(int _Value)
{
	std::vector<unsigned int> ResultValue = std::vector<unsigned int>();

	std::string StringValue = GameEngineString::ToString(_Value);

	int StartIndex = 0;

	if (0 != StringValue.size() && StringValue[0] == '-')
	{
		StartIndex = 1;
	}

	return static_cast<unsigned int>(StringValue.size()) - StartIndex;
}
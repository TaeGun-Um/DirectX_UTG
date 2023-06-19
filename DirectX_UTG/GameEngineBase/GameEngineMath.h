#pragma once

#include <math.h>
#include <cmath>
#include <string>
#include <Windows.h>
#include <vector>

// dx함수들
// 다이렉트용 벡터
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

// final 더이상 상속내릴지 못한다.
class GameEngineMath final
{
public:
	static const float PIE;
	static const float PIE2;
	static const float DegToRad;
	static const float RadToDeg;

	static std::vector<unsigned int> GetDigits(int _Value);
	static unsigned int GetLenth(int _Value);

private:
	virtual ~GameEngineMath() = 0;
};

// float4 (x, y, z, w) 데이터
class float4
{
public:
	static const float4 Left;
	static const float4 Right;
	static const float4 Up;
	static const float4 Down;
	static const float4 Forward;
	static const float4 Back;
	static const float4 One;
	static const float4 Zero;
	static const float4 Null;

	static const float4 Red;
	static const float4 Blue;
	static const float4 Green;
	static const float4 White;
	static const float4 Black;

	// Degree를 Radian으로 변환한 뒤 벡터 회전
	static float4 AngleToDirection2DToDeg(float _Deg)
	{
		return AngleToDirection2DToRad(_Deg * GameEngineMath::DegToRad);
	}

	// 벡터 회전
	static float4 AngleToDirection2DToRad(float _Rad)
	{
		return float4(cosf(_Rad), sinf(_Rad), 0.0f, 1.0f);
	}

	// Degree를 Radian으로 변환한 뒤 백터의 내적 계산
	static float GetAngleVectorToVectorDeg(const float4& _Left, const float4& _Right)
	{
		return GetAngleVectorToVectorRad(_Left, _Right) * GameEngineMath::RadToDeg;
	}

	static float GetAngleVectorToVectorDeg360(const float4& _Left, const float4& _Right)
	{
		return GetAngleVectorToVectorRad360(_Left, _Right) * GameEngineMath::RadToDeg;
	}

	// 벡터의 내적
	static float GetAngleVectorToVectorRad(const float4& _Left, const float4& _Right)
	{
		float4 Left = _Left;
		float4 Right = _Right;

		Left.Normalize();
		Right.Normalize();

		float CosSeta = DotProduct3D(Left, Right); // 벡터의 내적 실시

		float Angle = acosf(CosSeta); // 내적 결과 각도

		return Angle;
	}

	static float GetAngleVectorToVectorRad360(const float4& _Left, const float4& _Right)
	{
		float4 Left = _Left;
		float4 Right = _Right;

		Left.Normalize();
		Right.Normalize();

		float CosSeta = DotProduct3D(Left, Right);


		float Angle = 0.f;
		(Left.y * Right.x + Left.x * Right.y > 0.0f) ? Angle = acosf(CosSeta) : Angle = -acosf(CosSeta);


		return Angle;
	}

	// 벡터를 노말라이즈 한 뒤 외적
	static float4 Cross3DReturnNormal(const float4& _Left, const float4& _Right)
	{
		return Cross3DReturn(_Left.NormalizeReturn(), _Right.NormalizeReturn()).NormalizeReturn();
	}

	// 벡터의 외적
	static float4 Cross3DReturn(const float4& _Left, const float4& _Right)
	{
		// 다이렉트의 네임 스페이스는 DirectX:: 이다.
		// DirectX::XMVector3Cross == 다이렉트 벡터의 외적
		float4 ReturnValue = DirectX::XMVector3Cross(_Left, _Right);
		return ReturnValue;
	}

	// 다이렉트 벡터 내적
	static float DotProduct3D(const float4& _Left, const float4& _Right)
	{
		// DirectX::XMVector3Dot == 다이렉트 벡터의 내적
		float4 ReturnValue = DirectX::XMVector3Dot(_Left, _Right);
		return ReturnValue.x;
	}

public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float r;
			float g;
			float b;
			float a;
		};

		float Arr1D[4];

		// 심드 연산을 위한 Direct 전용 float3, float4, DirectVector
		DirectX::XMFLOAT3 DirectFloat3; // x, y, z
		DirectX::XMFLOAT4 DirectFloat4; // x, y, z, w
		DirectX::XMVECTOR DirectVector; // 

		struct
		{
			float PosX;
			float PosY;
			float SizeX;
			float SizeY;
		};
	};

	float4()
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{

	}

	float4(float _x, float _y)
		: x(_x), y(_y), z(0.0f), w(1.0f)
	{

	}

	float4(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z), w(1.0f)
	{

	}

	float4(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{

	}

	float4(DirectX::FXMVECTOR _Vector)
		: DirectVector(_Vector)
	{

	}

	// 쿼터니온을 행렬로 변환하여 리턴(DirectX : XMMatrixRotationQuaternion(쿼터니온))
	class float4x4 QuaternionToRotationMatrix();
	
	// 오일러 각도를 쿼터니온으로 변환하여 리턴(DirectX : XMQuaternionRotationRollPitchYawFromVector(오일러각도))
	float4 EulerDegToQuaternion();

	// 쿼터니온을 오일러 각도로 변환하여 리턴(Degree)
	float4 QuaternionToEulerDeg();

	// 쿼터니온을 오일러 각도로 변환하여 리턴(Radian)
	float4 QuaternionToEulerRad();

	float XYDistance(float4 _Value);
	float XYZDistance(float4 _Value);

	// float4의 x, y, z, w의 절반값(1/2)를 리턴
	float hx() const
	{
		return x * 0.5f;
	}
	float hy() const
	{
		return y * 0.5f;
	}
	float hz() const
	{
		return z * 0.5f;
	}
	float hw() const
	{
		return w * 0.5f;
	}

	// float4의 x, y, z, w를 int로 static_cast 후 리턴
	int ix() const
	{
		return static_cast<int>(x);
	}
	int iy() const
	{
		return static_cast<int>(y);
	}
	int iz() const
	{
		return static_cast<int>(z);
	}
	int iw() const
	{
		return static_cast<int>(w);
	}

	// float4의 x, y, z, w의 절반값(1/2)를 int로 static_cast 후 리턴
	int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}
	int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}
	int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}
	int hiw() const
	{
		return static_cast<int>(w * 0.5f);
	}

	// float4의 x, y, z, w를 unsigned int로 static_cast 후 리턴
	int uix() const
	{
		return static_cast<unsigned int>(x);
	}
	int uiy() const
	{
		return static_cast<unsigned int>(y);
	}
	int uiz() const
	{
		return static_cast<unsigned int>(z);
	}
	int uiw() const
	{
		return static_cast<unsigned int>(w);
	}

	// float4의 x, y, z, w의 절반값(1/2)를 unsigned int로 static_cast 후 리턴
	int uhix() const
	{
		return static_cast<unsigned int>(x * 0.5f);
	}
	int uhiy() const
	{
		return static_cast<unsigned int>(y * 0.5f);
	}
	int uhiz() const
	{
		return static_cast<unsigned int>(z * 0.5f);
	}
	int uhiw() const
	{
		return static_cast<unsigned int>(w * 0.5f);
	}

	float MaxFloat() const
	{
		return (x < y) ? (y < z ? z : y) : (x < z ? z : x);
	}

	UINT ColorToUint() const
	{
		UINT Return;

		char* Ptr = reinterpret_cast<char*>(&Return);

		// 0~1
		Ptr[0] = static_cast<int>(r * 255.0f);
		Ptr[1] = static_cast<int>(g * 255.0f);
		Ptr[2] = static_cast<int>(b * 255.0f);
		Ptr[3] = static_cast<int>(a * 255.0f);

		return Return;
	}

	// Degree을 통한 X축 회전 (Radian으로 변환)
	void RotaitonXDeg(float _Deg)
	{
		RotaitonXRad(_Deg * GameEngineMath::DegToRad);
	}

	// Degree을 통한 Y축 회전 (Radian으로 변환)
	void RotaitonYDeg(float _Deg)
	{
		RotaitonYRad(_Deg * GameEngineMath::DegToRad);
	}

	// Degree을 통한 Z축 회전 (Radian으로 변환)
	void RotaitonZDeg(float _Deg)
	{
		RotaitonZRad(_Deg * GameEngineMath::DegToRad);
	}

	// Radian을 통한 X축 회전 (내부에서 회전 행렬 활용)
	void RotaitonXRad(float _Rad);

	// Radian을 통한 Y축 회전 (내부에서 회전 행렬 활용)
	void RotaitonYRad(float _Rad);

	// Radian을 통한 Z축 회전 (내부에서 회전 행렬 활용)
	void RotaitonZRad(float _Rad);

	// Degree을 통한 X축 회전값 리턴 (내부에서 회전 행렬 활용)
	float4 RotaitonXDegReturn(float _Deg)
	{
		float4 ReturnValue = *this;
		ReturnValue.RotaitonXRad(_Deg * GameEngineMath::DegToRad);
		return ReturnValue;
	}

	// Degree을 통한 Y축 회전값 리턴 (내부에서 회전 행렬 활용)
	float4 RotaitonYDegReturn(float _Deg)
	{
		float4 ReturnValue = *this;
		ReturnValue.RotaitonYRad(_Deg * GameEngineMath::DegToRad);
		return ReturnValue;
	}

	// Degree을 통한 Z축 회전값 리턴 (내부에서 회전 행렬 활용)
	float4 RotaitonZDegReturn(float _Deg)
	{
		float4 ReturnValue = *this;
		ReturnValue.RotaitonZRad(_Deg * GameEngineMath::DegToRad);
		return ReturnValue;
	}

	// Z각도 얻기(Degree)
	float GetAnagleDegZ()
	{
		return GetAnagleRadZ() * GameEngineMath::RadToDeg;
	}

	// Z각도 얻기, 값 리턴(Radian)
	float GetAnagleRadZ()
	{
		float4 AngleCheck = (*this);
		// this를 노말라이즈
		AngleCheck.Normalize();
		// 노말라이즈한 this의 x에 대해 acosf()(cosf() 역함수) 값
		float Result = acosf(AngleCheck.x);

		// 노말라이즈한 this의 y 값이 0보다 크면 0으로 초기화(2파이)
		if (AngleCheck.y < 0)
		{
			Result = GameEngineMath::PIE2 - Result;
		}

		return Result;
	}

	// 4바이트 자료형 x, y 구조체 값 리턴
	POINT ToWindowPOINT()
	{
		return POINT(ix(), iy());
	}

	// float4의 전체 half값 리턴 (w는 1.0f로 고정)
	float4 half() const
	{
		return { x * 0.5f, y * 0.5f, z * 0.5f, w};
	}

	// float4의 전체 0.0f 으로 리턴 (w는 1.0f로 고정)
	bool IsZero() const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	// 빗변의 제곱근 값 구하기
	float Size() const
	{
		// sqrtf() : 제곱근 함수 (제곱의 근 : 2^2 = 4 일때, 2제곱2의 제곱근은 2)
		// 2차원 예시 : x, y의 제곱(밑변, 높이의 제곱)을 알 경우 빗변의 제곱을 알 수 있음
		// 밑변^2 + 높이^2 = 빗변^2
		return sqrtf(x * x + y * y + z * z);
	}

	// 벡터 노말라이즈, 기저단위벡터(길이 1)로 변경, DirectX : XMVector3Normalize(벡터)
	void Normalize()
	{
		DirectVector = DirectX::XMVector3Normalize(*this);
	}

	// 벡터 노말라이즈, 기저단위벡터(길이 1)로 변경, DirectX : XMVector3Normalize(벡터)의 값 리턴
	float4 NormalizeReturn() const
	{
		float4 Result = *this;
		Result.Normalize();
		return Result;
	}

	// 벡터 러프값 리턴
	static float4 Lerp(const float4& Start, const float4& End, float Ratio)
	{
		return DirectX::XMVectorLerp(Start, End, Ratio);
	}

	// 벡터 러프클럼프(Ratio의 범위 0.0f ~ 1.0f 로 고정) 후 러프 값 리턴
	static float4 LerpClamp(const float4& Start, const float4& End, float Ratio)
	{
		if (0 >= Ratio)
		{
			Ratio = 0.0f;
		}

		if (1.0f <= Ratio)
		{
			Ratio = 1.0f;
		}

		return Lerp(Start, End, Ratio);
	}

	// 심드 연산을 위한 Direct 전용 벡터
	operator DirectX::FXMVECTOR() const
	{
		return DirectVector;
	}

	// float4 x, y, z 비교 연산 bool값 리턴
	bool operator ==(const float4& _Value) const
	{
		return _Value.x == x && _Value.y == y && _Value.z == z;
	}

	// float4 x, y, z 합 리턴, DirectX : XMVectorAdd(주체, 대상)
	float4 operator +(const float4& _Value) const
	{
		float PrevW = w;
		float4 Return = DirectX::XMVectorAdd(*this, _Value);
		Return.w = PrevW;
		return Return;
	}

	// float4 x, y, z 차 리턴, DirectX : XMVectorAdd(주체, 대상)
	float4 operator -(const float4& _Value) const
	{
		float PrevW = w;
		float4 Return = DirectX::XMVectorAdd(*this, -_Value);
		Return.w = PrevW;
		return Return;
	}

	// float과 float4 곱 리턴, DirectX : XMVectorMultiply(float, float4)
	float4 operator *(const float _Value) const
	{
		return DirectX::XMVectorMultiply(*this, float4{ _Value , _Value , _Value , 1.0f });
	}

	// float4과 float4 곱 리턴, DirectX : XMVectorMultiply(float4, float4)
	float4 operator *(const float4& _Value) const
	{
		float PrevW = w;
		float4 Return = DirectX::XMVectorMultiply(*this, _Value);
		Return.w = PrevW;
		return Return;
	}

	// float과 float4 나눗셈 리턴, DirectX : XMVectorDivide(float, float4)
	float4 operator /(const float _Value) const
	{
		float PrevW = w;
		float4 Return = DirectX::XMVectorDivide(*this, { _Value , _Value , _Value , _Value });
		Return.w = PrevW;
		return Return;
	}

	// float4과 float4 나눗셈 리턴, DirectX : XMVectorDivide(float4, float4)
	float4 operator /(const float4& _Value) const
	{
		float PrevW = w;
		float4 Return = DirectX::XMVectorDivide(*this, _Value);
		Return.w = PrevW;
		return Return;
	}

	// float4의 w 제외 x, y, z에 음수 적용
	float4 operator -() const
	{
		return { -x, -y, -z, w };
	}

	// float4 += 연산 (자기 자신 합)
	float4& operator +=(const float4& _Other)
	{
		*this = *this + _Other;
		return *this;
	}

	// float4 -= 연산 (자기 자신 합)
	float4& operator -=(const float4& _Other)
	{
		*this = *this - _Other;
		return *this;
	}

	// float4, float *= 연산 (자기 자신 곱)
	float4& operator *=(const float _Value)
	{
		*this = *this * _Value;
		return *this;
	}

	// float4 *= 연산 (자기 자신 곱)
	float4& operator *=(const float4& _Other)
	{
		*this = *this * _Other;
		return *this;
	}

	// float4, float /= 연산 (자기 자신 나누기)
	float4& operator /=(const float _Value)
	{
		*this = *this / _Value;
		return *this;
	}

	// float4 (자기 자신 나누기)
	float4& operator /=(const float4& _Other)
	{
		*this = *this / _Other;
		return *this;
	}

	// float4와 행렬의 곱(다이렉트)
	float4 operator*(const class float4x4& _Other);

	// float4와 자기자신, 행렬의 곱
	float4& operator*=(const class float4x4& _Other);

	// float4의 x, y, z, w 값 string으로 출력
	std::string ToString()
	{
		char ArrReturn[256];

		sprintf_s(ArrReturn, "x: %f, y: %f, z: %f, w: %f", x, y, z, w);

		return std::string(ArrReturn);
	}

};

// 충돌체 데이터
class CollisionDataAPI
{
public:
	float4 Position;  // 충돌체 Pos
	float4 Scale;     // x만 원의 반지름으로 보겠습니다.

	float Left() const
	{
		return Position.x - Scale.hx();
	}
	float Right() const
	{
		return Position.x + Scale.hx();
	}
	float Top() const
	{
		return Position.y - Scale.hy();
	}
	float Bot() const
	{
		return Position.y + Scale.hy();
	}

	float4 LeftTop() const
	{
		return float4{ Left(), Top() };
	}
	float4 RightTop() const
	{
		return float4{ Right(), Top() };
	}
	float4 LeftBot() const
	{
		return float4{ Left(), Bot() };
	}
	float4 RightBot() const
	{
		return float4{ Right(), Bot() };
	}
};

typedef float4 Quaternion; // Quaternion == float4

// 행렬 데이터
class float4x4
{
public:
	// 영행렬(제로행렬)
	static const float4x4 Zero;
	
	// 4x4 행렬로 설정
	static const int YCount = 4;
	static const int XCount = 4;

public:
	union
	{
		float Arr1D[16];                // 일렬로 나열
		float Arr2D[4][4];              // 4x4로 나열
		float4 ArrVector[4];            // 한 행만 나열
		DirectX::XMMATRIX DirectMatrix; // DirectX 행렬 : XMMATRIX

		struct
		{
			float _00;
			float _01;
			float _02;
			float _03;
			float _10;
			float _11;
			float _12;
			float _13;
			float _20;
			float _21;
			float _22;
			float _23;
			float _30;
			float _31;
			float _32;
			float _33;
		};
	};

	// 다이렉트 행렬 리턴
	operator DirectX::FXMMATRIX() const
	{
		return DirectMatrix;
	}

	float4x4()
	{
		Identity();
	}

	float4x4(DirectX::FXMMATRIX _DirectMatrix)
		: DirectMatrix(_DirectMatrix)
	{

	}

	float4x4(float4 _x, float4 _y, float4 _z, float4 _w)
	{
		ArrVector[0] = _x;
		ArrVector[1] = _y;
		ArrVector[2] = _z;
		ArrVector[3] = _w;
	}

	// 항등행렬, DirectX : XMMatrixIdentity()
	void Identity()
	{
		DirectMatrix = DirectX::XMMatrixIdentity();
	}

	// 행렬 전치, DirectX : XMMatrixTranspose(전치할 행렬)
	void Transpose()
	{
		DirectMatrix = DirectX::XMMatrixTranspose(*this);
	}

	// 역행렬, DirectX : XMMatrixTranspose(nullptr, 역행렬 구할 행렬)
	void Inverse()
	{
		DirectMatrix = DirectX::XMMatrixInverse(nullptr, *this);
	}

	// 역행렬된 행렬을 리턴
	float4x4 InverseReturn() const
	{
		float4x4 Return = *this;
		Return.Inverse();
		return Return;
	}

	// 뷰 행렬을 위한 Z(앞; _EyeDir), Y(위; _EyeUp)
	// 외적을 통해 회전 방향 구함, 내적을 통해 얼만큼 돌아야하는지 구함, DirectX : XMMatrixLookToLH()
	void LookToLH(const float4& _EyePos, const float4& _EyeDir, const float4& _EyeUp)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixLookToLH(_EyePos, _EyeDir, _EyeUp);
	}

	// 직교투영, DirectX : XMMatrixOrthographicLH
	void OrthographicLH(float _ScreenWidth, float _ScreenHeight, float _NearZ = 0.1f, float _FarZ = 10000.0f)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixOrthographicLH(_ScreenWidth, _ScreenHeight, _NearZ, _FarZ);
	}

	// 원근투영, 프로젝션 행렬, DirectX : XMMatrixPerspectiveFovLH()
	void PerspectiveFovLH(float _FovAngle, float _AspectRatio, float _NearZ = 0.1f, float _FarZ = 10000.0f)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixPerspectiveFovLH(_FovAngle * GameEngineMath::DegToRad, _AspectRatio, _NearZ, _FarZ);
	}

	// 뷰포트 행렬, 뷰포트 행렬은 다이렉트 함수가 없다.
	// -1 ~ 1 사이에 존재하게 된 액터들을 화면 크기로 확장
	void ViewPort(float _Width, float _Height, float _Left, float _Right, float _ZMin = 0.0f, float _ZMax = 1.0f)
	{
		Identity();

		Arr2D[0][0] = _Width * 0.5f;                             // 화면 너비 절반
		Arr2D[1][1] = -_Height * 0.5f;                           // 화면 높이 절반
		Arr2D[2][2] = _ZMax != 0.0f ? 1.0f : _ZMin / _ZMax;      // 프로젝션 시 z 범위 (0 ~ 1)

		Arr2D[3][0] = Arr2D[0][0] + _Left;                       // 화면 너비 절반 + 화면 왼쪽 끝 
		Arr2D[3][1] = _Height * 0.5f + _Right;                   // 화면 높이 저란 + 화면 오른쪽 끝
		Arr2D[3][2] = _ZMax != 0.0f ? 0.0f : _ZMin / _ZMax;      // 프로젝션 시 z 범위 (0 ~ 1)
		Arr2D[3][3] = 1.0f;                                      // w = 1
	}

	// SRT(변환 행렬) 분리
	// 변환행렬은 위치벡터에서 크기, 회전, 위치변환을 위해 곱해지는 행렬을 말한다.
	void Decompose(float4& _Scale, float4& _RotQuaternion, float4& _Pos) const
	{
		DirectX::XMMatrixDecompose(&_Scale.DirectVector, &_RotQuaternion.DirectVector, &_Pos.DirectVector, DirectMatrix);
	}

	// SRT 중 크기 분리
	void DecomposeScale(float4& _Scale)
	{
		float4 Temp0;
		float4 Temp1;

		DirectX::XMMatrixDecompose(&_Scale.DirectVector, &Temp0.DirectVector, &Temp1.DirectVector, DirectMatrix);
	}

	// SRT 중 회전 분리
	void DecomposeRotQuaternion(float4& _RotQuaternion)
	{
		float4 Temp0;
		float4 Temp1;

		DirectX::XMMatrixDecompose(&Temp0.DirectVector, &_RotQuaternion.DirectVector, &Temp1.DirectVector, DirectMatrix);
	}

	// SRT 중 이동 분리
	void DecomposePos(float4& _Pos)
	{
		float4 Temp0;
		float4 Temp1;

		DirectX::XMMatrixDecompose(&Temp0.DirectVector, &Temp1.DirectVector, &_Pos.DirectVector, DirectMatrix);
	}

	// 크기 행렬, DirectX : XMMatrixScalingFromVector()
	void Scale(const float4& _Value)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixScalingFromVector(_Value);
	}

	// 이동 행렬, DirectX : XMMatrixTranslationFromVector()
	void Pos(const float4& _Value)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixTranslationFromVector(_Value);
	}

	// 회전 행렬, DirectX : XMMatrixRotationRollPitchYaw(x, y, z)
	void RotationDeg(const float4& _Deg)
	{
		float4 Rot = _Deg * GameEngineMath::DegToRad;

		DirectMatrix = DirectX::XMMatrixRotationRollPitchYaw(Rot.x, Rot.y, Rot.z);
	}

	// X, Y, Z 회전 행렬, X->Y->Z 순으로 곱함
	void RotationDegToXYZ(const float4& _Deg)
	{
		float4 Rot = _Deg * GameEngineMath::DegToRad;

		float4x4 RotX = DirectX::XMMatrixRotationX(Rot.x);
		float4x4 RotY = DirectX::XMMatrixRotationY(Rot.y);
		float4x4 RotZ = DirectX::XMMatrixRotationZ(Rot.z);

		*this = RotX * RotY * RotZ;
	}

	// X축 회전 행렬, DirectX : XMMatrixRotationX(라디안)
	void RotationXDeg(const float _Deg)
	{
		RotationXRad(_Deg * GameEngineMath::DegToRad);
	}
	void RotationXRad(const float _Rad)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixRotationX(_Rad);
	}

	// Y축 회전 행렬, DirectX : XMMatrixRotationY(라디안)
	void RotationYDeg(const float _Deg)
	{
		RotationYRad(_Deg * GameEngineMath::DegToRad);
	}
	void RotationYRad(const float _Rad)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixRotationY(_Rad);
	}

	// Z축 회전 행렬, DirectX : XMMatrixRotationZ(라디안)
	void RotationZDeg(const float _Deg)
	{
		RotationZRad(_Deg * GameEngineMath::DegToRad);
	}
	void RotationZRad(const float _Rad)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixRotationZ(_Rad);
	}

	// 노말 : w가 0인 곱하기
	float4 TransformNormal(const float4& _Value)
	{
		return DirectX::XMVector3TransformNormal(_Value, *this);
	}
	// 쿠드 : w가 1인 곱하기
	float4 TransformCoord(const float4& _Value)
	{
		return DirectX::XMVector3TransformCoord(_Value, *this);
	}

	// 행렬과 행렬 곱, DirectX : XMMatrixMultiply(주체, 대상)
	float4x4 operator*(const float4x4& _Other)
	{
		float4x4 Return = DirectX::XMMatrixMultiply(*this, _Other);

		return Return;
	}

	// 자신행렬과 행렬 곱, DirectX : XMMatrixMultiply(주체, 대상)
	float4x4& operator*=(const float4x4& _Other)
	{
		DirectMatrix = DirectX::XMMatrixMultiply(*this, _Other);

		return *this;
	}
};


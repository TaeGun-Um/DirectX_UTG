#pragma once

#include <math.h>
#include <cmath>
#include <string>
#include <Windows.h>
#include <vector>

// dx�Լ���
// ���̷�Ʈ�� ����
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

// final ���̻� ��ӳ����� ���Ѵ�.
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

// float4 (x, y, z, w) ������
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

	// Degree�� Radian���� ��ȯ�� �� ���� ȸ��
	static float4 AngleToDirection2DToDeg(float _Deg)
	{
		return AngleToDirection2DToRad(_Deg * GameEngineMath::DegToRad);
	}

	// ���� ȸ��
	static float4 AngleToDirection2DToRad(float _Rad)
	{
		return float4(cosf(_Rad), sinf(_Rad), 0.0f, 1.0f);
	}

	// Degree�� Radian���� ��ȯ�� �� ������ ���� ���
	static float GetAngleVectorToVectorDeg(const float4& _Left, const float4& _Right)
	{
		return GetAngleVectorToVectorRad(_Left, _Right) * GameEngineMath::RadToDeg;
	}

	static float GetAngleVectorToVectorDeg360(const float4& _Left, const float4& _Right)
	{
		return GetAngleVectorToVectorRad360(_Left, _Right) * GameEngineMath::RadToDeg;
	}

	// ������ ����
	static float GetAngleVectorToVectorRad(const float4& _Left, const float4& _Right)
	{
		float4 Left = _Left;
		float4 Right = _Right;

		Left.Normalize();
		Right.Normalize();

		float CosSeta = DotProduct3D(Left, Right); // ������ ���� �ǽ�

		float Angle = acosf(CosSeta); // ���� ��� ����

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

	// ���͸� �븻������ �� �� ����
	static float4 Cross3DReturnNormal(const float4& _Left, const float4& _Right)
	{
		return Cross3DReturn(_Left.NormalizeReturn(), _Right.NormalizeReturn()).NormalizeReturn();
	}

	// ������ ����
	static float4 Cross3DReturn(const float4& _Left, const float4& _Right)
	{
		// ���̷�Ʈ�� ���� �����̽��� DirectX:: �̴�.
		// DirectX::XMVector3Cross == ���̷�Ʈ ������ ����
		float4 ReturnValue = DirectX::XMVector3Cross(_Left, _Right);
		return ReturnValue;
	}

	// ���̷�Ʈ ���� ����
	static float DotProduct3D(const float4& _Left, const float4& _Right)
	{
		// DirectX::XMVector3Dot == ���̷�Ʈ ������ ����
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

		// �ɵ� ������ ���� Direct ���� float3, float4, DirectVector
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

	// ���ʹϿ��� ��ķ� ��ȯ�Ͽ� ����(DirectX : XMMatrixRotationQuaternion(���ʹϿ�))
	class float4x4 QuaternionToRotationMatrix();
	
	// ���Ϸ� ������ ���ʹϿ����� ��ȯ�Ͽ� ����(DirectX : XMQuaternionRotationRollPitchYawFromVector(���Ϸ�����))
	float4 EulerDegToQuaternion();

	// ���ʹϿ��� ���Ϸ� ������ ��ȯ�Ͽ� ����(Degree)
	float4 QuaternionToEulerDeg();

	// ���ʹϿ��� ���Ϸ� ������ ��ȯ�Ͽ� ����(Radian)
	float4 QuaternionToEulerRad();

	float XYDistance(float4 _Value);
	float XYZDistance(float4 _Value);

	// float4�� x, y, z, w�� ���ݰ�(1/2)�� ����
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

	// float4�� x, y, z, w�� int�� static_cast �� ����
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

	// float4�� x, y, z, w�� ���ݰ�(1/2)�� int�� static_cast �� ����
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

	// float4�� x, y, z, w�� unsigned int�� static_cast �� ����
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

	// float4�� x, y, z, w�� ���ݰ�(1/2)�� unsigned int�� static_cast �� ����
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

	// Degree�� ���� X�� ȸ�� (Radian���� ��ȯ)
	void RotaitonXDeg(float _Deg)
	{
		RotaitonXRad(_Deg * GameEngineMath::DegToRad);
	}

	// Degree�� ���� Y�� ȸ�� (Radian���� ��ȯ)
	void RotaitonYDeg(float _Deg)
	{
		RotaitonYRad(_Deg * GameEngineMath::DegToRad);
	}

	// Degree�� ���� Z�� ȸ�� (Radian���� ��ȯ)
	void RotaitonZDeg(float _Deg)
	{
		RotaitonZRad(_Deg * GameEngineMath::DegToRad);
	}

	// Radian�� ���� X�� ȸ�� (���ο��� ȸ�� ��� Ȱ��)
	void RotaitonXRad(float _Rad);

	// Radian�� ���� Y�� ȸ�� (���ο��� ȸ�� ��� Ȱ��)
	void RotaitonYRad(float _Rad);

	// Radian�� ���� Z�� ȸ�� (���ο��� ȸ�� ��� Ȱ��)
	void RotaitonZRad(float _Rad);

	// Degree�� ���� X�� ȸ���� ���� (���ο��� ȸ�� ��� Ȱ��)
	float4 RotaitonXDegReturn(float _Deg)
	{
		float4 ReturnValue = *this;
		ReturnValue.RotaitonXRad(_Deg * GameEngineMath::DegToRad);
		return ReturnValue;
	}

	// Degree�� ���� Y�� ȸ���� ���� (���ο��� ȸ�� ��� Ȱ��)
	float4 RotaitonYDegReturn(float _Deg)
	{
		float4 ReturnValue = *this;
		ReturnValue.RotaitonYRad(_Deg * GameEngineMath::DegToRad);
		return ReturnValue;
	}

	// Degree�� ���� Z�� ȸ���� ���� (���ο��� ȸ�� ��� Ȱ��)
	float4 RotaitonZDegReturn(float _Deg)
	{
		float4 ReturnValue = *this;
		ReturnValue.RotaitonZRad(_Deg * GameEngineMath::DegToRad);
		return ReturnValue;
	}

	// Z���� ���(Degree)
	float GetAnagleDegZ()
	{
		return GetAnagleRadZ() * GameEngineMath::RadToDeg;
	}

	// Z���� ���, �� ����(Radian)
	float GetAnagleRadZ()
	{
		float4 AngleCheck = (*this);
		// this�� �븻������
		AngleCheck.Normalize();
		// �븻�������� this�� x�� ���� acosf()(cosf() ���Լ�) ��
		float Result = acosf(AngleCheck.x);

		// �븻�������� this�� y ���� 0���� ũ�� 0���� �ʱ�ȭ(2����)
		if (AngleCheck.y < 0)
		{
			Result = GameEngineMath::PIE2 - Result;
		}

		return Result;
	}

	// 4����Ʈ �ڷ��� x, y ����ü �� ����
	POINT ToWindowPOINT()
	{
		return POINT(ix(), iy());
	}

	// float4�� ��ü half�� ���� (w�� 1.0f�� ����)
	float4 half() const
	{
		return { x * 0.5f, y * 0.5f, z * 0.5f, w};
	}

	// float4�� ��ü 0.0f ���� ���� (w�� 1.0f�� ����)
	bool IsZero() const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	// ������ ������ �� ���ϱ�
	float Size() const
	{
		// sqrtf() : ������ �Լ� (������ �� : 2^2 = 4 �϶�, 2����2�� �������� 2)
		// 2���� ���� : x, y�� ����(�غ�, ������ ����)�� �� ��� ������ ������ �� �� ����
		// �غ�^2 + ����^2 = ����^2
		return sqrtf(x * x + y * y + z * z);
	}

	// ���� �븻������, ������������(���� 1)�� ����, DirectX : XMVector3Normalize(����)
	void Normalize()
	{
		DirectVector = DirectX::XMVector3Normalize(*this);
	}

	// ���� �븻������, ������������(���� 1)�� ����, DirectX : XMVector3Normalize(����)�� �� ����
	float4 NormalizeReturn() const
	{
		float4 Result = *this;
		Result.Normalize();
		return Result;
	}

	// ���� ������ ����
	static float4 Lerp(const float4& Start, const float4& End, float Ratio)
	{
		return DirectX::XMVectorLerp(Start, End, Ratio);
	}

	// ���� ����Ŭ����(Ratio�� ���� 0.0f ~ 1.0f �� ����) �� ���� �� ����
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

	// �ɵ� ������ ���� Direct ���� ����
	operator DirectX::FXMVECTOR() const
	{
		return DirectVector;
	}

	// float4 x, y, z �� ���� bool�� ����
	bool operator ==(const float4& _Value) const
	{
		return _Value.x == x && _Value.y == y && _Value.z == z;
	}

	// float4 x, y, z �� ����, DirectX : XMVectorAdd(��ü, ���)
	float4 operator +(const float4& _Value) const
	{
		float PrevW = w;
		float4 Return = DirectX::XMVectorAdd(*this, _Value);
		Return.w = PrevW;
		return Return;
	}

	// float4 x, y, z �� ����, DirectX : XMVectorAdd(��ü, ���)
	float4 operator -(const float4& _Value) const
	{
		float PrevW = w;
		float4 Return = DirectX::XMVectorAdd(*this, -_Value);
		Return.w = PrevW;
		return Return;
	}

	// float�� float4 �� ����, DirectX : XMVectorMultiply(float, float4)
	float4 operator *(const float _Value) const
	{
		return DirectX::XMVectorMultiply(*this, float4{ _Value , _Value , _Value , 1.0f });
	}

	// float4�� float4 �� ����, DirectX : XMVectorMultiply(float4, float4)
	float4 operator *(const float4& _Value) const
	{
		float PrevW = w;
		float4 Return = DirectX::XMVectorMultiply(*this, _Value);
		Return.w = PrevW;
		return Return;
	}

	// float�� float4 ������ ����, DirectX : XMVectorDivide(float, float4)
	float4 operator /(const float _Value) const
	{
		float PrevW = w;
		float4 Return = DirectX::XMVectorDivide(*this, { _Value , _Value , _Value , _Value });
		Return.w = PrevW;
		return Return;
	}

	// float4�� float4 ������ ����, DirectX : XMVectorDivide(float4, float4)
	float4 operator /(const float4& _Value) const
	{
		float PrevW = w;
		float4 Return = DirectX::XMVectorDivide(*this, _Value);
		Return.w = PrevW;
		return Return;
	}

	// float4�� w ���� x, y, z�� ���� ����
	float4 operator -() const
	{
		return { -x, -y, -z, w };
	}

	// float4 += ���� (�ڱ� �ڽ� ��)
	float4& operator +=(const float4& _Other)
	{
		*this = *this + _Other;
		return *this;
	}

	// float4 -= ���� (�ڱ� �ڽ� ��)
	float4& operator -=(const float4& _Other)
	{
		*this = *this - _Other;
		return *this;
	}

	// float4, float *= ���� (�ڱ� �ڽ� ��)
	float4& operator *=(const float _Value)
	{
		*this = *this * _Value;
		return *this;
	}

	// float4 *= ���� (�ڱ� �ڽ� ��)
	float4& operator *=(const float4& _Other)
	{
		*this = *this * _Other;
		return *this;
	}

	// float4, float /= ���� (�ڱ� �ڽ� ������)
	float4& operator /=(const float _Value)
	{
		*this = *this / _Value;
		return *this;
	}

	// float4 (�ڱ� �ڽ� ������)
	float4& operator /=(const float4& _Other)
	{
		*this = *this / _Other;
		return *this;
	}

	// float4�� ����� ��(���̷�Ʈ)
	float4 operator*(const class float4x4& _Other);

	// float4�� �ڱ��ڽ�, ����� ��
	float4& operator*=(const class float4x4& _Other);

	// float4�� x, y, z, w �� string���� ���
	std::string ToString()
	{
		char ArrReturn[256];

		sprintf_s(ArrReturn, "x: %f, y: %f, z: %f, w: %f", x, y, z, w);

		return std::string(ArrReturn);
	}

};

// �浹ü ������
class CollisionDataAPI
{
public:
	float4 Position;  // �浹ü Pos
	float4 Scale;     // x�� ���� ���������� ���ڽ��ϴ�.

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

// ��� ������
class float4x4
{
public:
	// �����(�������)
	static const float4x4 Zero;
	
	// 4x4 ��ķ� ����
	static const int YCount = 4;
	static const int XCount = 4;

public:
	union
	{
		float Arr1D[16];                // �Ϸķ� ����
		float Arr2D[4][4];              // 4x4�� ����
		float4 ArrVector[4];            // �� �ุ ����
		DirectX::XMMATRIX DirectMatrix; // DirectX ��� : XMMATRIX

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

	// ���̷�Ʈ ��� ����
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

	// �׵����, DirectX : XMMatrixIdentity()
	void Identity()
	{
		DirectMatrix = DirectX::XMMatrixIdentity();
	}

	// ��� ��ġ, DirectX : XMMatrixTranspose(��ġ�� ���)
	void Transpose()
	{
		DirectMatrix = DirectX::XMMatrixTranspose(*this);
	}

	// �����, DirectX : XMMatrixTranspose(nullptr, ����� ���� ���)
	void Inverse()
	{
		DirectMatrix = DirectX::XMMatrixInverse(nullptr, *this);
	}

	// ����ĵ� ����� ����
	float4x4 InverseReturn() const
	{
		float4x4 Return = *this;
		Return.Inverse();
		return Return;
	}

	// �� ����� ���� Z(��; _EyeDir), Y(��; _EyeUp)
	// ������ ���� ȸ�� ���� ����, ������ ���� ��ŭ ���ƾ��ϴ��� ����, DirectX : XMMatrixLookToLH()
	void LookToLH(const float4& _EyePos, const float4& _EyeDir, const float4& _EyeUp)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixLookToLH(_EyePos, _EyeDir, _EyeUp);
	}

	// ��������, DirectX : XMMatrixOrthographicLH
	void OrthographicLH(float _ScreenWidth, float _ScreenHeight, float _NearZ = 0.1f, float _FarZ = 10000.0f)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixOrthographicLH(_ScreenWidth, _ScreenHeight, _NearZ, _FarZ);
	}

	// ��������, �������� ���, DirectX : XMMatrixPerspectiveFovLH()
	void PerspectiveFovLH(float _FovAngle, float _AspectRatio, float _NearZ = 0.1f, float _FarZ = 10000.0f)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixPerspectiveFovLH(_FovAngle * GameEngineMath::DegToRad, _AspectRatio, _NearZ, _FarZ);
	}

	// ����Ʈ ���, ����Ʈ ����� ���̷�Ʈ �Լ��� ����.
	// -1 ~ 1 ���̿� �����ϰ� �� ���͵��� ȭ�� ũ��� Ȯ��
	void ViewPort(float _Width, float _Height, float _Left, float _Right, float _ZMin = 0.0f, float _ZMax = 1.0f)
	{
		Identity();

		Arr2D[0][0] = _Width * 0.5f;                             // ȭ�� �ʺ� ����
		Arr2D[1][1] = -_Height * 0.5f;                           // ȭ�� ���� ����
		Arr2D[2][2] = _ZMax != 0.0f ? 1.0f : _ZMin / _ZMax;      // �������� �� z ���� (0 ~ 1)

		Arr2D[3][0] = Arr2D[0][0] + _Left;                       // ȭ�� �ʺ� ���� + ȭ�� ���� �� 
		Arr2D[3][1] = _Height * 0.5f + _Right;                   // ȭ�� ���� ���� + ȭ�� ������ ��
		Arr2D[3][2] = _ZMax != 0.0f ? 0.0f : _ZMin / _ZMax;      // �������� �� z ���� (0 ~ 1)
		Arr2D[3][3] = 1.0f;                                      // w = 1
	}

	// SRT(��ȯ ���) �и�
	// ��ȯ����� ��ġ���Ϳ��� ũ��, ȸ��, ��ġ��ȯ�� ���� �������� ����� ���Ѵ�.
	void Decompose(float4& _Scale, float4& _RotQuaternion, float4& _Pos) const
	{
		DirectX::XMMatrixDecompose(&_Scale.DirectVector, &_RotQuaternion.DirectVector, &_Pos.DirectVector, DirectMatrix);
	}

	// SRT �� ũ�� �и�
	void DecomposeScale(float4& _Scale)
	{
		float4 Temp0;
		float4 Temp1;

		DirectX::XMMatrixDecompose(&_Scale.DirectVector, &Temp0.DirectVector, &Temp1.DirectVector, DirectMatrix);
	}

	// SRT �� ȸ�� �и�
	void DecomposeRotQuaternion(float4& _RotQuaternion)
	{
		float4 Temp0;
		float4 Temp1;

		DirectX::XMMatrixDecompose(&Temp0.DirectVector, &_RotQuaternion.DirectVector, &Temp1.DirectVector, DirectMatrix);
	}

	// SRT �� �̵� �и�
	void DecomposePos(float4& _Pos)
	{
		float4 Temp0;
		float4 Temp1;

		DirectX::XMMatrixDecompose(&Temp0.DirectVector, &Temp1.DirectVector, &_Pos.DirectVector, DirectMatrix);
	}

	// ũ�� ���, DirectX : XMMatrixScalingFromVector()
	void Scale(const float4& _Value)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixScalingFromVector(_Value);
	}

	// �̵� ���, DirectX : XMMatrixTranslationFromVector()
	void Pos(const float4& _Value)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixTranslationFromVector(_Value);
	}

	// ȸ�� ���, DirectX : XMMatrixRotationRollPitchYaw(x, y, z)
	void RotationDeg(const float4& _Deg)
	{
		float4 Rot = _Deg * GameEngineMath::DegToRad;

		DirectMatrix = DirectX::XMMatrixRotationRollPitchYaw(Rot.x, Rot.y, Rot.z);
	}

	// X, Y, Z ȸ�� ���, X->Y->Z ������ ����
	void RotationDegToXYZ(const float4& _Deg)
	{
		float4 Rot = _Deg * GameEngineMath::DegToRad;

		float4x4 RotX = DirectX::XMMatrixRotationX(Rot.x);
		float4x4 RotY = DirectX::XMMatrixRotationY(Rot.y);
		float4x4 RotZ = DirectX::XMMatrixRotationZ(Rot.z);

		*this = RotX * RotY * RotZ;
	}

	// X�� ȸ�� ���, DirectX : XMMatrixRotationX(����)
	void RotationXDeg(const float _Deg)
	{
		RotationXRad(_Deg * GameEngineMath::DegToRad);
	}
	void RotationXRad(const float _Rad)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixRotationX(_Rad);
	}

	// Y�� ȸ�� ���, DirectX : XMMatrixRotationY(����)
	void RotationYDeg(const float _Deg)
	{
		RotationYRad(_Deg * GameEngineMath::DegToRad);
	}
	void RotationYRad(const float _Rad)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixRotationY(_Rad);
	}

	// Z�� ȸ�� ���, DirectX : XMMatrixRotationZ(����)
	void RotationZDeg(const float _Deg)
	{
		RotationZRad(_Deg * GameEngineMath::DegToRad);
	}
	void RotationZRad(const float _Rad)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixRotationZ(_Rad);
	}

	// �븻 : w�� 0�� ���ϱ�
	float4 TransformNormal(const float4& _Value)
	{
		return DirectX::XMVector3TransformNormal(_Value, *this);
	}
	// ��� : w�� 1�� ���ϱ�
	float4 TransformCoord(const float4& _Value)
	{
		return DirectX::XMVector3TransformCoord(_Value, *this);
	}

	// ��İ� ��� ��, DirectX : XMMatrixMultiply(��ü, ���)
	float4x4 operator*(const float4x4& _Other)
	{
		float4x4 Return = DirectX::XMMatrixMultiply(*this, _Other);

		return Return;
	}

	// �ڽ���İ� ��� ��, DirectX : XMMatrixMultiply(��ü, ���)
	float4x4& operator*=(const float4x4& _Other)
	{
		DirectMatrix = DirectX::XMMatrixMultiply(*this, _Other);

		return *this;
	}
};


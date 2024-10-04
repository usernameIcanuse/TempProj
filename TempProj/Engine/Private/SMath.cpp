#include "SMath.h"
#include <random>
#include "GameInstance.h"
#include "MeshData.h"

XMMATRIX Engine::SMath::Get_RotationMatrix(FXMMATRIX Mat)
{
	XMMATRIX ResultMat(XMMatrixIdentity());
	for (int i(0); i < 3; i++)
		ResultMat.r[i] = XMVector3Normalize(Mat.r[i]);

	return ResultMat;
}

XMMATRIX ENGINE_DLL Engine::SMath::Get_ScaleMatrix(FXMMATRIX Mat)
{
	XMMATRIX ResultMat(XMMatrixIdentity());
	for (int i(0); i < 3; i++)
		ResultMat.r[i].m128_f32[i] = XMVectorGetX(XMVector3Length(Mat.r[i]));

	return ResultMat;
}

XMMATRIX ENGINE_DLL Engine::SMath::Get_PositionMatrix(FXMMATRIX Mat)
{
	XMMATRIX ResultMat(XMMatrixIdentity());
	ResultMat.r[3] = Mat.r[3];
	return ResultMat;
}

XMMATRIX ENGINE_DLL Engine::SMath::Get_MatrixNormalize(FXMMATRIX Mat)
{
	_matrix ResultMat(XMMatrixIdentity());
	ResultMat.r[0] = XMVector3Normalize(Mat.r[0]);
	ResultMat.r[1] = XMVector3Normalize(Mat.r[1]);
	ResultMat.r[2] = XMVector3Normalize(Mat.r[2]);
	ResultMat.r[3] = Mat.r[3];
	return ResultMat;
}

XMMATRIX ENGINE_DLL Engine::SMath::Bake_MatrixNormalizeUseLookVector(FXMVECTOR In_vLook)
{
	_vector vLook(XMVector3Normalize(In_vLook));
	_vector vRight(XMVector3Cross(XMVectorSet(0.f, 1.f, 0.f, 0.f), vLook));
	_vector vUp(XMVector3Cross(vLook, vRight));

	_matrix ResultMat(XMMatrixIdentity());
	ResultMat.r[0] = XMVector3Normalize(vRight);
	ResultMat.r[1] = XMVector3Normalize(vUp);
	ResultMat.r[2] = XMVector3Normalize(vLook);
	ResultMat.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);
	return ResultMat;
}

XMMATRIX ENGINE_DLL Engine::SMath::Get_RotationQuaternion(FXMMATRIX Mat, FXMVECTOR In_vQauternion)
{
	_vector vScale(SMath::Get_Scale(Mat));

	_vector vRight(XMVectorSet(1.f, 0.f, 0.f, 0.f));
	_vector vUp(XMVectorSet(0.f, 1.f, 0.f, 0.f));
	_vector vLook(XMVectorSet(0.f, 0.f, 1.f, 0.f));

	_matrix RotationMatrix(XMMatrixRotationQuaternion(In_vQauternion));

	vRight = XMVector3Normalize(XMVector3TransformNormal(vRight, RotationMatrix));
	vUp    = XMVector3Normalize(XMVector3TransformNormal(vUp, RotationMatrix));
	vLook  = XMVector3Normalize(XMVector3TransformNormal(vLook, RotationMatrix));

	_matrix Result(XMMatrixIdentity());
	Result.r[0] = vRight * XMVectorGetX(vScale);
	Result.r[1] = vUp * XMVectorGetY(vScale);
	Result.r[2] = vLook * XMVectorGetZ(vScale);
	Result.r[3] = Mat.r[3];

	return Result;
}

XMVECTOR ENGINE_DLL Engine::SMath::Get_Scale(FXMMATRIX Mat)
{
	return XMVectorSet(XMVectorGetX(XMVector3Length(Mat.r[0])), XMVectorGetX(XMVector3Length(Mat.r[1])), XMVectorGetX(XMVector3Length(Mat.r[2])), 0.f);
}

XMVECTOR ENGINE_DLL Engine::SMath::Rotate_PositionPitchYawRoll(FXMVECTOR vPosition, FXMVECTOR vPitchYawRoll)
{
	XMMATRIX RotationMatrix(XMMatrixRotationRollPitchYaw(XMVectorGetX(vPitchYawRoll), XMVectorGetY(vPitchYawRoll), XMVectorGetZ(vPitchYawRoll)));
	return XMVector3TransformCoord(vPosition, RotationMatrix);
}

XMFLOAT3 ENGINE_DLL Engine::SMath::Extract_PitchYawRollFromRotationMatrix(FXMMATRIX Mat)
{
	XMFLOAT4X4 MatFrom4x4;
	XMStoreFloat4x4(&MatFrom4x4, Mat);

	float pitch(DirectX::XMScalarASin(-MatFrom4x4._32));

	DirectX::XMVECTOR from(DirectX::XMVectorSet(MatFrom4x4._12, MatFrom4x4._31, 0.f, 0.f));
	DirectX::XMVECTOR to(DirectX::XMVectorSet(MatFrom4x4._22, MatFrom4x4._33, 0.f, 0.f));
	DirectX::XMVECTOR res(DirectX::XMVectorATan2(from, to));

	float roll(DirectX::XMVectorGetX(res));
	float yaw(DirectX::XMVectorGetY(res));

	return XMFLOAT3(pitch, yaw, roll);
}

XMFLOAT2 ENGINE_DLL Engine::SMath::Add_Float2(const XMFLOAT2& Left, const XMFLOAT2& Right)
{
	XMVECTOR vResult(XMVectorSet(0.f, 0.f, 0.f, 0.f));

	XMVECTOR vLeft(XMLoadFloat2(&Left));
	XMVECTOR vRight(XMLoadFloat2(&Right));

	vResult = XMVectorSetX(vResult, XMVectorGetX(vLeft) + XMVectorGetX(vRight));
	vResult = XMVectorSetY(vResult, XMVectorGetY(vLeft) + XMVectorGetY(vRight));

	XMFLOAT2 f2Result;
	XMStoreFloat2(&f2Result, vResult);
	return f2Result;
}

XMFLOAT2 ENGINE_DLL Engine::SMath::Mul_Float2(const XMFLOAT2& Left, const float& Right)
{
	XMVECTOR vResult(XMVectorSet(0.f, 0.f, 0.f, 0.f));

	XMVECTOR vLeft(XMLoadFloat2(&Left));

	vResult = XMVectorSetX(vResult, XMVectorGetX(vLeft) * Right);
	vResult = XMVectorSetY(vResult, XMVectorGetY(vLeft) * Right);

	XMFLOAT2 f2Result;
	XMStoreFloat2(&f2Result, vResult);
	return f2Result;
}

void ENGINE_DLL Engine::SMath::Add_Float2(XMFLOAT2* InOut_Left, const XMFLOAT2& Right)
{
	InOut_Left->x += Right.x;
	InOut_Left->y += Right.y;
}

void ENGINE_DLL Engine::SMath::Mul_Float2(XMFLOAT2* InOut_Left, const float& Right)
{
	InOut_Left->x *= Right;
	InOut_Left->y *= Right;
}

XMFLOAT3 ENGINE_DLL Engine::SMath::Add_Float3(const XMFLOAT3& Left, const XMFLOAT3& Right)
{
	XMVECTOR vResult(XMVectorSet(0.f, 0.f, 0.f, 0.f));

	XMVECTOR vLeft(XMLoadFloat3(&Left));
	XMVECTOR vRight(XMLoadFloat3(&Right));

	vResult = XMVectorSetX(vResult, XMVectorGetX(vLeft) + XMVectorGetX(vRight));
	vResult = XMVectorSetY(vResult, XMVectorGetY(vLeft) + XMVectorGetY(vRight));
	vResult = XMVectorSetZ(vResult, XMVectorGetZ(vLeft) + XMVectorGetZ(vRight));

	XMFLOAT3 f3Result;
	XMStoreFloat3(&f3Result, vResult);
	return f3Result;
}

XMFLOAT3 ENGINE_DLL Engine::SMath::Mul_Float3(const XMFLOAT3& Left, const float& Right)
{
	XMVECTOR vResult(XMVectorSet(0.f, 0.f, 0.f, 0.f));

	XMVECTOR vLeft(XMLoadFloat3(&Left));

	vResult = XMVectorSetX(vResult, XMVectorGetX(vLeft) * Right);
	vResult = XMVectorSetY(vResult, XMVectorGetY(vLeft) * Right);
	vResult = XMVectorSetZ(vResult, XMVectorGetZ(vLeft) * Right);

	XMFLOAT3 f3Result;
	XMStoreFloat3(&f3Result, vResult);
	return f3Result;
}

void ENGINE_DLL Engine::SMath::Add_Float3(XMFLOAT3* InOut_Left, const XMFLOAT3& Right)
{
	InOut_Left->x += Right.x;
	InOut_Left->y += Right.y;
	InOut_Left->z += Right.z;
}

void ENGINE_DLL Engine::SMath::Mul_Float3(XMFLOAT3* InOut_Left, const float& Right)
{
	InOut_Left->x *= Right;
	InOut_Left->y *= Right;
	InOut_Left->z *= Right;
}

_bool ENGINE_DLL Engine::SMath::Equal_Float3(const XMFLOAT3& Left, const XMFLOAT3& Right)
{
	_vector vLeft(XMLoadFloat3(&Left));
	_vector vRight(XMLoadFloat3(&Right));
	return XMVector3Equal(vLeft, vRight);
}

XMFLOAT4 ENGINE_DLL Engine::SMath::Add_Float4(const XMFLOAT4& Left, const XMFLOAT4& Right)
{
	XMVECTOR vResult(XMVectorSet(0.f, 0.f, 0.f, 0.f));

	XMVECTOR vLeft(XMLoadFloat4(&Left));
	XMVECTOR vRight(XMLoadFloat4(&Right));

	vResult = XMVectorSetX(vResult, XMVectorGetX(vLeft) + XMVectorGetX(vRight));
	vResult = XMVectorSetY(vResult, XMVectorGetY(vLeft) + XMVectorGetY(vRight));
	vResult = XMVectorSetZ(vResult, XMVectorGetZ(vLeft) + XMVectorGetZ(vRight));
	vResult = XMVectorSetW(vResult, XMVectorGetW(vLeft) + XMVectorGetW(vRight));

	XMFLOAT4 f4Result;
	XMStoreFloat4(&f4Result, vResult);
	return f4Result;
}

XMFLOAT4 ENGINE_DLL Engine::SMath::Mul_Float4(const XMFLOAT4& Left, const float& Right)
{
	XMVECTOR vResult(XMVectorSet(0.f, 0.f, 0.f, 0.f));

	XMVECTOR vLeft(XMLoadFloat4(&Left));

	vResult = XMVectorSetX(vResult, XMVectorGetX(vLeft) * Right);
	vResult = XMVectorSetY(vResult, XMVectorGetY(vLeft) * Right);
	vResult = XMVectorSetZ(vResult, XMVectorGetZ(vLeft) * Right);
	vResult = XMVectorSetW(vResult, XMVectorGetW(vLeft) * Right);

	XMFLOAT4 f4Result;
	XMStoreFloat4(&f4Result, vResult);
	return f4Result;
}

void ENGINE_DLL Engine::SMath::Add_Float4(XMFLOAT4* InOut_Left, const XMFLOAT4& Right)
{
	InOut_Left->x += Right.x;
	InOut_Left->y += Right.y;
	InOut_Left->z += Right.z;
	InOut_Left->w += Right.w;
}

void ENGINE_DLL Engine::SMath::Mul_Float4(XMFLOAT4* InOut_Left, const float& Right)
{
	InOut_Left->x *= Right;
	InOut_Left->y *= Right;
	InOut_Left->z *= Right;
	InOut_Left->w *= Right;
}

float ENGINE_DLL Engine::SMath::Lerp(const float& fLeft, const float& fRight, float fRatio)
{
	fRatio = max(min(fRatio, 1.f), 0.f);

	return (fLeft * (1.f - fRatio)) + (fRight * (fRatio));
}

int ENGINE_DLL Engine::SMath::Random(const int& _iMin, const int& _iMax)
{
	if (_iMin >= _iMax)
		return _iMin;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> disx(_iMin, _iMax);

	return disx(gen);
}

float ENGINE_DLL Engine::SMath::fRandom(const float& _fMin, const float& _fMax)
{
	if (_fMin >= _fMax)
		return _fMin;

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> disx(_fMin, _fMax);

	return disx(gen);
}

XMFLOAT3 ENGINE_DLL Engine::SMath::vRandom(const XMFLOAT3& _vMin, const XMFLOAT3& _vMax)
{
	XMFLOAT3 Result;

	Result.x = fRandom(_vMin.x, _vMax.x);
	Result.y = fRandom(_vMin.y, _vMax.y);
	Result.z = fRandom(_vMin.z, _vMax.z);

	if (0.f == Result.x)
		Result.x = DBL_EPSILON;

	if (0.f == Result.y)
		Result.y = DBL_EPSILON;

	if (0.f == Result.z)
		Result.z = DBL_EPSILON;

	return Result;
}

XMFLOAT4 ENGINE_DLL Engine::SMath::vRandom(const XMFLOAT4& _vMin, const XMFLOAT4& _vMax)
{
	XMFLOAT4 Result;

	Result.x = fRandom(_vMin.x, _vMax.x);
	Result.y = fRandom(_vMin.y, _vMax.y);
	Result.z = fRandom(_vMin.z, _vMax.z);
	Result.w = fRandom(_vMin.w, _vMax.w);

	if (0.f == Result.x)
		Result.x = DBL_EPSILON;

	if (0.f == Result.y)
		Result.y = DBL_EPSILON;

	if (0.f == Result.z)
		Result.z = DBL_EPSILON;

	if (0.f == Result.w)
		Result.w = DBL_EPSILON;

	return Result;
}

XMVECTOR ENGINE_DLL Engine::SMath::vRandom(const XMVECTOR& _vMin, const XMVECTOR& _vMax)
{
	XMVECTOR Result(XMVectorSet(0.f, 0.f, 0.f, 0.f));

	Result = XMVectorSetX(Result, fRandom(XMVectorGetX(_vMin), XMVectorGetX(_vMax)));
	if (0.f == XMVectorGetX(Result))
		Result = XMVectorSetX(Result, DBL_EPSILON);

	Result = XMVectorSetY(Result, fRandom(XMVectorGetY(_vMin), XMVectorGetY(_vMax)));
	if (0.f == XMVectorGetY(Result))
		Result = XMVectorSetY(Result, DBL_EPSILON);

	Result = XMVectorSetZ(Result, fRandom(XMVectorGetZ(_vMin), XMVectorGetZ(_vMax)));
	if (0.f == XMVectorGetZ(Result))
		Result = XMVectorSetZ(Result, DBL_EPSILON);

	Result = XMVectorSetW(Result, fRandom(XMVectorGetW(_vMin), XMVectorGetW(_vMax)));
	if (0.f == XMVectorGetW(Result))
		Result = XMVectorSetW(Result, DBL_EPSILON);

	return Result;
}

void ENGINE_DLL Engine::SMath::Get_MouseRayInWorldSpace(RAY& Out_Ray, const _uint& In_ViewPortWidth, const _uint& In_ViewPortHeight)
{
	POINT  ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(GAMEINSTANCE->Get_WindowHandle(), &ptMouse);

	_vector vProjPos(XMVectorSet(ptMouse.x / (In_ViewPortWidth * 0.5f) - 1.f, ptMouse.y / -(In_ViewPortHeight * 0.5f) + 1.f, 0.f, 1.f));

	_matrix ProjMatrixInv(GAMEINSTANCE->Get_Transform(CPipeLine::D3DTS_PROJ));
	ProjMatrixInv = XMMatrixInverse(nullptr, ProjMatrixInv);

	_vector vViewPos(XMVector3TransformCoord(vProjPos, ProjMatrixInv));

	_vector vRayDir(vViewPos);
	_vector vRayPos(XMVectorSet(0.f, 0.f, 0.f, 1.f));

	_matrix	ViewMatrixInv(GAMEINSTANCE->Get_Transform(CPipeLine::D3DTS_VIEW));
	ViewMatrixInv = XMMatrixInverse(nullptr, ViewMatrixInv);

	XMStoreFloat3(&Out_Ray.vDirection, XMVector3TransformNormal(vRayDir, ViewMatrixInv));
	XMStoreFloat4(&Out_Ray.vOrigin, XMVector3TransformCoord(vRayPos, ViewMatrixInv));

	Out_Ray.fLength = 1000000.0f;
}

RAY ENGINE_DLL Engine::SMath::Get_MouseRayInWorldSpace(const _uint& In_ViewPortWidth, const _uint& In_ViewPortHeight)
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(GAMEINSTANCE->Get_WindowHandle(), &ptMouse);

	_vector vProjPos(XMVectorSet(ptMouse.x / (In_ViewPortWidth * 0.5f) - 1.f, ptMouse.y / -(In_ViewPortHeight * 0.5f) + 1.f, 0.f, 0.f));

	_matrix ProjMatrixInv(GAMEINSTANCE->Get_Transform(CPipeLine::D3DTS_PROJ));
	ProjMatrixInv = XMMatrixInverse(nullptr, ProjMatrixInv);

	_vector vViewPos(XMVector3TransformCoord(vProjPos, ProjMatrixInv));

	_vector vRayDir(vViewPos);
	_vector vRayPos(XMVectorSet(0.f, 0.f, 0.f, 1.f));

	_matrix	ViewMatrixInv(GAMEINSTANCE->Get_Transform(CPipeLine::D3DTS_VIEW));
	ViewMatrixInv = XMMatrixInverse(nullptr, ViewMatrixInv);

	RAY MouseRay;
	ZeroMemory(&MouseRay, sizeof(RAY));

	XMStoreFloat3(&MouseRay.vDirection, XMVector3Normalize(XMVector3TransformNormal(vRayDir, ViewMatrixInv)));
	XMStoreFloat4(&MouseRay.vOrigin, XMVector3TransformCoord(vRayPos, ViewMatrixInv));

	MouseRay.fLength = 1000000.0f;
	return MouseRay;
}


XMMATRIX ENGINE_DLL Engine::SMath::Set_ScaleMatrix(FXMMATRIX Mat, FXMVECTOR Scale)
{
	XMMATRIX ResultMat(XMMatrixIdentity());
	ResultMat.r[0] = XMVector3Normalize(Mat.r[0]) * XMVectorGetX(Scale);
	ResultMat.r[1] = XMVector3Normalize(Mat.r[1]) * XMVectorGetY(Scale);
	ResultMat.r[2] = XMVector3Normalize(Mat.r[2]) * XMVectorGetZ(Scale);
	ResultMat.r[3] = Mat.r[3];
	return ResultMat;
}

XMMATRIX ENGINE_DLL Engine::SMath::Go_Right(FXMMATRIX Mat, float fScaler)
{
	XMMATRIX ResultMat(Mat);
	_vector vPosition(ResultMat.r[3]);
	_vector vRight(ResultMat.r[0]);
	vPosition += XMVector3Normalize(vRight) * fScaler;
	ResultMat.r[3] = vPosition;
	return ResultMat;
}

XMMATRIX ENGINE_DLL Engine::SMath::Go_Straight(FXMMATRIX Mat, float fScaler)
{
	XMMATRIX ResultMat(Mat);
	_vector vPosition(ResultMat.r[3]);
	_vector vLook(ResultMat.r[2]);
	vPosition += XMVector3Normalize(vLook) * fScaler;
	ResultMat.r[3] = vPosition;
	return ResultMat;
}

XMMATRIX ENGINE_DLL Engine::SMath::Go_Up(FXMMATRIX Mat, float fScaler)
{
	XMMATRIX ResultMat(Mat);
	_vector vPosition(ResultMat.r[3]);
	_vector vUp(ResultMat.r[1]);
	vPosition += XMVector3Normalize(vUp) * fScaler;
	ResultMat.r[3] = vPosition;
	return ResultMat;
}

XMMATRIX ENGINE_DLL Engine::SMath::Add_PositionWithRotation(FXMMATRIX Mat, FXMVECTOR vPosition)
{
	_vector vRotatedPosition(XMVector3TransformCoord(vPosition, SMath::Get_RotationMatrix(Mat)));
	_matrix ResultMatrix(Mat);
	ResultMatrix.r[3] += vRotatedPosition;
	ResultMatrix.r[3] = XMVectorSetW(ResultMatrix.r[3], 1.f);
	return ResultMatrix;
}

XMMATRIX ENGINE_DLL Engine::SMath::LookAt(FXMMATRIX Mat, FXMVECTOR In_vPosition)
{
	XMMATRIX ResultMat(XMMatrixIdentity());
	XMVECTOR vScale(SMath::Get_Scale(Mat));
	_vector vPosition(Mat.r[3]);
	_vector vLook(XMVector3Normalize(In_vPosition - vPosition));
	_vector vRight(XMVector3Normalize(XMVector3Cross(XMVectorSet(0.f, 1.f, 0.f, 0.f), vLook)));
	_vector vUp(XMVector3Normalize(XMVector3Cross(vLook, vRight)));
	ResultMat.r[0] = XMVector3Normalize(vRight) * XMVectorGetX(vScale);
	ResultMat.r[1] = XMVector3Normalize(vUp)	* XMVectorGetY(vScale);
	ResultMat.r[2] = XMVector3Normalize(vLook)	* XMVectorGetZ(vScale);
	ResultMat.r[3] = vPosition;
	return ResultMat;
}

XMMATRIX ENGINE_DLL Engine::SMath::Bake_WorldMatrix(const XMFLOAT3& In_vScale, const XMFLOAT3& In_vRot, const XMFLOAT3& In_vPos)
{
	_vector vPitchYawRoll(XMLoadFloat3(&In_vRot));
	_vector vPosition(XMLoadFloat3(&In_vPos));
	vPosition = XMVectorSetW(vPosition, 1.f);
	_matrix RotationMatrix(XMMatrixRotationRollPitchYawFromVector(vPitchYawRoll));
	_matrix ScaleMatrix(XMMatrixScaling(In_vScale.x, In_vScale.y, In_vScale.z));
	_matrix TransformationMatrix(ScaleMatrix * RotationMatrix);
	TransformationMatrix.r[3] = vPosition;
	return TransformationMatrix;
}

XMMATRIX ENGINE_DLL Engine::SMath::Bake_WorldMatrix(const XMFLOAT2& In_vScale, const XMFLOAT3& In_vRot, const XMFLOAT3& In_vPos)
{
	_vector vPitchYawRoll(XMLoadFloat3(&In_vRot));
	_vector vPosition(XMLoadFloat3(&In_vPos));
	vPosition = XMVectorSetW(vPosition, 1.f);
	_matrix RotationMatrix(XMMatrixRotationRollPitchYawFromVector(vPitchYawRoll));
	_matrix ScaleMatrix(XMMatrixScaling(In_vScale.x, In_vScale.y, 1.f));
	_matrix TransformationMatrix(ScaleMatrix * RotationMatrix);
	TransformationMatrix.r[3] = vPosition;
	return TransformationMatrix;
}

bool ENGINE_DLL Engine::SMath::Is_SphereToRayCollision(const XMFLOAT3& Center, const float& Radius, FXMVECTOR Origin, FXMVECTOR Direction, float& Dist)
{
	XMVECTOR vCenter(XMLoadFloat3(&Center));
	XMVECTOR vRadius(XMVectorReplicatePtr(&Radius));
	XMVECTOR l(XMVectorSubtract(vCenter, Origin));
	XMVECTOR s(XMVector3Dot(l, Direction));
	XMVECTOR l2(XMVector3Dot(l, l));
	XMVECTOR r2(XMVectorMultiply(vRadius, vRadius));
	XMVECTOR m2(XMVectorNegativeMultiplySubtract(s, s, l2));
	XMVECTOR NoIntersection{ 0.f, 0.f, 0.f, 0.f };
	NoIntersection = XMVectorAndInt(XMVectorLess(s, XMVectorZero()), XMVectorGreater(l2, r2));
	NoIntersection = XMVectorOrInt(NoIntersection, XMVectorGreater(m2, r2));
	XMVECTOR q(XMVectorSqrt(XMVectorSubtract(r2, m2)));
	XMVECTOR t1(XMVectorSubtract(s, q));
	XMVECTOR t2(XMVectorAdd(s, q));
	XMVECTOR OriginInside(XMVectorLessOrEqual(l2, r2));
	XMVECTOR t(XMVectorSelect(t1, t2, OriginInside));
	if (XMVector4NotEqualInt(NoIntersection, XMVectorTrueInt()))
	{
		XMStoreFloat(&Dist, t);
		return true;
	}
	Dist = 0.f;
	return false;
}

void ENGINE_DLL Engine::SMath::Set_ClockwiseTriangle(XMFLOAT3* InOut_TrianglePosition)
{
	_vector vPositionFromVector[3];
	for (int i(0); i < 3; i++)
		vPositionFromVector[i] = XMLoadFloat3(&(InOut_TrianglePosition[i]));

	_vector vAtoB(vPositionFromVector[1] - vPositionFromVector[0]);
	_vector vAtoC(vPositionFromVector[2] - vPositionFromVector[0]);

	_vector vAtoB2D, vAtoC2D, vAtoB2DCross;
	vAtoB2D = vAtoC2D = vAtoB2DCross = XMVectorSet(0.f, 0.f, 0.f, 0.f);
	vAtoB2D = XMVectorSetX(vAtoB2D, XMVectorGetX(vAtoB));
	vAtoB2D = XMVectorSetY(vAtoB2D, XMVectorGetZ(vAtoB));
	vAtoC2D = XMVectorSetX(vAtoC2D, XMVectorGetX(vAtoC));
	vAtoC2D = XMVectorSetY(vAtoC2D, XMVectorGetZ(vAtoC));
	vAtoB2DCross = XMVectorSetX(vAtoB2DCross, -1.f * XMVectorGetY(vAtoB2D));
	vAtoB2DCross = XMVectorSetY(vAtoB2DCross, XMVectorGetX(vAtoB2D));
	_float fDot(XMVectorGetX(XMVector2Dot(vAtoB2DCross, vAtoC2D)));
	if (0.f < fDot)
	{
		XMStoreFloat3(&InOut_TrianglePosition[1], vPositionFromVector[2]);
		XMStoreFloat3(&InOut_TrianglePosition[2], vPositionFromVector[1]);
	}
}

_bool ENGINE_DLL Engine::SMath::Is_Picked_AbstractTerrain(const RAY& _Ray, _float4* _pOutPos)
{
	if (0 != isnan(_Ray.vOrigin.x))
		return false;

	_float3 vPos[4] =
	{
		_float3(-99999.f, _pOutPos->y,  99999.f),
		_float3( 99999.f, _pOutPos->y,  99999.f),
		_float3( 99999.f, _pOutPos->y, -99999.f),
		_float3(-99999.f, _pOutPos->y, -99999.f)
	};

	_uint3 iIndex[2] =
	{
		_uint3(0, 1, 2),
		_uint3(0, 2, 3)
	};

	for (_uint i(0); i < 2; ++i)
	{
		if (0 != isnan(_Ray.vOrigin.x))
			break;

		_vector vPickedPos(XMVectorSet(0.f, 0.f, 0.f, 0.f));
		_vector	vVec0(XMLoadFloat3(&vPos[iIndex[i].ix]));
		_vector	vVec1(XMLoadFloat3(&vPos[iIndex[i].iy]));
		_vector	vVec2(XMLoadFloat3(&vPos[iIndex[i].iz]));

		_float fDist(0.f);
		if (DirectX::TriangleTests::Intersects(XMLoadFloat4(&_Ray.vOrigin), XMLoadFloat3(&_Ray.vDirection), vVec0, vVec1, vVec2, fDist))
		{
			vPickedPos = XMLoadFloat4(&_Ray.vOrigin) + XMVector3Normalize(XMLoadFloat3(&_Ray.vDirection)) * fDist;
			XMStoreFloat4(_pOutPos, vPickedPos);

			return true;
		}
	}

	return false;
}

_bool ENGINE_DLL Engine::SMath::Is_Picked_AbstractCube(const RAY& _Ray, MESH_VTX_INFO _VtxInfo, _matrix _WorldMatrix, _float* Out_pDist)
{
	if (0 != isnan(_Ray.vOrigin.x))
		return false;

	_matrix WorldMatrixInv(XMMatrixInverse(nullptr, _WorldMatrix));

	_vector vRayPos(XMVector3TransformCoord(XMLoadFloat4(&_Ray.vOrigin), WorldMatrixInv));
	_vector vRayDir(XMVector3Normalize(XMVector3TransformNormal(XMLoadFloat3(&_Ray.vDirection), WorldMatrixInv)));

	_float3 vPosition[8];
	_uint3	vIndex[12];

	vPosition[0] = { _VtxInfo.vMin.x, _VtxInfo.vMax.y, _VtxInfo.vMin.z };
	vPosition[1] = { _VtxInfo.vMax.x, _VtxInfo.vMax.y, _VtxInfo.vMin.z };
	vPosition[2] = { _VtxInfo.vMax.x, _VtxInfo.vMin.y, _VtxInfo.vMin.z };
	vPosition[3] = { _VtxInfo.vMin.x, _VtxInfo.vMin.y, _VtxInfo.vMin.z };
	vPosition[4] = { _VtxInfo.vMin.x, _VtxInfo.vMax.y, _VtxInfo.vMax.z };
	vPosition[5] = { _VtxInfo.vMax.x, _VtxInfo.vMax.y, _VtxInfo.vMax.z };
	vPosition[6] = { _VtxInfo.vMax.x, _VtxInfo.vMin.y, _VtxInfo.vMax.z };
	vPosition[7] = { _VtxInfo.vMin.x, _VtxInfo.vMin.y, _VtxInfo.vMax.z };

	vIndex[0]  = { 1, 5, 6 };
	vIndex[1]  = { 1, 6, 2 };
	vIndex[2]  = { 4, 0, 3 };
	vIndex[3]  = { 4, 3, 7 };
	vIndex[4]  = { 4, 5, 1 };
	vIndex[5]  = { 4, 1, 0 };
	vIndex[6]  = { 3, 2, 6 };
	vIndex[7]  = { 3, 6, 7 };
	vIndex[8]  = { 5, 4, 7 };
	vIndex[9]  = { 5, 7, 6 };
	vIndex[10] = { 0, 1, 2 };
	vIndex[11] = { 0, 2, 3 };

	_float fDist(0.f);
	for (_uint i(0); i < 12; ++i)
	{
		_vector	vVec0(XMLoadFloat3(&vPosition[vIndex[i].ix]));
		_vector	vVec1(XMLoadFloat3(&vPosition[vIndex[i].iy]));
		_vector	vVec2(XMLoadFloat3(&vPosition[vIndex[i].iz]));

		if (true == DirectX::TriangleTests::Intersects(vRayPos, vRayDir, vVec0, vVec1, vVec2, fDist))
		{
			if (Out_pDist)
				*Out_pDist = fDist;

			return true;
		}
	}

	return false;
}

const _bool ENGINE_DLL Engine::SMath::Is_Equal(const XMFLOAT2 Left, const XMFLOAT2 Right)
{
	_float fXDiff(fabs(Left.x - Right.x));
	_float fYDiff(fabs(Left.y - Right.y));
	return ((fXDiff < DBL_EPSILON) && (fYDiff < DBL_EPSILON)) ? true : false;
}

const _bool ENGINE_DLL Engine::SMath::Is_Equal(const XMFLOAT3 Left, const XMFLOAT3 Right)
{
	_float fXDiff(fabs(Left.x - Right.x));
	_float fYDiff(fabs(Left.y - Right.y));
	_float fZDiff(fabs(Left.z - Right.z));
	return ((fXDiff < DBL_EPSILON) && (fYDiff < DBL_EPSILON) && (fZDiff < DBL_EPSILON)) ? true : false;
}

const _bool ENGINE_DLL Engine::SMath::Is_Equal(const XMFLOAT4 Left, const XMFLOAT4 Right)
{
	_float fXDiff(fabs(Left.x - Right.x));
	_float fYDiff(fabs(Left.y - Right.y));
	_float fZDiff(fabs(Left.z - Right.z));
	_float fWDiff(fabs(Left.w - Right.w));
	return ((fXDiff < DBL_EPSILON) && (fYDiff < DBL_EPSILON) && (fZDiff < DBL_EPSILON) && (fWDiff < DBL_EPSILON)) ? true : false;
}

const _bool ENGINE_DLL Engine::SMath::Is_InRange(const XMFLOAT3 Left, const XMFLOAT3 Right, const _float fRange)
{
	XMVECTOR vLeft(XMLoadFloat3(&Left));
	XMVECTOR vRight(XMLoadFloat3(&Right));
	XMVECTOR vDistance(vLeft - vRight);

	_float fDistance(XMVectorGetX(XMVector3Length(vDistance)));

	return fDistance < fRange ? true : false;
}

const _bool ENGINE_DLL Engine::SMath::Is_InRange(const XMFLOAT4 Left, const XMFLOAT4 Right, const _float fRange)
{
	XMVECTOR vLeft(XMLoadFloat4(&Left));
	XMVECTOR vRight(XMLoadFloat4(&Right));
	XMVECTOR vDistance(vLeft - vRight);

	_float fDistance(XMVectorGetX(XMVector3Length(vDistance)));

	return fDistance < fRange ? true : false;
}


void ENGINE_DLL Engine::SMath::Convert_PxVec3FromMeshData(PxVec3* In_PxVec3, weak_ptr<MESH_DATA> pMeshData)
{
	_uint iNumVertices(pMeshData.lock()->iNumVertices);
	MODEL_TYPE eActorType(pMeshData.lock()->eModelType);
	for (_uint i(0); i < iNumVertices; ++i)
	{
		switch (eActorType)
		{
		case MODEL_TYPE::NONANIM:
			memcpy(&In_PxVec3[i], &pMeshData.lock()->pVertices[i].vPosition, sizeof(PxVec3));
			break;
		case MODEL_TYPE::ANIM:
			memcpy(&In_PxVec3[i], &pMeshData.lock()->pAnimVertices[i].vPosition, sizeof(PxVec3));
			break;
		case MODEL_TYPE::NAVI:
			memcpy(&In_PxVec3[i], &pMeshData.lock()->pPosVertices[i].vPosition, sizeof(PxVec3));
			break;
		case MODEL_TYPE::GROUND:
			memcpy(&In_PxVec3[i], &pMeshData.lock()->pGroundVertices[i].vPosition, sizeof(PxVec3));
			break;
		case MODEL_TYPE::TYPE_END:
			DEBUG_ASSERT;
			break;
		default:
			DEBUG_ASSERT;
			break;
		}
	}

}

void ENGINE_DLL Engine::SMath::Convert_PxVec3FromMeshDataWithTransformMatrix(PxVec3* In_PxVec3, weak_ptr<MESH_DATA> pMeshData, FXMMATRIX In_TransformMatrix)
{
	_uint iNumVertices(pMeshData.lock()->iNumVertices);
	MODEL_TYPE eActorType(pMeshData.lock()->eModelType);
	_vector vPosition(XMVectorSet(0.f, 0.f, 0.f, 0.f));
	for (_uint i(0); i < iNumVertices; ++i)
	{
		switch (eActorType)
		{
		case MODEL_TYPE::NONANIM:
			vPosition = XMVector3TransformCoord(XMLoadFloat3(&pMeshData.lock()->pVertices[i].vPosition), In_TransformMatrix);
			memcpy(&In_PxVec3[i], &vPosition, sizeof(PxVec3));
			break;
		case MODEL_TYPE::ANIM:
			vPosition = XMVector3TransformCoord(XMLoadFloat3(&pMeshData.lock()->pAnimVertices[i].vPosition), In_TransformMatrix);
			memcpy(&In_PxVec3[i], &vPosition, sizeof(PxVec3));
			break;
		case MODEL_TYPE::NAVI:
			vPosition = XMVector3TransformCoord(XMLoadFloat3(&pMeshData.lock()->pPosVertices[i].vPosition), In_TransformMatrix);
			memcpy(&In_PxVec3[i], &vPosition, sizeof(PxVec3));
			break;
		case MODEL_TYPE::GROUND:
			vPosition = XMVector3TransformCoord(XMLoadFloat3(&pMeshData.lock()->pGroundVertices[i].vPosition), In_TransformMatrix);
			memcpy(&In_PxVec3[i], &vPosition, sizeof(PxVec3));
			break;
		case MODEL_TYPE::TYPE_END:
			DEBUG_ASSERT;
			break;
		default:
			DEBUG_ASSERT;
			break;
		}
	}
}

PxExtendedVec3 ENGINE_DLL Engine::SMath::Convert_PxExtendedVec3(FXMVECTOR In_Vector)
{
	return PxExtendedVec3(XMVectorGetX(In_Vector), XMVectorGetY(In_Vector), XMVectorGetZ(In_Vector));
}

PxExtendedVec3 ENGINE_DLL Engine::SMath::Convert_PxExtendedVec3(PxVec3 In_Vector)
{
	return PxExtendedVec3(In_Vector.x, In_Vector.y, In_Vector.z);
}

PxVec3 ENGINE_DLL Engine::SMath::Convert_PxVec3(FXMVECTOR In_Vector)
{
	return PxVec3(XMVectorGetX(In_Vector), XMVectorGetY(In_Vector), XMVectorGetZ(In_Vector));
}

PxVec3 ENGINE_DLL Engine::SMath::Convert_PxVec3(const XMFLOAT3& In_Float3)
{
	return PxVec3(In_Float3.x, In_Float3.y, In_Float3.z);
}

XMVECTOR ENGINE_DLL Engine::SMath::Convert_Vector(const PxVec3& In_PxVec3)
{
	return XMVectorSet(_float(In_PxVec3.x), _float(In_PxVec3.y), _float(In_PxVec3.z), 0.f);
}

XMVECTOR ENGINE_DLL Engine::SMath::Convert_Vector(const PxVec4& In_PxVec4)
{
	return XMVectorSet(_float(In_PxVec4.x), _float(In_PxVec4.y), _float(In_PxVec4.z), _float(In_PxVec4.w));
}

XMVECTOR ENGINE_DLL Engine::SMath::Convert_PxExtendedVec3ToVector(const PxExtendedVec3& In_PxVec3)
{
	return XMVectorSet(_float(In_PxVec3.x), _float(In_PxVec3.y), _float(In_PxVec3.z), 0.f);
}

PxQuat ENGINE_DLL Engine::SMath::Convert_PxQuat(FXMVECTOR In_Vector)
{
	return PxQuat(In_Vector.m128_f32[0], In_Vector.m128_f32[1], In_Vector.m128_f32[2], In_Vector.m128_f32[3]);
}

FMOD_VECTOR ENGINE_DLL Engine::SMath::Convert_FMOD_VECTOR(FXMVECTOR In_Vector)
{
	FMOD_VECTOR vResult;
	vResult.x = In_Vector.m128_f32[0];
	vResult.y = In_Vector.m128_f32[1];
	vResult.z = In_Vector.m128_f32[2];

	return vResult;
}

PxVec3 ENGINE_DLL Engine::SMath::Convert_PxVec3(PxExtendedVec3 In_Vector)
{
	return PxVec3(_float(In_Vector.x), _float(In_Vector.y), _float(In_Vector.z));
}

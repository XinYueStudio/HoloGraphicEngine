#pragma once
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
 
#define MAT(m,r,c) (m)[(c)*4+(r)]

#define RETURN_ZERO \
{ \
	for (int i=0;i<16;i++) \
		out[i] = 0.0F; \
	return false; \
}

// 4x4 matrix inversion by Gaussian reduction with partial pivoting followed by back/substitution;
// with loops manually unrolled.

#define SWAP_ROWS(a, b) { float *_tmp = a; (a)=(b); (b)=_tmp; }
inline bool InvertMatrix4x4_Full(const float* m, float* out)
{
	float wtmp[4][8];
	float m0, m1, m2, m3, s;
	float *r0, *r1, *r2, *r3;

	r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];

	r0[0] = MAT(m, 0, 0), r0[1] = MAT(m, 0, 1),
		r0[2] = MAT(m, 0, 2), r0[3] = MAT(m, 0, 3),
		r0[4] = 1.0, r0[5] = r0[6] = r0[7] = 0.0,

		r1[0] = MAT(m, 1, 0), r1[1] = MAT(m, 1, 1),
		r1[2] = MAT(m, 1, 2), r1[3] = MAT(m, 1, 3),
		r1[5] = 1.0, r1[4] = r1[6] = r1[7] = 0.0,

		r2[0] = MAT(m, 2, 0), r2[1] = MAT(m, 2, 1),
		r2[2] = MAT(m, 2, 2), r2[3] = MAT(m, 2, 3),
		r2[6] = 1.0, r2[4] = r2[5] = r2[7] = 0.0,

		r3[0] = MAT(m, 3, 0), r3[1] = MAT(m, 3, 1),
		r3[2] = MAT(m, 3, 2), r3[3] = MAT(m, 3, 3),
		r3[7] = 1.0, r3[4] = r3[5] = r3[6] = 0.0;

	/* choose pivot - or die */
	if (Abs(r3[0])>Abs(r2[0])) SWAP_ROWS(r3, r2);
	if (Abs(r2[0])>Abs(r1[0])) SWAP_ROWS(r2, r1);
	if (Abs(r1[0])>Abs(r0[0])) SWAP_ROWS(r1, r0);
	if (0.0F == r0[0]) RETURN_ZERO

		/* eliminate first variable     */
		m1 = r1[0] / r0[0]; m2 = r2[0] / r0[0]; m3 = r3[0] / r0[0];
	s = r0[1]; r1[1] -= m1 * s; r2[1] -= m2 * s; r3[1] -= m3 * s;
	s = r0[2]; r1[2] -= m1 * s; r2[2] -= m2 * s; r3[2] -= m3 * s;
	s = r0[3]; r1[3] -= m1 * s; r2[3] -= m2 * s; r3[3] -= m3 * s;
	s = r0[4];
	if (s != 0.0F) { r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s; }
	s = r0[5];
	if (s != 0.0F) { r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s; }
	s = r0[6];
	if (s != 0.0F) { r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s; }
	s = r0[7];
	if (s != 0.0F) { r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s; }

	/* choose pivot - or die */
	if (Abs(r3[1])>Abs(r2[1])) SWAP_ROWS(r3, r2);
	if (Abs(r2[1])>Abs(r1[1])) SWAP_ROWS(r2, r1);
	if (0.0F == r1[1]) RETURN_ZERO;

	/* eliminate second variable */
	m2 = r2[1] / r1[1]; m3 = r3[1] / r1[1];
	r2[2] -= m2 * r1[2]; r3[2] -= m3 * r1[2];
	r2[3] -= m2 * r1[3]; r3[3] -= m3 * r1[3];
	s = r1[4]; if (0.0F != s) { r2[4] -= m2 * s; r3[4] -= m3 * s; }
	s = r1[5]; if (0.0F != s) { r2[5] -= m2 * s; r3[5] -= m3 * s; }
	s = r1[6]; if (0.0F != s) { r2[6] -= m2 * s; r3[6] -= m3 * s; }
	s = r1[7]; if (0.0F != s) { r2[7] -= m2 * s; r3[7] -= m3 * s; }

	/* choose pivot - or die */
	if (Abs(r3[2])>Abs(r2[2])) SWAP_ROWS(r3, r2);
	if (0.0F == r2[2]) RETURN_ZERO;

	/* eliminate third variable */
	m3 = r3[2] / r2[2];
	r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
		r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6],
		r3[7] -= m3 * r2[7];

	/* last check */
	if (0.0F == r3[3]) RETURN_ZERO;

	s = 1.0F / r3[3];             /* now back substitute row 3 */
	r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;

	m2 = r2[3];                 /* now back substitute row 2 */
	s = 1.0F / r2[2];
	r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
		r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
	m1 = r1[3];
	r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
		r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
	m0 = r0[3];
	r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
		r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;

	m1 = r1[2];                 /* now back substitute row 1 */
	s = 1.0F / r1[1];
	r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
		r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
	m0 = r0[2];
	r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
		r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;

	m0 = r0[1];                 /* now back substitute row 0 */
	s = 1.0F / r0[0];
	r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
		r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);

	MAT(out, 0, 0) = r0[4]; MAT(out, 0, 1) = r0[5], MAT(out, 0, 2) = r0[6]; MAT(out, 0, 3) = r0[7],
		MAT(out, 1, 0) = r1[4]; MAT(out, 1, 1) = r1[5], MAT(out, 1, 2) = r1[6]; MAT(out, 1, 3) = r1[7],
		MAT(out, 2, 0) = r2[4]; MAT(out, 2, 1) = r2[5], MAT(out, 2, 2) = r2[6]; MAT(out, 2, 3) = r2[7],
		MAT(out, 3, 0) = r3[4]; MAT(out, 3, 1) = r3[5], MAT(out, 3, 2) = r3[6]; MAT(out, 3, 3) = r3[7];

	return true;
}

#undef SWAP_ROWS

 


class Matrix4x4
{
public:
	float m_Data[16];

	Matrix4x4() {}


	float& Get(int row, int column) { return m_Data[row + (column * 4)]; }
	const float& Get(int row, int column)const { return m_Data[row + (column * 4)]; }
	float* GetPtr() { return m_Data; }
	const float* GetPtr()const { return m_Data; }

	float operator [] (int index) const { return m_Data[index]; }
	float& operator [] (int index) { return m_Data[index]; }

	Matrix4x4& operator *= (const Matrix4x4& inM);

	 
	Matrix4x4& SetPerspective(float fovy, float aspect, float zNear, float zFar);
	 

	 

	Matrix4x4& Invert_Full() {
		InvertMatrix4x4_Full(m_Data, m_Data);
		return *this;}
 
};
 

void MultiplyMatrices4x4REF(const Matrix4x4*  lhs, const Matrix4x4*  rhs, Matrix4x4*  res);

inline Matrix4x4 MultiplyMatrix(Matrix4x4 lhs, Matrix4x4 rhs)
{
	Matrix4x4 res = Matrix4x4();
	res.m_Data[0] = lhs.m_Data[0] * rhs.m_Data[0] + lhs.m_Data[4] * rhs.m_Data[1] + lhs.m_Data[8] * rhs.m_Data[2] + lhs.m_Data[12] * rhs.m_Data[3];
	res.m_Data[4] = lhs.m_Data[0] * rhs.m_Data[4] + lhs.m_Data[4] * rhs.m_Data[5] + lhs.m_Data[8] * rhs.m_Data[6] + lhs.m_Data[12] * rhs.m_Data[7];
	res.m_Data[8] = lhs.m_Data[0] * rhs.m_Data[8] + lhs.m_Data[4] * rhs.m_Data[9] + lhs.m_Data[8] * rhs.m_Data[10] + lhs.m_Data[12] * rhs.m_Data[11];
	res.m_Data[12] = lhs.m_Data[0] * rhs.m_Data[12] + lhs.m_Data[4] * rhs.m_Data[13] + lhs.m_Data[8] * rhs.m_Data[14] + lhs.m_Data[12] * rhs.m_Data[15];

	res.m_Data[1] = lhs.m_Data[1] * rhs.m_Data[0] + lhs.m_Data[5] * rhs.m_Data[1] + lhs.m_Data[9] * rhs.m_Data[2] + lhs.m_Data[13] * rhs.m_Data[3];
	res.m_Data[5] = lhs.m_Data[1] * rhs.m_Data[4] + lhs.m_Data[5] * rhs.m_Data[5] + lhs.m_Data[9] * rhs.m_Data[6] + lhs.m_Data[13] * rhs.m_Data[7];
	res.m_Data[9] = lhs.m_Data[1] * rhs.m_Data[8] + lhs.m_Data[5] * rhs.m_Data[9] + lhs.m_Data[9] * rhs.m_Data[10] + lhs.m_Data[13] * rhs.m_Data[11];
	res.m_Data[13] = lhs.m_Data[1] * rhs.m_Data[12] + lhs.m_Data[5] * rhs.m_Data[13] + lhs.m_Data[9] * rhs.m_Data[14] + lhs.m_Data[13] * rhs.m_Data[15];

	res.m_Data[2] = lhs.m_Data[2] * rhs.m_Data[0] + lhs.m_Data[6] * rhs.m_Data[1] + lhs.m_Data[10] * rhs.m_Data[2] + lhs.m_Data[14] * rhs.m_Data[3];
	res.m_Data[6] = lhs.m_Data[2] * rhs.m_Data[4] + lhs.m_Data[6] * rhs.m_Data[5] + lhs.m_Data[10] * rhs.m_Data[6] + lhs.m_Data[14] * rhs.m_Data[7];
	res.m_Data[10] = lhs.m_Data[2] * rhs.m_Data[8] + lhs.m_Data[6] * rhs.m_Data[9] + lhs.m_Data[10] * rhs.m_Data[10] + lhs.m_Data[14] * rhs.m_Data[11];
	res.m_Data[14] = lhs.m_Data[2] * rhs.m_Data[12] + lhs.m_Data[6] * rhs.m_Data[13] + lhs.m_Data[10] * rhs.m_Data[14] + lhs.m_Data[14] * rhs.m_Data[15];

	res.m_Data[3] = lhs.m_Data[3] * rhs.m_Data[0] + lhs.m_Data[7] * rhs.m_Data[1] + lhs.m_Data[11] * rhs.m_Data[2] + lhs.m_Data[15] * rhs.m_Data[3];
	res.m_Data[7] = lhs.m_Data[3] * rhs.m_Data[4] + lhs.m_Data[7] * rhs.m_Data[5] + lhs.m_Data[11] * rhs.m_Data[6] + lhs.m_Data[15] * rhs.m_Data[7];
	res.m_Data[11] = lhs.m_Data[3] * rhs.m_Data[8] + lhs.m_Data[7] * rhs.m_Data[9] + lhs.m_Data[11] * rhs.m_Data[10] + lhs.m_Data[15] * rhs.m_Data[11];
	res.m_Data[15] = lhs.m_Data[3] * rhs.m_Data[12] + lhs.m_Data[7] * rhs.m_Data[13] + lhs.m_Data[11] * rhs.m_Data[14] + lhs.m_Data[15] * rhs.m_Data[15];

	return res;
}

inline Vector4  MultiplyVector4(Matrix4x4  lhs,Vector4 v)
{
	Vector4 res = Vector4();
	res.x = lhs.m_Data[0] * v.x + lhs.m_Data[4] * v.y + lhs.m_Data[8] * v.z + lhs.m_Data[12] * v.w;
	res.y = lhs.m_Data[1] * v.x + lhs.m_Data[5] * v.y + lhs.m_Data[9] * v.z + lhs.m_Data[13] * v.w;
	res.z = lhs.m_Data[2] * v.x + lhs.m_Data[6] * v.y + lhs.m_Data[10] * v.z + lhs.m_Data[14] * v.w;
	res.w = lhs.m_Data[3] * v.x + lhs.m_Data[7] * v.y + lhs.m_Data[11] * v.z + lhs.m_Data[15] * v.w;
	return res;

}

inline float Deg2RadFun(float deg)
{
	// TODO : should be deg * kDeg2Rad, but can't be changed, 
	// because it changes the order of operations and that affects a replay in some RegressionTests
	return deg / 360.0F * 2.0F * 3.14159265358979323846264338327950288419716939937510F;
}

inline Matrix4x4  Perspective(float fovy, float aspect, float zNear, float zFar)
{
	float cotangent, deltaZ;
	float radians = Deg2RadFun(fovy / 2.0f);
	cotangent = cos(radians) / sin(radians);
	deltaZ = zNear - zFar;
	Matrix4x4 res = Matrix4x4();
	res.Get(0, 0) = cotangent / aspect;	res.Get(0, 1) = 0.0F;      res.Get(0, 2) = 0.0F;                   res.Get(0, 3) = 0.0F;
	res.Get(1, 0) = 0.0F;               res.Get(1, 1) = cotangent; res.Get(1, 2) = 0.0F;                   res.Get(1, 3) = 0.0F;
	res.Get(2, 0) = 0.0F;               res.Get(2, 1) = 0.0F;      res.Get(2, 2) = (zFar + zNear) / deltaZ; res.Get(2, 3) = 2.0F * zNear * zFar / deltaZ;
	res.Get(3, 0) = 0.0F;               res.Get(3, 1) = 0.0F;      res.Get(3, 2) = -1.0F;                   res.Get(3, 3) = 0.0F;

	return res;
}

inline Matrix4x4 QuaternionToMatrix(Quaternion  &q)
{
	Matrix4x4 m = Matrix4x4();
	//float norm = GetNorm (q);
	//float s = (norm > 0.0) ? 2.0/norm : 0;

	// Precalculate coordinate products
	float x = q.x * 2.0F;
	float y = q.y * 2.0F;
	float z = q.z * 2.0F;
	float xx = q.x * x;
	float yy = q.y * y;
	float zz = q.z * z;
	float xy = q.x * y;
	float xz = q.x * z;
	float yz = q.y * z;
	float wx = q.w * x;
	float wy = q.w * y;
	float wz = q.w * z;

	// Calculate 3x3 matrix from orthonormal basis
	m.m_Data[0] = 1.0f - (yy + zz);
	m.m_Data[1] = xy + wz;
	m.m_Data[2] = xz - wy;
	m.m_Data[3] = 0;

	m.m_Data[4] = xy - wz;
	m.m_Data[5] = 1.0f - (xx + zz);
	m.m_Data[6] = yz + wx;
	m.m_Data[7] = 0;

	m.m_Data[8] = xz + wy;
	m.m_Data[9] = yz - wx;
	m.m_Data[10] = 1.0f - (xx + yy);
	m.m_Data[11] = 0.0F;

	m.m_Data[12] = 0.0F;
	m.m_Data[13] = 0.0F;
	m.m_Data[14] = 0.0F;
	m.m_Data[15] = 1.0F;

	return m;
}

inline Matrix4x4 SetTRS( Vector3  pos,  Vector3  iv, const Vector3  s)
{
	Vector3  v = iv * (3.1415926535897931f*2.0F / 360.0F);
	Matrix4x4 res = Matrix4x4();

	float cX(cos(v.x / 2.0f));
	float sX(sin(v.x / 2.0f));

	float cY(cos(v.y / 2.0f));
	float sY(sin(v.y / 2.0f));

	float cZ(cos(v.z / 2.0f));
	float sZ(sin(v.z / 2.0f));

	Quaternion qX(sX, 0.0F, 0.0F, cX);
	Quaternion qY(0.0F, sY, 0.0F, cY);
	Quaternion qZ(0.0F, 0.0F, sZ, cZ);

	Quaternion q = (qY * qX) * qZ;


	res=	QuaternionToMatrix(q);

	res.m_Data[0] *= s[0];
	res.m_Data[1] *= s[0];
	res.m_Data[2] *= s[0];

	res.m_Data[4] *= s[1];
	res.m_Data[5] *= s[1];
	res.m_Data[6] *= s[1];

	res.m_Data[8] *= s[2];
	res.m_Data[9] *= s[2];
	res.m_Data[10] *= s[2];

	res.m_Data[12] = pos[0];
	res.m_Data[13] = pos[1];
	res.m_Data[14] = pos[2];

	return res;
}

inline Matrix4x4 SetFrustum(
	float left,
	float right,
	float bottom,
	float top,
	float nearval,
	float farval)
{
	float x, y, a, b, c, d, e;

	x = (2.0F * nearval) / (right - left);
	y = (2.0F * nearval) / (top - bottom);
	a = (right + left) / (right - left);
	b = (top + bottom) / (top - bottom);
	c = -(farval + nearval) / (farval - nearval);
	d = -(2.0f * farval * nearval) / (farval - nearval);
	e = -1.0f;
	Matrix4x4 res = Matrix4x4();
	res.Get(0, 0) = x;    res.Get(0, 1) = 0.0;  res.Get(0, 2) = a;   res.Get(0, 3) = 0.0;
	res.Get(1, 0) = 0.0;  res.Get(1, 1) = y;    res.Get(1, 2) = b;   res.Get(1, 3) = 0.0;
	res.Get(2, 0) = 0.0;  res.Get(2, 1) = 0.0;  res.Get(2, 2) = c;   res.Get(2, 3) = d;
	res.Get(3, 0) = 0.0;  res.Get(3, 1) = 0.0;  res.Get(3, 2) = e;	res.Get(3, 3) = 0.0;
	return res;
}

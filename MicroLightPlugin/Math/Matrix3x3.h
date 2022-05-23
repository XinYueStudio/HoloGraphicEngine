#pragma once

#include "Vector3.h"
#include "Quaternion.h"
// Returns true if the distance between f0 and f1 is smaller than epsilon
inline bool CompareApproximately(float f0, float f1, float epsilon = 0.000001F)
{
	float dist = (f0 - f1);
	dist = Abs(dist);
	return dist < epsilon;
}
class  Matrix3x3
{
	public:

	float m_Data[9];
	

	Matrix3x3 () {}
	Matrix3x3 (float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22) { Get (0,0) = m00; Get (1,0) = m10; Get (2,0) = m20; Get (0,1) = m01; Get (1,1) =m11; Get (2,1) = m21; Get (0,2) = m02; Get (1,2) = m12; Get (2,2) = m22; }
	

	float& Get (int row, int column) 				{ return m_Data[row + (column * 3)]; }
	const float& Get (int row, int column)const 	{ return m_Data[row + (column * 3)]; }
	
	float& operator [] (int row) 				{ return m_Data[row]; }
	float operator [] (int row) const 				{ return m_Data[row]; }
	
	float* GetPtr ()								{ return m_Data; }
	const float* GetPtr () const				{ return m_Data; }
	
	Vector3 GetColumn (int col) const { return Vector3 (Get (0, col), Get (1, col), Get (2, col)); }
	Matrix3x3& operator = (const class Matrix4x4& m);

	Matrix3x3(const Matrix4x4 & other);
		
	Matrix3x3& operator *= (const Matrix3x3& inM);
	Matrix3x3& operator *= (const class Matrix4x4& inM);
	friend Matrix3x3 operator * (const Matrix3x3& lhs, const Matrix3x3& rhs)	{ Matrix3x3 temp (lhs); temp *= rhs; return temp; }
	Vector3 MultiplyVector3 (const Vector3& inV) const;
	void MultiplyVector3 (const Vector3& inV, Vector3& output) const;

	Vector3 MultiplyPoint3 (const Vector3& inV) const					{ return MultiplyVector3 (inV); }
	Vector3 MultiplyVector3Transpose (const Vector3& inV) const;
	Vector3 MultiplyPoint3Transpose (const Vector3& inV) const		{ return MultiplyVector3Transpose (inV); }

	Matrix3x3& operator *= (float f);
	Matrix3x3& operator /= (float f) { return *this *= (1.0F / f); }
	
	float GetDeterminant () const;
	
//	Matrix3x3& Transpose (const Matrix3x3& inM);
	Matrix3x3& Transpose ();
//	Matrix3x3& Invert (const Matrix3x3& inM)												{ return Transpose (inM); }
	bool Invert ();
	void InvertTranspose ();
	
	Matrix3x3& SetIdentity ();
	Matrix3x3& SetZero ();
	Matrix3x3& SetFromToRotation (const Vector3& from, const Vector3& to);
	Matrix3x3& SetAxisAngle (const Vector3& rotationAxis, float radians);
	Matrix3x3& SetOrthoNormalBasis (const Vector3& inX, const Vector3& inY, const Vector3& inZ);
	Matrix3x3& SetOrthoNormalBasisInverse (const Vector3& inX, const Vector3& inY, const Vector3& inZ);
	Matrix3x3& SetScale (const Vector3& inScale);
	Matrix3x3& Scale (const Vector3& inScale);
	
	bool IsIdentity (float threshold = 0.000001f);
	
	static const Matrix3x3 zero;
	static const Matrix3x3 identity;


	 
};

// Generates an orthornormal basis from a look at rotation, returns if it was successful
// (Righthanded)
bool LookRotationToMatrix (const Vector3& viewVec, const Vector3& upVec, Matrix3x3* m);

bool MatrixToEuler (const Matrix3x3& matrix, Vector3& v);
void EulerToMatrix (const Vector3& v, Matrix3x3& matrix);

inline Vector3 Matrix3x3::MultiplyVector3 (const Vector3& v) const
{
	Vector3 res;
	res.x = m_Data[0] * v.x + m_Data[3] * v.y + m_Data[6] * v.z;
	res.y = m_Data[1] * v.x + m_Data[4] * v.y + m_Data[7] * v.z;
	res.z = m_Data[2] * v.x + m_Data[5] * v.y + m_Data[8] * v.z;
	return res;
}

inline void Matrix3x3::MultiplyVector3 (const Vector3& v, Vector3& output) const
{
	output.x = m_Data[0] * v.x + m_Data[3] * v.y + m_Data[6] * v.z;
	output.y = m_Data[1] * v.x + m_Data[4] * v.y + m_Data[7] * v.z;
	output.z = m_Data[2] * v.x + m_Data[5] * v.y + m_Data[8] * v.z;
}


inline Vector3 Matrix3x3::MultiplyVector3Transpose (const Vector3& v) const
{
	Vector3 res;
	res.x = Get (0, 0) * v.x + Get (1, 0) * v.y + Get (2, 0) * v.z;
	res.y = Get (0, 1) * v.x + Get (1, 1) * v.y + Get (2, 1) * v.z;
	res.z = Get (0, 2) * v.x + Get (1, 2) * v.y + Get (2, 2) * v.z;
	return res;
}


inline void MatrixToQuaternion(const Matrix3x3& kRot, Quaternion& q)
{
	// Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
	// article "Quaternionf Calculus and Fast Animation".

	float fTrace = kRot.Get(0, 0) + kRot.Get(1, 1) + kRot.Get(2, 2);
	float fRoot;

	if (fTrace > 0.0f)
	{
		// |w| > 1/2, may as well choose w > 1/2
		fRoot = sqrt(fTrace + 1.0f);  // 2w
		q.w = 0.5f*fRoot;
		fRoot = 0.5f / fRoot;  // 1/(4w)
		q.x = (kRot.Get(2, 1) - kRot.Get(1, 2))*fRoot;
		q.y = (kRot.Get(0, 2) - kRot.Get(2, 0))*fRoot;
		q.z = (kRot.Get(1, 0) - kRot.Get(0, 1))*fRoot;
	}
	else
	{
		// |w| <= 1/2
		int s_iNext[3] = { 1, 2, 0 };
		int i = 0;
		if (kRot.Get(1, 1) > kRot.Get(0, 0))
			i = 1;
		if (kRot.Get(2, 2) > kRot.Get(i, i))
			i = 2;
		int j = s_iNext[i];
		int k = s_iNext[j];

		fRoot = sqrt(kRot.Get(i, i) - kRot.Get(j, j) - kRot.Get(k, k) + 1.0f);
		float* apkQuat[3] = { &q.x, &q.y, &q.z };

		*apkQuat[i] = 0.5f*fRoot;
		fRoot = 0.5f / fRoot;
		q.w = (kRot.Get(k, j) - kRot.Get(j, k)) * fRoot;
		*apkQuat[j] = (kRot.Get(j, i) + kRot.Get(i, j))*fRoot;
		*apkQuat[k] = (kRot.Get(k, i) + kRot.Get(i, k))*fRoot;
	}
	q = Normalize(q);
}






inline bool LookRotationToQuaternion(const Vector3& viewVec, const Vector3& upVec, Quaternion* res)
{
	Matrix3x3 m;
	if (!LookRotationToMatrix(viewVec, upVec, &m))
		return false;
	MatrixToQuaternion(m, *res);
	return true;
}
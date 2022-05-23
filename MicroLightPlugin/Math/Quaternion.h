#pragma once
#include <algorithm>
#include <stdio.h>
#include <math.h>
 
class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;
	Quaternion() : x(0.f), y(0.f), z(0.f) ,w(0.f) {}
	Quaternion(float inX, float inY, float inZ, float inW)
	{
		x = inX; y = inY; z = inZ; w = inW;
	}

	const float* GetPtr()const { return &x; }
	float* GetPtr() { return &x; }

	const float& operator [] (int i)const { return GetPtr()[i]; }
	float& operator [] (int i) { return GetPtr()[i]; }

	void Set(float inX, float inY, float inZ, float inW);
	void Set(const Quaternion& aQuat);
	void Set(const float* array) { x = array[0]; y = array[1]; z = array[2]; w = array[3]; }


	bool operator == (const Quaternion& q)const { return x == q.x && y == q.y && z == q.z && w == q.w; }
	bool operator != (const Quaternion& q)const { return x != q.x || y != q.y || z != q.z || w != q.w; }

	Quaternion& operator += (const Quaternion& inV)
	{
		x += inV.x;
		y += inV.y;
		z += inV.z;
		w += inV.w;

		return *this;
	}
	Quaternion& operator -= (const Quaternion& inV)
	{
		x -= inV.x;
		y -= inV.y;
		z -= inV.z;
		w -= inV.w;

		return *this;
	}


	Quaternion& operator *= (float s) { x *= s; y *= s; z *= s; w *= s; return *this; }
	Quaternion&	operator *= (const Quaternion& 	aQuat);
	Quaternion& operator /= (float s) { x /= s; y /= s; z /= s; w /= s; return *this; }

	Quaternion operator - () const
	{
		return Quaternion(-x, -y, -z, -w);
	}

	friend Quaternion Conjugate(const Quaternion& q);
	friend Quaternion Inverse(const Quaternion& q);
	
	friend Quaternion	operator * (const float s, const Quaternion& q)
	{
		Quaternion t(q);
		return t *= s;
	}

	inline friend Quaternion operator * (const Quaternion& lhs, const Quaternion& rhs)
	{
		return Quaternion(
			lhs.w*rhs.x + lhs.x*rhs.w + lhs.y*rhs.z - lhs.z*rhs.y,
			lhs.w*rhs.y + lhs.y*rhs.w + lhs.z*rhs.x - lhs.x*rhs.z,
			lhs.w*rhs.z + lhs.z*rhs.w + lhs.x*rhs.y - lhs.y*rhs.x,
			lhs.w*rhs.w - lhs.x*rhs.x - lhs.y*rhs.y - lhs.z*rhs.z);
	}

	static Quaternion identity() { return Quaternion(0.0F, 0.0F, 0.0F, 1.0F); }
};

inline void Quaternion::Set(float inX, float inY, float inZ, float inW)
{
	x = inX;
	y = inY;
	z = inZ;
	w = inW;
}

inline void Quaternion::Set(const Quaternion& aQuat)
{
	x = aQuat.x;
	y = aQuat.y;
	z = aQuat.z;
	w = aQuat.w;
}

inline Quaternion&	Quaternion::operator *= (const Quaternion& 	rhs)
{
	float tempx = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
	float tempy = w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z;
	float tempz = w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x;
	float tempw = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
	x = tempx; y = tempy; z = tempz; w = tempw;
	return *this;
}

 
inline Quaternion Conjugate(const Quaternion& q)
{
	return Quaternion(-q.x, -q.y, -q.z, q.w);
}

inline Quaternion Inverse(const Quaternion& q)
{
	// Is it necessary to divide by SqrMagnitude???
	Quaternion res = Conjugate(q);
	return res;
}
inline float Dot(const Quaternion& q1, const Quaternion& q2)
{
	return (q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w);
}
inline float SqrMagnitude(const Quaternion& q)
{
	return Dot(q, q);
}
inline float Magnitude(const Quaternion& q)
{
	return sqrt(SqrMagnitude(q));
}

 

#ifndef kPI
#define kPI 3.14159265358979323846264338327950288419716939937510F
#endif
#define kDeg2Rad (2.0F * kPI / 360.0F)
#define kRad2Deg (1.F / kDeg2Rad)

inline float Deg2RadF(float deg)
{
	// TODO : should be deg * kDeg2Rad, but can't be changed, 
	// because it changes the order of operations and that affects a replay in some RegressionTests
	return deg / 360.0F * 2.0F * kPI;
}

inline float Rad2DegF(float rad)
{
	// TODO : should be rad * kRad2Deg, but can't be changed, 
	// because it changes the order of operations and that affects a replay in some RegressionTests
	return rad / 2.0F / kPI * 360.0F;
}

inline float Lerp(float from, float to, float t)
{
	return to * t + from * (1.0F - t);
}

inline float Sign(float f)
{
#if defined(_XBOX)
	return __fsel(f, 1.0f, -1.0f);
#else
	if (f < 0.0F)
		return -1.0F;
	else
		return 1.0;
#endif
}
// Version of QuaternionToEuler that prevents "snapping" on X when getting
// close to gimbal lock.  Noticeably changes behavior compared to version
// above, so deactivated for now.

inline Vector3 QuaternionToEuler(const Quaternion& q)
{
	const float sqw = q.w * q.w;
	const float sqx = q.x * q.x;
	const float sqy = q.y * q.y;
	const float sqz = q.z * q.z;

	const float unit = sqx + sqy + sqz + sqw;
	const float test = q.x * q.y + q.z * q.w;

	float yaw = 0.0f;
	float pitch = 0.0f;
	float roll = 0.0f;

	// North pole singularity
	if (test > 0.499f * unit)
	{
		yaw = 2.0f * atan2(q.x, q.w);
		pitch = kPI * 0.5f;
		roll = 0.0f;
	}

	// South pole singularity
	else if (test < -0.499f * unit)
	{
		yaw = -2.0f * atan2(q.x, q.w);
		pitch = -kPI * 0.5f;
		roll = 0.0f;
	}

	else
	{
		yaw = atan2(2.0f * q.y * q.w - 2.0f * q.x * q.z, sqx - sqy - sqz + sqw);
		pitch = asin(2.0f * test / unit);
		roll = atan2(2.0f * q.x * q.w - 2.0f * q.y * q.z, -sqx + sqy - sqz + sqw);
	}

	// Keep angles [0..360].
	if (Sign(yaw) < 0.f)
		yaw = Deg2RadF(360.f) + yaw;
	if (Sign(pitch) < 0.f)
		pitch = Deg2RadF(360.f) + pitch;
	if (Sign(roll) < 0.f)
		roll = Deg2RadF(360.f) + roll;

	return Vector3(roll, yaw, pitch);
}

inline Quaternion EulerToQuaternion(const Vector3& someEulerAngles)
{
	float cX(cos(someEulerAngles.x / 2.0f));
	float sX(sin(someEulerAngles.x / 2.0f));

	float cY(cos(someEulerAngles.y / 2.0f));
	float sY(sin(someEulerAngles.y / 2.0f));

	float cZ(cos(someEulerAngles.z / 2.0f));
	float sZ(sin(someEulerAngles.z / 2.0f));

	Quaternion qX(sX, 0.0F, 0.0F, cX);
	Quaternion qY(0.0F, sY, 0.0F, cY);
	Quaternion qZ(0.0F, 0.0F, sZ, cZ);

	Quaternion q = (qY * qX) * qZ;
	
	return q;
}



inline Quaternion Normalize(const Quaternion& q) 
{
	float aScalar = Magnitude(q);
	Quaternion n = q;
	n.x /= aScalar;
	n.y /= aScalar;
	n.z /= aScalar;
	n.w /= aScalar;
	return n ;
}

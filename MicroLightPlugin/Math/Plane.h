#ifndef PLANE_H
#define PLANE_H

#include "Vector3.h"
 
 

 
enum{
	kPlaneFrustumLeft,
	kPlaneFrustumRight,
	kPlaneFrustumBottom,
	kPlaneFrustumTop,
	kPlaneFrustumNear,
	kPlaneFrustumFar,
	kPlaneFrustumNum,
};

class Plane
{
public:

	Vector3 normal=Vector3();
	float distance;


	const float& a ()const  			{ return normal.x; }
	const float& b ()const				{ return normal.y; }
	const float& c ()const				{ return normal.z; }

	const float& d () const { return distance; }
	float& d () { return distance; }

	const Vector3& GetNormal ()const{ return normal; }
		
	Plane ():normal(0,0,0){ }
	Plane (float a, float b, float c, float d) { normal.x = a; normal.y = b; normal.z = c; distance = d; }
	Plane(const Vector3& inNormal, const Vector3& inPoint)
	{
		 
		SetNormalAndPosition(inNormal, inPoint);
	}
	Plane(const Vector3& a, const Vector3& b, const Vector3& c)
	{

		Set3Points( a,  b,  c);
	}
	Plane& operator *= (float scale);
 
	
	void SetInvalid () { normal = Vector3(); distance = 0.0F; }


	void Set3Points (const Vector3& a, const Vector3& b, const Vector3& c);
	void Set3PointsUnnormalized (const Vector3& a, const Vector3& b, const Vector3& c);
	
	void SetNormalAndPosition (const Vector3& inNormal, const Vector3& inPoint);
	
	float GetDistanceToPoint (const Vector3& inPt) const;

	bool GetSide (const Vector3& inPt) const;
	bool SameSide (const Vector3& inPt0, const Vector3& inPt1);

	void NormalizeUnsafe ();

    Vector3 ClosestPointOnPlane(const Vector3& point);
};

 
inline float Plane::GetDistanceToPoint (const Vector3& inPt)const
{
	
	return Dot (normal, inPt) + distance;
}



// Returns true if we are on the front side (same as: GetDistanceToPoint () > 0.0)
inline bool Plane::GetSide (const Vector3& inPt) const
{
	return Dot (normal, inPt) + distance > 0.0F;
}


// Calculates the normal from 3 points unnormalized
inline Vector3 CalcRawNormalFromTriangle (const Vector3& a, const Vector3& b, const Vector3& c)
{
	Vector3 delta = b;
	delta.x -= a.x;
	delta.y -= a.y;
	delta.z -= a.z;

	Vector3 celta = c;
	celta.x -= a.x;
	celta.y -= a.y;
	celta.z -= a.z;

	return Cross (delta, celta);
}

 


inline void Plane::Set3Points (const Vector3& a, const Vector3& b, const Vector3& c)
{
	normal = CalcRawNormalFromTriangle (a, b, c);
	normal = Normalize (normal);
	distance = -Dot (normal, a);
	
}

inline void Plane::Set3PointsUnnormalized (const Vector3& a, const Vector3& b, const Vector3& c)
{
	normal = CalcRawNormalFromTriangle (a, b, c);
	distance = -Dot (normal, a);
}

inline void Plane::SetNormalAndPosition (const Vector3& inNormal, const Vector3& inPoint)
{
	normal = inNormal;

	distance = -Dot (inNormal, inPoint);
}

inline bool Plane::SameSide (const Vector3& inPt0, const Vector3& inPt1)
{
	float d0 = GetDistanceToPoint(inPt0);
	float d1 = GetDistanceToPoint(inPt1);
	if (d0 > 0.0f && d1 > 0.0f)
		return true;
	else if (d0 <= 0.0f && d1 <= 0.0f)
		return true;
	else
		return false;
}

inline Plane& Plane::operator *= (float scale)
{
 
	normal.x *= scale;
	normal.y *= scale;
	normal.z *= scale;

	distance *= scale;
	return *this;
}

inline void Plane::NormalizeUnsafe ()
{
	float invMag = 1.0f/ sqrt(Dot(normal, normal));
	normal.x *= invMag;
	normal.y *= invMag;
	normal.z *= invMag;

	distance *= invMag;
}

inline Vector3 Plane::ClosestPointOnPlane( const Vector3& point)
{
	float d = Dot(normal, point) + distance;
	return point - normal * d;
}
#endif

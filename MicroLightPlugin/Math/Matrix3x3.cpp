 
#include "Matrix3x3.h"
#include "Matrix4x4.h"
using namespace std;

namespace
{
	Matrix3x3 CreateIdentityMatrix3x3 ()
	{
		Matrix3x3 temp; 
		temp.SetIdentity (); 
		return temp;
	}

	Matrix3x3 CreateZeroMatrix3x3 ()
	{
		Matrix3x3 temp; 
		temp.SetZero (); 
		return temp;
	}
}

inline void MatrixToQuaternion(Matrix4x4& m, Quaternion& q) {
	Matrix3x3 mat(
		m.Get(0, 0), m.Get(0, 1), m.Get(0, 2),
		m.Get(1, 0), m.Get(1, 1), m.Get(1, 2),
		m.Get(2, 0), m.Get(2, 1), m.Get(2, 2));

	MatrixToQuaternion(mat, q);
	//	mat.Get(0,0) = m.Get(0,0); mat.Get(0,1) = m.Get(0,1); mat.Get(0,2) = m.Get(0,2);
	//	mat.Get(1,0) = m.Get(1,0); mat.Get(1,1) = m.Get(1,1); mat.Get(1,2) = m.Get(1,2);
	//	mat.Get(2,0) = m.Get(2,0); mat.Get(2,1) = m.Get(2,1); mat.Get(2,2) = m.Get(2,2);
}



const Matrix3x3 Matrix3x3::identity = CreateIdentityMatrix3x3 ();
const Matrix3x3 Matrix3x3::zero = CreateZeroMatrix3x3 ();

void GetRotMatrixNormVec (float* out, const float* inVec, float radians);

Matrix3x3& Matrix3x3::operator = (const Matrix4x4& other)
{
	m_Data[0] = other.m_Data[0];
	m_Data[1] = other.m_Data[1];
	m_Data[2] = other.m_Data[2];

	m_Data[3] = other.m_Data[4];
	m_Data[4] = other.m_Data[5];
	m_Data[5] = other.m_Data[6];

	m_Data[6] = other.m_Data[8];
	m_Data[7] = other.m_Data[9];
	m_Data[8] = other.m_Data[10];
	return *this;
}

Matrix3x3::Matrix3x3 (const Matrix4x4& other)
{
	m_Data[0] = other.m_Data[0];
	m_Data[1] = other.m_Data[1];
	m_Data[2] = other.m_Data[2];

	m_Data[3] = other.m_Data[4];
	m_Data[4] = other.m_Data[5];
	m_Data[5] = other.m_Data[6];

	m_Data[6] = other.m_Data[8];
	m_Data[7] = other.m_Data[9];
	m_Data[8] = other.m_Data[10];
}

Matrix3x3& Matrix3x3::SetIdentity ()
{
	Get (0, 0) = 1.0F;	Get (0, 1) = 0.0F;	Get (0, 2) = 0.0F;
	Get (1, 0) = 0.0F;	Get (1, 1) = 1.0F;	Get (1, 2) = 0.0F;
	Get (2, 0) = 0.0F;	Get (2, 1) = 0.0F;	Get (2, 2) = 1.0F;
	return *this;
}

Matrix3x3& Matrix3x3::SetZero ()
{
	Get (0, 0) = 0.0F;	Get (0, 1) = 0.0F;	Get (0, 2) = 0.0F;
	Get (1, 0) = 0.0F;	Get (1, 1) = 0.0F;	Get (1, 2) = 0.0F;
	Get (2, 0) = 0.0F;	Get (2, 1) = 0.0F;	Get (2, 2) = 0.0F;
	return *this;
}

Matrix3x3& Matrix3x3::SetOrthoNormalBasis (const Vector3& inX, const Vector3& inY, const Vector3& inZ)
{
	Get (0, 0) = inX[0];	Get (0, 1) = inY[0];	Get (0, 2) = inZ[0];
	Get (1, 0) = inX[1];	Get (1, 1) = inY[1];	Get (1, 2) = inZ[1];
	Get (2, 0) = inX[2];	Get (2, 1) = inY[2];	Get (2, 2) = inZ[2];
	return *this;
}

Matrix3x3& Matrix3x3::SetOrthoNormalBasisInverse (const Vector3& inX, const Vector3& inY, const Vector3& inZ)
{
	Get (0, 0) = inX[0];	Get (1, 0) = inY[0];	Get (2, 0) = inZ[0];
	Get (0, 1) = inX[1];	Get (1, 1) = inY[1];	Get (2, 1) = inZ[1];
	Get (0, 2) = inX[2];	Get (1, 2) = inY[2];	Get (2, 2) = inZ[2];
	return *this;
}

Matrix3x3& Matrix3x3::SetScale (const Vector3& inScale)
{
	Get (0, 0) = inScale[0];	Get (0, 1) = 0.0F;			Get (0, 2) = 0.0F;
	Get (1, 0) = 0.0F;			Get (1, 1) = inScale[1];	Get (1, 2) = 0.0F;
	Get (2, 0) = 0.0F;			Get (2, 1) = 0.0F;			Get (2, 2) = inScale[2];
	return *this;
}

bool Matrix3x3::IsIdentity (float threshold) {
	if (CompareApproximately (Get (0,0),1.0f, threshold) && CompareApproximately (Get (0,1),0.0f, threshold) && CompareApproximately (Get (0,2),0.0f, threshold) &&
	CompareApproximately (Get (1,0),0.0f, threshold) && CompareApproximately (Get (1,1),1.0f, threshold) && CompareApproximately (Get (1,2),0.0f, threshold) &&
	CompareApproximately (Get (2,0),0.0f, threshold) && CompareApproximately (Get (2,1),0.0f, threshold) && CompareApproximately (Get (2,2),1.0f, threshold))
		return true;
	return false;
}


Matrix3x3& Matrix3x3::Scale (const Vector3& inScale)
{
	Get (0, 0) *= inScale[0];
	Get (1, 0) *= inScale[0];
	Get (2, 0) *= inScale[0];

	Get (0, 1) *= inScale[1];
	Get (1, 1) *= inScale[1];
	Get (2, 1) *= inScale[1];

	Get (0, 2) *= inScale[2];
	Get (1, 2) *= inScale[2];
	Get (2, 2) *= inScale[2];
	return *this;
}

float Matrix3x3::GetDeterminant () const
{
	float fCofactor0 = Get (0, 0) * Get (1, 1) * Get (2, 2);
	float fCofactor1 = Get (0, 1) * Get (1, 2) * Get (2, 0);
	float fCofactor2 = Get (0, 2) * Get (1, 0) * Get (2, 1);

	float fCofactor3 = Get (0, 2) * Get (1, 1) * Get (2, 0);
	float fCofactor4 = Get (0, 1) * Get (1, 0) * Get (2, 2);
	float fCofactor5 = Get (0, 0) * Get (1, 2) * Get (2, 1);
	
	return fCofactor0 + fCofactor1 + fCofactor2 - fCofactor3 - fCofactor4 - fCofactor5;
}

Matrix3x3& Matrix3x3::Transpose ()
{
	swap (Get (0, 1), Get (1, 0));
	swap (Get (0, 2), Get (2, 0));
	swap (Get (2, 1), Get (1, 2));
	return *this;
}
/*
Matrix3x3& Matrix3x3::Transpose (const Matrix3x3& inMat)
{
	int i;
	for (i=0;i<3;i++)
	{
		Get (i, 0) = inMat.Get (0, i);
		Get (i, 1) = inMat.Get (1, i);
		Get (i, 2) = inMat.Get (2, i);
	}
	return *this;
}
*/

bool Matrix3x3::Invert ()
{
 
	////// THIS METHOD IS NUMERICALLY LESS ROBUST
	// Invert a 3x3 using cofactors.  This is faster than using a generic
	// Gaussian elimination because of the loop overhead of such a method.

	Matrix3x3 kInverse;

	kInverse.Get (0, 0) = Get (1, 1) * Get (2, 2) - Get (1, 2) * Get (2, 1);
	kInverse.Get (0, 1) = Get (0, 2) * Get (2, 1) - Get (0, 1) * Get (2, 2);
	kInverse.Get (0, 2) = Get (0, 1) * Get (1, 2) - Get (0, 2) * Get (1, 1);
	kInverse.Get (1, 0) = Get (1, 2) * Get (2, 0) - Get (1, 0) * Get (2, 2);
	kInverse.Get (1, 1) = Get (0, 0) * Get (2, 2) - Get (0, 2) * Get (2, 0);
	kInverse.Get (1, 2) = Get (0, 2) * Get (1, 0) - Get (0, 0) * Get (1, 2);
	kInverse.Get (2, 0) = Get (1, 0) * Get (2, 1) - Get (1, 1) * Get (2, 0);
	kInverse.Get (2, 1) = Get (0, 1) * Get (2, 0) - Get (0, 0) * Get (2, 1);
	kInverse.Get (2, 2) = Get (0, 0) * Get (1, 1) - Get (0, 1) * Get (1, 0);

	float fDet = Get (0, 0) * kInverse.Get (0, 0) + Get (0, 1) * kInverse.Get (1, 0) + Get (0, 2) * kInverse.Get (2, 0);

	if (Abs (fDet) >0.000001f)
	{
		kInverse /= fDet;
		*this = kInverse;
		return true;
	}
	else
	{
		SetZero ();
		return false;
	}
 
}

void Matrix3x3::InvertTranspose ()
{	
	Invert ();
	Transpose ();
}

Matrix3x3& Matrix3x3::operator *= (float f)
{
	for (int i=0;i<9;i++)
		m_Data[i] *= f;
	return *this;
}

Matrix3x3& Matrix3x3::operator *= (const Matrix3x3& inM)
{
	int i;
	for (i=0;i<3;i++)
	{
		float v[3] = {Get (i, 0), Get (i, 1), Get (i, 2)};
		Get (i, 0) = v[0] * inM.Get (0, 0) + v[1] * inM.Get (1, 0) + v[2] * inM.Get (2, 0);
		Get (i, 1) = v[0] * inM.Get (0, 1) + v[1] * inM.Get (1, 1) + v[2] * inM.Get (2, 1);
		Get (i, 2) = v[0] * inM.Get (0, 2) + v[1] * inM.Get (1, 2) + v[2] * inM.Get (2, 2);
	}
	return *this;
}

Matrix3x3& Matrix3x3::operator *= (const Matrix4x4& inM)
{
	int i;
	for (i=0;i<3;i++)
	{
		float v[3] = {Get (i, 0), Get (i, 1), Get (i, 2)};
		Get (i, 0) = v[0] * inM.Get (0, 0) + v[1] * inM.Get (1, 0) + v[2] * inM.Get (2, 0);
		Get (i, 1) = v[0] * inM.Get (0, 1) + v[1] * inM.Get (1, 1) + v[2] * inM.Get (2, 1);
		Get (i, 2) = v[0] * inM.Get (0, 2) + v[1] * inM.Get (1, 2) + v[2] * inM.Get (2, 2);
	}
	return *this;
}

Matrix3x3& Matrix3x3::SetAxisAngle (const Vector3& rotationAxis, float radians)
{
	GetRotMatrixNormVec (m_Data, rotationAxis.GetPtr (), radians);
	return *this;
}

void fromToRotation(const float from[3], const float to[3],float mtx[3][3]);

Matrix3x3& Matrix3x3::SetFromToRotation (const Vector3& from, const Vector3& to)
{
	float mtx[3][3];
	fromToRotation (from.GetPtr (), to.GetPtr (), mtx);
	Get (0, 0) = mtx[0][0];	Get (0, 1) = mtx[0][1];	Get (0, 2) = mtx[0][2];
	Get (1, 0) = mtx[1][0];	Get (1, 1) = mtx[1][1];	Get (1, 2) = mtx[1][2];
	Get (2, 0) = mtx[2][0];	Get (2, 1) = mtx[2][1];	Get (2, 2) = mtx[2][2];
	return *this;
}

inline void MakePositive (Vector3& euler)
{
	const float negativeFlip = -0.0001F;
	const float positiveFlip = (kPI * 2.0F) - 0.0001F;
	
	if (euler.x < negativeFlip)
		euler.x += 2.0 * kPI;
	else if (euler.x > positiveFlip)
		euler.x -= 2.0 * kPI;
    
	if (euler.y < negativeFlip)
		euler.y += 2.0 * kPI;
	else if (euler.y > positiveFlip)
		euler.y -= 2.0 * kPI;
    
	if (euler.z < negativeFlip)
		euler.z += 2.0 * kPI;
	else if (euler.z > positiveFlip)
		euler.z -= 2.0 * kPI;
}

inline void SanitizeEuler (Vector3& euler)
{
	MakePositive (euler);
    /*
     Vector3 option0 = euler;
     option0.x = kPI - option0.x;
     option0.y = kPI - option0.y;
     option0.z = kPI - option0.z;
     
     MakePositive (euler);
     MakePositive (option0);
     if (option0.x+option0.y+option0.z < euler.x+euler.y+euler.z)
     euler = option0;
     */
}

void EulerToMatrix (const Vector3& v, Matrix3x3& matrix)
{
	float cx = cos (v.x);
	float sx = sin (v.x);
	float cy = cos (v.y);
	float sy = sin (v.y);
	float cz = cos (v.z);
	float sz = sin (v.z);
	
	matrix.Get(0,0) = cy*cz + sx*sy*sz;
	matrix.Get(0,1) = cz*sx*sy - cy*sz;
	matrix.Get(0,2) = cx*sy;
    
	matrix.Get(1,0) = cx*sz;
	matrix.Get(1,1) = cx*cz;
	matrix.Get(1,2) = -sx;
    
	matrix.Get(2,0) = -cz*sy + cy*sx*sz;
	matrix.Get(2,1) = cy*cz*sx + sy*sz;
	matrix.Get(2,2) = cx*cy;
}

/// This is YXZ euler conversion
bool MatrixToEuler (const Matrix3x3& matrix, Vector3& v)
{
	// from http://www.geometrictools.com/Documentation/EulerAngles.pdf
	// YXZ order
	if ( matrix.Get(1,2) < 0.999F ) // some fudge for imprecision
	{
		if ( matrix.Get(1,2) > -0.999F ) // some fudge for imprecision
		{
			v.x = asin(-matrix.Get(1,2));
			v.y = atan2(matrix.Get(0,2), matrix.Get(2,2));
			v.z = atan2(matrix.Get(1,0), matrix.Get(1,1));
			SanitizeEuler (v);
            return true;
        }
        else
        {
            // WARNING.  Not unique.  YA - ZA = atan2(r01,r00)
            v.x = kPI * 0.5F;
            v.y = atan2(matrix.Get (0,1), matrix.Get(0,0));
            v.z = 0.0F;
			SanitizeEuler (v);
            
            return false;
        }
    }
    else
    {
        // WARNING.  Not unique.  YA + ZA = atan2(-r01,r00)
        v.x = -kPI * 0.5F;
        v.y = atan2(-matrix.Get(0,1),matrix.Get(0,0));
        v.z = 0.0F;
 		SanitizeEuler (v);
        return false;
    }
}


#define EPSILON 0.000001

#define CROSS(dest,v1,v2){                 \
          dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
          dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
          dest[2]=v1[0]*v2[1]-v1[1]*v2[0];}

#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])

#define SUB(dest,v1,v2){       \
          dest[0]=v1[0]-v2[0]; \
          dest[1]=v1[1]-v2[1]; \
          dest[2]=v1[2]-v2[2];}

/*
 * A function for creating a rotation matrix that rotates a vector called
 * "from" into another vector called "to".
 * Input : from[3], to[3] which both must be *normalized* non-zero vectors
 * Output: mtx[3][3] -- a 3x3 matrix in colum-major form
 * Author: Tomas M?ller, 1999
 */
void fromToRotation(const float* from, const float* to,float mtx[3][3])
{	
	float v[3];
	float e,h;
	CROSS(v,from,to);
	e=DOT(from,to);
	if(e>1.0-EPSILON)     /* "from" almost or equal to "to"-vector? */
	{
		/* return identity */
		mtx[0][0]=1.0; mtx[0][1]=0.0; mtx[0][2]=0.0;
		mtx[1][0]=0.0; mtx[1][1]=1.0; mtx[1][2]=0.0;
		mtx[2][0]=0.0; mtx[2][1]=0.0; mtx[2][2]=1.0;
	}
	else if(e<-1.0+EPSILON) /* "from" almost or equal to negated "to"? */
	{
		float up[3],left[3];
		float invlen;
		float fxx,fyy,fzz,fxy,fxz,fyz;
		float uxx,uyy,uzz,uxy,uxz,uyz;
		float lxx,lyy,lzz,lxy,lxz,lyz;
		/* left=CROSS(from, (1,0,0)) */
		left[0]=0.0; left[1]=from[2]; left[2]=-from[1];
		if(DOT(left,left)<EPSILON) /* was left=CROSS(from,(1,0,0)) a good choice? */
		{
			/* here we now that left = CROSS(from, (1,0,0)) will be a good choice */
			left[0]=-from[2]; left[1]=0.0; left[2]=from[0];
		}
		/* normalize "left" */
		invlen=1.0f/sqrt(DOT(left,left));
		left[0]*=invlen;
		left[1]*=invlen;
		left[2]*=invlen;
		CROSS(up,left,from);
		/* now we have a coordinate system, i.e., a basis;    */
		/* M=(from, up, left), and we want to rotate to:      */
		/* N=(-from, up, -left). This is done with the matrix:*/
		/* N*M^T where M^T is the transpose of M              */
		fxx=-from[0]*from[0]; fyy=-from[1]*from[1]; fzz=-from[2]*from[2];
		fxy=-from[0]*from[1]; fxz=-from[0]*from[2]; fyz=-from[1]*from[2];

		uxx=up[0]*up[0]; uyy=up[1]*up[1]; uzz=up[2]*up[2];
		uxy=up[0]*up[1]; uxz=up[0]*up[2]; uyz=up[1]*up[2];

		lxx=-left[0]*left[0]; lyy=-left[1]*left[1]; lzz=-left[2]*left[2];
		lxy=-left[0]*left[1]; lxz=-left[0]*left[2]; lyz=-left[1]*left[2];
		/* symmetric matrix */
		mtx[0][0]=fxx+uxx+lxx; mtx[0][1]=fxy+uxy+lxy; mtx[0][2]=fxz+uxz+lxz;
		mtx[1][0]=mtx[0][1];   mtx[1][1]=fyy+uyy+lyy; mtx[1][2]=fyz+uyz+lyz;
		mtx[2][0]=mtx[0][2];   mtx[2][1]=mtx[1][2];   mtx[2][2]=fzz+uzz+lzz;
	}
	else  /* the most common case, unless "from"="to", or "from"=-"to" */
	{
		/* ...otherwise use this hand optimized version (9 mults less) */
		float hvx,hvz,hvxy,hvxz,hvyz;
		h=(1.0f-e)/DOT(v,v);
		hvx=h*v[0];
		hvz=h*v[2];
		hvxy=hvx*v[1];
		hvxz=hvx*v[2];
		hvyz=hvz*v[1];
		mtx[0][0]=e+hvx*v[0]; mtx[0][1]=hvxy-v[2];     mtx[0][2]=hvxz+v[1];
		mtx[1][0]=hvxy+v[2];  mtx[1][1]=e+h*v[1]*v[1]; mtx[1][2]=hvyz-v[0];
		mtx[2][0]=hvxz-v[1];  mtx[2][1]=hvyz+v[0];     mtx[2][2]=e+hvz*v[2];
	}
}

// Right handed
bool LookRotationToMatrix (const Vector3& viewVec, const Vector3& upVec, Matrix3x3* m)
{
	Vector3 z = viewVec;
	// compute u0
	float mag = Magnitude (z);
	if (mag < 0.000001f)
	{
		m->SetIdentity();
		return false;
	}
	z /= mag;

	Vector3 x = Cross (upVec, z);
	mag = Magnitude (x);
	if (mag < 0.000001f)
	{
		m->SetIdentity();
		return false;
	}
	x /= mag;
	
	Vector3 y (Cross (z, x));
	if (!CompareApproximately (SqrMagnitude (y), 1.0F))
		return false;
	
	m->SetOrthoNormalBasis (x, y, z);
	return true;	
}
/*
//Left handed
bool LookRotationToMatrixLeftHanded (const Vector3& viewVec, const Vector3& upVec, Matrix3x3* m)
{
	Vector3 z = viewVec;
	// compute u0
	float mag = Magnitude (z);
	if (mag < Vector3::epsilon)
		return false;
	z /= mag;

	Vector3 x = Cross (z, upVec);
	mag = Magnitude (x);
	if (mag < Vector3::epsilon)
		return false;
	x /= mag;
	
	Vector3 y (Cross (x, z));
	if (!CompareApproximately (SqrMagnitude (y), 1.0F))
		return false;
	
	m->SetOrthoNormalBasis (x, y, z);
	return true;
}
*/

void GetRotMatrixNormVec (float* out, const float* inVec, float radians) 
{
  /* This function contributed by Erich Boleyn (erich@uruk.org) */
  /* This function used from the Mesa OpenGL code (matrix.c)  */
  float s, c;
  float vx, vy, vz, xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;
  
  s = sin (radians);
  c = cos (radians);
    
  vx = inVec[0];
  vy = inVec[1];
  vz = inVec[2];
  
#define M(row,col)  out[row*3 + col]
  /*
  *     Arbitrary axis rotation matrix.
  *
  *  This is composed of 5 matrices, Rz, Ry, T, Ry', Rz', multiplied
  *  like so:  Rz * Ry * T * Ry' * Rz'.  T is the final rotation
  *  (which is about the X-axis), and the two composite transforms
  *  Ry' * Rz' and Rz * Ry are (respectively) the rotations necessary
  *  from the arbitrary axis to the X-axis then back.  They are
  *  all elementary rotations.
  *
  *  Rz' is a rotation about the Z-axis, to bring the axis vector
  *  into the x-z plane.  Then Ry' is applied, rotating about the
  *  Y-axis to bring the axis vector parallel with the X-axis.  The
  *  rotation about the X-axis is then performed.  Ry and Rz are
  *  simply the respective inverse transforms to bring the arbitrary
  *  axis back to its original orientation.  The first transforms
  *  Rz' and Ry' are considered inverses, since the data from the
  *  arbitrary axis gives you info on how to get to it, not how
  *  to get away from it, and an inverse must be applied.
  *
  *  The basic calculation used is to recognize that the arbitrary
  *  axis vector (x, y, z), since it is of unit length, actually
  *  represents the sines and cosines of the angles to rotate the
  *  X-axis to the same orientation, with theta being the angle about
  *  Z and phi the angle about Y (in the order described above)
  *  as follows:
  *
  *  cos ( theta ) = x / sqrt ( 1 - z^2 )
  *  sin ( theta ) = y / sqrt ( 1 - z^2 )
  *
  *  cos ( phi ) = sqrt ( 1 - z^2 )
  *  sin ( phi ) = z
  *
  *  Note that cos ( phi ) can further be inserted to the above
  *  formulas:
  *
  *  cos ( theta ) = x / cos ( phi )
  *  sin ( theta ) = y / cos ( phi )
  *
  *  ...etc.  Because of those relations and the standard trigonometric
  *  relations, it is pssible to reduce the transforms down to what
  *  is used below.  It may be that any primary axis chosen will give the
  *  same results (modulo a sign convention) using thie method.
  *
  *  Particularly nice is to notice that all divisions that might
  *  have caused trouble when parallel to certain planes or
  *  axis go away with care paid to reducing the expressions.
  *  After checking, it does perform correctly under all cases, since
  *  in all the cases of division where the denominator would have
  *  been zero, the numerator would have been zero as well, giving
  *  the expected result.
  */
  
  xx = vx * vx;
  yy = vy * vy;
  zz = vz * vz;
  xy = vx * vy;
  yz = vy * vz;
  zx = vz * vx;
  xs = vx * s;
  ys = vy * s;
  zs = vz * s;
  one_c = 1.0F - c;
  
  M(0,0) = (one_c * xx) + c;
  M(1,0) = (one_c * xy) - zs;
  M(2,0) = (one_c * zx) + ys;
  
  M(0,1) = (one_c * xy) + zs;
  M(1,1) = (one_c * yy) + c;
  M(2,1) = (one_c * yz) - xs;
  
  M(0,2) = (one_c * zx) - ys;
  M(1,2) = (one_c * yz) + xs;
  M(2,2) = (one_c * zz) + c;
  
#undef M
}


 
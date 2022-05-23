#include "Matrix4x4.h"


void MultiplyMatrices4x4REF(const Matrix4x4*  lhs, const Matrix4x4*  rhs, Matrix4x4*  res)
{

	for (int i = 0; i<4; i++)
	{
		res->m_Data[i] = lhs->m_Data[i] * rhs->m_Data[0] + lhs->m_Data[i + 4] * rhs->m_Data[1] + lhs->m_Data[i + 8] * rhs->m_Data[2] + lhs->m_Data[i + 12] * rhs->m_Data[3];
		res->m_Data[i + 4] = lhs->m_Data[i] * rhs->m_Data[4] + lhs->m_Data[i + 4] * rhs->m_Data[5] + lhs->m_Data[i + 8] * rhs->m_Data[6] + lhs->m_Data[i + 12] * rhs->m_Data[7];
		res->m_Data[i + 8] = lhs->m_Data[i] * rhs->m_Data[8] + lhs->m_Data[i + 4] * rhs->m_Data[9] + lhs->m_Data[i + 8] * rhs->m_Data[10] + lhs->m_Data[i + 12] * rhs->m_Data[11];
		res->m_Data[i + 12] = lhs->m_Data[i] * rhs->m_Data[12] + lhs->m_Data[i + 4] * rhs->m_Data[13] + lhs->m_Data[i + 8] * rhs->m_Data[14] + lhs->m_Data[i + 12] * rhs->m_Data[15];
	}
}



Matrix4x4 & Matrix4x4::operator*=(const Matrix4x4 & inM)
{	 
	Matrix4x4 tmp;
	MultiplyMatrices4x4REF(this, &inM, &tmp);
	*this = tmp;
	return *this;
}



Matrix4x4 & Matrix4x4::SetPerspective(float fovy, float aspect, float zNear, float zFar)
{
	float cotangent, deltaZ;
	float radians = Deg2RadFun(fovy / 2.0f);
	cotangent = cos(radians) / sin(radians);
	deltaZ = zNear - zFar;

	Get(0, 0) = cotangent / aspect;	Get(0, 1) = 0.0F;      Get(0, 2) = 0.0F;                    Get(0, 3) = 0.0F;
	Get(1, 0) = 0.0F;               Get(1, 1) = cotangent; Get(1, 2) = 0.0F;                    Get(1, 3) = 0.0F;
	Get(2, 0) = 0.0F;               Get(2, 1) = 0.0F;      Get(2, 2) = (zFar + zNear) / deltaZ; Get(2, 3) = 2.0F * zNear * zFar / deltaZ;
	Get(3, 0) = 0.0F;               Get(3, 1) = 0.0F;      Get(3, 2) = -1.0F;                   Get(3, 3) = 0.0F;

	return *this;
}



 


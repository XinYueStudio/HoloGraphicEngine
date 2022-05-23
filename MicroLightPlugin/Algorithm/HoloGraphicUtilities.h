#pragma once
#if defined(_WINDOWS)
// Windows 头文件
#include <windows.h>
#include <algorithm>
#include "Shlwapi.h"
#endif
#include <assert.h>
#include <locale>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include<map>
using namespace std;

 
// System Headers
#include <vector>
#include <map>
#include "../Math/Vector3.h"
#include "../Math/Vector2.h"
#include "../Math/Vector4.h"
#include "../Math/Plane.h"
#include "../Math/Matrix3x3.h"
#include "../Math/Matrix4x4.h"

typedef struct _HoloGraphicFrustum
{

	Matrix4x4 ProjectionMatrix;
	Quaternion Rotation;
	bool GoodData;
}HoloGraphicFrustum;

class HoloGraphicUtilities
{
public:
	//https://edom18.medium.com/implementation-of-generalized-perspective-projection-on-the-unity-c9472a94f083
	//https://github.com/Oblong/generalized-perspective-projection
	//http://160592857366.free.fr/joe/ebooks/ShareData/Generalized%20Perspective%20Projection.pdf
	//static	void projection(const float *pa,
	//	const float *pb,
	//	const float *pc,
	//	const float *pe, float n, float f)
	//{
	//	float va[3], vb[3], vc[3];
	//	float vr[3], vu[3], vn[3];
	//	float l, r, b, t, d, M[16];
	//	// Compute an orthonormal basis for the screen.
	//	subtract(vr, pb, pa);
	//	subtract(vu, pc, pa);
	//	normalize(vr);
	//	normalize(vu);
	//	cross_product(vn, vr, vu);
	//	normalize(vn);
	//	// Compute the screen corner vectors.
	//	subtract(va, pa, pe);
	//	subtract(vb, pb, pe);
	//	subtract(vc, pc, pe);
	//	// Find the distance from the eye to screen plane.
	//	d = -dot_product(va, vn);
	//	// Find the extent of the perpendicular projection.
	//	l = dot_product(vr, va) * n / d;
	//	r = dot_product(vr, vb) * n / d;
	//	b = dot_product(vu, va) * n / d;
	//	t = dot_product(vu, vc) * n / d;
	//	// Load the perpendicular projection.
	//	glMatrixMode(GL_PROJECTION);
	//	glLoadIdentity();
	//	glFrustum(l, r, b, t, n, f);
	//	// Rotate the projection to be non-perpendicular.
	//	memset(M, 0, 16 * sizeof(float));
	//	M[0] = vr[0]; M[4] = vr[1]; M[8] = vr[2];
	//	M[1] = vu[0]; M[5] = vu[1]; M[9] = vu[2];
	//	M[2] = vn[0]; M[6] = vn[1]; M[10] = vn[2];
	//	M[15] = 1.0f;
	//	glMultMatrixf(M);
	//	// Move the apex of the frustum to the origin.
	//	glTranslatef(-pe[0], -pe[1], -pe[2]);
	//	glMatrixMode(GL_MODELVIEW);
	//}

	static HoloGraphicFrustum  GetCalculateFrustumMatrix(float nearClipPlane, float farClipPlane, Vector3 Corner0, Vector3 Corner1, Vector3 Corner2, Vector3 Corner3, Vector3 pe)
	{
		float n = nearClipPlane;
		float f = farClipPlane;

		Vector3 pa = Corner0;
		Vector3 pb = Corner3;
		Vector3 pc = Corner1;

		// Compute an orthonormal basis for the screen. 计算屏幕的正交基。
		Vector3 vr = (pb - pa).normalize();
		Vector3 vu = (pc - pa).normalize();
		Vector3 vn = Cross(vu, vr).normalize();

		// Compute the screen corner vectors. 计算屏幕角向量。
		Vector3 va = pa - pe;
		Vector3 vb = pb - pe;
		Vector3 vc = pc - pe;

		// Find the distance from the eye to screen plane.找出眼睛到屏幕平面的距离。
		float d = -Dot(va, vn);

		//跑到反面去了
		if (d < 0)
		{

			pa = Corner3;
			pb = Corner0;
			pc = Corner2;

			// Compute an orthonormal basis for the screen. 计算屏幕的正交基。
			vr = (pb - pa).normalize();
			vu = (pc - pa).normalize();
			vn = Cross(vu, vr).normalize();

			// Compute the screen corner vectors. 计算屏幕角向量。
			va = pa - pe;
			vb = pb - pe;
			vc = pc - pe;

			// Find the distance from the eye to screen plane.找出眼睛到屏幕平面的距离。
			d = -Dot(va, vn);
		}

		// Find the extent of the perpendicular projection. 找出垂直投影的范围
		float nd = n / d * 1.0f;
		float l = Dot(vr, va) * nd;
		float r = Dot(vr, vb) * nd;
		float b = Dot(vu, va) * nd;
		float t = Dot(vu, vc) * nd;

		// Load the perpendicular projection. 加载垂直投影。
		Matrix4x4 P = SetFrustum(l, r, b, t, n, f);
		HoloGraphicFrustum mFrustum = HoloGraphicFrustum();
		mFrustum.ProjectionMatrix = P;

		Quaternion  q;
		mFrustum.GoodData = LookRotationToQuaternion(-vn, vu, &q);
		mFrustum.Rotation = q;

		Plane mPlane(Corner0, Corner1, Corner2);
		Vector3 pec = mPlane.ClosestPointOnPlane(pe);
		if (pec == pe)
		{
			mFrustum.GoodData = false;
		}
 
		return mFrustum;
	}

};
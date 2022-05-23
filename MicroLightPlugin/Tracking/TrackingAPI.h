#pragma once
#include "../Math/Vector3.h"
#include "../Math/Quaternion.h"
#include "MicroLightLibrary.h"
class TrackingAPI
{
public:

	virtual ~TrackingAPI() { }
	virtual	bool Init() = 0;
	virtual	bool Reset() = 0;	
	virtual	bool Shutdown() = 0;
	virtual	int GetActiveDeviceCount() = 0;

	virtual	int GetActiveDeviceId(int index) = 0;
	virtual	bool IsActive(Controller controller) = 0;
	virtual	bool ReCenter(Controller controller) = 0;
	virtual	Vector3  GetPosition(Controller controller) = 0;
	virtual	Quaternion  GetRotation(Controller controller) = 0;
 
	virtual	bool GetButtonDown(Controller controller, int key) = 0;
	virtual	bool GetButtonPressed(Controller controller, int key) = 0;
	virtual	bool GetButtonUp(Controller controller, int key) = 0;
	virtual	float GetButtonAxis1D(Controller controller, int key) = 0;
	virtual  Vector3 GetButtonAxis2D(Controller controller, int key) = 0;

	virtual Vector3 GetPositionOffSet(Controller controller) = 0;;
	virtual	Vector3  GetEulerAnglesOffSet(Controller controller) = 0;;
	virtual bool SetPositionOffSet(Vector3 vector) = 0;;
	virtual	bool  SetEulerAnglesOffSet(Vector3 vector) = 0;;

};

TrackingAPI* CreateTrackingAPI(const char* file);
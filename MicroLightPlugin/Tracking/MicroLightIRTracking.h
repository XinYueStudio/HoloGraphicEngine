#pragma once
#include "../Tracking/TrackingAPI.h"
#include "MicroLightLibrary.h"

class MicroLightIRTracking :public TrackingAPI
{
public:
	MicroLightIRTracking(const char* file);
	~MicroLightIRTracking() {};

	virtual	bool Init();
	virtual	bool Shutdown();

	virtual	bool Reset();
	virtual	int GetActiveDeviceCount();
	virtual	int GetActiveDeviceId(int index);
	virtual	bool IsActive(Controller controller) ;
	virtual	bool ReCenter(Controller controller);
	virtual	Vector3  GetPosition(Controller controller);
	virtual	Quaternion  GetRotation(Controller controller);

	virtual	bool GetButtonDown(Controller controller, int key);
	virtual	bool GetButtonPressed(Controller controller, int key);
	virtual	bool GetButtonUp(Controller controller, int key);
	virtual	float GetButtonAxis1D(Controller controller, int key);
	virtual  Vector3 GetButtonAxis2D(Controller controller, int key);
 
	virtual Vector3 GetPositionOffSet(Controller controller);
	virtual	Vector3  GetEulerAnglesOffSet(Controller controller);
	virtual bool SetPositionOffSet(Vector3 vector);
	virtual	bool  SetEulerAnglesOffSet(Vector3 vector);


private:
	MicroLightLibrary* mLibrary = NULL;

	Vector3 HmdPositionOffSet;
	Vector3 TouchpadPositionOffSet;
	Vector3 RemotePositionOffSet;

	Vector3 HmdEulerOffSet;
	Vector3 TouchpadEulerOffSet;
	Vector3 RemoteEulerOffSet;
};
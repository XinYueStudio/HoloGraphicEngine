#pragma once
#include "../../Engine/Source/Core/PluginInterface.h"
#include "../Tracking/TrackingAPI.h"
#include "../../Engine/Dependencies/glm/glm.hpp"
#include "../../Engine/Dependencies/glm/gtc/quaternion.hpp"
#include "../Tracking/MicroLightLibrary.h"
using namespace HoloGraphicEngine;

class MicroLightPluginForHoloGraphicEngine:public PluginInterface
{
public:
	//  Functions
	virtual void Start(const char* file) ;
	virtual	bool Reset();
	virtual	int GetActiveDeviceCount() ;
	virtual	int GetActiveDeviceId(int index);
	virtual	bool IsActive(int controller) ;
	virtual	bool ReCenter(int controller) ;
	virtual	glm::vec3  GetPosition(int controller) ;
	virtual	glm::quat  GetRotation(int controller) ;

	virtual	bool GetButtonDown(int controller, int key) ;
	virtual	bool GetButtonPressed(int controller, int key) ;
	virtual	bool GetButtonUp(int controller, int key) ;
	virtual	float GetButtonAxis1D(int controller, int key);
	virtual  glm::vec3 GetButtonAxis2D(int controller, int key);

	virtual glm::vec3 GetPositionOffSet(int controller) ;
	virtual	glm::vec3  GetEulerAnglesOffSet(int controller) ;
	virtual bool SetPositionOffSet(glm::vec3 vector);
	virtual	bool  SetEulerAnglesOffSet(glm::vec3 vector) ;
	virtual void Destroy() ;

private:
	TrackingAPI* mTrackingAPI;
};

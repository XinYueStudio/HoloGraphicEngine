#pragma once

// External Headers
#include "glm.hpp"
namespace HoloGraphicEngine {

	 
	class PluginInterface
	{
	public:

		// Pure Virtual Destructor
		virtual ~PluginInterface() = 0;

		//  Functions 
		virtual void Start(const char* file) = 0;
		virtual	bool Reset() = 0;
		virtual	int GetActiveDeviceCount() = 0;
		virtual	int GetActiveDeviceId(int index) = 0;
		virtual	bool IsActive(int controller) = 0;
		virtual	bool ReCenter(int controller) = 0;
		virtual	glm::vec3  GetPosition(int controller) = 0;
		virtual	glm::quat  GetRotation(int controller) = 0;

		virtual	bool GetButtonDown(int controller, int key) = 0;
		virtual	bool GetButtonPressed(int controller, int key) = 0;
		virtual	bool GetButtonUp(int controller, int key) = 0;
		virtual	float GetButtonAxis1D(int controller, int key) = 0;
		virtual  glm::vec3 GetButtonAxis2D(int controller, int key) = 0;

		virtual glm::vec3 GetPositionOffSet(int controller) = 0;
		virtual	glm::vec3  GetEulerAnglesOffSet(int controller) = 0;
		virtual bool SetPositionOffSet(glm::vec3 vector) = 0;
		virtual	bool  SetEulerAnglesOffSet(glm::vec3 vector) = 0;
		virtual void Destroy() = 0;
		 
	};

	// Implementation of Pure Virtual Destructor
	inline PluginInterface::~PluginInterface() {}
}
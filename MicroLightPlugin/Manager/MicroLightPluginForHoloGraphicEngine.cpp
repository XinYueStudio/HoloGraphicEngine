#include "MicroLightPluginForHoloGraphicEngine.h"

void MicroLightPluginForHoloGraphicEngine::Start(const char* file)
{
	if (mTrackingAPI == NULL)
		mTrackingAPI = CreateTrackingAPI(file);

	if (mTrackingAPI)
	{
		mTrackingAPI->Init();
	}
}

bool MicroLightPluginForHoloGraphicEngine::Reset()
{
	if (mTrackingAPI)
	{
		bool value = mTrackingAPI->Reset();
		return value;
	}
	else
		return false;
}

int MicroLightPluginForHoloGraphicEngine::GetActiveDeviceCount()
{
	return 1;
}

int MicroLightPluginForHoloGraphicEngine::GetActiveDeviceId(int index)
{
	return 0;
}

bool MicroLightPluginForHoloGraphicEngine::IsActive(int controller)
{
	if (mTrackingAPI)
	{
		bool value = mTrackingAPI->IsActive((Controller)controller);
		return value;
	}
	else
	return false;
}

bool MicroLightPluginForHoloGraphicEngine::ReCenter(int controller)
{
	if (mTrackingAPI)
	{
		bool value = mTrackingAPI->Reset();
		return value;
	}
	else
	return false;
}

glm::vec3 MicroLightPluginForHoloGraphicEngine::GetPosition(int controller)
{
	if (mTrackingAPI)
	{
		Vector3 value = mTrackingAPI->GetPosition((Controller)controller);
		return glm::vec3(value.x, value.y, value.z);
	}
	else
	return glm::vec3();
}

glm::quat MicroLightPluginForHoloGraphicEngine::GetRotation(int controller)
{
	if (mTrackingAPI)
	{
		Quaternion value = mTrackingAPI->GetRotation((Controller)controller);
		return glm::quat( value.w,value.x, value.y, value.z);
	}
	else
	return glm::quat();
}

bool MicroLightPluginForHoloGraphicEngine::GetButtonDown(int controller, int key)
{
	if (mTrackingAPI)
	{
		bool value = mTrackingAPI->GetButtonDown((Controller)controller, key);
		return value;
	}
	else
	return false;
}

bool MicroLightPluginForHoloGraphicEngine::GetButtonPressed(int controller, int key)
{
	if (mTrackingAPI)
	{
		bool value = mTrackingAPI->GetButtonPressed((Controller)controller, key);
		return value;
	}
	else
	return false;
}

bool MicroLightPluginForHoloGraphicEngine::GetButtonUp(int controller, int key)
{
	if (mTrackingAPI)
	{
		bool value = mTrackingAPI->GetButtonUp((Controller)controller, key);
		return value;
	}
	else
	return false;
}

float MicroLightPluginForHoloGraphicEngine::GetButtonAxis1D(int controller, int key)
{
	if (mTrackingAPI)
	{
		float value = mTrackingAPI->GetButtonAxis1D((Controller)controller, key);
		return value;
	}
	else
	return 0.0f;
}

glm::vec3 MicroLightPluginForHoloGraphicEngine::GetButtonAxis2D(int controller, int key)
{
	if (mTrackingAPI)
	{
	  Vector3 value=	mTrackingAPI->GetButtonAxis2D((Controller)controller, key);
	  return glm::vec3(value.x, value.y, value.z);
	}
	else
	return glm::vec3();
}


//Custom to Save And Read

glm::vec3 MicroLightPluginForHoloGraphicEngine::GetPositionOffSet(int controller)
{
	return glm::vec3();
}

glm::vec3 MicroLightPluginForHoloGraphicEngine::GetEulerAnglesOffSet(int controller)
{
	return glm::vec3();
}




bool MicroLightPluginForHoloGraphicEngine::SetPositionOffSet(glm::vec3 vector)
{
	return false;
}

bool MicroLightPluginForHoloGraphicEngine::SetEulerAnglesOffSet(glm::vec3 vector)
{
	return false;
}

 

void MicroLightPluginForHoloGraphicEngine::Destroy()
{
	if (mTrackingAPI)
	{
		mTrackingAPI->Shutdown();
	}
}

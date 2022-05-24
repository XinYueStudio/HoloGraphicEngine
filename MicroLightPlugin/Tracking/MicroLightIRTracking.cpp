#include "MicroLightIRTracking.h"

MicroLightIRTracking::MicroLightIRTracking(const char* file)
{
	if (mLibrary == NULL)
	{
		mLibrary = new MicroLightLibrary(file);
		if (mLibrary)
		{
			HmdPositionOffSet= GetPositionOffSet( Controller::Hmd);
			TouchpadPositionOffSet = GetPositionOffSet(Controller::Touchpad1);
			RemotePositionOffSet = GetPositionOffSet(Controller::Remote1);

			HmdEulerOffSet= GetEulerAnglesOffSet(Controller::Hmd);
			TouchpadEulerOffSet = GetEulerAnglesOffSet(Controller::Touchpad1);
			RemoteEulerOffSet = GetEulerAnglesOffSet(Controller::Remote1);
		}
	}
}

bool MicroLightIRTracking::Init()
{
	if (mLibrary)
	{
		return mLibrary->Initialization();
	}
	else
	{
		return false;
	}
	 
}



bool MicroLightIRTracking::Shutdown()
{
	if (mLibrary)
	{
		return mLibrary->ShutDown();
	}
	else
	{
		return false;
	}
}

bool MicroLightIRTracking::Reset()
{
	if (mLibrary)
	{
		return mLibrary->Reset(Controller::All);
	}
	else
	{
		return false;
	}
}

int MicroLightIRTracking::GetActiveDeviceCount()
{
	if (mLibrary)
	{
		return mLibrary->GetActiveCount();
	}
	else
	{
		return 1;
	}
}

int MicroLightIRTracking::GetActiveDeviceId(int index)
{
	return index;
}

bool MicroLightIRTracking::IsActive(Controller controller)
{
	return true;
}

bool MicroLightIRTracking::ReCenter(Controller controller)
{
	return true;
}

Vector3 MicroLightIRTracking::GetPosition(Controller controller)
{
	if (mLibrary)
	{
		float x = 0, y = 0, z = 0;
		 
		 
		mLibrary->GetPosition(controller,&x,&y,&z);
		
	 
		switch (controller)
		{
		case Controller::Hmd:
		{
			return Vector3(-x, -y, -z) + HmdPositionOffSet;
		}
		break;
		case Controller::Touchpad1:
		case Controller::Touchpad2:
		{
			return Vector3(-x, -y, -z) + TouchpadPositionOffSet;
		}

		break;
		case Controller::Remote1:
		case Controller::Remote2:
		{
			return Vector3(-x, -y, -z) + RemotePositionOffSet;
		}
		break;

		default:
			return Vector3();
			break;
		}
	}
	else
	{
		return Vector3();
	}

}

Quaternion MicroLightIRTracking::GetRotation(Controller controller)
{
	if (mLibrary)
	{
		float x=0, y = 0, z = 0;
		float qx = 0, qy = 0, qz = 0,qw = 0;
	 
		mLibrary->GetControllerMatrix(controller, &x, &y, &z, &qw, &qy, &qz,&qz);
		return Quaternion(qx, qy, qz,qw);
	}
	else
	{
		return Quaternion();
	}
}

bool MicroLightIRTracking::GetButtonDown(Controller controller, int key)
{
	if (mLibrary)
	{
	 
		return mLibrary->GetButtonDown(controller,(Button)key);
	}
	else
	{
		return false;
	}
}

bool MicroLightIRTracking::GetButtonPressed(Controller controller, int key)
{
	if (mLibrary)
	{
	 
		return mLibrary->GetButtonPressed(controller, (Button)key);
	}
	else
	{
		return false;
	}
}

bool MicroLightIRTracking::GetButtonUp(Controller controller, int key)
{
	if (mLibrary)
	{
	 
		 
		return mLibrary->GetButtonUp(controller, (Button)key);
	}
	else
	{
		return false;
	}
}

float MicroLightIRTracking::GetButtonAxis1D(Controller controller, int key)
{
	if (mLibrary)
	{
	
		return mLibrary->GetButtonAxis1D((Axis1D)key);
	}
	else
	{
		return 0.0f;
	}
	
}

Vector3 MicroLightIRTracking::GetButtonAxis2D(Controller controller, int key)
{
	if (mLibrary)
	{
		float x = 0, y = 0, z = 0;
		mLibrary->GetButtonAxis2D((Axis2D)key,&x,&y);
		return Vector3(x, y, z);
	}
	else
	{
		return Vector3();
	}
	
}

Vector3 MicroLightIRTracking::GetPositionOffSet(Controller controller)
{
	Vector3 OffSet = Vector3();
 
 
	return OffSet;

}


Vector3 MicroLightIRTracking::GetEulerAnglesOffSet(Controller controller)
{
	Vector3 OffSet = Vector3();
	 
	return OffSet;


}

bool MicroLightIRTracking::SetPositionOffSet(Vector3 vector)
{
	return false;
}

bool MicroLightIRTracking::SetEulerAnglesOffSet(Vector3 vector)
{
	return false;
}

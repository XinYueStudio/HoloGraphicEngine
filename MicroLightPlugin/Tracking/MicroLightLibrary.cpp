

#include "MicroLightLibrary.h"
 

MicroLightLibrary::MicroLightLibrary(const char* file)
{
 	 
	 hMod = LoadLibrary(file);
	if (hMod)
	{
		GPA_Initialization = (FUN0)GetProcAddress(hMod, "Initialization");
		GPA_InitializationWithOption = (FUN1)GetProcAddress(hMod, "InitializationWithOption");
		GPA_ShutDown = (FUN2)GetProcAddress(hMod, "ShutDown");
		GPA_GetActiveCount = (FUN3)GetProcAddress(hMod, "GetActiveCount");
		GPA_GetActiveControllers = (FUN4)GetProcAddress(hMod, "GetActiveControllers");
		GPA_ActiveController = (FUN5)GetProcAddress(hMod, "ActiveController");
		GPA_Reset = (FUN6)GetProcAddress(hMod, "Reset");;
		GPA_SetOriginPosition = (FUN7)GetProcAddress(hMod, "SetOriginPosition");
		GPA_SetOriginEulerAngles = (FUN8)GetProcAddress(hMod, "SetOriginEulerAngles");
		GPA_SetEnable = (FUN9)GetProcAddress(hMod, "SetEnable");
		GPA_SetDisEnable = (FUNA)GetProcAddress(hMod, "SetDisEnable");
		GPA_GetOriginPosition = (FUNB)GetProcAddress(hMod, "GetOriginPosition");
		GPA_GetOriginEulerAngles = (FUNC)GetProcAddress(hMod, "GetOriginEulerAngles");
		GPA_GetPosition = (FUND)GetProcAddress(hMod, "GetPosition");
		GPA_GetEulerAngles = (FUNE)GetProcAddress(hMod, "GetEulerAngles");
		GPA_GetControllerMatrix = (FUNF)GetProcAddress(hMod, "GetControllerMatrix");
		GPA_GetButtonDown = (FUNG)GetProcAddress(hMod, "GetButtonDown");
		GPA_GetButtonPressed = (FUNH)GetProcAddress(hMod, "GetButtonPressed");
		GPA_GetButtonUp = (FUNI)GetProcAddress(hMod, "GetButtonUp");
		GPA_GetButtonAxis1D = (FUNJ)GetProcAddress(hMod, "GetButtonAxis1D");
		GPA_GetButtonAxis2D = (FUNK)GetProcAddress(hMod, "GetButtonAxis2D");
		GPA_GetCtlComboButtonState = (FUNL)GetProcAddress(hMod, "GetCtlComboButtonState");
		//GPA_Clear = (FUNM)GetProcAddress(hMod, "Clear");;
		//GPA_WriteSample = (FUNN)GetProcAddress(hMod, "WriteSample");
	}
	else
	{
		cout << "ERROR on LoadLibrary" << endl;
	}

}


MicroLightLibrary::~MicroLightLibrary()
{
	if (hMod)
	{

		FreeLibrary(hMod);
	
		hMod = NULL;
		GPA_Initialization = NULL;
		GPA_InitializationWithOption = NULL;
		GPA_ShutDown = NULL;
		GPA_GetActiveCount = NULL;
		GPA_GetActiveControllers = NULL;
		GPA_ActiveController = NULL;
		GPA_Reset = NULL;
		GPA_SetOriginPosition = NULL;
		GPA_SetOriginEulerAngles = NULL;
		GPA_SetEnable = NULL;
		GPA_SetDisEnable = NULL;
		GPA_GetOriginPosition = NULL;
		GPA_GetOriginEulerAngles = NULL;
		GPA_GetPosition = NULL;
		GPA_GetEulerAngles = NULL;
		GPA_GetControllerMatrix = NULL;
		GPA_GetButtonDown = NULL;
		GPA_GetButtonPressed = NULL;
		GPA_GetButtonUp = NULL;
		GPA_GetButtonAxis1D = NULL;
		GPA_GetButtonAxis2D = NULL;
		GPA_GetCtlComboButtonState = NULL;
		//GPA_Clear = NULL;
		//GPA_WriteSample = NULL;
	}
}

bool MicroLightLibrary::Initialization()
{
	if (hMod)
	{
		if (GPA_Initialization)
		{
			return	GPA_Initialization();
		}

	}
	return false;
}

bool MicroLightLibrary::InitializationWithOption(CameraList whichCAM, LEDList whichLED, CtlLEDList whichCTL)
{
	if (hMod)
	{
		if (GPA_InitializationWithOption)
		{
			return	GPA_InitializationWithOption(whichCAM, whichLED, whichCTL);
		}
	}
	return false;
}

bool MicroLightLibrary::ShutDown()
{
	if (hMod)
	{

		if (GPA_ShutDown)
		{
			return GPA_ShutDown();
		}

	}
	return false;
}

int MicroLightLibrary::GetActiveCount()
{
	if (hMod)
	{
		if (GPA_GetActiveCount)
		{
			return	GPA_GetActiveCount();
		}

	}
	return 0;
}

bool MicroLightLibrary::GetActiveControllers(int * controllers)
{
	if (hMod)
	{
		if (GPA_GetActiveControllers)
		{
			return	GPA_GetActiveControllers(controllers);
		}

	}
	return false;
}

bool MicroLightLibrary::ActiveController(Controller controller)
{
	if (hMod)
	{
		if (GPA_ActiveController)
		{
			return	GPA_ActiveController(controller);
		}

	}
	return false;
}

bool MicroLightLibrary::Reset(Controller controller)
{
	if (hMod)
	{
		if (GPA_Reset)
		{
			return GPA_Reset(controller);
		}


	}
	return false;
}

bool MicroLightLibrary::SetOriginPosition(Controller controller, float x, float y, float z)
{
	if (hMod)
	{
		if (GPA_SetOriginPosition)
		{
			return GPA_SetOriginPosition(controller, x, y, z);
	}


	}
	return false;
}

bool MicroLightLibrary::SetOriginEulerAngles(Controller controller, float x, float y, float z)
{
	if (hMod)
	{
		if (GPA_SetOriginEulerAngles)
		{
			return	GPA_SetOriginEulerAngles(controller, x, y, z);
	   }


	}
	return false;
}

bool MicroLightLibrary::SetEnable(Controller controller)
{
	if (hMod)
	{
		if (GPA_SetEnable)
		{
			GPA_SetEnable(controller);
	}


	}
	return false;
}

bool MicroLightLibrary::SetDisEnable(Controller controller)
{
	if (hMod)
	{
		if (GPA_SetDisEnable)
		{
			return	GPA_SetDisEnable(controller);
		}

	}
	return false;
}

bool MicroLightLibrary::GetOriginPosition(Controller controller, float * x, float * y, float * z)
{
	if (hMod)
	{
		if (GPA_GetOriginPosition)
		{
			return GPA_GetOriginPosition(controller, x, y, z);
	}


	}
	return false;
}

bool MicroLightLibrary::GetOriginEulerAngles(Controller controller, float * x, float * y, float * z)
{
	if (hMod)
	{
		if (GPA_GetOriginEulerAngles)
		{
			return	GPA_GetOriginEulerAngles(controller, x, y, z);
		}

	}
	return false;
}

bool MicroLightLibrary::GetPosition(Controller controller, float* x, float* y, float* z)
{
	if (hMod)
	{
		if (GPA_GetPosition)
		{
			return	GPA_GetPosition(controller, x, y, z);
    	}


	}
	return false;
}

bool MicroLightLibrary::GetEulerAngles(Controller controller, float * x, float * y, float * z)
{
	if (hMod)
	{
		if (GPA_GetEulerAngles)
		{
		   return	GPA_GetEulerAngles(controller, x, y,z);
		}


	}
	return false;
}

void MicroLightLibrary::GetControllerMatrix(Controller controller, float * x, float * y, float * z, float * qw, float * qx, float * qy, float * qz)
{
	if (hMod)
	{
		if (GPA_GetControllerMatrix)
			GPA_GetControllerMatrix(controller,x,y,z,qw,qy,qz,qz);


	}
}

bool MicroLightLibrary::GetButtonDown(Controller controller, Button button)
{
	if (hMod)
	{
		if (GPA_GetButtonDown)
		{
			return	GPA_GetButtonDown(controller, button);
		 
	}


	}
	return false;
}

bool MicroLightLibrary::GetButtonPressed(Controller controller, Button button)
{
	if (hMod)
	{
		if (GPA_GetButtonPressed)
		{
			return	GPA_GetButtonPressed(controller, button);
		 
	}


	}
	return false;
}

bool MicroLightLibrary::GetButtonUp(Controller controller, Button button)
{
	if (hMod)
	{
		if (GPA_GetButtonUp)
		{
			return GPA_GetButtonUp(controller, button);
			 
		}
	}
	return false;
}

float MicroLightLibrary::GetButtonAxis1D(Axis1D axis1D)
{
	if (hMod)
	{
		if (GPA_GetButtonAxis1D)
		{
			return	GPA_GetButtonAxis1D(axis1D);
		 
	}

	}
	return 0.0f;
}

bool MicroLightLibrary::GetButtonAxis2D(Axis2D axis2D, float * x, float * y)
{
	if (hMod)
	{
		if (GPA_GetButtonAxis2D)
		{
			return GPA_GetButtonAxis2D(axis2D,x,y);
		 
	}


	}
	return false;
}

bool MicroLightLibrary::GetCtlComboButtonState(Controller controller, int * keycode)
{
	if (hMod)
	{
		if (GPA_GetCtlComboButtonState)
		{
			return	GPA_GetCtlComboButtonState(controller, keycode);
		 
	}


	}
	return false;
}

//bool MicroLightLibrary::Clear(HapticsChannel channel)
//{
//	if (hMod)
//	{
//		if (GPA_Clear)
//		{
//			return	GPA_Clear(channel);
//
//		}
//
//	}
//	return false;
//}
//
//bool MicroLightLibrary::WriteSample(HapticsChannel channel, byte sample)
//{
//	if (hMod)
//	{
//		if (GPA_WriteSample)
//		{
//			return GPA_WriteSample(channel, sample);
//		
//			 
//		}
//
//	}
//	return false;
//}

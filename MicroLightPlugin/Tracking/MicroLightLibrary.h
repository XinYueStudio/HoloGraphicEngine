#pragma once
#include <windows.h>
#include <iostream>
using namespace std;
enum class  Controller:int
{
	None,
	Hmd,
	Touchpad1,
	Touchpad2,
	Remote1,
	Remote2,

	All = ~None
};
enum class  Button :int
{
	None = 0,
	Back = 1, //K1
	Menu = 2,//k2
	IndexTriggerUp = 3,//k3
	IndexTriggerDown = 4,//k3
	ThumbstickUp = 5,//StickUp
	ThumbstickDown = 6,//StickDown
	ThumbstickLeft = 7,//StickLeft
	ThumbstickRight = 8,//StickRight

	Any = ~None
};

enum class Axis1D :int
{
	None = 0,
	LIndexTrigger,
	RIndexTrigger,
	Any = ~None
};
enum class Axis2D :int
{
	None = 0,
	RThumbstick,
	LThumbstick,
	Any = ~None
};

enum class CameraList :int //动捕相机选择
{
	CAM3_120,   //3号相机120度广角
	CAM4_120,   //4号相机120度广角
	CAM_HS      //高速相机
};
enum class LEDList :int //LED板选择
{
	LED_GLASS,  //眼镜
	LED_DEMO2,  //2#板
	LED_DEMO4,  //4#板
	LED_5MM     //5mmLED板
};

enum class CtlLEDList :int //控制器LED板选择
{
	CTL_JS1,    //1#手柄(JOYSTICK 1)
	CTL_JS2,    //2#手柄
	CTL_PEN1,   //1#笔
	CTL_PEN2    //2#笔
};
enum class HapticsChannel :int
{
	LeftChannel,
	RightChannel
};

typedef bool (*FUN0)();
typedef bool(*FUN1)(CameraList , LEDList , CtlLEDList );
typedef bool(*FUN2)();
typedef int(*FUN3)();
typedef bool(*FUN4)(int*);
typedef bool(*FUN5)(Controller );
typedef bool(*FUN6)(Controller );
typedef bool(*FUN7)(Controller , float , float , float );
typedef bool(*FUN8)(Controller, float, float , float);
typedef bool(*FUN9)(Controller );
typedef bool(*FUNA)(Controller );
typedef bool(*FUNB)(Controller, float*, float*, float*);
typedef bool(*FUNC)(Controller, float*, float*, float*);
typedef bool(*FUND)(Controller, float*, float*, float*);
typedef bool(*FUNE)(Controller, float*, float*, float*);
typedef  void(*FUNF)(Controller, float*, float*, float*, float*, float*, float*, float*);
typedef bool(*FUNG)(Controller, Button);
typedef bool(*FUNH)(Controller, Button);
typedef bool(*FUNI)(Controller, Button);
typedef  float(*FUNJ)(Axis1D);
typedef bool(*FUNK)(Axis2D, float*, float*);
typedef bool(*FUNL)(Controller , int*);
typedef bool(*FUNM)(HapticsChannel);
typedef bool(*FUNN)(HapticsChannel , byte);



class MicroLightLibrary
{
public:
	MicroLightLibrary(const char* file);
	~MicroLightLibrary();

	bool Initialization();
	bool InitializationWithOption(CameraList whichCAM, LEDList whichLED, CtlLEDList whichCTL);
    bool ShutDown();
	int GetActiveCount();
	bool GetActiveControllers(int* controllers);
	bool ActiveController(Controller controller);
	bool Reset(Controller controller);
	bool SetOriginPosition(Controller controller, float x, float y, float z);
	bool SetOriginEulerAngles(Controller controller, float x, float y, float z);
	bool SetEnable(Controller controller);
	bool SetDisEnable(Controller controller);
	bool GetOriginPosition(Controller controller,  float* x,  float* y,  float* z);
	bool GetOriginEulerAngles(Controller controller,  float* x,  float* y,  float* z);
	bool GetPosition(Controller controller,  float* x,  float* y,  float* z);
	bool GetEulerAngles(Controller controller,  float* x,  float* y,  float* z);
	void GetControllerMatrix(Controller controller,  float* x, float* y, float* z, float* qw, float* qx, float* qy, float* qz);
	bool GetButtonDown(Controller controller, Button button);
	bool GetButtonPressed(Controller controller, Button button);
	bool GetButtonUp(Controller controller, Button button);
	float GetButtonAxis1D(Axis1D axis1D);
	bool GetButtonAxis2D(Axis2D axis2D, float*  x, float*  y);
	bool GetCtlComboButtonState(Controller controller, int*  keycode);
	bool Clear(HapticsChannel channel);
	bool WriteSample(HapticsChannel channel, byte sample);


	HMODULE hMod = NULL;

private:
 

	FUN0  GPA_Initialization = NULL;
	FUN1 GPA_InitializationWithOption = NULL;
	FUN2 GPA_ShutDown = NULL;
	FUN3 GPA_GetActiveCount = NULL;
	FUN4 GPA_GetActiveControllers = NULL;
	FUN5 GPA_ActiveController = NULL;
	FUN6 GPA_Reset = NULL;
	FUN7 GPA_SetOriginPosition = NULL;
	FUN8 GPA_SetOriginEulerAngles = NULL;
	FUN9 GPA_SetEnable = NULL;
	FUNA GPA_SetDisEnable = NULL;
	FUNB GPA_GetOriginPosition = NULL;
	FUNC GPA_GetOriginEulerAngles = NULL;
	FUND GPA_GetPosition = NULL;
	FUNE GPA_GetEulerAngles = NULL;
	FUNF GPA_GetControllerMatrix = NULL;
	FUNG	GPA_GetButtonDown = NULL;
	FUNH	GPA_GetButtonPressed = NULL;
	FUNI GPA_GetButtonUp = NULL;
	FUNJ GPA_GetButtonAxis1D = NULL;
	FUNK GPA_GetButtonAxis2D = NULL;
	FUNL GPA_GetCtlComboButtonState = NULL;
	FUNM GPA_Clear = NULL;
	FUNN GPA_WriteSample = NULL;
};




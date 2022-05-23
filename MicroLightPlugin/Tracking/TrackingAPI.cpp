#include "TrackingAPI.h"
#include "MicroLightIRTracking.h"

TrackingAPI* CreateTrackingAPI(const char* file)
{

		return	new MicroLightIRTracking(file);

}

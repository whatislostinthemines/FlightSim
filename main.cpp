#include <irrlicht.h>
#include <driverChoice.h>
#include "FlightEventReceiver.h"

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;

int main()
{
	E_DRIVER_TYPE driverType = driverChoiceConsole();
	if (driverType == EDT_COUNT) return 1;
	IrrlichtDevice* device = createDevice(driverType, dimension2d<u32>(960, 540), 16, false, true, false, 0);
	Controller controller(device);
	controller.mainLoop();
	device->drop();
	return 0;

}
#include "BaseHeader.h"
#include "Controller.h"

int main()
{

	E_DRIVER_TYPE driverType = EDT_DIRECT3D9; 
	if (driverType == EDT_COUNT) return 1;
	IrrlichtDevice* device = createDevice(driverType, dimension2d<u32>(960, 540), 16, false, true, false, 0);
	Controller controller(device);
	controller.mainLoop();
	device->drop();
	return 0;

}
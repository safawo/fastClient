#include "UsbDetect.hpp"
#include <libusb/lusb0_usb.h>

// Device vendor and product id.
#define DEV_VID 0x18D1
#define DEV_PID 0x4E22


// Device of bytes to transfer.
#define BUF_SIZE 64


UsbDetect::UsbDetect()
{
	freopen("test.log", "w", stdout);
}

UsbDetect::~UsbDetect()
{

}

usb_dev_handle* UsbDetect::open_dev()
{

	std::cout << "Enter open_dev()" << std::endl;
	struct usb_bus *bus;
	struct usb_device *dev;

	for (bus = usb_get_busses(); bus; bus = bus->next)
	{   
		for (dev = bus->devices; dev; dev = dev->next)
		{
			if (dev->descriptor.idVendor == DEV_VID &&
				dev->descriptor.idProduct == DEV_PID )
			{
				std::cout << "Find the device:" << " DEV_VID= " <<  dev->descriptor.idVendor
					      << " and DEV_PID= " <<  dev->descriptor.idProduct << std::endl;

				return usb_open(dev);
			}
		}
	}

	return NULL;
}

bool UsbDetect::IsDeviceConnUsb()
{

	usb_dev_handle * dev = NULL;

	/* initialize the library */
	usb_init();
	/* find all buses */
	usb_find_busses();
	/* find all connected devices */
	usb_find_devices(); 

	if (! (dev = open_dev()) )
	{
		std::cout <<"Error opening device: "<< usb_strerror() << std::endl;
		return false;
	}
	else
	{
		m_dev = dev;
		std::cout <<"Success opening device: DEV_VID = "<< DEV_VID
			      << " and DEV_PID = " << DEV_PID << std::endl;
	}
	return true;
}



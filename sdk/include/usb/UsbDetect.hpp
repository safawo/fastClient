#ifndef Think_Usb_UsbDetect
#define Think_Usb_UsbDetect

#include <stdio.h>
#include <usb/UsbDll.hpp>
#include <iostream>
#include <fstream>

class usb_dev_handle;

class Usb_API UsbDetect
{
public:

	UsbDetect();

	~UsbDetect();


public:
	bool IsDeviceConnUsb();

	usb_dev_handle * open_dev();



private:
	usb_dev_handle* m_dev;


};


#endif
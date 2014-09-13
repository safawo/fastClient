#ifndef Think_Usb_UsbDll
#define Think_Usb_UsbDll
 
#ifdef Usb_Lib 
#define Usb_API __declspec(dllexport)
#else
#define Usb_API __declspec(dllimport)
#endif

#endif

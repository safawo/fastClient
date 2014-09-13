#ifndef Think_Safety_SafetyDll
#define Think_Safety_SafetyDll

#include <QtCore/qglobal.h>

#ifdef Safety_Lib 
#define Safety_API Q_DECL_EXPORT
#else
#define Safety_API Q_DECL_IMPORT
#endif

#endif  

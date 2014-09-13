#ifndef Think_FastUI_FastUIDLL
#define Think_FastUI_FastUIDLL

#include <QtCore/qglobal.h>

#ifdef FastUI_Lib 
#define FastUI_API Q_DECL_EXPORT
#else
#define FastUI_API Q_DECL_IMPORT
#endif

#endif  

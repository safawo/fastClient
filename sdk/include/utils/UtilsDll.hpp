#ifndef Think_Utils_UtilsDll
#define Think_Utils_UtilsDll

#include <QtCore/qglobal.h>

#ifdef Utils_Lib 
    #define Utils_API Q_DECL_EXPORT
#else
    #define Utils_API Q_DECL_IMPORT
#endif

#endif  
 
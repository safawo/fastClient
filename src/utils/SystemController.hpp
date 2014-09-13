#ifndef Think_Utils_SystemController
#define Think_Utils_SystemController

#include <utils/UtilsDll.hpp>  

#include <QTextCodec>
#include <QVariant>

#include <QDateTime>

#include <QString>
#include <QStringList>
#include <QByteArray>

class Utils_API SystemController
{
public:   
    virtual QString getId() = 0;
    virtual QString getName() = 0;

    virtual void start() = 0;
    virtual void stop() = 0; 
    virtual void reload() = 0;
 
    virtual ~SystemController(){};
};
 
#endif


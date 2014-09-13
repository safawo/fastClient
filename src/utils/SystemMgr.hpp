#ifndef Think_Utils_SystemMgr
#define Think_Utils_SystemMgr

#include <utils/UtilsDll.hpp>  
#include <utils/SystemController.hpp>  
 
#include <QTextCodec>
#include <QVariant>

#include <QDateTime>

#include <QString>
#include <QStringList>
#include <QByteArray>

class Utils_API SystemMgr
{
public:   
    virtual QString exeName() = 0;
    virtual QString exeFullName() = 0; 
    virtual QString exePath() = 0;

    virtual bool isRun() = 0;
    virtual bool isDebug() = 0;

    virtual QString getIni() = 0;

    virtual QString getProductInfo() = 0;
    virtual QString getProductInfoEx() = 0;

    virtual QString getVersion() = 0;
    virtual QString getVersionEx() = 0;

    virtual QString getNodeIp() = 0;
    virtual QString getNodelName() = 0;

    virtual QString getPeerIp() = 0;
    virtual QString getPeerPort() = 0;

    virtual QString getRootPath() = 0;
    virtual QString getTempPath() = 0;
    virtual QString getLogPath() = 0;
    virtual QString getToolPath() = 0;
	virtual QString getDownloadPath() = 0;
    virtual QString getCachePath() = 0;
    
    virtual void buildEnv(QString const& exeName) = 0;
    virtual void logout() = 0;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void relaod() = 0;

    virtual void regController(SystemController* sysController) = 0;
    virtual void unRegController(QString const& controllerId) = 0;

    virtual ~SystemMgr(){};
};

Utils_API SystemMgr& sys(); 

#endif


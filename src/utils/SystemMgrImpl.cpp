#include <utils/SystemMgr.hpp>
#include <utils/Common.hpp>

#include <QtCore/QDebug>

#include <QtCore/QTextCodec>
#include <QtCore/QDateTime>
#include <QtCore/QFileInfo>
#include <QtCore/QFile>

#include <QtCore/QDir>

#include <QtCore/QSettings>
#include <QtCore/QMutex> 

#include <QtNetwork/QHostInfo>

#define FAST_CLIENT_INI    "fastHotelCard.ini"
 
#define LOGIN_SERVER_IP    "Login Server/IP"
#define LOGIN_SERVER_PORT  "Login Server/Port"

class SystemMgrImpl: public SystemMgr
{
public:     
    virtual QString getIni()  
    {
        if (QFile::exists(FAST_CLIENT_INI))
        {
            return FAST_CLIENT_INI;
        }

        QString debugRunIni = QString("../") + FAST_CLIENT_INI;
        if (QFile::exists(debugRunIni))
        {
            return debugRunIni;
        }

        return NULL_STR;

    }

    virtual QString exeName() {
        return this->_exeName;
    }

    virtual QString exeFullName() { 
        return this->_exeFullName;
    }

    virtual QString exePath() {
        return this->_exePath;
    }

    virtual bool isRun() {
        return this->_isRun;
    }

    virtual bool isDebug() { 
        if (!QFile::exists(FAST_CLIENT_INI))
        {
            return true;
        }

        return false;
    }
     
    virtual QString getProductInfo() {
        QString productInfo = NULL_STR;
        productInfo = "SafeKingCard";
        return productInfo;
    }

    virtual QString getProductInfoEx() {
        QString productInfo = NULL_STR;
        productInfo = "SafeKingCard V5.0.0";
        return productInfo;
    }

    virtual QString getVersion() {
        QString versionInfo = NULL_STR;
        versionInfo = "V5.0.0";
        return versionInfo;
    }

    virtual QString getVersionEx() {
        QString versionInfo = NULL_STR;
        versionInfo = "SafeKingCard V5.0.0";
        return versionInfo;
    }

    virtual QString getNodeIp() { 
        QString localHostName = QHostInfo::localHostName();  
        QString localHostIp = "127.0.0.1";

        QList<QHostAddress> addresses = QHostInfo::fromName(localHostName).addresses();
        for (int index = 0; index < addresses.size(); index++)
        {
            QHostAddress& address = addresses[index];  
            if (address.protocol() != QAbstractSocket::IPv4Protocol) { 
                continue; 
            }

            if (address.toString() == localHostIp) { 
                continue;
            }

            localHostIp = address.toString();
            break;
        }  

        return localHostIp;
    }

    virtual QString getNodelName() {
        QString localHostName = QHostInfo::localHostName(); 
        return localHostName; 
    }

    virtual QString getPeerIp() { 
        QSettings settings(getIni(), QSettings::IniFormat);

        QString loginIp = NULL_STR;  
        if (!settings.contains(LOGIN_SERVER_IP))
        {
            return loginIp;
        } 
        loginIp = settings.value(LOGIN_SERVER_IP).toString().trimmed();

        return loginIp;
    }

    virtual QString getPeerPort() { 
        QSettings settings(getIni(), QSettings::IniFormat); 

        QString loginPort = NULL_STR;

        if (!settings.contains(LOGIN_SERVER_PORT)) { 
            return loginPort;
        }   
        loginPort = settings.value(LOGIN_SERVER_PORT).toString().trimmed(); 

        return loginPort;
    }
     
    virtual QString getRootPath() {
        QString clientRootPath = QDir::currentPath();
        if (!isDebug()) { 
            return clientRootPath;
        }
   
        clientRootPath = clientRootPath.replace("\\", "/");
        clientRootPath = clientRootPath.replace("//", "/");
        clientRootPath = clientRootPath.replace("//", "/");
        
        int repIndex = clientRootPath.lastIndexOf("/client/");
        clientRootPath = clientRootPath.remove(repIndex, (clientRootPath.length() - repIndex));
        clientRootPath.append("/build/deploy/client");
         
        return clientRootPath;
    }

    virtual QString getTempPath() {
        QString clientTemp = getRootPath() + "/temp";
        return clientTemp;
    }

    virtual QString getLogPath() {
        QString clientLog = getRootPath() + "/log";
        return clientLog;
    }
      
    virtual QString getToolPath() {
        QString clientLog = getRootPath() + "/tools";
        return clientLog;
    }

	virtual QString getDownloadPath() {
		QString clientLog = getRootPath() + "/download";
		return clientLog;
	}

    virtual QString getCachePath() {
        QString clientLog = getRootPath() + "/cache";
        return clientLog;
    }

	
    virtual ~SystemMgrImpl() {   

    }

    virtual void buildEnv(QString const& exeName) {
        QString exeObjStr = exeName;
        exeObjStr = exeObjStr.replace("\\", "/");
        exeObjStr = exeObjStr.replace("//", "/");
        exeObjStr = exeObjStr.replace("//", "/");

        int repIndex = exeObjStr.lastIndexOf("/");

        this->_exeFullName = exeObjStr;
        this->_exePath = exeObjStr.mid(0,repIndex);
        this->_exeName = exeObjStr.mid(repIndex + 1);

    }
 
    virtual void logout() {
        this->_isRun = false;
    }

    virtual void start(){

    }

    virtual void stop(){

    }

    virtual void relaod(){

    }

    virtual void regController(SystemController* sysController){

    }

    virtual void unRegController(QString const& controllerId){

    }

    static SystemMgr* getInstance() {
        if (_instance == NULL) {
            _instance = new SystemMgrImpl();
        }

        return _instance;
    }

private:
    SystemMgrImpl() {
        this->_exeName = "";
        this->_exeFullName = ""; 
        this->_exePath = "";

        _isRun = true;
    }
     
private:
    static SystemMgr* _instance;

private:
    QString _exeName;
    QString _exeFullName;
    QString _exePath;

    bool _isRun;
};

SystemMgr* SystemMgrImpl::_instance = NULL;

Utils_API SystemMgr& sys() 
{
    return *(SystemMgrImpl::getInstance());
}
  

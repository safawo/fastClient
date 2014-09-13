#ifndef Think_Safety_SafeSessionDAO
#define Think_Safety_SafeSessionDAO

#include <QtCore/QString>  
#include <QtCore/QList> 
#include <QtCore/QStringList>

#include <utils/Common.hpp> 

#include <safety/SafetyDll.hpp>

#include <safety/SafeSessionInfo.hpp>
#include <safety/SafeUserInfo.hpp>

class Safety_API SafeSessionDAO
{
public:
    virtual void reLoad() = 0;
    
    virtual bool login(QString const& userName, QString const& password, QString const& reqIp = NULL_QSTR, QString const& reqPort = NULL_QSTR) = 0;
    virtual bool logout() = 0;
    virtual bool shankHand() = 0;
    virtual bool awakeLogin(QString const& password) = 0;
    virtual bool forceOffline() = 0;

    virtual QString getCacheLoginUserName() = 0;
    virtual void saveCacheLoginUserName(QString const& loginUserName) = 0;

    virtual QString getCacheLoginReqHost() = 0;
    virtual void saveCacheLoginReqHost(QString const& loginReqHost) = 0;

    virtual SafeSessionInfo::SESSION_STATUS getSessionStatus() = 0;

public:
    virtual QString getUserName() = 0;
    virtual QString getPassword() = 0;
    virtual QString getReqIp() = 0;
    virtual QString getReqPort() = 0; 
    virtual QString getReqHostName() = 0;
     
    virtual QString getLocalIp() = 0;
    virtual QString getLocalHostName() = 0;

    virtual ~SafeSessionDAO(){}; 

};

Safety_API SafeSessionDAO&  safeSessionDAO();

#endif





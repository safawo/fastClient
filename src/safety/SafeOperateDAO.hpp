#ifndef Think_Safety_SafeOperateDAO
#define Think_Safety_SafeOperateDAO

#include <QtCore/QString>  
#include <QtCore/QList> 
#include <QtCore/QStringList>  

#include <utils/Common.hpp> 

#include <safety/SafetyDll.hpp>

#include <safety/SafeOperateInfo.hpp>
#include <safety/SafeOperateAuthInfo.hpp>

class Safety_API SafeOperateDAO
{
public:
    virtual void reLoad() = 0;

    virtual bool authOperate(QList<SafeOperateAuthInfo> const& auths, QList<SafeOperateAuthInfo> const& unAuths) = 0;  
    virtual bool queryAuth(QList<SafeOperateAuthInfo>& auths) = 0;

    virtual QList<SafeOperateInfo> queryOperates(QString const& subSysName = NULL_STR, QString const& operateGroup = NULL_STR) = 0;
    virtual QStringList queryOperateNames(QString const& subSysName = NULL_STR, QString const& operateGroup = NULL_STR) = 0;
      
    virtual ~SafeOperateDAO(){}; 

};

Safety_API SafeOperateDAO&  safeOperateDAO();

#endif





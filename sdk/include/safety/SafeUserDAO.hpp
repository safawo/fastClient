#ifndef Think_Safety_SafeUserDAO
#define Think_Safety_SafeUserDAO

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QStringList>

#include <utils/Common.hpp>

#include <safety/SafetyDll.hpp>

#include <safety/SafeUserInfo.hpp>

class Safety_API SafeUserDAO
{
public:
    virtual void reLoad() = 0;

    virtual SafeUserInfo queryUser(QString const& userId) = 0; 
    virtual SafeUserInfo queryByEmployeeId(QString const& employeeId) = 0; 

    virtual QList<SafeUserInfo> queryUsers() = 0;
    virtual QList<SafeUserInfo> queryByDepartId(QString const& departId) = 0;
     
    virtual QStringList queryUserNames() = 0;

    virtual bool createUser(SafeUserInfo const& user) = 0;  
    virtual bool delUser(QString const& userId) = 0;  
    virtual bool changeUser(SafeUserInfo const& user) = 0;  

    virtual bool modPassword(QString const& userId, QString const& newPassword) = 0;
    virtual bool lockUser(QString const& userId, QString const& lockReason) = 0;  
    virtual bool unlockUser(QString const& userId) = 0;
    virtual bool offlineUser(QString const& userId) = 0;

    virtual ~SafeUserDAO(){};

};

Safety_API SafeUserDAO&  safeUserDAO();

#endif





#ifndef Think_Safety_SafeRoleDAO
#define Think_Safety_SafeRoleDAO

#include <QtCore/QString>  
#include <QtCore/QList> 
#include <QtCore/QStringList> 

#include <utils/Common.hpp> 

#include <safety/SafetyDll.hpp>

#include <safety/SafeRoleInfo.hpp> 
#include <safety/SafeRoleAllocInfo.hpp> 

class Safety_API SafeRoleDAO
{
public:
    virtual void reLoad() = 0;

    virtual SafeRoleInfo queryRole(QString const& roleId) = 0;
    virtual SafeRoleInfo queryRoleByName(QString const& roleName) = 0;

    virtual QList<SafeRoleInfo> queryRoles() = 0; 

    virtual bool createRole(SafeRoleInfo const& role) = 0;  
    virtual bool delRole(QString const& roleId) = 0;  
    virtual bool changeRole(SafeRoleInfo const& role) = 0;  

    virtual bool allocRole(QList<SafeRoleAllocInfo> const& allocs, QList<SafeRoleAllocInfo> const& unAllocs) = 0;
    virtual bool queryAlloc(QList<SafeRoleAllocInfo>& allocs) = 0;

    virtual SafeRoleInfo getRoleById(QString const& roleId) = 0;
    virtual SafeRoleInfo getRoleByName(QString const& roleName) = 0;

    virtual ~SafeRoleDAO(){}; 

};

Safety_API SafeRoleDAO&  safeRoleDAO();

#endif





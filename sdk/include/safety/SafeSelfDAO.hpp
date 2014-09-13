#ifndef Think_Safety_SafeSelfDAO
#define Think_Safety_SafeSelfDAO

#include <QtCore/QString>  
#include <QtCore/QList> 
#include <QtCore/QStringList> 

#include <utils/Common.hpp> 

#include <safety/SafetyDll.hpp>

#include <safety/SafeUserInfo.hpp>

class Safety_API SafeSelfDAO
{
public:
    virtual void reLoad() = 0;
    
    virtual SafeUserInfo queryMyInfo() = 0;

    virtual bool modPassword(QString const& currentPassword, QString const& newPassword) = 0;
    virtual bool modUserInfo(SafeUserInfo const& selfInfo) = 0;

    virtual ~SafeSelfDAO(){}; 

};

Safety_API SafeSelfDAO&  safeSelfDAO();

#endif




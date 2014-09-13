#ifndef Think_Safety_SafeSubSysDAO
#define Think_Safety_SafeSubSysDAO

#include <QtCore/QString>  
#include <QtCore/QList>  

#include <utils/Common.hpp>

#include <safety/SafetyDll.hpp> 
#include <safety/SafeSubSysInfo.hpp>

class Safety_API SafeSubSysDAO
{
public:
    virtual void reLoad() = 0;

    virtual QList<SafeSubSysInfo> querySubSyss() = 0;
    virtual QStringList querySubSysNames() = 0;

    virtual SafeSubSysInfo querySubSysById(QString const& subSysId) = 0;
    virtual SafeSubSysInfo querySubSysByName(QString const& subSysName) = 0;

    virtual ~SafeSubSysDAO(){}; 
    
};

Safety_API SafeSubSysDAO&  safeSubSysDAO();

#endif





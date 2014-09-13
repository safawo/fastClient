#ifndef Think_Safety_SafeObjectDAO
#define Think_Safety_SafeObjectDAO

#include <QtCore/QString>  
#include <QtCore/QList> 
#include <QtCore/QStringList>  

#include <utils/Common.hpp> 

#include <safety/SafetyDll.hpp>

#include <safety/SafeObjectInfo.hpp>
#include <safety/SafeObjectAuthInfo.hpp>

class Safety_API SafeObjectDAO
{
public:
    virtual void reLoad() = 0;

    virtual bool createObject(SafeObjectInfo const& safeObject) = 0;
    virtual bool delObject(QString const& objectId) = 0;
    virtual bool delObjectByName(QString const& objectName) = 0;

    virtual QList<SafeObjectInfo> queryObjects(QString const& objectType = NULL_QSTR) = 0;

    virtual bool authObject(QList<SafeObjectAuthInfo> const& auths, QList<SafeObjectAuthInfo> const& unAuths) = 0;
    virtual QList<SafeObjectAuthInfo> queryAuth(QString const& objectType = NULL_QSTR) = 0;
     
    virtual ~SafeObjectDAO(){}; 

};

Safety_API SafeObjectDAO&  safeObjectDAO();

#endif





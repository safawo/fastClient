#ifndef Think_Safety_SafeAccessDAO
#define Think_Safety_SafeAccessDAO

#include <QtCore/QString>  
#include <QtCore/QList> 
#include <QtCore/QStringList>  

#include <utils/Common.hpp> 

#include <safety/SafetyDll.hpp>

#include <safety/SafeObjectInfo.hpp>
#include <safety/SafeObjectAuthInfo.hpp>

class Safety_API SafeAccessDAO
{
public:
    virtual void reLoad() = 0;

    virtual bool tryAccessObject(QString objectId) = 0;
    virtual void getAccessObjects(QString objectType, QStringList& objectIds) = 0; 
    virtual void getAccessObjectNames(QString objectType, QStringList& objectNames) = 0;  

    virtual ~SafeAccessDAO(){}; 

};

Safety_API SafeAccessDAO&  accessDAO();

#endif





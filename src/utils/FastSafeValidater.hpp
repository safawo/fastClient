#ifndef Think_Utils_Fast_Safe_Validater
#define Think_Utils_Fast_Safe_Validater

#include <utils/UtilsDll.hpp>  
#include <QtCore/QDebug>

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QMap>

#include <QtCore/QJsonArray> 
#include <QtCore/QJsonObject> 
#include <QtCore/QJsonValue> 
#include <QtCore/QJsonValueRef> 
#include <QtCore/QJsonDocument>

#include <utils/FastRequestInfo.hpp>
#include <utils/FastResponseInfo.hpp>

class Utils_API FastSafeValidater  
{  
public: 
    virtual bool checkRequest(QString const& sessionId, QString const& reqPath, QString& checkMsg = NULL_QSTR) const = 0;
     
    virtual ~FastSafeValidater(){}; 
};

#endif



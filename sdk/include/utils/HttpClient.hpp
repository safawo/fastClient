#ifndef Think_Utils_Http_Client 
#define Think_Utils_Http_Client
 
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
#include <utils/FastSafeValidater.hpp> 

class Utils_API HttpClient  
{  
public:
    virtual QJsonObject postJson(QString const& reqPath) = 0; 
    virtual QJsonObject postJson(QString const& reqPath, QJsonObject const& requestMsg) = 0; 

    virtual QString download(QString const& reqPath, bool isForce = true) = 0;
    virtual bool upload(QString const& localPath) = 0;

    virtual bool verifyResponse(QJsonObject const& rspMsg) = 0;
    virtual bool verifyRespNoTip(QJsonObject const& rspMsg) = 0;

    virtual ~HttpClient(){}; 
};

Utils_API HttpClient&  httpClient();
 
#endif

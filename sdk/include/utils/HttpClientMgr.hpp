#ifndef Think_Utils_Http_ClientMgr 
#define Think_Utils_Http_ClientMgr

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

#include <utils/HttpClient.hpp>
#include <utils/FastSafeValidater.hpp>

#define FAST_REQ_JSON_IP_DEFAULT       "localhost"
#define FAST_REQ_JSON_PORT_DEFAULT     "65533"
#define FAST_REQ_JSON_SESSION_INIT     "init"

class Utils_API HttpClientMgr
{  
public: 
    virtual HttpClient& getClient() = 0;

    virtual void resetServer(QString const& reqIp = FAST_REQ_JSON_IP_DEFAULT, QString const& reqPort = FAST_REQ_JSON_PORT_DEFAULT) = 0;
    virtual void resetSession(QString const& sessionId = FAST_REQ_JSON_SESSION_INIT) = 0;
    
    virtual void regValidater(FastSafeValidater* validater = NULL) = 0;
     
public:
    virtual QString& getReqIp() = 0;
    virtual QString& getReqPort() = 0; 
    virtual QString& getReqSessionId() = 0;

    virtual FastSafeValidater* getValidater() = 0;
    virtual QString getReqUrl(QString const& reqPath) = 0;

    virtual ~HttpClientMgr(){}; 
};

Utils_API HttpClientMgr&  httpClientMgr();

#endif



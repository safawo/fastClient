#ifndef Think_Safety_SafeSessionInfo
#define Think_Safety_SafeSessionInfo

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QJsonArray> 
#include <QtCore/QJsonObject> 
#include <QtCore/QJsonValue> 
#include <QtCore/QJsonDocument> 

#include <safety/SafetyDll.hpp>

#include <utils/Common.hpp>

class Safety_API SafeSessionInfo
{  
public:
    enum SESSION_STATUS
    {
        SESSION_INIT,
        SESSION_LOGIN,
        SESSION_TIMEOUT,
        SESSION_LOGOUT,
        SESSION_SLEEP,
        SESSION_LOCK,
        SESSION_EXIT
    };

public:
    SafeSessionInfo()
    {
        reset();
    }

    SafeSessionInfo(SafeSessionInfo const& other)
    {
        id = other.id;
        randId = other.randId; 
        connTime = other.connTime; 

        loginUserId = other.loginUserId; 
        loginUserName = other.loginUserName;

        clientIp = other.clientIp; 
        clientHost = other.clientHost;
        serverIp = other.serverIp; 
        serverHost = other.serverHost;

        keepAliveTime = other.keepAliveTime;
        sessionStatus = other.sessionStatus;

        sessionKey = other.sessionKey;
    }

    ~SafeSessionInfo()
    {

    }

public: 
    SafeSessionInfo& reset()
    { 
        id = NULL_STR;
        randId = NULL_STR; 
        connTime = NULL_STR; 

        loginUserId = NULL_STR;
        loginUserName = NULL_STR;

        clientIp = NULL_STR;
        clientHost = NULL_STR;
        serverIp = NULL_STR;
        serverHost = NULL_STR;

        keepAliveTime = NULL_STR;
        sessionStatus = NULL_STR;

        sessionKey = NULL_STR;

        return *this;
    }

    SafeSessionInfo& reset(SafeSessionInfo const& other)
    { 
        *this = other;
        return *this;
    }

    SafeSessionInfo& operator=(SafeSessionInfo const& other)
    {
        if (this == &other)
        {
            return *this;
        }

        id = other.id;
        randId = other.randId; 
        connTime = other.connTime; 

        loginUserId = other.loginUserId; 
        loginUserName = other.loginUserName;

        clientIp = other.clientIp; 
        clientHost = other.clientHost;
        serverIp = other.serverIp; 
        serverHost = other.serverHost;

        keepAliveTime = other.keepAliveTime;
        sessionStatus = other.sessionStatus;

        sessionKey = other.sessionKey;

        return *this;
    }

public:
    bool isNull()
    {
        if (this->id.isEmpty())
        {
            return true;
        }

        return false;
    }

public:
    QString const& toKey()
    {
        return this->sessionKey;
    }

    QString const& fromKey(QString const& sessionInfo)
    {
        this->sessionKey = sessionInfo;
        return this->sessionKey;
    }

public:
    QJsonObject const& toJson(QJsonObject& jsonObj) const 
    {  
        jsonObj.insert("id", QJsonValue(id));
        jsonObj.insert("randId", QJsonValue(randId));
        jsonObj.insert("connTime", QJsonValue(connTime));

        jsonObj.insert("loginUserId", QJsonValue(loginUserId));
        jsonObj.insert("loginUserName", QJsonValue(loginUserName));

        jsonObj.insert("clientIp", QJsonValue(clientIp));
        jsonObj.insert("clientHost", QJsonValue(clientHost));
        jsonObj.insert("serverIp", QJsonValue(serverIp)); 
        jsonObj.insert("serverHost", QJsonValue(serverHost)); 

        jsonObj.insert("keepAliveTime", QJsonValue(keepAliveTime)); 
        jsonObj.insert("sessionStatus", QJsonValue(sessionStatus));  

        jsonObj.insert("sessionKey", QJsonValue(sessionKey));  

        return jsonObj;
    }

    QJsonObject toJson() const
    {
        QJsonObject jsonObj; 
        return toJson(jsonObj);
    }

    static QJsonArray const& toJsons(QList<SafeSessionInfo> const& objs, QJsonArray& jsons)
    { 
        for (int index = 0; index < objs.count(); index++)
        { 
            jsons.push_back(QJsonValue(objs[index].toJson()));
        } 
        return jsons;
    }

    static QJsonArray toJsons(QList<SafeSessionInfo> const& objs)
    {
        QJsonArray jsons;
        return toJsons(objs, jsons);
    } 

    SafeSessionInfo& fromJson(QJsonObject const& jsonObj)
    {   
        id = jsonObj["id"].toString(); 
        randId = jsonObj["randId"].toString(); 
        connTime = jsonObj["connTime"].toString();   

        loginUserId = jsonObj["loginUserId"].toString();  
        loginUserName = jsonObj["loginUserName"].toString();  

        clientIp = jsonObj["clientIp"].toString();  
        clientHost = jsonObj["clientHost"].toString();  
        serverIp = jsonObj["serverIp"].toString();  
        serverHost = jsonObj["serverHost"].toString();  

        keepAliveTime = jsonObj["keepAliveTime"].toString();  
        sessionStatus = jsonObj["sessionStatus"].toString();  

        sessionKey = jsonObj["sessionKey"].toString();  
         
        return *this;
    }

    SafeSessionInfo(QJsonObject const& jsonObj)
    {
        fromJson(jsonObj);
    }

    static QList<SafeSessionInfo>& fromJsons(QJsonArray const& jsons, QList<SafeSessionInfo>& objs)
    {
        objs.clear();
        for (int index = 0; index < jsons.count(); index++)
        { 
            objs.push_back(SafeSessionInfo(jsons.at(index).toObject()));
        }

        return objs;
    }

    static QList<SafeSessionInfo> fromJsons(QJsonArray const& jsons)
    {
        QList<SafeSessionInfo> objs;
        return fromJsons(jsons, objs);
    } 

    static QList<SafeSessionInfo>& fromJsons(QJsonObject const& parentJson, QList<SafeSessionInfo>& objs)
    {
        objs.clear();
        if (!parentJson.contains("sessions"))
        {
            return objs;  
        }
        QJsonValue objsValue = parentJson["sessions"];
        if (!objsValue.isArray())  
        {
            return objs;
        }

        return fromJsons(objsValue.toArray(), objs);
    }

    static QList<SafeSessionInfo> fromJsons(QJsonObject const& parentJson)
    {
        QList<SafeSessionInfo> objs;
        return fromJsons(parentJson, objs);
    }

public:  
    QString id; 
    QString randId; 
    QString connTime;

    QString loginUserId;
    QString loginUserName;
     
    QString clientIp;
    QString clientHost;    
    QString serverIp;
    QString serverHost;

    QString keepAliveTime; 
    QString sessionStatus; 

    QString sessionKey; 

}; 


#endif


#include <safety/SafeObjectDAO.hpp> 

#include <utils/HttpClient.hpp> 

#include <safety/SafeAccessDAO.hpp>

#define REQ_SAFEOBJECT_CREATEOBJECT   "/think/fast/safe/object/createObject"   
#define REQ_SAFEOBJECT_DELOBJECT      "/think/fast/safe/object/delObject"

#define REQ_SAFEOBJECT_QUERYOBJECT    "/think/fast/safe/object/queryObject"   
#define REQ_SAFEOBJECT_AUTH           "/think/fast/safe/object/auth"  
#define REQ_SAFEOBJECT_QUERYAUTH      "/think/fast/safe/object/queryAuth"  

#define REQ_SAFE_REFRESH_STAMP      "/think/hotel/conf/common/refreshConfStamp"

class SafeObjectDAOImpl: public SafeObjectDAO
{
public:
    virtual void reLoad()
    {

    }
    
    virtual bool createObject(SafeObjectInfo const& safeObject)
    {
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEOBJECT_CREATEOBJECT, safeObject.toJson());
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        accessDAO().reLoad(); 

        this->refreshStamp();

        return true;
    }

    virtual bool delObject(QString const& objectId)
    {
        QJsonObject reqMsg;
        reqMsg.insert("objectId", QJsonValue(objectId)); 

        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEOBJECT_DELOBJECT, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        accessDAO().reLoad();

        this->refreshStamp();

        return true;
    }

    virtual bool delObjectByName(QString const& objectName)
    {
        QJsonObject reqMsg;
        reqMsg.insert("objectName", QJsonValue(objectName)); 

        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEOBJECT_DELOBJECT, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        accessDAO().reLoad();

        this->refreshStamp();

        return true;
    }

    virtual QList<SafeObjectInfo> queryObjects(QString const& objectType = NULL_QSTR) 
    {
        QList<SafeObjectInfo> objects;

        QJsonObject reqMsg;
        reqMsg.insert("objectType", QJsonValue(objectType)); 

        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEOBJECT_QUERYOBJECT, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return objects;
        }
        SafeObjectInfo::fromJsons(rspMsg, objects);

        return objects;
    }

    virtual bool authObject(QList<SafeObjectAuthInfo> const& auths, QList<SafeObjectAuthInfo> const& unAuths)  
    {
        QJsonObject reqMsg;
        reqMsg.insert("auths", QJsonValue(SafeObjectAuthInfo::toJsons(auths)));
        reqMsg.insert("unAuths", QJsonValue(SafeObjectAuthInfo::toJsons(unAuths)));

        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEOBJECT_AUTH, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        accessDAO().reLoad();

        this->refreshStamp();

        return true;
    }

    virtual QList<SafeObjectAuthInfo> queryAuth(QString const& objectType = NULL_QSTR) 
    {
        QList<SafeObjectAuthInfo> auths;

        QJsonObject reqMsg;
        reqMsg.insert("objectType", QJsonValue(objectType)); 
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEOBJECT_QUERYAUTH, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return auths;
        }

        SafeObjectAuthInfo::fromJsons(rspMsg, auths);
        return auths;
    }

    virtual ~SafeObjectDAOImpl()
    {

    }

    static SafeObjectDAO* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new SafeObjectDAOImpl();
        }

        return _instance;
    }

private:
    SafeObjectDAOImpl()
    {
        this->queryAll();
    }

    void queryAll()
    {   
        return;
    }

    void refreshStamp(){  
        httpClient().postJson(REQ_SAFE_REFRESH_STAMP);  
        return;
    }
     
private:
    static SafeObjectDAO* _instance; 

};

SafeObjectDAO* SafeObjectDAOImpl::_instance = NULL; 

SafeObjectDAO& safeObjectDAO()
{ 
    return *(SafeObjectDAOImpl::getInstance());
}




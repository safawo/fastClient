#include <safety/SafeOperateDAO.hpp> 

#include <utils/HttpClient.hpp> 

#define REQ_SAFEOPERATE_AUTH             "/think/fast/safe/operate/auth"  
#define REQ_SAFEOPERATE_QUERYAUTH        "/think/fast/safe/operate/queryAuth"  
 
#define REQ_SAFEOPERATE_QUERYOPERATE     "/think/fast/safe/operate/queryOperate" 

#define REQ_SAFE_REFRESH_STAMP           "/think/hotel/conf/common/refreshConfStamp"

class SafeOperateDAOImpl: public SafeOperateDAO
{
public:
    virtual void reLoad()
    {
        this->queryAll();
    }

    virtual bool authOperate(QList<SafeOperateAuthInfo> const& auths, QList<SafeOperateAuthInfo> const& unAuths)  
    {
        QJsonObject reqMsg;
        reqMsg.insert("auths", QJsonValue(SafeOperateAuthInfo::toJsons(auths)));
        reqMsg.insert("unAuths", QJsonValue(SafeOperateAuthInfo::toJsons(unAuths)));

        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEOPERATE_AUTH, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        this->refreshStamp();
        return true;
    }
     
    virtual bool queryAuth(QList<SafeOperateAuthInfo>& auths)
    {
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEOPERATE_QUERYAUTH);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        SafeOperateAuthInfo::fromJsons(rspMsg, auths);
    }

    virtual QList<SafeOperateInfo> queryOperates(QString const& subSysName, QString const& operateGroup)  
    { 
        QList<SafeOperateInfo> operates;

        QJsonObject reqMsg;
        reqMsg.insert("subSys", subSysName);
        reqMsg.insert("operateGroup", operateGroup);

        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEOPERATE_QUERYOPERATE, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return operates;
        }

        SafeOperateInfo::fromJsons(rspMsg, operates); 
        return operates;
    }
     
    virtual QStringList queryOperateNames(QString const& subSysName, QString const& operateGroup)
    {
        QList<SafeOperateInfo> operates = queryOperates(subSysName, operateGroup);

        QStringList operateNames;
        int operateCount = operates.size();
        for (int indexOperate = 0; indexOperate < operateCount; indexOperate++)
        {
            operateNames.push_back(operates[indexOperate].operateName);
        }

        operateNames.sort(); 

        return operateNames;
    }

    virtual ~SafeOperateDAOImpl()
    {

    }

    static SafeOperateDAO* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new SafeOperateDAOImpl();
        }

        return _instance;
    }

private:
    SafeOperateDAOImpl()
    {
        this->reLoad();
    }

    void queryAll()
    {    
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEOPERATE_QUERYOPERATE);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return;
        }

        listData.clear();
        mapId.clear();
        mapName.clear();
        SafeOperateInfo::fromJsons(rspMsg, listData); 
        for (int index = 0; index < listData.size(); index++){
            mapId[listData[index].id] = listData[index];
            mapId[listData[index].operateName] = listData[index]; 
        }

        return;
    }
     
    void refreshStamp(){  
        httpClient().postJson(REQ_SAFE_REFRESH_STAMP);  
        return;
    }

private:
    static SafeOperateDAO* _instance; 

    QList<SafeOperateInfo> listData;
    QMap<QString, SafeOperateInfo> mapId;
    QMap<QString, SafeOperateInfo> mapName;

};

SafeOperateDAO* SafeOperateDAOImpl::_instance = NULL; 

SafeOperateDAO& safeOperateDAO()
{ 
    return *(SafeOperateDAOImpl::getInstance());
}

 
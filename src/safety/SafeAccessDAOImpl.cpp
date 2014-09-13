#include <safety/SafeAccessDAO.hpp> 

#include <utils/HttpClient.hpp> 

#define REQ_SafeAccess_QueryAccessObj   "/think/fast/safe/access/queryAccessObj"    

class SafeAccessDAOImpl: public SafeAccessDAO
{
public:
    virtual void reLoad(){
        allObjectIds.clear();

        QJsonObject rspMsg = httpClient().postJson(REQ_SafeAccess_QueryAccessObj);
        if (!httpClient().verifyResponse(rspMsg)){
            return;
        }
        
        if (!rspMsg.contains("objectIds")){
            return;
        }

        QJsonValue objsValue = rspMsg["objectIds"];
        if (!objsValue.isArray()){
            return;
        }

        QJsonArray objsArray = objsValue.toArray();
        for (int index = 0; index < objsArray.count(); index++){ 
            allObjectIds.insert(objsArray.at(index).toString());
        }
    }

    virtual bool tryAccessObject(QString objectId){
        if (allObjectIds.contains(objectId)){
            return true;
        }

        return false;
    }

    virtual void getAccessObjects(QString objectType, QStringList& objectIds){
        objectIds.clear();
         
        QJsonObject reqMsg;
        reqMsg.insert("objectType", QJsonValue(objectType));
        QJsonObject rspMsg = httpClient().postJson(REQ_SafeAccess_QueryAccessObj, reqMsg);
        if (!httpClient().verifyResponse(rspMsg)){
            return;
        }

        if (!rspMsg.contains("objectIds")){
            return;
        }

        QJsonValue objsValue = rspMsg["objectIds"];
        if (!objsValue.isArray()){
            return;
        }

        QJsonArray objsArray = objsValue.toArray();
        for (int index = 0; index < objsArray.count(); index++){ 
            objectIds.push_back(objsArray.at(index).toString());
        }

        return;
    }
    
    virtual void getAccessObjectNames(QString objectType, QStringList& objectNames){
        objectNames.clear();

        QJsonObject reqMsg;
        reqMsg.insert("objectType", QJsonValue(objectType));
        QJsonObject rspMsg = httpClient().postJson(REQ_SafeAccess_QueryAccessObj, reqMsg);
        if (!httpClient().verifyResponse(rspMsg)){
            return;
        }

        if (!rspMsg.contains("objectNames")){
            return;
        }

        QJsonValue objsValue = rspMsg["objectNames"];
        if (!objsValue.isArray()){
            return;
        }

        QJsonArray objsArray = objsValue.toArray();
        for (int index = 0; index < objsArray.count(); index++){ 
            objectNames.push_back(objsArray.at(index).toString());
        }

        return;
    }
 
    virtual ~SafeAccessDAOImpl()
    {

    }

    static SafeAccessDAO* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new SafeAccessDAOImpl();
        }

        return _instance;
    }

private:
    SafeAccessDAOImpl()
    {
        this->reLoad();
    }

private:
    QSet<QString> allObjectIds;

private:
    static SafeAccessDAO* _instance; 

};

SafeAccessDAO* SafeAccessDAOImpl::_instance = NULL; 

SafeAccessDAO& accessDAO()
{ 
    return *(SafeAccessDAOImpl::getInstance());
}




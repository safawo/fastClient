#include <safety/SafeUserDAO.hpp> 
#include <safety/SafeUserInfo.hpp>

#include <utils/HttpClient.hpp> 

#define REQ_SAFEUSER_QUERY          "/think/fast/safe/user/query"
#define REQ_SAFEUSER_CREATE         "/think/fast/safe/user/create"
#define REQ_SAFEUSER_DELETE         "/think/fast/safe/user/delete"
#define REQ_SAFEUSER_CHANGE         "/think/fast/safe/user/change"

#define REQ_SAFEUSER_MODPASSWORD    "/think/fast/safe/user/modPassword"
#define REQ_SAFEUSER_LOCKUSER       "/think/fast/safe/user/lockUser"
#define REQ_SAFEUSER_UNLOCKUSER     "/think/fast/safe/user/unlockUser"
#define REQ_SAFEUSER_OFFLINEUSER    "/think/fast/safe/user/offlineUser"

#define REQ_SAFE_REFRESH_STAMP      "/think/hotel/conf/common/refreshConfStamp"

class SafeUserDAOImpl: public SafeUserDAO
{
public:
    virtual void reLoad()
    {

    }

    virtual SafeUserInfo queryUser(QString const& userId)
    {
        SafeUserInfo emptyUser;

        QJsonObject reqMsg;
        reqMsg.insert("userId", userId);
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEUSER_QUERY, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return emptyUser;
        }

        QList<SafeUserInfo> users;
        SafeUserInfo::fromJsons(rspMsg, users);

        if (users.isEmpty())
        {
            return emptyUser;
        }

        return users[0];
    }

    virtual SafeUserInfo queryByEmployeeId(QString const& employeeId)
    {
        SafeUserInfo emptyUser;

        QJsonObject reqMsg;
        reqMsg.insert("employeeId", employeeId);
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEUSER_QUERY, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return emptyUser;
        }

        QList<SafeUserInfo> users;
        SafeUserInfo::fromJsons(rspMsg, users);

        if (users.isEmpty())
        {
            return emptyUser;
        }

        return users[0];
    }

    virtual QList<SafeUserInfo> queryUsers()
    {
        QList<SafeUserInfo> users;

        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEUSER_QUERY);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return users;
        }

        SafeUserInfo::fromJsons(rspMsg, users);
        return users;
    }

    virtual QList<SafeUserInfo> queryByDepartId(QString const& departId)
    {
        QList<SafeUserInfo> users;

        QJsonObject reqMsg;
        reqMsg.insert("departId", departId);
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEUSER_QUERY, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return users;
        }

        SafeUserInfo::fromJsons(rspMsg, users);
        return users;
    }

    virtual QStringList queryUserNames()
    {
        QList<SafeUserInfo> users = queryUsers();
        QStringList userNames;
        int userCount = users.count();
        for (int indexUser = 0; indexUser < userCount; indexUser++)
        {
            userNames.push_back(users[indexUser].name);
        } 

        userNames.sort();
        return userNames;
    }

    virtual bool createUser(SafeUserInfo const& user)
    { 
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEUSER_CREATE, user.toJson());
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        this->refreshStamp();
        return true;
    }

    virtual bool delUser(QString const& userId)
    {
        QJsonObject reqMsg;
        reqMsg.insert("userId", userId);
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEUSER_DELETE, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        this->refreshStamp();
        return true;
    }

    virtual bool changeUser(SafeUserInfo const& user)
    {
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEUSER_CHANGE, user.toJson());
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        this->refreshStamp();
        return true;
    }

    virtual bool modPassword(QString const& userId, QString const& newPassword)
    {
        QJsonObject reqMsg;
        reqMsg.insert("userId", userId);
        reqMsg.insert("newPassword", utils().password(newPassword));
         
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEUSER_MODPASSWORD, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        this->refreshStamp();  
        return true;
    }

    virtual bool lockUser(QString const& userId, QString const& lockReason)
    {
        QJsonObject reqMsg;
        reqMsg.insert("userId", userId);
        reqMsg.insert("lockReason", lockReason);
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEUSER_LOCKUSER, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        this->refreshStamp();
        return true;
    }

    virtual bool unlockUser(QString const& userId)
    {
        QJsonObject reqMsg;
        reqMsg.insert("userId", userId); 
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEUSER_UNLOCKUSER, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        this->refreshStamp();
        return true;
    }
    
    virtual bool offlineUser(QString const& userId) 
    {
        QJsonObject reqMsg;
        reqMsg.insert("userId", userId); 
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEUSER_OFFLINEUSER, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        return true;
    }

    virtual ~SafeUserDAOImpl()
    {

    }

    static SafeUserDAO* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new SafeUserDAOImpl();
        }

        return _instance;
    }

private:
    SafeUserDAOImpl()
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
    static SafeUserDAO* _instance; 

};

SafeUserDAO* SafeUserDAOImpl::_instance = NULL; 

SafeUserDAO& safeUserDAO()
{ 
    return *(SafeUserDAOImpl::getInstance());
}  
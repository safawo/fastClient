#include <safety/SafeRoleDAO.hpp>
#include <safety/SafeRoleInfo.hpp>
#include <safety/SafeUserInfo.hpp>

#include <utils/HttpClient.hpp> 
 
#define REQ_SAFEROLE_QUERY           "/think/fast/safe/role/query" 
#define REQ_SAFEROLE_CREATE          "/think/fast/safe/role/create" 
#define REQ_SAFEROLE_DELETE          "/think/fast/safe/role/delete" 
#define REQ_SAFEROLE_CHANGE          "/think/fast/safe/role/change"

#define REQ_SAFEROLE_ALLOC           "/think/fast/safe/role/alloc"
#define REQ_SAFEROLE_QUERYALLOC      "/think/fast/safe/role/queryAlloc"

#define REQ_SAFE_REFRESH_STAMP      "/think/hotel/conf/common/refreshConfStamp"

class SafeRoleDAOImpl: public SafeRoleDAO
{
public:
    virtual void reLoad()
    {

    }

    virtual SafeRoleInfo queryRole(QString const& roleId)
    {
        SafeRoleInfo emptyRole;

        QJsonObject reqMsg;
        reqMsg.insert("roleId", roleId);
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEROLE_QUERY, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return emptyRole;
        }

        QList<SafeRoleInfo> roles;
        SafeRoleInfo::fromJsons(rspMsg, roles);

        if (roles.isEmpty())
        {
            return emptyRole;
        }

        return roles[0];
    }

    virtual SafeRoleInfo queryRoleByName(QString const& roleName)
    {
        SafeRoleInfo emptyRole;

        QJsonObject reqMsg;
        reqMsg.insert("roleName", roleName);
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEROLE_QUERY, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return emptyRole;
        }

        QList<SafeRoleInfo> roles;
        SafeRoleInfo::fromJsons(rspMsg, roles);

        if (roles.isEmpty())
        {
            return emptyRole;
        }

        return roles[0];
    }

    virtual QList<SafeRoleInfo> queryRoles()
    {
        QList<SafeRoleInfo> roles;

        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEROLE_QUERY);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return roles;
        }

        SafeRoleInfo::fromJsons(rspMsg, roles);
        return roles;
    }

    virtual bool createRole(SafeRoleInfo const& role)
    {
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEROLE_CREATE, role.toJson());
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }
         
        this->refreshStamp();
        return true;
    }
  
    virtual bool delRole(QString const& roleId)
    {
        QJsonObject reqMsg;
        reqMsg.insert("roleId", roleId);
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEROLE_DELETE, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        this->refreshStamp();
        return true;
    }
  
    virtual bool changeRole(SafeRoleInfo const& role)
    {
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEROLE_CHANGE, role.toJson());
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        this->refreshStamp();
        return true;
    }

    virtual bool allocRole(QList<SafeRoleAllocInfo> const& allocs, QList<SafeRoleAllocInfo> const& unAllocs)  
    {
        QJsonObject reqMsg;
        reqMsg.insert("allocs", QJsonValue(SafeRoleAllocInfo::toJsons(allocs)));
        reqMsg.insert("unAllocs", QJsonValue(SafeRoleAllocInfo::toJsons(unAllocs)));

        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEROLE_ALLOC, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        this->refreshStamp();
        return true;
    }

    virtual bool queryAlloc(QList<SafeRoleAllocInfo>& allocs)  
    {
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEROLE_QUERYALLOC);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        SafeRoleAllocInfo::fromJsons(rspMsg, allocs);
    }

    virtual SafeRoleInfo getRoleById(QString const& roleId)
    {
        SafeRoleInfo emptyRole;

        QJsonObject reqMsg;
        reqMsg.insert("roleId", roleId);
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEROLE_QUERY, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return emptyRole;
        }

        QList<SafeRoleInfo> roles;
        SafeRoleInfo::fromJsons(rspMsg, roles);

        if (roles.isEmpty())
        {
            return emptyRole;
        }

        return roles[0]; 
    }

    virtual SafeRoleInfo getRoleByName(QString const& roleName)
    {
        SafeRoleInfo emptyRole;

        QJsonObject reqMsg;
        reqMsg.insert("roleName", roleName);
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFEROLE_QUERY, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return emptyRole;
        }

        QList<SafeRoleInfo> roles;
        SafeRoleInfo::fromJsons(rspMsg, roles);

        if (roles.isEmpty())
        {
            return emptyRole;
        }

        return roles[0]; 
    }

    virtual ~SafeRoleDAOImpl()
    {

    }
      
    static SafeRoleDAO* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new SafeRoleDAOImpl();
        }

        return _instance;
    }

private:
    SafeRoleDAOImpl()
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
    static SafeRoleDAO* _instance; 

};

SafeRoleDAO* SafeRoleDAOImpl::_instance = NULL; 

SafeRoleDAO& safeRoleDAO()
{ 
    return *(SafeRoleDAOImpl::getInstance());
}  
#include <safety/SafeSelfDAO.hpp>
#include <safety/SafeRoleInfo.hpp>
#include <safety/SafeUserInfo.hpp>

#include <utils/HttpClient.hpp> 

#include <utils/Utils.hpp>

#define REQ_SAFESELF_QUERY_MYINFO    "/think/fast/safe/self/queryMyInfo"
#define REQ_SAFESELF_MODPASSWORD     "/think/fast/safe/self/modPassword"
#define REQ_SAFESELF_MODUSERINFO     "/think/fast/safe/self/modUserInfo"

#define REQ_SAFE_REFRESH_STAMP      "/think/hotel/conf/common/refreshConfStamp"

class SafeSelfDAOImpl: public SafeSelfDAO
{
public:
    virtual void reLoad()
    {

    }

    virtual SafeUserInfo queryMyInfo()
    {
        SafeUserInfo userInfo; 
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFESELF_QUERY_MYINFO);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return userInfo;
        }

        userInfo.fromJson(rspMsg);

        return userInfo;
    }

    virtual bool modPassword(QString const& currentPassword, QString const& newPassword)
    {
        QJsonObject reqMsg;

        reqMsg.insert("currentPassword", utils().password(currentPassword));
        reqMsg.insert("newPassword", utils().password(newPassword));
         
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFESELF_MODPASSWORD, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        this->refreshStamp();
        return true;
    }

    virtual bool modUserInfo(SafeUserInfo const& selfInfo)
    {  
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFESELF_MODPASSWORD, selfInfo.toJson());
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        this->refreshStamp();
        return true;
    }
     
    virtual ~SafeSelfDAOImpl()
    {

    }

    static SafeSelfDAO* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new SafeSelfDAOImpl();
        }

        return _instance;
    }

private:
    SafeSelfDAOImpl()
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
    static SafeSelfDAO* _instance; 

};

SafeSelfDAO* SafeSelfDAOImpl::_instance = NULL; 

SafeSelfDAO& safeSelfDAO()
{ 
    return *(SafeSelfDAOImpl::getInstance());
}  
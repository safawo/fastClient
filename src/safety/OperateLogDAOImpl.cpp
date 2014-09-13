#include <safety/OperateLogDAO.hpp>
#include <safety/OperateLogInfo.hpp>

#include <utils/HttpClient.hpp>

#define REQ_SAFETY_LOG_QUERY_OPERATELOG     "/think/fast/safe/log/queryOperateLog" 
#define REQ_SAFETY_LOG_IMPORT_OPERATELOG     "/think/fast/safe/log/importOperateLog" 

class OperateLogDAOImpl: public OperateLogDAO   
{
public:
    virtual void reLoad()
    {

    }

    virtual void queryLogs(QString const& startTime, QString const& endTime, QString const& subSys, QString const& operateGroup, QString const& operateName, 
        QString const& userName, QString const& operateObj, QString const& operateContent, QList<OperateLogInfo>& logs)
    {
        logs.clear();

        QJsonObject reqMsg;
        reqMsg.insert("startTime", startTime.trimmed());
        reqMsg.insert("endTime", endTime.trimmed());
        reqMsg.insert("subSys", subSys.trimmed());
        reqMsg.insert("operateGroup", operateGroup.trimmed());
        reqMsg.insert("operateName", operateName.trimmed());
        reqMsg.insert("userName", userName.trimmed());
        reqMsg.insert("operateObj", operateObj.trimmed());
        reqMsg.insert("operateContent", operateContent.trimmed());
         
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFETY_LOG_QUERY_OPERATELOG, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return;
        }

        OperateLogInfo::fromJsons(rspMsg, logs);

        return;
    }

    virtual void importLogs(QList<OperateLogInfo>& logs){
        QJsonObject reqMsg;
        reqMsg.insert("logs", OperateLogInfo::toJsons(logs));

        QJsonObject rspMsg = httpClient().postJson(REQ_SAFETY_LOG_QUERY_OPERATELOG, reqMsg);
        
        httpClient().verifyResponse(rspMsg);

        return;
    }

    virtual ~OperateLogDAOImpl() {

    } 

    static OperateLogDAO* getInstance() {
        if (_instance == NULL)
        {
            _instance = new OperateLogDAOImpl();
        }

        return _instance;
    }

private:
    OperateLogDAOImpl(){
         
    }
     
private:
    static OperateLogDAO* _instance; 

};

OperateLogDAO* OperateLogDAOImpl::_instance = NULL; 

OperateLogDAO& operateLogDAO()
{ 
    return *(OperateLogDAOImpl::getInstance());
} 



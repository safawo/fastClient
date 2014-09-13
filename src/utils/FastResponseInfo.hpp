#ifndef Think_Utils_FastResponseInfo
#define Think_Utils_FastResponseInfo

#include <QtCore/QDebug>

#include <QtCore/QList>
#include <QtCore/QString>

#include <QtCore/QJsonArray> 
#include <QtCore/QJsonObject> 
#include <QtCore/QJsonValue> 
#include <QtCore/QJsonDocument>

 

#include <utils/Common.hpp>
#include <utils/UtilsDll.hpp>

#include <utils/FastMsgBox.hpp>

#define MSG_LEVEL_INFO   "level_info"
#define MSG_LEVEL_WARN   "level_warn"
#define MSG_LEVEL_ERROR  "level_error"
#define MSG_LEVEL_FATAL  "level_fatal"

#define MSG_ID_SUCCESS   "id_success"
#define MSG_ID_FAIL      "id_fail"
#define MSG_ID_ERROR     "id_error"

class Utils_API FastResponseInfo
{
public:
    FastResponseInfo()
    {
        reset();
    } 
     
    FastResponseInfo(FastResponseInfo const& other)
    {
        reset(other);
    }

    ~FastResponseInfo()
    {

    }

public:
    static bool verify(QJsonObject const& rspMsg)
    {
        FastResponseInfo rspInfo(rspMsg);
        return rspInfo.verify();
    }

    static bool verifyNoTip(QJsonObject const& rspMsg)
    {
        FastResponseInfo rspInfo(rspMsg);
        return rspInfo.isSucceess();
    }

    bool verify()
    {
        if (isSucceess())
        {
            return true;
        }  

        msgBox().information(this->getRspRetMsg());
        
        return false;
    }

    bool isSucceess()
    { 
        if (getRspRetId() == MSG_ID_SUCCESS)
        { 
            return true;
        } 
        return false;
    }

    void printMsg()
    {
        qDebug()<<QJsonDocument(toRspMsg()).toJson();
    }

public:
    QString& setReqSessionId(QString const& sessionId)
    {
        this->reqSessionId = sessionId;
        return this->reqSessionId;
    }

    QString& setReqActionId(QString const& actionId)
    {
        this->reqActionId = actionId;
        return this->reqActionId;
    }

    QString& setReqStartTime(QString const& startTime)
    {
        this->reqStartTime = startTime;
        return this->reqStartTime;
    }

    QString& setRspFinishTime(QString const& finishTime)
    {
        this->rspFinishTime = finishTime;
        return this->rspFinishTime;
    }

    QString& setRspRetLevel(QString const& retLevel)
    {
        this->rspRetLevel = retLevel;
        return this->rspRetLevel;
    }

    QString& setRspRetId(QString const& retId)
    {
        this->rspRetId = retId;
        return this->rspRetId;
    }

    QString& setRspRetMsg(QString const& retMsg)
    {
        this->rspRetMsg = retMsg;
        return this->rspRetMsg;
    }

    QString& setRspRetMsgDetail(QString const& retMsgDetail)
    {
        this->rspRetMsgDetail = retMsgDetail;
        return this->rspRetMsgDetail;
    }

    QString& getReqSessionId()
    {
        return this->reqSessionId;
    }

    QString& getReqActionId()
    {
        return this->reqActionId;
    }

    QString& getReqStartTime()
    {
        return this->reqStartTime;
    }
     
    QString& getRspFinishTime()
    { 
        return this->rspFinishTime;
    }

    QString& getRspRetLevel()
    { 
        return this->rspRetLevel;
    }

    QString& getRspRetId()
    { 
        return this->rspRetId;
    }

    QString& getRspRetMsg()
    { 
        return this->rspRetMsg;
    }

    QString& getRspRetMsgDetail()
    { 
        return this->rspRetMsgDetail;
    }

public: 
    FastResponseInfo& reset()
    {
        reqSessionId = NULL_STR;
        reqActionId = NULL_STR;
        reqStartTime = NULL_STR;

        rspFinishTime = NULL_STR;
        rspRetLevel = NULL_STR;

        rspRetId = NULL_STR; 
        rspRetMsg = NULL_STR;

        rspRetMsgDetail = NULL_STR;

        return *this;
    }

    FastResponseInfo& reset(FastResponseInfo const& other)
    { 
        *this = other;
        return *this;
    }

    FastResponseInfo& operator=(FastResponseInfo const& other)
    {
        if (this == &other)
        {
            return *this;
        }

        reqSessionId = other.reqSessionId;
        reqActionId = other.reqActionId;  
        reqStartTime = other.reqStartTime; 

        rspFinishTime = other.rspFinishTime; 
        rspRetLevel = other.rspRetLevel; 

        rspRetId = other.rspRetId;  
        rspRetMsg = other.rspRetMsg;

        rspRetMsgDetail = other.rspRetMsgDetail; 

        return *this;
    }
     
public:
    QJsonObject& toRspHeader(QJsonObject& rspHeader)  
    {  
        rspHeader.insert("reqSessionId", QJsonValue(reqSessionId));
        rspHeader.insert("reqActionId", QJsonValue(reqActionId));
        rspHeader.insert("reqStartTime", QJsonValue(reqStartTime));

        rspHeader.insert("rspFinishTime", QJsonValue(rspFinishTime));
        rspHeader.insert("rspRetLevel", QJsonValue(rspRetLevel));

        rspHeader.insert("rspRetId", QJsonValue(rspRetId)); 
        rspHeader.insert("rspRetMsg", QJsonValue(rspRetMsg));

        rspHeader.insert("rspRetMsgDetail", QJsonValue(rspRetMsgDetail));

        return rspHeader;
    }

    QJsonObject toRspHeader()
    {
        QJsonObject rspHeader; 
        return toRspHeader(rspHeader);
    }
 
    QJsonObject& toRspMsg(QJsonObject& rspMsg) 
    {
        QJsonObject rspHeader; 
        toRspHeader(rspHeader);
        rspMsg.insert("header", rspHeader);
        return rspMsg;
    }

    QJsonObject toRspMsg() 
    {
        QJsonObject rspMsg; 
        return toRspMsg(rspMsg);
    }

    FastResponseInfo& fromRspHeader(QJsonObject const& rspHeader)
    { 
        reqSessionId = rspHeader["reqSessionId"].toString(); 
        reqActionId = rspHeader["reqActionId"].toString(); 
        reqStartTime = rspHeader["reqStartTime"].toString(); 

        rspFinishTime = rspHeader["rspFinishTime"].toString(); 
        rspRetLevel = rspHeader["rspRetLevel"].toString(); 

        rspRetId = rspHeader["rspRetId"].toString();
        rspRetMsg = rspHeader["rspRetMsg"].toString();

        rspRetMsgDetail = rspHeader["rspRetMsgDetail"].toString();

        return *this;
    }

    FastResponseInfo& fromRspMsg(QJsonObject const& rspMsg)
    {  
        if (!rspMsg.contains("header"))
        { 
            return *this;
        }

        QJsonValue rspHeader = rspMsg["header"];
        if (!rspHeader.isObject())
        { 
            return *this;
        } 
        fromRspHeader(rspHeader.toObject());
    }
     
    FastResponseInfo(QJsonObject const& rspMsg)
    { 
        fromRspMsg(rspMsg);
    }

private:
    QString reqSessionId;
    QString reqActionId;
    QString reqStartTime;

    QString rspFinishTime; 
    QString rspRetLevel;
    
    QString rspRetId; 
    QString rspRetMsg;

    QString rspRetMsgDetail;

};
 

#endif
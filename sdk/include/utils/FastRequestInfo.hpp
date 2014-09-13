#ifndef Think_Utils_FastRequestInfo
#define Think_Utils_FastRequestInfo

#include <QtCore/QDebug>

#include <QtCore/QList>
#include <QtCore/QString>

#include <QtCore/QJsonArray> 
#include <QtCore/QJsonObject> 
#include <QtCore/QJsonValue> 
#include <QtCore/QJsonDocument>

#include <utils/Common.hpp>
#include <utils/UtilsDll.hpp>

class Utils_API FastRequestInfo
{
public:
    FastRequestInfo()
    {
        reset();
    } 

    FastRequestInfo(QString const& sessionId, QString const& actionId, QString const& startTime)
    {
        this->reqSessionId = sessionId;
        this->reqActionId = actionId;
        this->reqStartTime = startTime;
    } 

    FastRequestInfo(FastRequestInfo const& other)
    {
        reset(other);
    }

    ~FastRequestInfo()
    {

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

public: 
    FastRequestInfo& reset()
    {
        reqSessionId = NULL_STR;
        reqActionId = NULL_STR;
        reqStartTime = NULL_STR;

        return *this;
    }

    FastRequestInfo& reset(FastRequestInfo const& other)
    { 
        *this = other;
        return *this;
    }

    FastRequestInfo& operator=(FastRequestInfo const& other)
    {
        if (this == &other)
        {
            return *this;
        }

        reqSessionId = other.reqSessionId;
        reqActionId = other.reqActionId;  
        reqStartTime = other.reqStartTime; 

        return *this;
    }

public:
    void printMsg()
    {
        qDebug()<<QJsonDocument(toReqMsg()).toJson();
    }
    
public:
    QJsonObject& toReqHeader(QJsonObject& reqHeader)  
    {  
        reqHeader.insert("reqSessionId", QJsonValue(reqSessionId));
        reqHeader.insert("reqActionId", QJsonValue(reqActionId));
        reqHeader.insert("reqStartTime", QJsonValue(reqStartTime));

        return reqHeader;
    }

    QJsonObject toReqHeader()
    {
        QJsonObject reqHeader;
        return toReqHeader(reqHeader);
    }

    QJsonObject& toReqMsg(QJsonObject& reqMsg)
    {
        QJsonObject reqHeader; 
        toReqHeader(reqHeader);
        reqMsg.insert("header", reqHeader);
        return reqMsg;
    }

    QJsonObject toReqMsg()
    {
        QJsonObject reqMsg;
        return toReqMsg(reqMsg);
    }

    FastRequestInfo& fromReqHeader(QJsonObject const& reqHeader)
    {
        if (reqHeader.contains("reqSessionId"))
        {
            reqSessionId = reqHeader["reqSessionId"].toString(); 
        }
        if (reqHeader.contains("reqActionId"))
        {
            reqActionId = reqHeader["reqActionId"].toString(); 
        }
        if (reqHeader.contains("reqStartTime"))
        {
            reqStartTime = reqHeader["reqStartTime"].toString(); 
        }
         
        return *this;
    }

    FastRequestInfo& fromReqMsg(QJsonObject const& reqMsg)
    {
        if (!reqMsg.contains("header"))
        {
            return *this;
        }
        QJsonValue reqHeader = reqMsg["header"];
        if (!reqHeader.isObject())
        {
            return *this;
        }

        return fromReqHeader(reqHeader.toObject());
    }
    
    FastRequestInfo(QJsonObject& reqMsg)
    {
        fromReqMsg(reqMsg);
    }

private:
    QString reqSessionId;
    QString reqActionId;
    QString reqStartTime;

};


#endif


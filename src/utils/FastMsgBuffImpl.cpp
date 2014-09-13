#include <utils/FastMsgBuff.hpp> 
#include <utils/FastMsgInfo.hpp> 

#include <utils/HttpClient.hpp>

#define REQ_MSGBUFF_LOADLIST      "/think/fast/msg/loadList"  

class FastMsgInfoImpl: public FastMsgInfo
{
public: 
    virtual FastMsgInfo::MsgLevel const& getLevel() const
    {
        return _msgLevel;
    }

    virtual QString const& getId() const
    {
        return _msgId;
    }

    virtual QString const& getInfo() const
    {
        return _msgInfo;
    }

    virtual ~FastMsgInfoImpl()
    {

    }

public: 
    FastMsgInfoImpl(QString const& msgLevel, QString const& msgId, QString const& msgInfo)
    {
        this->setMsgLevel(msgLevel);

        this->_msgId = msgId;
        this->_msgInfo = msgInfo;
    }

    FastMsgInfoImpl(FastMsgInfo::MsgLevel const& msgLevel, QString const& msgId, QString const& msgInfo)
    {
        this->_msgLevel = msgLevel;
        this->_msgId = msgId;
        this->_msgInfo = msgInfo;
    }

    FastMsgInfoImpl& fromJson(QJsonObject const& jsonObj)
    {   
        this->setMsgLevel(jsonObj["level"].toString());

        this->_msgId = jsonObj["msgId"].toString(); 
        this->_msgInfo = jsonObj["msgInfo"].toString();  

        return *this;
    }

    FastMsgInfoImpl(QJsonObject const& jsonObj)
    {
        fromJson(jsonObj);
    }

    static QMap<QString, FastMsgInfo*>& fromJsons(QJsonArray const& jsons, QMap<QString, FastMsgInfo*>& objs)
    {
        objs.clear();
        for (int index = 0; index < jsons.count(); index++)
        { 
            FastMsgInfo* newMsg = new FastMsgInfoImpl(jsons.at(index).toObject());
            objs[newMsg->getId()] = newMsg;
        }

        return objs;
    }
     
    static QMap<QString, FastMsgInfo*>& fromJsons(QJsonObject const& parentJson, QMap<QString, FastMsgInfo*>& objs)
    {
        objs.clear();
        if (!parentJson.contains("msgs"))
        {
            return objs;  
        }
        QJsonValue objsValue = parentJson["msgs"].toArray();
        if (!objsValue.isArray())  
        {
            return objs;
        }

        return fromJsons(objsValue.toArray(), objs);
    }

private:
    void setMsgLevel(QString const& msgLevel)
    {
        FastMsgInfo::MsgLevel resultLevel = FastMsgInfo::Msg_FATAL;
        if (msgLevel == MSG_LEVEL_ERROR)
        {
            resultLevel = FastMsgInfo::Msg_ERROR;
        }
        else if (msgLevel == MSG_LEVEL_WARN)
        {
            resultLevel = FastMsgInfo::Msg_WARN;
        }
        else if (msgLevel == MSG_LEVEL_INFO)
        {
            resultLevel = FastMsgInfo::Msg_INFO;
        }
        else if (msgLevel == MSG_LEVEL_FATAL)
        {
            resultLevel = FastMsgInfo::Msg_FATAL;
        }

        this->_msgLevel = resultLevel;
    }

private:
    FastMsgInfo::MsgLevel _msgLevel;

    QString _msgId;
    QString _msgInfo;

};

class FastMsgBuffImpl: public FastMsgBuff 
{
public:
    virtual void reLoad()
    {
        this->_mapMsgs.clear();
        this->queryAll();
    }
    
    virtual FastMsgInfo const& getMsg(QString const& msgId) const
    {
        if (_mapMsgs.contains(msgId))
        {
            return *_mapMsgs[msgId];
        }
        
        return *_nullMsg;
    }

    virtual ~FastMsgBuffImpl()
    {

    }

    static FastMsgBuff* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new FastMsgBuffImpl();
        }

        return _instance;
    }

private:
    FastMsgBuffImpl()
    {
        this->_nullMsg = new FastMsgInfoImpl(FastMsgInfo::Msg_FATAL, QString("id_unKnown"), QString("id_unKnown"));

        this->queryAll();
    }

    void queryAll()
    {   
        QJsonObject rspMsg = httpClient().postJson(REQ_MSGBUFF_LOADLIST);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return;
        }

        FastMsgInfoImpl::fromJsons(rspMsg, _mapMsgs);
        return;
    }

private:
    QMap<QString, FastMsgInfo*> _mapMsgs;
    FastMsgInfo* _nullMsg;

private:
    static FastMsgBuff* _instance; 

};

FastMsgBuff* FastMsgBuffImpl::_instance = NULL; 

FastMsgBuff& msgBuff()
{ 
    return *(FastMsgBuffImpl::getInstance());
}  


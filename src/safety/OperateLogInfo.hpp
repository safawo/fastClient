#ifndef Think_Safety_OperateLogInfo
#define Think_Safety_OperateLogInfo

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QJsonArray> 
#include <QtCore/QJsonObject> 
#include <QtCore/QJsonValue> 
#include <QtCore/QJsonDocument>   

#include <safety/SafetyDll.hpp> 

#include <utils/Common.hpp>
  
class Safety_API OperateLogInfo
{  
public:
    OperateLogInfo()
    {
        reset();
    }

    OperateLogInfo(OperateLogInfo const& other)
    {
        userName = other.userName;
         
        subsys = other.subsys;
        operateGroup = other.operateGroup;
        operateName = other.operateName;

        operateRet = other.operateRet;
        operateRetDetail = other.operateRetDetail;

        operateObj = other.operateObj;
        operateContent = other.operateContent;
         
        userIpAddress = other.userIpAddress;
        userHostName = other.userHostName;
        operateTime = other.operateTime;

        logType = other.logType;
        serialNum = other.serialNum;
         
    }

    ~OperateLogInfo()
    {

    }

public: 
    OperateLogInfo& reset()
    {   
        userName = NULL_STR;

        subsys = NULL_STR; 
        operateGroup = NULL_STR;
        operateName = NULL_STR;

        operateRet = NULL_STR;
        operateRetDetail = NULL_STR; 
         
        operateObj = NULL_STR;
        operateContent = NULL_STR;

        userIpAddress = NULL_STR;
        userHostName = NULL_STR;
        operateTime = NULL_STR;

        logType = NULL_STR;
        serialNum = NULL_STR;
           
        return *this;
    }

    OperateLogInfo& reset(OperateLogInfo const& other)
    { 
        *this = other;
        return *this;
    }

    OperateLogInfo& operator=(OperateLogInfo const& other)
    {
        if (this == &other)
        {
            return *this;
        }

        userName = other.userName;

        subsys = other.subsys;
        operateGroup = other.operateGroup;
        operateName = other.operateName;

        operateRet = other.operateRet;
        operateRetDetail = other.operateRetDetail;

        operateObj = other.operateObj;
        operateContent = other.operateContent;

        userIpAddress = other.userIpAddress;
        userHostName = other.userHostName;
        operateTime = other.operateTime;

        logType = other.logType;
        serialNum = other.serialNum;    

        return *this;
    }

public:
    bool isNull()
    {
        if (this->userName.isEmpty())
        {
            return true;
        }

        return false;
    }

public:
    QJsonObject const& toJson(QJsonObject& jsonObj) const 
    {  
        jsonObj.insert("userName", QJsonValue(userName));

        jsonObj.insert("subsys", QJsonValue(subsys));
        jsonObj.insert("operateGroup", QJsonValue(operateGroup));
        jsonObj.insert("operateName", QJsonValue(operateName));

        jsonObj.insert("operateRet", QJsonValue(operateRet));
        jsonObj.insert("operateRetDetail", QJsonValue(operateRetDetail));

        jsonObj.insert("operateObj", QJsonValue(operateObj));
        jsonObj.insert("operateContent", QJsonValue(operateContent));
        
        jsonObj.insert("userIpAddress", QJsonValue(userIpAddress));
        jsonObj.insert("userHostName", QJsonValue(userHostName));
        jsonObj.insert("operateTime", QJsonValue(operateTime));

        jsonObj.insert("logType", QJsonValue(logType));
        jsonObj.insert("serialNum", QJsonValue(serialNum));
         
        return jsonObj;
    }

    QJsonObject toJson() const
    {
        QJsonObject jsonObj; 
        return toJson(jsonObj);
    }

    static QJsonArray const& toJsons(QList<OperateLogInfo> const& objs, QJsonArray& jsons)
    { 
        for (int index = 0; index < objs.count(); index++)
        { 
            jsons.push_back(QJsonValue(objs[index].toJson()));
        } 
        return jsons;
    }

    static QJsonArray toJsons(QList<OperateLogInfo> const& objs)
    {
        QJsonArray jsons;
        return toJsons(objs, jsons);
    } 

    OperateLogInfo& fromJson(QJsonObject const& jsonObj)
    {   
        userName = jsonObj["userName"].toString();  
         
        subsys = jsonObj["subsys"].toString();  
        operateGroup = jsonObj["operateGroup"].toString();  
        operateName = jsonObj["operateName"].toString();  
        
        operateRet = jsonObj["operateRet"].toString();  
        operateRetDetail = jsonObj["operateRetDetail"].toString();  

        operateObj = jsonObj["operateObj"].toString();  
        operateContent = jsonObj["operateContent"].toString();  

        userIpAddress = jsonObj["userIpAddress"].toString();  
        userHostName = jsonObj["userHostName"].toString();  
        operateTime = jsonObj["operateTime"].toString();  

        logType = jsonObj["logType"].toString();  
        serialNum = jsonObj["serialNum"].toString();  
         

        return *this;
    }

    OperateLogInfo(QJsonObject const& jsonObj)
    {
        fromJson(jsonObj);
    }

    static QList<OperateLogInfo>& fromJsons(QJsonArray const& jsons, QList<OperateLogInfo>& objs)
    {
        objs.clear();
        for (int index = 0; index < jsons.count(); index++)
        { 
            objs.push_back(OperateLogInfo(jsons.at(index).toObject()));
        }

        return objs;
    }

    static QList<OperateLogInfo> fromJsons(QJsonArray const& jsons)
    {
        QList<OperateLogInfo> objs;
        return fromJsons(jsons, objs);
    } 

    static QList<OperateLogInfo>& fromJsons(QJsonObject const& parentJson, QList<OperateLogInfo>& objs)
    {
        objs.clear();
        if (!parentJson.contains("logs"))
        {
            return objs;  
        }
        QJsonValue objsValue = parentJson["logs"];
        if (!objsValue.isArray())  
        {
            return objs;
        }

        return fromJsons(objsValue.toArray(), objs);
    }

    static QList<OperateLogInfo> fromJsons(QJsonObject const& parentJson)
    {
        QList<OperateLogInfo> objs;
        return fromJsons(parentJson, objs);
    }

public:  
    QString userName; 

    QString subsys;  
    QString operateGroup;
    QString operateName;

    QString operateRet;
    QString operateRetDetail;

    QString operateObj;
    QString operateContent;

    QString userIpAddress;
    QString userHostName;
    QString operateTime;

    QString logType;
    QString serialNum;

}; 


#endif





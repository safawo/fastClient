#ifndef Think_Safety_SafeOperateInfo
#define Think_Safety_SafeOperateInfo

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QJsonArray> 
#include <QtCore/QJsonObject> 
#include <QtCore/QJsonValue> 
#include <QtCore/QJsonDocument> 

#include <safety/SafetyDll.hpp>

#include <utils/Common.hpp>

class Safety_API SafeOperateInfo
{  
public:
    SafeOperateInfo()
    {
        reset();
    }

    SafeOperateInfo(SafeOperateInfo const& other)
    {
        id = other.id;
        serialId = other.serialId; 
        operateCode = other.operateCode; 

        subsys = other.subsys; 
        operateGroup = other.operateGroup;
        operateName = other.operateName;        
        operateDetail = other.operateDetail;
        operateRemark = other.operateRemark;

        isAuth = other.isAuth;
        isLog = other.isLog;

        departs = other.departs; 
        users = other.users;
        roles = other.roles;        

    }

    ~SafeOperateInfo()
    {

    }

public: 
    SafeOperateInfo& reset()
    { 
        id = NULL_STR;
        serialId = NULL_INT; 
        operateCode = NULL_STR;

        subsys = NULL_STR;
        operateGroup = NULL_STR; 
        operateName = NULL_STR;
        operateDetail = NULL_STR;
        operateRemark = NULL_STR;

        isAuth = NULL_BOOL;
        isLog = NULL_BOOL;

        departs.clear();
        users.clear();
        roles.clear(); 

        return *this;
    }

    SafeOperateInfo& reset(SafeOperateInfo const& other)
    { 
        *this = other;
        return *this;
    }

    SafeOperateInfo& operator=(SafeOperateInfo const& other)
    {
        if (this == &other)
        {
            return *this;
        }

        id = other.id;
        serialId = other.serialId; 
        operateCode = other.operateCode; 

        subsys = other.subsys; 
        operateGroup = other.operateGroup;
        operateName = other.operateName;        
        operateDetail = other.operateDetail;
        operateRemark = other.operateRemark;

        isAuth = other.isAuth;
        isLog = other.isLog;

        departs = other.departs; 
        users = other.users;
        roles = other.roles;       

        return *this;
    }

public:
    bool isNull()
    {
        if (this->id.isEmpty())
        {
            return true;
        }

        return false;
    }

public:
    QJsonObject const& toJson(QJsonObject& jsonObj) const 
    {  
        jsonObj.insert("id", QJsonValue(id));
        jsonObj.insert("serialId", QJsonValue(serialId));
        jsonObj.insert("operateCode", QJsonValue(operateCode));

        jsonObj.insert("subsys", QJsonValue(subsys));
        jsonObj.insert("operateGroup", QJsonValue(operateGroup));
        jsonObj.insert("operateName", QJsonValue(operateName));
        jsonObj.insert("operateDetail", QJsonValue(operateDetail));
        jsonObj.insert("operateRemark", QJsonValue(operateRemark));

        jsonObj.insert("isAuth", QJsonValue(isAuth));
        jsonObj.insert("isLog", QJsonValue(isLog));

        QJsonArray departsJson;
        foreach (QString depart, departs)
        {
            departsJson.push_back(QJsonValue(depart));
        } 
        jsonObj.insert("departs", QJsonValue(departsJson));

        QJsonArray usersJson;
        foreach (QString user, users)
        {
            usersJson.push_back(QJsonValue(user));
        } 
        jsonObj.insert("users", QJsonValue(usersJson));

        QJsonArray rolesJson;
        foreach (QString role, roles)
        {
            rolesJson.push_back(QJsonValue(role));
        } 
        jsonObj.insert("roles", QJsonValue(rolesJson));

        return jsonObj;
    }

    QJsonObject toJson() const
    {
        QJsonObject jsonObj; 
        return toJson(jsonObj);
    }

    static QJsonArray const& toJsons(QList<SafeOperateInfo> const& objs, QJsonArray& jsons)
    { 
        for (int index = 0; index < objs.count(); index++)
        { 
            jsons.push_back(QJsonValue(objs[index].toJson()));
        } 
        return jsons;
    }

    static QJsonArray toJsons(QList<SafeOperateInfo> const& objs)
    {
        QJsonArray jsons;
        return toJsons(objs, jsons);
    } 

    SafeOperateInfo& fromJson(QJsonObject const& jsonObj)
    {   
        id = jsonObj["id"].toString(); 
        serialId = int(jsonObj["serialId"].toDouble()); 
        operateCode = jsonObj["operateCode"].toString();  

        subsys = jsonObj["subsys"].toString();  
        operateGroup = jsonObj["operateGroup"].toString();  
        operateName = jsonObj["operateName"].toString();  
        operateDetail = jsonObj["operateDetail"].toString();  
        operateRemark = jsonObj["operateRemark"].toString();  

        isAuth = jsonObj["isAuth"].toBool();  
        isLog = jsonObj["isLog"].toBool();  

        if (jsonObj.contains("departs"))
        {
            QJsonValue departsJsonValue = jsonObj["departs"];
            QJsonArray departsJson = departsJsonValue.toArray();
            for (int index = 0; index < departsJson.count(); index++)
            { 
                departs.push_back(departsJson.at(index).toString());
            } 
        }

        if (jsonObj.contains("users"))
        {
            QJsonValue usersJsonValue = jsonObj["users"];
            QJsonArray usersJson = usersJsonValue.toArray();
            for (int index = 0; index < usersJson.count(); index++)
            { 
                users.push_back(usersJson.at(index).toString());
            } 
        }

        if (jsonObj.contains("roles"))
        {
            QJsonValue rolesJsonValue = jsonObj["roles"];
            QJsonArray rolesJson = rolesJsonValue.toArray();
            for (int index = 0; index < rolesJson.count(); index++)
            { 
                roles.push_back(rolesJson.at(index).toString());
            } 
        }

        return *this;
    }

    SafeOperateInfo(QJsonObject const& jsonObj)
    {
        fromJson(jsonObj);
    }

    static QList<SafeOperateInfo>& fromJsons(QJsonArray const& jsons, QList<SafeOperateInfo>& objs)
    {
        objs.clear();
        for (int index = 0; index < jsons.count(); index++)
        { 
            objs.push_back(SafeOperateInfo(jsons.at(index).toObject()));
        }

        return objs;
    }

    static QList<SafeOperateInfo> fromJsons(QJsonArray const& jsons)
    {
        QList<SafeOperateInfo> objs;
        return fromJsons(jsons, objs);
    } 

    static QList<SafeOperateInfo>& fromJsons(QJsonObject const& parentJson, QList<SafeOperateInfo>& objs)
    {
        objs.clear();
        if (!parentJson.contains("operates"))
        {
            return objs;  
        }
        QJsonValue objsValue = parentJson["operates"];
        if (!objsValue.isArray())  
        {
            return objs;
        }

        return fromJsons(objsValue.toArray(), objs);
    }

    static QList<SafeOperateInfo> fromJsons(QJsonObject const& parentJson)
    {
        QList<SafeOperateInfo> objs;
        return fromJsons(parentJson, objs);
    }

public:  
    QString id;
    int serialId; 
    QString operateCode; 

    QString subsys;
    QString operateGroup;
    QString operateName;
    QString operateDetail;
    QString operateRemark;

    bool isAuth;
    bool isLog;

    QStringList departs; 
    QStringList users;
    QStringList roles; 

}; 


#endif


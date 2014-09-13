#ifndef Think_Safety_SafeRoleAllocInfo
#define Think_Safety_SafeRoleAllocInfo

#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtCore/QJsonDocument>

#include <utils/Common.hpp>

#include <safety/SafetyDll.hpp>

class Safety_API SafeRoleAllocInfo
{
public:
    SafeRoleAllocInfo()
    {
        reset();
    } 

    SafeRoleAllocInfo(SafeRoleAllocInfo const& other)
    {   
        roleId = other.roleId;
        userId = other.userId;
    }
     
    SafeRoleAllocInfo(QString const& newRoleId, QString const& newUserId)
    :roleId(newRoleId), userId(newUserId)
    {

    }
     
    ~SafeRoleAllocInfo()
    {

    }


public: 
    SafeRoleAllocInfo& reset()
    { 
        roleId = NULL_QSTR;
        userId = NULL_QSTR;

        return *this;
    }

    SafeRoleAllocInfo& reset(SafeRoleAllocInfo const& other)
    { 
        *this = other;
        return *this;
    }

    SafeRoleAllocInfo& operator=(SafeRoleAllocInfo const& other)
    {
        if (this == &other)
        {
            return *this;
        }

        roleId = other.roleId;
        userId = other.userId;

        return *this;
    }

public:
    bool isNull() const
    {
        if (this->roleId.isEmpty() || this->userId.isEmpty())
        {
            return true;
        }

        return false;
    }

    QString getId() const
    {
        return getId(roleId, userId);
    }

    static QString getId(QString const& roleId, QString const& userId)
    {
        QString allocId = roleId;
        allocId.append(":");
        allocId.append(userId);

        return allocId;
    }

public:
    QJsonObject const& toJson(QJsonObject& jsonObj) const  
    {   
        jsonObj.insert("roleId", QJsonValue(roleId));
        jsonObj.insert("userId", QJsonValue(userId));

        return jsonObj;
    }

    QJsonObject toJson() const
    {
        QJsonObject jsonObj; 
        return toJson(jsonObj);
    }

    static QJsonArray const& toJsons(QList<SafeRoleAllocInfo> const& objs, QJsonArray& jsons)
    { 
        for (int index = 0; index < objs.count(); index++)
        { 
            jsons.push_back(QJsonValue(objs[index].toJson()));
        } 
        return jsons;
    }

    static QJsonArray toJsons(QList<SafeRoleAllocInfo> const& objs)
    {
        QJsonArray jsons;
        return toJsons(objs, jsons);
    } 

    SafeRoleAllocInfo const& fromJson(QJsonObject const& jsonObj)
    {   
        roleId = jsonObj["roleId"].toString(); 
        userId = jsonObj["userId"].toString(); 

        return *this;
    }

    SafeRoleAllocInfo(QJsonObject const& jsonObj)
    {
        fromJson(jsonObj);
    }


    static QList<SafeRoleAllocInfo>& fromJsons(QJsonArray const& jsons, QList<SafeRoleAllocInfo>& objs)
    {
        objs.clear();
        for (int index = 0; index < jsons.count(); index++)
        { 
            objs.push_back(SafeRoleAllocInfo(jsons.at(index).toObject()));
        }

        return objs;
    }

    static QList<SafeRoleAllocInfo> fromJsons(QJsonArray const& jsons)
    {
        QList<SafeRoleAllocInfo> objs;
        return fromJsons(jsons, objs);
    } 

    static QList<SafeRoleAllocInfo>& fromJsons(QJsonObject const& parentJson, QList<SafeRoleAllocInfo>& objs)
    {
        objs.clear();
        
        if (!parentJson.contains("allocs"))
        {
            return objs;  
        }

        QJsonValue objsValue = parentJson["allocs"];
        if (!objsValue.isArray())  
        {
            return objs;
        }

        return fromJsons(objsValue.toArray(), objs);
    }

    static QList<SafeRoleAllocInfo> fromJsons(QJsonObject const& parentJson)
    {
        QList<SafeRoleAllocInfo> objs;
        return fromJsons(parentJson, objs);
    }

public:
    QString roleId;
    QString userId;

}; 


#endif


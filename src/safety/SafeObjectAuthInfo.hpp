#ifndef Think_Safety_SafeObjectAuthInfo
#define Think_Safety_SafeObjectAuthInfo

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

class Safety_API SafeObjectAuthInfo
{
public:
    SafeObjectAuthInfo()
    {
        reset();
    } 

    SafeObjectAuthInfo(SafeObjectAuthInfo const& other)
    {   
        objectId = other.objectId;
        roleId = other.roleId;
    }

    SafeObjectAuthInfo(QString const& newObjectId, QString const& newRoleId)
    :objectId(newObjectId), roleId(newRoleId)
    {

    }

    ~SafeObjectAuthInfo()
    {

    }

public: 
    SafeObjectAuthInfo& reset()
    { 
        objectId = NULL_QSTR;
        roleId = NULL_QSTR;

        return *this;
    }

    SafeObjectAuthInfo& reset(SafeObjectAuthInfo const& other)
    { 
        *this = other;
        return *this;
    }

    SafeObjectAuthInfo& operator=(SafeObjectAuthInfo const& other)
    {
        if (this == &other)
        {
            return *this;
        }

        objectId = other.objectId;
        roleId = other.roleId;

        return *this;
    }

public:
    bool isNull() const
    {
        if (this->objectId.isEmpty() || this->roleId.isEmpty())
        {
            return true;
        }

        return false;
    }

    QString getId() const
    {
        return getId(objectId, roleId);
    }

    static QString getId(QString const& objectId, QString const& roleId) 
    {
        QString authId = objectId;
        authId.append(":");
        authId.append(roleId);

        return authId;
    }

public:
    QJsonObject const& toJson(QJsonObject& jsonObj) const  
    {   
        jsonObj.insert("objectId", QJsonValue(objectId));
        jsonObj.insert("roleId", QJsonValue(roleId));

        return jsonObj;
    }

    QJsonObject toJson() const
    {
        QJsonObject jsonObj; 
        return toJson(jsonObj);
    }

    static QJsonArray const& toJsons(QList<SafeObjectAuthInfo> const& objs, QJsonArray& jsons)
    { 
        for (int index = 0; index < objs.count(); index++)
        { 
            jsons.push_back(QJsonValue(objs[index].toJson()));
        } 
        return jsons;
    }

    static QJsonArray toJsons(QList<SafeObjectAuthInfo> const& objs)
    {
        QJsonArray jsons;
        return toJsons(objs, jsons);
    } 

    SafeObjectAuthInfo const& fromJson(QJsonObject const& jsonObj)
    {   
        objectId = jsonObj["objectId"].toString(); 
        roleId = jsonObj["roleId"].toString(); 

        return *this;
    }

    SafeObjectAuthInfo(QJsonObject const& jsonObj)
    {
        fromJson(jsonObj);
    }


    static QList<SafeObjectAuthInfo>& fromJsons(QJsonArray const& jsons, QList<SafeObjectAuthInfo>& objs)
    {
        objs.clear();
        for (int index = 0; index < jsons.count(); index++)
        { 
            objs.push_back(SafeObjectAuthInfo(jsons.at(index).toObject()));
        }

        return objs;
    }

    static QList<SafeObjectAuthInfo> fromJsons(QJsonArray const& jsons)
    {
        QList<SafeObjectAuthInfo> objs;
        return fromJsons(jsons, objs);
    } 

    static QList<SafeObjectAuthInfo>& fromJsons(QJsonObject const& parentJson, QList<SafeObjectAuthInfo>& objs)
    {
        objs.clear();

        if (!parentJson.contains("auths"))
        {
            return objs;  
        }

        QJsonValue objsValue = parentJson["auths"];
        if (!objsValue.isArray())  
        {
            return objs;
        }

        return fromJsons(objsValue.toArray(), objs);
    }

    static QList<SafeObjectAuthInfo> fromJsons(QJsonObject const& parentJson)
    {
        QList<SafeObjectAuthInfo> objs;
        return fromJsons(parentJson, objs);
    }

public:
    QString objectId;
    QString roleId;

}; 


#endif


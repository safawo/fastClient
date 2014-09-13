#ifndef Think_Safety_SafeOperateAuthInfo
#define Think_Safety_SafeOperateAuthInfo

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

class Safety_API SafeOperateAuthInfo
{
public:
    SafeOperateAuthInfo()
    {
        reset();
    } 

    SafeOperateAuthInfo(SafeOperateAuthInfo const& other)
    {   
        operateId = other.operateId;
        roleId = other.roleId;
    }

    SafeOperateAuthInfo(QString const& newOperateId, QString const& newRoleId)
    :operateId(newOperateId), roleId(newRoleId)
    {

    }
     
    ~SafeOperateAuthInfo()
    {

    }

public: 
    SafeOperateAuthInfo& reset()
    { 
        operateId = NULL_QSTR;
        roleId = NULL_QSTR;

        return *this;
    }

    SafeOperateAuthInfo& reset(SafeOperateAuthInfo const& other)
    { 
        *this = other;
        return *this;
    }

    SafeOperateAuthInfo& operator=(SafeOperateAuthInfo const& other)
    {
        if (this == &other)
        {
            return *this;
        }

        operateId = other.operateId;
        roleId = other.roleId;

        return *this;
    }

public:
    bool isNull() const
    {
        if (this->operateId.isEmpty() || this->roleId.isEmpty())
        {
            return true;
        }

        return false;
    }

    QString getId() const
    {
        return getId(operateId, roleId);
    }

    static QString getId(QString const& operateId, QString const& roleId)
    {
        QString authId = operateId;
        authId.append(":");
        authId.append(roleId);

        return authId;
    }

public:
    QJsonObject const& toJson(QJsonObject& jsonObj) const  
    {   
        jsonObj.insert("operateId", QJsonValue(operateId));
        jsonObj.insert("roleId", QJsonValue(roleId));

        return jsonObj;
    }

    QJsonObject toJson() const
    {
        QJsonObject jsonObj; 
        return toJson(jsonObj);
    }

    static QJsonArray const& toJsons(QList<SafeOperateAuthInfo> const& objs, QJsonArray& jsons)
    { 
        for (int index = 0; index < objs.count(); index++)
        { 
            jsons.push_back(QJsonValue(objs[index].toJson()));
        } 
        return jsons;
    }

    static QJsonArray toJsons(QList<SafeOperateAuthInfo> const& objs)
    {
        QJsonArray jsons;
        return toJsons(objs, jsons);
    } 

    SafeOperateAuthInfo const& fromJson(QJsonObject const& jsonObj)
    {   
        operateId = jsonObj["operateId"].toString(); 
        roleId = jsonObj["roleId"].toString(); 

        return *this;
    }

    SafeOperateAuthInfo(QJsonObject const& jsonObj)
    {
        fromJson(jsonObj);
    }


    static QList<SafeOperateAuthInfo>& fromJsons(QJsonArray const& jsons, QList<SafeOperateAuthInfo>& objs)
    {
        objs.clear();
        for (int index = 0; index < jsons.count(); index++)
        { 
            objs.push_back(SafeOperateAuthInfo(jsons.at(index).toObject()));
        }

        return objs;
    }

    static QList<SafeOperateAuthInfo> fromJsons(QJsonArray const& jsons)
    {
        QList<SafeOperateAuthInfo> objs;
        return fromJsons(jsons, objs);
    } 

    static QList<SafeOperateAuthInfo>& fromJsons(QJsonObject const& parentJson, QList<SafeOperateAuthInfo>& objs)
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

    static QList<SafeOperateAuthInfo> fromJsons(QJsonObject const& parentJson)
    {
        QList<SafeOperateAuthInfo> objs;
        return fromJsons(parentJson, objs);
    }

public:
    QString operateId;
    QString roleId;

}; 


#endif


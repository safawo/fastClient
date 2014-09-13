#ifndef Think_Safety_SafeObjectInfo
#define Think_Safety_SafeObjectInfo

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QJsonArray> 
#include <QtCore/QJsonObject> 
#include <QtCore/QJsonValue> 
#include <QtCore/QJsonDocument> 

#include <safety/SafetyDll.hpp>

#include <utils/Common.hpp>

class Safety_API SafeObjectInfo
{  
public:
    SafeObjectInfo()
    {
        reset();
    }

    SafeObjectInfo(SafeObjectInfo const& other)
    {
        id = other.id;
        serialId = other.serialId; 
        objectType = other.objectType; 
        parentPath = other.parentPath; 

        objectName = other.objectName;
        objectText = other.objectText;        
        objectImage = other.objectImage;
        objectRemark = other.objectRemark;

        departs = other.departs; 
        users = other.users;
        roles = other.roles;        

    }

    ~SafeObjectInfo()
    {

    }

public: 
    SafeObjectInfo& reset()
    { 
        id = NULL_STR;
        serialId = NULL_INT; 
        objectType = NULL_STR;
        parentPath = NULL_STR;

        objectName = NULL_STR;
        objectText = NULL_STR; 
        objectImage = NULL_STR;
        objectRemark = NULL_STR;

        departs.clear();
        users.clear();
        roles.clear(); 

        return *this;
    }

    SafeObjectInfo& reset(SafeObjectInfo const& other)
    { 
        *this = other;
        return *this;
    }

    SafeObjectInfo& operator=(SafeObjectInfo const& other)
    {
        if (this == &other)
        {
            return *this;
        }

        id = other.id;
        serialId = other.serialId; 
        objectType = other.objectType; 
        parentPath = other.parentPath; 

        objectName = other.objectName;
        objectText = other.objectText;        
        objectImage = other.objectImage;
        objectRemark = other.objectRemark;

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
        jsonObj.insert("objectType", QJsonValue(objectType));
        jsonObj.insert("parentPath", QJsonValue(parentPath));

        jsonObj.insert("objectName", QJsonValue(objectName));
        jsonObj.insert("objectText", QJsonValue(objectText));
        jsonObj.insert("objectImage", QJsonValue(objectImage));
        jsonObj.insert("objectRemark", QJsonValue(objectRemark));

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

    static QJsonArray const& toJsons(QList<SafeObjectInfo> const& objs, QJsonArray& jsons)
    { 
        for (int index = 0; index < objs.count(); index++)
        { 
            jsons.push_back(QJsonValue(objs[index].toJson()));
        } 
        return jsons;
    }

    static QJsonArray toJsons(QList<SafeObjectInfo> const& objs)
    {
        QJsonArray jsons;
        return toJsons(objs, jsons);
    } 

    SafeObjectInfo& fromJson(QJsonObject const& jsonObj)
    {   
        id = jsonObj["id"].toString(); 
        serialId = int(jsonObj["serialId"].toDouble()); 
        objectType = jsonObj["objectType"].toString();  
        parentPath = jsonObj["parentPath"].toString();  

        objectName = jsonObj["objectName"].toString();  
        objectText = jsonObj["objectText"].toString();  
        objectImage = jsonObj["objectImage"].toString();  
        objectRemark = jsonObj["objectRemark"].toString();  

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

    SafeObjectInfo(QJsonObject const& jsonObj)
    {
        fromJson(jsonObj);
    }

    static QList<SafeObjectInfo>& fromJsons(QJsonArray const& jsons, QList<SafeObjectInfo>& objs)
    {
        objs.clear();
        for (int index = 0; index < jsons.count(); index++)
        { 
            objs.push_back(SafeObjectInfo(jsons.at(index).toObject()));
        }

        return objs;
    }

    static QList<SafeObjectInfo> fromJsons(QJsonArray const& jsons)
    {
        QList<SafeObjectInfo> objs;
        return fromJsons(jsons, objs);
    } 

    static QList<SafeObjectInfo>& fromJsons(QJsonObject const& parentJson, QList<SafeObjectInfo>& objs)
    {
        objs.clear();
        if (!parentJson.contains("objects"))
        {
            return objs;  
        }
        QJsonValue objsValue = parentJson["objects"];
        if (!objsValue.isArray())  
        {
            return objs;
        }

        return fromJsons(objsValue.toArray(), objs);
    }

    static QList<SafeObjectInfo> fromJsons(QJsonObject const& parentJson)
    {
        QList<SafeObjectInfo> objs;
        return fromJsons(parentJson, objs);
    }

public:  
    QString id;
    int serialId; 
    QString objectType;
    QString parentPath;

    QString objectName;
    QString objectText;
    QString objectImage;
    QString objectRemark;

    QStringList departs; 
    QStringList users;
    QStringList roles; 
    
}; 


#endif


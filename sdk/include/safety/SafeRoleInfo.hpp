#ifndef Think_Safety_SafeRoleInfo
#define Think_Safety_SafeRoleInfo

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QJsonArray> 
#include <QtCore/QJsonObject> 
#include <QtCore/QJsonValue> 
#include <QtCore/QJsonDocument> 

#include <safety/SafetyDll.hpp>

#include <utils/Common.hpp>

class Safety_API SafeRoleInfo
{  
public:
    SafeRoleInfo()
    {
        reset();
    }

    SafeRoleInfo(SafeRoleInfo const& other)
    {
        id = other.id;
        name = other.name; 
        roleDetail = other.roleDetail; 
        roleRemark = other.roleRemark; 

        isUser = other.isUser;
        isDepart = other.isDepart;        
        defaultSafeObject = other.defaultSafeObject; 

        departs = other.departs;
        users = other.users;        
        operates = other.operates;
        objects = other.objects;

    }

    ~SafeRoleInfo()
    {

    }

public: 
    SafeRoleInfo& reset()
    { 
        id = NULL_STR;
        name = NULL_STR; 
        roleDetail = NULL_STR;
        roleRemark = NULL_STR;

        isUser = NULL_BOOL;
        isDepart = NULL_BOOL;
        defaultSafeObject = NULL_STR;

        departs.clear();
        users.clear();
        operates.clear();
        objects.clear();

        return *this;
    }

    SafeRoleInfo& reset(SafeRoleInfo const& other)
    { 
        *this = other;
        return *this;
    }

    SafeRoleInfo& operator=(SafeRoleInfo const& other)
    {
        if (this == &other)
        {
            return *this;
        }

        id = other.id;
        name = other.name; 
        roleDetail = other.roleDetail; 
        roleRemark = other.roleRemark; 

        isUser = other.isUser;
        isDepart = other.isDepart;        
        defaultSafeObject = other.defaultSafeObject; 

        departs = other.departs;
        users = other.users;        
        operates = other.operates;
        objects = other.objects;

        return *this;
    }

public:
    bool isNull() const
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
        jsonObj.insert("name", QJsonValue(name));
        jsonObj.insert("roleDetail", QJsonValue(roleDetail));
        jsonObj.insert("roleRemark", QJsonValue(roleRemark));

        jsonObj.insert("isUser", QJsonValue(isUser));
        jsonObj.insert("isDepart", QJsonValue(isDepart));
        jsonObj.insert("defaultSafeObject", QJsonValue(defaultSafeObject)); 

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

        QJsonArray operatesJson;
        foreach (QString operate, operates)
        {
            operatesJson.push_back(QJsonValue(operate));
        } 
        jsonObj.insert("operates", QJsonValue(operatesJson));

        QJsonArray objectsJson;
        foreach (QString object, objects)
        {
            objectsJson.push_back(QJsonValue(object));
        } 
        jsonObj.insert("objects", QJsonValue(objectsJson));


        return jsonObj;
    }

    QJsonObject toJson() const
    {
        QJsonObject jsonObj; 
        return toJson(jsonObj);
    }

    static QJsonArray const& toJsons(QList<SafeRoleInfo> const& objs, QJsonArray& jsons)
    { 
        for (int index = 0; index < objs.count(); index++)
        { 
            jsons.push_back(QJsonValue(objs[index].toJson()));
        } 
        return jsons;
    }

    static QJsonArray toJsons(QList<SafeRoleInfo> const& objs)
    {
        QJsonArray jsons;
        return toJsons(objs, jsons);
    } 

    SafeRoleInfo& fromJson(QJsonObject const& jsonObj)
    {   
        id = jsonObj["id"].toString(); 
        name = jsonObj["name"].toString(); 
        roleDetail = jsonObj["roleDetail"].toString();  
        roleRemark = jsonObj["roleRemark"].toString();  

        isUser = jsonObj["isUser"].toBool();  
        isDepart = jsonObj["isDepart"].toBool();  
        defaultSafeObject = jsonObj["defaultSafeObject"].toString();   

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

        if (jsonObj.contains("operates"))
        {
            QJsonValue operatesJsonValue = jsonObj["operates"];
            QJsonArray operatesJson = operatesJsonValue.toArray();
            for (int index = 0; index < operatesJson.count(); index++)
            { 
                operates.push_back(operatesJson.at(index).toString());
            } 
        }

        if (jsonObj.contains("objects"))
        {
            QJsonValue objectsJsonValue = jsonObj["objects"];
            QJsonArray objectsJson = objectsJsonValue.toArray();
            for (int index = 0; index < objectsJson.count(); index++)
            { 
                objects.push_back(objectsJson.at(index).toString());
            } 
        }
        return *this;
    }

    SafeRoleInfo(QJsonObject const& jsonObj)
    {
        fromJson(jsonObj);
    }

    static QList<SafeRoleInfo>& fromJsons(QJsonArray const& jsons, QList<SafeRoleInfo>& objs)
    {
        objs.clear();
        for (int index = 0; index < jsons.count(); index++)
        { 
            objs.push_back(SafeRoleInfo(jsons.at(index).toObject()));
        }

        return objs;
    }

    static QList<SafeRoleInfo> fromJsons(QJsonArray const& jsons)
    {
        QList<SafeRoleInfo> objs;
        return fromJsons(jsons, objs);
    } 

    static QList<SafeRoleInfo>& fromJsons(QJsonObject const& parentJson, QList<SafeRoleInfo>& objs)
    {
        objs.clear();
        if (!parentJson.contains("roles"))
        {
            return objs;  
        }
        QJsonValue objsValue = parentJson["roles"];
        if (!objsValue.isArray())  
        {
            return objs;
        }

        return fromJsons(objsValue.toArray(), objs);
    }

    static QList<SafeRoleInfo> fromJsons(QJsonObject const& parentJson)
    {
        QList<SafeRoleInfo> objs;
        return fromJsons(parentJson, objs);
    }

public:  
    QString id; 
    QString name; 
    QString roleDetail;
    QString roleRemark;

    bool isUser;
    bool isDepart;
    QString defaultSafeObject;

    QStringList departs; 
    QStringList users;
    QStringList operates;
    QStringList objects; 

}; 


#endif


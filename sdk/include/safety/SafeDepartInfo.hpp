#ifndef Think_Safety_SafeDepartInfo
#define Think_Safety_SafeDepartInfo

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QJsonArray> 
#include <QtCore/QJsonObject> 
#include <QtCore/QJsonValue> 
#include <QtCore/QJsonDocument> 

#include <safety/SafetyDll.hpp>

#include <utils/Common.hpp>

class Safety_API SafeDepartInfo
{  
public:
    SafeDepartInfo()
    {
        reset();
    }

    SafeDepartInfo(SafeDepartInfo const& other)
    {
        id = other.id;
        serialId = other.serialId; 
        parentPath = other.parentPath; 

        departName = other.departName;
        departText = other.departText;        
        departImage = other.departImage;
        departRemark = other.departRemark;
           
        users = other.users;
        roles = other.roles;        
        operates = other.operates;
        objects = other.objects;

    }

    ~SafeDepartInfo()
    {

    }

public: 
    SafeDepartInfo& reset()
    { 
        id = NULL_STR;
        serialId = NULL_INT; 
        parentPath = NULL_STR;
        
        departName = NULL_STR;
        departText = NULL_STR; 
        departImage = NULL_STR;
        departRemark = NULL_STR;

        users.clear();
        roles.clear();
        operates.clear();
        objects.clear();

        return *this;
    }

    SafeDepartInfo& reset(SafeDepartInfo const& other)
    { 
        *this = other;
        return *this;
    }

    SafeDepartInfo& operator=(SafeDepartInfo const& other)
    {
        if (this == &other)
        {
            return *this;
        }

        id = other.id;
        serialId = other.serialId; 
        parentPath = other.parentPath; 

        departName = other.departName;
        departText = other.departText;        
        departImage = other.departImage;
        departRemark = other.departRemark;

        users = other.users;
        roles = other.roles;        
        operates = other.operates;
        objects = other.objects;

        return *this;
    }

public:
    QJsonObject const& toJson(QJsonObject& jsonObj) const 
    {  
        jsonObj.insert("id", QJsonValue(id));
        jsonObj.insert("serialId", QJsonValue(serialId));
        jsonObj.insert("parentPath", QJsonValue(parentPath));

        jsonObj.insert("departName", QJsonValue(departName));
        jsonObj.insert("departText", QJsonValue(departText));
        jsonObj.insert("departImage", QJsonValue(departImage));
        jsonObj.insert("departRemark", QJsonValue(departRemark));

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

    static QJsonArray const& toJsons(QList<SafeDepartInfo> const& objs, QJsonArray& jsons)
    { 
        for (int index = 0; index < objs.count(); index++)
        { 
            jsons.push_back(QJsonValue(objs[index].toJson()));
        } 
        return jsons;
    }

    static QJsonArray toJsons(QList<SafeDepartInfo> const& objs)
    {
        QJsonArray jsons;
        return toJsons(objs, jsons);
    } 

    SafeDepartInfo& fromJson(QJsonObject const& jsonObj)
    {   
        id = jsonObj["id"].toString(); 
        serialId = int(jsonObj["serialId"].toDouble()); 
        parentPath = jsonObj["parentPath"].toString();  

        departName = jsonObj["departName"].toString();  
        departText = jsonObj["departText"].toString();  
        departImage = jsonObj["departImage"].toString();  
        departRemark = jsonObj["departRemark"].toString();  

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

    SafeDepartInfo(QJsonObject const& jsonObj)
    {
        fromJson(jsonObj);
    }

    static QList<SafeDepartInfo>& fromJsons(QJsonArray const& jsons, QList<SafeDepartInfo>& objs)
    {
        objs.clear();
        for (int index = 0; index < jsons.count(); index++)
        { 
            objs.push_back(SafeDepartInfo(jsons.at(index).toObject()));
        }

        return objs;
    }

    static QList<SafeDepartInfo> fromJsons(QJsonArray const& jsons)
    {
        QList<SafeDepartInfo> objs;
        return fromJsons(jsons, objs);
    } 

    static QList<SafeDepartInfo>& fromJsons(QJsonObject const& parentJson, QList<SafeDepartInfo>& objs)
    {
        objs.clear();
        if (!parentJson.contains("departs"))
        {
            return objs;  
        }
        QJsonValue objsValue = parentJson["departs"];
        if (!objsValue.isArray())  
        {
            return objs;
        }

        return fromJsons(objsValue.toArray(), objs);
    }

    static QList<SafeDepartInfo> fromJsons(QJsonObject const& parentJson)
    {
        QList<SafeDepartInfo> objs;
        return fromJsons(parentJson, objs);
    }

public:  
    QString id;
    int serialId; 
    QString parentPath;

    QString departName;
    QString departText;
    QString departImage;
    QString departRemark;

    QStringList users;
    QStringList roles; 
    QStringList operates;
    QStringList objects; 

}; 


#endif


#ifndef Think_Safety_SafeUserInfo
#define Think_Safety_SafeUserInfo

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QJsonArray> 
#include <QtCore/QJsonObject> 
#include <QtCore/QJsonValue> 
#include <QtCore/QJsonDocument> 

#include <safety/SafetyDll.hpp>

#include <utils/Common.hpp>
#include <utils/Utils.hpp>

class Safety_API SafeUserInfo
{  
public:
    SafeUserInfo()
    {
        reset();
    }

    SafeUserInfo(SafeUserInfo const& other)
    {
        id = other.id;
        departId = other.departId; 
        name = other.name; 
        password = other.password; 

        employeeId = other.employeeId;
        nickName = other.nickName;        
        firstName = other.firstName;
        lastName = other.lastName;

        mobile = other.mobile;        
        email = other.email;
        userRemark = other.userRemark;

        isLock = other.isLock;
        lockReason = other.lockReason;        
        isForever = other.isForever;
        accountExpired = other.accountExpired;
         
        roles = other.roles;        
        operates = other.operates;
        objects = other.objects;

    }

    ~SafeUserInfo()
    {

    }

public: 
    SafeUserInfo& reset()
    { 
        id = NULL_STR;
        departId = NULL_STR; 
        name = NULL_STR;
        password = NULL_STR;

        employeeId = NULL_STR;
        nickName = NULL_STR; 
        firstName = NULL_STR;
        lastName = NULL_STR;
        
        mobile = NULL_STR; 
        email = NULL_STR;
        userRemark = NULL_STR;
         
        isLock = NULL_BOOL;
        lockReason = NULL_STR; 
        isForever = NULL_BOOL;
        accountExpired = NULL_STR;

        roles.clear();
        operates.clear();
        objects.clear();

        return *this;
    }

    SafeUserInfo& reset(SafeUserInfo const& other)
    { 
        *this = other;
        return *this;
    }

    SafeUserInfo& operator=(SafeUserInfo const& other)
    {
        if (this == &other)
        {
            return *this;
        }

        id = other.id;
        departId = other.departId; 
        name = other.name; 
        password = other.password; 

        employeeId = other.employeeId;
        nickName = other.nickName;        
        firstName = other.firstName;
        lastName = other.lastName;

        mobile = other.mobile;        
        email = other.email;
        userRemark = other.userRemark;

        isLock = other.isLock;
        lockReason = other.lockReason;        
        isForever = other.isForever;
        accountExpired = other.accountExpired;

        roles = other.roles;        
        operates = other.operates;
        objects = other.objects;

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
        jsonObj.insert("departId", QJsonValue(departId));
        jsonObj.insert("name", QJsonValue(name));

        jsonObj.insert("password", QJsonValue(utils().password(password)));
         
        jsonObj.insert("employeeId", QJsonValue(employeeId));
        jsonObj.insert("nickName", QJsonValue(nickName));
        jsonObj.insert("firstName", QJsonValue(firstName));
        jsonObj.insert("lastName", QJsonValue(lastName));

        jsonObj.insert("mobile", QJsonValue(mobile));
        jsonObj.insert("email", QJsonValue(email));
        jsonObj.insert("userRemark", QJsonValue(userRemark));

        jsonObj.insert("isLock", QJsonValue(isLock));
        jsonObj.insert("lockReason", QJsonValue(lockReason));
        jsonObj.insert("isForever", QJsonValue(isForever));
        jsonObj.insert("accountExpired", QJsonValue(accountExpired));
         
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

    static QJsonArray const& toJsons(QList<SafeUserInfo> const& objs, QJsonArray& jsons)
    { 
        for (int index = 0; index < objs.count(); index++)
        { 
            jsons.push_back(QJsonValue(objs[index].toJson()));
        } 
        return jsons;
    }

    static QJsonArray toJsons(QList<SafeUserInfo> const& objs)
    {
        QJsonArray jsons;
        return toJsons(objs, jsons);
    } 

    SafeUserInfo& fromJson(QJsonObject const& jsonObj)
    {   
        id = jsonObj["id"].toString(); 
        departId = jsonObj["departId"].toString(); 
        name = jsonObj["name"].toString();  
        password = jsonObj["password"].toString();  

        employeeId = jsonObj["employeeId"].toString();  
        nickName = jsonObj["nickName"].toString();  
        firstName = jsonObj["firstName"].toString();  
        lastName = jsonObj["lastName"].toString();  

        mobile = jsonObj["mobile"].toString();  
        email = jsonObj["email"].toString();  
        userRemark = jsonObj["userRemark"].toString();  
        
        isLock = jsonObj["isLock"].toBool();
        lockReason = jsonObj["lockReason"].toString();  
        isForever = jsonObj["isForever"].toBool();  
        accountExpired = jsonObj["accountExpired"].toString();  
         
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

    SafeUserInfo(QJsonObject const& jsonObj)
    {
        fromJson(jsonObj);
    }

    static QList<SafeUserInfo>& fromJsons(QJsonArray const& jsons, QList<SafeUserInfo>& objs)
    {
        objs.clear();
        for (int index = 0; index < jsons.count(); index++)
        { 
            objs.push_back(SafeUserInfo(jsons.at(index).toObject()));
        }

        return objs;
    }

    static QList<SafeUserInfo> fromJsons(QJsonArray const& jsons)
    {
        QList<SafeUserInfo> objs;
        return fromJsons(jsons, objs);
    } 

    static QList<SafeUserInfo>& fromJsons(QJsonObject const& parentJson, QList<SafeUserInfo>& objs)
    {
        objs.clear();
        if (!parentJson.contains("users"))
        {
            return objs;  
        }
        QJsonValue objsValue = parentJson["users"];
        if (!objsValue.isArray())  
        {
            return objs;
        }

        return fromJsons(objsValue.toArray(), objs);
    }

    static QList<SafeUserInfo> fromJsons(QJsonObject const& parentJson)
    {
        QList<SafeUserInfo> objs;
        return fromJsons(parentJson, objs);
    }

public:  
    QString id; 
    QString departId;
    QString name;
    QString password;

    QString employeeId;
    QString nickName;
    QString firstName;
    QString lastName;

    QString mobile;
    QString email;
    QString userRemark;


    bool isLock;
    QString lockReason;
    bool isForever;
    QString accountExpired;
     
    QStringList roles; 
    QStringList operates;
    QStringList objects; 

}; 


#endif


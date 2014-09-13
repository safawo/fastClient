#ifndef Think_Safety_SafeSubSysInfo
#define Think_Safety_SafeSubSysInfo

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QJsonArray> 
#include <QtCore/QJsonObject> 
#include <QtCore/QJsonValue> 
#include <QtCore/QJsonDocument> 

#include <safety/SafetyDll.hpp>

#include <utils/Common.hpp>

class Safety_API SafeSubSysInfo
{  
public:
    SafeSubSysInfo()
    {
        reset();
    }

    SafeSubSysInfo(SafeSubSysInfo const& other)
    {
        id = other.id;
        name = other.name;  
    }

    ~SafeSubSysInfo()
    {

    }

public: 
    SafeSubSysInfo& reset()
    { 
        id = NULL_STR;
        name = NULL_STR;   

        return *this;
    }

    SafeSubSysInfo& reset(SafeSubSysInfo const& other)
    { 
        *this = other;
        return *this;
    }

    SafeSubSysInfo& operator=(SafeSubSysInfo const& other)
    {
        if (this == &other)
        {
            return *this;
        }

        id = other.id;
        name = other.name;  

        return *this;
    }

public:
    QJsonObject const& toJson(QJsonObject& jsonObj) const 
    {  
        jsonObj.insert("id", QJsonValue(id));
        jsonObj.insert("name", QJsonValue(name)); 
 
        return jsonObj;
    }

    QJsonObject toJson() const
    {
        QJsonObject jsonObj; 
        return toJson(jsonObj);
    }

    static QJsonArray const& toJsons(QList<SafeSubSysInfo> const& objs, QJsonArray& jsons)
    { 
        for (int index = 0; index < objs.count(); index++)
        { 
            jsons.push_back(QJsonValue(objs[index].toJson()));
        } 
        return jsons;
    }

    static QJsonArray toJsons(QList<SafeSubSysInfo> const& objs)
    {
        QJsonArray jsons;
        return toJsons(objs, jsons);
    } 

    SafeSubSysInfo& fromJson(QJsonObject const& jsonObj)
    {   
        id = jsonObj["id"].toString();  
        name = jsonObj["name"].toString();  
         
        return *this;
    }

    SafeSubSysInfo(QJsonObject const& jsonObj)
    {
        fromJson(jsonObj);
    }

    static QList<SafeSubSysInfo>& fromJsons(QJsonArray const& jsons, QList<SafeSubSysInfo>& objs)
    {
        objs.clear();
        for (int index = 0; index < jsons.count(); index++)
        { 
            objs.push_back(SafeSubSysInfo(jsons.at(index).toObject()));
        }

        return objs;
    }

    static QList<SafeSubSysInfo> fromJsons(QJsonArray const& jsons)
    {
        QList<SafeSubSysInfo> objs;
        return fromJsons(jsons, objs);
    } 

    static QList<SafeSubSysInfo>& fromJsons(QJsonObject const& parentJson, QList<SafeSubSysInfo>& objs)
    {
        objs.clear();
        if (!parentJson.contains("subSyss"))
        {
            return objs;  
        }
        QJsonValue objsValue = parentJson["subSyss"];
        if (!objsValue.isArray())  
        {
            return objs;
        }

        return fromJsons(objsValue.toArray(), objs);
    }

    static QList<SafeSubSysInfo> fromJsons(QJsonObject const& parentJson)
    {
        QList<SafeSubSysInfo> objs;
        return fromJsons(parentJson, objs);
    }

public:  
    QString id; 
    QString name; 
}; 


#endif


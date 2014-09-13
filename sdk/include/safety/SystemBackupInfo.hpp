#ifndef Think_Safety_SystemBackupInfo
#define Think_Safety_SystemBackupInfo

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QJsonArray> 
#include <QtCore/QJsonObject> 
#include <QtCore/QJsonValue> 
#include <QtCore/QJsonDocument> 

#include <safety/SafetyDll.hpp>

#include <utils/Common.hpp>

class Safety_API SystemBackupInfo
{  
public:
    SystemBackupInfo()
    {
        reset();
    }

    SystemBackupInfo(SystemBackupInfo const& other)
    {
        backupId = other.backupId; 

    }

    ~SystemBackupInfo()
    {

    }

public: 
    SystemBackupInfo& reset()
    { 
        backupId = NULL_STR; 

        return *this;
    }

    SystemBackupInfo& reset(SystemBackupInfo const& other)
    { 
        *this = other;
        return *this;
    }

    SystemBackupInfo& operator=(SystemBackupInfo const& other)
    {
        if (this == &other)
        {
            return *this;
        }

        backupId = other.backupId; 

        return *this;
    }

public:
    QString& getBackupId(){
        return this->backupId;
    }

    QString& setBackupId(QString const& newBackupId){
        this->backupId = newBackupId;
        return this->backupId;
    }

public:
    QJsonObject const& toJson(QJsonObject& jsonObj) const{  
        jsonObj.insert("backupId", QJsonValue(backupId)); 

        return jsonObj;
    }

    QJsonObject toJson() const {
        QJsonObject jsonObj; 
        return toJson(jsonObj);
    }

    static QJsonArray const& toJsons(QList<SystemBackupInfo> const& objs, QJsonArray& jsons) { 
        for (int index = 0; index < objs.count(); index++) { 
            jsons.push_back(QJsonValue(objs[index].toJson()));
        } 
        return jsons;
    }

    static QJsonArray toJsons(QList<SystemBackupInfo> const& objs) {
        QJsonArray jsons;
        return toJsons(objs, jsons);
    } 

    SystemBackupInfo& fromJson(QJsonObject const& jsonObj) {   
        backupId = jsonObj["backupId"].toString();  

        return *this;
    }

    SystemBackupInfo(QJsonObject const& jsonObj) {
        fromJson(jsonObj);
    } 

    static QList<SystemBackupInfo>& fromJsons(QJsonArray const& jsons, QList<SystemBackupInfo>& objs)
    {
        objs.clear();
        for (int index = 0; index < jsons.count(); index++)
        { 
            objs.push_back(SystemBackupInfo(jsons.at(index).toObject()));
        }

        return objs;
    }

    static QList<SystemBackupInfo> fromJsons(QJsonArray const& jsons)
    {
        QList<SystemBackupInfo> objs;
        return fromJsons(jsons, objs);
    } 

    static QList<SystemBackupInfo>& fromJsons(QJsonObject const& parentJson, QList<SystemBackupInfo>& objs)
    {
        objs.clear();
        if (!parentJson.contains("backups"))
        {
            return objs;  
        }
        QJsonValue objsValue = parentJson["backups"];
        if (!objsValue.isArray())  
        {
            return objs;
        }

        return fromJsons(objsValue.toArray(), objs);
    }

    static QList<SystemBackupInfo> fromJsons(QJsonObject const& parentJson)
    {
        QList<SystemBackupInfo> objs;
        return fromJsons(parentJson, objs);
    }

public:  
    QString backupId;  

}; 


#endif


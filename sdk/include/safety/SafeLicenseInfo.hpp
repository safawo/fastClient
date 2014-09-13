#ifndef Think_Safety_SafeLicenseInfo
#define Think_Safety_SafeLicenseInfo

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QMap>
#include <QtCore/QVector>
#include <QtCore/QList>

#include <QtCore/QJsonArray> 
#include <QtCore/QJsonObject> 
#include <QtCore/QJsonValue> 
#include <QtCore/QJsonDocument> 

#include <safety/SafetyDll.hpp>

#include <utils/Common.hpp>

class Safety_API SafeLicenseInfo
{  
public:
    SafeLicenseInfo()
    {
        reset();
    }

    SafeLicenseInfo(SafeLicenseInfo const& other)
    {
        distributor = other.distributor;
        distributeId = other.distributeId;

        licenseId = other.licenseId;
        licenseType = other.licenseType;

        customerId = other.customerId;        
        customerName = other.customerName;

        bindNetCard = other.bindNetCard;
        bindDisk = other.bindDisk;
        bindCPU = other.bindCPU;

        expiryDate = other.expiryDate;
        remark = other.remark;

        allowStr = other.allowStr;
        allowInt = other.allowInt;
        allowStrs = other.allowStrs;
        allowInts = other.allowInts;
    }

    ~SafeLicenseInfo()
    {

    }

public: 
    SafeLicenseInfo& reset()
    { 
        distributor = NULL_STR;
        distributeId = NULL_STR;

        licenseId = NULL_STR;
        licenseType = NULL_STR;

        customerId = NULL_STR;        
        customerName = NULL_STR; 

        bindNetCard = NULL_STR;
        bindDisk = NULL_STR;
        bindCPU = NULL_STR;

        expiryDate = NULL_STR;
        remark = NULL_STR;

        allowStr.clear();
        allowInt.clear();
        allowStrs.clear();
        allowInts.clear();

        return *this;
    }

    SafeLicenseInfo& reset(SafeLicenseInfo const& other)
    { 
        *this = other;
        return *this;
    }

    SafeLicenseInfo& operator=(SafeLicenseInfo const& other)
    {
        if (this == &other)
        {
            return *this;
        } 

        distributor = other.distributor;
        distributeId = other.distributeId;

        licenseId = other.licenseId;
        licenseType = other.licenseType;

        customerId = other.customerId;        
        customerName = other.customerName; 
        
        bindNetCard = other.bindNetCard;
        bindDisk = other.bindDisk;
        bindCPU = other.bindCPU;

        expiryDate = other.expiryDate; 
        remark = other.remark;

        allowStr = other.allowStr;
        allowInt = other.allowInt;
        allowStrs = other.allowStrs;
        allowInts = other.allowInts;

        return *this;
    }

public:
    bool isNull() const
    {
        if (this->distributor.isEmpty())
        {
            return true;
        }

        return false;
    }

public:
    QJsonObject const& toJson(QJsonObject& jsonObj) const 
    {  
        jsonObj.insert("distributor", QJsonValue(distributor));
        jsonObj.insert("distributeId", QJsonValue(distributeId));

        jsonObj.insert("licenseId", QJsonValue(licenseId));
        jsonObj.insert("licenseType", QJsonValue(licenseType));

        jsonObj.insert("customerId", QJsonValue(customerId));
        jsonObj.insert("customerName", QJsonValue(customerName));

        jsonObj.insert("bindNetCard", QJsonValue(bindNetCard));
        jsonObj.insert("bindDisk", QJsonValue(bindDisk));
        jsonObj.insert("bindCPU", QJsonValue(bindCPU));

        jsonObj.insert("expiryDate", QJsonValue(expiryDate));
        jsonObj.insert("remark", QJsonValue(remark));  

        QJsonObject allowStrJson;  
        QMap<QString,QString>::const_iterator allowStrIter = allowStr.begin();

        for (allowStrIter = allowStr.begin(); allowStrIter != allowStr.end();allowStrIter++)
        {
            allowStrJson.insert(allowStrIter.key(), QJsonValue(allowStrIter.value()));
        }
        jsonObj.insert("allowStr", QJsonValue(allowStrJson));

        QJsonObject allowIntJson;  
        QMap<QString,int>::const_iterator allowIntIter = allowInt.begin();

        for (allowIntIter = allowInt.begin(); allowIntIter != allowInt.end();allowIntIter++)
        {
            allowIntJson.insert(allowIntIter.key(), QJsonValue(allowIntIter.value()));
        }
        jsonObj.insert("allowInt", QJsonValue(allowIntJson));

        QJsonObject allowStrsJson;  
        QMap<QString,QStringList>::const_iterator allowStrsIter = allowStrs.begin();

        for (allowStrsIter = allowStrs.begin(); allowStrsIter != allowStrs.end();allowStrsIter++)
        {                                 
            QStringList const& allowStrsItem = allowStrsIter.value();
 
            QJsonArray allowStrsItemJsonArray;
            for (int indexAllowStrsItem = 0; indexAllowStrsItem < allowStrsItem.length(); indexAllowStrsItem++)
            {                                 
                allowStrsItemJsonArray.push_back(QJsonValue(allowStrsItem[indexAllowStrsItem]));
            }
            allowStrJson.insert(allowStrsIter.key(), QJsonValue(allowStrsItemJsonArray));
        }
        jsonObj.insert("allowStrs", QJsonValue(allowStrsJson));

        QJsonObject allowIntsJson;  
        QMap<QString,QList<int> >::const_iterator allowIntsIter = allowInts.begin();

        for (allowIntsIter = allowInts.begin(); allowIntsIter != allowInts.end();allowIntsIter++)
        {                                 
            QList<int> const& allowIntsItem = allowIntsIter.value();

            QJsonArray allowIntsItemJsonArray;
            for (int indexAllowIntsItem = 0; indexAllowIntsItem < allowIntsItem.length(); indexAllowIntsItem++)
            {                                 
                allowIntsItemJsonArray.push_back(QJsonValue(allowIntsItem[indexAllowIntsItem]));
            }
            allowIntJson.insert(allowIntsIter.key(), QJsonValue(allowIntsItemJsonArray));
        }
        jsonObj.insert("allowInts", QJsonValue(allowIntsJson));

        return jsonObj;
    }

    QJsonObject toJson() const
    {
        QJsonObject jsonObj; 
        return toJson(jsonObj);
    }
     
    SafeLicenseInfo& fromJson(QJsonObject const& jsonObj)
    {   
        distributor = jsonObj["distributor"].toString(); 
        distributeId = jsonObj["distributeId"].toString(); 

        licenseId = jsonObj["licenseId"].toString();  
        licenseType = jsonObj["licenseType"].toString();  

        customerId = jsonObj["customerId"].toString();  
        customerName = jsonObj["customerName"].toString();

        bindNetCard = jsonObj["bindNetCard"].toString();  
        bindDisk = jsonObj["bindDisk"].toString(); 
        bindCPU = jsonObj["bindCPU"].toString(); 

        expiryDate = jsonObj["expiryDate"].toString();
        remark = jsonObj["remark"].toString();

        if (jsonObj.contains("allowStr"))
        {
            QJsonObject allowStrJsonValue = jsonObj["allowStr"].toObject();
            QStringList allowStrNames = allowStrJsonValue.keys();
            foreach (QString allowStrName, allowStrNames)
            {
                if (!allowStrJsonValue[allowStrName].isString())
                {
                    continue;
                }
                allowStr[allowStrName] = allowStrJsonValue[allowStrName].toString();
            }
        }

        if (jsonObj.contains("allowInt"))
        {
            QJsonObject allowIntJsonValue = jsonObj["allowInt"].toObject();
            QStringList allowIntNames = allowIntJsonValue.keys();
            foreach (QString allowIntName, allowIntNames)
            {
                if (!allowIntJsonValue[allowIntName].isDouble())
                {
                    continue;
                }
                allowInt[allowIntName] = int(allowIntJsonValue[allowIntName].toDouble());
            }
        } 

        if (jsonObj.contains("allowStrs"))
        {
            QJsonObject allowStrsJsonValue = jsonObj["allowStrs"].toObject();
            QStringList allowStrsNames = allowStrsJsonValue.keys();
            foreach (QString allowStrsName, allowStrsNames)
            {
                if (!allowStrsJsonValue[allowStrsName].isArray())
                {
                    continue;
                }
                QJsonArray allowStrsJsonArray = allowStrsJsonValue[allowStrsName].toArray();

                QStringList allowStrsItem;
                for (int indexStrsItem = 0; indexStrsItem < allowStrsJsonArray.size(); indexStrsItem++)
                { 
                    allowStrsItem.push_back(allowStrsJsonArray[indexStrsItem].toString());
                } 
                allowStrs[allowStrsName] = allowStrsItem;
            }
        }
        if (jsonObj.contains("allowInts"))
        {
            QJsonObject allowIntsJsonValue = jsonObj["allowInts"].toObject();
            QStringList allowIntsNames = allowIntsJsonValue.keys();
            foreach (QString allowIntsName, allowIntsNames)
            {
                if (!allowIntsJsonValue[allowIntsName].isArray())
                {
                    continue;
                }
                QJsonArray allowIntsJsonArray = allowIntsJsonValue[allowIntsName].toArray();

                QList<int> allowIntsItem;
                for (int indexIntsItem = 0; indexIntsItem < allowIntsJsonArray.size(); indexIntsItem++)
                { 
                    allowIntsItem.push_back((int)allowIntsJsonArray[indexIntsItem].toDouble());
                } 
                allowInts[allowIntsName] = allowIntsItem;
            }
        }

        return *this;
    }

    SafeLicenseInfo(QJsonObject const& jsonObj)
    {
        fromJson(jsonObj);
    }
 
public:  
    QString distributor;
    QString distributeId;

    QString licenseId;  
    QString licenseType; 

    QString customerId; 
    QString customerName; 

    QString bindNetCard; 
    QString bindDisk; 
    QString bindCPU; 

    QString expiryDate; 
    QString remark;  

    QMap<QString, QString> allowStr;
    QMap<QString, int> allowInt;


    QMap<QString, QStringList> allowStrs; 
    QMap<QString, QList<int> > allowInts;
}; 


#endif


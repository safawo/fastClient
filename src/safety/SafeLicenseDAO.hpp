#ifndef Think_Safety_SafeLicenseDAO
#define Think_Safety_SafeLicenseDAO

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QStringList>

#include <utils/Common.hpp>

#include <safety/SafetyDll.hpp>

#include <safety/SafeLicenseInfo.hpp>


class Safety_API SafeLicenseDAO
{
public:
    virtual void reLoad() = 0;
    
    virtual bool isNormal() = 0;

    virtual bool isEmpty() = 0;
    virtual bool isTimeout() = 0;
    virtual bool needTimeoutTips() = 0;
     
    virtual SafeLicenseInfo const& getLicense() = 0;  

    virtual bool importLicense(QString const& newLicense) = 0;  
    virtual QString  exportLicense() = 0;  
    virtual bool clearLicense() = 0;  

    virtual bool verifyLicense(QString const& licData) = 0;
    virtual bool matchLicense(QString const& licData) = 0;

    virtual QString const& getDistributor() = 0;
    virtual QString const& getDistributeId() = 0;

    virtual QString const& getLicenseId() = 0;
    virtual QString const& getLicenseType() = 0;

    virtual QString const& getCustomerId() = 0; 
    virtual QString const& getCustomerName() = 0;

    virtual QString const& getBindNetCard() = 0; 
    virtual QString const& getBindDisk() = 0; 
    virtual QString const& getBindCPU() = 0;

    virtual QString const& getExpiryDate() = 0; 
    virtual QString const& getRemark() = 0;

    virtual QString getAllowStr(QString const& allowName) = 0;
    virtual int getAllowInt(QString const& allowName) = 0;

    virtual QStringList getAllowStrs(QString const& allowName) = 0;
    virtual QList<int> getAllowInts(QString const& allowName) = 0;

    virtual QSet<QString> getAllowStrSet(QString const& allowName) = 0;
    virtual QSet<int> getAllowIntSet(QString const& allowName) = 0;

    virtual ~SafeLicenseDAO(){};

};

Safety_API SafeLicenseDAO&  licenseDAO();

#endif





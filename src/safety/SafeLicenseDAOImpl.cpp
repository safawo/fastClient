#include <safety/SafeLicenseDAO.hpp> 
#include <safety/SafeLicenseInfo.hpp>
 
#include <utils/HttpClient.hpp> 
#include <utils/Utils.hpp>

#include <QtCore/QDateTime>
#include <QtCore/QDate>
#include <QtCore/QTime>

#define REQ_LICENSE_QUERY               "/think/fast/license/query"
#define REQ_LICENSE_IMPORT              "/think/fast/license/import"
#define REQ_LICENSE_EXPORT              "/think/fast/license/export" 
#define REQ_LICENSE_CLEAR               "/think/fast/license/clear" 

#define REQ_LICENSE_VERIFY              "/think/fast/license/verify" 
#define REQ_LICENSE_MATCH               "/think/fast/license/match" 

#define REQ_SAFE_REFRESH_STAMP      "/think/hotel/conf/common/refreshConfStamp"

#define REQ_LICENSE_TIMEOUT_TIPS_DAY    15

class SafeLicenseDAOImpl: public SafeLicenseDAO
{
public:
    virtual void reLoad()
    {
        licenseConf.reset(); 

        QJsonObject rspMsg = httpClient().postJson(REQ_LICENSE_QUERY);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return;
        }

        licenseConf.fromJson(rspMsg);

        return;
    }

    virtual bool isNormal(){
        if (this->isEmpty()){
            return false;
        }

        if (this->isTimeout()){
            return false;
        }

        return true;
    }

    virtual bool isEmpty(){
        if (getLicense().isNull())
        {
            return true;
        }

        return false;
    }
     
    virtual bool isTimeout() {
        if (this->isEmpty()) {
            return true;
        }

        QString currentTimeStr = utils().YYYY_MM_DD_HH_MM_SS();
        if (currentTimeStr >= this->getExpiryDate()) {
            return true;
        }

        return false;
    }

    virtual bool needTimeoutTips()  
    {
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QDateTime expiryDate = QDateTime::fromString(getExpiryDate(), "yyyy-MM-dd HH:mm:ss");

        int daysAvailable = currentDateTime.daysTo(expiryDate);
        if (daysAvailable < REQ_LICENSE_TIMEOUT_TIPS_DAY) {
            return true;
        }

        return false;
    }

    virtual SafeLicenseInfo const& getLicense()
    {
        return this->licenseConf;
    }

    virtual bool importLicense(QString const& newLicense)
    {
        QJsonObject reqMsg;
        reqMsg.insert("license", newLicense);
        QJsonObject rspMsg = httpClient().postJson(REQ_LICENSE_IMPORT, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }
         
        reLoad(); 
        this->refreshStamp();

        return true;
    }

    virtual QString  exportLicense()
    {
        QString existLicenseData = NULL_STR;

        QJsonObject rspMsg = httpClient().postJson(REQ_LICENSE_EXPORT);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return existLicenseData;
        }

        if (rspMsg.contains("license"))
        {
            existLicenseData = rspMsg["license"].toString();
        }

        return existLicenseData;
    }

    virtual bool clearLicense()
    {
        QJsonObject rspMsg = httpClient().postJson(REQ_LICENSE_CLEAR);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        reLoad();

        this->refreshStamp();
        return true;
    } 

    virtual bool verifyLicense(QString const& licData){
        QJsonObject reqMsg;
        reqMsg.insert("license", licData);
        QJsonObject rspMsg = httpClient().postJson(REQ_LICENSE_VERIFY, reqMsg);
        if (!httpClient().verifyRespNoTip(rspMsg))
        {
            return false;
        }

        if (!rspMsg.contains("isValid")){
            return false; 
        }
        
        return rspMsg["isValid"].toBool();
    }

    virtual bool matchLicense(QString const& licData){
        QJsonObject reqMsg;
        reqMsg.insert("license", licData);
        QJsonObject rspMsg = httpClient().postJson(REQ_LICENSE_MATCH, reqMsg);
        if (!httpClient().verifyRespNoTip(rspMsg))
        {
            return false;
        }

        if (!rspMsg.contains("isMatch")){
            return false; 
        }

        return rspMsg["isMatch"].toBool();
    }

    virtual QString const& getDistributor()
    {
        return this->getLicense().distributor;
    }

    virtual QString const& getDistributeId()
    {
        return this->getLicense().distributeId;
    } 

    virtual QString const& getLicenseId() 
    {
        return this->getLicense().licenseId;
    }

    virtual QString const& getLicenseType()
    {
        return this->getLicense().licenseType;
    }


    virtual QString const& getCustomerId() 
    {
        return this->getLicense().customerId;
    }
 
    virtual QString const& getCustomerName()
    {
        return this->getLicense().customerName;
    }

    virtual QString const& getBindNetCard()
    {
        return this->getLicense().bindNetCard;
    }

    virtual QString const& getBindDisk()
    {
        return this->getLicense().bindDisk;    
    }

    virtual QString const& getBindCPU()
    {
        return this->getLicense().bindCPU;
    }

    virtual QString const& getExpiryDate()
    {
        return this->getLicense().expiryDate;
    }

    virtual QString const& getRemark()
    {
        return this->getLicense().remark;
    }

    virtual QString getAllowStr(QString const& allowName)
    {
        if (getLicense().allowStr.contains(allowName))
        {
            return getLicense().allowStr[allowName];
        }
        
        return NULL_STR;
    }

    virtual int getAllowInt(QString const& allowName)
    {
        if (getLicense().allowInt.contains(allowName))
        {
            return getLicense().allowInt[allowName];
        }

        return NULL_INT;
    }

    virtual QStringList getAllowStrs(QString const& allowName)
    {
        if (getLicense().allowStrs.contains(allowName))
        {
            return getLicense().allowStrs[allowName];
        }

        QStringList allowStrs;
        return allowStrs;
    }

    virtual QList<int> getAllowInts(QString const& allowName)
    {
        if (getLicense().allowInts.contains(allowName))
        {
            return getLicense().allowInts[allowName];
        }

        QList<int> allowInts;
        return allowInts;
    }

    virtual QSet<QString> getAllowStrSet(QString const& allowName)
    {
        return getAllowStrs(allowName).toSet();
    }

    virtual QSet<int> getAllowIntSet(QString const& allowName)
    {
        return getAllowInts(allowName).toSet();
    }

    virtual ~SafeLicenseDAOImpl()
    {

    }

    static SafeLicenseDAO* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new SafeLicenseDAOImpl();
        }

        return _instance;
    }

private:
    SafeLicenseDAOImpl()
    {
        reLoad();
    } 

    void refreshStamp(){  
        httpClient().postJson(REQ_SAFE_REFRESH_STAMP);  
        return;
    }

private: 
    SafeLicenseInfo licenseConf;

private:
    static SafeLicenseDAO* _instance; 

};

SafeLicenseDAO* SafeLicenseDAOImpl::_instance = NULL; 

SafeLicenseDAO& licenseDAO()
{ 
    return *(SafeLicenseDAOImpl::getInstance());
}  




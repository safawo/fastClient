#ifndef Think_Utils_Utils
#define Think_Utils_Utils

#include <utils/UtilsDll.hpp>  
#include <utils/SystemMgr.hpp>

#include <QtWidgets/QListWidget>

#include <QtCore/QTextCodec>
#include <QtCore/QVariant>

#include <QtCore/QDateTime>

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QByteArray>

#include <QtCore/QDebug> 
 
class Utils_API Utils
{
public:  
    virtual QHash<QString, QString> str2Map(QString const& mapStrings) = 0;  
    virtual QHash<QString, QString> str2Map(QStringList const& mapStrings) = 0; 
     
    virtual char typeFrom(QVariant::Type const& type) = 0;  
    virtual char typeFrom(QVariant const& v) = 0;  
         
    virtual QString YYYY_MM_DD_HH_MM_SS_ZZZ() = 0; 
    virtual QString YYYY_MM_DD_HH_MM_SS() = 0; 
    virtual QString YYYY_MM_DD() = 0;

    virtual bool isValidIP(QString const& ip) = 0;

    virtual QDateTime toDateTime(QString const& text) = 0;
     
    virtual char getIDCardVerifyCode(QByteArray const& id) = 0; 
     
    virtual QDateTime complieDateTime(QString const& complieDate, QString const& complieTime) = 0; 
    virtual bool isDigitStr(QString const& str) = 0;
     
    virtual QString randId() = 0;
    virtual QString randPwd() = 0;

    virtual QString md5(QString const& srcData) = 0;
    virtual QString md5Two(QString const& srcData) = 0;
    virtual QString md5Three(QString const& srcData) = 0;

    virtual QString password(QString const& password) = 0;
    virtual QString passwordBySeed(QString const& password, QString const& seed) = 0;

    virtual QString enCodeBase64(QString const& srcData) = 0;
    virtual QString deCodeBase64(QString const& srcData) = 0;

    virtual bool compareLock(const QString &lockA, const QString &lockB) = 0;
	virtual QStringList sortLocks(QStringList const& srcLocks) = 0;
    virtual void sortLocks(QListWidget* locksView) = 0;

    virtual bool isOddLock(QString const& lockName) = 0;  
    virtual QStringList filtOddLock(QStringList const& locks) = 0;

    virtual bool filtLock(QString const& lockName, int step = 0) = 0;
    virtual QStringList filtLock(QStringList const& locks, int step = 0) = 0;

    virtual void killAdb() = 0;

	virtual unsigned char lrcVerify(QByteArray charbytes) = 0;
	virtual unsigned char lrcCheck(uint buf[], uint length) = 0;

    virtual ~Utils(){};
};
 
Utils_API Utils& utils(); 
 
#endif


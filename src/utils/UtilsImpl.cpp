#include <utils/Utils.hpp>
#include <utils/HttpClient.hpp>
#include <utils/CommonFunction.h>
#include <QtCore/QDebug>

#include <QtCore/QTextCodec>
#include <QtCore/QDateTime>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QProcess>
#include <QtCore/QRegExp>
#include <QtCore/QMutex> 
#include <QtCore/QSettings> 
#include <QtWidgets/QListWidget>

#include <utils/Md5.hpp>
  
bool qcomparefun(const QString &lockA, const QString &lockB)
{ 
    QString localLockA = lockA.trimmed().toLower(); 
    QString localLockB = lockB.trimmed().toLower();

    if (lockB.isEmpty())
    {
        return false;
    }
    if (lockA.isEmpty())
    {
        return true;
    }

    QString lockAStr = ""; 
    QString lockAInt = ""; 

    QString lockBStr = ""; 
    QString lockBInt = "";

    QByteArray byteA = localLockA.toLatin1();//QString 转换为 char*  
    QByteArray byteB = localLockB.toLatin1(); 
     
    const char *byteAS = byteA.data();  
    const char *byteBS = byteB.data();  

    while(*byteAS){
        if (*byteAS>='0' && *byteAS<='9') {
            lockAInt.append(*byteAS);
        } else {
            if (!lockAInt.isEmpty()){
                break;
            }
            lockAStr.append(*byteAS);
        }
        byteAS++; 
    } 

    while(*byteBS){
        if (*byteBS>='0' && *byteBS<='9') {
            lockBInt.append(*byteBS);
        } else {
            if (!lockBInt.isEmpty()){
                break;
            }
            lockBStr.append(*byteBS);
        }
        byteBS++; 
    } 
    
    if (!lockAInt.isEmpty() && !lockBInt.isEmpty() && lockAStr.isEmpty() && lockBStr.isEmpty()) {
        int lockAIntV = lockAInt.toInt();
        int lockBIntV = lockBInt.toInt();

        if (lockAIntV < lockBIntV) {
            return true;
        }else{
            return false;
        } 
    }

	if (lockAInt.isEmpty() && lockBInt.isEmpty() && !lockAStr.isEmpty() && !lockBStr.isEmpty()) {
	    return (lockAStr < lockBStr); 
	}
	 
    if (lockAStr < lockBStr) {
        return true;
    }else if (lockAStr > lockBStr){
        return false;
    }
    
    int lockAIntVT = lockAInt.toInt();
    int lockBIntVT = lockBInt.toInt();
    if (lockAIntVT < lockBIntVT) {
        return true;
    }else{
        return false;
    } 

}

class UtilsImpl: public Utils
{
public: 
    QHash<QString, QString> str2Map(QString const& mapStrings)
    {
        QStringList strings = mapStrings.split("\n", QString::SkipEmptyParts);

        return str2Map(strings);
    }

    QHash<QString, QString> str2Map(QStringList const& mapStrings) 
    {
        QHash<QString, QString> ret;

        foreach(QString s, mapStrings)
        {
            QString key;
            QString value;
            int pos = s.indexOf("=");
            if ( pos >= 0 )
            {
                key = s.mid(0, pos).trimmed();
                value = s.mid(pos+1).trimmed();
                if (!key.isEmpty() && !value.isEmpty())
                {
                    ret[key] = value;
                }
            }
        }
        return ret;
    }
     
    char typeFrom(QVariant::Type const& type)
    {
        char c = '\0';
        if ( type == QVariant::Int
            || type == QVariant::UInt
            || type == QVariant::LongLong
            || type == QVariant::ULongLong )
        {
            c = 'i';
        }else if ( type == QVariant::Double )
        {
            c = 'n';
        }else if ( type == QVariant::String )
        {
            c = 's';
        }else if ( type == QVariant::Date
            || type == QVariant::Time
            || type == QVariant::DateTime )
        {
            c = 't';
        }else if ( type == QVariant::Date
            || type == QVariant::Time
            || type == QVariant::DateTime )
        {
            c = 't';
        }else if ( type == QVariant::ByteArray )
        {
            c = 'm';
        }else
        {

        }
        return c;
    }

    char typeFrom(QVariant const& v)
    {
        return typeFrom(v.type());
    }

    QString YYYY_MM_DD_HH_MM_SS_ZZZ()
    {
        return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
    }

    QString YYYY_MM_DD_HH_MM_SS()
    {
        return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    }

    QString YYYY_MM_DD()
    {
        return QDateTime::currentDateTime().toString("yyyy-MM-dd");
    }

    bool isValidIP(QString const& ip){
        QRegExp rx2("(\\d+)(\\.)(\\d+)(\\.)(\\d+)(\\.)(\\d+)");
        int pos = rx2.indexIn(ip);
        if(pos>-1){
            for(int i=0;i<4;i++){
                if( rx2.cap(i*2+1).toInt()>=255 ){ 
                    return false;
                }
            }
            if(rx2.cap(7).toInt()==0){ 
                return false;
            }
            if(rx2.cap(7).toInt()==0){ 
                return false;
            }
        }else{ 
            return false;
        }

        return true;
    }

    QDateTime toDateTime(QString const& text)
    {
        QDateTime ret = QDateTime();
        switch(text.length())
        {
        case 23:
            ret = QDateTime::fromString(text, "yyyy-MM-dd HH:mm:ss.zzz");
            break;
        case 19:
            ret = QDateTime::fromString(text, "yyyy-MM-dd HH:mm:ss");
            break;
        case 16:
            ret = QDateTime::fromString(text, "yyyy-MM-dd HH:mm");
            break;
        case 14:
            ret = QDateTime::fromString(text, "yyyyMMddHHmmss");
            break;
        case 10:
            ret = QDateTime::fromString(text, "yyyy-MM-dd");
            break;
        case  8:
            ret = QDateTime::fromString(text, "HH:mm:ss");
            break;
        case  7:
            ret = QDateTime::fromString(text, "yyyy/MM");
            break;
        case  6:
            ret = QDateTime::fromString(text, "HHmmss");
            break;
        case  5:
            if ( text.at(2) == '/'
                || text.at(2) == '-' )
            {
                ret = QDateTime::fromString(text, "MM/dd");
            }else
                if ( text.at(2) == ':' )
                {
                    ret = QDateTime::fromString(text, "HH:mm");
                }
                break;
        case  4:
            ret = QDateTime::fromString(text, "yyyy");
            break;
        case  2:
            ret.fromString(text, "dd");
            break;
        case  1:
            ret = QDateTime::fromString(text, "d");
            break;
        }
        return ret;
    }

    char getIDCardVerifyCode(QByteArray const& id)
    {
        char ret = '\0';
        if ( id.length() >= 17 )
        {
            // 加权乘积求和除以11的余数所对应的校验数
            const char verifyMap[] = "10X98765432";
            // 加权因子
            const int factor[] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2, 1 };

            int Sum = 0;  //加权乘积求和
            for( int i=0;i<17;i++ )
            {
                char c = id[i];

                Sum += (c-'0') * factor[i]; // 加权乘积求和
            }
            ret = verifyMap[Sum % 11]; // 取模
        }
        return ret;
    }

    QDateTime complieDateTime(QString const& complieDate, QString const& complieTime)
    {
        QString DateString = complieDate;
        QString Year  = DateString.right(4);
        QString Month = DateString.left(3).toUpper();
        QString Day   = DateString.mid(4, 2);
        QString TimeString = complieTime;
        QString Hour   = TimeString.left(2);
        QString Minute = TimeString.mid(3, 2);
        QString Second = TimeString.right(2);
        const QString MonthString[12] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
            "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
        unsigned int MonthValue;
        for( MonthValue=0;MonthValue<sizeof(MonthString);MonthValue++ )
        {
            if ( Month == MonthString[MonthValue] )
            {
                MonthValue++;
                break;
            }
        }
        return QDateTime(QDate(Year.toInt(), MonthValue, Day.toInt()),
            QTime(Hour.toInt(), Minute.toInt(), Second.toInt()));
    }

    bool isDigitStr(QString const& str)
    {  
        QByteArray ba = str.trimmed().toLatin1();//QString 转换为 char*  
        if (ba.length() == 0)
        {
            return false;
        }

        const char *s = ba.data();  

        while(*s && *s>='0' && *s<='9') s++;  

        if (*s)  
        { 
            //不是纯数字  
            return false;  
        }  
        else  
        { 
            //纯数字  
            return true;  
        }  
    }  
 
    virtual QString randId()
    {
        mutexRandSelfId.lock();
        dyncRandId++;
        if (dyncRandId > 9999)
        {
            dyncRandId = 1;
        }
        QString strDyncRandId = "0000" + QString::number(dyncRandId);
        mutexRandSelfId.unlock();

        strDyncRandId = strDyncRandId.right(4);
        QString strRandId = QDateTime::currentDateTime().toString("yyyyMMddHHmmsszzz");
        strRandId += strDyncRandId;

        return strRandId;
    }

    virtual QString randPwd()
    {
        //随机生成两个字符,一个取高4bit，一个取低4bit，生成随机密码
        QTime t;
        t= QTime::currentTime();
        qsrand(t.msec()+t.second()*1000);

        char ch1 = SEQUENCEOFCHAR[uint(qrand())%62];  
        char ch2 = SEQUENCEOFCHAR[uint(qrand())%62];
        unsigned char uPwd = (ch1 & 0X0F) | (ch2 & 0XF0); 
        QString strPwd = NULL_STR;
        UC2Str(&uPwd, 1, strPwd);

        return strPwd;
    }

    virtual QString md5(QString const& srcData)
    {
        MD5 md5Obj;
        md5Obj.update(srcData);

        return md5Obj.toString();
    }

    virtual QString md5Two(QString const& srcData)
    {
        return md5(md5(srcData));
    }

    virtual QString md5Three(QString const& srcData)
    {
        return md5Two(md5(srcData));
    }
     
    virtual QString password(QString const& password)
    {
        return passwordBySeed(password, password);
    }

    virtual QString passwordBySeed(QString const& password, QString const& seed)  
    {
        QString passwordSrc = password.trimmed();
        QString passwordObj = password.trimmed() + "ujmiklop";

        if (passwordSrc.isEmpty())
        {
            passwordSrc = passwordObj;
        } 

        passwordSrc = enCodeBase64(passwordSrc);
        passwordObj = enCodeBase64(passwordSrc + passwordObj + seed);

        passwordObj = md5(passwordSrc + passwordObj + seed + "qazwsx");
        passwordObj = enCodeBase64(passwordSrc + passwordObj + seed);

        passwordObj = md5(passwordSrc + passwordObj + seed + "edcrfv");
        passwordObj = enCodeBase64(passwordSrc + passwordObj + seed);
        
        passwordObj = md5(passwordSrc + passwordObj + seed + "tgbyhn"); 
        passwordObj = enCodeBase64(passwordSrc + passwordObj + seed); 
        
        passwordObj = md5(passwordObj);

        return passwordObj;
    }

    virtual QString enCodeBase64(QString const& srcData)
    {
        QByteArray enCodeData;
        enCodeData.append(srcData);
        QString objData = QString(enCodeData.toBase64());

        //qDebug()<<"srcData:"<<srcData<<",objData:"<<objData;

        return objData;
    }
   
    virtual QString deCodeBase64(QString const& srcData)
    {
        QByteArray deCodeData;
        deCodeData.append(srcData);
        return QString(deCodeData); 
    }

    virtual bool compareLock(const QString &lockA, const QString &lockB){
        return qcomparefun(lockA, lockB);
    }
     
	virtual QStringList sortLocks(QStringList const& srcLocks){
		QStringList templocks = srcLocks; 
		qSort(templocks.begin(), templocks.end(), qcomparefun);
		return templocks;
	}

    virtual void sortLocks(QListWidget* locksView){
        QStringList lockNames;
        for (int index = 0; index < locksView->count(); index++)
        {  
            lockNames.push_back(locksView->item(index)->text().trimmed());  
        } 

        QStringList sortLockNames = utils().sortLocks(lockNames); 

        locksView->clear();
        locksView->addItems(sortLockNames);

        return;
    }

    virtual bool isOddLock(QString const& lockName){
        QString lockLockName = lockName.trimmed().toLower();
        QByteArray byteLock = lockLockName.toLatin1();
 
        QString lockNumStr = NULL_STR;

        const char *byteAsLock = byteLock.data();   
        while(*byteAsLock){
            if (*byteAsLock<'0' || *byteAsLock>'9'){
                if (!lockNumStr.isEmpty()){
                    break;
                } 
            }else{
                lockNumStr.append(*byteAsLock);
            } 

            byteAsLock++; 
        } 

        if (lockNumStr.isEmpty()){
            return false;
        }

        int lockNum = lockNumStr.toInt();
        if ((lockNum%2) == 0){
            return false;
        }else{
            return true;
        }
    }
    
    virtual QStringList filtOddLock(QStringList const& locks){
        QStringList filtLocks;
        for (int index = 0; index < locks.size(); index++){
            if (!isOddLock(locks[index])){
                continue;
            }
            filtLocks.push_back(locks[index]);
        }
        return filtLocks;
    }

    virtual bool filtLock(QString const& lockName, int step = 0){
        QString lockLockName = lockName.trimmed().toLower();
        QByteArray byteLock = lockLockName.toLatin1();

        if (step == 0){
            return true;
        }

        QString lockNumStr = NULL_STR;

        const char *byteAsLock = byteLock.data();   
        while(*byteAsLock){
            if (*byteAsLock<'0' || *byteAsLock>'9'){
                if (!lockNumStr.isEmpty()){
                    break;
                } 
            }else{
                lockNumStr.append(*byteAsLock);
            } 

            byteAsLock++; 
        } 

        if (lockNumStr.isEmpty()){
            return false;
        }
        
        int lockNum = lockNumStr.toInt();
        if ((lockNum%step) == 0){
            return true;
        }else{
            return false;
        }
    }

    virtual QStringList filtLock(QStringList const& locks, int step = 0){
        QStringList filtLocks;
        for (int index = 0; index < locks.size(); index++){
            if (!filtLock(locks[index], step)){
                continue;
            }
            filtLocks.push_back(locks[index]);
        }
        return filtLocks;
    }

	virtual void killAdb(){
		qDebug() << "enter the killadb function" ;
		//QString killAdbCmd = "taskkill -F -IM adb.exe\n";
		QString adb = sys().getRootPath()+"/tools/adb/adb.exe";
		QProcess* proces = new QProcess();
		//p.start("cmd"); 
		//p.waitForStarted();

		//p.write(killAdbCmd.toUtf8());
		proces->setProcessChannelMode(QProcess::MergedChannels);
		proces->start("\"" + adb + "\" kill-server");
		proces->waitForStarted();
		proces->waitForFinished();

		proces->close();
		proces->terminate();

		if (proces!= NULL)
		{
			delete proces;
			proces = NULL;
		}
		//p.closeWriteChannel();
		//p.waitForFinished(-1);
	}

	unsigned char lrcVerify(QByteArray charbytes)
	{
		unsigned char res;
		if (charbytes.isEmpty() || charbytes.isNull())
		{
			return res;
		}
		QByteArray hex = charbytes;
		qDebug() << "hex:" << hex;
		bool ok;
		/*
        for (int i = 0 ; i< hex.size(); i++)
		{
			qDebug() << "QByteArray value:" << QString::number(hex[i],16);
		}
		*/
		uint lrcValue = 0x00;
		for (int i = 0; i< hex.size(); i++)
		{
			lrcValue = lrcValue + hex[i];
		}

		res =   (~lrcValue) + 1;
		qDebug() << "res:" << QString::number(res,16);
		return res;
	}

	unsigned char lrcCheck(uint buf[], uint length)
	{
		uint iCount  = 0;
		uint lrcValue = 0x00;

		for(iCount = 0; iCount < length ; iCount ++) { 

			lrcValue = lrcValue + buf[iCount];
		}
		qDebug() << "lrcValue:" << lrcValue;
		//return ((unsigned char)(-((char)lrcValue)));
		return (~lrcValue) + 1;
	}

    virtual ~UtilsImpl()
    {   
        
    }

    static Utils* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new UtilsImpl();
        }

        return _instance;
    }

private:
    UtilsImpl()
    {
        dyncRandId = 0;
    }

private:
    QMutex mutexRandSelfId;
    int dyncRandId;

private:
    static Utils* _instance;

};

Utils* UtilsImpl::_instance = NULL;
 
Utils_API Utils& utils()
{
    return *(UtilsImpl::getInstance());
}

 
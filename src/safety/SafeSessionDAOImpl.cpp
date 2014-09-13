#include <safety/SafeSessionDAO.hpp> 

#include <utils/HttpClient.hpp> 
#include <utils/HttpClientMgr.hpp> 
#include <utils/FastSafeValidater.hpp>
#include <utils/FastMsgBox.hpp>

#include <QtNetwork/QHostInfo>
#include <utils/Utils.hpp>

#include <QtCore/QProcess>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtCore/QTextCodec>
#include <QtCore/QTextStream>

#include <QtCore/QSettings>
#include <utils/SystemMgr.hpp>

#define REQ_SAFESESSION_LOGIN             "/think/fast/safe/session/login"
#define REQ_SAFESESSION_LOGOUT            "/think/fast/safe/session/logout"
#define REQ_SAFESESSION_SHAKEHAND         "/think/fast/safe/session/shakeHand"
#define REQ_SAFESESSION_AWAKELOGIN        "/think/fast/safe/session/awakeLogin"
#define REQ_SAFESESSION_FORCEOFFLINE      "/think/fast/safe/session/forceOffline"

#define REQ_SAFESESSION_CONSULTSESSION    "/think/fast/safe/session/consultSession"

#define CACHE_SIZE_PAD                    "Cache Size/PadCache"
#define CACHE_SIZE_DOWNLOAD               "Cache Size/DownloadCache"

class SafeSessionDAOImpl: public SafeSessionDAO, public FastSafeValidater
{
public:
    virtual void reLoad()
    {

    }

    virtual bool login(QString const& userName, QString const& password, QString const& reqIp = NULL_QSTR, QString const& reqPort = NULL_QSTR)
    {
        if (userName.trimmed().isEmpty())
        {
            msgBox().information("UserName is empty!");
            return false;
        }
        
        if (password.trimmed().isEmpty())
        {
            msgBox().information("Password is empty!");
            return false;
        }

        this->_latestUserName = userName.trimmed();
        this->_latestPassword = password.trimmed(); 

        httpClientMgr().resetServer(reqIp.trimmed(), reqPort.trimmed());

        QJsonObject reqMsg;
        reqMsg.insert("userName", getUserName());
        reqMsg.insert("password", utils().password(getPassword()));
          
        reqMsg.insert("hostName", getLocalHostName()); 
        reqMsg.insert("hostIp", getLocalIp());
         
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFESESSION_LOGIN, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }
        QString reqSessionId = NULL_QSTR;
        if (rspMsg.contains("newSessionId"))
        {                       
            reqSessionId = rspMsg["newSessionId"].toString();
        }
        if (rspMsg.contains("serverHostName"))
        {                       
            _reqHostName = rspMsg["serverHostName"].toString();
        }

        httpClientMgr().resetSession(reqSessionId);

        this->setSessionStatus(SafeSessionInfo::SESSION_LOGIN);

        initEnv();

        return true;
    }

    virtual bool logout()
    { 
        sys().logout();

        this->killDaemon();

        QJsonObject rspMsg = httpClient().postJson(REQ_SAFESESSION_LOGOUT);
        if (!httpClient().verifyRespNoTip(rspMsg))
        {
            return false;
        }

        httpClientMgr().resetSession();

        this->setSessionStatus(SafeSessionInfo::SESSION_LOGOUT);
         
        return true;
    }

    virtual bool shankHand()
    {
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFESESSION_SHAKEHAND);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        return true;
    }

    virtual bool awakeLogin(QString const& password)
    {
        QJsonObject reqMsg;
        reqMsg.insert("password", utils().password(password));

        QJsonObject rspMsg = httpClient().postJson(REQ_SAFESESSION_AWAKELOGIN, reqMsg);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        this->setSessionStatus(SafeSessionInfo::SESSION_LOGIN);
        return true;
    }

    virtual bool forceOffline() {
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFESESSION_FORCEOFFLINE);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return false;
        }

        this->setSessionStatus(SafeSessionInfo::SESSION_LOGOUT);

        return true;
    }

    virtual QString getCacheLoginUserName(){
        QString cacheLoginUserName = NULL_STR;
        QString fileName = sys().getTempPath() + "/loginUserName.login";

        if (!QFile::exists(fileName)){
            return cacheLoginUserName;
        }

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            return cacheLoginUserName;
        }

        if (!file.atEnd()) {
            cacheLoginUserName.append(file.readLine());
            cacheLoginUserName = cacheLoginUserName.trimmed();
        } 
        file.close();

        return cacheLoginUserName;
    }

    virtual void saveCacheLoginUserName(QString const& loginUserName){
        QString fileName = sys().getTempPath() + "/loginUserName.login"; 

        if (QFile::exists(fileName)) { 
            QFile::remove(fileName); 
        }
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
            return;
        }
        QTextStream out(&file);
        out << loginUserName.trimmed() << "\n";

        file.flush();
        file.close();

        return;
    }

    virtual QString getCacheLoginReqHost(){
        QString cacheHostName = NULL_STR;
        QString fileName = sys().getTempPath() + "/loginReqHost.login";

        if (!QFile::exists(fileName)){
            return cacheHostName;
        }

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            return cacheHostName;
        }

        if (!file.atEnd()) {
            cacheHostName.append(file.readLine());
            cacheHostName = cacheHostName.trimmed();
        } 
        file.close();

        return cacheHostName;
    }

    virtual void saveCacheLoginReqHost(QString const& loginReqHost){
        QString fileName = sys().getTempPath() + "/loginReqHost.login"; 

        if (QFile::exists(fileName)) { 
            QFile::remove(fileName); 
        }
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
            return;
        }
        QTextStream out(&file);
        out << loginReqHost.trimmed() << "\n";

        file.flush();
        file.close();

        return;
    }

    virtual SafeSessionInfo::SESSION_STATUS getSessionStatus(){
        return this->_activateSessionStatus;
    }

public:
    virtual QString getUserName(){
        return this->_latestUserName;
    }

    virtual QString getPassword(){
        return this->_latestPassword;
    }

    virtual QString getReqIp(){
        return httpClientMgr().getReqIp();
    }

    virtual QString getReqPort(){
        return httpClientMgr().getReqPort();
    }
     
    virtual QString getReqHostName(){
        return _reqHostName;
    }

    virtual QString getLocalIp(){                       
        initLocalHost(); 
        return this->_localHostIp;
    }

    virtual QString getLocalHostName(){
       initLocalHost(); 
       return this->_localHostName;
    }

public:
    virtual bool checkRequest(QString const& sessionId, QString const& reqPath, QString& checkMsg = NULL_QSTR) const
    {
        return true;
    }

public:
    virtual ~SafeSessionDAOImpl()
    {

    }

    static SafeSessionDAO* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new SafeSessionDAOImpl();
        }

        return _instance;
    }

private:
    SafeSessionDAOImpl()
    :_latestUserName(NULL_STR), _latestPassword(NULL_STR), 
    _localHostIp(NULL_STR), _localHostName(NULL_STR),_reqHostName(NULL_STR)
    {
        _activateSessionStatus = SafeSessionInfo::SESSION_INIT;

        this->queryAll();

        httpClientMgr().regValidater(this);
    }

    void queryAll()
    {   
        return;
    }

    void setSessionStatus(SafeSessionInfo::SESSION_STATUS sessionStatus)
    {
        this->_activateSessionStatus = sessionStatus;
    }

    void initLocalHost()
    {
        if (this->_localHostIp != NULL_STR && this->_localHostName != NULL_STR)
        {
            return;
        }

        _localHostName = QHostInfo::localHostName(); 

        _localHostIp = "127.0.0.1";
        QList<QHostAddress> addresses = QHostInfo::fromName(_localHostName).addresses();
        for (int index = 0; index < addresses.size(); index++)
        {
            QHostAddress& address = addresses[index];  
            if (address.protocol() != QAbstractSocket::IPv4Protocol)
            { 
                continue; 
            }
             
            if (address.toString() == _localHostIp)
            { 
                continue;
            }

            _localHostIp = address.toString();
            break;
        }  
    }

    void killDaemon()
    {
        QString killAdbCmd = "taskkill -F -IM adb.exe\n";

        QProcess p(0);
        p.start("cmd"); 
        p.waitForStarted();

        p.write(killAdbCmd.toUtf8());

        p.closeWriteChannel();
        p.waitForFinished(-1);
    }

private:
    QString getSessionSeed()
    {
        QString sessionSeed = NULL_STR;
         
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFESESSION_CONSULTSESSION);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return sessionSeed;
        }

        if (rspMsg.contains("sessionSeed"))
        {                       
            sessionSeed = rspMsg["sessionSeed"].toString();
        }
         
        return sessionSeed; 
    }

    void initEnv(){
        QSettings settings(sys().getIni(), QSettings::IniFormat);
        int padCacheSize = NULL_INT; 
        int downloadCacheSize = NULL_INT;

        if (settings.contains(CACHE_SIZE_PAD))
        {
            padCacheSize = settings.value(CACHE_SIZE_PAD).toInt(); 
        }  

        if (settings.contains(CACHE_SIZE_DOWNLOAD))
        {
            downloadCacheSize = settings.value(CACHE_SIZE_DOWNLOAD).toInt(); 
        }  

        QDir padinDir(sys().getCachePath() + "/padin");
        if(padinDir.exists())
        {
            //padinDir.setFilter(QDir::Files | QDir::NoSymLinks);
            QStringList padFiles = padinDir.entryList(QDir::Files|QDir::NoSymLinks, QDir::Name);
            padFiles.sort();
            int fileCount = padFiles.size() - padCacheSize;
            for (int indexPad = 0; indexPad < fileCount; indexPad++){
                QFile::remove(sys().getCachePath() + "/padin/" + padFiles[indexPad]);
            } 
        }

        QDir downloadDir(sys().getDownloadPath());
        if(downloadDir.exists())
        { 
            QStringList downloadFiles = downloadDir.entryList(QDir::Files|QDir::NoSymLinks, QDir::Name);
            downloadFiles.sort();
            int fileCount = downloadFiles.size() - downloadCacheSize;
            for (int indexDownload = 0; indexDownload < fileCount; indexDownload++){
                QFile::remove(sys().getDownloadPath() + "/" + downloadFiles[indexDownload]);
            } 
        } 

        return;
    }

private:
    QString _latestUserName;
    QString _latestPassword; 

    QString _localHostIp;
    QString _localHostName; 
     
    QString _reqHostName; 

    SafeSessionInfo::SESSION_STATUS _activateSessionStatus;

private:
    static SafeSessionDAO* _instance; 

};

SafeSessionDAO* SafeSessionDAOImpl::_instance = NULL; 

SafeSessionDAO& safeSessionDAO()
{ 
    return *(SafeSessionDAOImpl::getInstance());
}



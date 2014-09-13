#include <safety/SystemBackupDAO.hpp>
#include <safety/SystemBackupInfo.hpp>

#include <utils/HttpClient.hpp> 

#define REQ_Backup_NotifyBackup       "/think/fast/backup/notifyBackup"    
#define REQ_Backup_NotifyRestore      "/think/fast/backup/notifyRestore"    
#define REQ_Backup_BackupSystem       "/think/fast/backup/backupSystem"    
#define REQ_Backup_RestoreSystem      "/think/fast/backup/restoreSystem"    
#define REQ_Backup_GetBackups         "/think/fast/backup/getBackups"    
#define REQ_Backup_DelBackup          "/think/fast/backup/delBackup"    
 

class SystemBackupDAOImpl: public SystemBackupDAO
{
public:
    virtual void reLoad() {
         return;
    }

    virtual bool notifyBackup(SystemBackupInfo const& backup) {
        QJsonObject rspMsg = httpClient().postJson(REQ_Backup_NotifyBackup, backup.toJson());
        if (!httpClient().verifyResponse(rspMsg)) {
            return false;
        } 

        return true;
    }

    virtual bool notifyRestore(SystemBackupInfo const& restore) {
        QJsonObject rspMsg = httpClient().postJson(REQ_Backup_NotifyRestore, restore.toJson());
        if (!httpClient().verifyResponse(rspMsg)){
            return false;
        } 

        return true;
    }

    virtual bool notifyBackup(QString const& backupId){
        SystemBackupInfo newBuckup;
        newBuckup.setBackupId(backupId);
        return this->notifyBackup(newBuckup);
    }

    virtual QString backupSystem() {
        QString backupId = NULL_STR;

        QJsonObject rspMsg = httpClient().postJson(REQ_Backup_BackupSystem);
        if (!httpClient().verifyResponse(rspMsg)) {
            return backupId;
        } 

        SystemBackupInfo backupInfo;
        backupInfo.fromJson(rspMsg);

        return backupInfo.getBackupId();
    }

    virtual bool restoreSystem(QString const& backupId) {
        QJsonObject reqMsg;
        reqMsg.insert("backupId", backupId);
        QJsonObject rspMsg = httpClient().postJson(REQ_Backup_RestoreSystem, reqMsg);
        if (!httpClient().verifyResponse(rspMsg)) {
            return false;
        }

        return true;
    }

    virtual bool getBackups(QList<SystemBackupInfo>& backups) {
        backups.clear();

        QJsonObject rspMsg = httpClient().postJson(REQ_Backup_GetBackups);
        if (!httpClient().verifyResponse(rspMsg)) {
            return false;
        } 

        SystemBackupInfo::fromJsons(rspMsg, backups);
        return true;
    }

    virtual bool delBackup(QString const& backupId) {
        QJsonObject reqMsg;
        reqMsg.insert("backupId", backupId);
        QJsonObject rspMsg = httpClient().postJson(REQ_Backup_DelBackup, reqMsg);
        if (!httpClient().verifyResponse(rspMsg)) {
            return false;
        }

        return true;
    }
     
    virtual ~SystemBackupDAOImpl() {

    }

    static SystemBackupDAO* getInstance() {
        if (_instance == NULL) {
            _instance = new SystemBackupDAOImpl();
        }

        return _instance;
    }

private:
    SystemBackupDAOImpl() {
        this->reLoad();
    }
     
private:
    static SystemBackupDAO* _instance; 

};

SystemBackupDAO* SystemBackupDAOImpl::_instance = NULL; 

SystemBackupDAO& backupDAO(){ 
    return *(SystemBackupDAOImpl::getInstance());
}




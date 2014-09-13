#ifndef Think_Safety_SystemBackupDAO
#define Think_Safety_SystemBackupDAO

#include <QtCore/QString>  
#include <QtCore/QList> 
#include <QtCore/QStringList> 

#include <utils/Common.hpp> 

#include <safety/SafetyDll.hpp>

#include <safety/SystemBackupInfo.hpp> 

class Safety_API SystemBackupDAO
{
public:
    virtual void reLoad() = 0;

    virtual bool notifyBackup(SystemBackupInfo const& backup) = 0; 
    virtual bool notifyRestore(SystemBackupInfo const& restore) = 0;

    virtual bool notifyBackup(QString const& backupId) = 0;

    virtual QString backupSystem() = 0; 
    virtual bool restoreSystem(QString const& backupId) = 0; 

    virtual bool getBackups(QList<SystemBackupInfo>& backups) = 0; 
    virtual bool delBackup(QString const& backupId) = 0; 

    virtual ~SystemBackupDAO(){}; 

};

Safety_API SystemBackupDAO&  backupDAO();

#endif






#ifndef Think_Safety_OperateLogDAO
#define Think_Safety_OperateLogDAO

#include <QtCore/QString>  
#include <QtCore/QList>  

#include <utils/Common.hpp>

#include <safety/SafetyDll.hpp> 
#include <safety/OperateLogInfo.hpp>

class Safety_API OperateLogDAO{
public:
    virtual void reLoad() = 0;

    virtual void queryLogs(QString const& startTime, QString const& endTime, QString const& subSys, QString const& operateGroup, QString const& operateName, 
        QString const& userName, QString const& operateObj, QString const& operateContent, QList<OperateLogInfo>& logs) = 0;
     
    virtual void importLogs(QList<OperateLogInfo>& logs) = 0;

    virtual ~OperateLogDAO(){}; 

};

Safety_API OperateLogDAO&  operateLogDAO();

#endif





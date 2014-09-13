#include <safety/SafeSubSysDAO.hpp>
#include <safety/SafeSubSysInfo.hpp>

#include <utils/HttpClient.hpp>

#define REQ_SAFETY_SUBSYS_QUERY     "/think/fast/safe/subSys/query" 

class SafeSubSysDAOImpl: public SafeSubSysDAO   
{
public:
    virtual void reLoad()
    {
        listSubSys.clear();

        mapSubSysId.clear();
        mapSubSysName.clear();
        
        QList<SafeSubSysInfo> subSyss;
        QJsonObject rspMsg = httpClient().postJson(REQ_SAFETY_SUBSYS_QUERY);
        if (!httpClient().verifyResponse(rspMsg))
        {
            return;
        }

        SafeSubSysInfo::fromJsons(rspMsg, listSubSys);

        foreach (SafeSubSysInfo subSys, listSubSys)
        {
            mapSubSysId[subSys.id] = subSys;
            mapSubSysName[subSys.name] = subSys; 
        }

        return;
    }

    virtual QList<SafeSubSysInfo> querySubSyss()
    { 
        return listSubSys;
    }

    virtual QStringList querySubSysNames()
    {
        QStringList subSysNames;
        QList<SafeSubSysInfo> subSyss;
        subSyss = this->querySubSyss();
        int subSysCount = subSyss.size();
        for (int indexSubSys = 0; indexSubSys < subSysCount; indexSubSys++)
        {
            subSysNames.push_back(subSyss[indexSubSys].name);
        }

        subSysNames.sort();
        return subSysNames;

    }

    virtual SafeSubSysInfo querySubSysById(QString const& subSysId) 
    {
        if (!mapSubSysId.contains(subSysId))
        {
            SafeSubSysInfo emptySubSys;
            return emptySubSys; 
        }

        return mapSubSysId[subSysId];
    }

    virtual SafeSubSysInfo querySubSysByName(QString const& subSysName)
    {
        if (!mapSubSysName.contains(subSysName))
        {
            SafeSubSysInfo emptySubSys;
            return emptySubSys; 
        }

        return mapSubSysName[subSysName];

    }

    virtual ~SafeSubSysDAOImpl()
    {

    } 

    static SafeSubSysDAO* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new SafeSubSysDAOImpl();
        }

        _instance->reLoad();

        return _instance;
    }

private:
    SafeSubSysDAOImpl()
    {

    }

private:
    QList<SafeSubSysInfo> listSubSys;
    QMap<QString, SafeSubSysInfo> mapSubSysId;
    QMap<QString, SafeSubSysInfo> mapSubSysName;

private:
    static SafeSubSysDAO* _instance; 

};

SafeSubSysDAO* SafeSubSysDAOImpl::_instance = NULL; 

SafeSubSysDAO& safeSubSysDAO()
{ 
    return *(SafeSubSysDAOImpl::getInstance());
} 



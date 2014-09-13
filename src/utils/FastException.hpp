#ifndef Think_Utils_Fast_Exception
#define Think_Utils_Fast_Exception

#include <utils/UtilsDll.hpp>

#include <QtCore/QDebug>
#include <QtCore/QString>

class FastException
{
public:
    FastException(QString const & msgInfo)
    {
        this->_msgId = "";
        this->_msgInfo = msgInfo.trimmed();
        this->_msgDetail = "";

        qDebug()<<"fast exception, msgInfo:" <<_msgInfo;
    }
     
    FastException(QString const& msgId, QString const & msgInfo)
    { 
        this->_msgId = msgId.trimmed();
        this->_msgInfo = msgInfo.trimmed();
        this->_msgDetail = "";

        qDebug()<<"fast exception, msgId:"<<_msgId<<",msgInfo:"<<_msgInfo;
    }

    FastException(QString const& msgId, QString const & msgInfo, QString const & msgDetail)
    {
        this->_msgId = msgId.trimmed();
        this->_msgInfo = msgInfo.trimmed();
        this->_msgDetail = msgDetail.trimmed();

        qDebug()<<"fast exception, msgId:"<<_msgId<<",msgInfo:"<<_msgInfo<<",msgDetail:"<<_msgDetail;
    }

    ~FastException()
    {

    }

public:
    void print() const
    {
        qDebug()<<toString();
    }

    QString toString() const
    {
        QString strInfo = QString("fast exception, msgId:%1,msgInfo:%2,msgDetail:%3").arg(_msgId, _msgInfo, _msgDetail);
        return strInfo;
    }

    QString const& getId() const
    {
        return _msgId;
    }

    QString const& getInfo() const
    {
        return _msgInfo;
    }

    QString const& getDetail() const
    {
        return _msgDetail;
    }

private:
    QString _msgId;
    QString _msgInfo;
    QString _msgDetail;

};


#endif

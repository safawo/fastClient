#ifndef Think_Utils_HttpDownLoader
#define Think_Utils_HttpDownLoader

#include <QtCore/QUrl>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>

#include <QtWidgets/QtWidgets>
#include <QtWidgets/QDialog>

#include <QtNetwork/QtNetwork> 
#include <QtNetwork/QNetworkAccessManager>

#include <utils/UtilsDll.hpp>
#include <utils/SystemMgr.hpp>

class Utils_API HttpDownLoader: public QObject
{
    Q_OBJECT

public:
    HttpDownLoader();
    ~HttpDownLoader();

public:
    QString start(QString const& reqPath, bool isForce = true);

private slots:
    void httpFinished();  
    void httpReadyRead();  
    void startRequest(QUrl url); 

private:
    QString downloadedFilePath;
    bool isDownloadSuccessful;

private:
    QUrl httpUrl;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QFile *file;

    int httpGetId;
    bool httpRequestAborted;

}; 

#endif



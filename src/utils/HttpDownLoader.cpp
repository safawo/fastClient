#include <utils/FastMsgBox.hpp> 
#include <utils/HttpDownLoader.hpp>  
#include <utils/HttpClientMgr.hpp>

#include <QtCore/QString>
#include <QtCore/QDebug>

HttpDownLoader::HttpDownLoader()
{ 

} 

HttpDownLoader::~HttpDownLoader()
{

} 

QString HttpDownLoader::start(QString const& reqPath, bool isForce)
{ 
    QString downloadFilePath = NULL_STR;

    httpUrl = QUrl(httpClientMgr().getReqUrl(reqPath)); 
     
    QFileInfo fileInfo(httpUrl.path());
    QString fileName = fileInfo.fileName();

    qDebug() << "downloadFile fileName:"<<fileName;
    if (fileName.isEmpty())
    {
        return downloadFilePath;
    } 

    QString filePathName = sys().getDownloadPath()+ "/" + fileName;

    if (QFile::exists(filePathName)) { 
        if (!isForce) {
            return filePathName;
        }
        QFile::remove(filePathName); 
    }

    file = new QFile(sys().getDownloadPath()+ "/"+fileName);
    if (!file->open(QIODevice::WriteOnly)) { 
        qDebug()<<tr("Unable to save the file %1: %2.").arg(fileName).arg(file->errorString());
        delete file;
        file = NULL;
        return filePathName;
    }

    //schedule the request
    httpRequestAborted = false;
    qDebug() << "downloadFile fileName url:"<<httpUrl.path();
    qDebug() << "downloadFile startRequest start";
    startRequest(httpUrl);
    qDebug() << "downloadFile startRequest end";
    qDebug() << "downloadFile isDownloadSuccessful:" << isDownloadSuccessful;
    qDebug() << "downloadFile downloadedFilePath:" << downloadedFilePath;

    if (!isDownloadSuccessful){
        filePathName = NULL_STR;
    }

    return filePathName;
}


void HttpDownLoader::httpFinished()
{
    if (httpRequestAborted) {
        if (file) {
            file->close();
            file->remove();
            delete file;
            file = 0;
        }
        reply->deleteLater();
        return;
    }

    file->flush();
    file->close();

    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error()) {
        file->remove(); 
        qDebug()<<tr("Download failed: %1.").arg(reply->errorString());

    } else if (!redirectionTarget.isNull()) {
        QUrl newUrl = httpUrl.resolved(redirectionTarget.toUrl()); 
        qDebug()<<tr("Redirect to %1 ?").arg(newUrl.toString());
        httpUrl = newUrl;
        reply->deleteLater();
        file->open(QIODevice::WriteOnly);
        file->resize(0);
        startRequest(httpUrl);
        return;
    } else {

        QString fileName = QFileInfo(httpUrl.path()).fileName();
        qDebug() << "Downloaded file:" <<  fileName << " to " << sys().getDownloadPath();
        if (QFile::exists(sys().getDownloadPath()+ "/" + fileName)) {
            downloadedFilePath = sys().getDownloadPath()+ "/" + fileName;
            isDownloadSuccessful = true;
        }
        //statusLabel->setText(tr("Downloaded %1 to %2.").arg(fileName).arg(sys().getClientDownloadPath()));
        //downloadButton->setEnabled(true);
    }

    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;
}

void HttpDownLoader::httpReadyRead()
{
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    if (file) {
        file->write(reply->readAll());
    }		
}

void HttpDownLoader::startRequest(QUrl url)
{
    QEventLoop eventLoop;
    reply = qnam.get(QNetworkRequest(url));

    QObject::connect(reply, SIGNAL(readyRead()),this, SLOT(httpReadyRead()));
    QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));

    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

    httpFinished();
}


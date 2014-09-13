#include <utils/HttpClient.hpp>
#include <utils/HttpClientMgr.hpp>
#include <utils/HttpDownLoader.hpp>

#include <utils/Utils.hpp>

#include <QtCore/QDebug>

#include <QtCore/QString>
#include <QtCore/QObject>

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonParseError>
#include <QtCore/QJsonObject>

#include <QtCore/QEventLoop>

#include <QtCore/QDateTime>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply> 

#include <QtNetwork/qnetworkreply.h>
#include <QtNetwork/qnetworkaccessmanager.h>

 
#include <utils/FastRequestInfo.hpp>
#include <utils/FastResponseInfo.hpp>


class HttpClientImpl: public HttpClient, public HttpClientMgr
{  
public: 
    virtual QJsonObject postJson(QString const& reqPath){
        QJsonObject reqMsg;
        return postJson(reqPath, reqMsg);
    }

    virtual QJsonObject postJson(QString const& reqPath, QJsonObject const& requestMsg){   
        QJsonObject reqMsg = requestMsg; 

        QJsonObject reqHeader;
        reqHeader.insert("reqSessionId", QJsonValue::fromVariant(getReqSessionId()));
        reqHeader.insert("reqActionId", QJsonValue(reqPath));
        reqHeader.insert("reqStartTime", QJsonValue(utils().YYYY_MM_DD_HH_MM_SS()));

        reqMsg.insert("header", QJsonValue(reqHeader));

        QJsonObject rspMsg; 
        QJsonObject rspHeader(reqHeader);

        if (getValidater() != NULL) {
            QString validateRet = NULL_STR;
            if (!getValidater()->checkRequest(getReqSessionId(), reqPath, validateRet)){
                rspHeader.insert("rspFinishTime", QJsonValue(utils().YYYY_MM_DD_HH_MM_SS()));  
                rspHeader.insert("rspRetLevel", QJsonValue::fromVariant(MSG_LEVEL_ERROR));
                rspHeader.insert("rspRetMsgDetail", QJsonValue::fromVariant("local response msg!"));

                rspHeader.insert("rspRetId", QJsonValue::fromVariant(validateRet));
                rspHeader.insert("rspRetMsg", QJsonValue::fromVariant("http request validate fail"));

                rspMsg.insert("header", QJsonValue(rspHeader));
                return rspMsg;
            }
        }
          
        QNetworkRequest request;
        request.setUrl(QUrl(getReqUrl(reqPath)));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=utf-8");    
 
        QJsonDocument reqDoc(reqMsg); 
        QByteArray reqByte = reqDoc.toJson(); 
        request.setHeader(QNetworkRequest::ContentLengthHeader, reqByte.length()); 
        
        qDebug()<<"http json request:" << reqPath;
        qDebug()<<reqByte; 

        QNetworkReply *reply = getNetMgr().post(request, reqByte);
        QEventLoop eventLoop;
        QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));

        eventLoop.exec(QEventLoop::ExcludeUserInputEvents);  
         
        rspHeader.insert("rspFinishTime", QJsonValue(utils().YYYY_MM_DD_HH_MM_SS()));  
        rspHeader.insert("rspRetLevel", QJsonValue::fromVariant(MSG_LEVEL_ERROR));
        rspHeader.insert("rspRetMsgDetail", QJsonValue::fromVariant("local response msg!"));

        if (reply->error() == QNetworkReply::TimeoutError){ 
            rspHeader.insert("rspRetId", QJsonValue::fromVariant("TIME_OUT"));
            rspHeader.insert("rspRetMsg", QJsonValue::fromVariant("conn time out"));
        } 
        else if (reply->error() == QNetworkReply::HostNotFoundError){  
            rspHeader.insert("rspRetId", QJsonValue::fromVariant("NOT_FIND_SERVER"));
            rspHeader.insert("rspRetMsg", QJsonValue::fromVariant("not find server"));
        }  
        else if (reply->error() == QNetworkReply::ConnectionRefusedError)
        {
            rspHeader.insert("rspRetId", QJsonValue::fromVariant("SERVER_SHUTDOWN"));
            rspHeader.insert("rspRetMsg", QJsonValue::fromVariant("server is shutdown"));
        }
        else if (reply->error() == QNetworkReply::ContentNotFoundError)
        {
            rspHeader.insert("rspRetId", QJsonValue::fromVariant("SERVER_REQ_NOT_FIND"));
            rspHeader.insert("rspRetMsg", QJsonValue::fromVariant("server request not find"));
        }
        else  
        {  
            rspHeader.insert("rspRetId", QJsonValue::fromVariant("UNKNOWN_NET_ERROR"));
            rspHeader.insert("rspRetMsg", QJsonValue::fromVariant("unknown net error")); 
        }   
        if (reply->error() != QNetworkReply::NoError){  
            rspMsg.insert("header", QJsonValue(rspHeader));

            qDebug()<<"http json response, local response msg:" << reqPath << ", replyCode:" <<reply->error();
            qDebug()<<QJsonDocument(rspMsg).toJson();

            return rspMsg;
        }

        rspHeader.insert("rspFinishTime", QJsonValue(utils().YYYY_MM_DD_HH_MM_SS()));  
        rspHeader.insert("rspRetLevel", QJsonValue::fromVariant(MSG_LEVEL_ERROR));
        rspHeader.insert("rspRetMsgDetail", QJsonValue::fromVariant("server error!"));

        QByteArray rspByte = reply->readAll();  
        qDebug()<<"http json response, server msg:" << reqPath;
        qDebug()<<rspByte; 
        QJsonParseError jsonParseError;
        QJsonDocument rspDoc = QJsonDocument::fromJson(rspByte, &jsonParseError);
        if (jsonParseError.error != QJsonParseError::NoError){ 
            rspHeader.insert("rspRetId", QJsonValue::fromVariant("DECODE_JSON_ERROR"));
            rspHeader.insert("rspRetMsg", QJsonValue::fromVariant("decode json error"));

            rspMsg.insert("header", QJsonValue(rspHeader)); 
            qDebug()<<"http json response, server error msg:" << reqPath;
            qDebug()<<QJsonDocument(rspMsg).toJson();
            return rspMsg;
        }
        
        if (rspDoc.isNull() || rspDoc.isEmpty()){  
            rspHeader.insert("rspRetId", QJsonValue::fromVariant("DECODE_JSON_EMPTY"));
            rspHeader.insert("rspRetMsg", QJsonValue::fromVariant("decode json is empty"));

            rspMsg.insert("header", QJsonValue(rspHeader)); 
            qDebug()<<"http json response, server error msg:" << reqPath;
            qDebug()<<QJsonDocument(rspMsg).toJson();
            return rspMsg;
        }
        
        if (!rspDoc.isObject()) {  
            rspHeader.insert("rspRetId", QJsonValue::fromVariant("DECODE_JSON_FORMAT_ERROR"));
            rspHeader.insert("rspRetMsg", QJsonValue::fromVariant("decode json format error"));

            rspMsg.insert("header", QJsonValue(rspHeader)); 
            qDebug()<<"http json response, server error msg:" << reqPath;
            qDebug()<<QJsonDocument(rspMsg).toJson();
            return rspMsg;
        } 

        rspMsg = rspDoc.object();
        return rspMsg; 
    }

	virtual QString download(QString const& reqPath, bool isForce){      
        HttpDownLoader* downLoader = new HttpDownLoader();
        if (downLoader == NULL) {
            return NULL_STR;
        }
         
        QString downloadFilePath = downLoader->start(reqPath, isForce);  

        delete downLoader;
        downLoader = NULL;

        return downloadFilePath;   
	}

    virtual bool upload(QString const& localFile){
        if (localFile.isEmpty()){
            return false;
        }        

        QFile file(localFile);
        if (!file.exists()){
            return false;
        }

        if (!file.open(QIODevice::ReadOnly)){
            file.close();
            return false;
        }        

        QFileInfo fileInfo(file);
         
        /*
        QNetworkRequest request;
        request.setUrl(QUrl(getReqUrl("/upload?file=" + fileInfo.fileName())));
        request.setHeader(QNetworkRequest::ContentTypeHeader,"application/octet-stream");
        QNetworkReply *reply = getNetMgr().post(request, &file);
        QEventLoop eventLoop;
        QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
        eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
        
        if (reply->error() != QNetworkReply::NoError){  
            qDebug()<<"HttpClientImpl::upload:.........ErroCode="<<reply->error();  
            file.close();
            return false;
        } 
        
        return true;
        */

        QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        QHttpPart filePart;
        
        //filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("multipart/form-data"));
        //filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\""));
          
        filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));
        filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uploadfile\";filename=\"" + fileInfo.fileName() + "\""));
         
        filePart.setBodyDevice(&file);
        file.setParent(multiPart);
        multiPart->append(filePart);

        QNetworkRequest request;
        request.setUrl(QUrl(getReqUrl("/upload")));
        QNetworkReply *reply = this->getNetMgr().post(request, multiPart); 
        multiPart->setParent(reply);

        QEventLoop eventLoop;
        QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
        eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
        if (reply->error() != QNetworkReply::NoError){  
            qDebug()<<"HttpClientImpl::upload:.........ErroCode="<<reply->error();   
            return false;
        }  

        return true;  
    }

    virtual bool verifyResponse(QJsonObject const& rspMsg){
        return FastResponseInfo::verify(rspMsg);
    }

    virtual bool verifyRespNoTip(QJsonObject const& rspMsg){
        return FastResponseInfo::verifyNoTip(rspMsg);
    }
	 
public:
    virtual HttpClient& getClient(){
        return *this;
    }

    virtual void resetServer(QString const& reqIp = FAST_REQ_JSON_IP_DEFAULT, QString const& reqPort = FAST_REQ_JSON_PORT_DEFAULT){
        this->_reqIp = reqIp.trimmed();
        this->_reqPort = reqPort.trimmed();

        if (this->_reqIp.isEmpty()){
            this->_reqIp = FAST_REQ_JSON_IP_DEFAULT;
        }

        if (this->_reqPort.isEmpty()){
            this->_reqPort = FAST_REQ_JSON_PORT_DEFAULT;
        } 
    }

    virtual void resetSession(QString const& sessionId = FAST_REQ_JSON_SESSION_INIT){
        this->_reqSessionId = sessionId.trimmed();
    }

    virtual void regValidater(FastSafeValidater* validater = NULL){
        this->_validater = validater;
    }

public: 
    QString& getReqIp() {
        return this->_reqIp;
    }

    QString& getReqPort() {
        return this->_reqPort;
    }

    QString& getReqSessionId() {
        return this->_reqSessionId;
    }

    FastSafeValidater* getValidater() {
        return this->_validater;
    }

    QString getReqUrl(QString const& reqPath) {
        QString reqUrl = "http://" + getReqIp() + ":" + getReqPort() + reqPath;
        return reqUrl;
    }

public:
    virtual ~HttpClientImpl(){
        if (NULL != _netMgr){
            delete _netMgr;
            _netMgr = NULL;
        } 
    }

public:
    static HttpClientImpl* getInstance() {
        if (_instance == NULL) {
            _instance = new HttpClientImpl();
        }

        return _instance;
    }

private:
    HttpClientImpl() {
        this->_reqIp = FAST_REQ_JSON_IP_DEFAULT;  
        this->_reqPort = FAST_REQ_JSON_PORT_DEFAULT;

        this->_reqSessionId = FAST_REQ_JSON_SESSION_INIT;

        this->_validater = NULL;

        this->_netMgr = new QNetworkAccessManager();
    }
      
private:
    QNetworkAccessManager& getNetMgr() {
        return *(this->_netMgr);
    }

private:
    static HttpClientImpl* _instance;

    QString _reqIp; 
    QString _reqPort;

    QString _reqSessionId;

    FastSafeValidater* _validater;

    QNetworkAccessManager* _netMgr;

};
  
HttpClientImpl* HttpClientImpl::_instance = NULL; 

HttpClient& httpClient(){ 
    return *(HttpClientImpl::getInstance());
} 
 
HttpClientMgr&  httpClientMgr(){
    return *(HttpClientImpl::getInstance());
}

#include <utils/FastMsgBox.hpp>

#include <QtCore/QString>
#include <QtCore/QDebug>
#include <QtWidgets/QMessageBox>
 
#include <QtGui/QIcon>
#include <utils/Common.hpp>

#include <utils/FastMessageBox.hpp>
#include <utils/MyMessageBox.hpp>
//msg.setIconPixmap(QPixmap(":/hotelRes/Resources/msgBoxInfo.ico"));  
//msg.setStyleSheet("background-image: url(:/hotelRes/Resources/msgBoxMain.png);font: 18pt \"Arial\";");
#define  styleSheetMsg "background-color: rgb(255, 255, 255);color: rgb(31, 31, 31);font-family: \"Arial\";font-size: 18px;"

class FastMsgBoxImpl: public FastMsgBox  
{

public:
    virtual void information(QString const& infoMsg, QString const& informative)
    { 
		
        //QMessageBox msg(QMessageBox::Information, "Information", "");
        MyMessageBox msg(QMessageBox::Information, "Information", "");
		msg.setWindowTitle("Information");
		msg.setIcon(QMessageBox::Information);
		msg.setText(infoMsg);
		msg.setStyleSheet(styleSheetMsg);
        //msg.setText("<br><font face='Arial' size='5'>" + infoMsg + "</font><br>"); 
		
        if (informative != NULL_STR)   
        {
            msg.setInformativeText(informative);    
        }
        msg.exec();
		
// 		MsgBoxDIY *msg_box = new MsgBoxDIY();
// 		msg_box->setInfo(QString("jinjie"),QString("DIY message"),
// 			QPixmap(":/hotelRes/Resources/msgBoxMain.png"), true, false);
// 		msg_box->exec();
        return;
         
    }

    virtual bool question(QString const& questMsg, QString informative)
    {
        /*
        int result = QMessageBox::question(NULL, "Question", questMsg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if (result == QMessageBox::Yes)
        {
            return true;
        }
        */
	
        //MessageBox msg(QMessageBox::Question, "Question", ""); 
		MyMessageBox msg(QMessageBox::Question, "Question", ""); 
        msg.addButton(QMessageBox::Yes);
        msg.addButton(QMessageBox::No);
        msg.setDefaultButton(QMessageBox::Yes);
		msg.setWindowTitle("Question");
		msg.setIcon(QMessageBox::Question);
        msg.setText(questMsg);
		msg.setStyleSheet(styleSheetMsg);
		//msg.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
		//msg.setContentsMargins(50,50,50,50);
        if (informative != NULL_STR)   
        {
            msg.setInformativeText(informative);    
        }
        if (msg.exec() == QMessageBox::Yes)
        {
            return true;
        } 

        return false; 
		

	/*	
		MsgBoxDIY* msg_box = MsgBoxDIY::getInstance();
		msg_box->setInfo(QString("Question"),QString(questMsg),
			QPixmap(":/hotelRes/Resources/msgBoxMain.png"), false);
		msg_box->exec();
		qDebug()<< "msg_box->m_operatorValue:"<< msg_box->m_operatorValue;
		if (msg_box->m_operatorValue == 1)
		{
			qDebug()<<"msg_box->openShow()1"<< msg_box->m_operatorValue;
			return true;
		}
		else if(msg_box->m_operatorValue == 2)
		{
			qDebug()<<"msg_box->openShow()2"<<msg_box->m_operatorValue;
			return false;
		}
		*/
    }

	virtual bool warning(QString const& warnMsg, QString informative)
	{
        //QMessageBox msg(QMessageBox::Warning, "Warning", "");
		MyMessageBox msg(QMessageBox::Warning, "Warning", "");
		msg.setWindowTitle("Warning");
		msg.setIcon(QMessageBox::Warning);
		msg.setText(warnMsg);
		msg.setStyleSheet(styleSheetMsg);
        //msg.setText("<br><font face='Arial' size='5'>" + warnMsg + "</font><br>");

        if (informative != NULL_STR)   
        {
            msg.setInformativeText(informative);    
        }
        msg.exec();

        return true;
	}

    virtual void error(QString const& errorMsg, QString informative)
    {
        //QMessageBox msg(QMessageBox::Critical, "Error", "");
		MyMessageBox msg(QMessageBox::Critical, "Error", "");
		msg.setWindowTitle("Error");
		msg.setIcon(QMessageBox::Critical);
		msg.setText(errorMsg);
		msg.setStyleSheet(styleSheetMsg);
        //msg.setText("<br><font face='Arial' size='5'>" + errorMsg + "</font><br>");

        if (informative != NULL_STR)   
        {
            msg.setInformativeText(informative);    
        }
        msg.exec();

        return;
    }

    virtual void information(QString const& infoMsg)
    {
        this->information(infoMsg, NULL_STR);
    }

    virtual bool question(QString const& questMsg)
    {
        return this->question(questMsg, NULL_STR);
    }

    virtual bool warning(QString const& warnMsg)
    {
        return this->warning(warnMsg, NULL_STR);
    }

    virtual void error(QString const& errorMsg)
    {
        this->error(errorMsg, NULL_STR);
    }

    virtual void operateSuccess()
    {
        this->information("Operate successfully");
    }
     
    virtual ~FastMsgBoxImpl()
    {

    }

    static FastMsgBox* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new FastMsgBoxImpl();
        }

        return _instance;
    }

private:
    FastMsgBoxImpl()
    {

    }

private:
    static FastMsgBox* _instance;

};

FastMsgBox* FastMsgBoxImpl::_instance = NULL;

FastMsgBox& msgBox()
{
    return *(FastMsgBoxImpl::getInstance());
}


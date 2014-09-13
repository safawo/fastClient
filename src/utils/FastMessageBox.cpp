#include <utils/FastMessageBox.hpp>
#include <QMouseEvent>
#include <QPainter>
#include <QBitmap>
#include <QDebug>

MsgBoxDIY* MsgBoxDIY::_instance = NULL;

MsgBoxDIY::MsgBoxDIY(QWidget* parent)
	:QDialog(parent),close_button(NULL),title_label(NULL),msg_label(NULL),
	ask_label(NULL),cancel_button(NULL),ok_button(NULL), m_operatorValue(1)
{
	_instance = NULL;
	this->resize(320, 160);
	//获取主界面的宽度
	int width = this->width();
	int height = this->height();
	//初始化为未按下鼠标左键
	mouse_press = false;
	//设置标题栏隐藏
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

	close_button = new QPushButton(this);
	close_button->setStyleSheet(QLatin1String("QPushButton{ border-image: url(:/hotelRes/Resources/metro/close.png); }\n"
		"QPushButton:hover{ border-image: url(:/hotelRes/Resources/metro/close1.png); }"));
	close_button->setGeometry(width-30, 0, 32, 19); 

	//设置标题
	title_label = new QLabel(this);
	title_label->setObjectName(QString::fromUtf8("labelOne"));
	QFont font = title_label->font();
	font.setBold(true);
	title_label->setFont(font);
	title_label->setGeometry(0, 0, width-50, 30);
	//设置提示图片
	msg_label = new QLabel(this);
	msg_label->setGeometry(20, 50, 36, 36);
	msg_label->setScaledContents(true);
	//设置提示信息，让QLabel能够自动判断并换行显示：
	ask_label = new QLabel(this);
	ask_label->setGeometry(65, 60, width-100, 25*2);
	ask_label->setWordWrap(true);
	ask_label->setAlignment(Qt::AlignTop);

	//check_box = new QCheckBox(this);
	//check_box->setGeometry(10, height - 35, 160, 25);
	//check_box->setHidden(true);
	cancel_button = new QPushButton(this);
	cancel_button->resize(70, 25);
	cancel_button->move(width - cancel_button->width() - 10, height - 35);
	ok_button = new QPushButton(this);
	ok_button->resize(70, 25);
	ok_button->move(width - ok_button->width() - cancel_button->width() - 20, height - 35);
	//check_box->setStyleSheet("background:transparent;");
	ok_button->setObjectName(QString::fromUtf8("pushButtonOk"));
	cancel_button->setObjectName(QString::fromUtf8("pushButtonCancel"));

	QObject::connect(ok_button, SIGNAL(clicked()), this, SLOT(okOperate()));
	QObject::connect(close_button, SIGNAL(clicked()), this, SLOT(cancelOperate()));
	QObject::connect(cancel_button, SIGNAL(clicked()), this, SLOT(cancelOperate()));
	this->translateLanguage();
	
}
MsgBoxDIY::~MsgBoxDIY()
{
	if (close_button != NULL)
	{
		delete close_button;
		close_button = NULL;
	}
	if (title_label != NULL)
	{
		delete title_label;
		title_label = NULL;
	}
	if (msg_label != NULL)
	{
		delete msg_label;
		msg_label = NULL;
	}
	if (ask_label != NULL)
	{
		delete ask_label;
		ask_label = NULL;
	}
	if (cancel_button != NULL)
	{
		delete cancel_button;
		cancel_button = NULL;
	}
	if (ok_button != NULL)
	{
		delete ok_button;
		ok_button = NULL;
	}
	
}
void MsgBoxDIY::translateLanguage()
{
	close_button->setToolTip(tr("close"));
	//check_box->setText(tr("remember"));
	ok_text = tr("ok");
	cancel_text = tr("cancel");
}
void MsgBoxDIY::setInfo(QString title_info, QString info, QPixmap pixmap, bool is_ok_hidden)
{
	title_label->setText(QString("  ") + title_info);
	//设置提示信息
	ask_label->setText(info);
	msg_label->setPixmap(pixmap);
	//是否隐藏确定按钮
	ok_button->setHidden(is_ok_hidden);
	if(is_ok_hidden)
	{
		cancel_button->setText(ok_text);
	}
	else
	{
		ok_button->setText(ok_text);
		cancel_button->setText(cancel_text);
	}
	//设置默认按钮为取消按钮
	cancel_button->setFocus();
}

// bool MsgBoxDIY::openShow()
// {
// 	this->exec();
// 	return true;
// 	
// }
void MsgBoxDIY::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawPixmap(rect(), QPixmap(":/icon/tip"));
	QBitmap bitmap(this->size());
	QPainter painter2(&bitmap);
	painter2.fillRect(bitmap.rect(), Qt::white);
	painter2.setBrush(QColor(0, 0, 0));
	painter2.drawRoundedRect(rect(), 4, 4);
	setMask(bitmap);
}
void MsgBoxDIY::mousePressEvent( QMouseEvent * event )
{
	//只能是鼠标左键移动和改变大小
	if(event->button() == Qt::LeftButton)
	{
		mouse_press = true;
	}
	//窗口移动距离
	move_point = event->globalPos() - pos();
}
void MsgBoxDIY::mouseReleaseEvent( QMouseEvent *)
{
	mouse_press = false;
}
void MsgBoxDIY::mouseMoveEvent(QMouseEvent *event)
{
	//移动窗口
	if(mouse_press)  
	{
		QPoint move_pos = event->globalPos();
		move(move_pos - move_point);
	}
}
void MsgBoxDIY::okOperate()
{
	//qDebug() << "okOperate1:" <<this->isPressOK;
	m_operatorValue = 1; 
	this->close();
	//qDebug() << "okOperate2:" <<this->isPressOK;
}

void MsgBoxDIY::cancelOperate()
{
	//qDebug() << "cancelOperate1:" <<this->isPressOK;
	m_operatorValue = 2;
	this->close();
	//qDebug() << "cancelOperate2:" <<this->isPressOK;
}

MsgBoxDIY* MsgBoxDIY::getInstance()
{
	if (_instance == NULL)
	{
		_instance = new MsgBoxDIY();
	}

	return _instance;
}
// 
// MsgBoxDIY& msgBoxDIY()
// {
// 	return *(MsgBoxDIY::getInstance());
// }
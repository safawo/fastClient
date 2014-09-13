#ifndef Think_Utils_Fast_MessageBoxDIY
#define Think_Utils_Fast_MessageBoxDIY

#include <QtWidgets/QDialog>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QString>
#include <QPoint>

class MsgBoxDIY: public QDialog
{
	Q_OBJECT

public:
	MsgBoxDIY(QWidget* parent = 0);
	~MsgBoxDIY();

public:
	void setInfo(QString title_info, QString info, QPixmap pixmap, bool is_ok_hidden);
    //bool openShow();
public:
	void translateLanguage();
public Q_SLOTS:
	void okOperate();
	void cancelOperate();
protected:	
	void mouseReleaseEvent( QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent( QMouseEvent * event );
	void paintEvent(QPaintEvent *);

private:
	bool mouse_press; 
	QPushButton* close_button;
	QLabel* title_label;
	QLabel* msg_label;
	QLabel* ask_label;
	QPushButton* cancel_button;
	QPushButton* ok_button;
	QString ok_text;
	QString cancel_text;
	QPoint move_point;


public:
	static MsgBoxDIY* getInstance();
private:
	static MsgBoxDIY* _instance;
public:
	int m_operatorValue;
};

#endif

//MsgBoxDIY& msgBoxDIY();
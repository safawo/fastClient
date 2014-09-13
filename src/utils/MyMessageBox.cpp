#include <MyMessageBox.hpp>

MyMessageBox::MyMessageBox(QWidget *parent) :
  QMessageBox(parent)
{

}

  MyMessageBox::MyMessageBox(Icon icon, const QString &title, const QString &text,
	  StandardButtons buttons, QWidget *parent,Qt::WindowFlags flags) :
QMessageBox(parent)
{

}

MyMessageBox::~MyMessageBox()
{

}

void MyMessageBox::showEvent(QShowEvent* event)
{
	QMessageBox::showEvent(event);

	QWidget  *textField = findChild<QWidget*>("qt_msgbox_label");

	if(textField  != NULL)

	{

		textField ->setMinimumSize(280, 80);
	}
	//setFixedSize(640, 480);

	QMessageBox::showEvent(event);
}
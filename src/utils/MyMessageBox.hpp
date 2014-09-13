#ifndef Think_Utils_Fast_MyMessageBox
#define Think_Utils_Fast_MyMessageBox
#include <QMessageBox>

class MyMessageBox : public QMessageBox {

public:
	MyMessageBox(QWidget* parent=0);
	MyMessageBox(Icon icon, const QString &title, const QString &text,
		StandardButtons buttons = NoButton, QWidget *parent = 0,
		Qt::WindowFlags flags = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	~MyMessageBox();

protected:
	void showEvent(QShowEvent* event);
	
};


#endif

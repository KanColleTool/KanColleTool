#ifndef KCGAMEWINDOW_H
#define KCGAMEWINDOW_H

#include <QMainWindow>
#include <QWebView>

class KCGameWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit KCGameWindow(QWidget *parent = 0);
	
protected:
	QWebView *webView;
};

#endif // KCGAMEWINDOW_H

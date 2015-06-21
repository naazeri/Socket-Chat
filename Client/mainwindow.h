#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_actionExit_triggered();
	void on_actionClear_triggered();
	void on_btn_send_clicked();
	void on_btn_connect_clicked();

	void connected();
	void disconnected();
	void readData();

	void on_btn_search_clicked();

private:
	Ui::MainWindow *ui;

	QTcpSocket *socket;
	bool condition;

	void initSocket();
	void findIP();
};

#endif // MAINWINDOW_H

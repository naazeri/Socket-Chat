#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

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
	void on_btn_start_clicked();
	void on_btn_send_clicked();

	void newConnection();
	void readData();

private:
	Ui::MainWindow *ui;

	QTcpServer *server;
	QTcpSocket *socket;
	bool condition;

	void findIP();
	void start();
	void stop();
	void initServer();
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QNetworkInterface>
//#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow), condition(false)
{
	ui->setupUi(this);

	server = new QTcpServer(this);
	socket = new QTcpSocket(this);

}

MainWindow::~MainWindow() {

	server->close();
	socket->close();
	delete ui;

}

void MainWindow::newConnection() {

	socket = server->nextPendingConnection();
	ui->label_reciveText->setText("Connected :)\n-----------\n\n");

	connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));

}

void MainWindow::readData() {

	QString data(socket->readAll());
	ui->label_reciveText->setText(ui->label_reciveText->text() + data);

}

void MainWindow::on_actionExit_triggered() {

	MainWindow::close();

}

void MainWindow::on_actionClear_triggered() {

	ui->label_reciveText->clear();

}

void MainWindow::on_btn_start_clicked() {

	if (!condition) {

		start();

	}

	else {

		stop();

	}

}

void MainWindow::on_btn_send_clicked() {

	socket->write(ui->lineEdit_sendText->text().toUtf8() + "\n");
	ui->lineEdit_sendText->clear();

}

void MainWindow::start() {

	initServer();
	findIP();

	ui->btn_start->setText("Stop");
	ui->btn_send->setEnabled(true);

	condition = true;

}

void MainWindow::stop() {

	server->close();
	socket->close();

	ui->btn_start->setText("Start");
	ui->btn_send->setEnabled(false);

	condition = false;

}

void MainWindow::initServer() {

	server->listen(QHostAddress::Any, ui->lineEdit_port->text().toInt());

	connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

}

void MainWindow::findIP() {

	bool first = true;

	foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {

		if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost)) {

			if(first) {

				ui->label_reciveText->setText(
							+ "My IP is:\n"
							+ address.toString());

				first = false;

			}

			else {
				ui->label_reciveText->setText(
							ui->label_reciveText->text()
							+ "\n" + address.toString());
			}
		}
	}

	if (first) {

		ui->label_reciveText->setText("We dont have IP. You can use Localhost IP.\n"
									  "Localhost IP is: 127.0.0.1\n-------------------------------------\n");

	}

	else {

		ui->label_reciveText->setText(ui->label_reciveText->text()
									  + "\n---------------------\n");
	}


}


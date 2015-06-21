#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork/QHostAddress>
#include <QNetworkInterface>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	condition(false)
{

	ui->setupUi(this);

	socket = new QTcpSocket(this);

	initSocket();

}

MainWindow::~MainWindow() {

	socket->close();
	delete ui;

}

void MainWindow::initSocket() {

	connect(socket, SIGNAL(connected()), this, SLOT(connected()));
	connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
	connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));

}

void MainWindow::connected() {

	ui->btn_send->setEnabled(true);
	ui->btn_search->setEnabled(false);
	ui->btn_connect->setText("Disconnect");
	ui->label_reciveText->setText("Connected :)\n-----------\n\n");

	condition = true;

}

void MainWindow::disconnected() {

	ui->btn_send->setEnabled(false);
	ui->btn_search->setEnabled(true);
	ui->btn_connect->setText("Connect");

	condition = false;

}

void MainWindow::readData() {

	QString data(socket->readAll());
	ui->label_reciveText->setText(ui->label_reciveText->text() + data);

}

void MainWindow::on_actionClear_triggered() {

	ui->label_reciveText->clear();

}

void MainWindow::on_actionExit_triggered() {

	MainWindow::close();

}

void MainWindow::on_btn_send_clicked() {

	socket->write(ui->led_sendText->text().toUtf8() + "\n");
	ui->led_sendText->clear();

}

void MainWindow::on_btn_connect_clicked() {

	QHostAddress address(ui->led_ip->text());

	if (!condition) {

		socket->connectToHost(address, ui->led_port->text().toInt());

	}

	else {

		socket->disconnectFromHost();

	}
}

void MainWindow::findIP() {

	bool first = true;

	foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {

		if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost)) {

			if(first) {

				ui->label_reciveText->setText(
							+ "These Servers are found:\n"
							+ address.toString());

				ui->led_ip->setText(address.toString());
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

		ui->label_reciveText->setText("We Cant find any Server. You can use Localhost IP.\n"
									  "Localhost IP is: 127.0.0.1\n-------------------------------------\n");

		ui->led_ip->setText("127.0.0.1");

	}

	else {

		ui->label_reciveText->setText(ui->label_reciveText->text()
									  + "\n--------------------\n");
	}

}

void MainWindow::on_btn_search_clicked() {

	findIP();

}

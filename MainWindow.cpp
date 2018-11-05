#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QListWidget"
#include "QListWidgetItem"
#include "QVBoxLayout"
#include "QMessageBox"
#include <QtNetwork/QHostInfo>
#include <QtNetwork/QHostAddress>
#include <QTextBlock>
#include "string"
#include "string.h"
#include "qicon.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setPersons();
    this->setStyleSheet("background-color: rgb(41,57,85)");
    ui->header->setStyleSheet("background-color:rgb(77,96,130)");

	ui->person_lw->setSelectionMode(QAbstractItemView::ExtendedSelection);
	ui->person_lw->setGeometry(45, 30, 115, 525);
	ui->person_lw->setIconSize(QSize(150, 105));
	ui->person_lw->setViewMode(QListWidget::IconMode);
	ui->person_lw->setStyleSheet("QListWidget{border: 2px solid rgb(204,206,219);background-color:rgb(77,96,120)}");

    ui->update->setStyleSheet("QPushButton{border: 2px solid rgb(77,96,130);background-color:rgb(214,219,233)}");
    ui->stackedWidget->setCurrentIndex(1);
	ui->title->setStyleSheet("background-color:rgb(255,255,255)");
	ui->code->setStyleSheet("background-color:rgb(255,255,255)");
	
	/*根据节点改*/
	ch->getfiles("node1");

	ch->setParent(this);
    ch->move(190,115);
    ch->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPersons(){
	QStringList persons;
	int n = this->geti();
	ui->person_lw->clear();
	int j = 1;
	for (int i = 1; i <= 5; i++)
		if (i != n) {
			QListWidgetItem *item = new QListWidgetItem(ui->person_lw, 0);
			item->setIcon(QIcon(":/MainWindow/Resources/cp_on.png"));
			item->setText("node" + QString::number(i));
			ui->person_lw->insertItem(j++, item);
		}
}

void MainWindow::getHistory(QString ip){
	ch->getfiles(ip);
	ch->show();
}

int MainWindow::geti()
{/*
	QString ips[] = { "169.254.142.196" };//输入全员ip??????????
	QString ip;
	QString localHostName = QHostInfo::localHostName();
	QHostInfo info = QHostInfo::fromName(localHostName);
	foreach(QHostAddress address, info.addresses())
	{
		if (address.protocol() == QAbstractSocket::IPv4Protocol) {
			ip = address.toString();
			break;
		}
	}
	int i = 1;
	for (; i <= 5; i++)
		if (ips[i - 1] == ip)
			break;
			*/
	QString s = "node" + QString::number(1);
	ui->user_ip->setText(s);
	/*根据节点改*/
	return 1;
}



void MainWindow::on_team_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ch->show();
}

void MainWindow::on_submit_clicked()//存到文件中
{
    ui->stackedWidget->setCurrentIndex(0);
    ch->close();
}

void MainWindow::on_person_lw_itemClicked(QListWidgetItem *item)//向指定对象发送请求获取
{
	QString node = item->text();
	auto i = Luxijun::getInstance();
	qDebug("node is %s", qPrintable(node));
	reusePub AtoOther;//根据person决定pub
	if (!node.compare("node2"))
	{
		//i->msgListB.clear();
		AtoOther.createConnection("AB", "msgab");
		AtoOther.pubMsg(1, "ask", "-1", "000000");//时间为-1的消息为请求
	}
	else if (!node.compare("node3"))
	{
		i->msgListC.clear();
		AtoOther.createConnection("AC", "msgac");
		AtoOther.pubMsg(1, "ask", "-1", "000000");//时间为-1的消息为请求
	}
	else if (!node.compare("node4"))
	{
		i->msgListD.clear();
		AtoOther.createConnection("AD", "msgad");
		AtoOther.pubMsg(1, "ask", "-1", "000000");//时间为-1的消息为请求
	}
	else if (!node.compare("node5"))
	{
		i->msgListE.clear();
		AtoOther.createConnection("AE", "msgae");
		AtoOther.pubMsg(1, "ask", "-1", "000000");//时间为-1的消息为请求
	}
	else
		AtoOther.createConnection("AB", "msgab");
	qDebug("Pub Access");
	AtoOther.endDelete();
	qDebug("PubDelete ShowHistory");
    getHistory(item->text());
}


void MainWindow::on_update_clicked()
{
	Files * c = new Files(ui->user_ip->text(), ui->title->document()->toPlainText(), ui->code->document()->lineCount());
	for (int i = 0; i<c->linenum; i++) {
		c->words += ui->code->document()->findBlockByLineNumber(i).text();
	}
	c->save();
}
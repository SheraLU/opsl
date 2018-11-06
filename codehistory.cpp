#include "codehistory.h"
#include "ui_codehistory.h"
#include "QMessageBox"
#include <Files.h>
#include <io.h>
#include<direct.h>
#include"qdebug.h"
using namespace std;
vector<Code> history;
int flag = 0;

CodeHistory::CodeHistory(QWidget *parent,QString person_ip) :
    QWidget(parent),
    ui(new Ui::CodeHistory)
{
    ui->setupUi(this);
	flag = 0;
	/*根据节点改变*/
	getfiles("node1");

    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);hide();
    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setStyleSheet("background-color:#cccedb");
    ui->code->setStyleSheet("background-color: rgb(255,255,255)");
    ui->uptime->setStyleSheet("background-color: rgb(255,255,255)");
}

CodeHistory::~CodeHistory()
{
    delete ui;
}

//根据消息队列设置
void CodeHistory::on_uptime_itemClicked(QListWidgetItem *item)
{
	qDebug() << item->text().toStdString().c_str();
	if (item->text().compare("NULL")==0)
		ui->code->setText("暂无数据");
	else
	{
		if (flag) 
		{
			/*string word;
			fstream filein;
			filein.open(".\\code\\"+item->text().toStdString(), ios::in);
			filein >> word;
			ui->code->setText(QString::fromStdString(word));*/
			//ui->code->setText("导入失败");
			Files* f = new Files("","",0);
			f->fname = item->text();
			f->get();
			ui->code->setText(f->words);

		}
		else
		{
			for (int i = 0; i < history.size(); i++)
			{
				QString fN = history[i].fileName;
				QString fC = history[i].codeContent;
				if (fN.compare(item->text()) == 0)
				{
					ui->code->setText(fC);
					break;
				}
			}
		}
	}
}



void getFiles(string path, vector<string>& files)
{
	// 文件句柄
	long long hFile = 0;
	// 文件信息
	struct _finddata_t fileinfo;

	string p;

	if ((hFile = _findfirst(p.assign(path).append("\\*.txt").c_str(), &fileinfo)) != -1) {
		while(1) {
			// 保存文件的全路径
			files.push_back(p.assign(fileinfo.name));
			qDebug("%s",fileinfo.name);
			if (_findnext(hFile, &fileinfo))
				break;
		} //寻找下一个，成功返回0，否则-1

		_findclose(hFile);
	}
}


//获取消息队列中的信息
void CodeHistory::getfiles(QString ip){
	ui->uptime->clear();
	flag = 0;
    QStringList times;
	QString time;
	auto i = Luxijun::getInstance();
	qDebug("getFiles %s", qPrintable(ip));
	if (ip.compare("node1") == 0)
	{
		flag = 1;
		vector<string> fs;
		getFiles("D:\\materials\\TISHE\\HDE\\x86_64.win64\\opslTest\\CodeManagerTest\\CodeManager\\code", fs);
		char str[100];
		int size = fs.size();
		for (int i = 0; i < size; i++)
			times.append(fs[i].c_str());
	}
	else if (ip.compare("node2")==0) 
	{
		history =i->msgListB;
		cout << "Bsize:" << i->msgListB.size() << endl;
	}
	else if (ip.compare("node3") == 0)
	{
		history = i->msgListC;
		cout << "Csize:" << i->msgListC.size() << endl;
	}
	else if (ip.compare("node4") == 0)
	{
		history = i->msgListD;
		cout << "Dsize:" << i->msgListD.size() << endl;
	}
	else if (ip.compare("node5") == 0)
	{
		history = i->msgListE;
		cout << "Esize:" << i->msgListE.size() << endl;
	}
	for (int k = 0; k < 10; k++)
	{
		if (k >= history.size())  break;
		time = history[history.size()-k-1].fileName;
		times.append(time);
	}
	if (times.empty())
	{
		qDebug("time is null");
		times.append("NULL");
	}
	ui->uptime->insertItems(1,times);
}
